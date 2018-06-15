/*
  Hatari - midi.c

  This file is distributed under the GNU General Public License, version 2
  or at your option any later version. Read the file gpl.txt for details.

  MIDI communication.
  Note that this code is far from being perfect. However, it is already
  enough to let some ST programs (e.g. the game Pirates!) use the host's midi
  system.

  TODO:
   - Most bits in the ACIA's status + control registers are currently ignored.
   - Check when we have to clear the ACIA_SR_INTERRUPT_REQUEST bit in the
     ACIA status register (it is currently done when reading or writing to
     the data register, but probably it should rather be done when reading the
     status register?).
*/
const char Midi_fileid[] = "Hatari midi.c : " __DATE__ " " __TIME__;

#include <libretro.h>
#include <SDL_types.h>

#include "main.h"
#include "configuration.h"
#include "ioMem.h"
#include "m68000.h"
#include "mfp.h"
#include "midi.h"
#include "file.h"
#include "acia.h"
#include "clocks_timings.h"


#define ACIA_SR_INTERRUPT_REQUEST  0x80
#define ACIA_SR_TX_EMPTY           0x02
#define ACIA_SR_RX_FULL            0x01


struct retro_midi_interface *MidiRetroInterface;
static Uint64 MidiWriteClockCounter;

static Uint8 MidiControlRegister;
static Uint8 MidiStatusRegister;
static Uint8 nRxDataByte;


/**
 * Initialization: Open MIDI device.
 */
void Midi_Init(void)
{
	MidiWriteClockCounter = 0;
}


/**
 * Close MIDI device.
 */
void Midi_UnInit(void)
{
	CycInt_RemovePendingInterrupt(INTERRUPT_MIDI);
}


/**
 * Reset MIDI emulation.
 */
void Midi_Reset(void)
{
	MidiControlRegister = 0;
	MidiStatusRegister = ACIA_SR_TX_EMPTY;
	nRxDataByte = 1;
	MidiWriteClockCounter = 0;

	if (MidiRetroInterface)
		CycInt_AddRelativeInterrupt(2050, INT_CPU_CYCLE, INTERRUPT_MIDI);
	else
		CycInt_RemovePendingInterrupt (INTERRUPT_MIDI);
}


/**
 * Read MIDI status register ($FFFC04).
 */
void Midi_Control_ReadByte(void)
{
	LOG_TRACE(TRACE_MIDI, "MIDI: ReadControl -> $%x\n", MidiStatusRegister);

	ACIA_AddWaitCycles ();						/* Additional cycles when accessing the ACIA */

	IoMem[0xfffc04] = MidiStatusRegister;
}


/**
 * Write to MIDI control register ($FFFC04).
 */
void Midi_Control_WriteByte(void)
{
	ACIA_AddWaitCycles ();						/* Additional cycles when accessing the ACIA */

	MidiControlRegister = IoMem[0xfffc04];

	LOG_TRACE(TRACE_MIDI, "MIDI: WriteControl($%x)\n", MidiControlRegister);

	/* Do we need to generate a transfer interrupt? */
	if ((MidiControlRegister & 0xA0) == 0xA0)
	{
		LOG_TRACE(TRACE_MIDI, "MIDI: WriteControl transfer interrupt!\n");

		/* Acknowledge in MFP circuit, pass bit,enable,pending */
		MFP_InputOnChannel ( MFP_INT_ACIA , 0 );

		MidiStatusRegister |= ACIA_SR_INTERRUPT_REQUEST;
	}
}


/**
 * Read MIDI data register ($FFFC06).
 */
void Midi_Data_ReadByte(void)
{
	LOG_TRACE(TRACE_MIDI, "MIDI: ReadData -> $%x\n", nRxDataByte);

	ACIA_AddWaitCycles ();						/* Additional cycles when accessing the ACIA */

	MidiStatusRegister &= ~(ACIA_SR_INTERRUPT_REQUEST|ACIA_SR_RX_FULL);

	/* GPIP I4 - General Purpose Pin Keyboard/MIDI interrupt,
	 * becomes high(1) again after data has been read. */
	MFP_GPIP |= 0x10;

	IoMem[0xfffc06] = nRxDataByte;
}


/**
 * Write to MIDI data register ($FFFC06).
 */
void Midi_Data_WriteByte(void)
{
	Uint8 nTxDataByte;

	ACIA_AddWaitCycles ();						/* Additional cycles when accessing the ACIA */

	nTxDataByte = IoMem[0xfffc06];

	LOG_TRACE(TRACE_MIDI, "MIDI: WriteData($%x)\n", nTxDataByte);

	MidiStatusRegister &= ~ACIA_SR_INTERRUPT_REQUEST;

	if (!MidiRetroInterface)
		return;

	if (MidiRetroInterface->output_enabled())
	{
		Uint64 deltaTime;
		bool ret;

		if (MidiWriteClockCounter == 0)
			MidiWriteClockCounter = CyclesGlobalClockCounter;

		deltaTime = (Uint64)((double)(CyclesGlobalClockCounter - MidiWriteClockCounter) /
                      ((double)MachineClocks.CPU_Freq / 1000000.0) + 0.5);
		if (deltaTime > 0xFFFFFFFF)
			deltaTime = 0;

		ret = MidiRetroInterface->write(nTxDataByte, (uint32_t)deltaTime);
		if (!ret)
			LOG_TRACE(TRACE_MIDI, "MIDI: write error (doesn't stop MIDI)\n");

		MidiWriteClockCounter = CyclesGlobalClockCounter;
	}

	MidiStatusRegister &= ~ACIA_SR_TX_EMPTY;
}


/**
 * Read and write MIDI interface data regularly
 */
void Midi_InterruptHandler_Update(void)
{
	Uint8 nInChar;

	/* Remove this interrupt from list and re-order */
	CycInt_AcknowledgeInterrupt();

	/* Flush outgoing data */
	if (!(MidiStatusRegister & ACIA_SR_TX_EMPTY))
	{
		/* Do we need to generate a transfer interrupt? */
		if ((MidiControlRegister & 0xA0) == 0xA0)
		{
			LOG_TRACE(TRACE_MIDI, "MIDI: WriteData transfer interrupt!\n");
			/* Acknowledge in MFP circuit, pass bit,enable,pending */
			MFP_InputOnChannel ( MFP_INT_ACIA , 0 );
			MidiStatusRegister |= ACIA_SR_INTERRUPT_REQUEST;
		}

		// if (pMidiFhOut)
		//	fflush(pMidiFhOut);

		MidiStatusRegister |= ACIA_SR_TX_EMPTY;
	}

	/* Read the bytes in, if we have any */
	if (MidiRetroInterface && MidiRetroInterface->input_enabled())
	{
		bool ret;

		ret = MidiRetroInterface->read(&nInChar);
		if (ret)
		{
			LOG_TRACE(TRACE_MIDI, "MIDI: Read character -> $%x\n", nInChar);
			/* Copy into our internal queue */
			nRxDataByte = nInChar;
			/* Do we need to generate a receive interrupt? */
			if ((MidiControlRegister & 0x80) == 0x80)
			{
				LOG_TRACE(TRACE_MIDI, "MIDI: WriteData receive interrupt!\n");
				/* Acknowledge in MFP circuit */
				MFP_InputOnChannel ( MFP_INT_ACIA , 0 );
				MidiStatusRegister |= ACIA_SR_INTERRUPT_REQUEST;
			}
			MidiStatusRegister |= ACIA_SR_RX_FULL;
			/* GPIP I4 - General Purpose Pin Keyboard/MIDI interrupt:
			 * It will remain low(0) until data is read from $fffc06. */
			MFP_GPIP &= ~0x10;
		}
		else
			LOG_TRACE(TRACE_MIDI, "MIDI: read error (doesn't stop MIDI)\n");
	}

	CycInt_AddRelativeInterrupt(2050, INT_CPU_CYCLE, INTERRUPT_MIDI);
}

void Midi_SetRetroInterface(struct retro_midi_interface *interface)
{
	MidiRetroInterface = interface;
}
