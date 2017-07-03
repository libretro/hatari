#include "main.h"
#include "sysdeps.h"
#include "hatari-glue.h"
#include "maccess.h"
#ifdef __LIBRETRO__ 	/* RETRO HACK */
#include "emumemory.h"
#else
#include "memory.h"
#endif /* RETRO HACK */
#include "custom.h"
#include "newcpu.h"
#include "cpu_prefetch.h"
#include "cputbl.h"
#define CPUFUNC(x) x##_ff
#define SET_CFLG_ALWAYS(x) SET_CFLG(x)
#define SET_NFLG_ALWAYS(x) SET_NFLG(x)
#ifdef NOFLAGS
#include "noflags.h"
#endif

#if !defined(PART_1) && !defined(PART_2) && !defined(PART_3) && !defined(PART_4) && !defined(PART_5) && !defined(PART_6) && !defined(PART_7) && !defined(PART_8)
#define PART_1 1
#define PART_2 1
#define PART_3 1
#define PART_4 1
#define PART_5 1
#define PART_6 1
#define PART_7 1
#define PART_8 1
#endif

#ifdef PART_1
/* OR.B #<data>.B,Dn */
void REGPARAM2 CPUFUNC(op_0000_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 1;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}	m68k_incpci (4);
return;
}

/* OR.B #<data>.B,(An) */
void REGPARAM2 CPUFUNC(op_0010_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 1;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = x_get_byte (dsta);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}	m68k_incpci (4);
return;
}

/* OR.B #<data>.B,(An)+ */
void REGPARAM2 CPUFUNC(op_0018_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 1;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}	m68k_incpci (4);
return;
}

/* OR.B #<data>.B,-(An) */
void REGPARAM2 CPUFUNC(op_0020_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 1;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}	m68k_incpci (4);
return;
}

/* OR.B #<data>.B,(d16,An) */
void REGPARAM2 CPUFUNC(op_0028_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 1;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s8 dst = x_get_byte (dsta);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}	m68k_incpci (6);
return;
}

/* OR.B #<data>.B,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_0030_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 1;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	m68k_incpci (4);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s8 dst = x_get_byte (dsta);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}}return;
}

/* OR.B #<data>.B,(xxx).W */
void REGPARAM2 CPUFUNC(op_0038_24)(uae_u32 opcode)
{
	OpcodeFamily = 1;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s8 dst = x_get_byte (dsta);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}	m68k_incpci (6);
return;
}

/* OR.B #<data>.B,(xxx).L */
void REGPARAM2 CPUFUNC(op_0039_24)(uae_u32 opcode)
{
	OpcodeFamily = 1;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (4);
{	uae_s8 dst = x_get_byte (dsta);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}	m68k_incpci (8);
return;
}

/* ORSR.B #<data>.W */
void REGPARAM2 CPUFUNC(op_003c_24)(uae_u32 opcode)
{
	OpcodeFamily = 4;
{	MakeSR ();
{	uae_s16 src = get_iword_cache_040 (2);
	src &= 0xFF;
	regs.sr |= src;
	MakeFromSR();
}}	m68k_incpci (4);
return;
}

/* OR.W #<data>.W,Dn */
void REGPARAM2 CPUFUNC(op_0040_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 1;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}	m68k_incpci (4);
return;
}

/* OR.W #<data>.W,(An) */
void REGPARAM2 CPUFUNC(op_0050_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 1;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s16 dst = x_get_word (dsta);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}	m68k_incpci (4);
return;
}

/* OR.W #<data>.W,(An)+ */
void REGPARAM2 CPUFUNC(op_0058_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 1;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s16 dst = x_get_word (dsta);
	m68k_areg (regs, dstreg) += 2;
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}	m68k_incpci (4);
return;
}

/* OR.W #<data>.W,-(An) */
void REGPARAM2 CPUFUNC(op_0060_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 1;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
{	uae_s16 dst = x_get_word (dsta);
	m68k_areg (regs, dstreg) = dsta;
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}	m68k_incpci (4);
return;
}

/* OR.W #<data>.W,(d16,An) */
void REGPARAM2 CPUFUNC(op_0068_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 1;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s16 dst = x_get_word (dsta);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}	m68k_incpci (6);
return;
}

/* OR.W #<data>.W,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_0070_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 1;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	m68k_incpci (4);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s16 dst = x_get_word (dsta);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}}return;
}

/* OR.W #<data>.W,(xxx).W */
void REGPARAM2 CPUFUNC(op_0078_24)(uae_u32 opcode)
{
	OpcodeFamily = 1;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s16 dst = x_get_word (dsta);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}	m68k_incpci (6);
return;
}

/* OR.W #<data>.W,(xxx).L */
void REGPARAM2 CPUFUNC(op_0079_24)(uae_u32 opcode)
{
	OpcodeFamily = 1;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (4);
{	uae_s16 dst = x_get_word (dsta);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}	m68k_incpci (8);
return;
}

/* ORSR.W #<data>.W */
void REGPARAM2 CPUFUNC(op_007c_24)(uae_u32 opcode)
{
	OpcodeFamily = 4;
{if (!regs.s) { Exception (8); goto l_240018; }
{	MakeSR ();
{	uae_s16 src = get_iword_cache_040 (2);
	regs.sr |= src;
	MakeFromSR();
}}}	m68k_incpci (4);
l_240018: ;
return;
}

/* OR.L #<data>.L,Dn */
void REGPARAM2 CPUFUNC(op_0080_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 1;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	m68k_dreg (regs, dstreg) = (src);
}}}	m68k_incpci (6);
return;
}

/* OR.L #<data>.L,(An) */
void REGPARAM2 CPUFUNC(op_0090_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 1;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s32 dst = x_get_long (dsta);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}	m68k_incpci (6);
return;
}

/* OR.L #<data>.L,(An)+ */
void REGPARAM2 CPUFUNC(op_0098_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 1;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s32 dst = x_get_long (dsta);
	m68k_areg (regs, dstreg) += 4;
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}	m68k_incpci (6);
return;
}

/* OR.L #<data>.L,-(An) */
void REGPARAM2 CPUFUNC(op_00a0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 1;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
{	uae_s32 dst = x_get_long (dsta);
	m68k_areg (regs, dstreg) = dsta;
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}	m68k_incpci (6);
return;
}

/* OR.L #<data>.L,(d16,An) */
void REGPARAM2 CPUFUNC(op_00a8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 1;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (6);
{	uae_s32 dst = x_get_long (dsta);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}	m68k_incpci (8);
return;
}

/* OR.L #<data>.L,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_00b0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 1;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	m68k_incpci (6);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s32 dst = x_get_long (dsta);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}}return;
}

/* OR.L #<data>.L,(xxx).W */
void REGPARAM2 CPUFUNC(op_00b8_24)(uae_u32 opcode)
{
	OpcodeFamily = 1;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (6);
{	uae_s32 dst = x_get_long (dsta);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}	m68k_incpci (8);
return;
}

/* OR.L #<data>.L,(xxx).L */
void REGPARAM2 CPUFUNC(op_00b9_24)(uae_u32 opcode)
{
	OpcodeFamily = 1;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (6);
{	uae_s32 dst = x_get_long (dsta);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}	m68k_incpci (10);
return;
}

/* CHK2.B #<data>.W,(An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_00d0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 81;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	{uae_s32 upper,lower,reg = regs.regs[(extra >> 12) & 15];
	lower = (uae_s32)(uae_s8)x_get_byte (dsta); upper = (uae_s32)(uae_s8)x_get_byte (dsta + 1);
	if ((extra & 0x8000) == 0) reg = (uae_s32)(uae_s8)reg;
	SET_ZFLG (upper == reg || lower == reg);
	SET_CFLG_ALWAYS (lower <= upper ? reg < lower || reg > upper : reg > upper || reg < lower);
	if ((extra & 0x800) && GET_CFLG ()) { Exception (6); goto l_240027; }
}
}}}	m68k_incpci (4);
l_240027: ;
return;
}

#endif
/* CHK2.B #<data>.W,(d16,An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_00e8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 81;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
	{uae_s32 upper,lower,reg = regs.regs[(extra >> 12) & 15];
	lower = (uae_s32)(uae_s8)x_get_byte (dsta); upper = (uae_s32)(uae_s8)x_get_byte (dsta + 1);
	if ((extra & 0x8000) == 0) reg = (uae_s32)(uae_s8)reg;
	SET_ZFLG (upper == reg || lower == reg);
	SET_CFLG_ALWAYS (lower <= upper ? reg < lower || reg > upper : reg > upper || reg < lower);
	if ((extra & 0x800) && GET_CFLG ()) { Exception (6); goto l_240028; }
}
}}}	m68k_incpci (6);
l_240028: ;
return;
}

#endif
/* CHK2.B #<data>.W,(d8,An,Xn) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_00f0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 81;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	m68k_incpci (4);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
	{uae_s32 upper,lower,reg = regs.regs[(extra >> 12) & 15];
	lower = (uae_s32)(uae_s8)x_get_byte (dsta); upper = (uae_s32)(uae_s8)x_get_byte (dsta + 1);
	if ((extra & 0x8000) == 0) reg = (uae_s32)(uae_s8)reg;
	SET_ZFLG (upper == reg || lower == reg);
	SET_CFLG_ALWAYS (lower <= upper ? reg < lower || reg > upper : reg > upper || reg < lower);
	if ((extra & 0x800) && GET_CFLG ()) { Exception (6); goto l_240029; }
}
}}}}l_240029: ;
return;
}

#endif
/* CHK2.B #<data>.W,(xxx).W */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_00f8_24)(uae_u32 opcode)
{
	OpcodeFamily = 81;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (4);
	{uae_s32 upper,lower,reg = regs.regs[(extra >> 12) & 15];
	lower = (uae_s32)(uae_s8)x_get_byte (dsta); upper = (uae_s32)(uae_s8)x_get_byte (dsta + 1);
	if ((extra & 0x8000) == 0) reg = (uae_s32)(uae_s8)reg;
	SET_ZFLG (upper == reg || lower == reg);
	SET_CFLG_ALWAYS (lower <= upper ? reg < lower || reg > upper : reg > upper || reg < lower);
	if ((extra & 0x800) && GET_CFLG ()) { Exception (6); goto l_240030; }
}
}}}	m68k_incpci (6);
l_240030: ;
return;
}

#endif
/* CHK2.B #<data>.W,(xxx).L */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_00f9_24)(uae_u32 opcode)
{
	OpcodeFamily = 81;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (4);
	{uae_s32 upper,lower,reg = regs.regs[(extra >> 12) & 15];
	lower = (uae_s32)(uae_s8)x_get_byte (dsta); upper = (uae_s32)(uae_s8)x_get_byte (dsta + 1);
	if ((extra & 0x8000) == 0) reg = (uae_s32)(uae_s8)reg;
	SET_ZFLG (upper == reg || lower == reg);
	SET_CFLG_ALWAYS (lower <= upper ? reg < lower || reg > upper : reg > upper || reg < lower);
	if ((extra & 0x800) && GET_CFLG ()) { Exception (6); goto l_240031; }
}
}}}	m68k_incpci (8);
l_240031: ;
return;
}

#endif
/* CHK2.B #<data>.W,(d16,PC) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_00fa_24)(uae_u32 opcode)
{
	uae_u32 dstreg = 2;
	OpcodeFamily = 81;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_getpci () + 4;
	dsta += (uae_s32)(uae_s16)get_iword_cache_040 (4);
	{uae_s32 upper,lower,reg = regs.regs[(extra >> 12) & 15];
	lower = (uae_s32)(uae_s8)x_get_byte (dsta); upper = (uae_s32)(uae_s8)x_get_byte (dsta + 1);
	if ((extra & 0x8000) == 0) reg = (uae_s32)(uae_s8)reg;
	SET_ZFLG (upper == reg || lower == reg);
	SET_CFLG_ALWAYS (lower <= upper ? reg < lower || reg > upper : reg > upper || reg < lower);
	if ((extra & 0x800) && GET_CFLG ()) { Exception (6); goto l_240032; }
}
}}}	m68k_incpci (6);
l_240032: ;
return;
}

#endif
/* CHK2.B #<data>.W,(d8,PC,Xn) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_00fb_24)(uae_u32 opcode)
{
	uae_u32 dstreg = 3;
	OpcodeFamily = 81;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr tmppc;
	uaecptr dsta;
	m68k_incpci (4);
{	tmppc = m68k_getpci ();
	dsta = x_get_disp_ea_040 (tmppc, 0);
	{uae_s32 upper,lower,reg = regs.regs[(extra >> 12) & 15];
	lower = (uae_s32)(uae_s8)x_get_byte (dsta); upper = (uae_s32)(uae_s8)x_get_byte (dsta + 1);
	if ((extra & 0x8000) == 0) reg = (uae_s32)(uae_s8)reg;
	SET_ZFLG (upper == reg || lower == reg);
	SET_CFLG_ALWAYS (lower <= upper ? reg < lower || reg > upper : reg > upper || reg < lower);
	if ((extra & 0x800) && GET_CFLG ()) { Exception (6); goto l_240033; }
}
}}}}l_240033: ;
return;
}

#endif
/* BTST.L Dn,Dn */
void REGPARAM2 CPUFUNC(op_0100_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 21;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src &= 31;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
}}}	m68k_incpci (2);
return;
}

/* MVPMR.W (d16,An),Dn */
void REGPARAM2 CPUFUNC(op_0108_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 29;
{	uaecptr memp = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_u16 val = ((x_get_byte (memp) & 0xff) << 8) + (x_get_byte (memp + 2) & 0xff);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}}	m68k_incpci (4);
return;
}

/* BTST.B Dn,(An) */
void REGPARAM2 CPUFUNC(op_0110_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 21;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = x_get_byte (dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
}}}}	m68k_incpci (2);
return;
}

/* BTST.B Dn,(An)+ */
void REGPARAM2 CPUFUNC(op_0118_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 21;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
}}}}	m68k_incpci (2);
return;
}

/* BTST.B Dn,-(An) */
void REGPARAM2 CPUFUNC(op_0120_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 21;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
}}}}	m68k_incpci (2);
return;
}

/* BTST.B Dn,(d16,An) */
void REGPARAM2 CPUFUNC(op_0128_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 21;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 dst = x_get_byte (dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
}}}}	m68k_incpci (4);
return;
}

/* BTST.B Dn,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_0130_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 21;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	m68k_incpci (2);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s8 dst = x_get_byte (dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
}}}}}return;
}

/* BTST.B Dn,(xxx).W */
void REGPARAM2 CPUFUNC(op_0138_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	OpcodeFamily = 21;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 dst = x_get_byte (dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
}}}}	m68k_incpci (4);
return;
}

/* BTST.B Dn,(xxx).L */
void REGPARAM2 CPUFUNC(op_0139_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	OpcodeFamily = 21;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (2);
{	uae_s8 dst = x_get_byte (dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
}}}}	m68k_incpci (6);
return;
}

/* BTST.B Dn,(d16,PC) */
void REGPARAM2 CPUFUNC(op_013a_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = 2;
	OpcodeFamily = 21;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_getpci () + 2;
	dsta += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 dst = x_get_byte (dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
}}}}	m68k_incpci (4);
return;
}

/* BTST.B Dn,(d8,PC,Xn) */
void REGPARAM2 CPUFUNC(op_013b_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = 3;
	OpcodeFamily = 21;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr tmppc;
	uaecptr dsta;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	dsta = x_get_disp_ea_040 (tmppc, 0);
{	uae_s8 dst = x_get_byte (dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
}}}}}return;
}

/* BTST.B Dn,#<data>.B */
void REGPARAM2 CPUFUNC(op_013c_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	OpcodeFamily = 21;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uae_s8 dst = (uae_u8)get_iword_cache_040 (2);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
}}}	m68k_incpci (4);
return;
}

/* BCHG.L Dn,Dn */
void REGPARAM2 CPUFUNC(op_0140_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 22;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src &= 31;
	dst ^= (1 << src);
	SET_ZFLG (((uae_u32)dst & (1 << src)) >> src);
	m68k_dreg (regs, dstreg) = (dst);
}}}	m68k_incpci (2);
return;
}

/* MVPMR.L (d16,An),Dn */
void REGPARAM2 CPUFUNC(op_0148_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 29;
{	uaecptr memp = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_u32 val = ((x_get_byte (memp) & 0xff) << 24) + ((x_get_byte (memp + 2) & 0xff) << 16)
              + ((x_get_byte (memp + 4) & 0xff) << 8) + (x_get_byte (memp + 6) & 0xff);
	m68k_dreg (regs, dstreg) = (val);
}}	m68k_incpci (4);
return;
}

/* BCHG.B Dn,(An) */
void REGPARAM2 CPUFUNC(op_0150_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 22;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = x_get_byte (dsta);
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (((uae_u32)dst & (1 << src)) >> src);
	x_put_byte (dsta, dst);
}}}}	m68k_incpci (2);
return;
}

/* BCHG.B Dn,(An)+ */
void REGPARAM2 CPUFUNC(op_0158_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 22;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (((uae_u32)dst & (1 << src)) >> src);
	x_put_byte (dsta, dst);
}}}}	m68k_incpci (2);
return;
}

/* BCHG.B Dn,-(An) */
void REGPARAM2 CPUFUNC(op_0160_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 22;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (((uae_u32)dst & (1 << src)) >> src);
	x_put_byte (dsta, dst);
}}}}	m68k_incpci (2);
return;
}

/* BCHG.B Dn,(d16,An) */
void REGPARAM2 CPUFUNC(op_0168_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 22;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 dst = x_get_byte (dsta);
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (((uae_u32)dst & (1 << src)) >> src);
	x_put_byte (dsta, dst);
}}}}	m68k_incpci (4);
return;
}

/* BCHG.B Dn,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_0170_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 22;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	m68k_incpci (2);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s8 dst = x_get_byte (dsta);
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (((uae_u32)dst & (1 << src)) >> src);
	x_put_byte (dsta, dst);
}}}}}return;
}

/* BCHG.B Dn,(xxx).W */
void REGPARAM2 CPUFUNC(op_0178_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	OpcodeFamily = 22;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 dst = x_get_byte (dsta);
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (((uae_u32)dst & (1 << src)) >> src);
	x_put_byte (dsta, dst);
}}}}	m68k_incpci (4);
return;
}

/* BCHG.B Dn,(xxx).L */
void REGPARAM2 CPUFUNC(op_0179_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	OpcodeFamily = 22;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (2);
{	uae_s8 dst = x_get_byte (dsta);
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (((uae_u32)dst & (1 << src)) >> src);
	x_put_byte (dsta, dst);
}}}}	m68k_incpci (6);
return;
}

/* BCLR.L Dn,Dn */
void REGPARAM2 CPUFUNC(op_0180_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 23;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src &= 31;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	m68k_dreg (regs, dstreg) = (dst);
}}}	m68k_incpci (2);
return;
}

/* MVPRM.W Dn,(d16,An) */
void REGPARAM2 CPUFUNC(op_0188_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 28;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
	uaecptr memp = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
	x_put_byte (memp, src >> 8);
	x_put_byte (memp + 2, src);
}}	m68k_incpci (4);
return;
}

/* BCLR.B Dn,(An) */
void REGPARAM2 CPUFUNC(op_0190_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 23;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = x_get_byte (dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	x_put_byte (dsta, dst);
}}}}	m68k_incpci (2);
return;
}

/* BCLR.B Dn,(An)+ */
void REGPARAM2 CPUFUNC(op_0198_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 23;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	x_put_byte (dsta, dst);
}}}}	m68k_incpci (2);
return;
}

/* BCLR.B Dn,-(An) */
void REGPARAM2 CPUFUNC(op_01a0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 23;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	x_put_byte (dsta, dst);
}}}}	m68k_incpci (2);
return;
}

/* BCLR.B Dn,(d16,An) */
void REGPARAM2 CPUFUNC(op_01a8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 23;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 dst = x_get_byte (dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	x_put_byte (dsta, dst);
}}}}	m68k_incpci (4);
return;
}

/* BCLR.B Dn,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_01b0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 23;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	m68k_incpci (2);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s8 dst = x_get_byte (dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	x_put_byte (dsta, dst);
}}}}}return;
}

/* BCLR.B Dn,(xxx).W */
void REGPARAM2 CPUFUNC(op_01b8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	OpcodeFamily = 23;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 dst = x_get_byte (dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	x_put_byte (dsta, dst);
}}}}	m68k_incpci (4);
return;
}

/* BCLR.B Dn,(xxx).L */
void REGPARAM2 CPUFUNC(op_01b9_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	OpcodeFamily = 23;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (2);
{	uae_s8 dst = x_get_byte (dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	x_put_byte (dsta, dst);
}}}}	m68k_incpci (6);
return;
}

/* BSET.L Dn,Dn */
void REGPARAM2 CPUFUNC(op_01c0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 24;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src &= 31;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	m68k_dreg (regs, dstreg) = (dst);
}}}	m68k_incpci (2);
return;
}

/* MVPRM.L Dn,(d16,An) */
void REGPARAM2 CPUFUNC(op_01c8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 28;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
	uaecptr memp = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
	x_put_byte (memp, src >> 24);
	x_put_byte (memp + 2, src >> 16);
	x_put_byte (memp + 4, src >> 8);
	x_put_byte (memp + 6, src);
}}	m68k_incpci (4);
return;
}

/* BSET.B Dn,(An) */
void REGPARAM2 CPUFUNC(op_01d0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 24;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = x_get_byte (dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	x_put_byte (dsta, dst);
}}}}	m68k_incpci (2);
return;
}

/* BSET.B Dn,(An)+ */
void REGPARAM2 CPUFUNC(op_01d8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 24;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	x_put_byte (dsta, dst);
}}}}	m68k_incpci (2);
return;
}

/* BSET.B Dn,-(An) */
void REGPARAM2 CPUFUNC(op_01e0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 24;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	x_put_byte (dsta, dst);
}}}}	m68k_incpci (2);
return;
}

/* BSET.B Dn,(d16,An) */
void REGPARAM2 CPUFUNC(op_01e8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 24;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 dst = x_get_byte (dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	x_put_byte (dsta, dst);
}}}}	m68k_incpci (4);
return;
}

/* BSET.B Dn,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_01f0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 24;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	m68k_incpci (2);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s8 dst = x_get_byte (dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	x_put_byte (dsta, dst);
}}}}}return;
}

/* BSET.B Dn,(xxx).W */
void REGPARAM2 CPUFUNC(op_01f8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	OpcodeFamily = 24;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 dst = x_get_byte (dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	x_put_byte (dsta, dst);
}}}}	m68k_incpci (4);
return;
}

/* BSET.B Dn,(xxx).L */
void REGPARAM2 CPUFUNC(op_01f9_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	OpcodeFamily = 24;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (2);
{	uae_s8 dst = x_get_byte (dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	x_put_byte (dsta, dst);
}}}}	m68k_incpci (6);
return;
}

/* AND.B #<data>.B,Dn */
void REGPARAM2 CPUFUNC(op_0200_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 2;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}	m68k_incpci (4);
return;
}

/* AND.B #<data>.B,(An) */
void REGPARAM2 CPUFUNC(op_0210_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 2;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = x_get_byte (dsta);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}	m68k_incpci (4);
return;
}

/* AND.B #<data>.B,(An)+ */
void REGPARAM2 CPUFUNC(op_0218_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 2;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}	m68k_incpci (4);
return;
}

/* AND.B #<data>.B,-(An) */
void REGPARAM2 CPUFUNC(op_0220_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 2;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}	m68k_incpci (4);
return;
}

/* AND.B #<data>.B,(d16,An) */
void REGPARAM2 CPUFUNC(op_0228_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 2;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s8 dst = x_get_byte (dsta);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}	m68k_incpci (6);
return;
}

/* AND.B #<data>.B,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_0230_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 2;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	m68k_incpci (4);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s8 dst = x_get_byte (dsta);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}}return;
}

/* AND.B #<data>.B,(xxx).W */
void REGPARAM2 CPUFUNC(op_0238_24)(uae_u32 opcode)
{
	OpcodeFamily = 2;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s8 dst = x_get_byte (dsta);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}	m68k_incpci (6);
return;
}

/* AND.B #<data>.B,(xxx).L */
void REGPARAM2 CPUFUNC(op_0239_24)(uae_u32 opcode)
{
	OpcodeFamily = 2;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (4);
{	uae_s8 dst = x_get_byte (dsta);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}	m68k_incpci (8);
return;
}

/* ANDSR.B #<data>.W */
void REGPARAM2 CPUFUNC(op_023c_24)(uae_u32 opcode)
{
	OpcodeFamily = 5;
{	MakeSR ();
{	uae_s16 src = get_iword_cache_040 (2);
	src |= 0xFF00;
	regs.sr &= src;
	MakeFromSR();
}}	m68k_incpci (4);
return;
}

/* AND.W #<data>.W,Dn */
void REGPARAM2 CPUFUNC(op_0240_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 2;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}	m68k_incpci (4);
return;
}

/* AND.W #<data>.W,(An) */
void REGPARAM2 CPUFUNC(op_0250_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 2;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s16 dst = x_get_word (dsta);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}	m68k_incpci (4);
return;
}

/* AND.W #<data>.W,(An)+ */
void REGPARAM2 CPUFUNC(op_0258_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 2;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s16 dst = x_get_word (dsta);
	m68k_areg (regs, dstreg) += 2;
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}	m68k_incpci (4);
return;
}

/* AND.W #<data>.W,-(An) */
void REGPARAM2 CPUFUNC(op_0260_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 2;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
{	uae_s16 dst = x_get_word (dsta);
	m68k_areg (regs, dstreg) = dsta;
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}	m68k_incpci (4);
return;
}

/* AND.W #<data>.W,(d16,An) */
void REGPARAM2 CPUFUNC(op_0268_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 2;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s16 dst = x_get_word (dsta);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}	m68k_incpci (6);
return;
}

/* AND.W #<data>.W,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_0270_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 2;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	m68k_incpci (4);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s16 dst = x_get_word (dsta);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}}return;
}

/* AND.W #<data>.W,(xxx).W */
void REGPARAM2 CPUFUNC(op_0278_24)(uae_u32 opcode)
{
	OpcodeFamily = 2;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s16 dst = x_get_word (dsta);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}	m68k_incpci (6);
return;
}

/* AND.W #<data>.W,(xxx).L */
void REGPARAM2 CPUFUNC(op_0279_24)(uae_u32 opcode)
{
	OpcodeFamily = 2;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (4);
{	uae_s16 dst = x_get_word (dsta);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}	m68k_incpci (8);
return;
}

/* ANDSR.W #<data>.W */
void REGPARAM2 CPUFUNC(op_027c_24)(uae_u32 opcode)
{
	OpcodeFamily = 5;
{if (!regs.s) { Exception (8); goto l_240090; }
{	MakeSR ();
{	uae_s16 src = get_iword_cache_040 (2);
	regs.sr &= src;
	MakeFromSR();
}}}	m68k_incpci (4);
l_240090: ;
return;
}

/* AND.L #<data>.L,Dn */
void REGPARAM2 CPUFUNC(op_0280_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 2;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	m68k_dreg (regs, dstreg) = (src);
}}}	m68k_incpci (6);
return;
}

/* AND.L #<data>.L,(An) */
void REGPARAM2 CPUFUNC(op_0290_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 2;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s32 dst = x_get_long (dsta);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}	m68k_incpci (6);
return;
}

/* AND.L #<data>.L,(An)+ */
void REGPARAM2 CPUFUNC(op_0298_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 2;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s32 dst = x_get_long (dsta);
	m68k_areg (regs, dstreg) += 4;
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}	m68k_incpci (6);
return;
}

/* AND.L #<data>.L,-(An) */
void REGPARAM2 CPUFUNC(op_02a0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 2;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
{	uae_s32 dst = x_get_long (dsta);
	m68k_areg (regs, dstreg) = dsta;
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}	m68k_incpci (6);
return;
}

/* AND.L #<data>.L,(d16,An) */
void REGPARAM2 CPUFUNC(op_02a8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 2;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (6);
{	uae_s32 dst = x_get_long (dsta);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}	m68k_incpci (8);
return;
}

/* AND.L #<data>.L,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_02b0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 2;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	m68k_incpci (6);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s32 dst = x_get_long (dsta);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}}return;
}

/* AND.L #<data>.L,(xxx).W */
void REGPARAM2 CPUFUNC(op_02b8_24)(uae_u32 opcode)
{
	OpcodeFamily = 2;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (6);
{	uae_s32 dst = x_get_long (dsta);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}	m68k_incpci (8);
return;
}

/* AND.L #<data>.L,(xxx).L */
void REGPARAM2 CPUFUNC(op_02b9_24)(uae_u32 opcode)
{
	OpcodeFamily = 2;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (6);
{	uae_s32 dst = x_get_long (dsta);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}	m68k_incpci (10);
return;
}

/* CHK2.W #<data>.W,(An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_02d0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 81;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	{uae_s32 upper,lower,reg = regs.regs[(extra >> 12) & 15];
	lower = (uae_s32)(uae_s16)x_get_word (dsta); upper = (uae_s32)(uae_s16)x_get_word (dsta + 2);
	if ((extra & 0x8000) == 0) reg = (uae_s32)(uae_s16)reg;
	SET_ZFLG (upper == reg || lower == reg);
	SET_CFLG_ALWAYS (lower <= upper ? reg < lower || reg > upper : reg > upper || reg < lower);
	if ((extra & 0x800) && GET_CFLG ()) { Exception (6); goto l_240099; }
}
}}}	m68k_incpci (4);
l_240099: ;
return;
}

#endif
/* CHK2.W #<data>.W,(d16,An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_02e8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 81;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
	{uae_s32 upper,lower,reg = regs.regs[(extra >> 12) & 15];
	lower = (uae_s32)(uae_s16)x_get_word (dsta); upper = (uae_s32)(uae_s16)x_get_word (dsta + 2);
	if ((extra & 0x8000) == 0) reg = (uae_s32)(uae_s16)reg;
	SET_ZFLG (upper == reg || lower == reg);
	SET_CFLG_ALWAYS (lower <= upper ? reg < lower || reg > upper : reg > upper || reg < lower);
	if ((extra & 0x800) && GET_CFLG ()) { Exception (6); goto l_240100; }
}
}}}	m68k_incpci (6);
l_240100: ;
return;
}

#endif
/* CHK2.W #<data>.W,(d8,An,Xn) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_02f0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 81;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	m68k_incpci (4);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
	{uae_s32 upper,lower,reg = regs.regs[(extra >> 12) & 15];
	lower = (uae_s32)(uae_s16)x_get_word (dsta); upper = (uae_s32)(uae_s16)x_get_word (dsta + 2);
	if ((extra & 0x8000) == 0) reg = (uae_s32)(uae_s16)reg;
	SET_ZFLG (upper == reg || lower == reg);
	SET_CFLG_ALWAYS (lower <= upper ? reg < lower || reg > upper : reg > upper || reg < lower);
	if ((extra & 0x800) && GET_CFLG ()) { Exception (6); goto l_240101; }
}
}}}}l_240101: ;
return;
}

#endif
/* CHK2.W #<data>.W,(xxx).W */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_02f8_24)(uae_u32 opcode)
{
	OpcodeFamily = 81;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (4);
	{uae_s32 upper,lower,reg = regs.regs[(extra >> 12) & 15];
	lower = (uae_s32)(uae_s16)x_get_word (dsta); upper = (uae_s32)(uae_s16)x_get_word (dsta + 2);
	if ((extra & 0x8000) == 0) reg = (uae_s32)(uae_s16)reg;
	SET_ZFLG (upper == reg || lower == reg);
	SET_CFLG_ALWAYS (lower <= upper ? reg < lower || reg > upper : reg > upper || reg < lower);
	if ((extra & 0x800) && GET_CFLG ()) { Exception (6); goto l_240102; }
}
}}}	m68k_incpci (6);
l_240102: ;
return;
}

#endif
/* CHK2.W #<data>.W,(xxx).L */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_02f9_24)(uae_u32 opcode)
{
	OpcodeFamily = 81;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (4);
	{uae_s32 upper,lower,reg = regs.regs[(extra >> 12) & 15];
	lower = (uae_s32)(uae_s16)x_get_word (dsta); upper = (uae_s32)(uae_s16)x_get_word (dsta + 2);
	if ((extra & 0x8000) == 0) reg = (uae_s32)(uae_s16)reg;
	SET_ZFLG (upper == reg || lower == reg);
	SET_CFLG_ALWAYS (lower <= upper ? reg < lower || reg > upper : reg > upper || reg < lower);
	if ((extra & 0x800) && GET_CFLG ()) { Exception (6); goto l_240103; }
}
}}}	m68k_incpci (8);
l_240103: ;
return;
}

#endif
/* CHK2.W #<data>.W,(d16,PC) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_02fa_24)(uae_u32 opcode)
{
	uae_u32 dstreg = 2;
	OpcodeFamily = 81;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_getpci () + 4;
	dsta += (uae_s32)(uae_s16)get_iword_cache_040 (4);
	{uae_s32 upper,lower,reg = regs.regs[(extra >> 12) & 15];
	lower = (uae_s32)(uae_s16)x_get_word (dsta); upper = (uae_s32)(uae_s16)x_get_word (dsta + 2);
	if ((extra & 0x8000) == 0) reg = (uae_s32)(uae_s16)reg;
	SET_ZFLG (upper == reg || lower == reg);
	SET_CFLG_ALWAYS (lower <= upper ? reg < lower || reg > upper : reg > upper || reg < lower);
	if ((extra & 0x800) && GET_CFLG ()) { Exception (6); goto l_240104; }
}
}}}	m68k_incpci (6);
l_240104: ;
return;
}

#endif
/* CHK2.W #<data>.W,(d8,PC,Xn) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_02fb_24)(uae_u32 opcode)
{
	uae_u32 dstreg = 3;
	OpcodeFamily = 81;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr tmppc;
	uaecptr dsta;
	m68k_incpci (4);
{	tmppc = m68k_getpci ();
	dsta = x_get_disp_ea_040 (tmppc, 0);
	{uae_s32 upper,lower,reg = regs.regs[(extra >> 12) & 15];
	lower = (uae_s32)(uae_s16)x_get_word (dsta); upper = (uae_s32)(uae_s16)x_get_word (dsta + 2);
	if ((extra & 0x8000) == 0) reg = (uae_s32)(uae_s16)reg;
	SET_ZFLG (upper == reg || lower == reg);
	SET_CFLG_ALWAYS (lower <= upper ? reg < lower || reg > upper : reg > upper || reg < lower);
	if ((extra & 0x800) && GET_CFLG ()) { Exception (6); goto l_240105; }
}
}}}}l_240105: ;
return;
}

#endif
/* SUB.B #<data>.B,Dn */
void REGPARAM2 CPUFUNC(op_0400_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}}	m68k_incpci (4);
return;
}

/* SUB.B #<data>.B,(An) */
void REGPARAM2 CPUFUNC(op_0410_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = x_get_byte (dsta);
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (dsta, newv);
}}}}}}}	m68k_incpci (4);
return;
}

/* SUB.B #<data>.B,(An)+ */
void REGPARAM2 CPUFUNC(op_0418_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (dsta, newv);
}}}}}}}	m68k_incpci (4);
return;
}

/* SUB.B #<data>.B,-(An) */
void REGPARAM2 CPUFUNC(op_0420_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (dsta, newv);
}}}}}}}	m68k_incpci (4);
return;
}

/* SUB.B #<data>.B,(d16,An) */
void REGPARAM2 CPUFUNC(op_0428_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s8 dst = x_get_byte (dsta);
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (dsta, newv);
}}}}}}}	m68k_incpci (6);
return;
}

/* SUB.B #<data>.B,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_0430_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	m68k_incpci (4);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s8 dst = x_get_byte (dsta);
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (dsta, newv);
}}}}}}}}return;
}

/* SUB.B #<data>.B,(xxx).W */
void REGPARAM2 CPUFUNC(op_0438_24)(uae_u32 opcode)
{
	OpcodeFamily = 7;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s8 dst = x_get_byte (dsta);
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (dsta, newv);
}}}}}}}	m68k_incpci (6);
return;
}

/* SUB.B #<data>.B,(xxx).L */
void REGPARAM2 CPUFUNC(op_0439_24)(uae_u32 opcode)
{
	OpcodeFamily = 7;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (4);
{	uae_s8 dst = x_get_byte (dsta);
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (dsta, newv);
}}}}}}}	m68k_incpci (8);
return;
}

/* SUB.W #<data>.W,Dn */
void REGPARAM2 CPUFUNC(op_0440_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}}	m68k_incpci (4);
return;
}

/* SUB.W #<data>.W,(An) */
void REGPARAM2 CPUFUNC(op_0450_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s16 dst = x_get_word (dsta);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (dsta, newv);
}}}}}}}	m68k_incpci (4);
return;
}

/* SUB.W #<data>.W,(An)+ */
void REGPARAM2 CPUFUNC(op_0458_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s16 dst = x_get_word (dsta);
	m68k_areg (regs, dstreg) += 2;
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (dsta, newv);
}}}}}}}	m68k_incpci (4);
return;
}

/* SUB.W #<data>.W,-(An) */
void REGPARAM2 CPUFUNC(op_0460_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
{	uae_s16 dst = x_get_word (dsta);
	m68k_areg (regs, dstreg) = dsta;
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (dsta, newv);
}}}}}}}	m68k_incpci (4);
return;
}

/* SUB.W #<data>.W,(d16,An) */
void REGPARAM2 CPUFUNC(op_0468_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s16 dst = x_get_word (dsta);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (dsta, newv);
}}}}}}}	m68k_incpci (6);
return;
}

/* SUB.W #<data>.W,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_0470_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	m68k_incpci (4);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s16 dst = x_get_word (dsta);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (dsta, newv);
}}}}}}}}return;
}

/* SUB.W #<data>.W,(xxx).W */
void REGPARAM2 CPUFUNC(op_0478_24)(uae_u32 opcode)
{
	OpcodeFamily = 7;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s16 dst = x_get_word (dsta);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (dsta, newv);
}}}}}}}	m68k_incpci (6);
return;
}

/* SUB.W #<data>.W,(xxx).L */
void REGPARAM2 CPUFUNC(op_0479_24)(uae_u32 opcode)
{
	OpcodeFamily = 7;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (4);
{	uae_s16 dst = x_get_word (dsta);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (dsta, newv);
}}}}}}}	m68k_incpci (8);
return;
}

/* SUB.L #<data>.L,Dn */
void REGPARAM2 CPUFUNC(op_0480_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}	m68k_incpci (6);
return;
}

/* SUB.L #<data>.L,(An) */
void REGPARAM2 CPUFUNC(op_0490_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s32 dst = x_get_long (dsta);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (dsta, newv);
}}}}}}}	m68k_incpci (6);
return;
}

/* SUB.L #<data>.L,(An)+ */
void REGPARAM2 CPUFUNC(op_0498_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s32 dst = x_get_long (dsta);
	m68k_areg (regs, dstreg) += 4;
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (dsta, newv);
}}}}}}}	m68k_incpci (6);
return;
}

/* SUB.L #<data>.L,-(An) */
void REGPARAM2 CPUFUNC(op_04a0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
{	uae_s32 dst = x_get_long (dsta);
	m68k_areg (regs, dstreg) = dsta;
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (dsta, newv);
}}}}}}}	m68k_incpci (6);
return;
}

/* SUB.L #<data>.L,(d16,An) */
void REGPARAM2 CPUFUNC(op_04a8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (6);
{	uae_s32 dst = x_get_long (dsta);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (dsta, newv);
}}}}}}}	m68k_incpci (8);
return;
}

/* SUB.L #<data>.L,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_04b0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	m68k_incpci (6);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s32 dst = x_get_long (dsta);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (dsta, newv);
}}}}}}}}return;
}

/* SUB.L #<data>.L,(xxx).W */
void REGPARAM2 CPUFUNC(op_04b8_24)(uae_u32 opcode)
{
	OpcodeFamily = 7;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (6);
{	uae_s32 dst = x_get_long (dsta);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (dsta, newv);
}}}}}}}	m68k_incpci (8);
return;
}

/* SUB.L #<data>.L,(xxx).L */
void REGPARAM2 CPUFUNC(op_04b9_24)(uae_u32 opcode)
{
	OpcodeFamily = 7;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (6);
{	uae_s32 dst = x_get_long (dsta);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (dsta, newv);
}}}}}}}	m68k_incpci (10);
return;
}

/* CHK2.L #<data>.W,(An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_04d0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 81;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	{uae_s32 upper,lower,reg = regs.regs[(extra >> 12) & 15];
	lower = x_get_long (dsta); upper = x_get_long (dsta + 4);
	SET_ZFLG (upper == reg || lower == reg);
	SET_CFLG_ALWAYS (lower <= upper ? reg < lower || reg > upper : reg > upper || reg < lower);
	if ((extra & 0x800) && GET_CFLG ()) { Exception (6); goto l_240130; }
}
}}}	m68k_incpci (4);
l_240130: ;
return;
}

#endif
/* CHK2.L #<data>.W,(d16,An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_04e8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 81;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
	{uae_s32 upper,lower,reg = regs.regs[(extra >> 12) & 15];
	lower = x_get_long (dsta); upper = x_get_long (dsta + 4);
	SET_ZFLG (upper == reg || lower == reg);
	SET_CFLG_ALWAYS (lower <= upper ? reg < lower || reg > upper : reg > upper || reg < lower);
	if ((extra & 0x800) && GET_CFLG ()) { Exception (6); goto l_240131; }
}
}}}	m68k_incpci (6);
l_240131: ;
return;
}

#endif
/* CHK2.L #<data>.W,(d8,An,Xn) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_04f0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 81;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	m68k_incpci (4);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
	{uae_s32 upper,lower,reg = regs.regs[(extra >> 12) & 15];
	lower = x_get_long (dsta); upper = x_get_long (dsta + 4);
	SET_ZFLG (upper == reg || lower == reg);
	SET_CFLG_ALWAYS (lower <= upper ? reg < lower || reg > upper : reg > upper || reg < lower);
	if ((extra & 0x800) && GET_CFLG ()) { Exception (6); goto l_240132; }
}
}}}}l_240132: ;
return;
}

#endif
/* CHK2.L #<data>.W,(xxx).W */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_04f8_24)(uae_u32 opcode)
{
	OpcodeFamily = 81;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (4);
	{uae_s32 upper,lower,reg = regs.regs[(extra >> 12) & 15];
	lower = x_get_long (dsta); upper = x_get_long (dsta + 4);
	SET_ZFLG (upper == reg || lower == reg);
	SET_CFLG_ALWAYS (lower <= upper ? reg < lower || reg > upper : reg > upper || reg < lower);
	if ((extra & 0x800) && GET_CFLG ()) { Exception (6); goto l_240133; }
}
}}}	m68k_incpci (6);
l_240133: ;
return;
}

#endif
/* CHK2.L #<data>.W,(xxx).L */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_04f9_24)(uae_u32 opcode)
{
	OpcodeFamily = 81;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (4);
	{uae_s32 upper,lower,reg = regs.regs[(extra >> 12) & 15];
	lower = x_get_long (dsta); upper = x_get_long (dsta + 4);
	SET_ZFLG (upper == reg || lower == reg);
	SET_CFLG_ALWAYS (lower <= upper ? reg < lower || reg > upper : reg > upper || reg < lower);
	if ((extra & 0x800) && GET_CFLG ()) { Exception (6); goto l_240134; }
}
}}}	m68k_incpci (8);
l_240134: ;
return;
}

#endif
/* CHK2.L #<data>.W,(d16,PC) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_04fa_24)(uae_u32 opcode)
{
	uae_u32 dstreg = 2;
	OpcodeFamily = 81;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_getpci () + 4;
	dsta += (uae_s32)(uae_s16)get_iword_cache_040 (4);
	{uae_s32 upper,lower,reg = regs.regs[(extra >> 12) & 15];
	lower = x_get_long (dsta); upper = x_get_long (dsta + 4);
	SET_ZFLG (upper == reg || lower == reg);
	SET_CFLG_ALWAYS (lower <= upper ? reg < lower || reg > upper : reg > upper || reg < lower);
	if ((extra & 0x800) && GET_CFLG ()) { Exception (6); goto l_240135; }
}
}}}	m68k_incpci (6);
l_240135: ;
return;
}

#endif
/* CHK2.L #<data>.W,(d8,PC,Xn) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_04fb_24)(uae_u32 opcode)
{
	uae_u32 dstreg = 3;
	OpcodeFamily = 81;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr tmppc;
	uaecptr dsta;
	m68k_incpci (4);
{	tmppc = m68k_getpci ();
	dsta = x_get_disp_ea_040 (tmppc, 0);
	{uae_s32 upper,lower,reg = regs.regs[(extra >> 12) & 15];
	lower = x_get_long (dsta); upper = x_get_long (dsta + 4);
	SET_ZFLG (upper == reg || lower == reg);
	SET_CFLG_ALWAYS (lower <= upper ? reg < lower || reg > upper : reg > upper || reg < lower);
	if ((extra & 0x800) && GET_CFLG ()) { Exception (6); goto l_240136; }
}
}}}}l_240136: ;
return;
}

#endif
/* ADD.B #<data>.B,Dn */
void REGPARAM2 CPUFUNC(op_0600_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u8)(dst)) + ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u8)(~dst)) < ((uae_u8)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}}	m68k_incpci (4);
return;
}

/* ADD.B #<data>.B,(An) */
void REGPARAM2 CPUFUNC(op_0610_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = x_get_byte (dsta);
{{uae_u32 newv = ((uae_u8)(dst)) + ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u8)(~dst)) < ((uae_u8)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (dsta, newv);
}}}}}}}	m68k_incpci (4);
return;
}

/* ADD.B #<data>.B,(An)+ */
void REGPARAM2 CPUFUNC(op_0618_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
{{uae_u32 newv = ((uae_u8)(dst)) + ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u8)(~dst)) < ((uae_u8)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (dsta, newv);
}}}}}}}	m68k_incpci (4);
return;
}

/* ADD.B #<data>.B,-(An) */
void REGPARAM2 CPUFUNC(op_0620_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
{{uae_u32 newv = ((uae_u8)(dst)) + ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u8)(~dst)) < ((uae_u8)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (dsta, newv);
}}}}}}}	m68k_incpci (4);
return;
}

/* ADD.B #<data>.B,(d16,An) */
void REGPARAM2 CPUFUNC(op_0628_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s8 dst = x_get_byte (dsta);
{{uae_u32 newv = ((uae_u8)(dst)) + ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u8)(~dst)) < ((uae_u8)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (dsta, newv);
}}}}}}}	m68k_incpci (6);
return;
}

/* ADD.B #<data>.B,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_0630_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	m68k_incpci (4);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s8 dst = x_get_byte (dsta);
{{uae_u32 newv = ((uae_u8)(dst)) + ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u8)(~dst)) < ((uae_u8)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (dsta, newv);
}}}}}}}}return;
}

/* ADD.B #<data>.B,(xxx).W */
void REGPARAM2 CPUFUNC(op_0638_24)(uae_u32 opcode)
{
	OpcodeFamily = 11;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s8 dst = x_get_byte (dsta);
{{uae_u32 newv = ((uae_u8)(dst)) + ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u8)(~dst)) < ((uae_u8)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (dsta, newv);
}}}}}}}	m68k_incpci (6);
return;
}

/* ADD.B #<data>.B,(xxx).L */
void REGPARAM2 CPUFUNC(op_0639_24)(uae_u32 opcode)
{
	OpcodeFamily = 11;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (4);
{	uae_s8 dst = x_get_byte (dsta);
{{uae_u32 newv = ((uae_u8)(dst)) + ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u8)(~dst)) < ((uae_u8)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (dsta, newv);
}}}}}}}	m68k_incpci (8);
return;
}

/* ADD.W #<data>.W,Dn */
void REGPARAM2 CPUFUNC(op_0640_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u16)(dst)) + ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u16)(~dst)) < ((uae_u16)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}}	m68k_incpci (4);
return;
}

/* ADD.W #<data>.W,(An) */
void REGPARAM2 CPUFUNC(op_0650_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s16 dst = x_get_word (dsta);
{{uae_u32 newv = ((uae_u16)(dst)) + ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u16)(~dst)) < ((uae_u16)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (dsta, newv);
}}}}}}}	m68k_incpci (4);
return;
}

/* ADD.W #<data>.W,(An)+ */
void REGPARAM2 CPUFUNC(op_0658_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s16 dst = x_get_word (dsta);
	m68k_areg (regs, dstreg) += 2;
{{uae_u32 newv = ((uae_u16)(dst)) + ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u16)(~dst)) < ((uae_u16)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (dsta, newv);
}}}}}}}	m68k_incpci (4);
return;
}

/* ADD.W #<data>.W,-(An) */
void REGPARAM2 CPUFUNC(op_0660_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
{	uae_s16 dst = x_get_word (dsta);
	m68k_areg (regs, dstreg) = dsta;
{{uae_u32 newv = ((uae_u16)(dst)) + ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u16)(~dst)) < ((uae_u16)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (dsta, newv);
}}}}}}}	m68k_incpci (4);
return;
}

/* ADD.W #<data>.W,(d16,An) */
void REGPARAM2 CPUFUNC(op_0668_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s16 dst = x_get_word (dsta);
{{uae_u32 newv = ((uae_u16)(dst)) + ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u16)(~dst)) < ((uae_u16)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (dsta, newv);
}}}}}}}	m68k_incpci (6);
return;
}

/* ADD.W #<data>.W,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_0670_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	m68k_incpci (4);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s16 dst = x_get_word (dsta);
{{uae_u32 newv = ((uae_u16)(dst)) + ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u16)(~dst)) < ((uae_u16)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (dsta, newv);
}}}}}}}}return;
}

/* ADD.W #<data>.W,(xxx).W */
void REGPARAM2 CPUFUNC(op_0678_24)(uae_u32 opcode)
{
	OpcodeFamily = 11;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s16 dst = x_get_word (dsta);
{{uae_u32 newv = ((uae_u16)(dst)) + ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u16)(~dst)) < ((uae_u16)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (dsta, newv);
}}}}}}}	m68k_incpci (6);
return;
}

/* ADD.W #<data>.W,(xxx).L */
void REGPARAM2 CPUFUNC(op_0679_24)(uae_u32 opcode)
{
	OpcodeFamily = 11;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (4);
{	uae_s16 dst = x_get_word (dsta);
{{uae_u32 newv = ((uae_u16)(dst)) + ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u16)(~dst)) < ((uae_u16)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (dsta, newv);
}}}}}}}	m68k_incpci (8);
return;
}

/* ADD.L #<data>.L,Dn */
void REGPARAM2 CPUFUNC(op_0680_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) + ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u32)(~dst)) < ((uae_u32)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}	m68k_incpci (6);
return;
}

/* ADD.L #<data>.L,(An) */
void REGPARAM2 CPUFUNC(op_0690_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s32 dst = x_get_long (dsta);
{{uae_u32 newv = ((uae_u32)(dst)) + ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u32)(~dst)) < ((uae_u32)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (dsta, newv);
}}}}}}}	m68k_incpci (6);
return;
}

/* ADD.L #<data>.L,(An)+ */
void REGPARAM2 CPUFUNC(op_0698_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s32 dst = x_get_long (dsta);
	m68k_areg (regs, dstreg) += 4;
{{uae_u32 newv = ((uae_u32)(dst)) + ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u32)(~dst)) < ((uae_u32)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (dsta, newv);
}}}}}}}	m68k_incpci (6);
return;
}

/* ADD.L #<data>.L,-(An) */
void REGPARAM2 CPUFUNC(op_06a0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
{	uae_s32 dst = x_get_long (dsta);
	m68k_areg (regs, dstreg) = dsta;
{{uae_u32 newv = ((uae_u32)(dst)) + ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u32)(~dst)) < ((uae_u32)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (dsta, newv);
}}}}}}}	m68k_incpci (6);
return;
}

/* ADD.L #<data>.L,(d16,An) */
void REGPARAM2 CPUFUNC(op_06a8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (6);
{	uae_s32 dst = x_get_long (dsta);
{{uae_u32 newv = ((uae_u32)(dst)) + ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u32)(~dst)) < ((uae_u32)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (dsta, newv);
}}}}}}}	m68k_incpci (8);
return;
}

/* ADD.L #<data>.L,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_06b0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	m68k_incpci (6);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s32 dst = x_get_long (dsta);
{{uae_u32 newv = ((uae_u32)(dst)) + ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u32)(~dst)) < ((uae_u32)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (dsta, newv);
}}}}}}}}return;
}

/* ADD.L #<data>.L,(xxx).W */
void REGPARAM2 CPUFUNC(op_06b8_24)(uae_u32 opcode)
{
	OpcodeFamily = 11;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (6);
{	uae_s32 dst = x_get_long (dsta);
{{uae_u32 newv = ((uae_u32)(dst)) + ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u32)(~dst)) < ((uae_u32)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (dsta, newv);
}}}}}}}	m68k_incpci (8);
return;
}

/* ADD.L #<data>.L,(xxx).L */
void REGPARAM2 CPUFUNC(op_06b9_24)(uae_u32 opcode)
{
	OpcodeFamily = 11;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (6);
{	uae_s32 dst = x_get_long (dsta);
{{uae_u32 newv = ((uae_u32)(dst)) + ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u32)(~dst)) < ((uae_u32)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (dsta, newv);
}}}}}}}	m68k_incpci (10);
return;
}

/* RTM.L Dn */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_06c0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 101;
{	m68k_incpci (2);
	op_illg (opcode);
}return;
}

#endif
/* RTM.L An */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_06c8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 101;
{	m68k_incpci (2);
	op_illg (opcode);
}return;
}

#endif
/* CALLM.L (An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_06d0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 100;
{	m68k_incpci (2);
	op_illg (opcode);
}return;
}

#endif
/* CALLM.L (d16,An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_06e8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 100;
{	m68k_incpci (2);
	op_illg (opcode);
}return;
}

#endif
/* CALLM.L (d8,An,Xn) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_06f0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 100;
{	m68k_incpci (2);
	op_illg (opcode);
}return;
}

#endif
/* CALLM.L (xxx).W */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_06f8_24)(uae_u32 opcode)
{
	OpcodeFamily = 100;
{	m68k_incpci (2);
	op_illg (opcode);
}return;
}

#endif
/* CALLM.L (xxx).L */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_06f9_24)(uae_u32 opcode)
{
	OpcodeFamily = 100;
{	m68k_incpci (2);
	op_illg (opcode);
}return;
}

#endif
/* CALLM.L (d16,PC) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_06fa_24)(uae_u32 opcode)
{
	OpcodeFamily = 100;
{	m68k_incpci (2);
	op_illg (opcode);
}return;
}

#endif
/* CALLM.L (d8,PC,Xn) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_06fb_24)(uae_u32 opcode)
{
	OpcodeFamily = 100;
{	m68k_incpci (2);
	op_illg (opcode);
}return;
}

#endif
/* BTST.L #<data>.W,Dn */
void REGPARAM2 CPUFUNC(op_0800_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 21;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src &= 31;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
}}}	m68k_incpci (4);
return;
}

/* BTST.B #<data>.W,(An) */
void REGPARAM2 CPUFUNC(op_0810_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 21;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = x_get_byte (dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
}}}}	m68k_incpci (4);
return;
}

/* BTST.B #<data>.W,(An)+ */
void REGPARAM2 CPUFUNC(op_0818_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 21;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
}}}}	m68k_incpci (4);
return;
}

/* BTST.B #<data>.W,-(An) */
void REGPARAM2 CPUFUNC(op_0820_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 21;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
}}}}	m68k_incpci (4);
return;
}

/* BTST.B #<data>.W,(d16,An) */
void REGPARAM2 CPUFUNC(op_0828_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 21;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s8 dst = x_get_byte (dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
}}}}	m68k_incpci (6);
return;
}

/* BTST.B #<data>.W,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_0830_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 21;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	m68k_incpci (4);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s8 dst = x_get_byte (dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
}}}}}return;
}

/* BTST.B #<data>.W,(xxx).W */
void REGPARAM2 CPUFUNC(op_0838_24)(uae_u32 opcode)
{
	OpcodeFamily = 21;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s8 dst = x_get_byte (dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
}}}}	m68k_incpci (6);
return;
}

/* BTST.B #<data>.W,(xxx).L */
void REGPARAM2 CPUFUNC(op_0839_24)(uae_u32 opcode)
{
	OpcodeFamily = 21;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (4);
{	uae_s8 dst = x_get_byte (dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
}}}}	m68k_incpci (8);
return;
}

/* BTST.B #<data>.W,(d16,PC) */
void REGPARAM2 CPUFUNC(op_083a_24)(uae_u32 opcode)
{
	uae_u32 dstreg = 2;
	OpcodeFamily = 21;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_getpci () + 4;
	dsta += (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s8 dst = x_get_byte (dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
}}}}	m68k_incpci (6);
return;
}

/* BTST.B #<data>.W,(d8,PC,Xn) */
void REGPARAM2 CPUFUNC(op_083b_24)(uae_u32 opcode)
{
	uae_u32 dstreg = 3;
	OpcodeFamily = 21;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr tmppc;
	uaecptr dsta;
	m68k_incpci (4);
{	tmppc = m68k_getpci ();
	dsta = x_get_disp_ea_040 (tmppc, 0);
{	uae_s8 dst = x_get_byte (dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
}}}}}return;
}

/* BCHG.L #<data>.W,Dn */
void REGPARAM2 CPUFUNC(op_0840_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 22;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src &= 31;
	dst ^= (1 << src);
	SET_ZFLG (((uae_u32)dst & (1 << src)) >> src);
	m68k_dreg (regs, dstreg) = (dst);
}}}	m68k_incpci (4);
return;
}

/* BCHG.B #<data>.W,(An) */
void REGPARAM2 CPUFUNC(op_0850_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 22;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = x_get_byte (dsta);
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (((uae_u32)dst & (1 << src)) >> src);
	x_put_byte (dsta, dst);
}}}}	m68k_incpci (4);
return;
}

/* BCHG.B #<data>.W,(An)+ */
void REGPARAM2 CPUFUNC(op_0858_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 22;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (((uae_u32)dst & (1 << src)) >> src);
	x_put_byte (dsta, dst);
}}}}	m68k_incpci (4);
return;
}

/* BCHG.B #<data>.W,-(An) */
void REGPARAM2 CPUFUNC(op_0860_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 22;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (((uae_u32)dst & (1 << src)) >> src);
	x_put_byte (dsta, dst);
}}}}	m68k_incpci (4);
return;
}

/* BCHG.B #<data>.W,(d16,An) */
void REGPARAM2 CPUFUNC(op_0868_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 22;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s8 dst = x_get_byte (dsta);
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (((uae_u32)dst & (1 << src)) >> src);
	x_put_byte (dsta, dst);
}}}}	m68k_incpci (6);
return;
}

/* BCHG.B #<data>.W,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_0870_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 22;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	m68k_incpci (4);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s8 dst = x_get_byte (dsta);
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (((uae_u32)dst & (1 << src)) >> src);
	x_put_byte (dsta, dst);
}}}}}return;
}

/* BCHG.B #<data>.W,(xxx).W */
void REGPARAM2 CPUFUNC(op_0878_24)(uae_u32 opcode)
{
	OpcodeFamily = 22;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s8 dst = x_get_byte (dsta);
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (((uae_u32)dst & (1 << src)) >> src);
	x_put_byte (dsta, dst);
}}}}	m68k_incpci (6);
return;
}

/* BCHG.B #<data>.W,(xxx).L */
void REGPARAM2 CPUFUNC(op_0879_24)(uae_u32 opcode)
{
	OpcodeFamily = 22;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (4);
{	uae_s8 dst = x_get_byte (dsta);
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (((uae_u32)dst & (1 << src)) >> src);
	x_put_byte (dsta, dst);
}}}}	m68k_incpci (8);
return;
}

/* BCLR.L #<data>.W,Dn */
void REGPARAM2 CPUFUNC(op_0880_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 23;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src &= 31;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	m68k_dreg (regs, dstreg) = (dst);
}}}	m68k_incpci (4);
return;
}

/* BCLR.B #<data>.W,(An) */
void REGPARAM2 CPUFUNC(op_0890_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 23;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = x_get_byte (dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	x_put_byte (dsta, dst);
}}}}	m68k_incpci (4);
return;
}

/* BCLR.B #<data>.W,(An)+ */
void REGPARAM2 CPUFUNC(op_0898_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 23;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	x_put_byte (dsta, dst);
}}}}	m68k_incpci (4);
return;
}

/* BCLR.B #<data>.W,-(An) */
void REGPARAM2 CPUFUNC(op_08a0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 23;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	x_put_byte (dsta, dst);
}}}}	m68k_incpci (4);
return;
}

/* BCLR.B #<data>.W,(d16,An) */
void REGPARAM2 CPUFUNC(op_08a8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 23;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s8 dst = x_get_byte (dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	x_put_byte (dsta, dst);
}}}}	m68k_incpci (6);
return;
}

/* BCLR.B #<data>.W,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_08b0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 23;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	m68k_incpci (4);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s8 dst = x_get_byte (dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	x_put_byte (dsta, dst);
}}}}}return;
}

/* BCLR.B #<data>.W,(xxx).W */
void REGPARAM2 CPUFUNC(op_08b8_24)(uae_u32 opcode)
{
	OpcodeFamily = 23;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s8 dst = x_get_byte (dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	x_put_byte (dsta, dst);
}}}}	m68k_incpci (6);
return;
}

/* BCLR.B #<data>.W,(xxx).L */
void REGPARAM2 CPUFUNC(op_08b9_24)(uae_u32 opcode)
{
	OpcodeFamily = 23;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (4);
{	uae_s8 dst = x_get_byte (dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	x_put_byte (dsta, dst);
}}}}	m68k_incpci (8);
return;
}

/* BSET.L #<data>.W,Dn */
void REGPARAM2 CPUFUNC(op_08c0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 24;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src &= 31;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	m68k_dreg (regs, dstreg) = (dst);
}}}	m68k_incpci (4);
return;
}

/* BSET.B #<data>.W,(An) */
void REGPARAM2 CPUFUNC(op_08d0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 24;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = x_get_byte (dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	x_put_byte (dsta, dst);
}}}}	m68k_incpci (4);
return;
}

/* BSET.B #<data>.W,(An)+ */
void REGPARAM2 CPUFUNC(op_08d8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 24;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	x_put_byte (dsta, dst);
}}}}	m68k_incpci (4);
return;
}

/* BSET.B #<data>.W,-(An) */
void REGPARAM2 CPUFUNC(op_08e0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 24;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	x_put_byte (dsta, dst);
}}}}	m68k_incpci (4);
return;
}

/* BSET.B #<data>.W,(d16,An) */
void REGPARAM2 CPUFUNC(op_08e8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 24;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s8 dst = x_get_byte (dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	x_put_byte (dsta, dst);
}}}}	m68k_incpci (6);
return;
}

/* BSET.B #<data>.W,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_08f0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 24;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	m68k_incpci (4);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s8 dst = x_get_byte (dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	x_put_byte (dsta, dst);
}}}}}return;
}

/* BSET.B #<data>.W,(xxx).W */
void REGPARAM2 CPUFUNC(op_08f8_24)(uae_u32 opcode)
{
	OpcodeFamily = 24;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s8 dst = x_get_byte (dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	x_put_byte (dsta, dst);
}}}}	m68k_incpci (6);
return;
}

/* BSET.B #<data>.W,(xxx).L */
void REGPARAM2 CPUFUNC(op_08f9_24)(uae_u32 opcode)
{
	OpcodeFamily = 24;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (4);
{	uae_s8 dst = x_get_byte (dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	x_put_byte (dsta, dst);
}}}}	m68k_incpci (8);
return;
}

/* EOR.B #<data>.B,Dn */
void REGPARAM2 CPUFUNC(op_0a00_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 3;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}	m68k_incpci (4);
return;
}

/* EOR.B #<data>.B,(An) */
void REGPARAM2 CPUFUNC(op_0a10_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 3;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = x_get_byte (dsta);
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}	m68k_incpci (4);
return;
}

/* EOR.B #<data>.B,(An)+ */
void REGPARAM2 CPUFUNC(op_0a18_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 3;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}	m68k_incpci (4);
return;
}

/* EOR.B #<data>.B,-(An) */
void REGPARAM2 CPUFUNC(op_0a20_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 3;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}	m68k_incpci (4);
return;
}

/* EOR.B #<data>.B,(d16,An) */
void REGPARAM2 CPUFUNC(op_0a28_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 3;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s8 dst = x_get_byte (dsta);
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}	m68k_incpci (6);
return;
}

/* EOR.B #<data>.B,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_0a30_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 3;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	m68k_incpci (4);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s8 dst = x_get_byte (dsta);
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}}return;
}

/* EOR.B #<data>.B,(xxx).W */
void REGPARAM2 CPUFUNC(op_0a38_24)(uae_u32 opcode)
{
	OpcodeFamily = 3;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s8 dst = x_get_byte (dsta);
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}	m68k_incpci (6);
return;
}

/* EOR.B #<data>.B,(xxx).L */
void REGPARAM2 CPUFUNC(op_0a39_24)(uae_u32 opcode)
{
	OpcodeFamily = 3;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (4);
{	uae_s8 dst = x_get_byte (dsta);
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}	m68k_incpci (8);
return;
}

/* EORSR.B #<data>.W */
void REGPARAM2 CPUFUNC(op_0a3c_24)(uae_u32 opcode)
{
	OpcodeFamily = 6;
{	MakeSR ();
{	uae_s16 src = get_iword_cache_040 (2);
	src &= 0xFF;
	regs.sr ^= src;
	MakeFromSR();
}}	m68k_incpci (4);
return;
}

/* EOR.W #<data>.W,Dn */
void REGPARAM2 CPUFUNC(op_0a40_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 3;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}	m68k_incpci (4);
return;
}

/* EOR.W #<data>.W,(An) */
void REGPARAM2 CPUFUNC(op_0a50_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 3;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s16 dst = x_get_word (dsta);
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}	m68k_incpci (4);
return;
}

/* EOR.W #<data>.W,(An)+ */
void REGPARAM2 CPUFUNC(op_0a58_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 3;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s16 dst = x_get_word (dsta);
	m68k_areg (regs, dstreg) += 2;
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}	m68k_incpci (4);
return;
}

/* EOR.W #<data>.W,-(An) */
void REGPARAM2 CPUFUNC(op_0a60_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 3;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
{	uae_s16 dst = x_get_word (dsta);
	m68k_areg (regs, dstreg) = dsta;
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}	m68k_incpci (4);
return;
}

/* EOR.W #<data>.W,(d16,An) */
void REGPARAM2 CPUFUNC(op_0a68_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 3;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s16 dst = x_get_word (dsta);
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}	m68k_incpci (6);
return;
}

/* EOR.W #<data>.W,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_0a70_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 3;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	m68k_incpci (4);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s16 dst = x_get_word (dsta);
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}}return;
}

/* EOR.W #<data>.W,(xxx).W */
void REGPARAM2 CPUFUNC(op_0a78_24)(uae_u32 opcode)
{
	OpcodeFamily = 3;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s16 dst = x_get_word (dsta);
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}	m68k_incpci (6);
return;
}

/* EOR.W #<data>.W,(xxx).L */
void REGPARAM2 CPUFUNC(op_0a79_24)(uae_u32 opcode)
{
	OpcodeFamily = 3;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (4);
{	uae_s16 dst = x_get_word (dsta);
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}	m68k_incpci (8);
return;
}

/* EORSR.W #<data>.W */
void REGPARAM2 CPUFUNC(op_0a7c_24)(uae_u32 opcode)
{
	OpcodeFamily = 6;
{if (!regs.s) { Exception (8); goto l_240221; }
{	MakeSR ();
{	uae_s16 src = get_iword_cache_040 (2);
	regs.sr ^= src;
	MakeFromSR();
}}}	m68k_incpci (4);
l_240221: ;
return;
}

/* EOR.L #<data>.L,Dn */
void REGPARAM2 CPUFUNC(op_0a80_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 3;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	m68k_dreg (regs, dstreg) = (src);
}}}	m68k_incpci (6);
return;
}

/* EOR.L #<data>.L,(An) */
void REGPARAM2 CPUFUNC(op_0a90_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 3;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s32 dst = x_get_long (dsta);
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}	m68k_incpci (6);
return;
}

/* EOR.L #<data>.L,(An)+ */
void REGPARAM2 CPUFUNC(op_0a98_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 3;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s32 dst = x_get_long (dsta);
	m68k_areg (regs, dstreg) += 4;
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}	m68k_incpci (6);
return;
}

/* EOR.L #<data>.L,-(An) */
void REGPARAM2 CPUFUNC(op_0aa0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 3;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
{	uae_s32 dst = x_get_long (dsta);
	m68k_areg (regs, dstreg) = dsta;
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}	m68k_incpci (6);
return;
}

/* EOR.L #<data>.L,(d16,An) */
void REGPARAM2 CPUFUNC(op_0aa8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 3;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (6);
{	uae_s32 dst = x_get_long (dsta);
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}	m68k_incpci (8);
return;
}

/* EOR.L #<data>.L,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_0ab0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 3;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	m68k_incpci (6);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s32 dst = x_get_long (dsta);
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}}return;
}

/* EOR.L #<data>.L,(xxx).W */
void REGPARAM2 CPUFUNC(op_0ab8_24)(uae_u32 opcode)
{
	OpcodeFamily = 3;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (6);
{	uae_s32 dst = x_get_long (dsta);
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}	m68k_incpci (8);
return;
}

/* EOR.L #<data>.L,(xxx).L */
void REGPARAM2 CPUFUNC(op_0ab9_24)(uae_u32 opcode)
{
	OpcodeFamily = 3;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (6);
{	uae_s32 dst = x_get_long (dsta);
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}	m68k_incpci (10);
return;
}

/* CAS.B #<data>.W,(An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0ad0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 84;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = x_get_byte (dsta);
{	int ru = (src >> 6) & 7;
	int rc = src & 7;
{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(m68k_dreg (regs, rc)));
{	int flgs = ((uae_s8)(m68k_dreg (regs, rc))) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u8)(m68k_dreg (regs, rc))) > ((uae_u8)(dst)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG ()) {
		x_put_byte (dsta, (m68k_dreg (regs, ru)));
	}else{
		x_put_byte (dsta, dst);
		m68k_dreg(regs, rc) = (m68k_dreg(regs, rc) & ~0xff) | (dst & 0xff);
}}}}}}}}	m68k_incpci (4);
return;
}

#endif
/* CAS.B #<data>.W,(An)+ */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0ad8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 84;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
{	int ru = (src >> 6) & 7;
	int rc = src & 7;
{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(m68k_dreg (regs, rc)));
{	int flgs = ((uae_s8)(m68k_dreg (regs, rc))) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u8)(m68k_dreg (regs, rc))) > ((uae_u8)(dst)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG ()) {
		x_put_byte (dsta, (m68k_dreg (regs, ru)));
	}else{
		x_put_byte (dsta, dst);
		m68k_dreg(regs, rc) = (m68k_dreg(regs, rc) & ~0xff) | (dst & 0xff);
}}}}}}}}	m68k_incpci (4);
return;
}

#endif
/* CAS.B #<data>.W,-(An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0ae0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 84;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
{	int ru = (src >> 6) & 7;
	int rc = src & 7;
{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(m68k_dreg (regs, rc)));
{	int flgs = ((uae_s8)(m68k_dreg (regs, rc))) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u8)(m68k_dreg (regs, rc))) > ((uae_u8)(dst)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG ()) {
		x_put_byte (dsta, (m68k_dreg (regs, ru)));
	}else{
		x_put_byte (dsta, dst);
		m68k_dreg(regs, rc) = (m68k_dreg(regs, rc) & ~0xff) | (dst & 0xff);
}}}}}}}}	m68k_incpci (4);
return;
}

#endif
/* CAS.B #<data>.W,(d16,An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0ae8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 84;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s8 dst = x_get_byte (dsta);
{	int ru = (src >> 6) & 7;
	int rc = src & 7;
{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(m68k_dreg (regs, rc)));
{	int flgs = ((uae_s8)(m68k_dreg (regs, rc))) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u8)(m68k_dreg (regs, rc))) > ((uae_u8)(dst)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG ()) {
		x_put_byte (dsta, (m68k_dreg (regs, ru)));
	}else{
		x_put_byte (dsta, dst);
		m68k_dreg(regs, rc) = (m68k_dreg(regs, rc) & ~0xff) | (dst & 0xff);
}}}}}}}}	m68k_incpci (6);
return;
}

#endif
#endif

#ifdef PART_2
/* CAS.B #<data>.W,(d8,An,Xn) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0af0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 84;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	m68k_incpci (4);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s8 dst = x_get_byte (dsta);
{	int ru = (src >> 6) & 7;
	int rc = src & 7;
{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(m68k_dreg (regs, rc)));
{	int flgs = ((uae_s8)(m68k_dreg (regs, rc))) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u8)(m68k_dreg (regs, rc))) > ((uae_u8)(dst)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG ()) {
		x_put_byte (dsta, (m68k_dreg (regs, ru)));
	}else{
		x_put_byte (dsta, dst);
		m68k_dreg(regs, rc) = (m68k_dreg(regs, rc) & ~0xff) | (dst & 0xff);
}}}}}}}}}return;
}

#endif
/* CAS.B #<data>.W,(xxx).W */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0af8_24)(uae_u32 opcode)
{
	OpcodeFamily = 84;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s8 dst = x_get_byte (dsta);
{	int ru = (src >> 6) & 7;
	int rc = src & 7;
{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(m68k_dreg (regs, rc)));
{	int flgs = ((uae_s8)(m68k_dreg (regs, rc))) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u8)(m68k_dreg (regs, rc))) > ((uae_u8)(dst)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG ()) {
		x_put_byte (dsta, (m68k_dreg (regs, ru)));
	}else{
		x_put_byte (dsta, dst);
		m68k_dreg(regs, rc) = (m68k_dreg(regs, rc) & ~0xff) | (dst & 0xff);
}}}}}}}}	m68k_incpci (6);
return;
}

#endif
/* CAS.B #<data>.W,(xxx).L */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0af9_24)(uae_u32 opcode)
{
	OpcodeFamily = 84;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (4);
{	uae_s8 dst = x_get_byte (dsta);
{	int ru = (src >> 6) & 7;
	int rc = src & 7;
{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(m68k_dreg (regs, rc)));
{	int flgs = ((uae_s8)(m68k_dreg (regs, rc))) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u8)(m68k_dreg (regs, rc))) > ((uae_u8)(dst)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG ()) {
		x_put_byte (dsta, (m68k_dreg (regs, ru)));
	}else{
		x_put_byte (dsta, dst);
		m68k_dreg(regs, rc) = (m68k_dreg(regs, rc) & ~0xff) | (dst & 0xff);
}}}}}}}}	m68k_incpci (8);
return;
}

#endif
/* CMP.B #<data>.B,Dn */
void REGPARAM2 CPUFUNC(op_0c00_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 25;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}	m68k_incpci (4);
return;
}

/* CMP.B #<data>.B,(An) */
void REGPARAM2 CPUFUNC(op_0c10_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 25;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = x_get_byte (dsta);
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (4);
return;
}

/* CMP.B #<data>.B,(An)+ */
void REGPARAM2 CPUFUNC(op_0c18_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 25;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (4);
return;
}

/* CMP.B #<data>.B,-(An) */
void REGPARAM2 CPUFUNC(op_0c20_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 25;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (4);
return;
}

/* CMP.B #<data>.B,(d16,An) */
void REGPARAM2 CPUFUNC(op_0c28_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 25;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s8 dst = x_get_byte (dsta);
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (6);
return;
}

/* CMP.B #<data>.B,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_0c30_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 25;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	m68k_incpci (4);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s8 dst = x_get_byte (dsta);
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}}return;
}

/* CMP.B #<data>.B,(xxx).W */
void REGPARAM2 CPUFUNC(op_0c38_24)(uae_u32 opcode)
{
	OpcodeFamily = 25;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s8 dst = x_get_byte (dsta);
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (6);
return;
}

/* CMP.B #<data>.B,(xxx).L */
void REGPARAM2 CPUFUNC(op_0c39_24)(uae_u32 opcode)
{
	OpcodeFamily = 25;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (4);
{	uae_s8 dst = x_get_byte (dsta);
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (8);
return;
}

/* CMP.B #<data>.B,(d16,PC) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0c3a_24)(uae_u32 opcode)
{
	uae_u32 dstreg = 2;
	OpcodeFamily = 25;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_getpci () + 4;
	dsta += (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s8 dst = x_get_byte (dsta);
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (6);
return;
}

#endif
/* CMP.B #<data>.B,(d8,PC,Xn) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0c3b_24)(uae_u32 opcode)
{
	uae_u32 dstreg = 3;
	OpcodeFamily = 25;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr tmppc;
	uaecptr dsta;
	m68k_incpci (4);
{	tmppc = m68k_getpci ();
	dsta = x_get_disp_ea_040 (tmppc, 0);
{	uae_s8 dst = x_get_byte (dsta);
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}}return;
}

#endif
/* CMP.W #<data>.W,Dn */
void REGPARAM2 CPUFUNC(op_0c40_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 25;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}	m68k_incpci (4);
return;
}

/* CMP.W #<data>.W,(An) */
void REGPARAM2 CPUFUNC(op_0c50_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 25;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s16 dst = x_get_word (dsta);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (4);
return;
}

/* CMP.W #<data>.W,(An)+ */
void REGPARAM2 CPUFUNC(op_0c58_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 25;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s16 dst = x_get_word (dsta);
	m68k_areg (regs, dstreg) += 2;
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (4);
return;
}

/* CMP.W #<data>.W,-(An) */
void REGPARAM2 CPUFUNC(op_0c60_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 25;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
{	uae_s16 dst = x_get_word (dsta);
	m68k_areg (regs, dstreg) = dsta;
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (4);
return;
}

/* CMP.W #<data>.W,(d16,An) */
void REGPARAM2 CPUFUNC(op_0c68_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 25;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s16 dst = x_get_word (dsta);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (6);
return;
}

/* CMP.W #<data>.W,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_0c70_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 25;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	m68k_incpci (4);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s16 dst = x_get_word (dsta);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}}return;
}

/* CMP.W #<data>.W,(xxx).W */
void REGPARAM2 CPUFUNC(op_0c78_24)(uae_u32 opcode)
{
	OpcodeFamily = 25;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s16 dst = x_get_word (dsta);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (6);
return;
}

/* CMP.W #<data>.W,(xxx).L */
void REGPARAM2 CPUFUNC(op_0c79_24)(uae_u32 opcode)
{
	OpcodeFamily = 25;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (4);
{	uae_s16 dst = x_get_word (dsta);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (8);
return;
}

/* CMP.W #<data>.W,(d16,PC) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0c7a_24)(uae_u32 opcode)
{
	uae_u32 dstreg = 2;
	OpcodeFamily = 25;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_getpci () + 4;
	dsta += (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s16 dst = x_get_word (dsta);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (6);
return;
}

#endif
/* CMP.W #<data>.W,(d8,PC,Xn) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0c7b_24)(uae_u32 opcode)
{
	uae_u32 dstreg = 3;
	OpcodeFamily = 25;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr tmppc;
	uaecptr dsta;
	m68k_incpci (4);
{	tmppc = m68k_getpci ();
	dsta = x_get_disp_ea_040 (tmppc, 0);
{	uae_s16 dst = x_get_word (dsta);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}}return;
}

#endif
/* CMP.L #<data>.L,Dn */
void REGPARAM2 CPUFUNC(op_0c80_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 25;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}	m68k_incpci (6);
return;
}

/* CMP.L #<data>.L,(An) */
void REGPARAM2 CPUFUNC(op_0c90_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 25;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s32 dst = x_get_long (dsta);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (6);
return;
}

/* CMP.L #<data>.L,(An)+ */
void REGPARAM2 CPUFUNC(op_0c98_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 25;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s32 dst = x_get_long (dsta);
	m68k_areg (regs, dstreg) += 4;
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (6);
return;
}

/* CMP.L #<data>.L,-(An) */
void REGPARAM2 CPUFUNC(op_0ca0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 25;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
{	uae_s32 dst = x_get_long (dsta);
	m68k_areg (regs, dstreg) = dsta;
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (6);
return;
}

/* CMP.L #<data>.L,(d16,An) */
void REGPARAM2 CPUFUNC(op_0ca8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 25;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (6);
{	uae_s32 dst = x_get_long (dsta);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (8);
return;
}

/* CMP.L #<data>.L,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_0cb0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 25;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	m68k_incpci (6);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s32 dst = x_get_long (dsta);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}}return;
}

/* CMP.L #<data>.L,(xxx).W */
void REGPARAM2 CPUFUNC(op_0cb8_24)(uae_u32 opcode)
{
	OpcodeFamily = 25;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (6);
{	uae_s32 dst = x_get_long (dsta);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (8);
return;
}

/* CMP.L #<data>.L,(xxx).L */
void REGPARAM2 CPUFUNC(op_0cb9_24)(uae_u32 opcode)
{
	OpcodeFamily = 25;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (6);
{	uae_s32 dst = x_get_long (dsta);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (10);
return;
}

/* CMP.L #<data>.L,(d16,PC) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0cba_24)(uae_u32 opcode)
{
	uae_u32 dstreg = 2;
	OpcodeFamily = 25;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_getpci () + 6;
	dsta += (uae_s32)(uae_s16)get_iword_cache_040 (6);
{	uae_s32 dst = x_get_long (dsta);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (8);
return;
}

#endif
/* CMP.L #<data>.L,(d8,PC,Xn) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0cbb_24)(uae_u32 opcode)
{
	uae_u32 dstreg = 3;
	OpcodeFamily = 25;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr tmppc;
	uaecptr dsta;
	m68k_incpci (6);
{	tmppc = m68k_getpci ();
	dsta = x_get_disp_ea_040 (tmppc, 0);
{	uae_s32 dst = x_get_long (dsta);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}}return;
}

#endif
/* CAS.W #<data>.W,(An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0cd0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 84;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s16 dst = x_get_word (dsta);
	if ((dsta & 1) && currprefs.int_no_unimplemented && get_cpu_model () == 68060) {
	m68k_incpci (4);
		op_unimpl (opcode);
		goto l_240267;
	}
{	int ru = (src >> 6) & 7;
	int rc = src & 7;
{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(m68k_dreg (regs, rc)));
{	int flgs = ((uae_s16)(m68k_dreg (regs, rc))) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u16)(m68k_dreg (regs, rc))) > ((uae_u16)(dst)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG ()) {
		x_put_word (dsta, (m68k_dreg (regs, ru)));
	}else{
		x_put_word (dsta, dst);
		m68k_dreg(regs, rc) = (m68k_dreg(regs, rc) & ~0xffff) | (dst & 0xffff);
}}}}}}}}	m68k_incpci (4);
l_240267: ;
return;
}

#endif
/* CAS.W #<data>.W,(An)+ */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0cd8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 84;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s16 dst = x_get_word (dsta);
	m68k_areg (regs, dstreg) += 2;
	if ((dsta & 1) && currprefs.int_no_unimplemented && get_cpu_model () == 68060) {
		m68k_areg (regs, dstreg) -= 2;
	m68k_incpci (4);
		op_unimpl (opcode);
		goto l_240268;
	}
{	int ru = (src >> 6) & 7;
	int rc = src & 7;
{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(m68k_dreg (regs, rc)));
{	int flgs = ((uae_s16)(m68k_dreg (regs, rc))) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u16)(m68k_dreg (regs, rc))) > ((uae_u16)(dst)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG ()) {
		x_put_word (dsta, (m68k_dreg (regs, ru)));
	}else{
		x_put_word (dsta, dst);
		m68k_dreg(regs, rc) = (m68k_dreg(regs, rc) & ~0xffff) | (dst & 0xffff);
}}}}}}}}	m68k_incpci (4);
l_240268: ;
return;
}

#endif
/* CAS.W #<data>.W,-(An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0ce0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 84;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
{	uae_s16 dst = x_get_word (dsta);
	m68k_areg (regs, dstreg) = dsta;
	if ((dsta & 1) && currprefs.int_no_unimplemented && get_cpu_model () == 68060) {
		m68k_areg (regs, dstreg) += 2;
	m68k_incpci (4);
		op_unimpl (opcode);
		goto l_240269;
	}
{	int ru = (src >> 6) & 7;
	int rc = src & 7;
{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(m68k_dreg (regs, rc)));
{	int flgs = ((uae_s16)(m68k_dreg (regs, rc))) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u16)(m68k_dreg (regs, rc))) > ((uae_u16)(dst)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG ()) {
		x_put_word (dsta, (m68k_dreg (regs, ru)));
	}else{
		x_put_word (dsta, dst);
		m68k_dreg(regs, rc) = (m68k_dreg(regs, rc) & ~0xffff) | (dst & 0xffff);
}}}}}}}}	m68k_incpci (4);
l_240269: ;
return;
}

#endif
/* CAS.W #<data>.W,(d16,An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0ce8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 84;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s16 dst = x_get_word (dsta);
	if ((dsta & 1) && currprefs.int_no_unimplemented && get_cpu_model () == 68060) {
	m68k_incpci (6);
		op_unimpl (opcode);
		goto l_240270;
	}
{	int ru = (src >> 6) & 7;
	int rc = src & 7;
{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(m68k_dreg (regs, rc)));
{	int flgs = ((uae_s16)(m68k_dreg (regs, rc))) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u16)(m68k_dreg (regs, rc))) > ((uae_u16)(dst)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG ()) {
		x_put_word (dsta, (m68k_dreg (regs, ru)));
	}else{
		x_put_word (dsta, dst);
		m68k_dreg(regs, rc) = (m68k_dreg(regs, rc) & ~0xffff) | (dst & 0xffff);
}}}}}}}}	m68k_incpci (6);
l_240270: ;
return;
}

#endif
/* CAS.W #<data>.W,(d8,An,Xn) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0cf0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 84;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	m68k_incpci (4);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s16 dst = x_get_word (dsta);
	if ((dsta & 1) && currprefs.int_no_unimplemented && get_cpu_model () == 68060) {
		op_unimpl (opcode);
		goto l_240271;
	}
{	int ru = (src >> 6) & 7;
	int rc = src & 7;
{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(m68k_dreg (regs, rc)));
{	int flgs = ((uae_s16)(m68k_dreg (regs, rc))) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u16)(m68k_dreg (regs, rc))) > ((uae_u16)(dst)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG ()) {
		x_put_word (dsta, (m68k_dreg (regs, ru)));
	}else{
		x_put_word (dsta, dst);
		m68k_dreg(regs, rc) = (m68k_dreg(regs, rc) & ~0xffff) | (dst & 0xffff);
}}}}}}}}}l_240271: ;
return;
}

#endif
/* CAS.W #<data>.W,(xxx).W */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0cf8_24)(uae_u32 opcode)
{
	OpcodeFamily = 84;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s16 dst = x_get_word (dsta);
	if ((dsta & 1) && currprefs.int_no_unimplemented && get_cpu_model () == 68060) {
	m68k_incpci (6);
		op_unimpl (opcode);
		goto l_240272;
	}
{	int ru = (src >> 6) & 7;
	int rc = src & 7;
{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(m68k_dreg (regs, rc)));
{	int flgs = ((uae_s16)(m68k_dreg (regs, rc))) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u16)(m68k_dreg (regs, rc))) > ((uae_u16)(dst)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG ()) {
		x_put_word (dsta, (m68k_dreg (regs, ru)));
	}else{
		x_put_word (dsta, dst);
		m68k_dreg(regs, rc) = (m68k_dreg(regs, rc) & ~0xffff) | (dst & 0xffff);
}}}}}}}}	m68k_incpci (6);
l_240272: ;
return;
}

#endif
/* CAS.W #<data>.W,(xxx).L */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0cf9_24)(uae_u32 opcode)
{
	OpcodeFamily = 84;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (4);
{	uae_s16 dst = x_get_word (dsta);
	if ((dsta & 1) && currprefs.int_no_unimplemented && get_cpu_model () == 68060) {
	m68k_incpci (8);
		op_unimpl (opcode);
		goto l_240273;
	}
{	int ru = (src >> 6) & 7;
	int rc = src & 7;
{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(m68k_dreg (regs, rc)));
{	int flgs = ((uae_s16)(m68k_dreg (regs, rc))) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u16)(m68k_dreg (regs, rc))) > ((uae_u16)(dst)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG ()) {
		x_put_word (dsta, (m68k_dreg (regs, ru)));
	}else{
		x_put_word (dsta, dst);
		m68k_dreg(regs, rc) = (m68k_dreg(regs, rc) & ~0xffff) | (dst & 0xffff);
}}}}}}}}	m68k_incpci (8);
l_240273: ;
return;
}

#endif
/* CAS2.W #<data>.L */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0cfc_24)(uae_u32 opcode)
{
	OpcodeFamily = 85;
{{	uae_s32 extra;
	extra = get_ilong_cache_040 (2);
	uae_u32 rn1 = regs.regs[(extra >> 28) & 15];
	uae_u32 rn2 = regs.regs[(extra >> 12) & 15];
	uae_u16 dst1 = x_get_word (rn1), dst2 = x_get_word (rn2);
{uae_u32 newv = ((uae_u16)(dst1)) - ((uae_u16)(m68k_dreg (regs, (extra >> 16) & 7)));
{	int flgs = ((uae_s16)(m68k_dreg (regs, (extra >> 16) & 7))) < 0;
	int flgo = ((uae_s16)(dst1)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u16)(m68k_dreg (regs, (extra >> 16) & 7))) > ((uae_u16)(dst1)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG ()) {
{uae_u32 newv = ((uae_u16)(dst2)) - ((uae_u16)(m68k_dreg (regs, extra & 7)));
{	int flgs = ((uae_s16)(m68k_dreg (regs, extra & 7))) < 0;
	int flgo = ((uae_s16)(dst2)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u16)(m68k_dreg (regs, extra & 7))) > ((uae_u16)(dst2)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG ()) {
	x_put_word (rn1, m68k_dreg (regs, (extra >> 22) & 7));
	x_put_word (rn2, m68k_dreg (regs, (extra >> 6) & 7));
	}}
}}}}	if (! GET_ZFLG ()) {
	m68k_dreg (regs, (extra >> 0) & 7) = (m68k_dreg (regs, (extra >> 6) & 7) & ~0xffff) | (dst2 & 0xffff);
	m68k_dreg (regs, (extra >> 16) & 7) = (m68k_dreg (regs, (extra >> 22) & 7) & ~0xffff) | (dst1 & 0xffff);
	}
}}	m68k_incpci (6);
return;
}

#endif
/* MOVES.B #<data>.W,(An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0e10_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 103;
{if (!regs.s) { Exception (8); goto l_240275; }
{{	uae_s16 extra = get_iword_cache_040 (2);
	if (extra & 0x800)
{	uae_u32 src = regs.regs[(extra >> 12) & 15];
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	x_put_byte (dsta, src);
}}else{{	uaecptr srca;
	srca = m68k_areg (regs, dstreg);
{	uae_s8 src = x_get_byte (srca);
	if (extra & 0x8000) {
	m68k_areg (regs, (extra >> 12) & 7) = (uae_s32)(uae_s8)src;
	} else {
	m68k_dreg (regs, (extra >> 12) & 7) = (m68k_dreg (regs, (extra >> 12) & 7) & ~0xff) | ((src) & 0xff);
	}
}}}}}}	m68k_incpci (4);
l_240275: ;
return;
}

#endif
/* MOVES.B #<data>.W,(An)+ */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0e18_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 103;
{if (!regs.s) { Exception (8); goto l_240276; }
{{	uae_s16 extra = get_iword_cache_040 (2);
	if (extra & 0x800)
{	uae_u32 src = regs.regs[(extra >> 12) & 15];
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	x_put_byte (dsta, src);
}}else{{	uaecptr srca;
	srca = m68k_areg (regs, dstreg);
{	uae_s8 src = x_get_byte (srca);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	if (extra & 0x8000) {
	m68k_areg (regs, (extra >> 12) & 7) = (uae_s32)(uae_s8)src;
	} else {
	m68k_dreg (regs, (extra >> 12) & 7) = (m68k_dreg (regs, (extra >> 12) & 7) & ~0xff) | ((src) & 0xff);
	}
}}}}}}	m68k_incpci (4);
l_240276: ;
return;
}

#endif
/* MOVES.B #<data>.W,-(An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0e20_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 103;
{if (!regs.s) { Exception (8); goto l_240277; }
{{	uae_s16 extra = get_iword_cache_040 (2);
	if (extra & 0x800)
{	uae_u32 src = regs.regs[(extra >> 12) & 15];
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
	m68k_areg (regs, dstreg) = dsta;
	x_put_byte (dsta, src);
}}else{{	uaecptr srca;
	srca = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 src = x_get_byte (srca);
	m68k_areg (regs, dstreg) = srca;
	if (extra & 0x8000) {
	m68k_areg (regs, (extra >> 12) & 7) = (uae_s32)(uae_s8)src;
	} else {
	m68k_dreg (regs, (extra >> 12) & 7) = (m68k_dreg (regs, (extra >> 12) & 7) & ~0xff) | ((src) & 0xff);
	}
}}}}}}	m68k_incpci (4);
l_240277: ;
return;
}

#endif
/* MOVES.B #<data>.W,(d16,An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0e28_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 103;
{if (!regs.s) { Exception (8); goto l_240278; }
{{	uae_s16 extra = get_iword_cache_040 (2);
	if (extra & 0x800)
{	uae_u32 src = regs.regs[(extra >> 12) & 15];
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
	x_put_byte (dsta, src);
}}else{{	uaecptr srca;
	srca = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s8 src = x_get_byte (srca);
	if (extra & 0x8000) {
	m68k_areg (regs, (extra >> 12) & 7) = (uae_s32)(uae_s8)src;
	} else {
	m68k_dreg (regs, (extra >> 12) & 7) = (m68k_dreg (regs, (extra >> 12) & 7) & ~0xff) | ((src) & 0xff);
	}
}}}}}}	m68k_incpci (6);
l_240278: ;
return;
}

#endif
/* MOVES.B #<data>.W,(d8,An,Xn) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0e30_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 103;
{if (!regs.s) { Exception (8); goto l_240279; }
{{	uae_s16 extra = get_iword_cache_040 (2);
	if (extra & 0x800)
{	uae_u32 src = regs.regs[(extra >> 12) & 15];
{	uaecptr dsta;
	m68k_incpci (4);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
	x_put_byte (dsta, src);
}}}else{{	uaecptr srca;
	m68k_incpci (4);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 1);
{	uae_s8 src = x_get_byte (srca);
	if (extra & 0x8000) {
	m68k_areg (regs, (extra >> 12) & 7) = (uae_s32)(uae_s8)src;
	} else {
	m68k_dreg (regs, (extra >> 12) & 7) = (m68k_dreg (regs, (extra >> 12) & 7) & ~0xff) | ((src) & 0xff);
	}
}}}}}}}l_240279: ;
return;
}

#endif
/* MOVES.B #<data>.W,(xxx).W */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0e38_24)(uae_u32 opcode)
{
	OpcodeFamily = 103;
{if (!regs.s) { Exception (8); goto l_240280; }
{{	uae_s16 extra = get_iword_cache_040 (2);
	if (extra & 0x800)
{	uae_u32 src = regs.regs[(extra >> 12) & 15];
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (4);
	x_put_byte (dsta, src);
}}else{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s8 src = x_get_byte (srca);
	if (extra & 0x8000) {
	m68k_areg (regs, (extra >> 12) & 7) = (uae_s32)(uae_s8)src;
	} else {
	m68k_dreg (regs, (extra >> 12) & 7) = (m68k_dreg (regs, (extra >> 12) & 7) & ~0xff) | ((src) & 0xff);
	}
}}}}}}	m68k_incpci (6);
l_240280: ;
return;
}

#endif
/* MOVES.B #<data>.W,(xxx).L */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0e39_24)(uae_u32 opcode)
{
	OpcodeFamily = 103;
{if (!regs.s) { Exception (8); goto l_240281; }
{{	uae_s16 extra = get_iword_cache_040 (2);
	if (extra & 0x800)
{	uae_u32 src = regs.regs[(extra >> 12) & 15];
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (4);
	x_put_byte (dsta, src);
}}else{{	uaecptr srca;
	srca = get_ilong_cache_040 (4);
{	uae_s8 src = x_get_byte (srca);
	if (extra & 0x8000) {
	m68k_areg (regs, (extra >> 12) & 7) = (uae_s32)(uae_s8)src;
	} else {
	m68k_dreg (regs, (extra >> 12) & 7) = (m68k_dreg (regs, (extra >> 12) & 7) & ~0xff) | ((src) & 0xff);
	}
}}}}}}	m68k_incpci (8);
l_240281: ;
return;
}

#endif
/* MOVES.W #<data>.W,(An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0e50_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 103;
{if (!regs.s) { Exception (8); goto l_240282; }
{{	uae_s16 extra = get_iword_cache_040 (2);
	if (extra & 0x800)
{	uae_u32 src = regs.regs[(extra >> 12) & 15];
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	x_put_word (dsta, src);
}}else{{	uaecptr srca;
	srca = m68k_areg (regs, dstreg);
{	uae_s16 src = x_get_word (srca);
	if (extra & 0x8000) {
	m68k_areg (regs, (extra >> 12) & 7) = (uae_s32)(uae_s16)src;
	} else {
	m68k_dreg (regs, (extra >> 12) & 7) = (m68k_dreg (regs, (extra >> 12) & 7) & ~0xffff) | ((src) & 0xffff);
	}
}}}}}}	m68k_incpci (4);
l_240282: ;
return;
}

#endif
/* MOVES.W #<data>.W,(An)+ */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0e58_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 103;
{if (!regs.s) { Exception (8); goto l_240283; }
{{	uae_s16 extra = get_iword_cache_040 (2);
	if (extra & 0x800)
{	uae_u32 src = regs.regs[(extra >> 12) & 15];
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += 2;
	x_put_word (dsta, src);
}}else{{	uaecptr srca;
	srca = m68k_areg (regs, dstreg);
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, dstreg) += 2;
	if (extra & 0x8000) {
	m68k_areg (regs, (extra >> 12) & 7) = (uae_s32)(uae_s16)src;
	} else {
	m68k_dreg (regs, (extra >> 12) & 7) = (m68k_dreg (regs, (extra >> 12) & 7) & ~0xffff) | ((src) & 0xffff);
	}
}}}}}}	m68k_incpci (4);
l_240283: ;
return;
}

#endif
/* MOVES.W #<data>.W,-(An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0e60_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 103;
{if (!regs.s) { Exception (8); goto l_240284; }
{{	uae_s16 extra = get_iword_cache_040 (2);
	if (extra & 0x800)
{	uae_u32 src = regs.regs[(extra >> 12) & 15];
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
	m68k_areg (regs, dstreg) = dsta;
	x_put_word (dsta, src);
}}else{{	uaecptr srca;
	srca = m68k_areg (regs, dstreg) - 2;
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, dstreg) = srca;
	if (extra & 0x8000) {
	m68k_areg (regs, (extra >> 12) & 7) = (uae_s32)(uae_s16)src;
	} else {
	m68k_dreg (regs, (extra >> 12) & 7) = (m68k_dreg (regs, (extra >> 12) & 7) & ~0xffff) | ((src) & 0xffff);
	}
}}}}}}	m68k_incpci (4);
l_240284: ;
return;
}

#endif
/* MOVES.W #<data>.W,(d16,An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0e68_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 103;
{if (!regs.s) { Exception (8); goto l_240285; }
{{	uae_s16 extra = get_iword_cache_040 (2);
	if (extra & 0x800)
{	uae_u32 src = regs.regs[(extra >> 12) & 15];
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
	x_put_word (dsta, src);
}}else{{	uaecptr srca;
	srca = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s16 src = x_get_word (srca);
	if (extra & 0x8000) {
	m68k_areg (regs, (extra >> 12) & 7) = (uae_s32)(uae_s16)src;
	} else {
	m68k_dreg (regs, (extra >> 12) & 7) = (m68k_dreg (regs, (extra >> 12) & 7) & ~0xffff) | ((src) & 0xffff);
	}
}}}}}}	m68k_incpci (6);
l_240285: ;
return;
}

#endif
/* MOVES.W #<data>.W,(d8,An,Xn) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0e70_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 103;
{if (!regs.s) { Exception (8); goto l_240286; }
{{	uae_s16 extra = get_iword_cache_040 (2);
	if (extra & 0x800)
{	uae_u32 src = regs.regs[(extra >> 12) & 15];
{	uaecptr dsta;
	m68k_incpci (4);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
	x_put_word (dsta, src);
}}}else{{	uaecptr srca;
	m68k_incpci (4);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 1);
{	uae_s16 src = x_get_word (srca);
	if (extra & 0x8000) {
	m68k_areg (regs, (extra >> 12) & 7) = (uae_s32)(uae_s16)src;
	} else {
	m68k_dreg (regs, (extra >> 12) & 7) = (m68k_dreg (regs, (extra >> 12) & 7) & ~0xffff) | ((src) & 0xffff);
	}
}}}}}}}l_240286: ;
return;
}

#endif
/* MOVES.W #<data>.W,(xxx).W */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0e78_24)(uae_u32 opcode)
{
	OpcodeFamily = 103;
{if (!regs.s) { Exception (8); goto l_240287; }
{{	uae_s16 extra = get_iword_cache_040 (2);
	if (extra & 0x800)
{	uae_u32 src = regs.regs[(extra >> 12) & 15];
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (4);
	x_put_word (dsta, src);
}}else{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s16 src = x_get_word (srca);
	if (extra & 0x8000) {
	m68k_areg (regs, (extra >> 12) & 7) = (uae_s32)(uae_s16)src;
	} else {
	m68k_dreg (regs, (extra >> 12) & 7) = (m68k_dreg (regs, (extra >> 12) & 7) & ~0xffff) | ((src) & 0xffff);
	}
}}}}}}	m68k_incpci (6);
l_240287: ;
return;
}

#endif
/* MOVES.W #<data>.W,(xxx).L */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0e79_24)(uae_u32 opcode)
{
	OpcodeFamily = 103;
{if (!regs.s) { Exception (8); goto l_240288; }
{{	uae_s16 extra = get_iword_cache_040 (2);
	if (extra & 0x800)
{	uae_u32 src = regs.regs[(extra >> 12) & 15];
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (4);
	x_put_word (dsta, src);
}}else{{	uaecptr srca;
	srca = get_ilong_cache_040 (4);
{	uae_s16 src = x_get_word (srca);
	if (extra & 0x8000) {
	m68k_areg (regs, (extra >> 12) & 7) = (uae_s32)(uae_s16)src;
	} else {
	m68k_dreg (regs, (extra >> 12) & 7) = (m68k_dreg (regs, (extra >> 12) & 7) & ~0xffff) | ((src) & 0xffff);
	}
}}}}}}	m68k_incpci (8);
l_240288: ;
return;
}

#endif
/* MOVES.L #<data>.W,(An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0e90_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 103;
{if (!regs.s) { Exception (8); goto l_240289; }
{{	uae_s16 extra = get_iword_cache_040 (2);
	if (extra & 0x800)
{	uae_u32 src = regs.regs[(extra >> 12) & 15];
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	x_put_long (dsta, src);
}}else{{	uaecptr srca;
	srca = m68k_areg (regs, dstreg);
{	uae_s32 src = x_get_long (srca);
	if (extra & 0x8000) {
	m68k_areg (regs, (extra >> 12) & 7) = src;
	} else {
	m68k_dreg (regs, (extra >> 12) & 7) = (src);
	}
}}}}}}	m68k_incpci (4);
l_240289: ;
return;
}

#endif
/* MOVES.L #<data>.W,(An)+ */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0e98_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 103;
{if (!regs.s) { Exception (8); goto l_240290; }
{{	uae_s16 extra = get_iword_cache_040 (2);
	if (extra & 0x800)
{	uae_u32 src = regs.regs[(extra >> 12) & 15];
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += 4;
	x_put_long (dsta, src);
}}else{{	uaecptr srca;
	srca = m68k_areg (regs, dstreg);
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, dstreg) += 4;
	if (extra & 0x8000) {
	m68k_areg (regs, (extra >> 12) & 7) = src;
	} else {
	m68k_dreg (regs, (extra >> 12) & 7) = (src);
	}
}}}}}}	m68k_incpci (4);
l_240290: ;
return;
}

#endif
/* MOVES.L #<data>.W,-(An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0ea0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 103;
{if (!regs.s) { Exception (8); goto l_240291; }
{{	uae_s16 extra = get_iword_cache_040 (2);
	if (extra & 0x800)
{	uae_u32 src = regs.regs[(extra >> 12) & 15];
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
	m68k_areg (regs, dstreg) = dsta;
	x_put_long (dsta, src);
}}else{{	uaecptr srca;
	srca = m68k_areg (regs, dstreg) - 4;
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, dstreg) = srca;
	if (extra & 0x8000) {
	m68k_areg (regs, (extra >> 12) & 7) = src;
	} else {
	m68k_dreg (regs, (extra >> 12) & 7) = (src);
	}
}}}}}}	m68k_incpci (4);
l_240291: ;
return;
}

#endif
/* MOVES.L #<data>.W,(d16,An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0ea8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 103;
{if (!regs.s) { Exception (8); goto l_240292; }
{{	uae_s16 extra = get_iword_cache_040 (2);
	if (extra & 0x800)
{	uae_u32 src = regs.regs[(extra >> 12) & 15];
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
	x_put_long (dsta, src);
}}else{{	uaecptr srca;
	srca = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s32 src = x_get_long (srca);
	if (extra & 0x8000) {
	m68k_areg (regs, (extra >> 12) & 7) = src;
	} else {
	m68k_dreg (regs, (extra >> 12) & 7) = (src);
	}
}}}}}}	m68k_incpci (6);
l_240292: ;
return;
}

#endif
/* MOVES.L #<data>.W,(d8,An,Xn) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0eb0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 103;
{if (!regs.s) { Exception (8); goto l_240293; }
{{	uae_s16 extra = get_iword_cache_040 (2);
	if (extra & 0x800)
{	uae_u32 src = regs.regs[(extra >> 12) & 15];
{	uaecptr dsta;
	m68k_incpci (4);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
	x_put_long (dsta, src);
}}}else{{	uaecptr srca;
	m68k_incpci (4);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 1);
{	uae_s32 src = x_get_long (srca);
	if (extra & 0x8000) {
	m68k_areg (regs, (extra >> 12) & 7) = src;
	} else {
	m68k_dreg (regs, (extra >> 12) & 7) = (src);
	}
}}}}}}}l_240293: ;
return;
}

#endif
/* MOVES.L #<data>.W,(xxx).W */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0eb8_24)(uae_u32 opcode)
{
	OpcodeFamily = 103;
{if (!regs.s) { Exception (8); goto l_240294; }
{{	uae_s16 extra = get_iword_cache_040 (2);
	if (extra & 0x800)
{	uae_u32 src = regs.regs[(extra >> 12) & 15];
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (4);
	x_put_long (dsta, src);
}}else{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s32 src = x_get_long (srca);
	if (extra & 0x8000) {
	m68k_areg (regs, (extra >> 12) & 7) = src;
	} else {
	m68k_dreg (regs, (extra >> 12) & 7) = (src);
	}
}}}}}}	m68k_incpci (6);
l_240294: ;
return;
}

#endif
/* MOVES.L #<data>.W,(xxx).L */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0eb9_24)(uae_u32 opcode)
{
	OpcodeFamily = 103;
{if (!regs.s) { Exception (8); goto l_240295; }
{{	uae_s16 extra = get_iword_cache_040 (2);
	if (extra & 0x800)
{	uae_u32 src = regs.regs[(extra >> 12) & 15];
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (4);
	x_put_long (dsta, src);
}}else{{	uaecptr srca;
	srca = get_ilong_cache_040 (4);
{	uae_s32 src = x_get_long (srca);
	if (extra & 0x8000) {
	m68k_areg (regs, (extra >> 12) & 7) = src;
	} else {
	m68k_dreg (regs, (extra >> 12) & 7) = (src);
	}
}}}}}}	m68k_incpci (8);
l_240295: ;
return;
}

#endif
/* CAS.L #<data>.W,(An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0ed0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 84;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s32 dst = x_get_long (dsta);
	if ((dsta & 3) && currprefs.int_no_unimplemented && get_cpu_model () == 68060) {
	m68k_incpci (4);
		op_unimpl (opcode);
		goto l_240296;
	}
{	int ru = (src >> 6) & 7;
	int rc = src & 7;
{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(m68k_dreg (regs, rc)));
{	int flgs = ((uae_s32)(m68k_dreg (regs, rc))) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(m68k_dreg (regs, rc))) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG ()) {
		x_put_long (dsta, (m68k_dreg (regs, ru)));
	}else{
		x_put_long (dsta, dst);
		m68k_dreg(regs, rc) = dst;
}}}}}}}}	m68k_incpci (4);
l_240296: ;
return;
}

#endif
/* CAS.L #<data>.W,(An)+ */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0ed8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 84;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s32 dst = x_get_long (dsta);
	m68k_areg (regs, dstreg) += 4;
	if ((dsta & 3) && currprefs.int_no_unimplemented && get_cpu_model () == 68060) {
		m68k_areg (regs, dstreg) -= 4;
	m68k_incpci (4);
		op_unimpl (opcode);
		goto l_240297;
	}
{	int ru = (src >> 6) & 7;
	int rc = src & 7;
{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(m68k_dreg (regs, rc)));
{	int flgs = ((uae_s32)(m68k_dreg (regs, rc))) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(m68k_dreg (regs, rc))) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG ()) {
		x_put_long (dsta, (m68k_dreg (regs, ru)));
	}else{
		x_put_long (dsta, dst);
		m68k_dreg(regs, rc) = dst;
}}}}}}}}	m68k_incpci (4);
l_240297: ;
return;
}

#endif
/* CAS.L #<data>.W,-(An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0ee0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 84;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
{	uae_s32 dst = x_get_long (dsta);
	m68k_areg (regs, dstreg) = dsta;
	if ((dsta & 3) && currprefs.int_no_unimplemented && get_cpu_model () == 68060) {
		m68k_areg (regs, dstreg) += 4;
	m68k_incpci (4);
		op_unimpl (opcode);
		goto l_240298;
	}
{	int ru = (src >> 6) & 7;
	int rc = src & 7;
{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(m68k_dreg (regs, rc)));
{	int flgs = ((uae_s32)(m68k_dreg (regs, rc))) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(m68k_dreg (regs, rc))) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG ()) {
		x_put_long (dsta, (m68k_dreg (regs, ru)));
	}else{
		x_put_long (dsta, dst);
		m68k_dreg(regs, rc) = dst;
}}}}}}}}	m68k_incpci (4);
l_240298: ;
return;
}

#endif
/* CAS.L #<data>.W,(d16,An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0ee8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 84;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s32 dst = x_get_long (dsta);
	if ((dsta & 3) && currprefs.int_no_unimplemented && get_cpu_model () == 68060) {
	m68k_incpci (6);
		op_unimpl (opcode);
		goto l_240299;
	}
{	int ru = (src >> 6) & 7;
	int rc = src & 7;
{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(m68k_dreg (regs, rc)));
{	int flgs = ((uae_s32)(m68k_dreg (regs, rc))) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(m68k_dreg (regs, rc))) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG ()) {
		x_put_long (dsta, (m68k_dreg (regs, ru)));
	}else{
		x_put_long (dsta, dst);
		m68k_dreg(regs, rc) = dst;
}}}}}}}}	m68k_incpci (6);
l_240299: ;
return;
}

#endif
/* CAS.L #<data>.W,(d8,An,Xn) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0ef0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 84;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	m68k_incpci (4);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s32 dst = x_get_long (dsta);
	if ((dsta & 3) && currprefs.int_no_unimplemented && get_cpu_model () == 68060) {
		op_unimpl (opcode);
		goto l_240300;
	}
{	int ru = (src >> 6) & 7;
	int rc = src & 7;
{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(m68k_dreg (regs, rc)));
{	int flgs = ((uae_s32)(m68k_dreg (regs, rc))) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(m68k_dreg (regs, rc))) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG ()) {
		x_put_long (dsta, (m68k_dreg (regs, ru)));
	}else{
		x_put_long (dsta, dst);
		m68k_dreg(regs, rc) = dst;
}}}}}}}}}l_240300: ;
return;
}

#endif
/* CAS.L #<data>.W,(xxx).W */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0ef8_24)(uae_u32 opcode)
{
	OpcodeFamily = 84;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s32 dst = x_get_long (dsta);
	if ((dsta & 3) && currprefs.int_no_unimplemented && get_cpu_model () == 68060) {
	m68k_incpci (6);
		op_unimpl (opcode);
		goto l_240301;
	}
{	int ru = (src >> 6) & 7;
	int rc = src & 7;
{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(m68k_dreg (regs, rc)));
{	int flgs = ((uae_s32)(m68k_dreg (regs, rc))) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(m68k_dreg (regs, rc))) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG ()) {
		x_put_long (dsta, (m68k_dreg (regs, ru)));
	}else{
		x_put_long (dsta, dst);
		m68k_dreg(regs, rc) = dst;
}}}}}}}}	m68k_incpci (6);
l_240301: ;
return;
}

#endif
/* CAS.L #<data>.W,(xxx).L */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0ef9_24)(uae_u32 opcode)
{
	OpcodeFamily = 84;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (4);
{	uae_s32 dst = x_get_long (dsta);
	if ((dsta & 3) && currprefs.int_no_unimplemented && get_cpu_model () == 68060) {
	m68k_incpci (8);
		op_unimpl (opcode);
		goto l_240302;
	}
{	int ru = (src >> 6) & 7;
	int rc = src & 7;
{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(m68k_dreg (regs, rc)));
{	int flgs = ((uae_s32)(m68k_dreg (regs, rc))) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(m68k_dreg (regs, rc))) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG ()) {
		x_put_long (dsta, (m68k_dreg (regs, ru)));
	}else{
		x_put_long (dsta, dst);
		m68k_dreg(regs, rc) = dst;
}}}}}}}}	m68k_incpci (8);
l_240302: ;
return;
}

#endif
/* CAS2.L #<data>.L */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_0efc_24)(uae_u32 opcode)
{
	OpcodeFamily = 85;
{{	uae_s32 extra;
	extra = get_ilong_cache_040 (2);
	uae_u32 rn1 = regs.regs[(extra >> 28) & 15];
	uae_u32 rn2 = regs.regs[(extra >> 12) & 15];
	uae_u32 dst1 = x_get_long (rn1), dst2 = x_get_long (rn2);
{uae_u32 newv = ((uae_u32)(dst1)) - ((uae_u32)(m68k_dreg (regs, (extra >> 16) & 7)));
{	int flgs = ((uae_s32)(m68k_dreg (regs, (extra >> 16) & 7))) < 0;
	int flgo = ((uae_s32)(dst1)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(m68k_dreg (regs, (extra >> 16) & 7))) > ((uae_u32)(dst1)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG ()) {
{uae_u32 newv = ((uae_u32)(dst2)) - ((uae_u32)(m68k_dreg (regs, extra & 7)));
{	int flgs = ((uae_s32)(m68k_dreg (regs, extra & 7))) < 0;
	int flgo = ((uae_s32)(dst2)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(m68k_dreg (regs, extra & 7))) > ((uae_u32)(dst2)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG ()) {
	x_put_long (rn1, m68k_dreg (regs, (extra >> 22) & 7));
	x_put_long (rn2, m68k_dreg (regs, (extra >> 6) & 7));
	}}
}}}}	if (! GET_ZFLG ()) {
	m68k_dreg (regs, (extra >> 0) & 7) = dst2;
	m68k_dreg (regs, (extra >> 16) & 7) = dst1;
	}
}}	m68k_incpci (6);
return;
}

#endif
/* MOVE.B Dn,Dn */
void REGPARAM2 CPUFUNC(op_1000_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
	m68k_incpci (2);
}}}return;
}

/* MOVE.B (An),Dn */
void REGPARAM2 CPUFUNC(op_1010_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s8 src = x_get_byte (srca);
{	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
	m68k_incpci (2);
}}}}return;
}

/* MOVE.B (An)+,Dn */
void REGPARAM2 CPUFUNC(op_1018_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s8 src = x_get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
	m68k_incpci (2);
}}}}return;
}

/* MOVE.B -(An),Dn */
void REGPARAM2 CPUFUNC(op_1020_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = x_get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
	m68k_incpci (2);
}}}}return;
}

/* MOVE.B (d16,An),Dn */
void REGPARAM2 CPUFUNC(op_1028_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.B (d8,An,Xn),Dn */
void REGPARAM2 CPUFUNC(op_1030_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s8 src = x_get_byte (srca);
{	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}}}return;
}

/* MOVE.B (xxx).W,Dn */
void REGPARAM2 CPUFUNC(op_1038_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.B (xxx).L,Dn */
void REGPARAM2 CPUFUNC(op_1039_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
	m68k_incpci (6);
}}}}return;
}

/* MOVE.B (d16,PC),Dn */
void REGPARAM2 CPUFUNC(op_103a_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.B (d8,PC,Xn),Dn */
void REGPARAM2 CPUFUNC(op_103b_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s8 src = x_get_byte (srca);
{	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}}}return;
}

/* MOVE.B #<data>.B,Dn */
void REGPARAM2 CPUFUNC(op_103c_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
	m68k_incpci (4);
}}}return;
}

/* MOVE.B Dn,(An) */
void REGPARAM2 CPUFUNC(op_1080_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (2);
}}}return;
}

/* MOVE.B (An),(An) */
void REGPARAM2 CPUFUNC(op_1090_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (2);
}}}}return;
}

/* MOVE.B (An)+,(An) */
void REGPARAM2 CPUFUNC(op_1098_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s8 src = x_get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (2);
}}}}return;
}

/* MOVE.B -(An),(An) */
void REGPARAM2 CPUFUNC(op_10a0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = x_get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (2);
}}}}return;
}

/* MOVE.B (d16,An),(An) */
void REGPARAM2 CPUFUNC(op_10a8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.B (d8,An,Xn),(An) */
void REGPARAM2 CPUFUNC(op_10b0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}}return;
}

/* MOVE.B (xxx).W,(An) */
void REGPARAM2 CPUFUNC(op_10b8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.B (xxx).L,(An) */
void REGPARAM2 CPUFUNC(op_10b9_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (6);
}}}}return;
}

/* MOVE.B (d16,PC),(An) */
void REGPARAM2 CPUFUNC(op_10ba_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.B (d8,PC,Xn),(An) */
void REGPARAM2 CPUFUNC(op_10bb_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}}return;
}

/* MOVE.B #<data>.B,(An) */
void REGPARAM2 CPUFUNC(op_10bc_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (4);
}}}return;
}

/* MOVE.B Dn,(An)+ */
void REGPARAM2 CPUFUNC(op_10c0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (2);
}}}return;
}

/* MOVE.B (An),(An)+ */
void REGPARAM2 CPUFUNC(op_10d0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (2);
}}}}return;
}

/* MOVE.B (An)+,(An)+ */
void REGPARAM2 CPUFUNC(op_10d8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s8 src = x_get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (2);
}}}}return;
}

/* MOVE.B -(An),(An)+ */
void REGPARAM2 CPUFUNC(op_10e0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = x_get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (2);
}}}}return;
}

/* MOVE.B (d16,An),(An)+ */
void REGPARAM2 CPUFUNC(op_10e8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.B (d8,An,Xn),(An)+ */
void REGPARAM2 CPUFUNC(op_10f0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}}return;
}

/* MOVE.B (xxx).W,(An)+ */
void REGPARAM2 CPUFUNC(op_10f8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.B (xxx).L,(An)+ */
void REGPARAM2 CPUFUNC(op_10f9_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (6);
}}}}return;
}

/* MOVE.B (d16,PC),(An)+ */
void REGPARAM2 CPUFUNC(op_10fa_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.B (d8,PC,Xn),(An)+ */
void REGPARAM2 CPUFUNC(op_10fb_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}}return;
}

/* MOVE.B #<data>.B,(An)+ */
void REGPARAM2 CPUFUNC(op_10fc_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (4);
}}}return;
}

/* MOVE.B Dn,-(An) */
void REGPARAM2 CPUFUNC(op_1100_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (2);
}}}return;
}

/* MOVE.B (An),-(An) */
void REGPARAM2 CPUFUNC(op_1110_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (2);
}}}}return;
}

/* MOVE.B (An)+,-(An) */
void REGPARAM2 CPUFUNC(op_1118_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s8 src = x_get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (2);
}}}}return;
}

/* MOVE.B -(An),-(An) */
void REGPARAM2 CPUFUNC(op_1120_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = x_get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (2);
}}}}return;
}

/* MOVE.B (d16,An),-(An) */
void REGPARAM2 CPUFUNC(op_1128_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.B (d8,An,Xn),-(An) */
void REGPARAM2 CPUFUNC(op_1130_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}}return;
}

/* MOVE.B (xxx).W,-(An) */
void REGPARAM2 CPUFUNC(op_1138_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.B (xxx).L,-(An) */
void REGPARAM2 CPUFUNC(op_1139_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (6);
}}}}return;
}

/* MOVE.B (d16,PC),-(An) */
void REGPARAM2 CPUFUNC(op_113a_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.B (d8,PC,Xn),-(An) */
void REGPARAM2 CPUFUNC(op_113b_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}}return;
}

/* MOVE.B #<data>.B,-(An) */
void REGPARAM2 CPUFUNC(op_113c_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (4);
}}}return;
}

/* MOVE.B Dn,(d16,An) */
void REGPARAM2 CPUFUNC(op_1140_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (4);
}}}return;
}

/* MOVE.B (An),(d16,An) */
void REGPARAM2 CPUFUNC(op_1150_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.B (An)+,(d16,An) */
void REGPARAM2 CPUFUNC(op_1158_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s8 src = x_get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.B -(An),(d16,An) */
void REGPARAM2 CPUFUNC(op_1160_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = x_get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.B (d16,An),(d16,An) */
void REGPARAM2 CPUFUNC(op_1168_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (6);
}}}}return;
}

/* MOVE.B (d8,An,Xn),(d16,An) */
void REGPARAM2 CPUFUNC(op_1170_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (2);
}}}}}return;
}

/* MOVE.B (xxx).W,(d16,An) */
void REGPARAM2 CPUFUNC(op_1178_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (6);
}}}}return;
}

/* MOVE.B (xxx).L,(d16,An) */
void REGPARAM2 CPUFUNC(op_1179_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (6);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (8);
}}}}return;
}

/* MOVE.B (d16,PC),(d16,An) */
void REGPARAM2 CPUFUNC(op_117a_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (6);
}}}}return;
}

/* MOVE.B (d8,PC,Xn),(d16,An) */
void REGPARAM2 CPUFUNC(op_117b_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (2);
}}}}}return;
}

/* MOVE.B #<data>.B,(d16,An) */
void REGPARAM2 CPUFUNC(op_117c_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (6);
}}}return;
}

/* MOVE.B Dn,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_1180_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	m68k_incpci (2);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}return;
}

/* MOVE.B (An),(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_1190_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
	m68k_incpci (2);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}}return;
}

/* MOVE.B (An)+,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_1198_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s8 src = x_get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{	uaecptr dsta;
	m68k_incpci (2);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}}return;
}

/* MOVE.B -(An),(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_11a0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = x_get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta;
	m68k_incpci (2);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}}return;
}

/* MOVE.B (d16,An),(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_11a8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
	m68k_incpci (4);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}}return;
}

/* MOVE.B (d8,An,Xn),(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_11b0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 1);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}}}return;
}

/* MOVE.B (xxx).W,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_11b8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
	m68k_incpci (4);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}}return;
}

/* MOVE.B (xxx).L,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_11b9_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
	m68k_incpci (6);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}}return;
}

/* MOVE.B (d16,PC),(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_11ba_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
	m68k_incpci (4);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}}return;
}

/* MOVE.B (d8,PC,Xn),(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_11bb_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 1);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}}}return;
}

/* MOVE.B #<data>.B,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_11bc_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	m68k_incpci (4);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}return;
}

/* MOVE.B Dn,(xxx).W */
void REGPARAM2 CPUFUNC(op_11c0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 30;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (4);
}}}return;
}

/* MOVE.B (An),(xxx).W */
void REGPARAM2 CPUFUNC(op_11d0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.B (An)+,(xxx).W */
void REGPARAM2 CPUFUNC(op_11d8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s8 src = x_get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.B -(An),(xxx).W */
void REGPARAM2 CPUFUNC(op_11e0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = x_get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.B (d16,An),(xxx).W */
void REGPARAM2 CPUFUNC(op_11e8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (4);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (6);
}}}}return;
}

/* MOVE.B (d8,An,Xn),(xxx).W */
void REGPARAM2 CPUFUNC(op_11f0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 30;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (2);
}}}}}return;
}

/* MOVE.B (xxx).W,(xxx).W */
void REGPARAM2 CPUFUNC(op_11f8_24)(uae_u32 opcode)
{
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (4);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (6);
}}}}return;
}

/* MOVE.B (xxx).L,(xxx).W */
void REGPARAM2 CPUFUNC(op_11f9_24)(uae_u32 opcode)
{
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (6);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (8);
}}}}return;
}

/* MOVE.B (d16,PC),(xxx).W */
void REGPARAM2 CPUFUNC(op_11fa_24)(uae_u32 opcode)
{
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (4);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (6);
}}}}return;
}

/* MOVE.B (d8,PC,Xn),(xxx).W */
void REGPARAM2 CPUFUNC(op_11fb_24)(uae_u32 opcode)
{
	OpcodeFamily = 30;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (2);
}}}}}return;
}

/* MOVE.B #<data>.B,(xxx).W */
void REGPARAM2 CPUFUNC(op_11fc_24)(uae_u32 opcode)
{
	OpcodeFamily = 30;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (4);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (6);
}}}return;
}

/* MOVE.B Dn,(xxx).L */
void REGPARAM2 CPUFUNC(op_13c0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 30;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (6);
}}}return;
}

/* MOVE.B (An),(xxx).L */
void REGPARAM2 CPUFUNC(op_13d0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (6);
}}}}return;
}

/* MOVE.B (An)+,(xxx).L */
void REGPARAM2 CPUFUNC(op_13d8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s8 src = x_get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (6);
}}}}return;
}

/* MOVE.B -(An),(xxx).L */
void REGPARAM2 CPUFUNC(op_13e0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = x_get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (6);
}}}}return;
}

/* MOVE.B (d16,An),(xxx).L */
void REGPARAM2 CPUFUNC(op_13e8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (4);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (8);
}}}}return;
}

/* MOVE.B (d8,An,Xn),(xxx).L */
void REGPARAM2 CPUFUNC(op_13f0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 30;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (4);
}}}}}return;
}

/* MOVE.B (xxx).W,(xxx).L */
void REGPARAM2 CPUFUNC(op_13f8_24)(uae_u32 opcode)
{
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (4);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (8);
}}}}return;
}

/* MOVE.B (xxx).L,(xxx).L */
void REGPARAM2 CPUFUNC(op_13f9_24)(uae_u32 opcode)
{
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (6);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (10);
}}}}return;
}

/* MOVE.B (d16,PC),(xxx).L */
void REGPARAM2 CPUFUNC(op_13fa_24)(uae_u32 opcode)
{
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (4);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (8);
}}}}return;
}

/* MOVE.B (d8,PC,Xn),(xxx).L */
void REGPARAM2 CPUFUNC(op_13fb_24)(uae_u32 opcode)
{
	OpcodeFamily = 30;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s8 src = x_get_byte (srca);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (4);
}}}}}return;
}

/* MOVE.B #<data>.B,(xxx).L */
void REGPARAM2 CPUFUNC(op_13fc_24)(uae_u32 opcode)
{
	OpcodeFamily = 30;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (4);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
	m68k_incpci (8);
}}}return;
}

/* MOVE.L Dn,Dn */
void REGPARAM2 CPUFUNC(op_2000_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	m68k_dreg (regs, dstreg) = (src);
	m68k_incpci (2);
}}}return;
}

/* MOVE.L An,Dn */
void REGPARAM2 CPUFUNC(op_2008_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s32 src = m68k_areg (regs, srcreg);
{	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	m68k_dreg (regs, dstreg) = (src);
	m68k_incpci (2);
}}}return;
}

/* MOVE.L (An),Dn */
void REGPARAM2 CPUFUNC(op_2010_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s32 src = x_get_long (srca);
{	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	m68k_dreg (regs, dstreg) = (src);
	m68k_incpci (2);
}}}}return;
}

/* MOVE.L (An)+,Dn */
void REGPARAM2 CPUFUNC(op_2018_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, srcreg) += 4;
{	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	m68k_dreg (regs, dstreg) = (src);
	m68k_incpci (2);
}}}}return;
}

/* MOVE.L -(An),Dn */
void REGPARAM2 CPUFUNC(op_2020_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, srcreg) = srca;
{	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	m68k_dreg (regs, dstreg) = (src);
	m68k_incpci (2);
}}}}return;
}

/* MOVE.L (d16,An),Dn */
void REGPARAM2 CPUFUNC(op_2028_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	m68k_dreg (regs, dstreg) = (src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.L (d8,An,Xn),Dn */
void REGPARAM2 CPUFUNC(op_2030_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s32 src = x_get_long (srca);
{	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	m68k_dreg (regs, dstreg) = (src);
}}}}}return;
}

/* MOVE.L (xxx).W,Dn */
void REGPARAM2 CPUFUNC(op_2038_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	m68k_dreg (regs, dstreg) = (src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.L (xxx).L,Dn */
void REGPARAM2 CPUFUNC(op_2039_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	m68k_dreg (regs, dstreg) = (src);
	m68k_incpci (6);
}}}}return;
}

/* MOVE.L (d16,PC),Dn */
void REGPARAM2 CPUFUNC(op_203a_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	m68k_dreg (regs, dstreg) = (src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.L (d8,PC,Xn),Dn */
void REGPARAM2 CPUFUNC(op_203b_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s32 src = x_get_long (srca);
{	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	m68k_dreg (regs, dstreg) = (src);
}}}}}return;
}

/* MOVE.L #<data>.L,Dn */
void REGPARAM2 CPUFUNC(op_203c_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	m68k_dreg (regs, dstreg) = (src);
	m68k_incpci (6);
}}}return;
}

/* MOVEA.L Dn,An */
void REGPARAM2 CPUFUNC(op_2040_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 31;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	m68k_areg (regs, dstreg) = (src);
	m68k_incpci (2);
}}}return;
}

/* MOVEA.L An,An */
void REGPARAM2 CPUFUNC(op_2048_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 31;
{{	uae_s32 src = m68k_areg (regs, srcreg);
{	m68k_areg (regs, dstreg) = (src);
	m68k_incpci (2);
}}}return;
}

/* MOVEA.L (An),An */
void REGPARAM2 CPUFUNC(op_2050_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 31;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s32 src = x_get_long (srca);
{	m68k_areg (regs, dstreg) = (src);
	m68k_incpci (2);
}}}}return;
}

/* MOVEA.L (An)+,An */
void REGPARAM2 CPUFUNC(op_2058_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 31;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, srcreg) += 4;
{	m68k_areg (regs, dstreg) = (src);
	m68k_incpci (2);
}}}}return;
}

/* MOVEA.L -(An),An */
void REGPARAM2 CPUFUNC(op_2060_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 31;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, srcreg) = srca;
{	m68k_areg (regs, dstreg) = (src);
	m68k_incpci (2);
}}}}return;
}

/* MOVEA.L (d16,An),An */
void REGPARAM2 CPUFUNC(op_2068_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 31;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	m68k_areg (regs, dstreg) = (src);
	m68k_incpci (4);
}}}}return;
}

/* MOVEA.L (d8,An,Xn),An */
void REGPARAM2 CPUFUNC(op_2070_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 31;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s32 src = x_get_long (srca);
{	m68k_areg (regs, dstreg) = (src);
}}}}}return;
}

/* MOVEA.L (xxx).W,An */
void REGPARAM2 CPUFUNC(op_2078_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 31;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	m68k_areg (regs, dstreg) = (src);
	m68k_incpci (4);
}}}}return;
}

/* MOVEA.L (xxx).L,An */
void REGPARAM2 CPUFUNC(op_2079_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 31;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	m68k_areg (regs, dstreg) = (src);
	m68k_incpci (6);
}}}}return;
}

/* MOVEA.L (d16,PC),An */
void REGPARAM2 CPUFUNC(op_207a_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 31;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	m68k_areg (regs, dstreg) = (src);
	m68k_incpci (4);
}}}}return;
}

/* MOVEA.L (d8,PC,Xn),An */
void REGPARAM2 CPUFUNC(op_207b_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 31;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s32 src = x_get_long (srca);
{	m68k_areg (regs, dstreg) = (src);
}}}}}return;
}

/* MOVEA.L #<data>.L,An */
void REGPARAM2 CPUFUNC(op_207c_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 31;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	m68k_areg (regs, dstreg) = (src);
	m68k_incpci (6);
}}}return;
}

/* MOVE.L Dn,(An) */
void REGPARAM2 CPUFUNC(op_2080_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (2);
}}}return;
}

/* MOVE.L An,(An) */
void REGPARAM2 CPUFUNC(op_2088_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s32 src = m68k_areg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (2);
}}}return;
}

/* MOVE.L (An),(An) */
void REGPARAM2 CPUFUNC(op_2090_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (2);
}}}}return;
}

/* MOVE.L (An)+,(An) */
void REGPARAM2 CPUFUNC(op_2098_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, srcreg) += 4;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (2);
}}}}return;
}

/* MOVE.L -(An),(An) */
void REGPARAM2 CPUFUNC(op_20a0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (2);
}}}}return;
}

/* MOVE.L (d16,An),(An) */
void REGPARAM2 CPUFUNC(op_20a8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.L (d8,An,Xn),(An) */
void REGPARAM2 CPUFUNC(op_20b0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}}return;
}

/* MOVE.L (xxx).W,(An) */
void REGPARAM2 CPUFUNC(op_20b8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.L (xxx).L,(An) */
void REGPARAM2 CPUFUNC(op_20b9_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (6);
}}}}return;
}

/* MOVE.L (d16,PC),(An) */
void REGPARAM2 CPUFUNC(op_20ba_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.L (d8,PC,Xn),(An) */
void REGPARAM2 CPUFUNC(op_20bb_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}}return;
}

/* MOVE.L #<data>.L,(An) */
void REGPARAM2 CPUFUNC(op_20bc_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (6);
}}}return;
}

/* MOVE.L Dn,(An)+ */
void REGPARAM2 CPUFUNC(op_20c0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += 4;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (2);
}}}return;
}

/* MOVE.L An,(An)+ */
void REGPARAM2 CPUFUNC(op_20c8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s32 src = m68k_areg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += 4;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (2);
}}}return;
}

/* MOVE.L (An),(An)+ */
void REGPARAM2 CPUFUNC(op_20d0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += 4;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (2);
}}}}return;
}

/* MOVE.L (An)+,(An)+ */
void REGPARAM2 CPUFUNC(op_20d8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, srcreg) += 4;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += 4;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (2);
}}}}return;
}

/* MOVE.L -(An),(An)+ */
void REGPARAM2 CPUFUNC(op_20e0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += 4;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (2);
}}}}return;
}

/* MOVE.L (d16,An),(An)+ */
void REGPARAM2 CPUFUNC(op_20e8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += 4;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.L (d8,An,Xn),(An)+ */
void REGPARAM2 CPUFUNC(op_20f0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += 4;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}}return;
}

/* MOVE.L (xxx).W,(An)+ */
void REGPARAM2 CPUFUNC(op_20f8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += 4;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.L (xxx).L,(An)+ */
void REGPARAM2 CPUFUNC(op_20f9_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += 4;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (6);
}}}}return;
}

/* MOVE.L (d16,PC),(An)+ */
void REGPARAM2 CPUFUNC(op_20fa_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += 4;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.L (d8,PC,Xn),(An)+ */
void REGPARAM2 CPUFUNC(op_20fb_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += 4;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}}return;
}

/* MOVE.L #<data>.L,(An)+ */
void REGPARAM2 CPUFUNC(op_20fc_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += 4;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (6);
}}}return;
}

/* MOVE.L Dn,-(An) */
void REGPARAM2 CPUFUNC(op_2100_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (2);
}}}return;
}

/* MOVE.L An,-(An) */
void REGPARAM2 CPUFUNC(op_2108_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s32 src = m68k_areg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (2);
}}}return;
}

/* MOVE.L (An),-(An) */
void REGPARAM2 CPUFUNC(op_2110_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (2);
}}}}return;
}

/* MOVE.L (An)+,-(An) */
void REGPARAM2 CPUFUNC(op_2118_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, srcreg) += 4;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (2);
}}}}return;
}

/* MOVE.L -(An),-(An) */
void REGPARAM2 CPUFUNC(op_2120_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (2);
}}}}return;
}

/* MOVE.L (d16,An),-(An) */
void REGPARAM2 CPUFUNC(op_2128_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.L (d8,An,Xn),-(An) */
void REGPARAM2 CPUFUNC(op_2130_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}}return;
}

/* MOVE.L (xxx).W,-(An) */
void REGPARAM2 CPUFUNC(op_2138_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.L (xxx).L,-(An) */
void REGPARAM2 CPUFUNC(op_2139_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (6);
}}}}return;
}

/* MOVE.L (d16,PC),-(An) */
void REGPARAM2 CPUFUNC(op_213a_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.L (d8,PC,Xn),-(An) */
void REGPARAM2 CPUFUNC(op_213b_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}}return;
}

/* MOVE.L #<data>.L,-(An) */
void REGPARAM2 CPUFUNC(op_213c_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (6);
}}}return;
}

/* MOVE.L Dn,(d16,An) */
void REGPARAM2 CPUFUNC(op_2140_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (4);
}}}return;
}

/* MOVE.L An,(d16,An) */
void REGPARAM2 CPUFUNC(op_2148_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s32 src = m68k_areg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (4);
}}}return;
}

/* MOVE.L (An),(d16,An) */
void REGPARAM2 CPUFUNC(op_2150_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.L (An)+,(d16,An) */
void REGPARAM2 CPUFUNC(op_2158_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, srcreg) += 4;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.L -(An),(d16,An) */
void REGPARAM2 CPUFUNC(op_2160_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.L (d16,An),(d16,An) */
void REGPARAM2 CPUFUNC(op_2168_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (6);
}}}}return;
}

/* MOVE.L (d8,An,Xn),(d16,An) */
void REGPARAM2 CPUFUNC(op_2170_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (2);
}}}}}return;
}

/* MOVE.L (xxx).W,(d16,An) */
void REGPARAM2 CPUFUNC(op_2178_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (6);
}}}}return;
}

/* MOVE.L (xxx).L,(d16,An) */
void REGPARAM2 CPUFUNC(op_2179_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (6);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (8);
}}}}return;
}

/* MOVE.L (d16,PC),(d16,An) */
void REGPARAM2 CPUFUNC(op_217a_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (6);
}}}}return;
}

/* MOVE.L (d8,PC,Xn),(d16,An) */
void REGPARAM2 CPUFUNC(op_217b_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (2);
}}}}}return;
}

/* MOVE.L #<data>.L,(d16,An) */
void REGPARAM2 CPUFUNC(op_217c_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (6);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (8);
}}}return;
}

/* MOVE.L Dn,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_2180_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	m68k_incpci (2);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}return;
}

/* MOVE.L An,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_2188_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s32 src = m68k_areg (regs, srcreg);
{	uaecptr dsta;
	m68k_incpci (2);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}return;
}

/* MOVE.L (An),(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_2190_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
	m68k_incpci (2);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}}return;
}

/* MOVE.L (An)+,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_2198_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, srcreg) += 4;
{	uaecptr dsta;
	m68k_incpci (2);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}}return;
}

#endif

#ifdef PART_3
/* MOVE.L -(An),(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_21a0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta;
	m68k_incpci (2);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}}return;
}

/* MOVE.L (d16,An),(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_21a8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
	m68k_incpci (4);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}}return;
}

/* MOVE.L (d8,An,Xn),(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_21b0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 1);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}}}return;
}

/* MOVE.L (xxx).W,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_21b8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
	m68k_incpci (4);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}}return;
}

/* MOVE.L (xxx).L,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_21b9_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
	m68k_incpci (6);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}}return;
}

/* MOVE.L (d16,PC),(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_21ba_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
	m68k_incpci (4);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}}return;
}

/* MOVE.L (d8,PC,Xn),(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_21bb_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 1);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}}}return;
}

/* MOVE.L #<data>.L,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_21bc_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	m68k_incpci (6);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}return;
}

/* MOVE.L Dn,(xxx).W */
void REGPARAM2 CPUFUNC(op_21c0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 30;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (4);
}}}return;
}

/* MOVE.L An,(xxx).W */
void REGPARAM2 CPUFUNC(op_21c8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 30;
{{	uae_s32 src = m68k_areg (regs, srcreg);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (4);
}}}return;
}

/* MOVE.L (An),(xxx).W */
void REGPARAM2 CPUFUNC(op_21d0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.L (An)+,(xxx).W */
void REGPARAM2 CPUFUNC(op_21d8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, srcreg) += 4;
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.L -(An),(xxx).W */
void REGPARAM2 CPUFUNC(op_21e0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.L (d16,An),(xxx).W */
void REGPARAM2 CPUFUNC(op_21e8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (4);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (6);
}}}}return;
}

/* MOVE.L (d8,An,Xn),(xxx).W */
void REGPARAM2 CPUFUNC(op_21f0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 30;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (2);
}}}}}return;
}

/* MOVE.L (xxx).W,(xxx).W */
void REGPARAM2 CPUFUNC(op_21f8_24)(uae_u32 opcode)
{
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (4);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (6);
}}}}return;
}

/* MOVE.L (xxx).L,(xxx).W */
void REGPARAM2 CPUFUNC(op_21f9_24)(uae_u32 opcode)
{
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (6);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (8);
}}}}return;
}

/* MOVE.L (d16,PC),(xxx).W */
void REGPARAM2 CPUFUNC(op_21fa_24)(uae_u32 opcode)
{
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (4);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (6);
}}}}return;
}

/* MOVE.L (d8,PC,Xn),(xxx).W */
void REGPARAM2 CPUFUNC(op_21fb_24)(uae_u32 opcode)
{
	OpcodeFamily = 30;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (2);
}}}}}return;
}

/* MOVE.L #<data>.L,(xxx).W */
void REGPARAM2 CPUFUNC(op_21fc_24)(uae_u32 opcode)
{
	OpcodeFamily = 30;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (6);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (8);
}}}return;
}

/* MOVE.L Dn,(xxx).L */
void REGPARAM2 CPUFUNC(op_23c0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 30;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (6);
}}}return;
}

/* MOVE.L An,(xxx).L */
void REGPARAM2 CPUFUNC(op_23c8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 30;
{{	uae_s32 src = m68k_areg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (6);
}}}return;
}

/* MOVE.L (An),(xxx).L */
void REGPARAM2 CPUFUNC(op_23d0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (6);
}}}}return;
}

/* MOVE.L (An)+,(xxx).L */
void REGPARAM2 CPUFUNC(op_23d8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, srcreg) += 4;
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (6);
}}}}return;
}

/* MOVE.L -(An),(xxx).L */
void REGPARAM2 CPUFUNC(op_23e0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (6);
}}}}return;
}

/* MOVE.L (d16,An),(xxx).L */
void REGPARAM2 CPUFUNC(op_23e8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (4);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (8);
}}}}return;
}

/* MOVE.L (d8,An,Xn),(xxx).L */
void REGPARAM2 CPUFUNC(op_23f0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 30;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (4);
}}}}}return;
}

/* MOVE.L (xxx).W,(xxx).L */
void REGPARAM2 CPUFUNC(op_23f8_24)(uae_u32 opcode)
{
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (4);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (8);
}}}}return;
}

/* MOVE.L (xxx).L,(xxx).L */
void REGPARAM2 CPUFUNC(op_23f9_24)(uae_u32 opcode)
{
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (6);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (10);
}}}}return;
}

/* MOVE.L (d16,PC),(xxx).L */
void REGPARAM2 CPUFUNC(op_23fa_24)(uae_u32 opcode)
{
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (4);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (8);
}}}}return;
}

/* MOVE.L (d8,PC,Xn),(xxx).L */
void REGPARAM2 CPUFUNC(op_23fb_24)(uae_u32 opcode)
{
	OpcodeFamily = 30;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s32 src = x_get_long (srca);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (4);
}}}}}return;
}

/* MOVE.L #<data>.L,(xxx).L */
void REGPARAM2 CPUFUNC(op_23fc_24)(uae_u32 opcode)
{
	OpcodeFamily = 30;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (6);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
	m68k_incpci (10);
}}}return;
}

/* MOVE.W Dn,Dn */
void REGPARAM2 CPUFUNC(op_3000_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
	m68k_incpci (2);
}}}return;
}

/* MOVE.W An,Dn */
void REGPARAM2 CPUFUNC(op_3008_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s16 src = m68k_areg (regs, srcreg);
{	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
	m68k_incpci (2);
}}}return;
}

/* MOVE.W (An),Dn */
void REGPARAM2 CPUFUNC(op_3010_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
{	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
	m68k_incpci (2);
}}}}return;
}

/* MOVE.W (An)+,Dn */
void REGPARAM2 CPUFUNC(op_3018_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
	m68k_incpci (2);
}}}}return;
}

/* MOVE.W -(An),Dn */
void REGPARAM2 CPUFUNC(op_3020_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
	m68k_incpci (2);
}}}}return;
}

/* MOVE.W (d16,An),Dn */
void REGPARAM2 CPUFUNC(op_3028_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.W (d8,An,Xn),Dn */
void REGPARAM2 CPUFUNC(op_3030_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s16 src = x_get_word (srca);
{	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}}}return;
}

/* MOVE.W (xxx).W,Dn */
void REGPARAM2 CPUFUNC(op_3038_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.W (xxx).L,Dn */
void REGPARAM2 CPUFUNC(op_3039_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
	m68k_incpci (6);
}}}}return;
}

/* MOVE.W (d16,PC),Dn */
void REGPARAM2 CPUFUNC(op_303a_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.W (d8,PC,Xn),Dn */
void REGPARAM2 CPUFUNC(op_303b_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s16 src = x_get_word (srca);
{	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}}}return;
}

/* MOVE.W #<data>.W,Dn */
void REGPARAM2 CPUFUNC(op_303c_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s16 src = get_iword_cache_040 (2);
{	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
	m68k_incpci (4);
}}}return;
}

/* MOVEA.W Dn,An */
void REGPARAM2 CPUFUNC(op_3040_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 31;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	src = (uae_s32)(uae_s16)src;
	m68k_areg (regs, dstreg) = (uae_s32)(uae_s16)(src);
	m68k_incpci (2);
}}}return;
}

/* MOVEA.W An,An */
void REGPARAM2 CPUFUNC(op_3048_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 31;
{{	uae_s16 src = m68k_areg (regs, srcreg);
{	src = (uae_s32)(uae_s16)src;
	m68k_areg (regs, dstreg) = (uae_s32)(uae_s16)(src);
	m68k_incpci (2);
}}}return;
}

/* MOVEA.W (An),An */
void REGPARAM2 CPUFUNC(op_3050_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 31;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
{	src = (uae_s32)(uae_s16)src;
	m68k_areg (regs, dstreg) = (uae_s32)(uae_s16)(src);
	m68k_incpci (2);
}}}}return;
}

/* MOVEA.W (An)+,An */
void REGPARAM2 CPUFUNC(op_3058_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 31;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	src = (uae_s32)(uae_s16)src;
	m68k_areg (regs, dstreg) = (uae_s32)(uae_s16)(src);
	m68k_incpci (2);
}}}}return;
}

/* MOVEA.W -(An),An */
void REGPARAM2 CPUFUNC(op_3060_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 31;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	src = (uae_s32)(uae_s16)src;
	m68k_areg (regs, dstreg) = (uae_s32)(uae_s16)(src);
	m68k_incpci (2);
}}}}return;
}

/* MOVEA.W (d16,An),An */
void REGPARAM2 CPUFUNC(op_3068_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 31;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	src = (uae_s32)(uae_s16)src;
	m68k_areg (regs, dstreg) = (uae_s32)(uae_s16)(src);
	m68k_incpci (4);
}}}}return;
}

/* MOVEA.W (d8,An,Xn),An */
void REGPARAM2 CPUFUNC(op_3070_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 31;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s16 src = x_get_word (srca);
{	src = (uae_s32)(uae_s16)src;
	m68k_areg (regs, dstreg) = (uae_s32)(uae_s16)(src);
}}}}}return;
}

/* MOVEA.W (xxx).W,An */
void REGPARAM2 CPUFUNC(op_3078_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 31;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	src = (uae_s32)(uae_s16)src;
	m68k_areg (regs, dstreg) = (uae_s32)(uae_s16)(src);
	m68k_incpci (4);
}}}}return;
}

/* MOVEA.W (xxx).L,An */
void REGPARAM2 CPUFUNC(op_3079_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 31;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	src = (uae_s32)(uae_s16)src;
	m68k_areg (regs, dstreg) = (uae_s32)(uae_s16)(src);
	m68k_incpci (6);
}}}}return;
}

/* MOVEA.W (d16,PC),An */
void REGPARAM2 CPUFUNC(op_307a_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 31;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	src = (uae_s32)(uae_s16)src;
	m68k_areg (regs, dstreg) = (uae_s32)(uae_s16)(src);
	m68k_incpci (4);
}}}}return;
}

/* MOVEA.W (d8,PC,Xn),An */
void REGPARAM2 CPUFUNC(op_307b_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 31;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s16 src = x_get_word (srca);
{	src = (uae_s32)(uae_s16)src;
	m68k_areg (regs, dstreg) = (uae_s32)(uae_s16)(src);
}}}}}return;
}

/* MOVEA.W #<data>.W,An */
void REGPARAM2 CPUFUNC(op_307c_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 31;
{{	uae_s16 src = get_iword_cache_040 (2);
{	src = (uae_s32)(uae_s16)src;
	m68k_areg (regs, dstreg) = (uae_s32)(uae_s16)(src);
	m68k_incpci (4);
}}}return;
}

/* MOVE.W Dn,(An) */
void REGPARAM2 CPUFUNC(op_3080_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (2);
}}}return;
}

/* MOVE.W An,(An) */
void REGPARAM2 CPUFUNC(op_3088_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s16 src = m68k_areg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (2);
}}}return;
}

/* MOVE.W (An),(An) */
void REGPARAM2 CPUFUNC(op_3090_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (2);
}}}}return;
}

/* MOVE.W (An)+,(An) */
void REGPARAM2 CPUFUNC(op_3098_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (2);
}}}}return;
}

/* MOVE.W -(An),(An) */
void REGPARAM2 CPUFUNC(op_30a0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (2);
}}}}return;
}

/* MOVE.W (d16,An),(An) */
void REGPARAM2 CPUFUNC(op_30a8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.W (d8,An,Xn),(An) */
void REGPARAM2 CPUFUNC(op_30b0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}}return;
}

/* MOVE.W (xxx).W,(An) */
void REGPARAM2 CPUFUNC(op_30b8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.W (xxx).L,(An) */
void REGPARAM2 CPUFUNC(op_30b9_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (6);
}}}}return;
}

/* MOVE.W (d16,PC),(An) */
void REGPARAM2 CPUFUNC(op_30ba_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.W (d8,PC,Xn),(An) */
void REGPARAM2 CPUFUNC(op_30bb_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}}return;
}

/* MOVE.W #<data>.W,(An) */
void REGPARAM2 CPUFUNC(op_30bc_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (4);
}}}return;
}

/* MOVE.W Dn,(An)+ */
void REGPARAM2 CPUFUNC(op_30c0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += 2;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (2);
}}}return;
}

/* MOVE.W An,(An)+ */
void REGPARAM2 CPUFUNC(op_30c8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s16 src = m68k_areg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += 2;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (2);
}}}return;
}

/* MOVE.W (An),(An)+ */
void REGPARAM2 CPUFUNC(op_30d0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += 2;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (2);
}}}}return;
}

/* MOVE.W (An)+,(An)+ */
void REGPARAM2 CPUFUNC(op_30d8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += 2;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (2);
}}}}return;
}

/* MOVE.W -(An),(An)+ */
void REGPARAM2 CPUFUNC(op_30e0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += 2;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (2);
}}}}return;
}

/* MOVE.W (d16,An),(An)+ */
void REGPARAM2 CPUFUNC(op_30e8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += 2;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.W (d8,An,Xn),(An)+ */
void REGPARAM2 CPUFUNC(op_30f0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += 2;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}}return;
}

/* MOVE.W (xxx).W,(An)+ */
void REGPARAM2 CPUFUNC(op_30f8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += 2;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.W (xxx).L,(An)+ */
void REGPARAM2 CPUFUNC(op_30f9_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += 2;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (6);
}}}}return;
}

/* MOVE.W (d16,PC),(An)+ */
void REGPARAM2 CPUFUNC(op_30fa_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += 2;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.W (d8,PC,Xn),(An)+ */
void REGPARAM2 CPUFUNC(op_30fb_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += 2;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}}return;
}

/* MOVE.W #<data>.W,(An)+ */
void REGPARAM2 CPUFUNC(op_30fc_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += 2;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (4);
}}}return;
}

/* MOVE.W Dn,-(An) */
void REGPARAM2 CPUFUNC(op_3100_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (2);
}}}return;
}

/* MOVE.W An,-(An) */
void REGPARAM2 CPUFUNC(op_3108_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s16 src = m68k_areg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (2);
}}}return;
}

/* MOVE.W (An),-(An) */
void REGPARAM2 CPUFUNC(op_3110_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (2);
}}}}return;
}

/* MOVE.W (An)+,-(An) */
void REGPARAM2 CPUFUNC(op_3118_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (2);
}}}}return;
}

/* MOVE.W -(An),-(An) */
void REGPARAM2 CPUFUNC(op_3120_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (2);
}}}}return;
}

/* MOVE.W (d16,An),-(An) */
void REGPARAM2 CPUFUNC(op_3128_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.W (d8,An,Xn),-(An) */
void REGPARAM2 CPUFUNC(op_3130_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}}return;
}

/* MOVE.W (xxx).W,-(An) */
void REGPARAM2 CPUFUNC(op_3138_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.W (xxx).L,-(An) */
void REGPARAM2 CPUFUNC(op_3139_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (6);
}}}}return;
}

/* MOVE.W (d16,PC),-(An) */
void REGPARAM2 CPUFUNC(op_313a_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.W (d8,PC,Xn),-(An) */
void REGPARAM2 CPUFUNC(op_313b_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}}return;
}

/* MOVE.W #<data>.W,-(An) */
void REGPARAM2 CPUFUNC(op_313c_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (4);
}}}return;
}

/* MOVE.W Dn,(d16,An) */
void REGPARAM2 CPUFUNC(op_3140_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (4);
}}}return;
}

/* MOVE.W An,(d16,An) */
void REGPARAM2 CPUFUNC(op_3148_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s16 src = m68k_areg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (4);
}}}return;
}

/* MOVE.W (An),(d16,An) */
void REGPARAM2 CPUFUNC(op_3150_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.W (An)+,(d16,An) */
void REGPARAM2 CPUFUNC(op_3158_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.W -(An),(d16,An) */
void REGPARAM2 CPUFUNC(op_3160_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.W (d16,An),(d16,An) */
void REGPARAM2 CPUFUNC(op_3168_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (6);
}}}}return;
}

/* MOVE.W (d8,An,Xn),(d16,An) */
void REGPARAM2 CPUFUNC(op_3170_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (2);
}}}}}return;
}

/* MOVE.W (xxx).W,(d16,An) */
void REGPARAM2 CPUFUNC(op_3178_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (6);
}}}}return;
}

/* MOVE.W (xxx).L,(d16,An) */
void REGPARAM2 CPUFUNC(op_3179_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (6);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (8);
}}}}return;
}

/* MOVE.W (d16,PC),(d16,An) */
void REGPARAM2 CPUFUNC(op_317a_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (6);
}}}}return;
}

/* MOVE.W (d8,PC,Xn),(d16,An) */
void REGPARAM2 CPUFUNC(op_317b_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (2);
}}}}}return;
}

/* MOVE.W #<data>.W,(d16,An) */
void REGPARAM2 CPUFUNC(op_317c_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (6);
}}}return;
}

/* MOVE.W Dn,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_3180_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	m68k_incpci (2);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}return;
}

/* MOVE.W An,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_3188_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s16 src = m68k_areg (regs, srcreg);
{	uaecptr dsta;
	m68k_incpci (2);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}return;
}

/* MOVE.W (An),(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_3190_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
	m68k_incpci (2);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}}return;
}

/* MOVE.W (An)+,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_3198_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	uaecptr dsta;
	m68k_incpci (2);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}}return;
}

/* MOVE.W -(An),(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_31a0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta;
	m68k_incpci (2);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}}return;
}

/* MOVE.W (d16,An),(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_31a8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
	m68k_incpci (4);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}}return;
}

/* MOVE.W (d8,An,Xn),(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_31b0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 1);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}}}return;
}

/* MOVE.W (xxx).W,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_31b8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
	m68k_incpci (4);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}}return;
}

/* MOVE.W (xxx).L,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_31b9_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
	m68k_incpci (6);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}}return;
}

/* MOVE.W (d16,PC),(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_31ba_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
	m68k_incpci (4);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}}return;
}

/* MOVE.W (d8,PC,Xn),(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_31bb_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 1);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}}}return;
}

/* MOVE.W #<data>.W,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_31bc_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	m68k_incpci (4);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}return;
}

/* MOVE.W Dn,(xxx).W */
void REGPARAM2 CPUFUNC(op_31c0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 30;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (4);
}}}return;
}

/* MOVE.W An,(xxx).W */
void REGPARAM2 CPUFUNC(op_31c8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 30;
{{	uae_s16 src = m68k_areg (regs, srcreg);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (4);
}}}return;
}

/* MOVE.W (An),(xxx).W */
void REGPARAM2 CPUFUNC(op_31d0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.W (An)+,(xxx).W */
void REGPARAM2 CPUFUNC(op_31d8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.W -(An),(xxx).W */
void REGPARAM2 CPUFUNC(op_31e0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (4);
}}}}return;
}

/* MOVE.W (d16,An),(xxx).W */
void REGPARAM2 CPUFUNC(op_31e8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (4);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (6);
}}}}return;
}

/* MOVE.W (d8,An,Xn),(xxx).W */
void REGPARAM2 CPUFUNC(op_31f0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 30;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (2);
}}}}}return;
}

/* MOVE.W (xxx).W,(xxx).W */
void REGPARAM2 CPUFUNC(op_31f8_24)(uae_u32 opcode)
{
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (4);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (6);
}}}}return;
}

/* MOVE.W (xxx).L,(xxx).W */
void REGPARAM2 CPUFUNC(op_31f9_24)(uae_u32 opcode)
{
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (6);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (8);
}}}}return;
}

/* MOVE.W (d16,PC),(xxx).W */
void REGPARAM2 CPUFUNC(op_31fa_24)(uae_u32 opcode)
{
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (4);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (6);
}}}}return;
}

/* MOVE.W (d8,PC,Xn),(xxx).W */
void REGPARAM2 CPUFUNC(op_31fb_24)(uae_u32 opcode)
{
	OpcodeFamily = 30;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (2);
}}}}}return;
}

/* MOVE.W #<data>.W,(xxx).W */
void REGPARAM2 CPUFUNC(op_31fc_24)(uae_u32 opcode)
{
	OpcodeFamily = 30;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (4);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (6);
}}}return;
}

/* MOVE.W Dn,(xxx).L */
void REGPARAM2 CPUFUNC(op_33c0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 30;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (6);
}}}return;
}

/* MOVE.W An,(xxx).L */
void REGPARAM2 CPUFUNC(op_33c8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 30;
{{	uae_s16 src = m68k_areg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (6);
}}}return;
}

/* MOVE.W (An),(xxx).L */
void REGPARAM2 CPUFUNC(op_33d0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (6);
}}}}return;
}

/* MOVE.W (An)+,(xxx).L */
void REGPARAM2 CPUFUNC(op_33d8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (6);
}}}}return;
}

/* MOVE.W -(An),(xxx).L */
void REGPARAM2 CPUFUNC(op_33e0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (6);
}}}}return;
}

/* MOVE.W (d16,An),(xxx).L */
void REGPARAM2 CPUFUNC(op_33e8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (4);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (8);
}}}}return;
}

/* MOVE.W (d8,An,Xn),(xxx).L */
void REGPARAM2 CPUFUNC(op_33f0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 30;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (4);
}}}}}return;
}

/* MOVE.W (xxx).W,(xxx).L */
void REGPARAM2 CPUFUNC(op_33f8_24)(uae_u32 opcode)
{
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (4);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (8);
}}}}return;
}

/* MOVE.W (xxx).L,(xxx).L */
void REGPARAM2 CPUFUNC(op_33f9_24)(uae_u32 opcode)
{
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (6);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (10);
}}}}return;
}

/* MOVE.W (d16,PC),(xxx).L */
void REGPARAM2 CPUFUNC(op_33fa_24)(uae_u32 opcode)
{
	OpcodeFamily = 30;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (4);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (8);
}}}}return;
}

/* MOVE.W (d8,PC,Xn),(xxx).L */
void REGPARAM2 CPUFUNC(op_33fb_24)(uae_u32 opcode)
{
	OpcodeFamily = 30;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s16 src = x_get_word (srca);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (4);
}}}}}return;
}

/* MOVE.W #<data>.W,(xxx).L */
void REGPARAM2 CPUFUNC(op_33fc_24)(uae_u32 opcode)
{
	OpcodeFamily = 30;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (4);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
	m68k_incpci (8);
}}}return;
}

/* NEGX.B Dn */
void REGPARAM2 CPUFUNC(op_4000_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 16;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uae_u32 newv = 0 - src - (GET_XFLG () ? 1 : 0);
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(0)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s8)(newv)) == 0));
	SET_NFLG (((uae_s8)(newv)) < 0);
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xff) | ((newv) & 0xff);
}}}}	m68k_incpci (2);
return;
}

/* NEGX.B (An) */
void REGPARAM2 CPUFUNC(op_4010_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 16;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s8 src = x_get_byte (srca);
{	uae_u32 newv = 0 - src - (GET_XFLG () ? 1 : 0);
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(0)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s8)(newv)) == 0));
	SET_NFLG (((uae_s8)(newv)) < 0);
	x_put_byte (srca, newv);
}}}}}	m68k_incpci (2);
return;
}

/* NEGX.B (An)+ */
void REGPARAM2 CPUFUNC(op_4018_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 16;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s8 src = x_get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{	uae_u32 newv = 0 - src - (GET_XFLG () ? 1 : 0);
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(0)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s8)(newv)) == 0));
	SET_NFLG (((uae_s8)(newv)) < 0);
	x_put_byte (srca, newv);
}}}}}	m68k_incpci (2);
return;
}

/* NEGX.B -(An) */
void REGPARAM2 CPUFUNC(op_4020_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 16;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = x_get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_u32 newv = 0 - src - (GET_XFLG () ? 1 : 0);
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(0)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s8)(newv)) == 0));
	SET_NFLG (((uae_s8)(newv)) < 0);
	x_put_byte (srca, newv);
}}}}}	m68k_incpci (2);
return;
}

/* NEGX.B (d16,An) */
void REGPARAM2 CPUFUNC(op_4028_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 16;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uae_u32 newv = 0 - src - (GET_XFLG () ? 1 : 0);
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(0)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s8)(newv)) == 0));
	SET_NFLG (((uae_s8)(newv)) < 0);
	x_put_byte (srca, newv);
}}}}}	m68k_incpci (4);
return;
}

/* NEGX.B (d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_4030_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 16;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s8 src = x_get_byte (srca);
{	uae_u32 newv = 0 - src - (GET_XFLG () ? 1 : 0);
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(0)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s8)(newv)) == 0));
	SET_NFLG (((uae_s8)(newv)) < 0);
	x_put_byte (srca, newv);
}}}}}}return;
}

/* NEGX.B (xxx).W */
void REGPARAM2 CPUFUNC(op_4038_24)(uae_u32 opcode)
{
	OpcodeFamily = 16;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uae_u32 newv = 0 - src - (GET_XFLG () ? 1 : 0);
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(0)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s8)(newv)) == 0));
	SET_NFLG (((uae_s8)(newv)) < 0);
	x_put_byte (srca, newv);
}}}}}	m68k_incpci (4);
return;
}

/* NEGX.B (xxx).L */
void REGPARAM2 CPUFUNC(op_4039_24)(uae_u32 opcode)
{
	OpcodeFamily = 16;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uae_u32 newv = 0 - src - (GET_XFLG () ? 1 : 0);
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(0)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s8)(newv)) == 0));
	SET_NFLG (((uae_s8)(newv)) < 0);
	x_put_byte (srca, newv);
}}}}}	m68k_incpci (6);
return;
}

/* NEGX.W Dn */
void REGPARAM2 CPUFUNC(op_4040_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 16;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_u32 newv = 0 - src - (GET_XFLG () ? 1 : 0);
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(0)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s16)(newv)) == 0));
	SET_NFLG (((uae_s16)(newv)) < 0);
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xffff) | ((newv) & 0xffff);
}}}}	m68k_incpci (2);
return;
}

/* NEGX.W (An) */
void REGPARAM2 CPUFUNC(op_4050_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 16;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
{	uae_u32 newv = 0 - src - (GET_XFLG () ? 1 : 0);
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(0)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s16)(newv)) == 0));
	SET_NFLG (((uae_s16)(newv)) < 0);
	x_put_word (srca, newv);
}}}}}	m68k_incpci (2);
return;
}

/* NEGX.W (An)+ */
void REGPARAM2 CPUFUNC(op_4058_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 16;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	uae_u32 newv = 0 - src - (GET_XFLG () ? 1 : 0);
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(0)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s16)(newv)) == 0));
	SET_NFLG (((uae_s16)(newv)) < 0);
	x_put_word (srca, newv);
}}}}}	m68k_incpci (2);
return;
}

/* NEGX.W -(An) */
void REGPARAM2 CPUFUNC(op_4060_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 16;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_u32 newv = 0 - src - (GET_XFLG () ? 1 : 0);
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(0)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s16)(newv)) == 0));
	SET_NFLG (((uae_s16)(newv)) < 0);
	x_put_word (srca, newv);
}}}}}	m68k_incpci (2);
return;
}

/* NEGX.W (d16,An) */
void REGPARAM2 CPUFUNC(op_4068_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 16;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_u32 newv = 0 - src - (GET_XFLG () ? 1 : 0);
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(0)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s16)(newv)) == 0));
	SET_NFLG (((uae_s16)(newv)) < 0);
	x_put_word (srca, newv);
}}}}}	m68k_incpci (4);
return;
}

/* NEGX.W (d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_4070_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 16;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s16 src = x_get_word (srca);
{	uae_u32 newv = 0 - src - (GET_XFLG () ? 1 : 0);
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(0)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s16)(newv)) == 0));
	SET_NFLG (((uae_s16)(newv)) < 0);
	x_put_word (srca, newv);
}}}}}}return;
}

/* NEGX.W (xxx).W */
void REGPARAM2 CPUFUNC(op_4078_24)(uae_u32 opcode)
{
	OpcodeFamily = 16;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_u32 newv = 0 - src - (GET_XFLG () ? 1 : 0);
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(0)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s16)(newv)) == 0));
	SET_NFLG (((uae_s16)(newv)) < 0);
	x_put_word (srca, newv);
}}}}}	m68k_incpci (4);
return;
}

/* NEGX.W (xxx).L */
void REGPARAM2 CPUFUNC(op_4079_24)(uae_u32 opcode)
{
	OpcodeFamily = 16;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_u32 newv = 0 - src - (GET_XFLG () ? 1 : 0);
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(0)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s16)(newv)) == 0));
	SET_NFLG (((uae_s16)(newv)) < 0);
	x_put_word (srca, newv);
}}}}}	m68k_incpci (6);
return;
}

/* NEGX.L Dn */
void REGPARAM2 CPUFUNC(op_4080_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 16;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uae_u32 newv = 0 - src - (GET_XFLG () ? 1 : 0);
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(0)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s32)(newv)) == 0));
	SET_NFLG (((uae_s32)(newv)) < 0);
	m68k_dreg (regs, srcreg) = (newv);
}}}}	m68k_incpci (2);
return;
}

/* NEGX.L (An) */
void REGPARAM2 CPUFUNC(op_4090_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 16;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s32 src = x_get_long (srca);
{	uae_u32 newv = 0 - src - (GET_XFLG () ? 1 : 0);
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(0)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s32)(newv)) == 0));
	SET_NFLG (((uae_s32)(newv)) < 0);
	x_put_long (srca, newv);
}}}}}	m68k_incpci (2);
return;
}

/* NEGX.L (An)+ */
void REGPARAM2 CPUFUNC(op_4098_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 16;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, srcreg) += 4;
{	uae_u32 newv = 0 - src - (GET_XFLG () ? 1 : 0);
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(0)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s32)(newv)) == 0));
	SET_NFLG (((uae_s32)(newv)) < 0);
	x_put_long (srca, newv);
}}}}}	m68k_incpci (2);
return;
}

/* NEGX.L -(An) */
void REGPARAM2 CPUFUNC(op_40a0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 16;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_u32 newv = 0 - src - (GET_XFLG () ? 1 : 0);
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(0)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s32)(newv)) == 0));
	SET_NFLG (((uae_s32)(newv)) < 0);
	x_put_long (srca, newv);
}}}}}	m68k_incpci (2);
return;
}

/* NEGX.L (d16,An) */
void REGPARAM2 CPUFUNC(op_40a8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 16;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uae_u32 newv = 0 - src - (GET_XFLG () ? 1 : 0);
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(0)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s32)(newv)) == 0));
	SET_NFLG (((uae_s32)(newv)) < 0);
	x_put_long (srca, newv);
}}}}}	m68k_incpci (4);
return;
}

/* NEGX.L (d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_40b0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 16;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s32 src = x_get_long (srca);
{	uae_u32 newv = 0 - src - (GET_XFLG () ? 1 : 0);
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(0)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s32)(newv)) == 0));
	SET_NFLG (((uae_s32)(newv)) < 0);
	x_put_long (srca, newv);
}}}}}}return;
}

/* NEGX.L (xxx).W */
void REGPARAM2 CPUFUNC(op_40b8_24)(uae_u32 opcode)
{
	OpcodeFamily = 16;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uae_u32 newv = 0 - src - (GET_XFLG () ? 1 : 0);
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(0)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s32)(newv)) == 0));
	SET_NFLG (((uae_s32)(newv)) < 0);
	x_put_long (srca, newv);
}}}}}	m68k_incpci (4);
return;
}

/* NEGX.L (xxx).L */
void REGPARAM2 CPUFUNC(op_40b9_24)(uae_u32 opcode)
{
	OpcodeFamily = 16;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uae_u32 newv = 0 - src - (GET_XFLG () ? 1 : 0);
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(0)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s32)(newv)) == 0));
	SET_NFLG (((uae_s32)(newv)) < 0);
	x_put_long (srca, newv);
}}}}}	m68k_incpci (6);
return;
}

/* MVSR2.W Dn */
void REGPARAM2 CPUFUNC(op_40c0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 32;
{if (!regs.s) { Exception (8); goto l_240632; }
{{	MakeSR ();
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xffff) | ((regs.sr) & 0xffff);
}}}	m68k_incpci (2);
l_240632: ;
return;
}

/* MVSR2.W (An) */
void REGPARAM2 CPUFUNC(op_40d0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 32;
{if (!regs.s) { Exception (8); goto l_240633; }
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
	MakeSR ();
	x_put_word (srca, regs.sr);
}}}	m68k_incpci (2);
l_240633: ;
return;
}

/* MVSR2.W (An)+ */
void REGPARAM2 CPUFUNC(op_40d8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 32;
{if (!regs.s) { Exception (8); goto l_240634; }
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
	m68k_areg (regs, srcreg) += 2;
	MakeSR ();
	x_put_word (srca, regs.sr);
}}}	m68k_incpci (2);
l_240634: ;
return;
}

/* MVSR2.W -(An) */
void REGPARAM2 CPUFUNC(op_40e0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 32;
{if (!regs.s) { Exception (8); goto l_240635; }
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
	m68k_areg (regs, srcreg) = srca;
	MakeSR ();
	x_put_word (srca, regs.sr);
}}}	m68k_incpci (2);
l_240635: ;
return;
}

/* MVSR2.W (d16,An) */
void REGPARAM2 CPUFUNC(op_40e8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 32;
{if (!regs.s) { Exception (8); goto l_240636; }
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
	MakeSR ();
	x_put_word (srca, regs.sr);
}}}	m68k_incpci (4);
l_240636: ;
return;
}

/* MVSR2.W (d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_40f0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 32;
{if (!regs.s) { Exception (8); goto l_240637; }
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
	MakeSR ();
	x_put_word (srca, regs.sr);
}}}}l_240637: ;
return;
}

/* MVSR2.W (xxx).W */
void REGPARAM2 CPUFUNC(op_40f8_24)(uae_u32 opcode)
{
	OpcodeFamily = 32;
{if (!regs.s) { Exception (8); goto l_240638; }
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
	MakeSR ();
	x_put_word (srca, regs.sr);
}}}	m68k_incpci (4);
l_240638: ;
return;
}

/* MVSR2.W (xxx).L */
void REGPARAM2 CPUFUNC(op_40f9_24)(uae_u32 opcode)
{
	OpcodeFamily = 32;
{if (!regs.s) { Exception (8); goto l_240639; }
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
	MakeSR ();
	x_put_word (srca, regs.sr);
}}}	m68k_incpci (6);
l_240639: ;
return;
}

/* CHK.L Dn,Dn */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_4100_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 80;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	m68k_incpci (2);
	if (dst > src) {
		SET_NFLG (0);
		Exception (6);
		goto l_240640;
	}
	if ((uae_s32)dst < 0) {
		SET_NFLG (1);
		Exception (6);
		goto l_240640;
	}
}}}l_240640: ;
return;
}

#endif
/* CHK.L (An),Dn */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_4110_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 80;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	m68k_incpci (2);
	if (dst > src) {
		SET_NFLG (0);
		Exception (6);
		goto l_240641;
	}
	if ((uae_s32)dst < 0) {
		SET_NFLG (1);
		Exception (6);
		goto l_240641;
	}
}}}}l_240641: ;
return;
}

#endif
/* CHK.L (An)+,Dn */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_4118_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 80;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, srcreg) += 4;
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	m68k_incpci (2);
	if (dst > src) {
		SET_NFLG (0);
		Exception (6);
		goto l_240642;
	}
	if ((uae_s32)dst < 0) {
		SET_NFLG (1);
		Exception (6);
		goto l_240642;
	}
}}}}l_240642: ;
return;
}

#endif
/* CHK.L -(An),Dn */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_4120_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 80;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	m68k_incpci (2);
	if (dst > src) {
		SET_NFLG (0);
		Exception (6);
		goto l_240643;
	}
	if ((uae_s32)dst < 0) {
		SET_NFLG (1);
		Exception (6);
		goto l_240643;
	}
}}}}l_240643: ;
return;
}

#endif
/* CHK.L (d16,An),Dn */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_4128_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 80;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	m68k_incpci (4);
	if (dst > src) {
		SET_NFLG (0);
		Exception (6);
		goto l_240644;
	}
	if ((uae_s32)dst < 0) {
		SET_NFLG (1);
		Exception (6);
		goto l_240644;
	}
}}}}l_240644: ;
return;
}

#endif
/* CHK.L (d8,An,Xn),Dn */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_4130_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 80;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	if (dst > src) {
		SET_NFLG (0);
		Exception (6);
		goto l_240645;
	}
	if ((uae_s32)dst < 0) {
		SET_NFLG (1);
		Exception (6);
		goto l_240645;
	}
}}}}}l_240645: ;
return;
}

#endif
/* CHK.L (xxx).W,Dn */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_4138_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 80;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	m68k_incpci (4);
	if (dst > src) {
		SET_NFLG (0);
		Exception (6);
		goto l_240646;
	}
	if ((uae_s32)dst < 0) {
		SET_NFLG (1);
		Exception (6);
		goto l_240646;
	}
}}}}l_240646: ;
return;
}

#endif
/* CHK.L (xxx).L,Dn */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_4139_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 80;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	m68k_incpci (6);
	if (dst > src) {
		SET_NFLG (0);
		Exception (6);
		goto l_240647;
	}
	if ((uae_s32)dst < 0) {
		SET_NFLG (1);
		Exception (6);
		goto l_240647;
	}
}}}}l_240647: ;
return;
}

#endif
/* CHK.L (d16,PC),Dn */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_413a_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 80;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	m68k_incpci (4);
	if (dst > src) {
		SET_NFLG (0);
		Exception (6);
		goto l_240648;
	}
	if ((uae_s32)dst < 0) {
		SET_NFLG (1);
		Exception (6);
		goto l_240648;
	}
}}}}l_240648: ;
return;
}

#endif
/* CHK.L (d8,PC,Xn),Dn */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_413b_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 80;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	if (dst > src) {
		SET_NFLG (0);
		Exception (6);
		goto l_240649;
	}
	if ((uae_s32)dst < 0) {
		SET_NFLG (1);
		Exception (6);
		goto l_240649;
	}
}}}}}l_240649: ;
return;
}

#endif
/* CHK.L #<data>.L,Dn */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_413c_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 80;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	m68k_incpci (6);
	if (dst > src) {
		SET_NFLG (0);
		Exception (6);
		goto l_240650;
	}
	if ((uae_s32)dst < 0) {
		SET_NFLG (1);
		Exception (6);
		goto l_240650;
	}
}}}l_240650: ;
return;
}

#endif
/* CHK.W Dn,Dn */
void REGPARAM2 CPUFUNC(op_4180_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 80;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	m68k_incpci (2);
	if (dst > src) {
		SET_NFLG (0);
		Exception (6);
		goto l_240651;
	}
	if ((uae_s32)dst < 0) {
		SET_NFLG (1);
		Exception (6);
		goto l_240651;
	}
}}}l_240651: ;
return;
}

/* CHK.W (An),Dn */
void REGPARAM2 CPUFUNC(op_4190_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 80;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	m68k_incpci (2);
	if (dst > src) {
		SET_NFLG (0);
		Exception (6);
		goto l_240652;
	}
	if ((uae_s32)dst < 0) {
		SET_NFLG (1);
		Exception (6);
		goto l_240652;
	}
}}}}l_240652: ;
return;
}

/* CHK.W (An)+,Dn */
void REGPARAM2 CPUFUNC(op_4198_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 80;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	m68k_incpci (2);
	if (dst > src) {
		SET_NFLG (0);
		Exception (6);
		goto l_240653;
	}
	if ((uae_s32)dst < 0) {
		SET_NFLG (1);
		Exception (6);
		goto l_240653;
	}
}}}}l_240653: ;
return;
}

/* CHK.W -(An),Dn */
void REGPARAM2 CPUFUNC(op_41a0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 80;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	m68k_incpci (2);
	if (dst > src) {
		SET_NFLG (0);
		Exception (6);
		goto l_240654;
	}
	if ((uae_s32)dst < 0) {
		SET_NFLG (1);
		Exception (6);
		goto l_240654;
	}
}}}}l_240654: ;
return;
}

/* CHK.W (d16,An),Dn */
void REGPARAM2 CPUFUNC(op_41a8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 80;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	m68k_incpci (4);
	if (dst > src) {
		SET_NFLG (0);
		Exception (6);
		goto l_240655;
	}
	if ((uae_s32)dst < 0) {
		SET_NFLG (1);
		Exception (6);
		goto l_240655;
	}
}}}}l_240655: ;
return;
}

/* CHK.W (d8,An,Xn),Dn */
void REGPARAM2 CPUFUNC(op_41b0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 80;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	if (dst > src) {
		SET_NFLG (0);
		Exception (6);
		goto l_240656;
	}
	if ((uae_s32)dst < 0) {
		SET_NFLG (1);
		Exception (6);
		goto l_240656;
	}
}}}}}l_240656: ;
return;
}

/* CHK.W (xxx).W,Dn */
void REGPARAM2 CPUFUNC(op_41b8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 80;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	m68k_incpci (4);
	if (dst > src) {
		SET_NFLG (0);
		Exception (6);
		goto l_240657;
	}
	if ((uae_s32)dst < 0) {
		SET_NFLG (1);
		Exception (6);
		goto l_240657;
	}
}}}}l_240657: ;
return;
}

/* CHK.W (xxx).L,Dn */
void REGPARAM2 CPUFUNC(op_41b9_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 80;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	m68k_incpci (6);
	if (dst > src) {
		SET_NFLG (0);
		Exception (6);
		goto l_240658;
	}
	if ((uae_s32)dst < 0) {
		SET_NFLG (1);
		Exception (6);
		goto l_240658;
	}
}}}}l_240658: ;
return;
}

/* CHK.W (d16,PC),Dn */
void REGPARAM2 CPUFUNC(op_41ba_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 80;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	m68k_incpci (4);
	if (dst > src) {
		SET_NFLG (0);
		Exception (6);
		goto l_240659;
	}
	if ((uae_s32)dst < 0) {
		SET_NFLG (1);
		Exception (6);
		goto l_240659;
	}
}}}}l_240659: ;
return;
}

/* CHK.W (d8,PC,Xn),Dn */
void REGPARAM2 CPUFUNC(op_41bb_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 80;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	if (dst > src) {
		SET_NFLG (0);
		Exception (6);
		goto l_240660;
	}
	if ((uae_s32)dst < 0) {
		SET_NFLG (1);
		Exception (6);
		goto l_240660;
	}
}}}}}l_240660: ;
return;
}

/* CHK.W #<data>.W,Dn */
void REGPARAM2 CPUFUNC(op_41bc_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 80;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	m68k_incpci (4);
	if (dst > src) {
		SET_NFLG (0);
		Exception (6);
		goto l_240661;
	}
	if ((uae_s32)dst < 0) {
		SET_NFLG (1);
		Exception (6);
		goto l_240661;
	}
}}}l_240661: ;
return;
}

/* LEA.L (An),An */
void REGPARAM2 CPUFUNC(op_41d0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 56;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	m68k_areg (regs, dstreg) = (srca);
}}}	m68k_incpci (2);
return;
}

/* LEA.L (d16,An),An */
void REGPARAM2 CPUFUNC(op_41e8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 56;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	m68k_areg (regs, dstreg) = (srca);
}}}	m68k_incpci (4);
return;
}

/* LEA.L (d8,An,Xn),An */
void REGPARAM2 CPUFUNC(op_41f0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 56;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	m68k_areg (regs, dstreg) = (srca);
}}}}return;
}

/* LEA.L (xxx).W,An */
void REGPARAM2 CPUFUNC(op_41f8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 56;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	m68k_areg (regs, dstreg) = (srca);
}}}	m68k_incpci (4);
return;
}

/* LEA.L (xxx).L,An */
void REGPARAM2 CPUFUNC(op_41f9_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 56;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	m68k_areg (regs, dstreg) = (srca);
}}}	m68k_incpci (6);
return;
}

/* LEA.L (d16,PC),An */
void REGPARAM2 CPUFUNC(op_41fa_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 56;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	m68k_areg (regs, dstreg) = (srca);
}}}	m68k_incpci (4);
return;
}

/* LEA.L (d8,PC,Xn),An */
void REGPARAM2 CPUFUNC(op_41fb_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 56;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	m68k_areg (regs, dstreg) = (srca);
}}}}return;
}

/* CLR.B Dn */
void REGPARAM2 CPUFUNC(op_4200_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 18;
{{	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(0)) == 0);
	SET_NFLG (((uae_s8)(0)) < 0);
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xff) | ((0) & 0xff);
}}	m68k_incpci (2);
return;
}

/* CLR.B (An) */
void REGPARAM2 CPUFUNC(op_4210_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 18;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(0)) == 0);
	SET_NFLG (((uae_s8)(0)) < 0);
	x_put_byte (srca, 0);
}}	m68k_incpci (2);
return;
}

/* CLR.B (An)+ */
void REGPARAM2 CPUFUNC(op_4218_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 18;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(0)) == 0);
	SET_NFLG (((uae_s8)(0)) < 0);
	x_put_byte (srca, 0);
}}	m68k_incpci (2);
return;
}

/* CLR.B -(An) */
void REGPARAM2 CPUFUNC(op_4220_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 18;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
	m68k_areg (regs, srcreg) = srca;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(0)) == 0);
	SET_NFLG (((uae_s8)(0)) < 0);
	x_put_byte (srca, 0);
}}	m68k_incpci (2);
return;
}

/* CLR.B (d16,An) */
void REGPARAM2 CPUFUNC(op_4228_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 18;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(0)) == 0);
	SET_NFLG (((uae_s8)(0)) < 0);
	x_put_byte (srca, 0);
}}	m68k_incpci (4);
return;
}

/* CLR.B (d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_4230_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 18;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(0)) == 0);
	SET_NFLG (((uae_s8)(0)) < 0);
	x_put_byte (srca, 0);
}}}return;
}

/* CLR.B (xxx).W */
void REGPARAM2 CPUFUNC(op_4238_24)(uae_u32 opcode)
{
	OpcodeFamily = 18;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(0)) == 0);
	SET_NFLG (((uae_s8)(0)) < 0);
	x_put_byte (srca, 0);
}}	m68k_incpci (4);
return;
}

/* CLR.B (xxx).L */
void REGPARAM2 CPUFUNC(op_4239_24)(uae_u32 opcode)
{
	OpcodeFamily = 18;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(0)) == 0);
	SET_NFLG (((uae_s8)(0)) < 0);
	x_put_byte (srca, 0);
}}	m68k_incpci (6);
return;
}

/* CLR.W Dn */
void REGPARAM2 CPUFUNC(op_4240_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 18;
{{	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(0)) == 0);
	SET_NFLG (((uae_s16)(0)) < 0);
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xffff) | ((0) & 0xffff);
}}	m68k_incpci (2);
return;
}

/* CLR.W (An) */
void REGPARAM2 CPUFUNC(op_4250_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 18;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(0)) == 0);
	SET_NFLG (((uae_s16)(0)) < 0);
	x_put_word (srca, 0);
}}	m68k_incpci (2);
return;
}

/* CLR.W (An)+ */
void REGPARAM2 CPUFUNC(op_4258_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 18;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
	m68k_areg (regs, srcreg) += 2;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(0)) == 0);
	SET_NFLG (((uae_s16)(0)) < 0);
	x_put_word (srca, 0);
}}	m68k_incpci (2);
return;
}

/* CLR.W -(An) */
void REGPARAM2 CPUFUNC(op_4260_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 18;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
	m68k_areg (regs, srcreg) = srca;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(0)) == 0);
	SET_NFLG (((uae_s16)(0)) < 0);
	x_put_word (srca, 0);
}}	m68k_incpci (2);
return;
}

/* CLR.W (d16,An) */
void REGPARAM2 CPUFUNC(op_4268_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 18;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(0)) == 0);
	SET_NFLG (((uae_s16)(0)) < 0);
	x_put_word (srca, 0);
}}	m68k_incpci (4);
return;
}

/* CLR.W (d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_4270_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 18;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(0)) == 0);
	SET_NFLG (((uae_s16)(0)) < 0);
	x_put_word (srca, 0);
}}}return;
}

/* CLR.W (xxx).W */
void REGPARAM2 CPUFUNC(op_4278_24)(uae_u32 opcode)
{
	OpcodeFamily = 18;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(0)) == 0);
	SET_NFLG (((uae_s16)(0)) < 0);
	x_put_word (srca, 0);
}}	m68k_incpci (4);
return;
}

/* CLR.W (xxx).L */
void REGPARAM2 CPUFUNC(op_4279_24)(uae_u32 opcode)
{
	OpcodeFamily = 18;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(0)) == 0);
	SET_NFLG (((uae_s16)(0)) < 0);
	x_put_word (srca, 0);
}}	m68k_incpci (6);
return;
}

/* CLR.L Dn */
void REGPARAM2 CPUFUNC(op_4280_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 18;
{{	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(0)) == 0);
	SET_NFLG (((uae_s32)(0)) < 0);
	m68k_dreg (regs, srcreg) = (0);
}}	m68k_incpci (2);
return;
}

/* CLR.L (An) */
void REGPARAM2 CPUFUNC(op_4290_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 18;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(0)) == 0);
	SET_NFLG (((uae_s32)(0)) < 0);
	x_put_long (srca, 0);
}}	m68k_incpci (2);
return;
}

/* CLR.L (An)+ */
void REGPARAM2 CPUFUNC(op_4298_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 18;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
	m68k_areg (regs, srcreg) += 4;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(0)) == 0);
	SET_NFLG (((uae_s32)(0)) < 0);
	x_put_long (srca, 0);
}}	m68k_incpci (2);
return;
}

/* CLR.L -(An) */
void REGPARAM2 CPUFUNC(op_42a0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 18;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
	m68k_areg (regs, srcreg) = srca;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(0)) == 0);
	SET_NFLG (((uae_s32)(0)) < 0);
	x_put_long (srca, 0);
}}	m68k_incpci (2);
return;
}

/* CLR.L (d16,An) */
void REGPARAM2 CPUFUNC(op_42a8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 18;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(0)) == 0);
	SET_NFLG (((uae_s32)(0)) < 0);
	x_put_long (srca, 0);
}}	m68k_incpci (4);
return;
}

/* CLR.L (d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_42b0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 18;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(0)) == 0);
	SET_NFLG (((uae_s32)(0)) < 0);
	x_put_long (srca, 0);
}}}return;
}

/* CLR.L (xxx).W */
void REGPARAM2 CPUFUNC(op_42b8_24)(uae_u32 opcode)
{
	OpcodeFamily = 18;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(0)) == 0);
	SET_NFLG (((uae_s32)(0)) < 0);
	x_put_long (srca, 0);
}}	m68k_incpci (4);
return;
}

/* CLR.L (xxx).L */
void REGPARAM2 CPUFUNC(op_42b9_24)(uae_u32 opcode)
{
	OpcodeFamily = 18;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(0)) == 0);
	SET_NFLG (((uae_s32)(0)) < 0);
	x_put_long (srca, 0);
}}	m68k_incpci (6);
return;
}

/* MVSR2.B Dn */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_42c0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 32;
{{	MakeSR ();
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xffff) | ((regs.sr & 0xff) & 0xffff);
}}	m68k_incpci (2);
return;
}

#endif
/* MVSR2.B (An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_42d0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 32;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
	MakeSR ();
	x_put_word (srca, regs.sr & 0xff);
}}	m68k_incpci (2);
return;
}

#endif
/* MVSR2.B (An)+ */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_42d8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 32;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
	m68k_areg (regs, srcreg) += 2;
	MakeSR ();
	x_put_word (srca, regs.sr & 0xff);
}}	m68k_incpci (2);
return;
}

#endif
/* MVSR2.B -(An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_42e0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 32;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
	m68k_areg (regs, srcreg) = srca;
	MakeSR ();
	x_put_word (srca, regs.sr & 0xff);
}}	m68k_incpci (2);
return;
}

#endif
/* MVSR2.B (d16,An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_42e8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 32;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
	MakeSR ();
	x_put_word (srca, regs.sr & 0xff);
}}	m68k_incpci (4);
return;
}

#endif
/* MVSR2.B (d8,An,Xn) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_42f0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 32;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
	MakeSR ();
	x_put_word (srca, regs.sr & 0xff);
}}}return;
}

#endif
/* MVSR2.B (xxx).W */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_42f8_24)(uae_u32 opcode)
{
	OpcodeFamily = 32;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
	MakeSR ();
	x_put_word (srca, regs.sr & 0xff);
}}	m68k_incpci (4);
return;
}

#endif
/* MVSR2.B (xxx).L */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_42f9_24)(uae_u32 opcode)
{
	OpcodeFamily = 32;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
	MakeSR ();
	x_put_word (srca, regs.sr & 0xff);
}}	m68k_incpci (6);
return;
}

#endif
/* NEG.B Dn */
void REGPARAM2 CPUFUNC(op_4400_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 15;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{{uae_u32 dst = ((uae_u8)(0)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(0)) < 0;
	int flgn = ((uae_s8)(dst)) < 0;
	SET_ZFLG (((uae_s8)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(0)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xff) | ((dst) & 0xff);
}}}}}	m68k_incpci (2);
return;
}

#endif

#ifdef PART_4
/* NEG.B (An) */
void REGPARAM2 CPUFUNC(op_4410_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 15;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s8 src = x_get_byte (srca);
{{uae_u32 dst = ((uae_u8)(0)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(0)) < 0;
	int flgn = ((uae_s8)(dst)) < 0;
	SET_ZFLG (((uae_s8)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(0)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (srca, dst);
}}}}}}	m68k_incpci (2);
return;
}

/* NEG.B (An)+ */
void REGPARAM2 CPUFUNC(op_4418_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 15;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s8 src = x_get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{{uae_u32 dst = ((uae_u8)(0)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(0)) < 0;
	int flgn = ((uae_s8)(dst)) < 0;
	SET_ZFLG (((uae_s8)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(0)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (srca, dst);
}}}}}}	m68k_incpci (2);
return;
}

/* NEG.B -(An) */
void REGPARAM2 CPUFUNC(op_4420_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 15;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = x_get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{{uae_u32 dst = ((uae_u8)(0)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(0)) < 0;
	int flgn = ((uae_s8)(dst)) < 0;
	SET_ZFLG (((uae_s8)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(0)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (srca, dst);
}}}}}}	m68k_incpci (2);
return;
}

/* NEG.B (d16,An) */
void REGPARAM2 CPUFUNC(op_4428_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 15;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{{uae_u32 dst = ((uae_u8)(0)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(0)) < 0;
	int flgn = ((uae_s8)(dst)) < 0;
	SET_ZFLG (((uae_s8)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(0)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (srca, dst);
}}}}}}	m68k_incpci (4);
return;
}

/* NEG.B (d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_4430_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 15;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s8 src = x_get_byte (srca);
{{uae_u32 dst = ((uae_u8)(0)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(0)) < 0;
	int flgn = ((uae_s8)(dst)) < 0;
	SET_ZFLG (((uae_s8)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(0)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (srca, dst);
}}}}}}}return;
}

/* NEG.B (xxx).W */
void REGPARAM2 CPUFUNC(op_4438_24)(uae_u32 opcode)
{
	OpcodeFamily = 15;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{{uae_u32 dst = ((uae_u8)(0)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(0)) < 0;
	int flgn = ((uae_s8)(dst)) < 0;
	SET_ZFLG (((uae_s8)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(0)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (srca, dst);
}}}}}}	m68k_incpci (4);
return;
}

/* NEG.B (xxx).L */
void REGPARAM2 CPUFUNC(op_4439_24)(uae_u32 opcode)
{
	OpcodeFamily = 15;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{{uae_u32 dst = ((uae_u8)(0)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(0)) < 0;
	int flgn = ((uae_s8)(dst)) < 0;
	SET_ZFLG (((uae_s8)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(0)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (srca, dst);
}}}}}}	m68k_incpci (6);
return;
}

/* NEG.W Dn */
void REGPARAM2 CPUFUNC(op_4440_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 15;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{{uae_u32 dst = ((uae_u16)(0)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(0)) < 0;
	int flgn = ((uae_s16)(dst)) < 0;
	SET_ZFLG (((uae_s16)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(0)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xffff) | ((dst) & 0xffff);
}}}}}	m68k_incpci (2);
return;
}

/* NEG.W (An) */
void REGPARAM2 CPUFUNC(op_4450_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 15;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
{{uae_u32 dst = ((uae_u16)(0)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(0)) < 0;
	int flgn = ((uae_s16)(dst)) < 0;
	SET_ZFLG (((uae_s16)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(0)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (srca, dst);
}}}}}}	m68k_incpci (2);
return;
}

/* NEG.W (An)+ */
void REGPARAM2 CPUFUNC(op_4458_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 15;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{{uae_u32 dst = ((uae_u16)(0)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(0)) < 0;
	int flgn = ((uae_s16)(dst)) < 0;
	SET_ZFLG (((uae_s16)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(0)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (srca, dst);
}}}}}}	m68k_incpci (2);
return;
}

/* NEG.W -(An) */
void REGPARAM2 CPUFUNC(op_4460_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 15;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{{uae_u32 dst = ((uae_u16)(0)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(0)) < 0;
	int flgn = ((uae_s16)(dst)) < 0;
	SET_ZFLG (((uae_s16)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(0)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (srca, dst);
}}}}}}	m68k_incpci (2);
return;
}

/* NEG.W (d16,An) */
void REGPARAM2 CPUFUNC(op_4468_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 15;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{{uae_u32 dst = ((uae_u16)(0)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(0)) < 0;
	int flgn = ((uae_s16)(dst)) < 0;
	SET_ZFLG (((uae_s16)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(0)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (srca, dst);
}}}}}}	m68k_incpci (4);
return;
}

/* NEG.W (d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_4470_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 15;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s16 src = x_get_word (srca);
{{uae_u32 dst = ((uae_u16)(0)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(0)) < 0;
	int flgn = ((uae_s16)(dst)) < 0;
	SET_ZFLG (((uae_s16)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(0)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (srca, dst);
}}}}}}}return;
}

/* NEG.W (xxx).W */
void REGPARAM2 CPUFUNC(op_4478_24)(uae_u32 opcode)
{
	OpcodeFamily = 15;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{{uae_u32 dst = ((uae_u16)(0)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(0)) < 0;
	int flgn = ((uae_s16)(dst)) < 0;
	SET_ZFLG (((uae_s16)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(0)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (srca, dst);
}}}}}}	m68k_incpci (4);
return;
}

/* NEG.W (xxx).L */
void REGPARAM2 CPUFUNC(op_4479_24)(uae_u32 opcode)
{
	OpcodeFamily = 15;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{{uae_u32 dst = ((uae_u16)(0)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(0)) < 0;
	int flgn = ((uae_s16)(dst)) < 0;
	SET_ZFLG (((uae_s16)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(0)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (srca, dst);
}}}}}}	m68k_incpci (6);
return;
}

/* NEG.L Dn */
void REGPARAM2 CPUFUNC(op_4480_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 15;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{{uae_u32 dst = ((uae_u32)(0)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(0)) < 0;
	int flgn = ((uae_s32)(dst)) < 0;
	SET_ZFLG (((uae_s32)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(0)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, srcreg) = (dst);
}}}}}	m68k_incpci (2);
return;
}

/* NEG.L (An) */
void REGPARAM2 CPUFUNC(op_4490_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 15;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s32 src = x_get_long (srca);
{{uae_u32 dst = ((uae_u32)(0)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(0)) < 0;
	int flgn = ((uae_s32)(dst)) < 0;
	SET_ZFLG (((uae_s32)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(0)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (srca, dst);
}}}}}}	m68k_incpci (2);
return;
}

/* NEG.L (An)+ */
void REGPARAM2 CPUFUNC(op_4498_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 15;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, srcreg) += 4;
{{uae_u32 dst = ((uae_u32)(0)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(0)) < 0;
	int flgn = ((uae_s32)(dst)) < 0;
	SET_ZFLG (((uae_s32)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(0)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (srca, dst);
}}}}}}	m68k_incpci (2);
return;
}

/* NEG.L -(An) */
void REGPARAM2 CPUFUNC(op_44a0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 15;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, srcreg) = srca;
{{uae_u32 dst = ((uae_u32)(0)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(0)) < 0;
	int flgn = ((uae_s32)(dst)) < 0;
	SET_ZFLG (((uae_s32)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(0)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (srca, dst);
}}}}}}	m68k_incpci (2);
return;
}

/* NEG.L (d16,An) */
void REGPARAM2 CPUFUNC(op_44a8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 15;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{{uae_u32 dst = ((uae_u32)(0)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(0)) < 0;
	int flgn = ((uae_s32)(dst)) < 0;
	SET_ZFLG (((uae_s32)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(0)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (srca, dst);
}}}}}}	m68k_incpci (4);
return;
}

/* NEG.L (d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_44b0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 15;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s32 src = x_get_long (srca);
{{uae_u32 dst = ((uae_u32)(0)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(0)) < 0;
	int flgn = ((uae_s32)(dst)) < 0;
	SET_ZFLG (((uae_s32)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(0)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (srca, dst);
}}}}}}}return;
}

/* NEG.L (xxx).W */
void REGPARAM2 CPUFUNC(op_44b8_24)(uae_u32 opcode)
{
	OpcodeFamily = 15;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{{uae_u32 dst = ((uae_u32)(0)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(0)) < 0;
	int flgn = ((uae_s32)(dst)) < 0;
	SET_ZFLG (((uae_s32)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(0)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (srca, dst);
}}}}}}	m68k_incpci (4);
return;
}

/* NEG.L (xxx).L */
void REGPARAM2 CPUFUNC(op_44b9_24)(uae_u32 opcode)
{
	OpcodeFamily = 15;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{{uae_u32 dst = ((uae_u32)(0)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(0)) < 0;
	int flgn = ((uae_s32)(dst)) < 0;
	SET_ZFLG (((uae_s32)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(0)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (srca, dst);
}}}}}}	m68k_incpci (6);
return;
}

/* MV2SR.B Dn */
void REGPARAM2 CPUFUNC(op_44c0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 33;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
	MakeSR ();
	regs.sr &= 0xFF00;
	regs.sr |= src & 0xFF;
	MakeFromSR();
}}	m68k_incpci (2);
return;
}

/* MV2SR.B (An) */
void REGPARAM2 CPUFUNC(op_44d0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 33;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
	MakeSR ();
	regs.sr &= 0xFF00;
	regs.sr |= src & 0xFF;
	MakeFromSR();
}}}	m68k_incpci (2);
return;
}

/* MV2SR.B (An)+ */
void REGPARAM2 CPUFUNC(op_44d8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 33;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) += 2;
	MakeSR ();
	regs.sr &= 0xFF00;
	regs.sr |= src & 0xFF;
	MakeFromSR();
}}}	m68k_incpci (2);
return;
}

/* MV2SR.B -(An) */
void REGPARAM2 CPUFUNC(op_44e0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 33;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) = srca;
	MakeSR ();
	regs.sr &= 0xFF00;
	regs.sr |= src & 0xFF;
	MakeFromSR();
}}}	m68k_incpci (2);
return;
}

/* MV2SR.B (d16,An) */
void REGPARAM2 CPUFUNC(op_44e8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 33;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
	MakeSR ();
	regs.sr &= 0xFF00;
	regs.sr |= src & 0xFF;
	MakeFromSR();
}}}	m68k_incpci (4);
return;
}

/* MV2SR.B (d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_44f0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 33;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s16 src = x_get_word (srca);
	MakeSR ();
	regs.sr &= 0xFF00;
	regs.sr |= src & 0xFF;
	MakeFromSR();
}}}}return;
}

/* MV2SR.B (xxx).W */
void REGPARAM2 CPUFUNC(op_44f8_24)(uae_u32 opcode)
{
	OpcodeFamily = 33;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
	MakeSR ();
	regs.sr &= 0xFF00;
	regs.sr |= src & 0xFF;
	MakeFromSR();
}}}	m68k_incpci (4);
return;
}

/* MV2SR.B (xxx).L */
void REGPARAM2 CPUFUNC(op_44f9_24)(uae_u32 opcode)
{
	OpcodeFamily = 33;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
	MakeSR ();
	regs.sr &= 0xFF00;
	regs.sr |= src & 0xFF;
	MakeFromSR();
}}}	m68k_incpci (6);
return;
}

/* MV2SR.B (d16,PC) */
void REGPARAM2 CPUFUNC(op_44fa_24)(uae_u32 opcode)
{
	OpcodeFamily = 33;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
	MakeSR ();
	regs.sr &= 0xFF00;
	regs.sr |= src & 0xFF;
	MakeFromSR();
}}}	m68k_incpci (4);
return;
}

/* MV2SR.B (d8,PC,Xn) */
void REGPARAM2 CPUFUNC(op_44fb_24)(uae_u32 opcode)
{
	OpcodeFamily = 33;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s16 src = x_get_word (srca);
	MakeSR ();
	regs.sr &= 0xFF00;
	regs.sr |= src & 0xFF;
	MakeFromSR();
}}}}return;
}

/* MV2SR.B #<data>.B */
void REGPARAM2 CPUFUNC(op_44fc_24)(uae_u32 opcode)
{
	OpcodeFamily = 33;
{{	uae_s16 src = get_iword_cache_040 (2);
	MakeSR ();
	regs.sr &= 0xFF00;
	regs.sr |= src & 0xFF;
	MakeFromSR();
}}	m68k_incpci (4);
return;
}

/* NOT.B Dn */
void REGPARAM2 CPUFUNC(op_4600_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 19;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uae_u32 dst = ~src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(dst)) == 0);
	SET_NFLG (((uae_s8)(dst)) < 0);
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xff) | ((dst) & 0xff);
}}}	m68k_incpci (2);
return;
}

/* NOT.B (An) */
void REGPARAM2 CPUFUNC(op_4610_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 19;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s8 src = x_get_byte (srca);
{	uae_u32 dst = ~src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(dst)) == 0);
	SET_NFLG (((uae_s8)(dst)) < 0);
	x_put_byte (srca, dst);
}}}}	m68k_incpci (2);
return;
}

/* NOT.B (An)+ */
void REGPARAM2 CPUFUNC(op_4618_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 19;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s8 src = x_get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{	uae_u32 dst = ~src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(dst)) == 0);
	SET_NFLG (((uae_s8)(dst)) < 0);
	x_put_byte (srca, dst);
}}}}	m68k_incpci (2);
return;
}

/* NOT.B -(An) */
void REGPARAM2 CPUFUNC(op_4620_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 19;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = x_get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_u32 dst = ~src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(dst)) == 0);
	SET_NFLG (((uae_s8)(dst)) < 0);
	x_put_byte (srca, dst);
}}}}	m68k_incpci (2);
return;
}

/* NOT.B (d16,An) */
void REGPARAM2 CPUFUNC(op_4628_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 19;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uae_u32 dst = ~src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(dst)) == 0);
	SET_NFLG (((uae_s8)(dst)) < 0);
	x_put_byte (srca, dst);
}}}}	m68k_incpci (4);
return;
}

/* NOT.B (d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_4630_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 19;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s8 src = x_get_byte (srca);
{	uae_u32 dst = ~src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(dst)) == 0);
	SET_NFLG (((uae_s8)(dst)) < 0);
	x_put_byte (srca, dst);
}}}}}return;
}

/* NOT.B (xxx).W */
void REGPARAM2 CPUFUNC(op_4638_24)(uae_u32 opcode)
{
	OpcodeFamily = 19;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uae_u32 dst = ~src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(dst)) == 0);
	SET_NFLG (((uae_s8)(dst)) < 0);
	x_put_byte (srca, dst);
}}}}	m68k_incpci (4);
return;
}

/* NOT.B (xxx).L */
void REGPARAM2 CPUFUNC(op_4639_24)(uae_u32 opcode)
{
	OpcodeFamily = 19;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uae_u32 dst = ~src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(dst)) == 0);
	SET_NFLG (((uae_s8)(dst)) < 0);
	x_put_byte (srca, dst);
}}}}	m68k_incpci (6);
return;
}

/* NOT.W Dn */
void REGPARAM2 CPUFUNC(op_4640_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 19;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_u32 dst = ~src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(dst)) == 0);
	SET_NFLG (((uae_s16)(dst)) < 0);
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xffff) | ((dst) & 0xffff);
}}}	m68k_incpci (2);
return;
}

/* NOT.W (An) */
void REGPARAM2 CPUFUNC(op_4650_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 19;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
{	uae_u32 dst = ~src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(dst)) == 0);
	SET_NFLG (((uae_s16)(dst)) < 0);
	x_put_word (srca, dst);
}}}}	m68k_incpci (2);
return;
}

/* NOT.W (An)+ */
void REGPARAM2 CPUFUNC(op_4658_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 19;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	uae_u32 dst = ~src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(dst)) == 0);
	SET_NFLG (((uae_s16)(dst)) < 0);
	x_put_word (srca, dst);
}}}}	m68k_incpci (2);
return;
}

/* NOT.W -(An) */
void REGPARAM2 CPUFUNC(op_4660_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 19;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_u32 dst = ~src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(dst)) == 0);
	SET_NFLG (((uae_s16)(dst)) < 0);
	x_put_word (srca, dst);
}}}}	m68k_incpci (2);
return;
}

/* NOT.W (d16,An) */
void REGPARAM2 CPUFUNC(op_4668_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 19;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_u32 dst = ~src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(dst)) == 0);
	SET_NFLG (((uae_s16)(dst)) < 0);
	x_put_word (srca, dst);
}}}}	m68k_incpci (4);
return;
}

/* NOT.W (d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_4670_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 19;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s16 src = x_get_word (srca);
{	uae_u32 dst = ~src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(dst)) == 0);
	SET_NFLG (((uae_s16)(dst)) < 0);
	x_put_word (srca, dst);
}}}}}return;
}

/* NOT.W (xxx).W */
void REGPARAM2 CPUFUNC(op_4678_24)(uae_u32 opcode)
{
	OpcodeFamily = 19;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_u32 dst = ~src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(dst)) == 0);
	SET_NFLG (((uae_s16)(dst)) < 0);
	x_put_word (srca, dst);
}}}}	m68k_incpci (4);
return;
}

/* NOT.W (xxx).L */
void REGPARAM2 CPUFUNC(op_4679_24)(uae_u32 opcode)
{
	OpcodeFamily = 19;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_u32 dst = ~src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(dst)) == 0);
	SET_NFLG (((uae_s16)(dst)) < 0);
	x_put_word (srca, dst);
}}}}	m68k_incpci (6);
return;
}

/* NOT.L Dn */
void REGPARAM2 CPUFUNC(op_4680_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 19;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uae_u32 dst = ~src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(dst)) == 0);
	SET_NFLG (((uae_s32)(dst)) < 0);
	m68k_dreg (regs, srcreg) = (dst);
}}}	m68k_incpci (2);
return;
}

/* NOT.L (An) */
void REGPARAM2 CPUFUNC(op_4690_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 19;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s32 src = x_get_long (srca);
{	uae_u32 dst = ~src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(dst)) == 0);
	SET_NFLG (((uae_s32)(dst)) < 0);
	x_put_long (srca, dst);
}}}}	m68k_incpci (2);
return;
}

/* NOT.L (An)+ */
void REGPARAM2 CPUFUNC(op_4698_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 19;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, srcreg) += 4;
{	uae_u32 dst = ~src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(dst)) == 0);
	SET_NFLG (((uae_s32)(dst)) < 0);
	x_put_long (srca, dst);
}}}}	m68k_incpci (2);
return;
}

/* NOT.L -(An) */
void REGPARAM2 CPUFUNC(op_46a0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 19;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_u32 dst = ~src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(dst)) == 0);
	SET_NFLG (((uae_s32)(dst)) < 0);
	x_put_long (srca, dst);
}}}}	m68k_incpci (2);
return;
}

/* NOT.L (d16,An) */
void REGPARAM2 CPUFUNC(op_46a8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 19;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uae_u32 dst = ~src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(dst)) == 0);
	SET_NFLG (((uae_s32)(dst)) < 0);
	x_put_long (srca, dst);
}}}}	m68k_incpci (4);
return;
}

/* NOT.L (d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_46b0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 19;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s32 src = x_get_long (srca);
{	uae_u32 dst = ~src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(dst)) == 0);
	SET_NFLG (((uae_s32)(dst)) < 0);
	x_put_long (srca, dst);
}}}}}return;
}

/* NOT.L (xxx).W */
void REGPARAM2 CPUFUNC(op_46b8_24)(uae_u32 opcode)
{
	OpcodeFamily = 19;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uae_u32 dst = ~src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(dst)) == 0);
	SET_NFLG (((uae_s32)(dst)) < 0);
	x_put_long (srca, dst);
}}}}	m68k_incpci (4);
return;
}

/* NOT.L (xxx).L */
void REGPARAM2 CPUFUNC(op_46b9_24)(uae_u32 opcode)
{
	OpcodeFamily = 19;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uae_u32 dst = ~src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(dst)) == 0);
	SET_NFLG (((uae_s32)(dst)) < 0);
	x_put_long (srca, dst);
}}}}	m68k_incpci (6);
return;
}

/* MV2SR.W Dn */
void REGPARAM2 CPUFUNC(op_46c0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 33;
{if (!regs.s) { Exception (8); goto l_240760; }
{{	uae_s16 src = m68k_dreg (regs, srcreg);
	regs.sr = src;
	MakeFromSR();
}}}	m68k_incpci (2);
l_240760: ;
return;
}

/* MV2SR.W (An) */
void REGPARAM2 CPUFUNC(op_46d0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 33;
{if (!regs.s) { Exception (8); goto l_240761; }
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
	regs.sr = src;
	MakeFromSR();
}}}}	m68k_incpci (2);
l_240761: ;
return;
}

/* MV2SR.W (An)+ */
void REGPARAM2 CPUFUNC(op_46d8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 33;
{if (!regs.s) { Exception (8); goto l_240762; }
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) += 2;
	regs.sr = src;
	MakeFromSR();
}}}}	m68k_incpci (2);
l_240762: ;
return;
}

/* MV2SR.W -(An) */
void REGPARAM2 CPUFUNC(op_46e0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 33;
{if (!regs.s) { Exception (8); goto l_240763; }
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) = srca;
	regs.sr = src;
	MakeFromSR();
}}}}	m68k_incpci (2);
l_240763: ;
return;
}

/* MV2SR.W (d16,An) */
void REGPARAM2 CPUFUNC(op_46e8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 33;
{if (!regs.s) { Exception (8); goto l_240764; }
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
	regs.sr = src;
	MakeFromSR();
}}}}	m68k_incpci (4);
l_240764: ;
return;
}

/* MV2SR.W (d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_46f0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 33;
{if (!regs.s) { Exception (8); goto l_240765; }
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s16 src = x_get_word (srca);
	regs.sr = src;
	MakeFromSR();
}}}}}l_240765: ;
return;
}

/* MV2SR.W (xxx).W */
void REGPARAM2 CPUFUNC(op_46f8_24)(uae_u32 opcode)
{
	OpcodeFamily = 33;
{if (!regs.s) { Exception (8); goto l_240766; }
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
	regs.sr = src;
	MakeFromSR();
}}}}	m68k_incpci (4);
l_240766: ;
return;
}

/* MV2SR.W (xxx).L */
void REGPARAM2 CPUFUNC(op_46f9_24)(uae_u32 opcode)
{
	OpcodeFamily = 33;
{if (!regs.s) { Exception (8); goto l_240767; }
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
	regs.sr = src;
	MakeFromSR();
}}}}	m68k_incpci (6);
l_240767: ;
return;
}

/* MV2SR.W (d16,PC) */
void REGPARAM2 CPUFUNC(op_46fa_24)(uae_u32 opcode)
{
	OpcodeFamily = 33;
{if (!regs.s) { Exception (8); goto l_240768; }
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
	regs.sr = src;
	MakeFromSR();
}}}}	m68k_incpci (4);
l_240768: ;
return;
}

/* MV2SR.W (d8,PC,Xn) */
void REGPARAM2 CPUFUNC(op_46fb_24)(uae_u32 opcode)
{
	OpcodeFamily = 33;
{if (!regs.s) { Exception (8); goto l_240769; }
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s16 src = x_get_word (srca);
	regs.sr = src;
	MakeFromSR();
}}}}}l_240769: ;
return;
}

/* MV2SR.W #<data>.W */
void REGPARAM2 CPUFUNC(op_46fc_24)(uae_u32 opcode)
{
	OpcodeFamily = 33;
{if (!regs.s) { Exception (8); goto l_240770; }
{{	uae_s16 src = get_iword_cache_040 (2);
	regs.sr = src;
	MakeFromSR();
}}}	m68k_incpci (4);
l_240770: ;
return;
}

/* NBCD.B Dn */
void REGPARAM2 CPUFUNC(op_4800_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 17;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uae_u16 newv_lo = - (src & 0xF) - (GET_XFLG () ? 1 : 0);
	uae_u16 newv_hi = - (src & 0xF0);
	uae_u16 newv;
	int cflg;
	if (newv_lo > 9) { newv_lo -= 6; }
	newv = newv_hi + newv_lo;
	cflg = (newv & 0x1F0) > 0x90;
	if (cflg) newv -= 0x60;
	SET_CFLG (cflg);
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s8)(newv)) == 0));
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xff) | ((newv) & 0xff);
}}}	m68k_incpci (2);
return;
}

/* LINK.L An,#<data>.L */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_4808_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 47;
{{	uaecptr olda;
	olda = m68k_areg (regs, 7) - 4;
	m68k_areg (regs, 7) = olda;
{	uae_s32 src = m68k_areg (regs, srcreg);
{	uae_s32 offs;
	offs = get_ilong_cache_040 (2);
	x_put_long (olda, src);
	m68k_areg (regs, srcreg) = (m68k_areg (regs, 7));
	m68k_areg (regs, 7) += offs;
}}}}	m68k_incpci (6);
return;
}

#endif
/* NBCD.B (An) */
void REGPARAM2 CPUFUNC(op_4810_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 17;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s8 src = x_get_byte (srca);
{	uae_u16 newv_lo = - (src & 0xF) - (GET_XFLG () ? 1 : 0);
	uae_u16 newv_hi = - (src & 0xF0);
	uae_u16 newv;
	int cflg;
	if (newv_lo > 9) { newv_lo -= 6; }
	newv = newv_hi + newv_lo;
	cflg = (newv & 0x1F0) > 0x90;
	if (cflg) newv -= 0x60;
	SET_CFLG (cflg);
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s8)(newv)) == 0));
	x_put_byte (srca, newv);
}}}}	m68k_incpci (2);
return;
}

/* NBCD.B (An)+ */
void REGPARAM2 CPUFUNC(op_4818_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 17;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s8 src = x_get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{	uae_u16 newv_lo = - (src & 0xF) - (GET_XFLG () ? 1 : 0);
	uae_u16 newv_hi = - (src & 0xF0);
	uae_u16 newv;
	int cflg;
	if (newv_lo > 9) { newv_lo -= 6; }
	newv = newv_hi + newv_lo;
	cflg = (newv & 0x1F0) > 0x90;
	if (cflg) newv -= 0x60;
	SET_CFLG (cflg);
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s8)(newv)) == 0));
	x_put_byte (srca, newv);
}}}}	m68k_incpci (2);
return;
}

/* NBCD.B -(An) */
void REGPARAM2 CPUFUNC(op_4820_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 17;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = x_get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_u16 newv_lo = - (src & 0xF) - (GET_XFLG () ? 1 : 0);
	uae_u16 newv_hi = - (src & 0xF0);
	uae_u16 newv;
	int cflg;
	if (newv_lo > 9) { newv_lo -= 6; }
	newv = newv_hi + newv_lo;
	cflg = (newv & 0x1F0) > 0x90;
	if (cflg) newv -= 0x60;
	SET_CFLG (cflg);
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s8)(newv)) == 0));
	x_put_byte (srca, newv);
}}}}	m68k_incpci (2);
return;
}

/* NBCD.B (d16,An) */
void REGPARAM2 CPUFUNC(op_4828_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 17;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uae_u16 newv_lo = - (src & 0xF) - (GET_XFLG () ? 1 : 0);
	uae_u16 newv_hi = - (src & 0xF0);
	uae_u16 newv;
	int cflg;
	if (newv_lo > 9) { newv_lo -= 6; }
	newv = newv_hi + newv_lo;
	cflg = (newv & 0x1F0) > 0x90;
	if (cflg) newv -= 0x60;
	SET_CFLG (cflg);
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s8)(newv)) == 0));
	x_put_byte (srca, newv);
}}}}	m68k_incpci (4);
return;
}

/* NBCD.B (d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_4830_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 17;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s8 src = x_get_byte (srca);
{	uae_u16 newv_lo = - (src & 0xF) - (GET_XFLG () ? 1 : 0);
	uae_u16 newv_hi = - (src & 0xF0);
	uae_u16 newv;
	int cflg;
	if (newv_lo > 9) { newv_lo -= 6; }
	newv = newv_hi + newv_lo;
	cflg = (newv & 0x1F0) > 0x90;
	if (cflg) newv -= 0x60;
	SET_CFLG (cflg);
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s8)(newv)) == 0));
	x_put_byte (srca, newv);
}}}}}return;
}

/* NBCD.B (xxx).W */
void REGPARAM2 CPUFUNC(op_4838_24)(uae_u32 opcode)
{
	OpcodeFamily = 17;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uae_u16 newv_lo = - (src & 0xF) - (GET_XFLG () ? 1 : 0);
	uae_u16 newv_hi = - (src & 0xF0);
	uae_u16 newv;
	int cflg;
	if (newv_lo > 9) { newv_lo -= 6; }
	newv = newv_hi + newv_lo;
	cflg = (newv & 0x1F0) > 0x90;
	if (cflg) newv -= 0x60;
	SET_CFLG (cflg);
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s8)(newv)) == 0));
	x_put_byte (srca, newv);
}}}}	m68k_incpci (4);
return;
}

/* NBCD.B (xxx).L */
void REGPARAM2 CPUFUNC(op_4839_24)(uae_u32 opcode)
{
	OpcodeFamily = 17;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uae_u16 newv_lo = - (src & 0xF) - (GET_XFLG () ? 1 : 0);
	uae_u16 newv_hi = - (src & 0xF0);
	uae_u16 newv;
	int cflg;
	if (newv_lo > 9) { newv_lo -= 6; }
	newv = newv_hi + newv_lo;
	cflg = (newv & 0x1F0) > 0x90;
	if (cflg) newv -= 0x60;
	SET_CFLG (cflg);
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s8)(newv)) == 0));
	x_put_byte (srca, newv);
}}}}	m68k_incpci (6);
return;
}

/* SWAP.W Dn */
void REGPARAM2 CPUFUNC(op_4840_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 34;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uae_u32 dst = ((src >> 16)&0xFFFF) | ((src&0xFFFF)<<16);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(dst)) == 0);
	SET_NFLG (((uae_s32)(dst)) < 0);
	m68k_dreg (regs, srcreg) = (dst);
}}}	m68k_incpci (2);
return;
}

/* BKPTQ.L #<data> */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_4848_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 99;
{	m68k_incpci (2);
	op_illg (opcode);
}return;
}

#endif
/* PEA.L (An) */
void REGPARAM2 CPUFUNC(op_4850_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 57;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, 7) - 4;
	m68k_areg (regs, 7) = dsta;
	x_put_long (dsta, srca);
}}}	m68k_incpci (2);
return;
}

/* PEA.L (d16,An) */
void REGPARAM2 CPUFUNC(op_4868_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 57;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, 7) - 4;
	m68k_areg (regs, 7) = dsta;
	x_put_long (dsta, srca);
}}}	m68k_incpci (4);
return;
}

/* PEA.L (d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_4870_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 57;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uaecptr dsta;
	dsta = m68k_areg (regs, 7) - 4;
	m68k_areg (regs, 7) = dsta;
	x_put_long (dsta, srca);
}}}}return;
}

/* PEA.L (xxx).W */
void REGPARAM2 CPUFUNC(op_4878_24)(uae_u32 opcode)
{
	OpcodeFamily = 57;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, 7) - 4;
	m68k_areg (regs, 7) = dsta;
	x_put_long (dsta, srca);
}}}	m68k_incpci (4);
return;
}

/* PEA.L (xxx).L */
void REGPARAM2 CPUFUNC(op_4879_24)(uae_u32 opcode)
{
	OpcodeFamily = 57;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, 7) - 4;
	m68k_areg (regs, 7) = dsta;
	x_put_long (dsta, srca);
}}}	m68k_incpci (6);
return;
}

/* PEA.L (d16,PC) */
void REGPARAM2 CPUFUNC(op_487a_24)(uae_u32 opcode)
{
	OpcodeFamily = 57;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, 7) - 4;
	m68k_areg (regs, 7) = dsta;
	x_put_long (dsta, srca);
}}}	m68k_incpci (4);
return;
}

/* PEA.L (d8,PC,Xn) */
void REGPARAM2 CPUFUNC(op_487b_24)(uae_u32 opcode)
{
	OpcodeFamily = 57;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uaecptr dsta;
	dsta = m68k_areg (regs, 7) - 4;
	m68k_areg (regs, 7) = dsta;
	x_put_long (dsta, srca);
}}}}return;
}

/* EXT.W Dn */
void REGPARAM2 CPUFUNC(op_4880_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 36;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uae_u16 dst = (uae_s16)(uae_s8)src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(dst)) == 0);
	SET_NFLG (((uae_s16)(dst)) < 0);
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xffff) | ((dst) & 0xffff);
}}}	m68k_incpci (2);
return;
}

/* MVMLE.W #<data>.W,(An) */
void REGPARAM2 CPUFUNC(op_4890_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 38;
{	uae_u16 mask = get_iword_cache_040 (2);
{	uaecptr srca;
	srca = m68k_areg (regs, dstreg);
{	uae_u16 dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
	while (dmask) { x_put_word (srca, m68k_dreg (regs, movem_index1[dmask])); srca += 2; dmask = movem_next[dmask]; }
	while (amask) { x_put_word (srca, m68k_areg (regs, movem_index1[amask])); srca += 2; amask = movem_next[amask]; }
}}}	m68k_incpci (4);
return;
}

/* MVMLE.W #<data>.W,-(An) */
void REGPARAM2 CPUFUNC(op_48a0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 38;
{	uae_u16 mask = get_iword_cache_040 (2);
{	uaecptr srca;
	srca = m68k_areg (regs, dstreg) - 0;
{	uae_u16 amask = mask & 0xff, dmask = (mask >> 8) & 0xff;
	int type = get_cpu_model () >= 68020;
	while (amask) {
		srca -= 2;
		if (!type || movem_index2[amask] != dstreg)
			x_put_word (srca, m68k_areg (regs, movem_index2[amask]));
		else
			x_put_word (srca, m68k_areg (regs, movem_index2[amask]) - 2);
		amask = movem_next[amask];
	}
	while (dmask) { srca -= 2; x_put_word (srca, m68k_dreg (regs, movem_index2[dmask])); dmask = movem_next[dmask]; }
	m68k_areg (regs, dstreg) = srca;
}}}	m68k_incpci (4);
return;
}

/* MVMLE.W #<data>.W,(d16,An) */
void REGPARAM2 CPUFUNC(op_48a8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 38;
{	uae_u16 mask = get_iword_cache_040 (2);
{	uaecptr srca;
	srca = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_u16 dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
	while (dmask) { x_put_word (srca, m68k_dreg (regs, movem_index1[dmask])); srca += 2; dmask = movem_next[dmask]; }
	while (amask) { x_put_word (srca, m68k_areg (regs, movem_index1[amask])); srca += 2; amask = movem_next[amask]; }
}}}	m68k_incpci (6);
return;
}

/* MVMLE.W #<data>.W,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_48b0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 38;
{	uae_u16 mask = get_iword_cache_040 (2);
{	uaecptr srca;
	m68k_incpci (4);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_u16 dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
	while (dmask) { x_put_word (srca, m68k_dreg (regs, movem_index1[dmask])); srca += 2; dmask = movem_next[dmask]; }
	while (amask) { x_put_word (srca, m68k_areg (regs, movem_index1[amask])); srca += 2; amask = movem_next[amask]; }
}}}}return;
}

/* MVMLE.W #<data>.W,(xxx).W */
void REGPARAM2 CPUFUNC(op_48b8_24)(uae_u32 opcode)
{
	OpcodeFamily = 38;
{	uae_u16 mask = get_iword_cache_040 (2);
{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_u16 dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
	while (dmask) { x_put_word (srca, m68k_dreg (regs, movem_index1[dmask])); srca += 2; dmask = movem_next[dmask]; }
	while (amask) { x_put_word (srca, m68k_areg (regs, movem_index1[amask])); srca += 2; amask = movem_next[amask]; }
}}}	m68k_incpci (6);
return;
}

/* MVMLE.W #<data>.W,(xxx).L */
void REGPARAM2 CPUFUNC(op_48b9_24)(uae_u32 opcode)
{
	OpcodeFamily = 38;
{	uae_u16 mask = get_iword_cache_040 (2);
{	uaecptr srca;
	srca = get_ilong_cache_040 (4);
{	uae_u16 dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
	while (dmask) { x_put_word (srca, m68k_dreg (regs, movem_index1[dmask])); srca += 2; dmask = movem_next[dmask]; }
	while (amask) { x_put_word (srca, m68k_areg (regs, movem_index1[amask])); srca += 2; amask = movem_next[amask]; }
}}}	m68k_incpci (8);
return;
}

/* EXT.L Dn */
void REGPARAM2 CPUFUNC(op_48c0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 36;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uae_u32 dst = (uae_s32)(uae_s16)src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(dst)) == 0);
	SET_NFLG (((uae_s32)(dst)) < 0);
	m68k_dreg (regs, srcreg) = (dst);
}}}	m68k_incpci (2);
return;
}

/* MVMLE.L #<data>.W,(An) */
void REGPARAM2 CPUFUNC(op_48d0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 38;
{	uae_u16 mask = get_iword_cache_040 (2);
{	uaecptr srca;
	srca = m68k_areg (regs, dstreg);
{	uae_u16 dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
	while (dmask) { x_put_long (srca, m68k_dreg (regs, movem_index1[dmask])); srca += 4; dmask = movem_next[dmask]; }
	while (amask) { x_put_long (srca, m68k_areg (regs, movem_index1[amask])); srca += 4; amask = movem_next[amask]; }
}}}	m68k_incpci (4);
return;
}

/* MVMLE.L #<data>.W,-(An) */
void REGPARAM2 CPUFUNC(op_48e0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 38;
{	uae_u16 mask = get_iword_cache_040 (2);
{	uaecptr srca;
	srca = m68k_areg (regs, dstreg) - 0;
{	uae_u16 amask = mask & 0xff, dmask = (mask >> 8) & 0xff;
	int type = get_cpu_model () >= 68020;
	while (amask) {
		srca -= 4;
		if (!type || movem_index2[amask] != dstreg)
			x_put_long (srca, m68k_areg (regs, movem_index2[amask]));
		else
			x_put_long (srca, m68k_areg (regs, movem_index2[amask]) - 4);
		amask = movem_next[amask];
	}
	while (dmask) { srca -= 4; x_put_long (srca, m68k_dreg (regs, movem_index2[dmask])); dmask = movem_next[dmask]; }
	m68k_areg (regs, dstreg) = srca;
}}}	m68k_incpci (4);
return;
}

/* MVMLE.L #<data>.W,(d16,An) */
void REGPARAM2 CPUFUNC(op_48e8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 38;
{	uae_u16 mask = get_iword_cache_040 (2);
{	uaecptr srca;
	srca = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_u16 dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
	while (dmask) { x_put_long (srca, m68k_dreg (regs, movem_index1[dmask])); srca += 4; dmask = movem_next[dmask]; }
	while (amask) { x_put_long (srca, m68k_areg (regs, movem_index1[amask])); srca += 4; amask = movem_next[amask]; }
}}}	m68k_incpci (6);
return;
}

/* MVMLE.L #<data>.W,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_48f0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 38;
{	uae_u16 mask = get_iword_cache_040 (2);
{	uaecptr srca;
	m68k_incpci (4);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_u16 dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
	while (dmask) { x_put_long (srca, m68k_dreg (regs, movem_index1[dmask])); srca += 4; dmask = movem_next[dmask]; }
	while (amask) { x_put_long (srca, m68k_areg (regs, movem_index1[amask])); srca += 4; amask = movem_next[amask]; }
}}}}return;
}

/* MVMLE.L #<data>.W,(xxx).W */
void REGPARAM2 CPUFUNC(op_48f8_24)(uae_u32 opcode)
{
	OpcodeFamily = 38;
{	uae_u16 mask = get_iword_cache_040 (2);
{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_u16 dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
	while (dmask) { x_put_long (srca, m68k_dreg (regs, movem_index1[dmask])); srca += 4; dmask = movem_next[dmask]; }
	while (amask) { x_put_long (srca, m68k_areg (regs, movem_index1[amask])); srca += 4; amask = movem_next[amask]; }
}}}	m68k_incpci (6);
return;
}

/* MVMLE.L #<data>.W,(xxx).L */
void REGPARAM2 CPUFUNC(op_48f9_24)(uae_u32 opcode)
{
	OpcodeFamily = 38;
{	uae_u16 mask = get_iword_cache_040 (2);
{	uaecptr srca;
	srca = get_ilong_cache_040 (4);
{	uae_u16 dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
	while (dmask) { x_put_long (srca, m68k_dreg (regs, movem_index1[dmask])); srca += 4; dmask = movem_next[dmask]; }
	while (amask) { x_put_long (srca, m68k_areg (regs, movem_index1[amask])); srca += 4; amask = movem_next[amask]; }
}}}	m68k_incpci (8);
return;
}

/* EXT.B Dn */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_49c0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 36;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uae_u32 dst = (uae_s32)(uae_s8)src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(dst)) == 0);
	SET_NFLG (((uae_s32)(dst)) < 0);
	m68k_dreg (regs, srcreg) = (dst);
}}}	m68k_incpci (2);
return;
}

#endif
/* TST.B Dn */
void REGPARAM2 CPUFUNC(op_4a00_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 20;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
}}	m68k_incpci (2);
return;
}

/* TST.B (An) */
void REGPARAM2 CPUFUNC(op_4a10_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 20;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s8 src = x_get_byte (srca);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
}}}	m68k_incpci (2);
return;
}

/* TST.B (An)+ */
void REGPARAM2 CPUFUNC(op_4a18_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 20;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s8 src = x_get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
}}}	m68k_incpci (2);
return;
}

/* TST.B -(An) */
void REGPARAM2 CPUFUNC(op_4a20_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 20;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = x_get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
}}}	m68k_incpci (2);
return;
}

/* TST.B (d16,An) */
void REGPARAM2 CPUFUNC(op_4a28_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 20;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
}}}	m68k_incpci (4);
return;
}

/* TST.B (d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_4a30_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 20;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s8 src = x_get_byte (srca);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
}}}}return;
}

/* TST.B (xxx).W */
void REGPARAM2 CPUFUNC(op_4a38_24)(uae_u32 opcode)
{
	OpcodeFamily = 20;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
}}}	m68k_incpci (4);
return;
}

/* TST.B (xxx).L */
void REGPARAM2 CPUFUNC(op_4a39_24)(uae_u32 opcode)
{
	OpcodeFamily = 20;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
}}}	m68k_incpci (6);
return;
}

/* TST.B (d16,PC) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_4a3a_24)(uae_u32 opcode)
{
	OpcodeFamily = 20;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
}}}	m68k_incpci (4);
return;
}

#endif
/* TST.B (d8,PC,Xn) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_4a3b_24)(uae_u32 opcode)
{
	OpcodeFamily = 20;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s8 src = x_get_byte (srca);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
}}}}return;
}

#endif
/* TST.B #<data>.B */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_4a3c_24)(uae_u32 opcode)
{
	OpcodeFamily = 20;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
}}	m68k_incpci (4);
return;
}

#endif
/* TST.W Dn */
void REGPARAM2 CPUFUNC(op_4a40_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 20;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
}}	m68k_incpci (2);
return;
}

/* TST.W An */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_4a48_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 20;
{{	uae_s16 src = m68k_areg (regs, srcreg);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
}}	m68k_incpci (2);
return;
}

#endif
/* TST.W (An) */
void REGPARAM2 CPUFUNC(op_4a50_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 20;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
}}}	m68k_incpci (2);
return;
}

/* TST.W (An)+ */
void REGPARAM2 CPUFUNC(op_4a58_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 20;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) += 2;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
}}}	m68k_incpci (2);
return;
}

/* TST.W -(An) */
void REGPARAM2 CPUFUNC(op_4a60_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 20;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) = srca;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
}}}	m68k_incpci (2);
return;
}

/* TST.W (d16,An) */
void REGPARAM2 CPUFUNC(op_4a68_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 20;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
}}}	m68k_incpci (4);
return;
}

/* TST.W (d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_4a70_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 20;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s16 src = x_get_word (srca);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
}}}}return;
}

/* TST.W (xxx).W */
void REGPARAM2 CPUFUNC(op_4a78_24)(uae_u32 opcode)
{
	OpcodeFamily = 20;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
}}}	m68k_incpci (4);
return;
}

/* TST.W (xxx).L */
void REGPARAM2 CPUFUNC(op_4a79_24)(uae_u32 opcode)
{
	OpcodeFamily = 20;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
}}}	m68k_incpci (6);
return;
}

/* TST.W (d16,PC) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_4a7a_24)(uae_u32 opcode)
{
	OpcodeFamily = 20;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
}}}	m68k_incpci (4);
return;
}

#endif
/* TST.W (d8,PC,Xn) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_4a7b_24)(uae_u32 opcode)
{
	OpcodeFamily = 20;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s16 src = x_get_word (srca);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
}}}}return;
}

#endif
/* TST.W #<data>.W */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_4a7c_24)(uae_u32 opcode)
{
	OpcodeFamily = 20;
{{	uae_s16 src = get_iword_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
}}	m68k_incpci (4);
return;
}

#endif
/* TST.L Dn */
void REGPARAM2 CPUFUNC(op_4a80_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 20;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
}}	m68k_incpci (2);
return;
}

/* TST.L An */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_4a88_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 20;
{{	uae_s32 src = m68k_areg (regs, srcreg);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
}}	m68k_incpci (2);
return;
}

#endif
/* TST.L (An) */
void REGPARAM2 CPUFUNC(op_4a90_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 20;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s32 src = x_get_long (srca);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
}}}	m68k_incpci (2);
return;
}

/* TST.L (An)+ */
void REGPARAM2 CPUFUNC(op_4a98_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 20;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, srcreg) += 4;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
}}}	m68k_incpci (2);
return;
}

/* TST.L -(An) */
void REGPARAM2 CPUFUNC(op_4aa0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 20;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, srcreg) = srca;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
}}}	m68k_incpci (2);
return;
}

/* TST.L (d16,An) */
void REGPARAM2 CPUFUNC(op_4aa8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 20;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
}}}	m68k_incpci (4);
return;
}

/* TST.L (d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_4ab0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 20;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s32 src = x_get_long (srca);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
}}}}return;
}

/* TST.L (xxx).W */
void REGPARAM2 CPUFUNC(op_4ab8_24)(uae_u32 opcode)
{
	OpcodeFamily = 20;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
}}}	m68k_incpci (4);
return;
}

/* TST.L (xxx).L */
void REGPARAM2 CPUFUNC(op_4ab9_24)(uae_u32 opcode)
{
	OpcodeFamily = 20;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
}}}	m68k_incpci (6);
return;
}

/* TST.L (d16,PC) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_4aba_24)(uae_u32 opcode)
{
	OpcodeFamily = 20;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
}}}	m68k_incpci (4);
return;
}

#endif
/* TST.L (d8,PC,Xn) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_4abb_24)(uae_u32 opcode)
{
	OpcodeFamily = 20;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s32 src = x_get_long (srca);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
}}}}return;
}

#endif
/* TST.L #<data>.L */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_4abc_24)(uae_u32 opcode)
{
	OpcodeFamily = 20;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
}}	m68k_incpci (6);
return;
}

#endif
/* TAS.B Dn */
void REGPARAM2 CPUFUNC(op_4ac0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 98;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	src |= 0x80;
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xff) | ((src) & 0xff);
}}	m68k_incpci (2);
return;
}

/* TAS.B (An) */
void REGPARAM2 CPUFUNC(op_4ad0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 98;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s8 src = x_get_byte (srca);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	src |= 0x80;
	x_put_byte (srca, src);
}}}	m68k_incpci (2);
return;
}

/* TAS.B (An)+ */
void REGPARAM2 CPUFUNC(op_4ad8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 98;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s8 src = x_get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	src |= 0x80;
	x_put_byte (srca, src);
}}}	m68k_incpci (2);
return;
}

/* TAS.B -(An) */
void REGPARAM2 CPUFUNC(op_4ae0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 98;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = x_get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	src |= 0x80;
	x_put_byte (srca, src);
}}}	m68k_incpci (2);
return;
}

/* TAS.B (d16,An) */
void REGPARAM2 CPUFUNC(op_4ae8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 98;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	src |= 0x80;
	x_put_byte (srca, src);
}}}	m68k_incpci (4);
return;
}

/* TAS.B (d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_4af0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 98;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s8 src = x_get_byte (srca);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	src |= 0x80;
	x_put_byte (srca, src);
}}}}return;
}

/* TAS.B (xxx).W */
void REGPARAM2 CPUFUNC(op_4af8_24)(uae_u32 opcode)
{
	OpcodeFamily = 98;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	src |= 0x80;
	x_put_byte (srca, src);
}}}	m68k_incpci (4);
return;
}

/* TAS.B (xxx).L */
void REGPARAM2 CPUFUNC(op_4af9_24)(uae_u32 opcode)
{
	OpcodeFamily = 98;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	src |= 0x80;
	x_put_byte (srca, src);
}}}	m68k_incpci (6);
return;
}

/* MULL.L #<data>.W,Dn */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_4c00_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 87;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	m68k_incpci (4);
	if (!m68k_mull(opcode, dst, extra)) goto l_240847;
}}}l_240847: ;
return;
}

#endif
/* MULL.L #<data>.W,(An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_4c10_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 87;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s32 dst = x_get_long (dsta);
	m68k_incpci (4);
	if (!m68k_mull(opcode, dst, extra)) goto l_240848;
}}}}l_240848: ;
return;
}

#endif
/* MULL.L #<data>.W,(An)+ */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_4c18_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 87;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s32 dst = x_get_long (dsta);
	m68k_areg (regs, dstreg) += 4;
	m68k_incpci (4);
	if (!m68k_mull(opcode, dst, extra)) goto l_240849;
}}}}l_240849: ;
return;
}

#endif
/* MULL.L #<data>.W,-(An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_4c20_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 87;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
{	uae_s32 dst = x_get_long (dsta);
	m68k_areg (regs, dstreg) = dsta;
	m68k_incpci (4);
	if (!m68k_mull(opcode, dst, extra)) goto l_240850;
}}}}l_240850: ;
return;
}

#endif
/* MULL.L #<data>.W,(d16,An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_4c28_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 87;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s32 dst = x_get_long (dsta);
	m68k_incpci (6);
	if (!m68k_mull(opcode, dst, extra)) goto l_240851;
}}}}l_240851: ;
return;
}

#endif
/* MULL.L #<data>.W,(d8,An,Xn) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_4c30_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 87;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	m68k_incpci (4);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s32 dst = x_get_long (dsta);
	if (!m68k_mull(opcode, dst, extra)) goto l_240852;
}}}}}l_240852: ;
return;
}

#endif
/* MULL.L #<data>.W,(xxx).W */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_4c38_24)(uae_u32 opcode)
{
	OpcodeFamily = 87;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s32 dst = x_get_long (dsta);
	m68k_incpci (6);
	if (!m68k_mull(opcode, dst, extra)) goto l_240853;
}}}}l_240853: ;
return;
}

#endif
/* MULL.L #<data>.W,(xxx).L */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_4c39_24)(uae_u32 opcode)
{
	OpcodeFamily = 87;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (4);
{	uae_s32 dst = x_get_long (dsta);
	m68k_incpci (8);
	if (!m68k_mull(opcode, dst, extra)) goto l_240854;
}}}}l_240854: ;
return;
}

#endif
/* MULL.L #<data>.W,(d16,PC) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_4c3a_24)(uae_u32 opcode)
{
	uae_u32 dstreg = 2;
	OpcodeFamily = 87;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_getpci () + 4;
	dsta += (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s32 dst = x_get_long (dsta);
	m68k_incpci (6);
	if (!m68k_mull(opcode, dst, extra)) goto l_240855;
}}}}l_240855: ;
return;
}

#endif
/* MULL.L #<data>.W,(d8,PC,Xn) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_4c3b_24)(uae_u32 opcode)
{
	uae_u32 dstreg = 3;
	OpcodeFamily = 87;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr tmppc;
	uaecptr dsta;
	m68k_incpci (4);
{	tmppc = m68k_getpci ();
	dsta = x_get_disp_ea_040 (tmppc, 0);
{	uae_s32 dst = x_get_long (dsta);
	if (!m68k_mull(opcode, dst, extra)) goto l_240856;
}}}}}l_240856: ;
return;
}

#endif
/* MULL.L #<data>.W,#<data>.L */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_4c3c_24)(uae_u32 opcode)
{
	OpcodeFamily = 87;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uae_s32 dst;
	dst = get_ilong_cache_040 (4);
	m68k_incpci (8);
	if (!m68k_mull(opcode, dst, extra)) goto l_240857;
}}}l_240857: ;
return;
}

#endif
/* DIVL.L #<data>.W,Dn */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_4c40_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 86;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	m68k_incpci (4);
	if (!m68k_divl(opcode, dst, extra)) goto l_240858;
}}}l_240858: ;
return;
}

#endif
/* DIVL.L #<data>.W,(An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_4c50_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 86;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s32 dst = x_get_long (dsta);
	m68k_incpci (4);
	if (!m68k_divl(opcode, dst, extra)) goto l_240859;
}}}}l_240859: ;
return;
}

#endif
/* DIVL.L #<data>.W,(An)+ */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_4c58_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 86;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s32 dst = x_get_long (dsta);
	m68k_areg (regs, dstreg) += 4;
	m68k_incpci (4);
	if (!m68k_divl(opcode, dst, extra)) goto l_240860;
}}}}l_240860: ;
return;
}

#endif
/* DIVL.L #<data>.W,-(An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_4c60_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 86;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
{	uae_s32 dst = x_get_long (dsta);
	m68k_areg (regs, dstreg) = dsta;
	m68k_incpci (4);
	if (!m68k_divl(opcode, dst, extra)) goto l_240861;
}}}}l_240861: ;
return;
}

#endif
/* DIVL.L #<data>.W,(d16,An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_4c68_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 86;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s32 dst = x_get_long (dsta);
	m68k_incpci (6);
	if (!m68k_divl(opcode, dst, extra)) goto l_240862;
}}}}l_240862: ;
return;
}

#endif
/* DIVL.L #<data>.W,(d8,An,Xn) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_4c70_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 86;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	m68k_incpci (4);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s32 dst = x_get_long (dsta);
	if (!m68k_divl(opcode, dst, extra)) goto l_240863;
}}}}}l_240863: ;
return;
}

#endif
/* DIVL.L #<data>.W,(xxx).W */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_4c78_24)(uae_u32 opcode)
{
	OpcodeFamily = 86;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s32 dst = x_get_long (dsta);
	m68k_incpci (6);
	if (!m68k_divl(opcode, dst, extra)) goto l_240864;
}}}}l_240864: ;
return;
}

#endif
/* DIVL.L #<data>.W,(xxx).L */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_4c79_24)(uae_u32 opcode)
{
	OpcodeFamily = 86;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (4);
{	uae_s32 dst = x_get_long (dsta);
	m68k_incpci (8);
	if (!m68k_divl(opcode, dst, extra)) goto l_240865;
}}}}l_240865: ;
return;
}

#endif
/* DIVL.L #<data>.W,(d16,PC) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_4c7a_24)(uae_u32 opcode)
{
	uae_u32 dstreg = 2;
	OpcodeFamily = 86;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_getpci () + 4;
	dsta += (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_s32 dst = x_get_long (dsta);
	m68k_incpci (6);
	if (!m68k_divl(opcode, dst, extra)) goto l_240866;
}}}}l_240866: ;
return;
}

#endif
/* DIVL.L #<data>.W,(d8,PC,Xn) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_4c7b_24)(uae_u32 opcode)
{
	uae_u32 dstreg = 3;
	OpcodeFamily = 86;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr tmppc;
	uaecptr dsta;
	m68k_incpci (4);
{	tmppc = m68k_getpci ();
	dsta = x_get_disp_ea_040 (tmppc, 0);
{	uae_s32 dst = x_get_long (dsta);
	if (!m68k_divl(opcode, dst, extra)) goto l_240867;
}}}}}l_240867: ;
return;
}

#endif
/* DIVL.L #<data>.W,#<data>.L */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_4c7c_24)(uae_u32 opcode)
{
	OpcodeFamily = 86;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uae_s32 dst;
	dst = get_ilong_cache_040 (4);
	m68k_incpci (8);
	if (!m68k_divl(opcode, dst, extra)) goto l_240868;
}}}l_240868: ;
return;
}

#endif
/* MVMEL.W #<data>.W,(An) */
void REGPARAM2 CPUFUNC(op_4c90_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 37;
{	uae_u16 mask = get_iword_cache_040 (2);
	uae_u32 dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{	uaecptr srca;
	srca = m68k_areg (regs, dstreg);
{	while (dmask) {
		m68k_dreg (regs, movem_index1[dmask]) = (uae_s32)(uae_s16)x_get_word (srca); srca += 2; dmask = movem_next[dmask];
	}
	while (amask) {
		m68k_areg (regs, movem_index1[amask]) = (uae_s32)(uae_s16)x_get_word (srca); srca += 2; amask = movem_next[amask];
	}
}}}	m68k_incpci (4);
return;
}

/* MVMEL.W #<data>.W,(An)+ */
void REGPARAM2 CPUFUNC(op_4c98_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 37;
{	uae_u16 mask = get_iword_cache_040 (2);
	uae_u32 dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{	uaecptr srca;
	srca = m68k_areg (regs, dstreg);
{	while (dmask) {
		m68k_dreg (regs, movem_index1[dmask]) = (uae_s32)(uae_s16)x_get_word (srca); srca += 2; dmask = movem_next[dmask];
	}
	while (amask) {
		m68k_areg (regs, movem_index1[amask]) = (uae_s32)(uae_s16)x_get_word (srca); srca += 2; amask = movem_next[amask];
	}
	m68k_areg (regs, dstreg) = srca;
}}}	m68k_incpci (4);
return;
}

/* MVMEL.W #<data>.W,(d16,An) */
void REGPARAM2 CPUFUNC(op_4ca8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 37;
{	uae_u16 mask = get_iword_cache_040 (2);
	uae_u32 dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{	uaecptr srca;
	srca = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	while (dmask) {
		m68k_dreg (regs, movem_index1[dmask]) = (uae_s32)(uae_s16)x_get_word (srca); srca += 2; dmask = movem_next[dmask];
	}
	while (amask) {
		m68k_areg (regs, movem_index1[amask]) = (uae_s32)(uae_s16)x_get_word (srca); srca += 2; amask = movem_next[amask];
	}
}}}	m68k_incpci (6);
return;
}

/* MVMEL.W #<data>.W,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_4cb0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 37;
{	uae_u16 mask = get_iword_cache_040 (2);
	uae_u32 dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{	uaecptr srca;
	m68k_incpci (4);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	while (dmask) {
		m68k_dreg (regs, movem_index1[dmask]) = (uae_s32)(uae_s16)x_get_word (srca); srca += 2; dmask = movem_next[dmask];
	}
	while (amask) {
		m68k_areg (regs, movem_index1[amask]) = (uae_s32)(uae_s16)x_get_word (srca); srca += 2; amask = movem_next[amask];
	}
}}}}return;
}

/* MVMEL.W #<data>.W,(xxx).W */
void REGPARAM2 CPUFUNC(op_4cb8_24)(uae_u32 opcode)
{
	OpcodeFamily = 37;
{	uae_u16 mask = get_iword_cache_040 (2);
	uae_u32 dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	while (dmask) {
		m68k_dreg (regs, movem_index1[dmask]) = (uae_s32)(uae_s16)x_get_word (srca); srca += 2; dmask = movem_next[dmask];
	}
	while (amask) {
		m68k_areg (regs, movem_index1[amask]) = (uae_s32)(uae_s16)x_get_word (srca); srca += 2; amask = movem_next[amask];
	}
}}}	m68k_incpci (6);
return;
}

/* MVMEL.W #<data>.W,(xxx).L */
void REGPARAM2 CPUFUNC(op_4cb9_24)(uae_u32 opcode)
{
	OpcodeFamily = 37;
{	uae_u16 mask = get_iword_cache_040 (2);
	uae_u32 dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{	uaecptr srca;
	srca = get_ilong_cache_040 (4);
{	while (dmask) {
		m68k_dreg (regs, movem_index1[dmask]) = (uae_s32)(uae_s16)x_get_word (srca); srca += 2; dmask = movem_next[dmask];
	}
	while (amask) {
		m68k_areg (regs, movem_index1[amask]) = (uae_s32)(uae_s16)x_get_word (srca); srca += 2; amask = movem_next[amask];
	}
}}}	m68k_incpci (8);
return;
}

/* MVMEL.W #<data>.W,(d16,PC) */
void REGPARAM2 CPUFUNC(op_4cba_24)(uae_u32 opcode)
{
	uae_u32 dstreg = 2;
	OpcodeFamily = 37;
{	uae_u16 mask = get_iword_cache_040 (2);
	uae_u32 dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{	uaecptr srca;
	srca = m68k_getpci () + 4;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	while (dmask) {
		m68k_dreg (regs, movem_index1[dmask]) = (uae_s32)(uae_s16)x_get_word (srca); srca += 2; dmask = movem_next[dmask];
	}
	while (amask) {
		m68k_areg (regs, movem_index1[amask]) = (uae_s32)(uae_s16)x_get_word (srca); srca += 2; amask = movem_next[amask];
	}
}}}	m68k_incpci (6);
return;
}

/* MVMEL.W #<data>.W,(d8,PC,Xn) */
void REGPARAM2 CPUFUNC(op_4cbb_24)(uae_u32 opcode)
{
	uae_u32 dstreg = 3;
	OpcodeFamily = 37;
{	uae_u16 mask = get_iword_cache_040 (2);
	uae_u32 dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (4);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	while (dmask) {
		m68k_dreg (regs, movem_index1[dmask]) = (uae_s32)(uae_s16)x_get_word (srca); srca += 2; dmask = movem_next[dmask];
	}
	while (amask) {
		m68k_areg (regs, movem_index1[amask]) = (uae_s32)(uae_s16)x_get_word (srca); srca += 2; amask = movem_next[amask];
	}
}}}}return;
}

/* MVMEL.L #<data>.W,(An) */
void REGPARAM2 CPUFUNC(op_4cd0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 37;
{	uae_u16 mask = get_iword_cache_040 (2);
	uae_u32 dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{	uaecptr srca;
	srca = m68k_areg (regs, dstreg);
{	while (dmask) {
		m68k_dreg (regs, movem_index1[dmask]) = x_get_long (srca); srca += 4; dmask = movem_next[dmask];
	}
	while (amask) {
		m68k_areg (regs, movem_index1[amask]) = x_get_long (srca); srca += 4; amask = movem_next[amask];
	}
}}}	m68k_incpci (4);
return;
}

/* MVMEL.L #<data>.W,(An)+ */
void REGPARAM2 CPUFUNC(op_4cd8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 37;
{	uae_u16 mask = get_iword_cache_040 (2);
	uae_u32 dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{	uaecptr srca;
	srca = m68k_areg (regs, dstreg);
{	while (dmask) {
		m68k_dreg (regs, movem_index1[dmask]) = x_get_long (srca); srca += 4; dmask = movem_next[dmask];
	}
	while (amask) {
		m68k_areg (regs, movem_index1[amask]) = x_get_long (srca); srca += 4; amask = movem_next[amask];
	}
	m68k_areg (regs, dstreg) = srca;
}}}	m68k_incpci (4);
return;
}

/* MVMEL.L #<data>.W,(d16,An) */
void REGPARAM2 CPUFUNC(op_4ce8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 37;
{	uae_u16 mask = get_iword_cache_040 (2);
	uae_u32 dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{	uaecptr srca;
	srca = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	while (dmask) {
		m68k_dreg (regs, movem_index1[dmask]) = x_get_long (srca); srca += 4; dmask = movem_next[dmask];
	}
	while (amask) {
		m68k_areg (regs, movem_index1[amask]) = x_get_long (srca); srca += 4; amask = movem_next[amask];
	}
}}}	m68k_incpci (6);
return;
}

/* MVMEL.L #<data>.W,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_4cf0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 37;
{	uae_u16 mask = get_iword_cache_040 (2);
	uae_u32 dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{	uaecptr srca;
	m68k_incpci (4);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	while (dmask) {
		m68k_dreg (regs, movem_index1[dmask]) = x_get_long (srca); srca += 4; dmask = movem_next[dmask];
	}
	while (amask) {
		m68k_areg (regs, movem_index1[amask]) = x_get_long (srca); srca += 4; amask = movem_next[amask];
	}
}}}}return;
}

/* MVMEL.L #<data>.W,(xxx).W */
void REGPARAM2 CPUFUNC(op_4cf8_24)(uae_u32 opcode)
{
	OpcodeFamily = 37;
{	uae_u16 mask = get_iword_cache_040 (2);
	uae_u32 dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	while (dmask) {
		m68k_dreg (regs, movem_index1[dmask]) = x_get_long (srca); srca += 4; dmask = movem_next[dmask];
	}
	while (amask) {
		m68k_areg (regs, movem_index1[amask]) = x_get_long (srca); srca += 4; amask = movem_next[amask];
	}
}}}	m68k_incpci (6);
return;
}

/* MVMEL.L #<data>.W,(xxx).L */
void REGPARAM2 CPUFUNC(op_4cf9_24)(uae_u32 opcode)
{
	OpcodeFamily = 37;
{	uae_u16 mask = get_iword_cache_040 (2);
	uae_u32 dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{	uaecptr srca;
	srca = get_ilong_cache_040 (4);
{	while (dmask) {
		m68k_dreg (regs, movem_index1[dmask]) = x_get_long (srca); srca += 4; dmask = movem_next[dmask];
	}
	while (amask) {
		m68k_areg (regs, movem_index1[amask]) = x_get_long (srca); srca += 4; amask = movem_next[amask];
	}
}}}	m68k_incpci (8);
return;
}

/* MVMEL.L #<data>.W,(d16,PC) */
void REGPARAM2 CPUFUNC(op_4cfa_24)(uae_u32 opcode)
{
	uae_u32 dstreg = 2;
	OpcodeFamily = 37;
{	uae_u16 mask = get_iword_cache_040 (2);
	uae_u32 dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{	uaecptr srca;
	srca = m68k_getpci () + 4;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	while (dmask) {
		m68k_dreg (regs, movem_index1[dmask]) = x_get_long (srca); srca += 4; dmask = movem_next[dmask];
	}
	while (amask) {
		m68k_areg (regs, movem_index1[amask]) = x_get_long (srca); srca += 4; amask = movem_next[amask];
	}
}}}	m68k_incpci (6);
return;
}

/* MVMEL.L #<data>.W,(d8,PC,Xn) */
void REGPARAM2 CPUFUNC(op_4cfb_24)(uae_u32 opcode)
{
	uae_u32 dstreg = 3;
	OpcodeFamily = 37;
{	uae_u16 mask = get_iword_cache_040 (2);
	uae_u32 dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (4);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	while (dmask) {
		m68k_dreg (regs, movem_index1[dmask]) = x_get_long (srca); srca += 4; dmask = movem_next[dmask];
	}
	while (amask) {
		m68k_areg (regs, movem_index1[amask]) = x_get_long (srca); srca += 4; amask = movem_next[amask];
	}
}}}}return;
}

/* TRAPQ.L #<data> */
void REGPARAM2 CPUFUNC(op_4e40_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 15);
	OpcodeFamily = 39;
{{	uae_u32 src = srcreg;
	m68k_incpci (2);
	Exception (src + 32);
}}return;
}

/* LINK.W An,#<data>.W */
void REGPARAM2 CPUFUNC(op_4e50_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 47;
{{	uaecptr olda;
	olda = m68k_areg (regs, 7) - 4;
	m68k_areg (regs, 7) = olda;
{	uae_s32 src = m68k_areg (regs, srcreg);
{	uae_s16 offs = get_iword_cache_040 (2);
	x_put_long (olda, src);
	m68k_areg (regs, srcreg) = (m68k_areg (regs, 7));
	m68k_areg (regs, 7) += offs;
}}}}	m68k_incpci (4);
return;
}

/* UNLK.L An */
void REGPARAM2 CPUFUNC(op_4e58_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 48;
{{	uae_s32 src = m68k_areg (regs, srcreg);
	m68k_areg (regs, 7) = src;
{	uaecptr olda;
	olda = m68k_areg (regs, 7);
{	uae_s32 old = x_get_long (olda);
	m68k_areg (regs, 7) += 4;
	m68k_areg (regs, srcreg) = (old);
}}}}	m68k_incpci (2);
return;
}

/* MVR2USP.L An */
void REGPARAM2 CPUFUNC(op_4e60_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 40;
{if (!regs.s) { Exception (8); goto l_240888; }
{{	uae_s32 src = m68k_areg (regs, srcreg);
	regs.usp = src;
}}}	m68k_incpci (2);
l_240888: ;
return;
}

/* MVUSP2R.L An */
void REGPARAM2 CPUFUNC(op_4e68_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 41;
{if (!regs.s) { Exception (8); goto l_240889; }
{{	m68k_areg (regs, srcreg) = (regs.usp);
}}}	m68k_incpci (2);
l_240889: ;
return;
}

/* RESET.L  */
void REGPARAM2 CPUFUNC(op_4e70_24)(uae_u32 opcode)
{
	OpcodeFamily = 42;
{if (!regs.s) { Exception (8); goto l_240890; }
{	cpureset ();
	m68k_incpci (2);
}}l_240890: ;
return;
}

/* NOP.L  */
void REGPARAM2 CPUFUNC(op_4e71_24)(uae_u32 opcode)
{
	OpcodeFamily = 43;
{}	m68k_incpci (2);
return;
}

/* STOP.L #<data>.W */
void REGPARAM2 CPUFUNC(op_4e72_24)(uae_u32 opcode)
{
	OpcodeFamily = 44;
{if (!regs.s) { Exception (8); goto l_240892; }
{{	uae_s16 src = get_iword_cache_040 (2);
	regs.sr = src;
	MakeFromSR();
	m68k_setstopped ();
	m68k_incpci (4);
}}}l_240892: ;
return;
}

/* RTE.L  */
void REGPARAM2 CPUFUNC(op_4e73_24)(uae_u32 opcode)
{
	OpcodeFamily = 45;
{if (!regs.s) { Exception (8); goto l_240893; }
{	uae_u16 newsr; uae_u32 newpc;
	for (;;) {
		uaecptr a = m68k_areg (regs, 7);
		uae_u16 sr = x_get_word (a);
		uae_u32 pc = x_get_long (a + 2);
		uae_u16 format = x_get_word (a + 2 + 4);
		int frame = format >> 12;
		int offset = 8;
		newsr = sr; newpc = pc;
		if (frame == 0x0) { m68k_areg (regs, 7) += offset; break; }
		else if (frame == 0x1) { m68k_areg (regs, 7) += offset; }
		else if (frame == 0x2) { m68k_areg (regs, 7) += offset + 4; break; }
		else if (frame == 0x4) { m68k_areg (regs, 7) += offset + 8; break; }
		else if (frame == 0x7) { m68k_areg (regs, 7) += offset + 52; break; }
		else if (frame == 0x9) { m68k_areg (regs, 7) += offset + 12; break; }
		else if (frame == 0xa) { m68k_areg (regs, 7) += offset + 24; break; }
		else if (frame == 0xb) { m68k_areg (regs, 7) += offset + 84; break; }
		else { m68k_areg (regs, 7) += offset; Exception (14); goto l_240893; }
		regs.sr = newsr;
	MakeFromSR();
}
	regs.sr = newsr;
	MakeFromSR();
	if (newpc & 1) {
		exception3i (0x4E73, newpc);
		goto l_240893;
	}
	m68k_setpci (newpc);
}}l_240893: ;
return;
}

/* RTD.L #<data>.W */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_4e74_24)(uae_u32 opcode)
{
	OpcodeFamily = 46;
{{	uaecptr pca;
	pca = m68k_areg (regs, 7);
{	uae_s32 pc = x_get_long (pca);
	m68k_areg (regs, 7) += 4;
{	uae_s16 offs = get_iword_cache_040 (2);
	m68k_areg (regs, 7) += offs;
	if (pc & 1) {
		exception3i (0x4E74, pc);
		goto l_240894;
	}
	m68k_setpci (pc);
}}}}l_240894: ;
return;
}

#endif
/* RTS.L  */
void REGPARAM2 CPUFUNC(op_4e75_24)(uae_u32 opcode)
{
	OpcodeFamily = 49;
{	uaecptr pc = m68k_getpci ();
	m68k_do_rtsi ();
	if (m68k_getpci () & 1) {
		uaecptr faultpc = m68k_getpci ();
	m68k_setpci (pc);
		exception3i (0x4E75, faultpc);
		goto l_240895;
	}
}l_240895: ;
return;
}

/* TRAPV.L  */
void REGPARAM2 CPUFUNC(op_4e76_24)(uae_u32 opcode)
{
	OpcodeFamily = 50;
{	m68k_incpci (2);
	if (GET_VFLG ()) {
		Exception (7);
		goto l_240896;
	}
}l_240896: ;
return;
}

/* RTR.L  */
void REGPARAM2 CPUFUNC(op_4e77_24)(uae_u32 opcode)
{
	OpcodeFamily = 51;
{	uaecptr oldpc = m68k_getpci ();
	MakeSR ();
{	uaecptr sra;
	sra = m68k_areg (regs, 7);
{	uae_s16 sr = x_get_word (sra);
	m68k_areg (regs, 7) += 2;
{	uaecptr pca;
	pca = m68k_areg (regs, 7);
{	uae_s32 pc = x_get_long (pca);
	m68k_areg (regs, 7) += 4;
	regs.sr &= 0xFF00; sr &= 0xFF;
	regs.sr |= sr;
	m68k_setpci (pc);
	MakeFromSR();
	if (m68k_getpci () & 1) {
		uaecptr faultpc = m68k_getpci ();
	m68k_setpci (oldpc);
		exception3i (0x4E77, faultpc);
		goto l_240897;
	}
}}}}}l_240897: ;
return;
}

/* MOVEC2.L #<data>.W */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_4e7a_24)(uae_u32 opcode)
{
	OpcodeFamily = 82;
{if (!regs.s) { Exception (8); goto l_240898; }
{{	uae_s16 src = get_iword_cache_040 (2);
{	int regno = (src >> 12) & 15;
	uae_u32 *regp = regs.regs + regno;
	if (! m68k_movec2(src & 0xFFF, regp)) goto l_240898;
}}}}	m68k_incpci (4);
l_240898: ;
return;
}

#endif
/* MOVE2C.L #<data>.W */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_4e7b_24)(uae_u32 opcode)
{
	OpcodeFamily = 83;
{if (!regs.s) { Exception (8); goto l_240899; }
{{	uae_s16 src = get_iword_cache_040 (2);
{	int regno = (src >> 12) & 15;
	uae_u32 *regp = regs.regs + regno;
	if (! m68k_move2c(src & 0xFFF, regp)) goto l_240899;
}}}}	m68k_incpci (4);
l_240899: ;
return;
}

#endif
/* JSR.L (An) */
void REGPARAM2 CPUFUNC(op_4e90_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 52;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uaecptr oldpc = m68k_getpci () + 2;
	if (srca & 1) {
		exception3i (opcode, srca);
		goto l_240900;
	}
	m68k_setpci (srca);
	m68k_areg (regs, 7) -= 4;
	x_put_long (m68k_areg (regs, 7), oldpc);
}}}l_240900: ;
return;
}

/* JSR.L (d16,An) */
void REGPARAM2 CPUFUNC(op_4ea8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 52;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uaecptr oldpc = m68k_getpci () + 4;
	if (srca & 1) {
		exception3i (opcode, srca);
		goto l_240901;
	}
	m68k_setpci (srca);
	m68k_areg (regs, 7) -= 4;
	x_put_long (m68k_areg (regs, 7), oldpc);
}}}l_240901: ;
return;
}

/* JSR.L (d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_4eb0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 52;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uaecptr oldpc = m68k_getpci () + 0;
	if (srca & 1) {
		exception3i (opcode, srca);
		goto l_240902;
	}
	m68k_setpci (srca);
	m68k_areg (regs, 7) -= 4;
	x_put_long (m68k_areg (regs, 7), oldpc);
}}}}l_240902: ;
return;
}

/* JSR.L (xxx).W */
void REGPARAM2 CPUFUNC(op_4eb8_24)(uae_u32 opcode)
{
	OpcodeFamily = 52;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uaecptr oldpc = m68k_getpci () + 4;
	if (srca & 1) {
		exception3i (opcode, srca);
		goto l_240903;
	}
	m68k_setpci (srca);
	m68k_areg (regs, 7) -= 4;
	x_put_long (m68k_areg (regs, 7), oldpc);
}}}l_240903: ;
return;
}

/* JSR.L (xxx).L */
void REGPARAM2 CPUFUNC(op_4eb9_24)(uae_u32 opcode)
{
	OpcodeFamily = 52;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uaecptr oldpc = m68k_getpci () + 6;
	if (srca & 1) {
		exception3i (opcode, srca);
		goto l_240904;
	}
	m68k_setpci (srca);
	m68k_areg (regs, 7) -= 4;
	x_put_long (m68k_areg (regs, 7), oldpc);
}}}l_240904: ;
return;
}

/* JSR.L (d16,PC) */
void REGPARAM2 CPUFUNC(op_4eba_24)(uae_u32 opcode)
{
	OpcodeFamily = 52;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uaecptr oldpc = m68k_getpci () + 4;
	if (srca & 1) {
		exception3i (opcode, srca);
		goto l_240905;
	}
	m68k_setpci (srca);
	m68k_areg (regs, 7) -= 4;
	x_put_long (m68k_areg (regs, 7), oldpc);
}}}l_240905: ;
return;
}

/* JSR.L (d8,PC,Xn) */
void REGPARAM2 CPUFUNC(op_4ebb_24)(uae_u32 opcode)
{
	OpcodeFamily = 52;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uaecptr oldpc = m68k_getpci () + 0;
	if (srca & 1) {
		exception3i (opcode, srca);
		goto l_240906;
	}
	m68k_setpci (srca);
	m68k_areg (regs, 7) -= 4;
	x_put_long (m68k_areg (regs, 7), oldpc);
}}}}l_240906: ;
return;
}

/* JMP.L (An) */
void REGPARAM2 CPUFUNC(op_4ed0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 53;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3i (opcode, srca);
		goto l_240907;
	}
	m68k_setpci (srca);
}}l_240907: ;
return;
}

/* JMP.L (d16,An) */
void REGPARAM2 CPUFUNC(op_4ee8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 53;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
	if (srca & 1) {
		exception3i (opcode, srca);
		goto l_240908;
	}
	m68k_setpci (srca);
}}l_240908: ;
return;
}

/* JMP.L (d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_4ef0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 53;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
	if (srca & 1) {
		exception3i (opcode, srca);
		goto l_240909;
	}
	m68k_setpci (srca);
}}}l_240909: ;
return;
}

/* JMP.L (xxx).W */
void REGPARAM2 CPUFUNC(op_4ef8_24)(uae_u32 opcode)
{
	OpcodeFamily = 53;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
	if (srca & 1) {
		exception3i (opcode, srca);
		goto l_240910;
	}
	m68k_setpci (srca);
}}l_240910: ;
return;
}

/* JMP.L (xxx).L */
void REGPARAM2 CPUFUNC(op_4ef9_24)(uae_u32 opcode)
{
	OpcodeFamily = 53;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
	if (srca & 1) {
		exception3i (opcode, srca);
		goto l_240911;
	}
	m68k_setpci (srca);
}}l_240911: ;
return;
}

/* JMP.L (d16,PC) */
void REGPARAM2 CPUFUNC(op_4efa_24)(uae_u32 opcode)
{
	OpcodeFamily = 53;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
	if (srca & 1) {
		exception3i (opcode, srca);
		goto l_240912;
	}
	m68k_setpci (srca);
}}l_240912: ;
return;
}

/* JMP.L (d8,PC,Xn) */
void REGPARAM2 CPUFUNC(op_4efb_24)(uae_u32 opcode)
{
	OpcodeFamily = 53;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
	if (srca & 1) {
		exception3i (opcode, srca);
		goto l_240913;
	}
	m68k_setpci (srca);
}}}l_240913: ;
return;
}

/* ADDQ.B #<data>,Dn */
void REGPARAM2 CPUFUNC(op_5000_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_u32 src = srcreg;
{	uae_s8 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u8)(dst)) + ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u8)(~dst)) < ((uae_u8)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}}	m68k_incpci (2);
return;
}

/* ADDQ.B #<data>,(An) */
void REGPARAM2 CPUFUNC(op_5010_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = x_get_byte (dsta);
{{uae_u32 newv = ((uae_u8)(dst)) + ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u8)(~dst)) < ((uae_u8)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (dsta, newv);
}}}}}}}	m68k_incpci (2);
return;
}

/* ADDQ.B #<data>,(An)+ */
void REGPARAM2 CPUFUNC(op_5018_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
{{uae_u32 newv = ((uae_u8)(dst)) + ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u8)(~dst)) < ((uae_u8)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (dsta, newv);
}}}}}}}	m68k_incpci (2);
return;
}

/* ADDQ.B #<data>,-(An) */
void REGPARAM2 CPUFUNC(op_5020_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
{{uae_u32 newv = ((uae_u8)(dst)) + ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u8)(~dst)) < ((uae_u8)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (dsta, newv);
}}}}}}}	m68k_incpci (2);
return;
}

/* ADDQ.B #<data>,(d16,An) */
void REGPARAM2 CPUFUNC(op_5028_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 dst = x_get_byte (dsta);
{{uae_u32 newv = ((uae_u8)(dst)) + ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u8)(~dst)) < ((uae_u8)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (dsta, newv);
}}}}}}}	m68k_incpci (4);
return;
}

/* ADDQ.B #<data>,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_5030_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	m68k_incpci (2);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s8 dst = x_get_byte (dsta);
{{uae_u32 newv = ((uae_u8)(dst)) + ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u8)(~dst)) < ((uae_u8)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (dsta, newv);
}}}}}}}}return;
}

/* ADDQ.B #<data>,(xxx).W */
void REGPARAM2 CPUFUNC(op_5038_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	OpcodeFamily = 11;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 dst = x_get_byte (dsta);
{{uae_u32 newv = ((uae_u8)(dst)) + ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u8)(~dst)) < ((uae_u8)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (dsta, newv);
}}}}}}}	m68k_incpci (4);
return;
}

/* ADDQ.B #<data>,(xxx).L */
void REGPARAM2 CPUFUNC(op_5039_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	OpcodeFamily = 11;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (2);
{	uae_s8 dst = x_get_byte (dsta);
{{uae_u32 newv = ((uae_u8)(dst)) + ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u8)(~dst)) < ((uae_u8)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (dsta, newv);
}}}}}}}	m68k_incpci (6);
return;
}

/* ADDQ.W #<data>,Dn */
void REGPARAM2 CPUFUNC(op_5040_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_u32 src = srcreg;
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u16)(dst)) + ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u16)(~dst)) < ((uae_u16)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}}	m68k_incpci (2);
return;
}

/* ADDAQ.W #<data>,An */
void REGPARAM2 CPUFUNC(op_5048_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 12;
{{	uae_u32 src = srcreg;
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}	m68k_incpci (2);
return;
}

/* ADDQ.W #<data>,(An) */
void REGPARAM2 CPUFUNC(op_5050_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s16 dst = x_get_word (dsta);
{{uae_u32 newv = ((uae_u16)(dst)) + ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u16)(~dst)) < ((uae_u16)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (dsta, newv);
}}}}}}}	m68k_incpci (2);
return;
}

/* ADDQ.W #<data>,(An)+ */
void REGPARAM2 CPUFUNC(op_5058_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s16 dst = x_get_word (dsta);
	m68k_areg (regs, dstreg) += 2;
{{uae_u32 newv = ((uae_u16)(dst)) + ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u16)(~dst)) < ((uae_u16)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (dsta, newv);
}}}}}}}	m68k_incpci (2);
return;
}

/* ADDQ.W #<data>,-(An) */
void REGPARAM2 CPUFUNC(op_5060_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
{	uae_s16 dst = x_get_word (dsta);
	m68k_areg (regs, dstreg) = dsta;
{{uae_u32 newv = ((uae_u16)(dst)) + ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u16)(~dst)) < ((uae_u16)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (dsta, newv);
}}}}}}}	m68k_incpci (2);
return;
}

/* ADDQ.W #<data>,(d16,An) */
void REGPARAM2 CPUFUNC(op_5068_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 dst = x_get_word (dsta);
{{uae_u32 newv = ((uae_u16)(dst)) + ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u16)(~dst)) < ((uae_u16)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (dsta, newv);
}}}}}}}	m68k_incpci (4);
return;
}

/* ADDQ.W #<data>,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_5070_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	m68k_incpci (2);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s16 dst = x_get_word (dsta);
{{uae_u32 newv = ((uae_u16)(dst)) + ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u16)(~dst)) < ((uae_u16)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (dsta, newv);
}}}}}}}}return;
}

/* ADDQ.W #<data>,(xxx).W */
void REGPARAM2 CPUFUNC(op_5078_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	OpcodeFamily = 11;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 dst = x_get_word (dsta);
{{uae_u32 newv = ((uae_u16)(dst)) + ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u16)(~dst)) < ((uae_u16)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (dsta, newv);
}}}}}}}	m68k_incpci (4);
return;
}

/* ADDQ.W #<data>,(xxx).L */
void REGPARAM2 CPUFUNC(op_5079_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	OpcodeFamily = 11;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (2);
{	uae_s16 dst = x_get_word (dsta);
{{uae_u32 newv = ((uae_u16)(dst)) + ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u16)(~dst)) < ((uae_u16)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (dsta, newv);
}}}}}}}	m68k_incpci (6);
return;
}

/* ADDQ.L #<data>,Dn */
void REGPARAM2 CPUFUNC(op_5080_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_u32 src = srcreg;
{	uae_s32 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) + ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u32)(~dst)) < ((uae_u32)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}	m68k_incpci (2);
return;
}

/* ADDAQ.L #<data>,An */
void REGPARAM2 CPUFUNC(op_5088_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 12;
{{	uae_u32 src = srcreg;
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}	m68k_incpci (2);
return;
}

/* ADDQ.L #<data>,(An) */
void REGPARAM2 CPUFUNC(op_5090_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s32 dst = x_get_long (dsta);
{{uae_u32 newv = ((uae_u32)(dst)) + ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u32)(~dst)) < ((uae_u32)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (dsta, newv);
}}}}}}}	m68k_incpci (2);
return;
}

/* ADDQ.L #<data>,(An)+ */
void REGPARAM2 CPUFUNC(op_5098_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s32 dst = x_get_long (dsta);
	m68k_areg (regs, dstreg) += 4;
{{uae_u32 newv = ((uae_u32)(dst)) + ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u32)(~dst)) < ((uae_u32)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (dsta, newv);
}}}}}}}	m68k_incpci (2);
return;
}

/* ADDQ.L #<data>,-(An) */
void REGPARAM2 CPUFUNC(op_50a0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
{	uae_s32 dst = x_get_long (dsta);
	m68k_areg (regs, dstreg) = dsta;
{{uae_u32 newv = ((uae_u32)(dst)) + ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u32)(~dst)) < ((uae_u32)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (dsta, newv);
}}}}}}}	m68k_incpci (2);
return;
}

#endif

#ifdef PART_5
/* ADDQ.L #<data>,(d16,An) */
void REGPARAM2 CPUFUNC(op_50a8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 dst = x_get_long (dsta);
{{uae_u32 newv = ((uae_u32)(dst)) + ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u32)(~dst)) < ((uae_u32)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (dsta, newv);
}}}}}}}	m68k_incpci (4);
return;
}

/* ADDQ.L #<data>,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_50b0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	m68k_incpci (2);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s32 dst = x_get_long (dsta);
{{uae_u32 newv = ((uae_u32)(dst)) + ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u32)(~dst)) < ((uae_u32)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (dsta, newv);
}}}}}}}}return;
}

/* ADDQ.L #<data>,(xxx).W */
void REGPARAM2 CPUFUNC(op_50b8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	OpcodeFamily = 11;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 dst = x_get_long (dsta);
{{uae_u32 newv = ((uae_u32)(dst)) + ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u32)(~dst)) < ((uae_u32)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (dsta, newv);
}}}}}}}	m68k_incpci (4);
return;
}

/* ADDQ.L #<data>,(xxx).L */
void REGPARAM2 CPUFUNC(op_50b9_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	OpcodeFamily = 11;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (2);
{	uae_s32 dst = x_get_long (dsta);
{{uae_u32 newv = ((uae_u32)(dst)) + ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u32)(~dst)) < ((uae_u32)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (dsta, newv);
}}}}}}}	m68k_incpci (6);
return;
}

/* Scc.B Dn (T) */
void REGPARAM2 CPUFUNC(op_50c0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{{{	int val = cctrue (0) ? 0xff : 0;
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpci (2);
return;
}

/* DBcc.W Dn,#<data>.W (T) */
void REGPARAM2 CPUFUNC(op_50c8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 58;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 offs = get_iword_cache_040 (2);
	uaecptr oldpc = m68k_getpci ();
	if (!cctrue (0)) {
	m68k_incpci ((uae_s32)offs + 2);
			m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xffff) | (((src - 1)) & 0xffff);
		if (src) {
			if (offs & 1) {
				exception3i (opcode, m68k_getpci () + 2 + (uae_s32)offs + 2);
				goto l_240941;
			}
			return;
		}
	} else {
	}
	m68k_setpci (oldpc + 4);
}}}l_240941: ;
return;
}

/* Scc.B (An) (T) */
void REGPARAM2 CPUFUNC(op_50d0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{{	int val = cctrue (0) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B (An)+ (T) */
void REGPARAM2 CPUFUNC(op_50d8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{{	int val = cctrue (0) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B -(An) (T) */
void REGPARAM2 CPUFUNC(op_50e0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
	m68k_areg (regs, srcreg) = srca;
{{	int val = cctrue (0) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B (d16,An) (T) */
void REGPARAM2 CPUFUNC(op_50e8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{{	int val = cctrue (0) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (4);
return;
}

/* Scc.B (d8,An,Xn) (T) */
void REGPARAM2 CPUFUNC(op_50f0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{{	int val = cctrue (0) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}}return;
}

/* Scc.B (xxx).W (T) */
void REGPARAM2 CPUFUNC(op_50f8_24)(uae_u32 opcode)
{
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{{	int val = cctrue (0) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (4);
return;
}

/* Scc.B (xxx).L (T) */
void REGPARAM2 CPUFUNC(op_50f9_24)(uae_u32 opcode)
{
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{{	int val = cctrue (0) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (6);
return;
}

/* TRAPcc.L #<data>.W (T) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_50fa_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{{	uae_s16 dummy = get_iword_cache_040 (2);
	if (cctrue (0)) { Exception (7); goto l_240949; }
}}	m68k_incpci (4);
l_240949: ;
return;
}

#endif
/* TRAPcc.L #<data>.L (T) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_50fb_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{{	uae_s32 dummy;
	dummy = get_ilong_cache_040 (2);
	if (cctrue (0)) { Exception (7); goto l_240950; }
}}	m68k_incpci (6);
l_240950: ;
return;
}

#endif
/* TRAPcc.L  (T) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_50fc_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{	if (cctrue (0)) { Exception (7); goto l_240951; }
}	m68k_incpci (2);
l_240951: ;
return;
}

#endif
/* SUBQ.B #<data>,Dn */
void REGPARAM2 CPUFUNC(op_5100_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_u32 src = srcreg;
{	uae_s8 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}}	m68k_incpci (2);
return;
}

/* SUBQ.B #<data>,(An) */
void REGPARAM2 CPUFUNC(op_5110_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = x_get_byte (dsta);
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (dsta, newv);
}}}}}}}	m68k_incpci (2);
return;
}

/* SUBQ.B #<data>,(An)+ */
void REGPARAM2 CPUFUNC(op_5118_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (dsta, newv);
}}}}}}}	m68k_incpci (2);
return;
}

/* SUBQ.B #<data>,-(An) */
void REGPARAM2 CPUFUNC(op_5120_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (dsta, newv);
}}}}}}}	m68k_incpci (2);
return;
}

/* SUBQ.B #<data>,(d16,An) */
void REGPARAM2 CPUFUNC(op_5128_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 dst = x_get_byte (dsta);
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (dsta, newv);
}}}}}}}	m68k_incpci (4);
return;
}

/* SUBQ.B #<data>,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_5130_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	m68k_incpci (2);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s8 dst = x_get_byte (dsta);
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (dsta, newv);
}}}}}}}}return;
}

/* SUBQ.B #<data>,(xxx).W */
void REGPARAM2 CPUFUNC(op_5138_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	OpcodeFamily = 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 dst = x_get_byte (dsta);
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (dsta, newv);
}}}}}}}	m68k_incpci (4);
return;
}

/* SUBQ.B #<data>,(xxx).L */
void REGPARAM2 CPUFUNC(op_5139_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	OpcodeFamily = 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (2);
{	uae_s8 dst = x_get_byte (dsta);
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (dsta, newv);
}}}}}}}	m68k_incpci (6);
return;
}

/* SUBQ.W #<data>,Dn */
void REGPARAM2 CPUFUNC(op_5140_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_u32 src = srcreg;
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}}	m68k_incpci (2);
return;
}

/* SUBAQ.W #<data>,An */
void REGPARAM2 CPUFUNC(op_5148_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 8;
{{	uae_u32 src = srcreg;
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}	m68k_incpci (2);
return;
}

/* SUBQ.W #<data>,(An) */
void REGPARAM2 CPUFUNC(op_5150_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s16 dst = x_get_word (dsta);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (dsta, newv);
}}}}}}}	m68k_incpci (2);
return;
}

/* SUBQ.W #<data>,(An)+ */
void REGPARAM2 CPUFUNC(op_5158_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s16 dst = x_get_word (dsta);
	m68k_areg (regs, dstreg) += 2;
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (dsta, newv);
}}}}}}}	m68k_incpci (2);
return;
}

/* SUBQ.W #<data>,-(An) */
void REGPARAM2 CPUFUNC(op_5160_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
{	uae_s16 dst = x_get_word (dsta);
	m68k_areg (regs, dstreg) = dsta;
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (dsta, newv);
}}}}}}}	m68k_incpci (2);
return;
}

/* SUBQ.W #<data>,(d16,An) */
void REGPARAM2 CPUFUNC(op_5168_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 dst = x_get_word (dsta);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (dsta, newv);
}}}}}}}	m68k_incpci (4);
return;
}

/* SUBQ.W #<data>,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_5170_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	m68k_incpci (2);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s16 dst = x_get_word (dsta);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (dsta, newv);
}}}}}}}}return;
}

/* SUBQ.W #<data>,(xxx).W */
void REGPARAM2 CPUFUNC(op_5178_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	OpcodeFamily = 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 dst = x_get_word (dsta);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (dsta, newv);
}}}}}}}	m68k_incpci (4);
return;
}

/* SUBQ.W #<data>,(xxx).L */
void REGPARAM2 CPUFUNC(op_5179_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	OpcodeFamily = 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (2);
{	uae_s16 dst = x_get_word (dsta);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (dsta, newv);
}}}}}}}	m68k_incpci (6);
return;
}

/* SUBQ.L #<data>,Dn */
void REGPARAM2 CPUFUNC(op_5180_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_u32 src = srcreg;
{	uae_s32 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}	m68k_incpci (2);
return;
}

/* SUBAQ.L #<data>,An */
void REGPARAM2 CPUFUNC(op_5188_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 8;
{{	uae_u32 src = srcreg;
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}	m68k_incpci (2);
return;
}

/* SUBQ.L #<data>,(An) */
void REGPARAM2 CPUFUNC(op_5190_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s32 dst = x_get_long (dsta);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (dsta, newv);
}}}}}}}	m68k_incpci (2);
return;
}

/* SUBQ.L #<data>,(An)+ */
void REGPARAM2 CPUFUNC(op_5198_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s32 dst = x_get_long (dsta);
	m68k_areg (regs, dstreg) += 4;
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (dsta, newv);
}}}}}}}	m68k_incpci (2);
return;
}

/* SUBQ.L #<data>,-(An) */
void REGPARAM2 CPUFUNC(op_51a0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
{	uae_s32 dst = x_get_long (dsta);
	m68k_areg (regs, dstreg) = dsta;
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (dsta, newv);
}}}}}}}	m68k_incpci (2);
return;
}

/* SUBQ.L #<data>,(d16,An) */
void REGPARAM2 CPUFUNC(op_51a8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 dst = x_get_long (dsta);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (dsta, newv);
}}}}}}}	m68k_incpci (4);
return;
}

/* SUBQ.L #<data>,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_51b0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	m68k_incpci (2);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s32 dst = x_get_long (dsta);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (dsta, newv);
}}}}}}}}return;
}

/* SUBQ.L #<data>,(xxx).W */
void REGPARAM2 CPUFUNC(op_51b8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	OpcodeFamily = 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 dst = x_get_long (dsta);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (dsta, newv);
}}}}}}}	m68k_incpci (4);
return;
}

/* SUBQ.L #<data>,(xxx).L */
void REGPARAM2 CPUFUNC(op_51b9_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	OpcodeFamily = 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (2);
{	uae_s32 dst = x_get_long (dsta);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (dsta, newv);
}}}}}}}	m68k_incpci (6);
return;
}

/* Scc.B Dn (F) */
void REGPARAM2 CPUFUNC(op_51c0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{{{	int val = cctrue (1) ? 0xff : 0;
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpci (2);
return;
}

/* DBcc.W Dn,#<data>.W (F) */
void REGPARAM2 CPUFUNC(op_51c8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 58;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 offs = get_iword_cache_040 (2);
	uaecptr oldpc = m68k_getpci ();
	if (!cctrue (1)) {
	m68k_incpci ((uae_s32)offs + 2);
			m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xffff) | (((src - 1)) & 0xffff);
		if (src) {
			if (offs & 1) {
				exception3i (opcode, m68k_getpci () + 2 + (uae_s32)offs + 2);
				goto l_240979;
			}
			return;
		}
	} else {
	}
	m68k_setpci (oldpc + 4);
}}}l_240979: ;
return;
}

/* Scc.B (An) (F) */
void REGPARAM2 CPUFUNC(op_51d0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{{	int val = cctrue (1) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B (An)+ (F) */
void REGPARAM2 CPUFUNC(op_51d8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{{	int val = cctrue (1) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B -(An) (F) */
void REGPARAM2 CPUFUNC(op_51e0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
	m68k_areg (regs, srcreg) = srca;
{{	int val = cctrue (1) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B (d16,An) (F) */
void REGPARAM2 CPUFUNC(op_51e8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{{	int val = cctrue (1) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (4);
return;
}

/* Scc.B (d8,An,Xn) (F) */
void REGPARAM2 CPUFUNC(op_51f0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{{	int val = cctrue (1) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}}return;
}

/* Scc.B (xxx).W (F) */
void REGPARAM2 CPUFUNC(op_51f8_24)(uae_u32 opcode)
{
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{{	int val = cctrue (1) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (4);
return;
}

/* Scc.B (xxx).L (F) */
void REGPARAM2 CPUFUNC(op_51f9_24)(uae_u32 opcode)
{
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{{	int val = cctrue (1) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (6);
return;
}

/* TRAPcc.L #<data>.W (F) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_51fa_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{{	uae_s16 dummy = get_iword_cache_040 (2);
	if (cctrue (1)) { Exception (7); goto l_240987; }
}}	m68k_incpci (4);
l_240987: ;
return;
}

#endif
/* TRAPcc.L #<data>.L (F) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_51fb_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{{	uae_s32 dummy;
	dummy = get_ilong_cache_040 (2);
	if (cctrue (1)) { Exception (7); goto l_240988; }
}}	m68k_incpci (6);
l_240988: ;
return;
}

#endif
/* TRAPcc.L  (F) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_51fc_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{	if (cctrue (1)) { Exception (7); goto l_240989; }
}	m68k_incpci (2);
l_240989: ;
return;
}

#endif
/* Scc.B Dn (HI) */
void REGPARAM2 CPUFUNC(op_52c0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{{{	int val = cctrue (2) ? 0xff : 0;
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpci (2);
return;
}

/* DBcc.W Dn,#<data>.W (HI) */
void REGPARAM2 CPUFUNC(op_52c8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 58;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 offs = get_iword_cache_040 (2);
	uaecptr oldpc = m68k_getpci ();
	if (!cctrue (2)) {
	m68k_incpci ((uae_s32)offs + 2);
			m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xffff) | (((src - 1)) & 0xffff);
		if (src) {
			if (offs & 1) {
				exception3i (opcode, m68k_getpci () + 2 + (uae_s32)offs + 2);
				goto l_240991;
			}
			return;
		}
	} else {
	}
	m68k_setpci (oldpc + 4);
}}}l_240991: ;
return;
}

/* Scc.B (An) (HI) */
void REGPARAM2 CPUFUNC(op_52d0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{{	int val = cctrue (2) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B (An)+ (HI) */
void REGPARAM2 CPUFUNC(op_52d8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{{	int val = cctrue (2) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B -(An) (HI) */
void REGPARAM2 CPUFUNC(op_52e0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
	m68k_areg (regs, srcreg) = srca;
{{	int val = cctrue (2) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B (d16,An) (HI) */
void REGPARAM2 CPUFUNC(op_52e8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{{	int val = cctrue (2) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (4);
return;
}

/* Scc.B (d8,An,Xn) (HI) */
void REGPARAM2 CPUFUNC(op_52f0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{{	int val = cctrue (2) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}}return;
}

/* Scc.B (xxx).W (HI) */
void REGPARAM2 CPUFUNC(op_52f8_24)(uae_u32 opcode)
{
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{{	int val = cctrue (2) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (4);
return;
}

/* Scc.B (xxx).L (HI) */
void REGPARAM2 CPUFUNC(op_52f9_24)(uae_u32 opcode)
{
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{{	int val = cctrue (2) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (6);
return;
}

/* TRAPcc.L #<data>.W (HI) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_52fa_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{{	uae_s16 dummy = get_iword_cache_040 (2);
	if (cctrue (2)) { Exception (7); goto l_240999; }
}}	m68k_incpci (4);
l_240999: ;
return;
}

#endif
/* TRAPcc.L #<data>.L (HI) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_52fb_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{{	uae_s32 dummy;
	dummy = get_ilong_cache_040 (2);
	if (cctrue (2)) { Exception (7); goto l_241000; }
}}	m68k_incpci (6);
l_241000: ;
return;
}

#endif
/* TRAPcc.L  (HI) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_52fc_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{	if (cctrue (2)) { Exception (7); goto l_241001; }
}	m68k_incpci (2);
l_241001: ;
return;
}

#endif
/* Scc.B Dn (LS) */
void REGPARAM2 CPUFUNC(op_53c0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{{{	int val = cctrue (3) ? 0xff : 0;
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpci (2);
return;
}

/* DBcc.W Dn,#<data>.W (LS) */
void REGPARAM2 CPUFUNC(op_53c8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 58;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 offs = get_iword_cache_040 (2);
	uaecptr oldpc = m68k_getpci ();
	if (!cctrue (3)) {
	m68k_incpci ((uae_s32)offs + 2);
			m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xffff) | (((src - 1)) & 0xffff);
		if (src) {
			if (offs & 1) {
				exception3i (opcode, m68k_getpci () + 2 + (uae_s32)offs + 2);
				goto l_241003;
			}
			return;
		}
	} else {
	}
	m68k_setpci (oldpc + 4);
}}}l_241003: ;
return;
}

/* Scc.B (An) (LS) */
void REGPARAM2 CPUFUNC(op_53d0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{{	int val = cctrue (3) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B (An)+ (LS) */
void REGPARAM2 CPUFUNC(op_53d8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{{	int val = cctrue (3) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B -(An) (LS) */
void REGPARAM2 CPUFUNC(op_53e0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
	m68k_areg (regs, srcreg) = srca;
{{	int val = cctrue (3) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B (d16,An) (LS) */
void REGPARAM2 CPUFUNC(op_53e8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{{	int val = cctrue (3) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (4);
return;
}

/* Scc.B (d8,An,Xn) (LS) */
void REGPARAM2 CPUFUNC(op_53f0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{{	int val = cctrue (3) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}}return;
}

/* Scc.B (xxx).W (LS) */
void REGPARAM2 CPUFUNC(op_53f8_24)(uae_u32 opcode)
{
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{{	int val = cctrue (3) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (4);
return;
}

/* Scc.B (xxx).L (LS) */
void REGPARAM2 CPUFUNC(op_53f9_24)(uae_u32 opcode)
{
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{{	int val = cctrue (3) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (6);
return;
}

/* TRAPcc.L #<data>.W (LS) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_53fa_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{{	uae_s16 dummy = get_iword_cache_040 (2);
	if (cctrue (3)) { Exception (7); goto l_241011; }
}}	m68k_incpci (4);
l_241011: ;
return;
}

#endif
/* TRAPcc.L #<data>.L (LS) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_53fb_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{{	uae_s32 dummy;
	dummy = get_ilong_cache_040 (2);
	if (cctrue (3)) { Exception (7); goto l_241012; }
}}	m68k_incpci (6);
l_241012: ;
return;
}

#endif
/* TRAPcc.L  (LS) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_53fc_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{	if (cctrue (3)) { Exception (7); goto l_241013; }
}	m68k_incpci (2);
l_241013: ;
return;
}

#endif
/* Scc.B Dn (CC) */
void REGPARAM2 CPUFUNC(op_54c0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{{{	int val = cctrue (4) ? 0xff : 0;
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpci (2);
return;
}

/* DBcc.W Dn,#<data>.W (CC) */
void REGPARAM2 CPUFUNC(op_54c8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 58;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 offs = get_iword_cache_040 (2);
	uaecptr oldpc = m68k_getpci ();
	if (!cctrue (4)) {
	m68k_incpci ((uae_s32)offs + 2);
			m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xffff) | (((src - 1)) & 0xffff);
		if (src) {
			if (offs & 1) {
				exception3i (opcode, m68k_getpci () + 2 + (uae_s32)offs + 2);
				goto l_241015;
			}
			return;
		}
	} else {
	}
	m68k_setpci (oldpc + 4);
}}}l_241015: ;
return;
}

/* Scc.B (An) (CC) */
void REGPARAM2 CPUFUNC(op_54d0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{{	int val = cctrue (4) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B (An)+ (CC) */
void REGPARAM2 CPUFUNC(op_54d8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{{	int val = cctrue (4) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B -(An) (CC) */
void REGPARAM2 CPUFUNC(op_54e0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
	m68k_areg (regs, srcreg) = srca;
{{	int val = cctrue (4) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B (d16,An) (CC) */
void REGPARAM2 CPUFUNC(op_54e8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{{	int val = cctrue (4) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (4);
return;
}

/* Scc.B (d8,An,Xn) (CC) */
void REGPARAM2 CPUFUNC(op_54f0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{{	int val = cctrue (4) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}}return;
}

/* Scc.B (xxx).W (CC) */
void REGPARAM2 CPUFUNC(op_54f8_24)(uae_u32 opcode)
{
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{{	int val = cctrue (4) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (4);
return;
}

/* Scc.B (xxx).L (CC) */
void REGPARAM2 CPUFUNC(op_54f9_24)(uae_u32 opcode)
{
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{{	int val = cctrue (4) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (6);
return;
}

/* TRAPcc.L #<data>.W (CC) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_54fa_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{{	uae_s16 dummy = get_iword_cache_040 (2);
	if (cctrue (4)) { Exception (7); goto l_241023; }
}}	m68k_incpci (4);
l_241023: ;
return;
}

#endif
/* TRAPcc.L #<data>.L (CC) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_54fb_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{{	uae_s32 dummy;
	dummy = get_ilong_cache_040 (2);
	if (cctrue (4)) { Exception (7); goto l_241024; }
}}	m68k_incpci (6);
l_241024: ;
return;
}

#endif
/* TRAPcc.L  (CC) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_54fc_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{	if (cctrue (4)) { Exception (7); goto l_241025; }
}	m68k_incpci (2);
l_241025: ;
return;
}

#endif
/* Scc.B Dn (CS) */
void REGPARAM2 CPUFUNC(op_55c0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{{{	int val = cctrue (5) ? 0xff : 0;
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpci (2);
return;
}

/* DBcc.W Dn,#<data>.W (CS) */
void REGPARAM2 CPUFUNC(op_55c8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 58;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 offs = get_iword_cache_040 (2);
	uaecptr oldpc = m68k_getpci ();
	if (!cctrue (5)) {
	m68k_incpci ((uae_s32)offs + 2);
			m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xffff) | (((src - 1)) & 0xffff);
		if (src) {
			if (offs & 1) {
				exception3i (opcode, m68k_getpci () + 2 + (uae_s32)offs + 2);
				goto l_241027;
			}
			return;
		}
	} else {
	}
	m68k_setpci (oldpc + 4);
}}}l_241027: ;
return;
}

/* Scc.B (An) (CS) */
void REGPARAM2 CPUFUNC(op_55d0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{{	int val = cctrue (5) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B (An)+ (CS) */
void REGPARAM2 CPUFUNC(op_55d8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{{	int val = cctrue (5) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B -(An) (CS) */
void REGPARAM2 CPUFUNC(op_55e0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
	m68k_areg (regs, srcreg) = srca;
{{	int val = cctrue (5) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B (d16,An) (CS) */
void REGPARAM2 CPUFUNC(op_55e8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{{	int val = cctrue (5) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (4);
return;
}

/* Scc.B (d8,An,Xn) (CS) */
void REGPARAM2 CPUFUNC(op_55f0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{{	int val = cctrue (5) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}}return;
}

/* Scc.B (xxx).W (CS) */
void REGPARAM2 CPUFUNC(op_55f8_24)(uae_u32 opcode)
{
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{{	int val = cctrue (5) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (4);
return;
}

/* Scc.B (xxx).L (CS) */
void REGPARAM2 CPUFUNC(op_55f9_24)(uae_u32 opcode)
{
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{{	int val = cctrue (5) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (6);
return;
}

/* TRAPcc.L #<data>.W (CS) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_55fa_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{{	uae_s16 dummy = get_iword_cache_040 (2);
	if (cctrue (5)) { Exception (7); goto l_241035; }
}}	m68k_incpci (4);
l_241035: ;
return;
}

#endif
/* TRAPcc.L #<data>.L (CS) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_55fb_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{{	uae_s32 dummy;
	dummy = get_ilong_cache_040 (2);
	if (cctrue (5)) { Exception (7); goto l_241036; }
}}	m68k_incpci (6);
l_241036: ;
return;
}

#endif
/* TRAPcc.L  (CS) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_55fc_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{	if (cctrue (5)) { Exception (7); goto l_241037; }
}	m68k_incpci (2);
l_241037: ;
return;
}

#endif
/* Scc.B Dn (NE) */
void REGPARAM2 CPUFUNC(op_56c0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{{{	int val = cctrue (6) ? 0xff : 0;
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpci (2);
return;
}

/* DBcc.W Dn,#<data>.W (NE) */
void REGPARAM2 CPUFUNC(op_56c8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 58;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 offs = get_iword_cache_040 (2);
	uaecptr oldpc = m68k_getpci ();
	if (!cctrue (6)) {
	m68k_incpci ((uae_s32)offs + 2);
			m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xffff) | (((src - 1)) & 0xffff);
		if (src) {
			if (offs & 1) {
				exception3i (opcode, m68k_getpci () + 2 + (uae_s32)offs + 2);
				goto l_241039;
			}
			return;
		}
	} else {
	}
	m68k_setpci (oldpc + 4);
}}}l_241039: ;
return;
}

/* Scc.B (An) (NE) */
void REGPARAM2 CPUFUNC(op_56d0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{{	int val = cctrue (6) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B (An)+ (NE) */
void REGPARAM2 CPUFUNC(op_56d8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{{	int val = cctrue (6) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B -(An) (NE) */
void REGPARAM2 CPUFUNC(op_56e0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
	m68k_areg (regs, srcreg) = srca;
{{	int val = cctrue (6) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B (d16,An) (NE) */
void REGPARAM2 CPUFUNC(op_56e8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{{	int val = cctrue (6) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (4);
return;
}

/* Scc.B (d8,An,Xn) (NE) */
void REGPARAM2 CPUFUNC(op_56f0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{{	int val = cctrue (6) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}}return;
}

/* Scc.B (xxx).W (NE) */
void REGPARAM2 CPUFUNC(op_56f8_24)(uae_u32 opcode)
{
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{{	int val = cctrue (6) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (4);
return;
}

/* Scc.B (xxx).L (NE) */
void REGPARAM2 CPUFUNC(op_56f9_24)(uae_u32 opcode)
{
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{{	int val = cctrue (6) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (6);
return;
}

/* TRAPcc.L #<data>.W (NE) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_56fa_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{{	uae_s16 dummy = get_iword_cache_040 (2);
	if (cctrue (6)) { Exception (7); goto l_241047; }
}}	m68k_incpci (4);
l_241047: ;
return;
}

#endif
/* TRAPcc.L #<data>.L (NE) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_56fb_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{{	uae_s32 dummy;
	dummy = get_ilong_cache_040 (2);
	if (cctrue (6)) { Exception (7); goto l_241048; }
}}	m68k_incpci (6);
l_241048: ;
return;
}

#endif
/* TRAPcc.L  (NE) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_56fc_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{	if (cctrue (6)) { Exception (7); goto l_241049; }
}	m68k_incpci (2);
l_241049: ;
return;
}

#endif
/* Scc.B Dn (EQ) */
void REGPARAM2 CPUFUNC(op_57c0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{{{	int val = cctrue (7) ? 0xff : 0;
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpci (2);
return;
}

/* DBcc.W Dn,#<data>.W (EQ) */
void REGPARAM2 CPUFUNC(op_57c8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 58;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 offs = get_iword_cache_040 (2);
	uaecptr oldpc = m68k_getpci ();
	if (!cctrue (7)) {
	m68k_incpci ((uae_s32)offs + 2);
			m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xffff) | (((src - 1)) & 0xffff);
		if (src) {
			if (offs & 1) {
				exception3i (opcode, m68k_getpci () + 2 + (uae_s32)offs + 2);
				goto l_241051;
			}
			return;
		}
	} else {
	}
	m68k_setpci (oldpc + 4);
}}}l_241051: ;
return;
}

/* Scc.B (An) (EQ) */
void REGPARAM2 CPUFUNC(op_57d0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{{	int val = cctrue (7) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B (An)+ (EQ) */
void REGPARAM2 CPUFUNC(op_57d8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{{	int val = cctrue (7) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B -(An) (EQ) */
void REGPARAM2 CPUFUNC(op_57e0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
	m68k_areg (regs, srcreg) = srca;
{{	int val = cctrue (7) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B (d16,An) (EQ) */
void REGPARAM2 CPUFUNC(op_57e8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{{	int val = cctrue (7) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (4);
return;
}

/* Scc.B (d8,An,Xn) (EQ) */
void REGPARAM2 CPUFUNC(op_57f0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{{	int val = cctrue (7) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}}return;
}

/* Scc.B (xxx).W (EQ) */
void REGPARAM2 CPUFUNC(op_57f8_24)(uae_u32 opcode)
{
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{{	int val = cctrue (7) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (4);
return;
}

/* Scc.B (xxx).L (EQ) */
void REGPARAM2 CPUFUNC(op_57f9_24)(uae_u32 opcode)
{
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{{	int val = cctrue (7) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (6);
return;
}

/* TRAPcc.L #<data>.W (EQ) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_57fa_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{{	uae_s16 dummy = get_iword_cache_040 (2);
	if (cctrue (7)) { Exception (7); goto l_241059; }
}}	m68k_incpci (4);
l_241059: ;
return;
}

#endif
/* TRAPcc.L #<data>.L (EQ) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_57fb_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{{	uae_s32 dummy;
	dummy = get_ilong_cache_040 (2);
	if (cctrue (7)) { Exception (7); goto l_241060; }
}}	m68k_incpci (6);
l_241060: ;
return;
}

#endif
/* TRAPcc.L  (EQ) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_57fc_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{	if (cctrue (7)) { Exception (7); goto l_241061; }
}	m68k_incpci (2);
l_241061: ;
return;
}

#endif
/* Scc.B Dn (VC) */
void REGPARAM2 CPUFUNC(op_58c0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{{{	int val = cctrue (8) ? 0xff : 0;
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpci (2);
return;
}

/* DBcc.W Dn,#<data>.W (VC) */
void REGPARAM2 CPUFUNC(op_58c8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 58;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 offs = get_iword_cache_040 (2);
	uaecptr oldpc = m68k_getpci ();
	if (!cctrue (8)) {
	m68k_incpci ((uae_s32)offs + 2);
			m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xffff) | (((src - 1)) & 0xffff);
		if (src) {
			if (offs & 1) {
				exception3i (opcode, m68k_getpci () + 2 + (uae_s32)offs + 2);
				goto l_241063;
			}
			return;
		}
	} else {
	}
	m68k_setpci (oldpc + 4);
}}}l_241063: ;
return;
}

/* Scc.B (An) (VC) */
void REGPARAM2 CPUFUNC(op_58d0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{{	int val = cctrue (8) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B (An)+ (VC) */
void REGPARAM2 CPUFUNC(op_58d8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{{	int val = cctrue (8) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B -(An) (VC) */
void REGPARAM2 CPUFUNC(op_58e0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
	m68k_areg (regs, srcreg) = srca;
{{	int val = cctrue (8) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B (d16,An) (VC) */
void REGPARAM2 CPUFUNC(op_58e8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{{	int val = cctrue (8) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (4);
return;
}

/* Scc.B (d8,An,Xn) (VC) */
void REGPARAM2 CPUFUNC(op_58f0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{{	int val = cctrue (8) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}}return;
}

/* Scc.B (xxx).W (VC) */
void REGPARAM2 CPUFUNC(op_58f8_24)(uae_u32 opcode)
{
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{{	int val = cctrue (8) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (4);
return;
}

/* Scc.B (xxx).L (VC) */
void REGPARAM2 CPUFUNC(op_58f9_24)(uae_u32 opcode)
{
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{{	int val = cctrue (8) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (6);
return;
}

/* TRAPcc.L #<data>.W (VC) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_58fa_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{{	uae_s16 dummy = get_iword_cache_040 (2);
	if (cctrue (8)) { Exception (7); goto l_241071; }
}}	m68k_incpci (4);
l_241071: ;
return;
}

#endif
/* TRAPcc.L #<data>.L (VC) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_58fb_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{{	uae_s32 dummy;
	dummy = get_ilong_cache_040 (2);
	if (cctrue (8)) { Exception (7); goto l_241072; }
}}	m68k_incpci (6);
l_241072: ;
return;
}

#endif
/* TRAPcc.L  (VC) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_58fc_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{	if (cctrue (8)) { Exception (7); goto l_241073; }
}	m68k_incpci (2);
l_241073: ;
return;
}

#endif
/* Scc.B Dn (VS) */
void REGPARAM2 CPUFUNC(op_59c0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{{{	int val = cctrue (9) ? 0xff : 0;
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpci (2);
return;
}

/* DBcc.W Dn,#<data>.W (VS) */
void REGPARAM2 CPUFUNC(op_59c8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 58;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 offs = get_iword_cache_040 (2);
	uaecptr oldpc = m68k_getpci ();
	if (!cctrue (9)) {
	m68k_incpci ((uae_s32)offs + 2);
			m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xffff) | (((src - 1)) & 0xffff);
		if (src) {
			if (offs & 1) {
				exception3i (opcode, m68k_getpci () + 2 + (uae_s32)offs + 2);
				goto l_241075;
			}
			return;
		}
	} else {
	}
	m68k_setpci (oldpc + 4);
}}}l_241075: ;
return;
}

/* Scc.B (An) (VS) */
void REGPARAM2 CPUFUNC(op_59d0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{{	int val = cctrue (9) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B (An)+ (VS) */
void REGPARAM2 CPUFUNC(op_59d8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{{	int val = cctrue (9) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B -(An) (VS) */
void REGPARAM2 CPUFUNC(op_59e0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
	m68k_areg (regs, srcreg) = srca;
{{	int val = cctrue (9) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B (d16,An) (VS) */
void REGPARAM2 CPUFUNC(op_59e8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{{	int val = cctrue (9) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (4);
return;
}

/* Scc.B (d8,An,Xn) (VS) */
void REGPARAM2 CPUFUNC(op_59f0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{{	int val = cctrue (9) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}}return;
}

/* Scc.B (xxx).W (VS) */
void REGPARAM2 CPUFUNC(op_59f8_24)(uae_u32 opcode)
{
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{{	int val = cctrue (9) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (4);
return;
}

/* Scc.B (xxx).L (VS) */
void REGPARAM2 CPUFUNC(op_59f9_24)(uae_u32 opcode)
{
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{{	int val = cctrue (9) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (6);
return;
}

/* TRAPcc.L #<data>.W (VS) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_59fa_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{{	uae_s16 dummy = get_iword_cache_040 (2);
	if (cctrue (9)) { Exception (7); goto l_241083; }
}}	m68k_incpci (4);
l_241083: ;
return;
}

#endif
/* TRAPcc.L #<data>.L (VS) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_59fb_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{{	uae_s32 dummy;
	dummy = get_ilong_cache_040 (2);
	if (cctrue (9)) { Exception (7); goto l_241084; }
}}	m68k_incpci (6);
l_241084: ;
return;
}

#endif
/* TRAPcc.L  (VS) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_59fc_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{	if (cctrue (9)) { Exception (7); goto l_241085; }
}	m68k_incpci (2);
l_241085: ;
return;
}

#endif
/* Scc.B Dn (PL) */
void REGPARAM2 CPUFUNC(op_5ac0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{{{	int val = cctrue (10) ? 0xff : 0;
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpci (2);
return;
}

/* DBcc.W Dn,#<data>.W (PL) */
void REGPARAM2 CPUFUNC(op_5ac8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 58;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 offs = get_iword_cache_040 (2);
	uaecptr oldpc = m68k_getpci ();
	if (!cctrue (10)) {
	m68k_incpci ((uae_s32)offs + 2);
			m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xffff) | (((src - 1)) & 0xffff);
		if (src) {
			if (offs & 1) {
				exception3i (opcode, m68k_getpci () + 2 + (uae_s32)offs + 2);
				goto l_241087;
			}
			return;
		}
	} else {
	}
	m68k_setpci (oldpc + 4);
}}}l_241087: ;
return;
}

/* Scc.B (An) (PL) */
void REGPARAM2 CPUFUNC(op_5ad0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{{	int val = cctrue (10) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B (An)+ (PL) */
void REGPARAM2 CPUFUNC(op_5ad8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{{	int val = cctrue (10) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B -(An) (PL) */
void REGPARAM2 CPUFUNC(op_5ae0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
	m68k_areg (regs, srcreg) = srca;
{{	int val = cctrue (10) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B (d16,An) (PL) */
void REGPARAM2 CPUFUNC(op_5ae8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{{	int val = cctrue (10) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (4);
return;
}

/* Scc.B (d8,An,Xn) (PL) */
void REGPARAM2 CPUFUNC(op_5af0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{{	int val = cctrue (10) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}}return;
}

/* Scc.B (xxx).W (PL) */
void REGPARAM2 CPUFUNC(op_5af8_24)(uae_u32 opcode)
{
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{{	int val = cctrue (10) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (4);
return;
}

/* Scc.B (xxx).L (PL) */
void REGPARAM2 CPUFUNC(op_5af9_24)(uae_u32 opcode)
{
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{{	int val = cctrue (10) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (6);
return;
}

/* TRAPcc.L #<data>.W (PL) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_5afa_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{{	uae_s16 dummy = get_iword_cache_040 (2);
	if (cctrue (10)) { Exception (7); goto l_241095; }
}}	m68k_incpci (4);
l_241095: ;
return;
}

#endif
/* TRAPcc.L #<data>.L (PL) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_5afb_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{{	uae_s32 dummy;
	dummy = get_ilong_cache_040 (2);
	if (cctrue (10)) { Exception (7); goto l_241096; }
}}	m68k_incpci (6);
l_241096: ;
return;
}

#endif
/* TRAPcc.L  (PL) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_5afc_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{	if (cctrue (10)) { Exception (7); goto l_241097; }
}	m68k_incpci (2);
l_241097: ;
return;
}

#endif
/* Scc.B Dn (MI) */
void REGPARAM2 CPUFUNC(op_5bc0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{{{	int val = cctrue (11) ? 0xff : 0;
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpci (2);
return;
}

/* DBcc.W Dn,#<data>.W (MI) */
void REGPARAM2 CPUFUNC(op_5bc8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 58;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 offs = get_iword_cache_040 (2);
	uaecptr oldpc = m68k_getpci ();
	if (!cctrue (11)) {
	m68k_incpci ((uae_s32)offs + 2);
			m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xffff) | (((src - 1)) & 0xffff);
		if (src) {
			if (offs & 1) {
				exception3i (opcode, m68k_getpci () + 2 + (uae_s32)offs + 2);
				goto l_241099;
			}
			return;
		}
	} else {
	}
	m68k_setpci (oldpc + 4);
}}}l_241099: ;
return;
}

/* Scc.B (An) (MI) */
void REGPARAM2 CPUFUNC(op_5bd0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{{	int val = cctrue (11) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B (An)+ (MI) */
void REGPARAM2 CPUFUNC(op_5bd8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{{	int val = cctrue (11) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B -(An) (MI) */
void REGPARAM2 CPUFUNC(op_5be0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
	m68k_areg (regs, srcreg) = srca;
{{	int val = cctrue (11) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B (d16,An) (MI) */
void REGPARAM2 CPUFUNC(op_5be8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{{	int val = cctrue (11) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (4);
return;
}

/* Scc.B (d8,An,Xn) (MI) */
void REGPARAM2 CPUFUNC(op_5bf0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{{	int val = cctrue (11) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}}return;
}

/* Scc.B (xxx).W (MI) */
void REGPARAM2 CPUFUNC(op_5bf8_24)(uae_u32 opcode)
{
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{{	int val = cctrue (11) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (4);
return;
}

/* Scc.B (xxx).L (MI) */
void REGPARAM2 CPUFUNC(op_5bf9_24)(uae_u32 opcode)
{
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{{	int val = cctrue (11) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (6);
return;
}

/* TRAPcc.L #<data>.W (MI) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_5bfa_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{{	uae_s16 dummy = get_iword_cache_040 (2);
	if (cctrue (11)) { Exception (7); goto l_241107; }
}}	m68k_incpci (4);
l_241107: ;
return;
}

#endif
/* TRAPcc.L #<data>.L (MI) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_5bfb_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{{	uae_s32 dummy;
	dummy = get_ilong_cache_040 (2);
	if (cctrue (11)) { Exception (7); goto l_241108; }
}}	m68k_incpci (6);
l_241108: ;
return;
}

#endif
/* TRAPcc.L  (MI) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_5bfc_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{	if (cctrue (11)) { Exception (7); goto l_241109; }
}	m68k_incpci (2);
l_241109: ;
return;
}

#endif
/* Scc.B Dn (GE) */
void REGPARAM2 CPUFUNC(op_5cc0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{{{	int val = cctrue (12) ? 0xff : 0;
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpci (2);
return;
}

/* DBcc.W Dn,#<data>.W (GE) */
void REGPARAM2 CPUFUNC(op_5cc8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 58;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 offs = get_iword_cache_040 (2);
	uaecptr oldpc = m68k_getpci ();
	if (!cctrue (12)) {
	m68k_incpci ((uae_s32)offs + 2);
			m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xffff) | (((src - 1)) & 0xffff);
		if (src) {
			if (offs & 1) {
				exception3i (opcode, m68k_getpci () + 2 + (uae_s32)offs + 2);
				goto l_241111;
			}
			return;
		}
	} else {
	}
	m68k_setpci (oldpc + 4);
}}}l_241111: ;
return;
}

/* Scc.B (An) (GE) */
void REGPARAM2 CPUFUNC(op_5cd0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{{	int val = cctrue (12) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B (An)+ (GE) */
void REGPARAM2 CPUFUNC(op_5cd8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{{	int val = cctrue (12) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B -(An) (GE) */
void REGPARAM2 CPUFUNC(op_5ce0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
	m68k_areg (regs, srcreg) = srca;
{{	int val = cctrue (12) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B (d16,An) (GE) */
void REGPARAM2 CPUFUNC(op_5ce8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{{	int val = cctrue (12) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (4);
return;
}

/* Scc.B (d8,An,Xn) (GE) */
void REGPARAM2 CPUFUNC(op_5cf0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{{	int val = cctrue (12) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}}return;
}

/* Scc.B (xxx).W (GE) */
void REGPARAM2 CPUFUNC(op_5cf8_24)(uae_u32 opcode)
{
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{{	int val = cctrue (12) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (4);
return;
}

/* Scc.B (xxx).L (GE) */
void REGPARAM2 CPUFUNC(op_5cf9_24)(uae_u32 opcode)
{
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{{	int val = cctrue (12) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (6);
return;
}

/* TRAPcc.L #<data>.W (GE) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_5cfa_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{{	uae_s16 dummy = get_iword_cache_040 (2);
	if (cctrue (12)) { Exception (7); goto l_241119; }
}}	m68k_incpci (4);
l_241119: ;
return;
}

#endif
/* TRAPcc.L #<data>.L (GE) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_5cfb_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{{	uae_s32 dummy;
	dummy = get_ilong_cache_040 (2);
	if (cctrue (12)) { Exception (7); goto l_241120; }
}}	m68k_incpci (6);
l_241120: ;
return;
}

#endif
/* TRAPcc.L  (GE) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_5cfc_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{	if (cctrue (12)) { Exception (7); goto l_241121; }
}	m68k_incpci (2);
l_241121: ;
return;
}

#endif
/* Scc.B Dn (LT) */
void REGPARAM2 CPUFUNC(op_5dc0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{{{	int val = cctrue (13) ? 0xff : 0;
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpci (2);
return;
}

/* DBcc.W Dn,#<data>.W (LT) */
void REGPARAM2 CPUFUNC(op_5dc8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 58;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 offs = get_iword_cache_040 (2);
	uaecptr oldpc = m68k_getpci ();
	if (!cctrue (13)) {
	m68k_incpci ((uae_s32)offs + 2);
			m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xffff) | (((src - 1)) & 0xffff);
		if (src) {
			if (offs & 1) {
				exception3i (opcode, m68k_getpci () + 2 + (uae_s32)offs + 2);
				goto l_241123;
			}
			return;
		}
	} else {
	}
	m68k_setpci (oldpc + 4);
}}}l_241123: ;
return;
}

/* Scc.B (An) (LT) */
void REGPARAM2 CPUFUNC(op_5dd0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{{	int val = cctrue (13) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B (An)+ (LT) */
void REGPARAM2 CPUFUNC(op_5dd8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{{	int val = cctrue (13) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B -(An) (LT) */
void REGPARAM2 CPUFUNC(op_5de0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
	m68k_areg (regs, srcreg) = srca;
{{	int val = cctrue (13) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B (d16,An) (LT) */
void REGPARAM2 CPUFUNC(op_5de8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{{	int val = cctrue (13) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (4);
return;
}

/* Scc.B (d8,An,Xn) (LT) */
void REGPARAM2 CPUFUNC(op_5df0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{{	int val = cctrue (13) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}}return;
}

/* Scc.B (xxx).W (LT) */
void REGPARAM2 CPUFUNC(op_5df8_24)(uae_u32 opcode)
{
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{{	int val = cctrue (13) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (4);
return;
}

/* Scc.B (xxx).L (LT) */
void REGPARAM2 CPUFUNC(op_5df9_24)(uae_u32 opcode)
{
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{{	int val = cctrue (13) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (6);
return;
}

/* TRAPcc.L #<data>.W (LT) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_5dfa_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{{	uae_s16 dummy = get_iword_cache_040 (2);
	if (cctrue (13)) { Exception (7); goto l_241131; }
}}	m68k_incpci (4);
l_241131: ;
return;
}

#endif
/* TRAPcc.L #<data>.L (LT) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_5dfb_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{{	uae_s32 dummy;
	dummy = get_ilong_cache_040 (2);
	if (cctrue (13)) { Exception (7); goto l_241132; }
}}	m68k_incpci (6);
l_241132: ;
return;
}

#endif
/* TRAPcc.L  (LT) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_5dfc_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{	if (cctrue (13)) { Exception (7); goto l_241133; }
}	m68k_incpci (2);
l_241133: ;
return;
}

#endif
/* Scc.B Dn (GT) */
void REGPARAM2 CPUFUNC(op_5ec0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{{{	int val = cctrue (14) ? 0xff : 0;
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpci (2);
return;
}

/* DBcc.W Dn,#<data>.W (GT) */
void REGPARAM2 CPUFUNC(op_5ec8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 58;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 offs = get_iword_cache_040 (2);
	uaecptr oldpc = m68k_getpci ();
	if (!cctrue (14)) {
	m68k_incpci ((uae_s32)offs + 2);
			m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xffff) | (((src - 1)) & 0xffff);
		if (src) {
			if (offs & 1) {
				exception3i (opcode, m68k_getpci () + 2 + (uae_s32)offs + 2);
				goto l_241135;
			}
			return;
		}
	} else {
	}
	m68k_setpci (oldpc + 4);
}}}l_241135: ;
return;
}

/* Scc.B (An) (GT) */
void REGPARAM2 CPUFUNC(op_5ed0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{{	int val = cctrue (14) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B (An)+ (GT) */
void REGPARAM2 CPUFUNC(op_5ed8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{{	int val = cctrue (14) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B -(An) (GT) */
void REGPARAM2 CPUFUNC(op_5ee0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
	m68k_areg (regs, srcreg) = srca;
{{	int val = cctrue (14) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B (d16,An) (GT) */
void REGPARAM2 CPUFUNC(op_5ee8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{{	int val = cctrue (14) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (4);
return;
}

/* Scc.B (d8,An,Xn) (GT) */
void REGPARAM2 CPUFUNC(op_5ef0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{{	int val = cctrue (14) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}}return;
}

/* Scc.B (xxx).W (GT) */
void REGPARAM2 CPUFUNC(op_5ef8_24)(uae_u32 opcode)
{
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{{	int val = cctrue (14) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (4);
return;
}

/* Scc.B (xxx).L (GT) */
void REGPARAM2 CPUFUNC(op_5ef9_24)(uae_u32 opcode)
{
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{{	int val = cctrue (14) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (6);
return;
}

/* TRAPcc.L #<data>.W (GT) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_5efa_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{{	uae_s16 dummy = get_iword_cache_040 (2);
	if (cctrue (14)) { Exception (7); goto l_241143; }
}}	m68k_incpci (4);
l_241143: ;
return;
}

#endif
/* TRAPcc.L #<data>.L (GT) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_5efb_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{{	uae_s32 dummy;
	dummy = get_ilong_cache_040 (2);
	if (cctrue (14)) { Exception (7); goto l_241144; }
}}	m68k_incpci (6);
l_241144: ;
return;
}

#endif
/* TRAPcc.L  (GT) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_5efc_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{	if (cctrue (14)) { Exception (7); goto l_241145; }
}	m68k_incpci (2);
l_241145: ;
return;
}

#endif
/* Scc.B Dn (LE) */
void REGPARAM2 CPUFUNC(op_5fc0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{{{	int val = cctrue (15) ? 0xff : 0;
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpci (2);
return;
}

/* DBcc.W Dn,#<data>.W (LE) */
void REGPARAM2 CPUFUNC(op_5fc8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 58;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 offs = get_iword_cache_040 (2);
	uaecptr oldpc = m68k_getpci ();
	if (!cctrue (15)) {
	m68k_incpci ((uae_s32)offs + 2);
			m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xffff) | (((src - 1)) & 0xffff);
		if (src) {
			if (offs & 1) {
				exception3i (opcode, m68k_getpci () + 2 + (uae_s32)offs + 2);
				goto l_241147;
			}
			return;
		}
	} else {
	}
	m68k_setpci (oldpc + 4);
}}}l_241147: ;
return;
}

/* Scc.B (An) (LE) */
void REGPARAM2 CPUFUNC(op_5fd0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{{	int val = cctrue (15) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B (An)+ (LE) */
void REGPARAM2 CPUFUNC(op_5fd8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{{	int val = cctrue (15) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B -(An) (LE) */
void REGPARAM2 CPUFUNC(op_5fe0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
	m68k_areg (regs, srcreg) = srca;
{{	int val = cctrue (15) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (2);
return;
}

/* Scc.B (d16,An) (LE) */
void REGPARAM2 CPUFUNC(op_5fe8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{{	int val = cctrue (15) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (4);
return;
}

/* Scc.B (d8,An,Xn) (LE) */
void REGPARAM2 CPUFUNC(op_5ff0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 59;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{{	int val = cctrue (15) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}}return;
}

/* Scc.B (xxx).W (LE) */
void REGPARAM2 CPUFUNC(op_5ff8_24)(uae_u32 opcode)
{
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{{	int val = cctrue (15) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (4);
return;
}

/* Scc.B (xxx).L (LE) */
void REGPARAM2 CPUFUNC(op_5ff9_24)(uae_u32 opcode)
{
	OpcodeFamily = 59;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{{	int val = cctrue (15) ? 0xff : 0;
	x_put_byte (srca, val);
}}}}	m68k_incpci (6);
return;
}

/* TRAPcc.L #<data>.W (LE) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_5ffa_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{{	uae_s16 dummy = get_iword_cache_040 (2);
	if (cctrue (15)) { Exception (7); goto l_241155; }
}}	m68k_incpci (4);
l_241155: ;
return;
}

#endif
/* TRAPcc.L #<data>.L (LE) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_5ffb_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{{	uae_s32 dummy;
	dummy = get_ilong_cache_040 (2);
	if (cctrue (15)) { Exception (7); goto l_241156; }
}}	m68k_incpci (6);
l_241156: ;
return;
}

#endif
/* TRAPcc.L  (LE) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_5ffc_24)(uae_u32 opcode)
{
	OpcodeFamily = 102;
{	if (cctrue (15)) { Exception (7); goto l_241157; }
}	m68k_incpci (2);
l_241157: ;
return;
}

#endif
/* Bcc.W #<data>.W (T) */
void REGPARAM2 CPUFUNC(op_6000_24)(uae_u32 opcode)
{
	OpcodeFamily = 55;
{{	uae_s16 src = get_iword_cache_040 (2);
	if (!cctrue (0)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpci () + 2 + (uae_s32)src);
		goto l_241158;
	}
	m68k_incpci ((uae_s32)src + 2);
	return;
didnt_jump:;
	m68k_incpci (4);
}}l_241158: ;
return;
}

/* BccQ.B #<data> (T) */
void REGPARAM2 CPUFUNC(op_6001_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (uae_s32)(uae_s8)(opcode & 255);
	OpcodeFamily = 55;
{{	uae_u32 src = srcreg;
	if (!cctrue (0)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpci () + 2 + (uae_s32)src);
		goto l_241159;
	}
	m68k_incpci ((uae_s32)src + 2);
	return;
didnt_jump:;
	m68k_incpci (2);
}}l_241159: ;
return;
}

/* Bcc.L #<data>.L (T) */
void REGPARAM2 CPUFUNC(op_60ff_24)(uae_u32 opcode)
{
	OpcodeFamily = 55;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
	if (!cctrue (0)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpci () + 2 + (uae_s32)src);
		goto l_241160;
	}
	m68k_incpci ((uae_s32)src + 2);
	return;
didnt_jump:;
	m68k_incpci (6);
}}l_241160: ;
return;
}

/* BSR.W #<data>.W */
void REGPARAM2 CPUFUNC(op_6100_24)(uae_u32 opcode)
{
	OpcodeFamily = 54;
{	uae_s32 s;
{	uae_s16 src = get_iword_cache_040 (2);
	s = (uae_s32)src + 2;
	if (src & 1) {
		exception3b (opcode, m68k_getpci () + s, 0, 1, m68k_getpci () + s);
		goto l_241161;
	}
	m68k_do_bsri (m68k_getpci () + 4, s);
}}l_241161: ;
return;
}

/* BSRQ.B #<data> */
void REGPARAM2 CPUFUNC(op_6101_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (uae_s32)(uae_s8)(opcode & 255);
	OpcodeFamily = 54;
{	uae_s32 s;
{	uae_u32 src = srcreg;
	s = (uae_s32)src + 2;
	if (src & 1) {
		exception3b (opcode, m68k_getpci () + s, 0, 1, m68k_getpci () + s);
		goto l_241162;
	}
	m68k_do_bsri (m68k_getpci () + 2, s);
}}l_241162: ;
return;
}

/* BSR.L #<data>.L */
void REGPARAM2 CPUFUNC(op_61ff_24)(uae_u32 opcode)
{
	OpcodeFamily = 54;
{	uae_s32 s;
{	uae_s32 src;
	src = get_ilong_cache_040 (2);
	s = (uae_s32)src + 2;
	if (src & 1) {
		exception3b (opcode, m68k_getpci () + s, 0, 1, m68k_getpci () + s);
		goto l_241163;
	}
	m68k_do_bsri (m68k_getpci () + 6, s);
}}l_241163: ;
return;
}

/* Bcc.W #<data>.W (HI) */
void REGPARAM2 CPUFUNC(op_6200_24)(uae_u32 opcode)
{
	OpcodeFamily = 55;
{{	uae_s16 src = get_iword_cache_040 (2);
	if (!cctrue (2)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpci () + 2 + (uae_s32)src);
		goto l_241164;
	}
	m68k_incpci ((uae_s32)src + 2);
	return;
didnt_jump:;
	m68k_incpci (4);
}}l_241164: ;
return;
}

/* BccQ.B #<data> (HI) */
void REGPARAM2 CPUFUNC(op_6201_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (uae_s32)(uae_s8)(opcode & 255);
	OpcodeFamily = 55;
{{	uae_u32 src = srcreg;
	if (!cctrue (2)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpci () + 2 + (uae_s32)src);
		goto l_241165;
	}
	m68k_incpci ((uae_s32)src + 2);
	return;
didnt_jump:;
	m68k_incpci (2);
}}l_241165: ;
return;
}

/* Bcc.L #<data>.L (HI) */
void REGPARAM2 CPUFUNC(op_62ff_24)(uae_u32 opcode)
{
	OpcodeFamily = 55;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
	if (!cctrue (2)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpci () + 2 + (uae_s32)src);
		goto l_241166;
	}
	m68k_incpci ((uae_s32)src + 2);
	return;
didnt_jump:;
	m68k_incpci (6);
}}l_241166: ;
return;
}

/* Bcc.W #<data>.W (LS) */
void REGPARAM2 CPUFUNC(op_6300_24)(uae_u32 opcode)
{
	OpcodeFamily = 55;
{{	uae_s16 src = get_iword_cache_040 (2);
	if (!cctrue (3)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpci () + 2 + (uae_s32)src);
		goto l_241167;
	}
	m68k_incpci ((uae_s32)src + 2);
	return;
didnt_jump:;
	m68k_incpci (4);
}}l_241167: ;
return;
}

/* BccQ.B #<data> (LS) */
void REGPARAM2 CPUFUNC(op_6301_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (uae_s32)(uae_s8)(opcode & 255);
	OpcodeFamily = 55;
{{	uae_u32 src = srcreg;
	if (!cctrue (3)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpci () + 2 + (uae_s32)src);
		goto l_241168;
	}
	m68k_incpci ((uae_s32)src + 2);
	return;
didnt_jump:;
	m68k_incpci (2);
}}l_241168: ;
return;
}

#endif

#ifdef PART_6
/* Bcc.L #<data>.L (LS) */
void REGPARAM2 CPUFUNC(op_63ff_24)(uae_u32 opcode)
{
	OpcodeFamily = 55;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
	if (!cctrue (3)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpci () + 2 + (uae_s32)src);
		goto l_241169;
	}
	m68k_incpci ((uae_s32)src + 2);
	return;
didnt_jump:;
	m68k_incpci (6);
}}l_241169: ;
return;
}

/* Bcc.W #<data>.W (CC) */
void REGPARAM2 CPUFUNC(op_6400_24)(uae_u32 opcode)
{
	OpcodeFamily = 55;
{{	uae_s16 src = get_iword_cache_040 (2);
	if (!cctrue (4)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpci () + 2 + (uae_s32)src);
		goto l_241170;
	}
	m68k_incpci ((uae_s32)src + 2);
	return;
didnt_jump:;
	m68k_incpci (4);
}}l_241170: ;
return;
}

/* BccQ.B #<data> (CC) */
void REGPARAM2 CPUFUNC(op_6401_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (uae_s32)(uae_s8)(opcode & 255);
	OpcodeFamily = 55;
{{	uae_u32 src = srcreg;
	if (!cctrue (4)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpci () + 2 + (uae_s32)src);
		goto l_241171;
	}
	m68k_incpci ((uae_s32)src + 2);
	return;
didnt_jump:;
	m68k_incpci (2);
}}l_241171: ;
return;
}

/* Bcc.L #<data>.L (CC) */
void REGPARAM2 CPUFUNC(op_64ff_24)(uae_u32 opcode)
{
	OpcodeFamily = 55;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
	if (!cctrue (4)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpci () + 2 + (uae_s32)src);
		goto l_241172;
	}
	m68k_incpci ((uae_s32)src + 2);
	return;
didnt_jump:;
	m68k_incpci (6);
}}l_241172: ;
return;
}

/* Bcc.W #<data>.W (CS) */
void REGPARAM2 CPUFUNC(op_6500_24)(uae_u32 opcode)
{
	OpcodeFamily = 55;
{{	uae_s16 src = get_iword_cache_040 (2);
	if (!cctrue (5)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpci () + 2 + (uae_s32)src);
		goto l_241173;
	}
	m68k_incpci ((uae_s32)src + 2);
	return;
didnt_jump:;
	m68k_incpci (4);
}}l_241173: ;
return;
}

/* BccQ.B #<data> (CS) */
void REGPARAM2 CPUFUNC(op_6501_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (uae_s32)(uae_s8)(opcode & 255);
	OpcodeFamily = 55;
{{	uae_u32 src = srcreg;
	if (!cctrue (5)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpci () + 2 + (uae_s32)src);
		goto l_241174;
	}
	m68k_incpci ((uae_s32)src + 2);
	return;
didnt_jump:;
	m68k_incpci (2);
}}l_241174: ;
return;
}

/* Bcc.L #<data>.L (CS) */
void REGPARAM2 CPUFUNC(op_65ff_24)(uae_u32 opcode)
{
	OpcodeFamily = 55;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
	if (!cctrue (5)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpci () + 2 + (uae_s32)src);
		goto l_241175;
	}
	m68k_incpci ((uae_s32)src + 2);
	return;
didnt_jump:;
	m68k_incpci (6);
}}l_241175: ;
return;
}

/* Bcc.W #<data>.W (NE) */
void REGPARAM2 CPUFUNC(op_6600_24)(uae_u32 opcode)
{
	OpcodeFamily = 55;
{{	uae_s16 src = get_iword_cache_040 (2);
	if (!cctrue (6)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpci () + 2 + (uae_s32)src);
		goto l_241176;
	}
	m68k_incpci ((uae_s32)src + 2);
	return;
didnt_jump:;
	m68k_incpci (4);
}}l_241176: ;
return;
}

/* BccQ.B #<data> (NE) */
void REGPARAM2 CPUFUNC(op_6601_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (uae_s32)(uae_s8)(opcode & 255);
	OpcodeFamily = 55;
{{	uae_u32 src = srcreg;
	if (!cctrue (6)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpci () + 2 + (uae_s32)src);
		goto l_241177;
	}
	m68k_incpci ((uae_s32)src + 2);
	return;
didnt_jump:;
	m68k_incpci (2);
}}l_241177: ;
return;
}

/* Bcc.L #<data>.L (NE) */
void REGPARAM2 CPUFUNC(op_66ff_24)(uae_u32 opcode)
{
	OpcodeFamily = 55;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
	if (!cctrue (6)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpci () + 2 + (uae_s32)src);
		goto l_241178;
	}
	m68k_incpci ((uae_s32)src + 2);
	return;
didnt_jump:;
	m68k_incpci (6);
}}l_241178: ;
return;
}

/* Bcc.W #<data>.W (EQ) */
void REGPARAM2 CPUFUNC(op_6700_24)(uae_u32 opcode)
{
	OpcodeFamily = 55;
{{	uae_s16 src = get_iword_cache_040 (2);
	if (!cctrue (7)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpci () + 2 + (uae_s32)src);
		goto l_241179;
	}
	m68k_incpci ((uae_s32)src + 2);
	return;
didnt_jump:;
	m68k_incpci (4);
}}l_241179: ;
return;
}

/* BccQ.B #<data> (EQ) */
void REGPARAM2 CPUFUNC(op_6701_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (uae_s32)(uae_s8)(opcode & 255);
	OpcodeFamily = 55;
{{	uae_u32 src = srcreg;
	if (!cctrue (7)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpci () + 2 + (uae_s32)src);
		goto l_241180;
	}
	m68k_incpci ((uae_s32)src + 2);
	return;
didnt_jump:;
	m68k_incpci (2);
}}l_241180: ;
return;
}

/* Bcc.L #<data>.L (EQ) */
void REGPARAM2 CPUFUNC(op_67ff_24)(uae_u32 opcode)
{
	OpcodeFamily = 55;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
	if (!cctrue (7)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpci () + 2 + (uae_s32)src);
		goto l_241181;
	}
	m68k_incpci ((uae_s32)src + 2);
	return;
didnt_jump:;
	m68k_incpci (6);
}}l_241181: ;
return;
}

/* Bcc.W #<data>.W (VC) */
void REGPARAM2 CPUFUNC(op_6800_24)(uae_u32 opcode)
{
	OpcodeFamily = 55;
{{	uae_s16 src = get_iword_cache_040 (2);
	if (!cctrue (8)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpci () + 2 + (uae_s32)src);
		goto l_241182;
	}
	m68k_incpci ((uae_s32)src + 2);
	return;
didnt_jump:;
	m68k_incpci (4);
}}l_241182: ;
return;
}

/* BccQ.B #<data> (VC) */
void REGPARAM2 CPUFUNC(op_6801_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (uae_s32)(uae_s8)(opcode & 255);
	OpcodeFamily = 55;
{{	uae_u32 src = srcreg;
	if (!cctrue (8)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpci () + 2 + (uae_s32)src);
		goto l_241183;
	}
	m68k_incpci ((uae_s32)src + 2);
	return;
didnt_jump:;
	m68k_incpci (2);
}}l_241183: ;
return;
}

/* Bcc.L #<data>.L (VC) */
void REGPARAM2 CPUFUNC(op_68ff_24)(uae_u32 opcode)
{
	OpcodeFamily = 55;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
	if (!cctrue (8)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpci () + 2 + (uae_s32)src);
		goto l_241184;
	}
	m68k_incpci ((uae_s32)src + 2);
	return;
didnt_jump:;
	m68k_incpci (6);
}}l_241184: ;
return;
}

/* Bcc.W #<data>.W (VS) */
void REGPARAM2 CPUFUNC(op_6900_24)(uae_u32 opcode)
{
	OpcodeFamily = 55;
{{	uae_s16 src = get_iword_cache_040 (2);
	if (!cctrue (9)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpci () + 2 + (uae_s32)src);
		goto l_241185;
	}
	m68k_incpci ((uae_s32)src + 2);
	return;
didnt_jump:;
	m68k_incpci (4);
}}l_241185: ;
return;
}

/* BccQ.B #<data> (VS) */
void REGPARAM2 CPUFUNC(op_6901_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (uae_s32)(uae_s8)(opcode & 255);
	OpcodeFamily = 55;
{{	uae_u32 src = srcreg;
	if (!cctrue (9)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpci () + 2 + (uae_s32)src);
		goto l_241186;
	}
	m68k_incpci ((uae_s32)src + 2);
	return;
didnt_jump:;
	m68k_incpci (2);
}}l_241186: ;
return;
}

/* Bcc.L #<data>.L (VS) */
void REGPARAM2 CPUFUNC(op_69ff_24)(uae_u32 opcode)
{
	OpcodeFamily = 55;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
	if (!cctrue (9)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpci () + 2 + (uae_s32)src);
		goto l_241187;
	}
	m68k_incpci ((uae_s32)src + 2);
	return;
didnt_jump:;
	m68k_incpci (6);
}}l_241187: ;
return;
}

/* Bcc.W #<data>.W (PL) */
void REGPARAM2 CPUFUNC(op_6a00_24)(uae_u32 opcode)
{
	OpcodeFamily = 55;
{{	uae_s16 src = get_iword_cache_040 (2);
	if (!cctrue (10)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpci () + 2 + (uae_s32)src);
		goto l_241188;
	}
	m68k_incpci ((uae_s32)src + 2);
	return;
didnt_jump:;
	m68k_incpci (4);
}}l_241188: ;
return;
}

/* BccQ.B #<data> (PL) */
void REGPARAM2 CPUFUNC(op_6a01_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (uae_s32)(uae_s8)(opcode & 255);
	OpcodeFamily = 55;
{{	uae_u32 src = srcreg;
	if (!cctrue (10)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpci () + 2 + (uae_s32)src);
		goto l_241189;
	}
	m68k_incpci ((uae_s32)src + 2);
	return;
didnt_jump:;
	m68k_incpci (2);
}}l_241189: ;
return;
}

/* Bcc.L #<data>.L (PL) */
void REGPARAM2 CPUFUNC(op_6aff_24)(uae_u32 opcode)
{
	OpcodeFamily = 55;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
	if (!cctrue (10)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpci () + 2 + (uae_s32)src);
		goto l_241190;
	}
	m68k_incpci ((uae_s32)src + 2);
	return;
didnt_jump:;
	m68k_incpci (6);
}}l_241190: ;
return;
}

/* Bcc.W #<data>.W (MI) */
void REGPARAM2 CPUFUNC(op_6b00_24)(uae_u32 opcode)
{
	OpcodeFamily = 55;
{{	uae_s16 src = get_iword_cache_040 (2);
	if (!cctrue (11)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpci () + 2 + (uae_s32)src);
		goto l_241191;
	}
	m68k_incpci ((uae_s32)src + 2);
	return;
didnt_jump:;
	m68k_incpci (4);
}}l_241191: ;
return;
}

/* BccQ.B #<data> (MI) */
void REGPARAM2 CPUFUNC(op_6b01_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (uae_s32)(uae_s8)(opcode & 255);
	OpcodeFamily = 55;
{{	uae_u32 src = srcreg;
	if (!cctrue (11)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpci () + 2 + (uae_s32)src);
		goto l_241192;
	}
	m68k_incpci ((uae_s32)src + 2);
	return;
didnt_jump:;
	m68k_incpci (2);
}}l_241192: ;
return;
}

/* Bcc.L #<data>.L (MI) */
void REGPARAM2 CPUFUNC(op_6bff_24)(uae_u32 opcode)
{
	OpcodeFamily = 55;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
	if (!cctrue (11)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpci () + 2 + (uae_s32)src);
		goto l_241193;
	}
	m68k_incpci ((uae_s32)src + 2);
	return;
didnt_jump:;
	m68k_incpci (6);
}}l_241193: ;
return;
}

/* Bcc.W #<data>.W (GE) */
void REGPARAM2 CPUFUNC(op_6c00_24)(uae_u32 opcode)
{
	OpcodeFamily = 55;
{{	uae_s16 src = get_iword_cache_040 (2);
	if (!cctrue (12)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpci () + 2 + (uae_s32)src);
		goto l_241194;
	}
	m68k_incpci ((uae_s32)src + 2);
	return;
didnt_jump:;
	m68k_incpci (4);
}}l_241194: ;
return;
}

/* BccQ.B #<data> (GE) */
void REGPARAM2 CPUFUNC(op_6c01_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (uae_s32)(uae_s8)(opcode & 255);
	OpcodeFamily = 55;
{{	uae_u32 src = srcreg;
	if (!cctrue (12)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpci () + 2 + (uae_s32)src);
		goto l_241195;
	}
	m68k_incpci ((uae_s32)src + 2);
	return;
didnt_jump:;
	m68k_incpci (2);
}}l_241195: ;
return;
}

/* Bcc.L #<data>.L (GE) */
void REGPARAM2 CPUFUNC(op_6cff_24)(uae_u32 opcode)
{
	OpcodeFamily = 55;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
	if (!cctrue (12)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpci () + 2 + (uae_s32)src);
		goto l_241196;
	}
	m68k_incpci ((uae_s32)src + 2);
	return;
didnt_jump:;
	m68k_incpci (6);
}}l_241196: ;
return;
}

/* Bcc.W #<data>.W (LT) */
void REGPARAM2 CPUFUNC(op_6d00_24)(uae_u32 opcode)
{
	OpcodeFamily = 55;
{{	uae_s16 src = get_iword_cache_040 (2);
	if (!cctrue (13)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpci () + 2 + (uae_s32)src);
		goto l_241197;
	}
	m68k_incpci ((uae_s32)src + 2);
	return;
didnt_jump:;
	m68k_incpci (4);
}}l_241197: ;
return;
}

/* BccQ.B #<data> (LT) */
void REGPARAM2 CPUFUNC(op_6d01_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (uae_s32)(uae_s8)(opcode & 255);
	OpcodeFamily = 55;
{{	uae_u32 src = srcreg;
	if (!cctrue (13)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpci () + 2 + (uae_s32)src);
		goto l_241198;
	}
	m68k_incpci ((uae_s32)src + 2);
	return;
didnt_jump:;
	m68k_incpci (2);
}}l_241198: ;
return;
}

/* Bcc.L #<data>.L (LT) */
void REGPARAM2 CPUFUNC(op_6dff_24)(uae_u32 opcode)
{
	OpcodeFamily = 55;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
	if (!cctrue (13)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpci () + 2 + (uae_s32)src);
		goto l_241199;
	}
	m68k_incpci ((uae_s32)src + 2);
	return;
didnt_jump:;
	m68k_incpci (6);
}}l_241199: ;
return;
}

/* Bcc.W #<data>.W (GT) */
void REGPARAM2 CPUFUNC(op_6e00_24)(uae_u32 opcode)
{
	OpcodeFamily = 55;
{{	uae_s16 src = get_iword_cache_040 (2);
	if (!cctrue (14)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpci () + 2 + (uae_s32)src);
		goto l_241200;
	}
	m68k_incpci ((uae_s32)src + 2);
	return;
didnt_jump:;
	m68k_incpci (4);
}}l_241200: ;
return;
}

/* BccQ.B #<data> (GT) */
void REGPARAM2 CPUFUNC(op_6e01_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (uae_s32)(uae_s8)(opcode & 255);
	OpcodeFamily = 55;
{{	uae_u32 src = srcreg;
	if (!cctrue (14)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpci () + 2 + (uae_s32)src);
		goto l_241201;
	}
	m68k_incpci ((uae_s32)src + 2);
	return;
didnt_jump:;
	m68k_incpci (2);
}}l_241201: ;
return;
}

/* Bcc.L #<data>.L (GT) */
void REGPARAM2 CPUFUNC(op_6eff_24)(uae_u32 opcode)
{
	OpcodeFamily = 55;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
	if (!cctrue (14)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpci () + 2 + (uae_s32)src);
		goto l_241202;
	}
	m68k_incpci ((uae_s32)src + 2);
	return;
didnt_jump:;
	m68k_incpci (6);
}}l_241202: ;
return;
}

/* Bcc.W #<data>.W (LE) */
void REGPARAM2 CPUFUNC(op_6f00_24)(uae_u32 opcode)
{
	OpcodeFamily = 55;
{{	uae_s16 src = get_iword_cache_040 (2);
	if (!cctrue (15)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpci () + 2 + (uae_s32)src);
		goto l_241203;
	}
	m68k_incpci ((uae_s32)src + 2);
	return;
didnt_jump:;
	m68k_incpci (4);
}}l_241203: ;
return;
}

/* BccQ.B #<data> (LE) */
void REGPARAM2 CPUFUNC(op_6f01_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (uae_s32)(uae_s8)(opcode & 255);
	OpcodeFamily = 55;
{{	uae_u32 src = srcreg;
	if (!cctrue (15)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpci () + 2 + (uae_s32)src);
		goto l_241204;
	}
	m68k_incpci ((uae_s32)src + 2);
	return;
didnt_jump:;
	m68k_incpci (2);
}}l_241204: ;
return;
}

/* Bcc.L #<data>.L (LE) */
void REGPARAM2 CPUFUNC(op_6fff_24)(uae_u32 opcode)
{
	OpcodeFamily = 55;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
	if (!cctrue (15)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpci () + 2 + (uae_s32)src);
		goto l_241205;
	}
	m68k_incpci ((uae_s32)src + 2);
	return;
didnt_jump:;
	m68k_incpci (6);
}}l_241205: ;
return;
}

/* MOVEQ.L #<data>,Dn */
void REGPARAM2 CPUFUNC(op_7000_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (uae_s32)(uae_s8)(opcode & 255);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 30;
{{	uae_u32 src = srcreg;
{	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	m68k_dreg (regs, dstreg) = (src);
	m68k_incpci (2);
}}}return;
}

/* OR.B Dn,Dn */
void REGPARAM2 CPUFUNC(op_8000_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 1;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}	m68k_incpci (2);
return;
}

/* OR.B (An),Dn */
void REGPARAM2 CPUFUNC(op_8010_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 1;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s8 src = x_get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}}	m68k_incpci (2);
return;
}

/* OR.B (An)+,Dn */
void REGPARAM2 CPUFUNC(op_8018_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 1;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s8 src = x_get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}}	m68k_incpci (2);
return;
}

/* OR.B -(An),Dn */
void REGPARAM2 CPUFUNC(op_8020_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 1;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = x_get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}}	m68k_incpci (2);
return;
}

/* OR.B (d16,An),Dn */
void REGPARAM2 CPUFUNC(op_8028_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 1;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}}	m68k_incpci (4);
return;
}

/* OR.B (d8,An,Xn),Dn */
void REGPARAM2 CPUFUNC(op_8030_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 1;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s8 src = x_get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}}}return;
}

/* OR.B (xxx).W,Dn */
void REGPARAM2 CPUFUNC(op_8038_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 1;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}}	m68k_incpci (4);
return;
}

/* OR.B (xxx).L,Dn */
void REGPARAM2 CPUFUNC(op_8039_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 1;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}}	m68k_incpci (6);
return;
}

/* OR.B (d16,PC),Dn */
void REGPARAM2 CPUFUNC(op_803a_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 1;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}}	m68k_incpci (4);
return;
}

/* OR.B (d8,PC,Xn),Dn */
void REGPARAM2 CPUFUNC(op_803b_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 1;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s8 src = x_get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}}}return;
}

/* OR.B #<data>.B,Dn */
void REGPARAM2 CPUFUNC(op_803c_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 1;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}	m68k_incpci (4);
return;
}

/* OR.W Dn,Dn */
void REGPARAM2 CPUFUNC(op_8040_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 1;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}	m68k_incpci (2);
return;
}

/* OR.W (An),Dn */
void REGPARAM2 CPUFUNC(op_8050_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 1;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}}	m68k_incpci (2);
return;
}

/* OR.W (An)+,Dn */
void REGPARAM2 CPUFUNC(op_8058_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 1;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}}	m68k_incpci (2);
return;
}

/* OR.W -(An),Dn */
void REGPARAM2 CPUFUNC(op_8060_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 1;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}}	m68k_incpci (2);
return;
}

/* OR.W (d16,An),Dn */
void REGPARAM2 CPUFUNC(op_8068_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 1;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}}	m68k_incpci (4);
return;
}

/* OR.W (d8,An,Xn),Dn */
void REGPARAM2 CPUFUNC(op_8070_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 1;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}}}return;
}

/* OR.W (xxx).W,Dn */
void REGPARAM2 CPUFUNC(op_8078_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 1;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}}	m68k_incpci (4);
return;
}

/* OR.W (xxx).L,Dn */
void REGPARAM2 CPUFUNC(op_8079_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 1;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}}	m68k_incpci (6);
return;
}

/* OR.W (d16,PC),Dn */
void REGPARAM2 CPUFUNC(op_807a_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 1;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}}	m68k_incpci (4);
return;
}

/* OR.W (d8,PC,Xn),Dn */
void REGPARAM2 CPUFUNC(op_807b_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 1;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}}}return;
}

/* OR.W #<data>.W,Dn */
void REGPARAM2 CPUFUNC(op_807c_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 1;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}	m68k_incpci (4);
return;
}

/* OR.L Dn,Dn */
void REGPARAM2 CPUFUNC(op_8080_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 1;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	m68k_dreg (regs, dstreg) = (src);
}}}	m68k_incpci (2);
return;
}

/* OR.L (An),Dn */
void REGPARAM2 CPUFUNC(op_8090_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 1;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	m68k_dreg (regs, dstreg) = (src);
}}}}	m68k_incpci (2);
return;
}

/* OR.L (An)+,Dn */
void REGPARAM2 CPUFUNC(op_8098_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 1;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, srcreg) += 4;
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	m68k_dreg (regs, dstreg) = (src);
}}}}	m68k_incpci (2);
return;
}

/* OR.L -(An),Dn */
void REGPARAM2 CPUFUNC(op_80a0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 1;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	m68k_dreg (regs, dstreg) = (src);
}}}}	m68k_incpci (2);
return;
}

/* OR.L (d16,An),Dn */
void REGPARAM2 CPUFUNC(op_80a8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 1;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	m68k_dreg (regs, dstreg) = (src);
}}}}	m68k_incpci (4);
return;
}

/* OR.L (d8,An,Xn),Dn */
void REGPARAM2 CPUFUNC(op_80b0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 1;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	m68k_dreg (regs, dstreg) = (src);
}}}}}return;
}

/* OR.L (xxx).W,Dn */
void REGPARAM2 CPUFUNC(op_80b8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 1;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	m68k_dreg (regs, dstreg) = (src);
}}}}	m68k_incpci (4);
return;
}

/* OR.L (xxx).L,Dn */
void REGPARAM2 CPUFUNC(op_80b9_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 1;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	m68k_dreg (regs, dstreg) = (src);
}}}}	m68k_incpci (6);
return;
}

/* OR.L (d16,PC),Dn */
void REGPARAM2 CPUFUNC(op_80ba_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 1;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	m68k_dreg (regs, dstreg) = (src);
}}}}	m68k_incpci (4);
return;
}

/* OR.L (d8,PC,Xn),Dn */
void REGPARAM2 CPUFUNC(op_80bb_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 1;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	m68k_dreg (regs, dstreg) = (src);
}}}}}return;
}

/* OR.L #<data>.L,Dn */
void REGPARAM2 CPUFUNC(op_80bc_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 1;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	m68k_dreg (regs, dstreg) = (src);
}}}	m68k_incpci (6);
return;
}

/* DIVU.W Dn,Dn */
void REGPARAM2 CPUFUNC(op_80c0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 60;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	CLEAR_CZNV ();
	if (src == 0) {
		divbyzero_special (0, dst);
	m68k_incpci (2);
		Exception (5);
		goto l_241240;
	} else {
		uae_u32 newv = (uae_u32)dst / (uae_u32)(uae_u16)src;
		uae_u32 rem = (uae_u32)dst % (uae_u32)(uae_u16)src;
		if (newv > 0xffff) {
			SET_VFLG (1);
			SET_NFLG (1);
		} else {
			CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_NFLG (((uae_s16)(newv)) < 0);
			newv = (newv & 0xffff) | ((uae_u32)rem << 16);
			m68k_dreg (regs, dstreg) = (newv);
		}
	m68k_incpci (2);
	}
}}}l_241240: ;
return;
}

/* DIVU.W (An),Dn */
void REGPARAM2 CPUFUNC(op_80d0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 60;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	CLEAR_CZNV ();
	if (src == 0) {
		divbyzero_special (0, dst);
	m68k_incpci (2);
		Exception (5);
		goto l_241241;
	} else {
		uae_u32 newv = (uae_u32)dst / (uae_u32)(uae_u16)src;
		uae_u32 rem = (uae_u32)dst % (uae_u32)(uae_u16)src;
		if (newv > 0xffff) {
			SET_VFLG (1);
			SET_NFLG (1);
		} else {
			CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_NFLG (((uae_s16)(newv)) < 0);
			newv = (newv & 0xffff) | ((uae_u32)rem << 16);
			m68k_dreg (regs, dstreg) = (newv);
		}
	m68k_incpci (2);
	}
}}}}l_241241: ;
return;
}

/* DIVU.W (An)+,Dn */
void REGPARAM2 CPUFUNC(op_80d8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 60;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	CLEAR_CZNV ();
	if (src == 0) {
		divbyzero_special (0, dst);
	m68k_incpci (2);
		Exception (5);
		goto l_241242;
	} else {
		uae_u32 newv = (uae_u32)dst / (uae_u32)(uae_u16)src;
		uae_u32 rem = (uae_u32)dst % (uae_u32)(uae_u16)src;
		if (newv > 0xffff) {
			SET_VFLG (1);
			SET_NFLG (1);
		} else {
			CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_NFLG (((uae_s16)(newv)) < 0);
			newv = (newv & 0xffff) | ((uae_u32)rem << 16);
			m68k_dreg (regs, dstreg) = (newv);
		}
	m68k_incpci (2);
	}
}}}}l_241242: ;
return;
}

/* DIVU.W -(An),Dn */
void REGPARAM2 CPUFUNC(op_80e0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 60;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	CLEAR_CZNV ();
	if (src == 0) {
		divbyzero_special (0, dst);
	m68k_incpci (2);
		Exception (5);
		goto l_241243;
	} else {
		uae_u32 newv = (uae_u32)dst / (uae_u32)(uae_u16)src;
		uae_u32 rem = (uae_u32)dst % (uae_u32)(uae_u16)src;
		if (newv > 0xffff) {
			SET_VFLG (1);
			SET_NFLG (1);
		} else {
			CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_NFLG (((uae_s16)(newv)) < 0);
			newv = (newv & 0xffff) | ((uae_u32)rem << 16);
			m68k_dreg (regs, dstreg) = (newv);
		}
	m68k_incpci (2);
	}
}}}}l_241243: ;
return;
}

/* DIVU.W (d16,An),Dn */
void REGPARAM2 CPUFUNC(op_80e8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 60;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	CLEAR_CZNV ();
	if (src == 0) {
		divbyzero_special (0, dst);
	m68k_incpci (4);
		Exception (5);
		goto l_241244;
	} else {
		uae_u32 newv = (uae_u32)dst / (uae_u32)(uae_u16)src;
		uae_u32 rem = (uae_u32)dst % (uae_u32)(uae_u16)src;
		if (newv > 0xffff) {
			SET_VFLG (1);
			SET_NFLG (1);
		} else {
			CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_NFLG (((uae_s16)(newv)) < 0);
			newv = (newv & 0xffff) | ((uae_u32)rem << 16);
			m68k_dreg (regs, dstreg) = (newv);
		}
	m68k_incpci (4);
	}
}}}}l_241244: ;
return;
}

/* DIVU.W (d8,An,Xn),Dn */
void REGPARAM2 CPUFUNC(op_80f0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 60;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s16 src = x_get_word (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	CLEAR_CZNV ();
	if (src == 0) {
		divbyzero_special (0, dst);
	m68k_incpci (0);
		Exception (5);
		goto l_241245;
	} else {
		uae_u32 newv = (uae_u32)dst / (uae_u32)(uae_u16)src;
		uae_u32 rem = (uae_u32)dst % (uae_u32)(uae_u16)src;
		if (newv > 0xffff) {
			SET_VFLG (1);
			SET_NFLG (1);
		} else {
			CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_NFLG (((uae_s16)(newv)) < 0);
			newv = (newv & 0xffff) | ((uae_u32)rem << 16);
			m68k_dreg (regs, dstreg) = (newv);
		}
	}
}}}}}l_241245: ;
return;
}

/* DIVU.W (xxx).W,Dn */
void REGPARAM2 CPUFUNC(op_80f8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 60;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	CLEAR_CZNV ();
	if (src == 0) {
		divbyzero_special (0, dst);
	m68k_incpci (4);
		Exception (5);
		goto l_241246;
	} else {
		uae_u32 newv = (uae_u32)dst / (uae_u32)(uae_u16)src;
		uae_u32 rem = (uae_u32)dst % (uae_u32)(uae_u16)src;
		if (newv > 0xffff) {
			SET_VFLG (1);
			SET_NFLG (1);
		} else {
			CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_NFLG (((uae_s16)(newv)) < 0);
			newv = (newv & 0xffff) | ((uae_u32)rem << 16);
			m68k_dreg (regs, dstreg) = (newv);
		}
	m68k_incpci (4);
	}
}}}}l_241246: ;
return;
}

/* DIVU.W (xxx).L,Dn */
void REGPARAM2 CPUFUNC(op_80f9_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 60;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	CLEAR_CZNV ();
	if (src == 0) {
		divbyzero_special (0, dst);
	m68k_incpci (6);
		Exception (5);
		goto l_241247;
	} else {
		uae_u32 newv = (uae_u32)dst / (uae_u32)(uae_u16)src;
		uae_u32 rem = (uae_u32)dst % (uae_u32)(uae_u16)src;
		if (newv > 0xffff) {
			SET_VFLG (1);
			SET_NFLG (1);
		} else {
			CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_NFLG (((uae_s16)(newv)) < 0);
			newv = (newv & 0xffff) | ((uae_u32)rem << 16);
			m68k_dreg (regs, dstreg) = (newv);
		}
	m68k_incpci (6);
	}
}}}}l_241247: ;
return;
}

/* DIVU.W (d16,PC),Dn */
void REGPARAM2 CPUFUNC(op_80fa_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 60;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	CLEAR_CZNV ();
	if (src == 0) {
		divbyzero_special (0, dst);
	m68k_incpci (4);
		Exception (5);
		goto l_241248;
	} else {
		uae_u32 newv = (uae_u32)dst / (uae_u32)(uae_u16)src;
		uae_u32 rem = (uae_u32)dst % (uae_u32)(uae_u16)src;
		if (newv > 0xffff) {
			SET_VFLG (1);
			SET_NFLG (1);
		} else {
			CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_NFLG (((uae_s16)(newv)) < 0);
			newv = (newv & 0xffff) | ((uae_u32)rem << 16);
			m68k_dreg (regs, dstreg) = (newv);
		}
	m68k_incpci (4);
	}
}}}}l_241248: ;
return;
}

/* DIVU.W (d8,PC,Xn),Dn */
void REGPARAM2 CPUFUNC(op_80fb_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 60;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s16 src = x_get_word (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	CLEAR_CZNV ();
	if (src == 0) {
		divbyzero_special (0, dst);
	m68k_incpci (0);
		Exception (5);
		goto l_241249;
	} else {
		uae_u32 newv = (uae_u32)dst / (uae_u32)(uae_u16)src;
		uae_u32 rem = (uae_u32)dst % (uae_u32)(uae_u16)src;
		if (newv > 0xffff) {
			SET_VFLG (1);
			SET_NFLG (1);
		} else {
			CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_NFLG (((uae_s16)(newv)) < 0);
			newv = (newv & 0xffff) | ((uae_u32)rem << 16);
			m68k_dreg (regs, dstreg) = (newv);
		}
	}
}}}}}l_241249: ;
return;
}

/* DIVU.W #<data>.W,Dn */
void REGPARAM2 CPUFUNC(op_80fc_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 60;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	CLEAR_CZNV ();
	if (src == 0) {
		divbyzero_special (0, dst);
	m68k_incpci (4);
		Exception (5);
		goto l_241250;
	} else {
		uae_u32 newv = (uae_u32)dst / (uae_u32)(uae_u16)src;
		uae_u32 rem = (uae_u32)dst % (uae_u32)(uae_u16)src;
		if (newv > 0xffff) {
			SET_VFLG (1);
			SET_NFLG (1);
		} else {
			CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_NFLG (((uae_s16)(newv)) < 0);
			newv = (newv & 0xffff) | ((uae_u32)rem << 16);
			m68k_dreg (regs, dstreg) = (newv);
		}
	m68k_incpci (4);
	}
}}}l_241250: ;
return;
}

/* SBCD.B Dn,Dn */
void REGPARAM2 CPUFUNC(op_8100_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 10;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
{	uae_u16 newv_lo = (dst & 0xF) - (src & 0xF) - (GET_XFLG () ? 1 : 0);
	uae_u16 newv_hi = (dst & 0xF0) - (src & 0xF0);
	uae_u16 newv, tmp_newv;
	int bcd = 0;
	newv = tmp_newv = newv_hi + newv_lo;
	if (newv_lo & 0xF0) { newv -= 6; bcd = 6; };
	if ((((dst & 0xFF) - (src & 0xFF) - (GET_XFLG () ? 1 : 0)) & 0x100) > 0xFF) { newv -= 0x60; }
	SET_CFLG ((((dst & 0xFF) - (src & 0xFF) - bcd - (GET_XFLG () ? 1 : 0)) & 0x300) > 0xFF);
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s8)(newv)) == 0));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}	m68k_incpci (2);
return;
}

/* SBCD.B -(An),-(An) */
void REGPARAM2 CPUFUNC(op_8108_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 10;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = x_get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
{	uae_u16 newv_lo = (dst & 0xF) - (src & 0xF) - (GET_XFLG () ? 1 : 0);
	uae_u16 newv_hi = (dst & 0xF0) - (src & 0xF0);
	uae_u16 newv, tmp_newv;
	int bcd = 0;
	newv = tmp_newv = newv_hi + newv_lo;
	if (newv_lo & 0xF0) { newv -= 6; bcd = 6; };
	if ((((dst & 0xFF) - (src & 0xFF) - (GET_XFLG () ? 1 : 0)) & 0x100) > 0xFF) { newv -= 0x60; }
	SET_CFLG ((((dst & 0xFF) - (src & 0xFF) - bcd - (GET_XFLG () ? 1 : 0)) & 0x300) > 0xFF);
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s8)(newv)) == 0));
	x_put_byte (dsta, newv);
}}}}}}	m68k_incpci (2);
return;
}

/* OR.B Dn,(An) */
void REGPARAM2 CPUFUNC(op_8110_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 1;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = x_get_byte (dsta);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}	m68k_incpci (2);
return;
}

/* OR.B Dn,(An)+ */
void REGPARAM2 CPUFUNC(op_8118_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 1;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}	m68k_incpci (2);
return;
}

/* OR.B Dn,-(An) */
void REGPARAM2 CPUFUNC(op_8120_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 1;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}	m68k_incpci (2);
return;
}

/* OR.B Dn,(d16,An) */
void REGPARAM2 CPUFUNC(op_8128_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 1;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 dst = x_get_byte (dsta);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}	m68k_incpci (4);
return;
}

/* OR.B Dn,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_8130_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 1;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	m68k_incpci (2);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s8 dst = x_get_byte (dsta);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}}return;
}

/* OR.B Dn,(xxx).W */
void REGPARAM2 CPUFUNC(op_8138_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	OpcodeFamily = 1;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 dst = x_get_byte (dsta);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}	m68k_incpci (4);
return;
}

/* OR.B Dn,(xxx).L */
void REGPARAM2 CPUFUNC(op_8139_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	OpcodeFamily = 1;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (2);
{	uae_s8 dst = x_get_byte (dsta);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}	m68k_incpci (6);
return;
}

/* PACK.L Dn,Dn */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_8140_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 96;
{	uae_u16 val = m68k_dreg (regs, srcreg) + get_iword_cache_040 (2);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & 0xffffff00) | ((val >> 4) & 0xf0) | (val & 0xf);
}	m68k_incpci (4);
return;
}

#endif
/* PACK.L -(An),-(An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_8148_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 96;
{	uae_u16 val;
	m68k_areg (regs, srcreg) -= areg_byteinc[srcreg];
	val = (uae_u16)(x_get_byte (m68k_areg (regs, srcreg)) & 0xff);
	m68k_areg (regs, srcreg) -= areg_byteinc[srcreg];
	val = (val | ((uae_u16)(x_get_byte (m68k_areg (regs, srcreg)) & 0xff) << 8)) + get_iword_cache_040 (2);
	m68k_areg (regs, dstreg) -= areg_byteinc[dstreg];
	x_put_byte (m68k_areg (regs, dstreg),((val >> 4) & 0xf0) | (val & 0xf));
}	m68k_incpci (4);
return;
}

#endif
/* OR.W Dn,(An) */
void REGPARAM2 CPUFUNC(op_8150_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 1;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s16 dst = x_get_word (dsta);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}	m68k_incpci (2);
return;
}

/* OR.W Dn,(An)+ */
void REGPARAM2 CPUFUNC(op_8158_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 1;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s16 dst = x_get_word (dsta);
	m68k_areg (regs, dstreg) += 2;
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}	m68k_incpci (2);
return;
}

/* OR.W Dn,-(An) */
void REGPARAM2 CPUFUNC(op_8160_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 1;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
{	uae_s16 dst = x_get_word (dsta);
	m68k_areg (regs, dstreg) = dsta;
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}	m68k_incpci (2);
return;
}

/* OR.W Dn,(d16,An) */
void REGPARAM2 CPUFUNC(op_8168_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 1;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 dst = x_get_word (dsta);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}	m68k_incpci (4);
return;
}

/* OR.W Dn,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_8170_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 1;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	m68k_incpci (2);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s16 dst = x_get_word (dsta);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}}return;
}

/* OR.W Dn,(xxx).W */
void REGPARAM2 CPUFUNC(op_8178_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	OpcodeFamily = 1;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 dst = x_get_word (dsta);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}	m68k_incpci (4);
return;
}

/* OR.W Dn,(xxx).L */
void REGPARAM2 CPUFUNC(op_8179_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	OpcodeFamily = 1;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (2);
{	uae_s16 dst = x_get_word (dsta);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}	m68k_incpci (6);
return;
}

/* UNPK.L Dn,Dn */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_8180_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 97;
{	uae_u16 val = m68k_dreg (regs, srcreg);
	val = (((val << 4) & 0xf00) | (val & 0xf)) + get_iword_cache_040 (2);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & 0xffff0000) | (val & 0xffff);
}	m68k_incpci (4);
return;
}

#endif
/* UNPK.L -(An),-(An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_8188_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 97;
{	uae_u16 val;
	m68k_areg (regs, srcreg) -= areg_byteinc[srcreg];
	val = (uae_u16)(x_get_byte (m68k_areg (regs, srcreg)) & 0xff);
	val = (((val << 4) & 0xf00) | (val & 0xf)) + get_iword_cache_040 (2);
	m68k_areg (regs, dstreg) -= 2 * areg_byteinc[dstreg];
	x_put_byte (m68k_areg (regs, dstreg) + areg_byteinc[dstreg], val);
	x_put_byte (m68k_areg (regs, dstreg), val >> 8);
}	m68k_incpci (4);
return;
}

#endif
/* OR.L Dn,(An) */
void REGPARAM2 CPUFUNC(op_8190_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 1;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s32 dst = x_get_long (dsta);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}	m68k_incpci (2);
return;
}

/* OR.L Dn,(An)+ */
void REGPARAM2 CPUFUNC(op_8198_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 1;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s32 dst = x_get_long (dsta);
	m68k_areg (regs, dstreg) += 4;
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}	m68k_incpci (2);
return;
}

/* OR.L Dn,-(An) */
void REGPARAM2 CPUFUNC(op_81a0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 1;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
{	uae_s32 dst = x_get_long (dsta);
	m68k_areg (regs, dstreg) = dsta;
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}	m68k_incpci (2);
return;
}

/* OR.L Dn,(d16,An) */
void REGPARAM2 CPUFUNC(op_81a8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 1;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 dst = x_get_long (dsta);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}	m68k_incpci (4);
return;
}

/* OR.L Dn,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_81b0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 1;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	m68k_incpci (2);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s32 dst = x_get_long (dsta);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}}return;
}

/* OR.L Dn,(xxx).W */
void REGPARAM2 CPUFUNC(op_81b8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	OpcodeFamily = 1;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 dst = x_get_long (dsta);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}	m68k_incpci (4);
return;
}

/* OR.L Dn,(xxx).L */
void REGPARAM2 CPUFUNC(op_81b9_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	OpcodeFamily = 1;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (2);
{	uae_s32 dst = x_get_long (dsta);
	src |= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}	m68k_incpci (6);
return;
}

/* DIVS.W Dn,Dn */
void REGPARAM2 CPUFUNC(op_81c0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 61;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	if (src == 0) {
		divbyzero_special (1, dst);
	m68k_incpci (2);
		Exception (5);
		goto l_241278;
	}
	CLEAR_CZNV ();
	if (dst == 0x80000000 && src == -1) {
		SET_VFLG (1);
		SET_NFLG (1);
	} else {
		uae_s32 newv = (uae_s32)dst / (uae_s32)(uae_s16)src;
		uae_u16 rem = (uae_s32)dst % (uae_s32)(uae_s16)src;
		if ((newv & 0xffff8000) != 0 && (newv & 0xffff8000) != 0xffff8000) {
			SET_VFLG (1);
			SET_NFLG (1);
		} else {
			if (((uae_s16)rem < 0) != ((uae_s32)dst < 0)) rem = -rem;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_NFLG (((uae_s16)(newv)) < 0);
			newv = (newv & 0xffff) | ((uae_u32)rem << 16);
			m68k_dreg (regs, dstreg) = (newv);
		}
	}
	m68k_incpci (2);
}}}l_241278: ;
return;
}

/* DIVS.W (An),Dn */
void REGPARAM2 CPUFUNC(op_81d0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 61;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	if (src == 0) {
		divbyzero_special (1, dst);
	m68k_incpci (2);
		Exception (5);
		goto l_241279;
	}
	CLEAR_CZNV ();
	if (dst == 0x80000000 && src == -1) {
		SET_VFLG (1);
		SET_NFLG (1);
	} else {
		uae_s32 newv = (uae_s32)dst / (uae_s32)(uae_s16)src;
		uae_u16 rem = (uae_s32)dst % (uae_s32)(uae_s16)src;
		if ((newv & 0xffff8000) != 0 && (newv & 0xffff8000) != 0xffff8000) {
			SET_VFLG (1);
			SET_NFLG (1);
		} else {
			if (((uae_s16)rem < 0) != ((uae_s32)dst < 0)) rem = -rem;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_NFLG (((uae_s16)(newv)) < 0);
			newv = (newv & 0xffff) | ((uae_u32)rem << 16);
			m68k_dreg (regs, dstreg) = (newv);
		}
	}
	m68k_incpci (2);
}}}}l_241279: ;
return;
}

/* DIVS.W (An)+,Dn */
void REGPARAM2 CPUFUNC(op_81d8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 61;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	if (src == 0) {
		divbyzero_special (1, dst);
	m68k_incpci (2);
		Exception (5);
		goto l_241280;
	}
	CLEAR_CZNV ();
	if (dst == 0x80000000 && src == -1) {
		SET_VFLG (1);
		SET_NFLG (1);
	} else {
		uae_s32 newv = (uae_s32)dst / (uae_s32)(uae_s16)src;
		uae_u16 rem = (uae_s32)dst % (uae_s32)(uae_s16)src;
		if ((newv & 0xffff8000) != 0 && (newv & 0xffff8000) != 0xffff8000) {
			SET_VFLG (1);
			SET_NFLG (1);
		} else {
			if (((uae_s16)rem < 0) != ((uae_s32)dst < 0)) rem = -rem;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_NFLG (((uae_s16)(newv)) < 0);
			newv = (newv & 0xffff) | ((uae_u32)rem << 16);
			m68k_dreg (regs, dstreg) = (newv);
		}
	}
	m68k_incpci (2);
}}}}l_241280: ;
return;
}

/* DIVS.W -(An),Dn */
void REGPARAM2 CPUFUNC(op_81e0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 61;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	if (src == 0) {
		divbyzero_special (1, dst);
	m68k_incpci (2);
		Exception (5);
		goto l_241281;
	}
	CLEAR_CZNV ();
	if (dst == 0x80000000 && src == -1) {
		SET_VFLG (1);
		SET_NFLG (1);
	} else {
		uae_s32 newv = (uae_s32)dst / (uae_s32)(uae_s16)src;
		uae_u16 rem = (uae_s32)dst % (uae_s32)(uae_s16)src;
		if ((newv & 0xffff8000) != 0 && (newv & 0xffff8000) != 0xffff8000) {
			SET_VFLG (1);
			SET_NFLG (1);
		} else {
			if (((uae_s16)rem < 0) != ((uae_s32)dst < 0)) rem = -rem;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_NFLG (((uae_s16)(newv)) < 0);
			newv = (newv & 0xffff) | ((uae_u32)rem << 16);
			m68k_dreg (regs, dstreg) = (newv);
		}
	}
	m68k_incpci (2);
}}}}l_241281: ;
return;
}

/* DIVS.W (d16,An),Dn */
void REGPARAM2 CPUFUNC(op_81e8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 61;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	if (src == 0) {
		divbyzero_special (1, dst);
	m68k_incpci (4);
		Exception (5);
		goto l_241282;
	}
	CLEAR_CZNV ();
	if (dst == 0x80000000 && src == -1) {
		SET_VFLG (1);
		SET_NFLG (1);
	} else {
		uae_s32 newv = (uae_s32)dst / (uae_s32)(uae_s16)src;
		uae_u16 rem = (uae_s32)dst % (uae_s32)(uae_s16)src;
		if ((newv & 0xffff8000) != 0 && (newv & 0xffff8000) != 0xffff8000) {
			SET_VFLG (1);
			SET_NFLG (1);
		} else {
			if (((uae_s16)rem < 0) != ((uae_s32)dst < 0)) rem = -rem;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_NFLG (((uae_s16)(newv)) < 0);
			newv = (newv & 0xffff) | ((uae_u32)rem << 16);
			m68k_dreg (regs, dstreg) = (newv);
		}
	}
	m68k_incpci (4);
}}}}l_241282: ;
return;
}

/* DIVS.W (d8,An,Xn),Dn */
void REGPARAM2 CPUFUNC(op_81f0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 61;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s16 src = x_get_word (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	if (src == 0) {
		divbyzero_special (1, dst);
	m68k_incpci (0);
		Exception (5);
		goto l_241283;
	}
	CLEAR_CZNV ();
	if (dst == 0x80000000 && src == -1) {
		SET_VFLG (1);
		SET_NFLG (1);
	} else {
		uae_s32 newv = (uae_s32)dst / (uae_s32)(uae_s16)src;
		uae_u16 rem = (uae_s32)dst % (uae_s32)(uae_s16)src;
		if ((newv & 0xffff8000) != 0 && (newv & 0xffff8000) != 0xffff8000) {
			SET_VFLG (1);
			SET_NFLG (1);
		} else {
			if (((uae_s16)rem < 0) != ((uae_s32)dst < 0)) rem = -rem;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_NFLG (((uae_s16)(newv)) < 0);
			newv = (newv & 0xffff) | ((uae_u32)rem << 16);
			m68k_dreg (regs, dstreg) = (newv);
		}
	}
}}}}}l_241283: ;
return;
}

/* DIVS.W (xxx).W,Dn */
void REGPARAM2 CPUFUNC(op_81f8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 61;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	if (src == 0) {
		divbyzero_special (1, dst);
	m68k_incpci (4);
		Exception (5);
		goto l_241284;
	}
	CLEAR_CZNV ();
	if (dst == 0x80000000 && src == -1) {
		SET_VFLG (1);
		SET_NFLG (1);
	} else {
		uae_s32 newv = (uae_s32)dst / (uae_s32)(uae_s16)src;
		uae_u16 rem = (uae_s32)dst % (uae_s32)(uae_s16)src;
		if ((newv & 0xffff8000) != 0 && (newv & 0xffff8000) != 0xffff8000) {
			SET_VFLG (1);
			SET_NFLG (1);
		} else {
			if (((uae_s16)rem < 0) != ((uae_s32)dst < 0)) rem = -rem;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_NFLG (((uae_s16)(newv)) < 0);
			newv = (newv & 0xffff) | ((uae_u32)rem << 16);
			m68k_dreg (regs, dstreg) = (newv);
		}
	}
	m68k_incpci (4);
}}}}l_241284: ;
return;
}

/* DIVS.W (xxx).L,Dn */
void REGPARAM2 CPUFUNC(op_81f9_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 61;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	if (src == 0) {
		divbyzero_special (1, dst);
	m68k_incpci (6);
		Exception (5);
		goto l_241285;
	}
	CLEAR_CZNV ();
	if (dst == 0x80000000 && src == -1) {
		SET_VFLG (1);
		SET_NFLG (1);
	} else {
		uae_s32 newv = (uae_s32)dst / (uae_s32)(uae_s16)src;
		uae_u16 rem = (uae_s32)dst % (uae_s32)(uae_s16)src;
		if ((newv & 0xffff8000) != 0 && (newv & 0xffff8000) != 0xffff8000) {
			SET_VFLG (1);
			SET_NFLG (1);
		} else {
			if (((uae_s16)rem < 0) != ((uae_s32)dst < 0)) rem = -rem;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_NFLG (((uae_s16)(newv)) < 0);
			newv = (newv & 0xffff) | ((uae_u32)rem << 16);
			m68k_dreg (regs, dstreg) = (newv);
		}
	}
	m68k_incpci (6);
}}}}l_241285: ;
return;
}

/* DIVS.W (d16,PC),Dn */
void REGPARAM2 CPUFUNC(op_81fa_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 61;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	if (src == 0) {
		divbyzero_special (1, dst);
	m68k_incpci (4);
		Exception (5);
		goto l_241286;
	}
	CLEAR_CZNV ();
	if (dst == 0x80000000 && src == -1) {
		SET_VFLG (1);
		SET_NFLG (1);
	} else {
		uae_s32 newv = (uae_s32)dst / (uae_s32)(uae_s16)src;
		uae_u16 rem = (uae_s32)dst % (uae_s32)(uae_s16)src;
		if ((newv & 0xffff8000) != 0 && (newv & 0xffff8000) != 0xffff8000) {
			SET_VFLG (1);
			SET_NFLG (1);
		} else {
			if (((uae_s16)rem < 0) != ((uae_s32)dst < 0)) rem = -rem;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_NFLG (((uae_s16)(newv)) < 0);
			newv = (newv & 0xffff) | ((uae_u32)rem << 16);
			m68k_dreg (regs, dstreg) = (newv);
		}
	}
	m68k_incpci (4);
}}}}l_241286: ;
return;
}

/* DIVS.W (d8,PC,Xn),Dn */
void REGPARAM2 CPUFUNC(op_81fb_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 61;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s16 src = x_get_word (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	if (src == 0) {
		divbyzero_special (1, dst);
	m68k_incpci (0);
		Exception (5);
		goto l_241287;
	}
	CLEAR_CZNV ();
	if (dst == 0x80000000 && src == -1) {
		SET_VFLG (1);
		SET_NFLG (1);
	} else {
		uae_s32 newv = (uae_s32)dst / (uae_s32)(uae_s16)src;
		uae_u16 rem = (uae_s32)dst % (uae_s32)(uae_s16)src;
		if ((newv & 0xffff8000) != 0 && (newv & 0xffff8000) != 0xffff8000) {
			SET_VFLG (1);
			SET_NFLG (1);
		} else {
			if (((uae_s16)rem < 0) != ((uae_s32)dst < 0)) rem = -rem;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_NFLG (((uae_s16)(newv)) < 0);
			newv = (newv & 0xffff) | ((uae_u32)rem << 16);
			m68k_dreg (regs, dstreg) = (newv);
		}
	}
}}}}}l_241287: ;
return;
}

/* DIVS.W #<data>.W,Dn */
void REGPARAM2 CPUFUNC(op_81fc_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 61;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	if (src == 0) {
		divbyzero_special (1, dst);
	m68k_incpci (4);
		Exception (5);
		goto l_241288;
	}
	CLEAR_CZNV ();
	if (dst == 0x80000000 && src == -1) {
		SET_VFLG (1);
		SET_NFLG (1);
	} else {
		uae_s32 newv = (uae_s32)dst / (uae_s32)(uae_s16)src;
		uae_u16 rem = (uae_s32)dst % (uae_s32)(uae_s16)src;
		if ((newv & 0xffff8000) != 0 && (newv & 0xffff8000) != 0xffff8000) {
			SET_VFLG (1);
			SET_NFLG (1);
		} else {
			if (((uae_s16)rem < 0) != ((uae_s32)dst < 0)) rem = -rem;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_NFLG (((uae_s16)(newv)) < 0);
			newv = (newv & 0xffff) | ((uae_u32)rem << 16);
			m68k_dreg (regs, dstreg) = (newv);
		}
	}
	m68k_incpci (4);
}}}l_241288: ;
return;
}

/* SUB.B Dn,Dn */
void REGPARAM2 CPUFUNC(op_9000_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}}	m68k_incpci (2);
return;
}

/* SUB.B (An),Dn */
void REGPARAM2 CPUFUNC(op_9010_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s8 src = x_get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}}}	m68k_incpci (2);
return;
}

/* SUB.B (An)+,Dn */
void REGPARAM2 CPUFUNC(op_9018_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s8 src = x_get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{	uae_s8 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}}}	m68k_incpci (2);
return;
}

/* SUB.B -(An),Dn */
void REGPARAM2 CPUFUNC(op_9020_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = x_get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s8 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}}}	m68k_incpci (2);
return;
}

/* SUB.B (d16,An),Dn */
void REGPARAM2 CPUFUNC(op_9028_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}}}	m68k_incpci (4);
return;
}

/* SUB.B (d8,An,Xn),Dn */
void REGPARAM2 CPUFUNC(op_9030_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 7;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s8 src = x_get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}}}}return;
}

/* SUB.B (xxx).W,Dn */
void REGPARAM2 CPUFUNC(op_9038_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 7;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}}}	m68k_incpci (4);
return;
}

/* SUB.B (xxx).L,Dn */
void REGPARAM2 CPUFUNC(op_9039_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 7;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}}}	m68k_incpci (6);
return;
}

/* SUB.B (d16,PC),Dn */
void REGPARAM2 CPUFUNC(op_903a_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 7;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}}}	m68k_incpci (4);
return;
}

/* SUB.B (d8,PC,Xn),Dn */
void REGPARAM2 CPUFUNC(op_903b_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 7;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s8 src = x_get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}}}}return;
}

/* SUB.B #<data>.B,Dn */
void REGPARAM2 CPUFUNC(op_903c_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 7;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}}	m68k_incpci (4);
return;
}

/* SUB.W Dn,Dn */
void REGPARAM2 CPUFUNC(op_9040_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}}	m68k_incpci (2);
return;
}

/* SUB.W An,Dn */
void REGPARAM2 CPUFUNC(op_9048_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 7;
{{	uae_s16 src = m68k_areg (regs, srcreg);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}}	m68k_incpci (2);
return;
}

/* SUB.W (An),Dn */
void REGPARAM2 CPUFUNC(op_9050_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}}}	m68k_incpci (2);
return;
}

/* SUB.W (An)+,Dn */
void REGPARAM2 CPUFUNC(op_9058_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}}}	m68k_incpci (2);
return;
}

/* SUB.W -(An),Dn */
void REGPARAM2 CPUFUNC(op_9060_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}}}	m68k_incpci (2);
return;
}

/* SUB.W (d16,An),Dn */
void REGPARAM2 CPUFUNC(op_9068_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}}}	m68k_incpci (4);
return;
}

/* SUB.W (d8,An,Xn),Dn */
void REGPARAM2 CPUFUNC(op_9070_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 7;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}}}}return;
}

/* SUB.W (xxx).W,Dn */
void REGPARAM2 CPUFUNC(op_9078_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 7;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}}}	m68k_incpci (4);
return;
}

/* SUB.W (xxx).L,Dn */
void REGPARAM2 CPUFUNC(op_9079_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 7;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}}}	m68k_incpci (6);
return;
}

/* SUB.W (d16,PC),Dn */
void REGPARAM2 CPUFUNC(op_907a_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 7;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}}}	m68k_incpci (4);
return;
}

/* SUB.W (d8,PC,Xn),Dn */
void REGPARAM2 CPUFUNC(op_907b_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 7;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}}}}return;
}

/* SUB.W #<data>.W,Dn */
void REGPARAM2 CPUFUNC(op_907c_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 7;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}}	m68k_incpci (4);
return;
}

/* SUB.L Dn,Dn */
void REGPARAM2 CPUFUNC(op_9080_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}	m68k_incpci (2);
return;
}

/* SUB.L An,Dn */
void REGPARAM2 CPUFUNC(op_9088_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 7;
{{	uae_s32 src = m68k_areg (regs, srcreg);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}	m68k_incpci (2);
return;
}

/* SUB.L (An),Dn */
void REGPARAM2 CPUFUNC(op_9090_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}}	m68k_incpci (2);
return;
}

/* SUB.L (An)+,Dn */
void REGPARAM2 CPUFUNC(op_9098_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, srcreg) += 4;
{	uae_s32 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}}	m68k_incpci (2);
return;
}

/* SUB.L -(An),Dn */
void REGPARAM2 CPUFUNC(op_90a0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s32 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}}	m68k_incpci (2);
return;
}

/* SUB.L (d16,An),Dn */
void REGPARAM2 CPUFUNC(op_90a8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}}	m68k_incpci (4);
return;
}

/* SUB.L (d8,An,Xn),Dn */
void REGPARAM2 CPUFUNC(op_90b0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 7;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}}}return;
}

/* SUB.L (xxx).W,Dn */
void REGPARAM2 CPUFUNC(op_90b8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 7;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}}	m68k_incpci (4);
return;
}

/* SUB.L (xxx).L,Dn */
void REGPARAM2 CPUFUNC(op_90b9_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 7;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}}	m68k_incpci (6);
return;
}

/* SUB.L (d16,PC),Dn */
void REGPARAM2 CPUFUNC(op_90ba_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 7;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}}	m68k_incpci (4);
return;
}

/* SUB.L (d8,PC,Xn),Dn */
void REGPARAM2 CPUFUNC(op_90bb_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 7;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}}}return;
}

/* SUB.L #<data>.L,Dn */
void REGPARAM2 CPUFUNC(op_90bc_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 7;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}	m68k_incpci (6);
return;
}

/* SUBA.W Dn,An */
void REGPARAM2 CPUFUNC(op_90c0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 8;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}	m68k_incpci (2);
return;
}

/* SUBA.W An,An */
void REGPARAM2 CPUFUNC(op_90c8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 8;
{{	uae_s16 src = m68k_areg (regs, srcreg);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}	m68k_incpci (2);
return;
}

/* SUBA.W (An),An */
void REGPARAM2 CPUFUNC(op_90d0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 8;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}	m68k_incpci (2);
return;
}

/* SUBA.W (An)+,An */
void REGPARAM2 CPUFUNC(op_90d8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 8;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}	m68k_incpci (2);
return;
}

/* SUBA.W -(An),An */
void REGPARAM2 CPUFUNC(op_90e0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 8;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}	m68k_incpci (2);
return;
}

/* SUBA.W (d16,An),An */
void REGPARAM2 CPUFUNC(op_90e8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 8;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}	m68k_incpci (4);
return;
}

/* SUBA.W (d8,An,Xn),An */
void REGPARAM2 CPUFUNC(op_90f0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 8;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s16 src = x_get_word (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}}return;
}

/* SUBA.W (xxx).W,An */
void REGPARAM2 CPUFUNC(op_90f8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 8;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}	m68k_incpci (4);
return;
}

/* SUBA.W (xxx).L,An */
void REGPARAM2 CPUFUNC(op_90f9_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 8;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}	m68k_incpci (6);
return;
}

/* SUBA.W (d16,PC),An */
void REGPARAM2 CPUFUNC(op_90fa_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 8;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}	m68k_incpci (4);
return;
}

/* SUBA.W (d8,PC,Xn),An */
void REGPARAM2 CPUFUNC(op_90fb_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 8;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s16 src = x_get_word (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}}return;
}

/* SUBA.W #<data>.W,An */
void REGPARAM2 CPUFUNC(op_90fc_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 8;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}	m68k_incpci (4);
return;
}

/* SUBX.B Dn,Dn */
void REGPARAM2 CPUFUNC(op_9100_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 9;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
{	uae_u32 newv = dst - src - (GET_XFLG () ? 1 : 0);
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s8)(newv)) == 0));
	SET_NFLG (((uae_s8)(newv)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}	m68k_incpci (2);
return;
}

/* SUBX.B -(An),-(An) */
void REGPARAM2 CPUFUNC(op_9108_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 9;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = x_get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
{	uae_u32 newv = dst - src - (GET_XFLG () ? 1 : 0);
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s8)(newv)) == 0));
	SET_NFLG (((uae_s8)(newv)) < 0);
	x_put_byte (dsta, newv);
}}}}}}}	m68k_incpci (2);
return;
}

/* SUB.B Dn,(An) */
void REGPARAM2 CPUFUNC(op_9110_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = x_get_byte (dsta);
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (dsta, newv);
}}}}}}}	m68k_incpci (2);
return;
}

/* SUB.B Dn,(An)+ */
void REGPARAM2 CPUFUNC(op_9118_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (dsta, newv);
}}}}}}}	m68k_incpci (2);
return;
}

/* SUB.B Dn,-(An) */
void REGPARAM2 CPUFUNC(op_9120_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (dsta, newv);
}}}}}}}	m68k_incpci (2);
return;
}

/* SUB.B Dn,(d16,An) */
void REGPARAM2 CPUFUNC(op_9128_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 dst = x_get_byte (dsta);
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (dsta, newv);
}}}}}}}	m68k_incpci (4);
return;
}

/* SUB.B Dn,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_9130_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	m68k_incpci (2);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s8 dst = x_get_byte (dsta);
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (dsta, newv);
}}}}}}}}return;
}

/* SUB.B Dn,(xxx).W */
void REGPARAM2 CPUFUNC(op_9138_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	OpcodeFamily = 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 dst = x_get_byte (dsta);
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (dsta, newv);
}}}}}}}	m68k_incpci (4);
return;
}

/* SUB.B Dn,(xxx).L */
void REGPARAM2 CPUFUNC(op_9139_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	OpcodeFamily = 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (2);
{	uae_s8 dst = x_get_byte (dsta);
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (dsta, newv);
}}}}}}}	m68k_incpci (6);
return;
}

/* SUBX.W Dn,Dn */
void REGPARAM2 CPUFUNC(op_9140_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 9;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{	uae_u32 newv = dst - src - (GET_XFLG () ? 1 : 0);
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s16)(newv)) == 0));
	SET_NFLG (((uae_s16)(newv)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}	m68k_incpci (2);
return;
}

/* SUBX.W -(An),-(An) */
void REGPARAM2 CPUFUNC(op_9148_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 9;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
{	uae_s16 dst = x_get_word (dsta);
	m68k_areg (regs, dstreg) = dsta;
{	uae_u32 newv = dst - src - (GET_XFLG () ? 1 : 0);
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s16)(newv)) == 0));
	SET_NFLG (((uae_s16)(newv)) < 0);
	x_put_word (dsta, newv);
}}}}}}}	m68k_incpci (2);
return;
}

/* SUB.W Dn,(An) */
void REGPARAM2 CPUFUNC(op_9150_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s16 dst = x_get_word (dsta);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (dsta, newv);
}}}}}}}	m68k_incpci (2);
return;
}

/* SUB.W Dn,(An)+ */
void REGPARAM2 CPUFUNC(op_9158_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s16 dst = x_get_word (dsta);
	m68k_areg (regs, dstreg) += 2;
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (dsta, newv);
}}}}}}}	m68k_incpci (2);
return;
}

/* SUB.W Dn,-(An) */
void REGPARAM2 CPUFUNC(op_9160_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
{	uae_s16 dst = x_get_word (dsta);
	m68k_areg (regs, dstreg) = dsta;
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (dsta, newv);
}}}}}}}	m68k_incpci (2);
return;
}

/* SUB.W Dn,(d16,An) */
void REGPARAM2 CPUFUNC(op_9168_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 dst = x_get_word (dsta);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (dsta, newv);
}}}}}}}	m68k_incpci (4);
return;
}

/* SUB.W Dn,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_9170_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	m68k_incpci (2);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s16 dst = x_get_word (dsta);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (dsta, newv);
}}}}}}}}return;
}

/* SUB.W Dn,(xxx).W */
void REGPARAM2 CPUFUNC(op_9178_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	OpcodeFamily = 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 dst = x_get_word (dsta);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (dsta, newv);
}}}}}}}	m68k_incpci (4);
return;
}

/* SUB.W Dn,(xxx).L */
void REGPARAM2 CPUFUNC(op_9179_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	OpcodeFamily = 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (2);
{	uae_s16 dst = x_get_word (dsta);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (dsta, newv);
}}}}}}}	m68k_incpci (6);
return;
}

/* SUBX.L Dn,Dn */
void REGPARAM2 CPUFUNC(op_9180_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 9;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
{	uae_u32 newv = dst - src - (GET_XFLG () ? 1 : 0);
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s32)(newv)) == 0));
	SET_NFLG (((uae_s32)(newv)) < 0);
	m68k_dreg (regs, dstreg) = (newv);
}}}}}	m68k_incpci (2);
return;
}

/* SUBX.L -(An),-(An) */
void REGPARAM2 CPUFUNC(op_9188_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 9;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
{	uae_s32 dst = x_get_long (dsta);
	m68k_areg (regs, dstreg) = dsta;
{	uae_u32 newv = dst - src - (GET_XFLG () ? 1 : 0);
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s32)(newv)) == 0));
	SET_NFLG (((uae_s32)(newv)) < 0);
	x_put_long (dsta, newv);
}}}}}}}	m68k_incpci (2);
return;
}

/* SUB.L Dn,(An) */
void REGPARAM2 CPUFUNC(op_9190_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s32 dst = x_get_long (dsta);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (dsta, newv);
}}}}}}}	m68k_incpci (2);
return;
}

/* SUB.L Dn,(An)+ */
void REGPARAM2 CPUFUNC(op_9198_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s32 dst = x_get_long (dsta);
	m68k_areg (regs, dstreg) += 4;
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (dsta, newv);
}}}}}}}	m68k_incpci (2);
return;
}

/* SUB.L Dn,-(An) */
void REGPARAM2 CPUFUNC(op_91a0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
{	uae_s32 dst = x_get_long (dsta);
	m68k_areg (regs, dstreg) = dsta;
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (dsta, newv);
}}}}}}}	m68k_incpci (2);
return;
}

/* SUB.L Dn,(d16,An) */
void REGPARAM2 CPUFUNC(op_91a8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 dst = x_get_long (dsta);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (dsta, newv);
}}}}}}}	m68k_incpci (4);
return;
}

/* SUB.L Dn,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_91b0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	m68k_incpci (2);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s32 dst = x_get_long (dsta);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (dsta, newv);
}}}}}}}}return;
}

/* SUB.L Dn,(xxx).W */
void REGPARAM2 CPUFUNC(op_91b8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	OpcodeFamily = 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 dst = x_get_long (dsta);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (dsta, newv);
}}}}}}}	m68k_incpci (4);
return;
}

/* SUB.L Dn,(xxx).L */
void REGPARAM2 CPUFUNC(op_91b9_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	OpcodeFamily = 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (2);
{	uae_s32 dst = x_get_long (dsta);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (dsta, newv);
}}}}}}}	m68k_incpci (6);
return;
}

/* SUBA.L Dn,An */
void REGPARAM2 CPUFUNC(op_91c0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 8;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}	m68k_incpci (2);
return;
}

/* SUBA.L An,An */
void REGPARAM2 CPUFUNC(op_91c8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 8;
{{	uae_s32 src = m68k_areg (regs, srcreg);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}	m68k_incpci (2);
return;
}

/* SUBA.L (An),An */
void REGPARAM2 CPUFUNC(op_91d0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 8;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}	m68k_incpci (2);
return;
}

/* SUBA.L (An)+,An */
void REGPARAM2 CPUFUNC(op_91d8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 8;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, srcreg) += 4;
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}	m68k_incpci (2);
return;
}

/* SUBA.L -(An),An */
void REGPARAM2 CPUFUNC(op_91e0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 8;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}	m68k_incpci (2);
return;
}

/* SUBA.L (d16,An),An */
void REGPARAM2 CPUFUNC(op_91e8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 8;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}	m68k_incpci (4);
return;
}

/* SUBA.L (d8,An,Xn),An */
void REGPARAM2 CPUFUNC(op_91f0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 8;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}}return;
}

/* SUBA.L (xxx).W,An */
void REGPARAM2 CPUFUNC(op_91f8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 8;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}	m68k_incpci (4);
return;
}

/* SUBA.L (xxx).L,An */
void REGPARAM2 CPUFUNC(op_91f9_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 8;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}	m68k_incpci (6);
return;
}

/* SUBA.L (d16,PC),An */
void REGPARAM2 CPUFUNC(op_91fa_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 8;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}	m68k_incpci (4);
return;
}

/* SUBA.L (d8,PC,Xn),An */
void REGPARAM2 CPUFUNC(op_91fb_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 8;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}}return;
}

/* SUBA.L #<data>.L,An */
void REGPARAM2 CPUFUNC(op_91fc_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 8;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}	m68k_incpci (6);
return;
}

/* CMP.B Dn,Dn */
void REGPARAM2 CPUFUNC(op_b000_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 25;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}	m68k_incpci (2);
return;
}

/* CMP.B (An),Dn */
void REGPARAM2 CPUFUNC(op_b010_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 25;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s8 src = x_get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (2);
return;
}

/* CMP.B (An)+,Dn */
void REGPARAM2 CPUFUNC(op_b018_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 25;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s8 src = x_get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{	uae_s8 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (2);
return;
}

/* CMP.B -(An),Dn */
void REGPARAM2 CPUFUNC(op_b020_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 25;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = x_get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s8 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (2);
return;
}

/* CMP.B (d16,An),Dn */
void REGPARAM2 CPUFUNC(op_b028_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 25;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (4);
return;
}

/* CMP.B (d8,An,Xn),Dn */
void REGPARAM2 CPUFUNC(op_b030_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 25;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s8 src = x_get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}}return;
}

/* CMP.B (xxx).W,Dn */
void REGPARAM2 CPUFUNC(op_b038_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 25;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (4);
return;
}

/* CMP.B (xxx).L,Dn */
void REGPARAM2 CPUFUNC(op_b039_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 25;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (6);
return;
}

/* CMP.B (d16,PC),Dn */
void REGPARAM2 CPUFUNC(op_b03a_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 25;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (4);
return;
}

/* CMP.B (d8,PC,Xn),Dn */
void REGPARAM2 CPUFUNC(op_b03b_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 25;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s8 src = x_get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}}return;
}

/* CMP.B #<data>.B,Dn */
void REGPARAM2 CPUFUNC(op_b03c_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 25;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}	m68k_incpci (4);
return;
}

/* CMP.W Dn,Dn */
void REGPARAM2 CPUFUNC(op_b040_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 25;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}	m68k_incpci (2);
return;
}

/* CMP.W An,Dn */
void REGPARAM2 CPUFUNC(op_b048_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 25;
{{	uae_s16 src = m68k_areg (regs, srcreg);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}	m68k_incpci (2);
return;
}

/* CMP.W (An),Dn */
void REGPARAM2 CPUFUNC(op_b050_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 25;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (2);
return;
}

/* CMP.W (An)+,Dn */
void REGPARAM2 CPUFUNC(op_b058_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 25;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (2);
return;
}

/* CMP.W -(An),Dn */
void REGPARAM2 CPUFUNC(op_b060_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 25;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (2);
return;
}

/* CMP.W (d16,An),Dn */
void REGPARAM2 CPUFUNC(op_b068_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 25;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (4);
return;
}

/* CMP.W (d8,An,Xn),Dn */
void REGPARAM2 CPUFUNC(op_b070_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 25;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}}return;
}

/* CMP.W (xxx).W,Dn */
void REGPARAM2 CPUFUNC(op_b078_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 25;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (4);
return;
}

/* CMP.W (xxx).L,Dn */
void REGPARAM2 CPUFUNC(op_b079_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 25;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (6);
return;
}

/* CMP.W (d16,PC),Dn */
void REGPARAM2 CPUFUNC(op_b07a_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 25;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (4);
return;
}

/* CMP.W (d8,PC,Xn),Dn */
void REGPARAM2 CPUFUNC(op_b07b_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 25;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}}return;
}

/* CMP.W #<data>.W,Dn */
void REGPARAM2 CPUFUNC(op_b07c_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 25;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}	m68k_incpci (4);
return;
}

/* CMP.L Dn,Dn */
void REGPARAM2 CPUFUNC(op_b080_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 25;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}	m68k_incpci (2);
return;
}

/* CMP.L An,Dn */
void REGPARAM2 CPUFUNC(op_b088_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 25;
{{	uae_s32 src = m68k_areg (regs, srcreg);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}	m68k_incpci (2);
return;
}

/* CMP.L (An),Dn */
void REGPARAM2 CPUFUNC(op_b090_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 25;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (2);
return;
}

/* CMP.L (An)+,Dn */
void REGPARAM2 CPUFUNC(op_b098_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 25;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, srcreg) += 4;
{	uae_s32 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (2);
return;
}

/* CMP.L -(An),Dn */
void REGPARAM2 CPUFUNC(op_b0a0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 25;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s32 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (2);
return;
}

#endif

#ifdef PART_7
/* CMP.L (d16,An),Dn */
void REGPARAM2 CPUFUNC(op_b0a8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 25;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (4);
return;
}

/* CMP.L (d8,An,Xn),Dn */
void REGPARAM2 CPUFUNC(op_b0b0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 25;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}}return;
}

/* CMP.L (xxx).W,Dn */
void REGPARAM2 CPUFUNC(op_b0b8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 25;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (4);
return;
}

/* CMP.L (xxx).L,Dn */
void REGPARAM2 CPUFUNC(op_b0b9_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 25;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (6);
return;
}

/* CMP.L (d16,PC),Dn */
void REGPARAM2 CPUFUNC(op_b0ba_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 25;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (4);
return;
}

/* CMP.L (d8,PC,Xn),Dn */
void REGPARAM2 CPUFUNC(op_b0bb_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 25;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}}return;
}

/* CMP.L #<data>.L,Dn */
void REGPARAM2 CPUFUNC(op_b0bc_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 25;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}	m68k_incpci (6);
return;
}

/* CMPA.W Dn,An */
void REGPARAM2 CPUFUNC(op_b0c0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 27;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}	m68k_incpci (2);
return;
}

/* CMPA.W An,An */
void REGPARAM2 CPUFUNC(op_b0c8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 27;
{{	uae_s16 src = m68k_areg (regs, srcreg);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}	m68k_incpci (2);
return;
}

/* CMPA.W (An),An */
void REGPARAM2 CPUFUNC(op_b0d0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 27;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (2);
return;
}

/* CMPA.W (An)+,An */
void REGPARAM2 CPUFUNC(op_b0d8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 27;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	uae_s32 dst = m68k_areg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (2);
return;
}

/* CMPA.W -(An),An */
void REGPARAM2 CPUFUNC(op_b0e0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 27;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s32 dst = m68k_areg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (2);
return;
}

/* CMPA.W (d16,An),An */
void REGPARAM2 CPUFUNC(op_b0e8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 27;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (4);
return;
}

/* CMPA.W (d8,An,Xn),An */
void REGPARAM2 CPUFUNC(op_b0f0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 27;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s16 src = x_get_word (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}}return;
}

/* CMPA.W (xxx).W,An */
void REGPARAM2 CPUFUNC(op_b0f8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 27;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (4);
return;
}

/* CMPA.W (xxx).L,An */
void REGPARAM2 CPUFUNC(op_b0f9_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 27;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (6);
return;
}

/* CMPA.W (d16,PC),An */
void REGPARAM2 CPUFUNC(op_b0fa_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 27;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (4);
return;
}

/* CMPA.W (d8,PC,Xn),An */
void REGPARAM2 CPUFUNC(op_b0fb_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 27;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s16 src = x_get_word (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}}return;
}

/* CMPA.W #<data>.W,An */
void REGPARAM2 CPUFUNC(op_b0fc_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 27;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}	m68k_incpci (4);
return;
}

/* EOR.B Dn,Dn */
void REGPARAM2 CPUFUNC(op_b100_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 3;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}	m68k_incpci (2);
return;
}

/* CMPM.B (An)+,(An)+ */
void REGPARAM2 CPUFUNC(op_b108_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 26;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s8 src = x_get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
{{uae_u32 newv = ((uae_u8)(dst)) - ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u8)(src)) > ((uae_u8)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}}	m68k_incpci (2);
return;
}

/* EOR.B Dn,(An) */
void REGPARAM2 CPUFUNC(op_b110_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 3;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = x_get_byte (dsta);
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}	m68k_incpci (2);
return;
}

/* EOR.B Dn,(An)+ */
void REGPARAM2 CPUFUNC(op_b118_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 3;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}	m68k_incpci (2);
return;
}

/* EOR.B Dn,-(An) */
void REGPARAM2 CPUFUNC(op_b120_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 3;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}	m68k_incpci (2);
return;
}

/* EOR.B Dn,(d16,An) */
void REGPARAM2 CPUFUNC(op_b128_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 3;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 dst = x_get_byte (dsta);
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}	m68k_incpci (4);
return;
}

/* EOR.B Dn,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_b130_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 3;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	m68k_incpci (2);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s8 dst = x_get_byte (dsta);
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}}return;
}

/* EOR.B Dn,(xxx).W */
void REGPARAM2 CPUFUNC(op_b138_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	OpcodeFamily = 3;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 dst = x_get_byte (dsta);
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}	m68k_incpci (4);
return;
}

/* EOR.B Dn,(xxx).L */
void REGPARAM2 CPUFUNC(op_b139_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	OpcodeFamily = 3;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (2);
{	uae_s8 dst = x_get_byte (dsta);
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}	m68k_incpci (6);
return;
}

/* EOR.W Dn,Dn */
void REGPARAM2 CPUFUNC(op_b140_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 3;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}	m68k_incpci (2);
return;
}

/* CMPM.W (An)+,(An)+ */
void REGPARAM2 CPUFUNC(op_b148_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 26;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s16 dst = x_get_word (dsta);
	m68k_areg (regs, dstreg) += 2;
{{uae_u32 newv = ((uae_u16)(dst)) - ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u16)(src)) > ((uae_u16)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}}	m68k_incpci (2);
return;
}

/* EOR.W Dn,(An) */
void REGPARAM2 CPUFUNC(op_b150_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 3;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s16 dst = x_get_word (dsta);
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}	m68k_incpci (2);
return;
}

/* EOR.W Dn,(An)+ */
void REGPARAM2 CPUFUNC(op_b158_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 3;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s16 dst = x_get_word (dsta);
	m68k_areg (regs, dstreg) += 2;
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}	m68k_incpci (2);
return;
}

/* EOR.W Dn,-(An) */
void REGPARAM2 CPUFUNC(op_b160_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 3;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
{	uae_s16 dst = x_get_word (dsta);
	m68k_areg (regs, dstreg) = dsta;
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}	m68k_incpci (2);
return;
}

/* EOR.W Dn,(d16,An) */
void REGPARAM2 CPUFUNC(op_b168_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 3;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 dst = x_get_word (dsta);
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}	m68k_incpci (4);
return;
}

/* EOR.W Dn,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_b170_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 3;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	m68k_incpci (2);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s16 dst = x_get_word (dsta);
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}}return;
}

/* EOR.W Dn,(xxx).W */
void REGPARAM2 CPUFUNC(op_b178_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	OpcodeFamily = 3;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 dst = x_get_word (dsta);
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}	m68k_incpci (4);
return;
}

/* EOR.W Dn,(xxx).L */
void REGPARAM2 CPUFUNC(op_b179_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	OpcodeFamily = 3;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (2);
{	uae_s16 dst = x_get_word (dsta);
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}	m68k_incpci (6);
return;
}

/* EOR.L Dn,Dn */
void REGPARAM2 CPUFUNC(op_b180_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 3;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	m68k_dreg (regs, dstreg) = (src);
}}}	m68k_incpci (2);
return;
}

/* CMPM.L (An)+,(An)+ */
void REGPARAM2 CPUFUNC(op_b188_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 26;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, srcreg) += 4;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s32 dst = x_get_long (dsta);
	m68k_areg (regs, dstreg) += 4;
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}}	m68k_incpci (2);
return;
}

/* EOR.L Dn,(An) */
void REGPARAM2 CPUFUNC(op_b190_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 3;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s32 dst = x_get_long (dsta);
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}	m68k_incpci (2);
return;
}

/* EOR.L Dn,(An)+ */
void REGPARAM2 CPUFUNC(op_b198_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 3;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s32 dst = x_get_long (dsta);
	m68k_areg (regs, dstreg) += 4;
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}	m68k_incpci (2);
return;
}

/* EOR.L Dn,-(An) */
void REGPARAM2 CPUFUNC(op_b1a0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 3;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
{	uae_s32 dst = x_get_long (dsta);
	m68k_areg (regs, dstreg) = dsta;
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}	m68k_incpci (2);
return;
}

/* EOR.L Dn,(d16,An) */
void REGPARAM2 CPUFUNC(op_b1a8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 3;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 dst = x_get_long (dsta);
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}	m68k_incpci (4);
return;
}

/* EOR.L Dn,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_b1b0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 3;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	m68k_incpci (2);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s32 dst = x_get_long (dsta);
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}}return;
}

/* EOR.L Dn,(xxx).W */
void REGPARAM2 CPUFUNC(op_b1b8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	OpcodeFamily = 3;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 dst = x_get_long (dsta);
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}	m68k_incpci (4);
return;
}

/* EOR.L Dn,(xxx).L */
void REGPARAM2 CPUFUNC(op_b1b9_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	OpcodeFamily = 3;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (2);
{	uae_s32 dst = x_get_long (dsta);
	src ^= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}	m68k_incpci (6);
return;
}

/* CMPA.L Dn,An */
void REGPARAM2 CPUFUNC(op_b1c0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 27;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}	m68k_incpci (2);
return;
}

/* CMPA.L An,An */
void REGPARAM2 CPUFUNC(op_b1c8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 27;
{{	uae_s32 src = m68k_areg (regs, srcreg);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}	m68k_incpci (2);
return;
}

/* CMPA.L (An),An */
void REGPARAM2 CPUFUNC(op_b1d0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 27;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (2);
return;
}

/* CMPA.L (An)+,An */
void REGPARAM2 CPUFUNC(op_b1d8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 27;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, srcreg) += 4;
{	uae_s32 dst = m68k_areg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (2);
return;
}

/* CMPA.L -(An),An */
void REGPARAM2 CPUFUNC(op_b1e0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 27;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s32 dst = m68k_areg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (2);
return;
}

/* CMPA.L (d16,An),An */
void REGPARAM2 CPUFUNC(op_b1e8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 27;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (4);
return;
}

/* CMPA.L (d8,An,Xn),An */
void REGPARAM2 CPUFUNC(op_b1f0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 27;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}}return;
}

/* CMPA.L (xxx).W,An */
void REGPARAM2 CPUFUNC(op_b1f8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 27;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (4);
return;
}

/* CMPA.L (xxx).L,An */
void REGPARAM2 CPUFUNC(op_b1f9_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 27;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (6);
return;
}

/* CMPA.L (d16,PC),An */
void REGPARAM2 CPUFUNC(op_b1fa_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 27;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}	m68k_incpci (4);
return;
}

/* CMPA.L (d8,PC,Xn),An */
void REGPARAM2 CPUFUNC(op_b1fb_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 27;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}}}return;
}

/* CMPA.L #<data>.L,An */
void REGPARAM2 CPUFUNC(op_b1fc_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 27;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) - ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((uae_u32)(src)) > ((uae_u32)(dst)));
	SET_NFLG (flgn != 0);
}}}}}}	m68k_incpci (6);
return;
}

/* AND.B Dn,Dn */
void REGPARAM2 CPUFUNC(op_c000_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 2;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}	m68k_incpci (2);
return;
}

/* AND.B (An),Dn */
void REGPARAM2 CPUFUNC(op_c010_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 2;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s8 src = x_get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}}	m68k_incpci (2);
return;
}

/* AND.B (An)+,Dn */
void REGPARAM2 CPUFUNC(op_c018_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 2;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s8 src = x_get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}}	m68k_incpci (2);
return;
}

/* AND.B -(An),Dn */
void REGPARAM2 CPUFUNC(op_c020_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 2;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = x_get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}}	m68k_incpci (2);
return;
}

/* AND.B (d16,An),Dn */
void REGPARAM2 CPUFUNC(op_c028_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 2;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}}	m68k_incpci (4);
return;
}

/* AND.B (d8,An,Xn),Dn */
void REGPARAM2 CPUFUNC(op_c030_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 2;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s8 src = x_get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}}}return;
}

/* AND.B (xxx).W,Dn */
void REGPARAM2 CPUFUNC(op_c038_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 2;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}}	m68k_incpci (4);
return;
}

/* AND.B (xxx).L,Dn */
void REGPARAM2 CPUFUNC(op_c039_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 2;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}}	m68k_incpci (6);
return;
}

/* AND.B (d16,PC),Dn */
void REGPARAM2 CPUFUNC(op_c03a_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 2;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}}	m68k_incpci (4);
return;
}

/* AND.B (d8,PC,Xn),Dn */
void REGPARAM2 CPUFUNC(op_c03b_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 2;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s8 src = x_get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}}}return;
}

/* AND.B #<data>.B,Dn */
void REGPARAM2 CPUFUNC(op_c03c_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 2;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}	m68k_incpci (4);
return;
}

/* AND.W Dn,Dn */
void REGPARAM2 CPUFUNC(op_c040_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 2;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}	m68k_incpci (2);
return;
}

/* AND.W (An),Dn */
void REGPARAM2 CPUFUNC(op_c050_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 2;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}}	m68k_incpci (2);
return;
}

/* AND.W (An)+,Dn */
void REGPARAM2 CPUFUNC(op_c058_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 2;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}}	m68k_incpci (2);
return;
}

/* AND.W -(An),Dn */
void REGPARAM2 CPUFUNC(op_c060_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 2;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}}	m68k_incpci (2);
return;
}

/* AND.W (d16,An),Dn */
void REGPARAM2 CPUFUNC(op_c068_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 2;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}}	m68k_incpci (4);
return;
}

/* AND.W (d8,An,Xn),Dn */
void REGPARAM2 CPUFUNC(op_c070_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 2;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}}}return;
}

/* AND.W (xxx).W,Dn */
void REGPARAM2 CPUFUNC(op_c078_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 2;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}}	m68k_incpci (4);
return;
}

/* AND.W (xxx).L,Dn */
void REGPARAM2 CPUFUNC(op_c079_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 2;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}}	m68k_incpci (6);
return;
}

/* AND.W (d16,PC),Dn */
void REGPARAM2 CPUFUNC(op_c07a_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 2;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}}	m68k_incpci (4);
return;
}

/* AND.W (d8,PC,Xn),Dn */
void REGPARAM2 CPUFUNC(op_c07b_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 2;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}}}return;
}

/* AND.W #<data>.W,Dn */
void REGPARAM2 CPUFUNC(op_c07c_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 2;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}	m68k_incpci (4);
return;
}

/* AND.L Dn,Dn */
void REGPARAM2 CPUFUNC(op_c080_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 2;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	m68k_dreg (regs, dstreg) = (src);
}}}	m68k_incpci (2);
return;
}

/* AND.L (An),Dn */
void REGPARAM2 CPUFUNC(op_c090_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 2;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	m68k_dreg (regs, dstreg) = (src);
}}}}	m68k_incpci (2);
return;
}

/* AND.L (An)+,Dn */
void REGPARAM2 CPUFUNC(op_c098_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 2;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, srcreg) += 4;
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	m68k_dreg (regs, dstreg) = (src);
}}}}	m68k_incpci (2);
return;
}

/* AND.L -(An),Dn */
void REGPARAM2 CPUFUNC(op_c0a0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 2;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	m68k_dreg (regs, dstreg) = (src);
}}}}	m68k_incpci (2);
return;
}

/* AND.L (d16,An),Dn */
void REGPARAM2 CPUFUNC(op_c0a8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 2;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	m68k_dreg (regs, dstreg) = (src);
}}}}	m68k_incpci (4);
return;
}

/* AND.L (d8,An,Xn),Dn */
void REGPARAM2 CPUFUNC(op_c0b0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 2;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	m68k_dreg (regs, dstreg) = (src);
}}}}}return;
}

/* AND.L (xxx).W,Dn */
void REGPARAM2 CPUFUNC(op_c0b8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 2;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	m68k_dreg (regs, dstreg) = (src);
}}}}	m68k_incpci (4);
return;
}

/* AND.L (xxx).L,Dn */
void REGPARAM2 CPUFUNC(op_c0b9_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 2;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	m68k_dreg (regs, dstreg) = (src);
}}}}	m68k_incpci (6);
return;
}

/* AND.L (d16,PC),Dn */
void REGPARAM2 CPUFUNC(op_c0ba_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 2;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	m68k_dreg (regs, dstreg) = (src);
}}}}	m68k_incpci (4);
return;
}

/* AND.L (d8,PC,Xn),Dn */
void REGPARAM2 CPUFUNC(op_c0bb_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 2;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	m68k_dreg (regs, dstreg) = (src);
}}}}}return;
}

/* AND.L #<data>.L,Dn */
void REGPARAM2 CPUFUNC(op_c0bc_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 2;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	m68k_dreg (regs, dstreg) = (src);
}}}	m68k_incpci (6);
return;
}

/* MULU.W Dn,Dn */
void REGPARAM2 CPUFUNC(op_c0c0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 62;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{	uae_u32 newv = (uae_u32)(uae_u16)dst * (uae_u32)(uae_u16)src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_NFLG (((uae_s32)(newv)) < 0);
	m68k_dreg (regs, dstreg) = (newv);
	m68k_incpci (2);
}}}}return;
}

/* MULU.W (An),Dn */
void REGPARAM2 CPUFUNC(op_c0d0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 62;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{	uae_u32 newv = (uae_u32)(uae_u16)dst * (uae_u32)(uae_u16)src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_NFLG (((uae_s32)(newv)) < 0);
	m68k_dreg (regs, dstreg) = (newv);
	m68k_incpci (2);
}}}}}return;
}

/* MULU.W (An)+,Dn */
void REGPARAM2 CPUFUNC(op_c0d8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 62;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{	uae_u32 newv = (uae_u32)(uae_u16)dst * (uae_u32)(uae_u16)src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_NFLG (((uae_s32)(newv)) < 0);
	m68k_dreg (regs, dstreg) = (newv);
	m68k_incpci (2);
}}}}}return;
}

/* MULU.W -(An),Dn */
void REGPARAM2 CPUFUNC(op_c0e0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 62;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{	uae_u32 newv = (uae_u32)(uae_u16)dst * (uae_u32)(uae_u16)src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_NFLG (((uae_s32)(newv)) < 0);
	m68k_dreg (regs, dstreg) = (newv);
	m68k_incpci (2);
}}}}}return;
}

/* MULU.W (d16,An),Dn */
void REGPARAM2 CPUFUNC(op_c0e8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 62;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{	uae_u32 newv = (uae_u32)(uae_u16)dst * (uae_u32)(uae_u16)src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_NFLG (((uae_s32)(newv)) < 0);
	m68k_dreg (regs, dstreg) = (newv);
	m68k_incpci (4);
}}}}}return;
}

/* MULU.W (d8,An,Xn),Dn */
void REGPARAM2 CPUFUNC(op_c0f0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 62;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{	uae_u32 newv = (uae_u32)(uae_u16)dst * (uae_u32)(uae_u16)src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_NFLG (((uae_s32)(newv)) < 0);
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}return;
}

/* MULU.W (xxx).W,Dn */
void REGPARAM2 CPUFUNC(op_c0f8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 62;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{	uae_u32 newv = (uae_u32)(uae_u16)dst * (uae_u32)(uae_u16)src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_NFLG (((uae_s32)(newv)) < 0);
	m68k_dreg (regs, dstreg) = (newv);
	m68k_incpci (4);
}}}}}return;
}

/* MULU.W (xxx).L,Dn */
void REGPARAM2 CPUFUNC(op_c0f9_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 62;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{	uae_u32 newv = (uae_u32)(uae_u16)dst * (uae_u32)(uae_u16)src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_NFLG (((uae_s32)(newv)) < 0);
	m68k_dreg (regs, dstreg) = (newv);
	m68k_incpci (6);
}}}}}return;
}

/* MULU.W (d16,PC),Dn */
void REGPARAM2 CPUFUNC(op_c0fa_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 62;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{	uae_u32 newv = (uae_u32)(uae_u16)dst * (uae_u32)(uae_u16)src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_NFLG (((uae_s32)(newv)) < 0);
	m68k_dreg (regs, dstreg) = (newv);
	m68k_incpci (4);
}}}}}return;
}

/* MULU.W (d8,PC,Xn),Dn */
void REGPARAM2 CPUFUNC(op_c0fb_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 62;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{	uae_u32 newv = (uae_u32)(uae_u16)dst * (uae_u32)(uae_u16)src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_NFLG (((uae_s32)(newv)) < 0);
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}return;
}

/* MULU.W #<data>.W,Dn */
void REGPARAM2 CPUFUNC(op_c0fc_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 62;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{	uae_u32 newv = (uae_u32)(uae_u16)dst * (uae_u32)(uae_u16)src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_NFLG (((uae_s32)(newv)) < 0);
	m68k_dreg (regs, dstreg) = (newv);
	m68k_incpci (4);
}}}}return;
}

/* ABCD.B Dn,Dn */
void REGPARAM2 CPUFUNC(op_c100_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 14;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
{	uae_u16 newv_lo = (src & 0xF) + (dst & 0xF) + (GET_XFLG () ? 1 : 0);
	uae_u16 newv_hi = (src & 0xF0) + (dst & 0xF0);
	uae_u16 newv, tmp_newv;
	int cflg;
	newv = tmp_newv = newv_hi + newv_lo;	if (newv_lo > 9) { newv += 6; }
	cflg = (newv & 0x3F0) > 0x90;
	if (cflg) newv += 0x60;
	SET_CFLG (cflg);
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s8)(newv)) == 0));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}	m68k_incpci (2);
return;
}

/* ABCD.B -(An),-(An) */
void REGPARAM2 CPUFUNC(op_c108_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 14;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = x_get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
{	uae_u16 newv_lo = (src & 0xF) + (dst & 0xF) + (GET_XFLG () ? 1 : 0);
	uae_u16 newv_hi = (src & 0xF0) + (dst & 0xF0);
	uae_u16 newv, tmp_newv;
	int cflg;
	newv = tmp_newv = newv_hi + newv_lo;	if (newv_lo > 9) { newv += 6; }
	cflg = (newv & 0x3F0) > 0x90;
	if (cflg) newv += 0x60;
	SET_CFLG (cflg);
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s8)(newv)) == 0));
	x_put_byte (dsta, newv);
}}}}}}	m68k_incpci (2);
return;
}

/* AND.B Dn,(An) */
void REGPARAM2 CPUFUNC(op_c110_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 2;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = x_get_byte (dsta);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}	m68k_incpci (2);
return;
}

/* AND.B Dn,(An)+ */
void REGPARAM2 CPUFUNC(op_c118_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 2;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}	m68k_incpci (2);
return;
}

/* AND.B Dn,-(An) */
void REGPARAM2 CPUFUNC(op_c120_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 2;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}	m68k_incpci (2);
return;
}

/* AND.B Dn,(d16,An) */
void REGPARAM2 CPUFUNC(op_c128_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 2;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 dst = x_get_byte (dsta);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}	m68k_incpci (4);
return;
}

/* AND.B Dn,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_c130_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 2;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	m68k_incpci (2);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s8 dst = x_get_byte (dsta);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}}return;
}

/* AND.B Dn,(xxx).W */
void REGPARAM2 CPUFUNC(op_c138_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	OpcodeFamily = 2;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 dst = x_get_byte (dsta);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}	m68k_incpci (4);
return;
}

/* AND.B Dn,(xxx).L */
void REGPARAM2 CPUFUNC(op_c139_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	OpcodeFamily = 2;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (2);
{	uae_s8 dst = x_get_byte (dsta);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s8)(src)) == 0);
	SET_NFLG (((uae_s8)(src)) < 0);
	x_put_byte (dsta, src);
}}}}	m68k_incpci (6);
return;
}

/* EXG.L Dn,Dn */
void REGPARAM2 CPUFUNC(op_c140_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 35;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	m68k_dreg (regs, srcreg) = (dst);
	m68k_dreg (regs, dstreg) = (src);
}}}	m68k_incpci (2);
return;
}

/* EXG.L An,An */
void REGPARAM2 CPUFUNC(op_c148_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 35;
{{	uae_s32 src = m68k_areg (regs, srcreg);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	m68k_areg (regs, srcreg) = (dst);
	m68k_areg (regs, dstreg) = (src);
}}}	m68k_incpci (2);
return;
}

/* AND.W Dn,(An) */
void REGPARAM2 CPUFUNC(op_c150_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 2;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s16 dst = x_get_word (dsta);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}	m68k_incpci (2);
return;
}

/* AND.W Dn,(An)+ */
void REGPARAM2 CPUFUNC(op_c158_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 2;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s16 dst = x_get_word (dsta);
	m68k_areg (regs, dstreg) += 2;
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}	m68k_incpci (2);
return;
}

/* AND.W Dn,-(An) */
void REGPARAM2 CPUFUNC(op_c160_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 2;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
{	uae_s16 dst = x_get_word (dsta);
	m68k_areg (regs, dstreg) = dsta;
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}	m68k_incpci (2);
return;
}

/* AND.W Dn,(d16,An) */
void REGPARAM2 CPUFUNC(op_c168_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 2;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 dst = x_get_word (dsta);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}	m68k_incpci (4);
return;
}

/* AND.W Dn,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_c170_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 2;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	m68k_incpci (2);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s16 dst = x_get_word (dsta);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}}return;
}

/* AND.W Dn,(xxx).W */
void REGPARAM2 CPUFUNC(op_c178_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	OpcodeFamily = 2;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 dst = x_get_word (dsta);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}	m68k_incpci (4);
return;
}

/* AND.W Dn,(xxx).L */
void REGPARAM2 CPUFUNC(op_c179_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	OpcodeFamily = 2;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (2);
{	uae_s16 dst = x_get_word (dsta);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(src)) == 0);
	SET_NFLG (((uae_s16)(src)) < 0);
	x_put_word (dsta, src);
}}}}	m68k_incpci (6);
return;
}

/* EXG.L Dn,An */
void REGPARAM2 CPUFUNC(op_c188_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 35;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	m68k_dreg (regs, srcreg) = (dst);
	m68k_areg (regs, dstreg) = (src);
}}}	m68k_incpci (2);
return;
}

/* AND.L Dn,(An) */
void REGPARAM2 CPUFUNC(op_c190_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 2;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s32 dst = x_get_long (dsta);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}	m68k_incpci (2);
return;
}

/* AND.L Dn,(An)+ */
void REGPARAM2 CPUFUNC(op_c198_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 2;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s32 dst = x_get_long (dsta);
	m68k_areg (regs, dstreg) += 4;
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}	m68k_incpci (2);
return;
}

/* AND.L Dn,-(An) */
void REGPARAM2 CPUFUNC(op_c1a0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 2;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
{	uae_s32 dst = x_get_long (dsta);
	m68k_areg (regs, dstreg) = dsta;
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}	m68k_incpci (2);
return;
}

/* AND.L Dn,(d16,An) */
void REGPARAM2 CPUFUNC(op_c1a8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 2;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 dst = x_get_long (dsta);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}	m68k_incpci (4);
return;
}

/* AND.L Dn,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_c1b0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 2;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	m68k_incpci (2);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s32 dst = x_get_long (dsta);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}}return;
}

/* AND.L Dn,(xxx).W */
void REGPARAM2 CPUFUNC(op_c1b8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	OpcodeFamily = 2;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 dst = x_get_long (dsta);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}	m68k_incpci (4);
return;
}

/* AND.L Dn,(xxx).L */
void REGPARAM2 CPUFUNC(op_c1b9_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	OpcodeFamily = 2;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (2);
{	uae_s32 dst = x_get_long (dsta);
	src &= dst;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(src)) == 0);
	SET_NFLG (((uae_s32)(src)) < 0);
	x_put_long (dsta, src);
}}}}	m68k_incpci (6);
return;
}

/* MULS.W Dn,Dn */
void REGPARAM2 CPUFUNC(op_c1c0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 63;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{	uae_u32 newv = (uae_s32)(uae_s16)dst * (uae_s32)(uae_s16)src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_NFLG (((uae_s32)(newv)) < 0);
	m68k_dreg (regs, dstreg) = (newv);
}}}}	m68k_incpci (2);
return;
}

/* MULS.W (An),Dn */
void REGPARAM2 CPUFUNC(op_c1d0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 63;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{	uae_u32 newv = (uae_s32)(uae_s16)dst * (uae_s32)(uae_s16)src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_NFLG (((uae_s32)(newv)) < 0);
	m68k_dreg (regs, dstreg) = (newv);
}}}}}	m68k_incpci (2);
return;
}

/* MULS.W (An)+,Dn */
void REGPARAM2 CPUFUNC(op_c1d8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 63;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{	uae_u32 newv = (uae_s32)(uae_s16)dst * (uae_s32)(uae_s16)src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_NFLG (((uae_s32)(newv)) < 0);
	m68k_dreg (regs, dstreg) = (newv);
}}}}}	m68k_incpci (2);
return;
}

/* MULS.W -(An),Dn */
void REGPARAM2 CPUFUNC(op_c1e0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 63;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{	uae_u32 newv = (uae_s32)(uae_s16)dst * (uae_s32)(uae_s16)src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_NFLG (((uae_s32)(newv)) < 0);
	m68k_dreg (regs, dstreg) = (newv);
}}}}}	m68k_incpci (2);
return;
}

/* MULS.W (d16,An),Dn */
void REGPARAM2 CPUFUNC(op_c1e8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 63;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{	uae_u32 newv = (uae_s32)(uae_s16)dst * (uae_s32)(uae_s16)src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_NFLG (((uae_s32)(newv)) < 0);
	m68k_dreg (regs, dstreg) = (newv);
}}}}}	m68k_incpci (4);
return;
}

/* MULS.W (d8,An,Xn),Dn */
void REGPARAM2 CPUFUNC(op_c1f0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 63;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{	uae_u32 newv = (uae_s32)(uae_s16)dst * (uae_s32)(uae_s16)src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_NFLG (((uae_s32)(newv)) < 0);
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}return;
}

/* MULS.W (xxx).W,Dn */
void REGPARAM2 CPUFUNC(op_c1f8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 63;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{	uae_u32 newv = (uae_s32)(uae_s16)dst * (uae_s32)(uae_s16)src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_NFLG (((uae_s32)(newv)) < 0);
	m68k_dreg (regs, dstreg) = (newv);
}}}}}	m68k_incpci (4);
return;
}

/* MULS.W (xxx).L,Dn */
void REGPARAM2 CPUFUNC(op_c1f9_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 63;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{	uae_u32 newv = (uae_s32)(uae_s16)dst * (uae_s32)(uae_s16)src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_NFLG (((uae_s32)(newv)) < 0);
	m68k_dreg (regs, dstreg) = (newv);
}}}}}	m68k_incpci (6);
return;
}

/* MULS.W (d16,PC),Dn */
void REGPARAM2 CPUFUNC(op_c1fa_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 63;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{	uae_u32 newv = (uae_s32)(uae_s16)dst * (uae_s32)(uae_s16)src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_NFLG (((uae_s32)(newv)) < 0);
	m68k_dreg (regs, dstreg) = (newv);
}}}}}	m68k_incpci (4);
return;
}

/* MULS.W (d8,PC,Xn),Dn */
void REGPARAM2 CPUFUNC(op_c1fb_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 63;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{	uae_u32 newv = (uae_s32)(uae_s16)dst * (uae_s32)(uae_s16)src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_NFLG (((uae_s32)(newv)) < 0);
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}return;
}

/* MULS.W #<data>.W,Dn */
void REGPARAM2 CPUFUNC(op_c1fc_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 63;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{	uae_u32 newv = (uae_s32)(uae_s16)dst * (uae_s32)(uae_s16)src;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_NFLG (((uae_s32)(newv)) < 0);
	m68k_dreg (regs, dstreg) = (newv);
}}}}	m68k_incpci (4);
return;
}

/* ADD.B Dn,Dn */
void REGPARAM2 CPUFUNC(op_d000_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 11;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u8)(dst)) + ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u8)(~dst)) < ((uae_u8)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}}	m68k_incpci (2);
return;
}

/* ADD.B (An),Dn */
void REGPARAM2 CPUFUNC(op_d010_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 11;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s8 src = x_get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u8)(dst)) + ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u8)(~dst)) < ((uae_u8)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}}}	m68k_incpci (2);
return;
}

/* ADD.B (An)+,Dn */
void REGPARAM2 CPUFUNC(op_d018_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 11;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s8 src = x_get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{	uae_s8 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u8)(dst)) + ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u8)(~dst)) < ((uae_u8)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}}}	m68k_incpci (2);
return;
}

/* ADD.B -(An),Dn */
void REGPARAM2 CPUFUNC(op_d020_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 11;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = x_get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s8 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u8)(dst)) + ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u8)(~dst)) < ((uae_u8)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}}}	m68k_incpci (2);
return;
}

/* ADD.B (d16,An),Dn */
void REGPARAM2 CPUFUNC(op_d028_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 11;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u8)(dst)) + ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u8)(~dst)) < ((uae_u8)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}}}	m68k_incpci (4);
return;
}

/* ADD.B (d8,An,Xn),Dn */
void REGPARAM2 CPUFUNC(op_d030_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 11;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s8 src = x_get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u8)(dst)) + ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u8)(~dst)) < ((uae_u8)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}}}}return;
}

/* ADD.B (xxx).W,Dn */
void REGPARAM2 CPUFUNC(op_d038_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 11;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u8)(dst)) + ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u8)(~dst)) < ((uae_u8)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}}}	m68k_incpci (4);
return;
}

/* ADD.B (xxx).L,Dn */
void REGPARAM2 CPUFUNC(op_d039_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 11;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u8)(dst)) + ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u8)(~dst)) < ((uae_u8)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}}}	m68k_incpci (6);
return;
}

/* ADD.B (d16,PC),Dn */
void REGPARAM2 CPUFUNC(op_d03a_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 11;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 src = x_get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u8)(dst)) + ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u8)(~dst)) < ((uae_u8)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}}}	m68k_incpci (4);
return;
}

/* ADD.B (d8,PC,Xn),Dn */
void REGPARAM2 CPUFUNC(op_d03b_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 11;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s8 src = x_get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u8)(dst)) + ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u8)(~dst)) < ((uae_u8)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}}}}return;
}

/* ADD.B #<data>.B,Dn */
void REGPARAM2 CPUFUNC(op_d03c_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 11;
{{	uae_s8 src = (uae_u8)get_iword_cache_040 (2);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u8)(dst)) + ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u8)(~dst)) < ((uae_u8)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}}	m68k_incpci (4);
return;
}

/* ADD.W Dn,Dn */
void REGPARAM2 CPUFUNC(op_d040_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 11;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u16)(dst)) + ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u16)(~dst)) < ((uae_u16)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}}	m68k_incpci (2);
return;
}

/* ADD.W An,Dn */
void REGPARAM2 CPUFUNC(op_d048_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 11;
{{	uae_s16 src = m68k_areg (regs, srcreg);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u16)(dst)) + ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u16)(~dst)) < ((uae_u16)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}}	m68k_incpci (2);
return;
}

/* ADD.W (An),Dn */
void REGPARAM2 CPUFUNC(op_d050_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 11;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u16)(dst)) + ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u16)(~dst)) < ((uae_u16)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}}}	m68k_incpci (2);
return;
}

/* ADD.W (An)+,Dn */
void REGPARAM2 CPUFUNC(op_d058_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 11;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u16)(dst)) + ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u16)(~dst)) < ((uae_u16)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}}}	m68k_incpci (2);
return;
}

/* ADD.W -(An),Dn */
void REGPARAM2 CPUFUNC(op_d060_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 11;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u16)(dst)) + ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u16)(~dst)) < ((uae_u16)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}}}	m68k_incpci (2);
return;
}

/* ADD.W (d16,An),Dn */
void REGPARAM2 CPUFUNC(op_d068_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 11;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u16)(dst)) + ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u16)(~dst)) < ((uae_u16)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}}}	m68k_incpci (4);
return;
}

/* ADD.W (d8,An,Xn),Dn */
void REGPARAM2 CPUFUNC(op_d070_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 11;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u16)(dst)) + ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u16)(~dst)) < ((uae_u16)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}}}}return;
}

/* ADD.W (xxx).W,Dn */
void REGPARAM2 CPUFUNC(op_d078_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 11;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u16)(dst)) + ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u16)(~dst)) < ((uae_u16)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}}}	m68k_incpci (4);
return;
}

/* ADD.W (xxx).L,Dn */
void REGPARAM2 CPUFUNC(op_d079_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 11;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u16)(dst)) + ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u16)(~dst)) < ((uae_u16)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}}}	m68k_incpci (6);
return;
}

/* ADD.W (d16,PC),Dn */
void REGPARAM2 CPUFUNC(op_d07a_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 11;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u16)(dst)) + ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u16)(~dst)) < ((uae_u16)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}}}	m68k_incpci (4);
return;
}

/* ADD.W (d8,PC,Xn),Dn */
void REGPARAM2 CPUFUNC(op_d07b_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 11;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s16 src = x_get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u16)(dst)) + ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u16)(~dst)) < ((uae_u16)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}}}}return;
}

/* ADD.W #<data>.W,Dn */
void REGPARAM2 CPUFUNC(op_d07c_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 11;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u16)(dst)) + ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u16)(~dst)) < ((uae_u16)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}}	m68k_incpci (4);
return;
}

/* ADD.L Dn,Dn */
void REGPARAM2 CPUFUNC(op_d080_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 11;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) + ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u32)(~dst)) < ((uae_u32)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}	m68k_incpci (2);
return;
}

/* ADD.L An,Dn */
void REGPARAM2 CPUFUNC(op_d088_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 11;
{{	uae_s32 src = m68k_areg (regs, srcreg);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) + ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u32)(~dst)) < ((uae_u32)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}	m68k_incpci (2);
return;
}

/* ADD.L (An),Dn */
void REGPARAM2 CPUFUNC(op_d090_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 11;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) + ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u32)(~dst)) < ((uae_u32)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}}	m68k_incpci (2);
return;
}

/* ADD.L (An)+,Dn */
void REGPARAM2 CPUFUNC(op_d098_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 11;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, srcreg) += 4;
{	uae_s32 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) + ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u32)(~dst)) < ((uae_u32)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}}	m68k_incpci (2);
return;
}

/* ADD.L -(An),Dn */
void REGPARAM2 CPUFUNC(op_d0a0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 11;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s32 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) + ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u32)(~dst)) < ((uae_u32)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}}	m68k_incpci (2);
return;
}

/* ADD.L (d16,An),Dn */
void REGPARAM2 CPUFUNC(op_d0a8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 11;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) + ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u32)(~dst)) < ((uae_u32)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}}	m68k_incpci (4);
return;
}

/* ADD.L (d8,An,Xn),Dn */
void REGPARAM2 CPUFUNC(op_d0b0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 11;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) + ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u32)(~dst)) < ((uae_u32)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}}}return;
}

/* ADD.L (xxx).W,Dn */
void REGPARAM2 CPUFUNC(op_d0b8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 11;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) + ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u32)(~dst)) < ((uae_u32)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}}	m68k_incpci (4);
return;
}

/* ADD.L (xxx).L,Dn */
void REGPARAM2 CPUFUNC(op_d0b9_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 11;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) + ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u32)(~dst)) < ((uae_u32)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}}	m68k_incpci (6);
return;
}

/* ADD.L (d16,PC),Dn */
void REGPARAM2 CPUFUNC(op_d0ba_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 11;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) + ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u32)(~dst)) < ((uae_u32)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}}	m68k_incpci (4);
return;
}

/* ADD.L (d8,PC,Xn),Dn */
void REGPARAM2 CPUFUNC(op_d0bb_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 11;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) + ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u32)(~dst)) < ((uae_u32)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}}}return;
}

/* ADD.L #<data>.L,Dn */
void REGPARAM2 CPUFUNC(op_d0bc_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 11;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
{{uae_u32 newv = ((uae_u32)(dst)) + ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u32)(~dst)) < ((uae_u32)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}	m68k_incpci (6);
return;
}

/* ADDA.W Dn,An */
void REGPARAM2 CPUFUNC(op_d0c0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 12;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}	m68k_incpci (2);
return;
}

/* ADDA.W An,An */
void REGPARAM2 CPUFUNC(op_d0c8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 12;
{{	uae_s16 src = m68k_areg (regs, srcreg);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}	m68k_incpci (2);
return;
}

/* ADDA.W (An),An */
void REGPARAM2 CPUFUNC(op_d0d0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 12;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}	m68k_incpci (2);
return;
}

/* ADDA.W (An)+,An */
void REGPARAM2 CPUFUNC(op_d0d8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 12;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}	m68k_incpci (2);
return;
}

/* ADDA.W -(An),An */
void REGPARAM2 CPUFUNC(op_d0e0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 12;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}	m68k_incpci (2);
return;
}

/* ADDA.W (d16,An),An */
void REGPARAM2 CPUFUNC(op_d0e8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 12;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}	m68k_incpci (4);
return;
}

/* ADDA.W (d8,An,Xn),An */
void REGPARAM2 CPUFUNC(op_d0f0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 12;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s16 src = x_get_word (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}}return;
}

/* ADDA.W (xxx).W,An */
void REGPARAM2 CPUFUNC(op_d0f8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 12;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}	m68k_incpci (4);
return;
}

/* ADDA.W (xxx).L,An */
void REGPARAM2 CPUFUNC(op_d0f9_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 12;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}	m68k_incpci (6);
return;
}

/* ADDA.W (d16,PC),An */
void REGPARAM2 CPUFUNC(op_d0fa_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 12;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 src = x_get_word (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}	m68k_incpci (4);
return;
}

/* ADDA.W (d8,PC,Xn),An */
void REGPARAM2 CPUFUNC(op_d0fb_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 12;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s16 src = x_get_word (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}}return;
}

/* ADDA.W #<data>.W,An */
void REGPARAM2 CPUFUNC(op_d0fc_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 12;
{{	uae_s16 src = get_iword_cache_040 (2);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}	m68k_incpci (4);
return;
}

/* ADDX.B Dn,Dn */
void REGPARAM2 CPUFUNC(op_d100_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 13;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
{	uae_u32 newv = dst + src + (GET_XFLG () ? 1 : 0);
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgo) & (flgo ^ flgn)));
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s8)(newv)) == 0));
	SET_NFLG (((uae_s8)(newv)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}	m68k_incpci (2);
return;
}

/* ADDX.B -(An),-(An) */
void REGPARAM2 CPUFUNC(op_d108_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 13;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = x_get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
{	uae_u32 newv = dst + src + (GET_XFLG () ? 1 : 0);
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgo) & (flgo ^ flgn)));
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s8)(newv)) == 0));
	SET_NFLG (((uae_s8)(newv)) < 0);
	x_put_byte (dsta, newv);
}}}}}}}	m68k_incpci (2);
return;
}

/* ADD.B Dn,(An) */
void REGPARAM2 CPUFUNC(op_d110_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = x_get_byte (dsta);
{{uae_u32 newv = ((uae_u8)(dst)) + ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u8)(~dst)) < ((uae_u8)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (dsta, newv);
}}}}}}}	m68k_incpci (2);
return;
}

/* ADD.B Dn,(An)+ */
void REGPARAM2 CPUFUNC(op_d118_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
{{uae_u32 newv = ((uae_u8)(dst)) + ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u8)(~dst)) < ((uae_u8)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (dsta, newv);
}}}}}}}	m68k_incpci (2);
return;
}

/* ADD.B Dn,-(An) */
void REGPARAM2 CPUFUNC(op_d120_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = x_get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
{{uae_u32 newv = ((uae_u8)(dst)) + ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u8)(~dst)) < ((uae_u8)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (dsta, newv);
}}}}}}}	m68k_incpci (2);
return;
}

/* ADD.B Dn,(d16,An) */
void REGPARAM2 CPUFUNC(op_d128_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 dst = x_get_byte (dsta);
{{uae_u32 newv = ((uae_u8)(dst)) + ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u8)(~dst)) < ((uae_u8)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (dsta, newv);
}}}}}}}	m68k_incpci (4);
return;
}

/* ADD.B Dn,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_d130_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	m68k_incpci (2);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s8 dst = x_get_byte (dsta);
{{uae_u32 newv = ((uae_u8)(dst)) + ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u8)(~dst)) < ((uae_u8)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (dsta, newv);
}}}}}}}}return;
}

/* ADD.B Dn,(xxx).W */
void REGPARAM2 CPUFUNC(op_d138_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	OpcodeFamily = 11;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s8 dst = x_get_byte (dsta);
{{uae_u32 newv = ((uae_u8)(dst)) + ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u8)(~dst)) < ((uae_u8)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (dsta, newv);
}}}}}}}	m68k_incpci (4);
return;
}

/* ADD.B Dn,(xxx).L */
void REGPARAM2 CPUFUNC(op_d139_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	OpcodeFamily = 11;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (2);
{	uae_s8 dst = x_get_byte (dsta);
{{uae_u32 newv = ((uae_u8)(dst)) + ((uae_u8)(src));
{	int flgs = ((uae_s8)(src)) < 0;
	int flgo = ((uae_s8)(dst)) < 0;
	int flgn = ((uae_s8)(newv)) < 0;
	SET_ZFLG (((uae_s8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u8)(~dst)) < ((uae_u8)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_byte (dsta, newv);
}}}}}}}	m68k_incpci (6);
return;
}

/* ADDX.W Dn,Dn */
void REGPARAM2 CPUFUNC(op_d140_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 13;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
{	uae_u32 newv = dst + src + (GET_XFLG () ? 1 : 0);
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgo) & (flgo ^ flgn)));
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s16)(newv)) == 0));
	SET_NFLG (((uae_s16)(newv)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}	m68k_incpci (2);
return;
}

/* ADDX.W -(An),-(An) */
void REGPARAM2 CPUFUNC(op_d148_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 13;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
{	uae_s16 src = x_get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
{	uae_s16 dst = x_get_word (dsta);
	m68k_areg (regs, dstreg) = dsta;
{	uae_u32 newv = dst + src + (GET_XFLG () ? 1 : 0);
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgo) & (flgo ^ flgn)));
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s16)(newv)) == 0));
	SET_NFLG (((uae_s16)(newv)) < 0);
	x_put_word (dsta, newv);
}}}}}}}	m68k_incpci (2);
return;
}

/* ADD.W Dn,(An) */
void REGPARAM2 CPUFUNC(op_d150_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s16 dst = x_get_word (dsta);
{{uae_u32 newv = ((uae_u16)(dst)) + ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u16)(~dst)) < ((uae_u16)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (dsta, newv);
}}}}}}}	m68k_incpci (2);
return;
}

/* ADD.W Dn,(An)+ */
void REGPARAM2 CPUFUNC(op_d158_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s16 dst = x_get_word (dsta);
	m68k_areg (regs, dstreg) += 2;
{{uae_u32 newv = ((uae_u16)(dst)) + ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u16)(~dst)) < ((uae_u16)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (dsta, newv);
}}}}}}}	m68k_incpci (2);
return;
}

/* ADD.W Dn,-(An) */
void REGPARAM2 CPUFUNC(op_d160_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
{	uae_s16 dst = x_get_word (dsta);
	m68k_areg (regs, dstreg) = dsta;
{{uae_u32 newv = ((uae_u16)(dst)) + ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u16)(~dst)) < ((uae_u16)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (dsta, newv);
}}}}}}}	m68k_incpci (2);
return;
}

/* ADD.W Dn,(d16,An) */
void REGPARAM2 CPUFUNC(op_d168_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 dst = x_get_word (dsta);
{{uae_u32 newv = ((uae_u16)(dst)) + ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u16)(~dst)) < ((uae_u16)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (dsta, newv);
}}}}}}}	m68k_incpci (4);
return;
}

/* ADD.W Dn,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_d170_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	m68k_incpci (2);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s16 dst = x_get_word (dsta);
{{uae_u32 newv = ((uae_u16)(dst)) + ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u16)(~dst)) < ((uae_u16)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (dsta, newv);
}}}}}}}}return;
}

/* ADD.W Dn,(xxx).W */
void REGPARAM2 CPUFUNC(op_d178_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	OpcodeFamily = 11;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 dst = x_get_word (dsta);
{{uae_u32 newv = ((uae_u16)(dst)) + ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u16)(~dst)) < ((uae_u16)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (dsta, newv);
}}}}}}}	m68k_incpci (4);
return;
}

/* ADD.W Dn,(xxx).L */
void REGPARAM2 CPUFUNC(op_d179_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	OpcodeFamily = 11;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (2);
{	uae_s16 dst = x_get_word (dsta);
{{uae_u32 newv = ((uae_u16)(dst)) + ((uae_u16)(src));
{	int flgs = ((uae_s16)(src)) < 0;
	int flgo = ((uae_s16)(dst)) < 0;
	int flgn = ((uae_s16)(newv)) < 0;
	SET_ZFLG (((uae_s16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u16)(~dst)) < ((uae_u16)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_word (dsta, newv);
}}}}}}}	m68k_incpci (6);
return;
}

/* ADDX.L Dn,Dn */
void REGPARAM2 CPUFUNC(op_d180_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 13;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
{	uae_u32 newv = dst + src + (GET_XFLG () ? 1 : 0);
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgo) & (flgo ^ flgn)));
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s32)(newv)) == 0));
	SET_NFLG (((uae_s32)(newv)) < 0);
	m68k_dreg (regs, dstreg) = (newv);
}}}}}	m68k_incpci (2);
return;
}

/* ADDX.L -(An),-(An) */
void REGPARAM2 CPUFUNC(op_d188_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 13;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
{	uae_s32 dst = x_get_long (dsta);
	m68k_areg (regs, dstreg) = dsta;
{	uae_u32 newv = dst + src + (GET_XFLG () ? 1 : 0);
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgo) & (flgo ^ flgn)));
	COPY_CARRY ();
	SET_ZFLG (GET_ZFLG () & (((uae_s32)(newv)) == 0));
	SET_NFLG (((uae_s32)(newv)) < 0);
	x_put_long (dsta, newv);
}}}}}}}	m68k_incpci (2);
return;
}

/* ADD.L Dn,(An) */
void REGPARAM2 CPUFUNC(op_d190_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s32 dst = x_get_long (dsta);
{{uae_u32 newv = ((uae_u32)(dst)) + ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u32)(~dst)) < ((uae_u32)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (dsta, newv);
}}}}}}}	m68k_incpci (2);
return;
}

/* ADD.L Dn,(An)+ */
void REGPARAM2 CPUFUNC(op_d198_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_s32 dst = x_get_long (dsta);
	m68k_areg (regs, dstreg) += 4;
{{uae_u32 newv = ((uae_u32)(dst)) + ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u32)(~dst)) < ((uae_u32)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (dsta, newv);
}}}}}}}	m68k_incpci (2);
return;
}

/* ADD.L Dn,-(An) */
void REGPARAM2 CPUFUNC(op_d1a0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
{	uae_s32 dst = x_get_long (dsta);
	m68k_areg (regs, dstreg) = dsta;
{{uae_u32 newv = ((uae_u32)(dst)) + ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u32)(~dst)) < ((uae_u32)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (dsta, newv);
}}}}}}}	m68k_incpci (2);
return;
}

/* ADD.L Dn,(d16,An) */
void REGPARAM2 CPUFUNC(op_d1a8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 dst = x_get_long (dsta);
{{uae_u32 newv = ((uae_u32)(dst)) + ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u32)(~dst)) < ((uae_u32)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (dsta, newv);
}}}}}}}	m68k_incpci (4);
return;
}

/* ADD.L Dn,(d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_d1b0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 11;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	m68k_incpci (2);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_s32 dst = x_get_long (dsta);
{{uae_u32 newv = ((uae_u32)(dst)) + ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u32)(~dst)) < ((uae_u32)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (dsta, newv);
}}}}}}}}return;
}

/* ADD.L Dn,(xxx).W */
void REGPARAM2 CPUFUNC(op_d1b8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	OpcodeFamily = 11;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 dst = x_get_long (dsta);
{{uae_u32 newv = ((uae_u32)(dst)) + ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u32)(~dst)) < ((uae_u32)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (dsta, newv);
}}}}}}}	m68k_incpci (4);
return;
}

/* ADD.L Dn,(xxx).L */
void REGPARAM2 CPUFUNC(op_d1b9_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	OpcodeFamily = 11;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (2);
{	uae_s32 dst = x_get_long (dsta);
{{uae_u32 newv = ((uae_u32)(dst)) + ((uae_u32)(src));
{	int flgs = ((uae_s32)(src)) < 0;
	int flgo = ((uae_s32)(dst)) < 0;
	int flgn = ((uae_s32)(newv)) < 0;
	SET_ZFLG (((uae_s32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((uae_u32)(~dst)) < ((uae_u32)(src)));
	COPY_CARRY ();
	SET_NFLG (flgn != 0);
	x_put_long (dsta, newv);
}}}}}}}	m68k_incpci (6);
return;
}

/* ADDA.L Dn,An */
void REGPARAM2 CPUFUNC(op_d1c0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 12;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}	m68k_incpci (2);
return;
}

/* ADDA.L An,An */
void REGPARAM2 CPUFUNC(op_d1c8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 12;
{{	uae_s32 src = m68k_areg (regs, srcreg);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}	m68k_incpci (2);
return;
}

/* ADDA.L (An),An */
void REGPARAM2 CPUFUNC(op_d1d0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 12;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}	m68k_incpci (2);
return;
}

/* ADDA.L (An)+,An */
void REGPARAM2 CPUFUNC(op_d1d8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 12;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg);
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, srcreg) += 4;
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}	m68k_incpci (2);
return;
}

/* ADDA.L -(An),An */
void REGPARAM2 CPUFUNC(op_d1e0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 12;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
{	uae_s32 src = x_get_long (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}	m68k_incpci (2);
return;
}

/* ADDA.L (d16,An),An */
void REGPARAM2 CPUFUNC(op_d1e8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 12;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}	m68k_incpci (4);
return;
}

/* ADDA.L (d8,An,Xn),An */
void REGPARAM2 CPUFUNC(op_d1f0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 12;
{{	uaecptr srca;
	m68k_incpci (2);
{	srca = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}}return;
}

/* ADDA.L (xxx).W,An */
void REGPARAM2 CPUFUNC(op_d1f8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 12;
{{	uaecptr srca;
	srca = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}	m68k_incpci (4);
return;
}

/* ADDA.L (xxx).L,An */
void REGPARAM2 CPUFUNC(op_d1f9_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 12;
{{	uaecptr srca;
	srca = get_ilong_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}	m68k_incpci (6);
return;
}

/* ADDA.L (d16,PC),An */
void REGPARAM2 CPUFUNC(op_d1fa_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 12;
{{	uaecptr srca;
	srca = m68k_getpci () + 2;
	srca += (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}	m68k_incpci (4);
return;
}

/* ADDA.L (d8,PC,Xn),An */
void REGPARAM2 CPUFUNC(op_d1fb_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 12;
{{	uaecptr tmppc;
	uaecptr srca;
	m68k_incpci (2);
{	tmppc = m68k_getpci ();
	srca = x_get_disp_ea_040 (tmppc, 0);
{	uae_s32 src = x_get_long (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}}return;
}

/* ADDA.L #<data>.L,An */
void REGPARAM2 CPUFUNC(op_d1fc_24)(uae_u32 opcode)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
	OpcodeFamily = 12;
{{	uae_s32 src;
	src = get_ilong_cache_040 (2);
{	uae_s32 dst = m68k_areg (regs, dstreg);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}	m68k_incpci (6);
return;
}

/* ASRQ.B #<data>,Dn */
void REGPARAM2 CPUFUNC(op_e000_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 64;
{{	uae_u32 cnt = srcreg;
{	uae_s8 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = (uae_u8)data;
	uae_u32 sign = (0x80 & val) >> 7;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
	if (cnt >= 8) {
		val = 0xff & (uae_u32)-sign;
		SET_CFLG (sign);
		COPY_CARRY ();
	} else {
		val >>= cnt - 1;
		SET_CFLG (val & 1);
		COPY_CARRY ();
		val >>= 1;
		val |= (0xff << (8 - cnt)) & (uae_u32)-sign;
		val &= 0xff;
	}
	SET_ZFLG (((uae_s8)(val)) == 0);
	SET_NFLG (((uae_s8)(val)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpci (2);
return;
}

/* LSRQ.B #<data>,Dn */
void REGPARAM2 CPUFUNC(op_e008_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 66;
{{	uae_u32 cnt = srcreg;
{	uae_s8 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = (uae_u8)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
	if (cnt >= 8) {
		SET_CFLG ((cnt == 8) & (val >> 7));
		COPY_CARRY ();
		val = 0;
	} else {
		val >>= cnt - 1;
		SET_CFLG (val & 1);
		COPY_CARRY ();
		val >>= 1;
	}
	SET_ZFLG (((uae_s8)(val)) == 0);
	SET_NFLG (((uae_s8)(val)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpci (2);
return;
}

/* ROXRQ.B #<data>,Dn */
void REGPARAM2 CPUFUNC(op_e010_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 71;
{{	uae_u32 cnt = srcreg;
{	uae_s8 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = (uae_u8)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
{	cnt--;
	{
	uae_u32 carry;
	uae_u32 hival = (val << 1) | GET_XFLG ();
	hival <<= (7 - cnt);
	val >>= cnt;
	carry = val & 1;
	val >>= 1;
	val |= hival;
	SET_XFLG (carry);
	val &= 0xff;
	} }
	SET_CFLG (GET_XFLG ());
	SET_ZFLG (((uae_s8)(val)) == 0);
	SET_NFLG (((uae_s8)(val)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpci (2);
return;
}

/* RORQ.B #<data>,Dn */
void REGPARAM2 CPUFUNC(op_e018_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 69;
{{	uae_u32 cnt = srcreg;
{	uae_s8 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = (uae_u8)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
{	uae_u32 hival;
	cnt &= 7;
	hival = val << (8 - cnt);
	val >>= cnt;
	val |= hival;
	val &= 0xff;
	SET_CFLG ((val & 0x80) >> 7);
	}
	SET_ZFLG (((uae_s8)(val)) == 0);
	SET_NFLG (((uae_s8)(val)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpci (2);
return;
}

/* ASR.B Dn,Dn */
void REGPARAM2 CPUFUNC(op_e020_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 64;
{{	uae_s8 cnt = m68k_dreg (regs, srcreg);
{	uae_s8 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = (uae_u8)data;
	uae_u32 sign = (0x80 & val) >> 7;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
	if (cnt >= 8) {
		val = 0xff & (uae_u32)-sign;
		SET_CFLG (sign);
		COPY_CARRY ();
	} else if (cnt > 0) {
		val >>= cnt - 1;
		SET_CFLG (val & 1);
		COPY_CARRY ();
		val >>= 1;
		val |= (0xff << (8 - cnt)) & (uae_u32)-sign;
		val &= 0xff;
	}
	SET_ZFLG (((uae_s8)(val)) == 0);
	SET_NFLG (((uae_s8)(val)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpci (2);
return;
}

/* LSR.B Dn,Dn */
void REGPARAM2 CPUFUNC(op_e028_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 66;
{{	uae_s8 cnt = m68k_dreg (regs, srcreg);
{	uae_s8 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = (uae_u8)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
	if (cnt >= 8) {
		SET_CFLG ((cnt == 8) & (val >> 7));
		COPY_CARRY ();
		val = 0;
	} else if (cnt > 0) {
		val >>= cnt - 1;
		SET_CFLG (val & 1);
		COPY_CARRY ();
		val >>= 1;
	}
	SET_ZFLG (((uae_s8)(val)) == 0);
	SET_NFLG (((uae_s8)(val)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpci (2);
return;
}

/* ROXR.B Dn,Dn */
void REGPARAM2 CPUFUNC(op_e030_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 71;
{{	uae_s8 cnt = m68k_dreg (regs, srcreg);
{	uae_s8 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = (uae_u8)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
	if (cnt >= 36) cnt -= 36;
	if (cnt >= 18) cnt -= 18;
	if (cnt >= 9) cnt -= 9;
	if (cnt > 0) {
	cnt--;
	{
	uae_u32 carry;
	uae_u32 hival = (val << 1) | GET_XFLG ();
	hival <<= (7 - cnt);
	val >>= cnt;
	carry = val & 1;
	val >>= 1;
	val |= hival;
	SET_XFLG (carry);
	val &= 0xff;
	} }
	SET_CFLG (GET_XFLG ());
	SET_ZFLG (((uae_s8)(val)) == 0);
	SET_NFLG (((uae_s8)(val)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpci (2);
return;
}

/* ROR.B Dn,Dn */
void REGPARAM2 CPUFUNC(op_e038_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 69;
{{	uae_s8 cnt = m68k_dreg (regs, srcreg);
{	uae_s8 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = (uae_u8)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
	if (cnt > 0) {	uae_u32 hival;
	cnt &= 7;
	hival = val << (8 - cnt);
	val >>= cnt;
	val |= hival;
	val &= 0xff;
	SET_CFLG ((val & 0x80) >> 7);
	}
	SET_ZFLG (((uae_s8)(val)) == 0);
	SET_NFLG (((uae_s8)(val)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpci (2);
return;
}

/* ASRQ.W #<data>,Dn */
void REGPARAM2 CPUFUNC(op_e040_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 64;
{{	uae_u32 cnt = srcreg;
{	uae_s16 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = (uae_u16)data;
	uae_u32 sign = (0x8000 & val) >> 15;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
	if (cnt >= 16) {
		val = 0xffff & (uae_u32)-sign;
		SET_CFLG (sign);
		COPY_CARRY ();
	} else {
		val >>= cnt - 1;
		SET_CFLG (val & 1);
		COPY_CARRY ();
		val >>= 1;
		val |= (0xffff << (16 - cnt)) & (uae_u32)-sign;
		val &= 0xffff;
	}
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}}}}	m68k_incpci (2);
return;
}

#endif

#ifdef PART_8
/* LSRQ.W #<data>,Dn */
void REGPARAM2 CPUFUNC(op_e048_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 66;
{{	uae_u32 cnt = srcreg;
{	uae_s16 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = (uae_u16)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
	if (cnt >= 16) {
		SET_CFLG ((cnt == 16) & (val >> 15));
		COPY_CARRY ();
		val = 0;
	} else {
		val >>= cnt - 1;
		SET_CFLG (val & 1);
		COPY_CARRY ();
		val >>= 1;
	}
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}}}}	m68k_incpci (2);
return;
}

/* ROXRQ.W #<data>,Dn */
void REGPARAM2 CPUFUNC(op_e050_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 71;
{{	uae_u32 cnt = srcreg;
{	uae_s16 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = (uae_u16)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
{	cnt--;
	{
	uae_u32 carry;
	uae_u32 hival = (val << 1) | GET_XFLG ();
	hival <<= (15 - cnt);
	val >>= cnt;
	carry = val & 1;
	val >>= 1;
	val |= hival;
	SET_XFLG (carry);
	val &= 0xffff;
	} }
	SET_CFLG (GET_XFLG ());
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}}}}	m68k_incpci (2);
return;
}

/* RORQ.W #<data>,Dn */
void REGPARAM2 CPUFUNC(op_e058_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 69;
{{	uae_u32 cnt = srcreg;
{	uae_s16 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = (uae_u16)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
{	uae_u32 hival;
	cnt &= 15;
	hival = val << (16 - cnt);
	val >>= cnt;
	val |= hival;
	val &= 0xffff;
	SET_CFLG ((val & 0x8000) >> 15);
	}
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}}}}	m68k_incpci (2);
return;
}

/* ASR.W Dn,Dn */
void REGPARAM2 CPUFUNC(op_e060_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 64;
{{	uae_s16 cnt = m68k_dreg (regs, srcreg);
{	uae_s16 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = (uae_u16)data;
	uae_u32 sign = (0x8000 & val) >> 15;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
	if (cnt >= 16) {
		val = 0xffff & (uae_u32)-sign;
		SET_CFLG (sign);
		COPY_CARRY ();
	} else if (cnt > 0) {
		val >>= cnt - 1;
		SET_CFLG (val & 1);
		COPY_CARRY ();
		val >>= 1;
		val |= (0xffff << (16 - cnt)) & (uae_u32)-sign;
		val &= 0xffff;
	}
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}}}}	m68k_incpci (2);
return;
}

/* LSR.W Dn,Dn */
void REGPARAM2 CPUFUNC(op_e068_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 66;
{{	uae_s16 cnt = m68k_dreg (regs, srcreg);
{	uae_s16 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = (uae_u16)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
	if (cnt >= 16) {
		SET_CFLG ((cnt == 16) & (val >> 15));
		COPY_CARRY ();
		val = 0;
	} else if (cnt > 0) {
		val >>= cnt - 1;
		SET_CFLG (val & 1);
		COPY_CARRY ();
		val >>= 1;
	}
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}}}}	m68k_incpci (2);
return;
}

/* ROXR.W Dn,Dn */
void REGPARAM2 CPUFUNC(op_e070_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 71;
{{	uae_s16 cnt = m68k_dreg (regs, srcreg);
{	uae_s16 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = (uae_u16)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
	if (cnt >= 34) cnt -= 34;
	if (cnt >= 17) cnt -= 17;
	if (cnt > 0) {
	cnt--;
	{
	uae_u32 carry;
	uae_u32 hival = (val << 1) | GET_XFLG ();
	hival <<= (15 - cnt);
	val >>= cnt;
	carry = val & 1;
	val >>= 1;
	val |= hival;
	SET_XFLG (carry);
	val &= 0xffff;
	} }
	SET_CFLG (GET_XFLG ());
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}}}}	m68k_incpci (2);
return;
}

/* ROR.W Dn,Dn */
void REGPARAM2 CPUFUNC(op_e078_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 69;
{{	uae_s16 cnt = m68k_dreg (regs, srcreg);
{	uae_s16 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = (uae_u16)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
	if (cnt > 0) {	uae_u32 hival;
	cnt &= 15;
	hival = val << (16 - cnt);
	val >>= cnt;
	val |= hival;
	val &= 0xffff;
	SET_CFLG ((val & 0x8000) >> 15);
	}
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}}}}	m68k_incpci (2);
return;
}

/* ASRQ.L #<data>,Dn */
void REGPARAM2 CPUFUNC(op_e080_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 64;
{{	uae_u32 cnt = srcreg;
{	uae_s32 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = data;
	uae_u32 sign = (0x80000000 & val) >> 31;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
	if (cnt >= 32) {
		val = 0xffffffff & (uae_u32)-sign;
		SET_CFLG (sign);
		COPY_CARRY ();
	} else {
		val >>= cnt - 1;
		SET_CFLG (val & 1);
		COPY_CARRY ();
		val >>= 1;
		val |= (0xffffffff << (32 - cnt)) & (uae_u32)-sign;
		val &= 0xffffffff;
	}
	SET_ZFLG (((uae_s32)(val)) == 0);
	SET_NFLG (((uae_s32)(val)) < 0);
	m68k_dreg (regs, dstreg) = (val);
}}}}	m68k_incpci (2);
return;
}

/* LSRQ.L #<data>,Dn */
void REGPARAM2 CPUFUNC(op_e088_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 66;
{{	uae_u32 cnt = srcreg;
{	uae_s32 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
	if (cnt >= 32) {
		SET_CFLG ((cnt == 32) & (val >> 31));
		COPY_CARRY ();
		val = 0;
	} else {
		val >>= cnt - 1;
		SET_CFLG (val & 1);
		COPY_CARRY ();
		val >>= 1;
	}
	SET_ZFLG (((uae_s32)(val)) == 0);
	SET_NFLG (((uae_s32)(val)) < 0);
	m68k_dreg (regs, dstreg) = (val);
}}}}	m68k_incpci (2);
return;
}

/* ROXRQ.L #<data>,Dn */
void REGPARAM2 CPUFUNC(op_e090_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 71;
{{	uae_u32 cnt = srcreg;
{	uae_s32 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
{	cnt--;
	{
	uae_u32 carry;
	uae_u32 hival = (val << 1) | GET_XFLG ();
	hival <<= (31 - cnt);
	val >>= cnt;
	carry = val & 1;
	val >>= 1;
	val |= hival;
	SET_XFLG (carry);
	val &= 0xffffffff;
	} }
	SET_CFLG (GET_XFLG ());
	SET_ZFLG (((uae_s32)(val)) == 0);
	SET_NFLG (((uae_s32)(val)) < 0);
	m68k_dreg (regs, dstreg) = (val);
}}}}	m68k_incpci (2);
return;
}

/* RORQ.L #<data>,Dn */
void REGPARAM2 CPUFUNC(op_e098_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 69;
{{	uae_u32 cnt = srcreg;
{	uae_s32 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
{	uae_u32 hival;
	cnt &= 31;
	hival = val << (32 - cnt);
	val >>= cnt;
	val |= hival;
	val &= 0xffffffff;
	SET_CFLG ((val & 0x80000000) >> 31);
	}
	SET_ZFLG (((uae_s32)(val)) == 0);
	SET_NFLG (((uae_s32)(val)) < 0);
	m68k_dreg (regs, dstreg) = (val);
}}}}	m68k_incpci (2);
return;
}

/* ASR.L Dn,Dn */
void REGPARAM2 CPUFUNC(op_e0a0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 64;
{{	uae_s32 cnt = m68k_dreg (regs, srcreg);
{	uae_s32 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = data;
	uae_u32 sign = (0x80000000 & val) >> 31;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
	if (cnt >= 32) {
		val = 0xffffffff & (uae_u32)-sign;
		SET_CFLG (sign);
		COPY_CARRY ();
	} else if (cnt > 0) {
		val >>= cnt - 1;
		SET_CFLG (val & 1);
		COPY_CARRY ();
		val >>= 1;
		val |= (0xffffffff << (32 - cnt)) & (uae_u32)-sign;
		val &= 0xffffffff;
	}
	SET_ZFLG (((uae_s32)(val)) == 0);
	SET_NFLG (((uae_s32)(val)) < 0);
	m68k_dreg (regs, dstreg) = (val);
}}}}	m68k_incpci (2);
return;
}

/* LSR.L Dn,Dn */
void REGPARAM2 CPUFUNC(op_e0a8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 66;
{{	uae_s32 cnt = m68k_dreg (regs, srcreg);
{	uae_s32 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
	if (cnt >= 32) {
		SET_CFLG ((cnt == 32) & (val >> 31));
		COPY_CARRY ();
		val = 0;
	} else if (cnt > 0) {
		val >>= cnt - 1;
		SET_CFLG (val & 1);
		COPY_CARRY ();
		val >>= 1;
	}
	SET_ZFLG (((uae_s32)(val)) == 0);
	SET_NFLG (((uae_s32)(val)) < 0);
	m68k_dreg (regs, dstreg) = (val);
}}}}	m68k_incpci (2);
return;
}

/* ROXR.L Dn,Dn */
void REGPARAM2 CPUFUNC(op_e0b0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 71;
{{	uae_s32 cnt = m68k_dreg (regs, srcreg);
{	uae_s32 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
	if (cnt >= 33) cnt -= 33;
	if (cnt > 0) {
	cnt--;
	{
	uae_u32 carry;
	uae_u32 hival = (val << 1) | GET_XFLG ();
	hival <<= (31 - cnt);
	val >>= cnt;
	carry = val & 1;
	val >>= 1;
	val |= hival;
	SET_XFLG (carry);
	val &= 0xffffffff;
	} }
	SET_CFLG (GET_XFLG ());
	SET_ZFLG (((uae_s32)(val)) == 0);
	SET_NFLG (((uae_s32)(val)) < 0);
	m68k_dreg (regs, dstreg) = (val);
}}}}	m68k_incpci (2);
return;
}

/* ROR.L Dn,Dn */
void REGPARAM2 CPUFUNC(op_e0b8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 69;
{{	uae_s32 cnt = m68k_dreg (regs, srcreg);
{	uae_s32 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
	if (cnt > 0) {	uae_u32 hival;
	cnt &= 31;
	hival = val << (32 - cnt);
	val >>= cnt;
	val |= hival;
	val &= 0xffffffff;
	SET_CFLG ((val & 0x80000000) >> 31);
	}
	SET_ZFLG (((uae_s32)(val)) == 0);
	SET_NFLG (((uae_s32)(val)) < 0);
	m68k_dreg (regs, dstreg) = (val);
}}}}	m68k_incpci (2);
return;
}

/* ASRW.W (An) */
void REGPARAM2 CPUFUNC(op_e0d0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 72;
{{	uaecptr dataa;
	dataa = m68k_areg (regs, srcreg);
{	uae_s16 data = x_get_word (dataa);
{	uae_u32 val = (uae_u16)data;
	uae_u32 sign = 0x8000 & val;
	uae_u32 cflg = val & 1;
	val = (val >> 1) | sign;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (cflg);
	COPY_CARRY ();
	x_put_word (dataa, val);
}}}}	m68k_incpci (2);
return;
}

/* ASRW.W (An)+ */
void REGPARAM2 CPUFUNC(op_e0d8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 72;
{{	uaecptr dataa;
	dataa = m68k_areg (regs, srcreg);
{	uae_s16 data = x_get_word (dataa);
	m68k_areg (regs, srcreg) += 2;
{	uae_u32 val = (uae_u16)data;
	uae_u32 sign = 0x8000 & val;
	uae_u32 cflg = val & 1;
	val = (val >> 1) | sign;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (cflg);
	COPY_CARRY ();
	x_put_word (dataa, val);
}}}}	m68k_incpci (2);
return;
}

/* ASRW.W -(An) */
void REGPARAM2 CPUFUNC(op_e0e0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 72;
{{	uaecptr dataa;
	dataa = m68k_areg (regs, srcreg) - 2;
{	uae_s16 data = x_get_word (dataa);
	m68k_areg (regs, srcreg) = dataa;
{	uae_u32 val = (uae_u16)data;
	uae_u32 sign = 0x8000 & val;
	uae_u32 cflg = val & 1;
	val = (val >> 1) | sign;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (cflg);
	COPY_CARRY ();
	x_put_word (dataa, val);
}}}}	m68k_incpci (2);
return;
}

/* ASRW.W (d16,An) */
void REGPARAM2 CPUFUNC(op_e0e8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 72;
{{	uaecptr dataa;
	dataa = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 data = x_get_word (dataa);
{	uae_u32 val = (uae_u16)data;
	uae_u32 sign = 0x8000 & val;
	uae_u32 cflg = val & 1;
	val = (val >> 1) | sign;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (cflg);
	COPY_CARRY ();
	x_put_word (dataa, val);
}}}}	m68k_incpci (4);
return;
}

/* ASRW.W (d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_e0f0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 72;
{{	uaecptr dataa;
	m68k_incpci (2);
{	dataa = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s16 data = x_get_word (dataa);
{	uae_u32 val = (uae_u16)data;
	uae_u32 sign = 0x8000 & val;
	uae_u32 cflg = val & 1;
	val = (val >> 1) | sign;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (cflg);
	COPY_CARRY ();
	x_put_word (dataa, val);
}}}}}return;
}

/* ASRW.W (xxx).W */
void REGPARAM2 CPUFUNC(op_e0f8_24)(uae_u32 opcode)
{
	OpcodeFamily = 72;
{{	uaecptr dataa;
	dataa = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 data = x_get_word (dataa);
{	uae_u32 val = (uae_u16)data;
	uae_u32 sign = 0x8000 & val;
	uae_u32 cflg = val & 1;
	val = (val >> 1) | sign;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (cflg);
	COPY_CARRY ();
	x_put_word (dataa, val);
}}}}	m68k_incpci (4);
return;
}

/* ASRW.W (xxx).L */
void REGPARAM2 CPUFUNC(op_e0f9_24)(uae_u32 opcode)
{
	OpcodeFamily = 72;
{{	uaecptr dataa;
	dataa = get_ilong_cache_040 (2);
{	uae_s16 data = x_get_word (dataa);
{	uae_u32 val = (uae_u16)data;
	uae_u32 sign = 0x8000 & val;
	uae_u32 cflg = val & 1;
	val = (val >> 1) | sign;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (cflg);
	COPY_CARRY ();
	x_put_word (dataa, val);
}}}}	m68k_incpci (6);
return;
}

/* ASLQ.B #<data>,Dn */
void REGPARAM2 CPUFUNC(op_e100_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 65;
{{	uae_u32 cnt = srcreg;
{	uae_s8 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = (uae_u8)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
	if (cnt >= 8) {
		SET_VFLG (val != 0);
		SET_CFLG (cnt == 8 ? val & 1 : 0);
		COPY_CARRY ();
		val = 0;
	} else {
		uae_u32 mask = (0xff << (7 - cnt)) & 0xff;
		SET_VFLG ((val & mask) != mask && (val & mask) != 0);
		val <<= cnt - 1;
		SET_CFLG ((val & 0x80) >> 7);
		COPY_CARRY ();
		val <<= 1;
		val &= 0xff;
	}
	SET_ZFLG (((uae_s8)(val)) == 0);
	SET_NFLG (((uae_s8)(val)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpci (2);
return;
}

/* LSLQ.B #<data>,Dn */
void REGPARAM2 CPUFUNC(op_e108_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 67;
{{	uae_u32 cnt = srcreg;
{	uae_s8 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = (uae_u8)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
	if (cnt >= 8) {
		SET_CFLG (cnt == 8 ? val & 1 : 0);
		COPY_CARRY ();
		val = 0;
	} else {
		val <<= (cnt - 1);
		SET_CFLG ((val & 0x80) >> 7);
		COPY_CARRY ();
		val <<= 1;
	val &= 0xff;
	}
	SET_ZFLG (((uae_s8)(val)) == 0);
	SET_NFLG (((uae_s8)(val)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpci (2);
return;
}

/* ROXLQ.B #<data>,Dn */
void REGPARAM2 CPUFUNC(op_e110_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 70;
{{	uae_u32 cnt = srcreg;
{	uae_s8 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = (uae_u8)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
{	cnt--;
	{
	uae_u32 carry;
	uae_u32 loval = val >> (7 - cnt);
	carry = loval & 1;
	val = (((val << 1) | GET_XFLG ()) << cnt) | (loval >> 1);
	SET_XFLG (carry);
	val &= 0xff;
	} }
	SET_CFLG (GET_XFLG ());
	SET_ZFLG (((uae_s8)(val)) == 0);
	SET_NFLG (((uae_s8)(val)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpci (2);
return;
}

/* ROLQ.B #<data>,Dn */
void REGPARAM2 CPUFUNC(op_e118_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 68;
{{	uae_u32 cnt = srcreg;
{	uae_s8 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = (uae_u8)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
{	uae_u32 loval;
	cnt &= 7;
	loval = val >> (8 - cnt);
	val <<= cnt;
	val |= loval;
	val &= 0xff;
	SET_CFLG (val & 1);
}
	SET_ZFLG (((uae_s8)(val)) == 0);
	SET_NFLG (((uae_s8)(val)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpci (2);
return;
}

/* ASL.B Dn,Dn */
void REGPARAM2 CPUFUNC(op_e120_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 65;
{{	uae_s8 cnt = m68k_dreg (regs, srcreg);
{	uae_s8 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = (uae_u8)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
	if (cnt >= 8) {
		SET_VFLG (val != 0);
		SET_CFLG (cnt == 8 ? val & 1 : 0);
		COPY_CARRY ();
		val = 0;
	} else if (cnt > 0) {
		uae_u32 mask = (0xff << (7 - cnt)) & 0xff;
		SET_VFLG ((val & mask) != mask && (val & mask) != 0);
		val <<= cnt - 1;
		SET_CFLG ((val & 0x80) >> 7);
		COPY_CARRY ();
		val <<= 1;
		val &= 0xff;
	}
	SET_ZFLG (((uae_s8)(val)) == 0);
	SET_NFLG (((uae_s8)(val)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpci (2);
return;
}

/* LSL.B Dn,Dn */
void REGPARAM2 CPUFUNC(op_e128_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 67;
{{	uae_s8 cnt = m68k_dreg (regs, srcreg);
{	uae_s8 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = (uae_u8)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
	if (cnt >= 8) {
		SET_CFLG (cnt == 8 ? val & 1 : 0);
		COPY_CARRY ();
		val = 0;
	} else if (cnt > 0) {
		val <<= (cnt - 1);
		SET_CFLG ((val & 0x80) >> 7);
		COPY_CARRY ();
		val <<= 1;
	val &= 0xff;
	}
	SET_ZFLG (((uae_s8)(val)) == 0);
	SET_NFLG (((uae_s8)(val)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpci (2);
return;
}

/* ROXL.B Dn,Dn */
void REGPARAM2 CPUFUNC(op_e130_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 70;
{{	uae_s8 cnt = m68k_dreg (regs, srcreg);
{	uae_s8 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = (uae_u8)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
	if (cnt >= 36) cnt -= 36;
	if (cnt >= 18) cnt -= 18;
	if (cnt >= 9) cnt -= 9;
	if (cnt > 0) {
	cnt--;
	{
	uae_u32 carry;
	uae_u32 loval = val >> (7 - cnt);
	carry = loval & 1;
	val = (((val << 1) | GET_XFLG ()) << cnt) | (loval >> 1);
	SET_XFLG (carry);
	val &= 0xff;
	} }
	SET_CFLG (GET_XFLG ());
	SET_ZFLG (((uae_s8)(val)) == 0);
	SET_NFLG (((uae_s8)(val)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpci (2);
return;
}

/* ROL.B Dn,Dn */
void REGPARAM2 CPUFUNC(op_e138_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 68;
{{	uae_s8 cnt = m68k_dreg (regs, srcreg);
{	uae_s8 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = (uae_u8)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
	if (cnt > 0) {
	uae_u32 loval;
	cnt &= 7;
	loval = val >> (8 - cnt);
	val <<= cnt;
	val |= loval;
	val &= 0xff;
	SET_CFLG (val & 1);
}
	SET_ZFLG (((uae_s8)(val)) == 0);
	SET_NFLG (((uae_s8)(val)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpci (2);
return;
}

/* ASLQ.W #<data>,Dn */
void REGPARAM2 CPUFUNC(op_e140_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 65;
{{	uae_u32 cnt = srcreg;
{	uae_s16 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = (uae_u16)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
	if (cnt >= 16) {
		SET_VFLG (val != 0);
		SET_CFLG (cnt == 16 ? val & 1 : 0);
		COPY_CARRY ();
		val = 0;
	} else {
		uae_u32 mask = (0xffff << (15 - cnt)) & 0xffff;
		SET_VFLG ((val & mask) != mask && (val & mask) != 0);
		val <<= cnt - 1;
		SET_CFLG ((val & 0x8000) >> 15);
		COPY_CARRY ();
		val <<= 1;
		val &= 0xffff;
	}
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}}}}	m68k_incpci (2);
return;
}

/* LSLQ.W #<data>,Dn */
void REGPARAM2 CPUFUNC(op_e148_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 67;
{{	uae_u32 cnt = srcreg;
{	uae_s16 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = (uae_u16)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
	if (cnt >= 16) {
		SET_CFLG (cnt == 16 ? val & 1 : 0);
		COPY_CARRY ();
		val = 0;
	} else {
		val <<= (cnt - 1);
		SET_CFLG ((val & 0x8000) >> 15);
		COPY_CARRY ();
		val <<= 1;
	val &= 0xffff;
	}
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}}}}	m68k_incpci (2);
return;
}

/* ROXLQ.W #<data>,Dn */
void REGPARAM2 CPUFUNC(op_e150_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 70;
{{	uae_u32 cnt = srcreg;
{	uae_s16 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = (uae_u16)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
{	cnt--;
	{
	uae_u32 carry;
	uae_u32 loval = val >> (15 - cnt);
	carry = loval & 1;
	val = (((val << 1) | GET_XFLG ()) << cnt) | (loval >> 1);
	SET_XFLG (carry);
	val &= 0xffff;
	} }
	SET_CFLG (GET_XFLG ());
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}}}}	m68k_incpci (2);
return;
}

/* ROLQ.W #<data>,Dn */
void REGPARAM2 CPUFUNC(op_e158_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 68;
{{	uae_u32 cnt = srcreg;
{	uae_s16 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = (uae_u16)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
{	uae_u32 loval;
	cnt &= 15;
	loval = val >> (16 - cnt);
	val <<= cnt;
	val |= loval;
	val &= 0xffff;
	SET_CFLG (val & 1);
}
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}}}}	m68k_incpci (2);
return;
}

/* ASL.W Dn,Dn */
void REGPARAM2 CPUFUNC(op_e160_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 65;
{{	uae_s16 cnt = m68k_dreg (regs, srcreg);
{	uae_s16 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = (uae_u16)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
	if (cnt >= 16) {
		SET_VFLG (val != 0);
		SET_CFLG (cnt == 16 ? val & 1 : 0);
		COPY_CARRY ();
		val = 0;
	} else if (cnt > 0) {
		uae_u32 mask = (0xffff << (15 - cnt)) & 0xffff;
		SET_VFLG ((val & mask) != mask && (val & mask) != 0);
		val <<= cnt - 1;
		SET_CFLG ((val & 0x8000) >> 15);
		COPY_CARRY ();
		val <<= 1;
		val &= 0xffff;
	}
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}}}}	m68k_incpci (2);
return;
}

/* LSL.W Dn,Dn */
void REGPARAM2 CPUFUNC(op_e168_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 67;
{{	uae_s16 cnt = m68k_dreg (regs, srcreg);
{	uae_s16 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = (uae_u16)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
	if (cnt >= 16) {
		SET_CFLG (cnt == 16 ? val & 1 : 0);
		COPY_CARRY ();
		val = 0;
	} else if (cnt > 0) {
		val <<= (cnt - 1);
		SET_CFLG ((val & 0x8000) >> 15);
		COPY_CARRY ();
		val <<= 1;
	val &= 0xffff;
	}
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}}}}	m68k_incpci (2);
return;
}

/* ROXL.W Dn,Dn */
void REGPARAM2 CPUFUNC(op_e170_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 70;
{{	uae_s16 cnt = m68k_dreg (regs, srcreg);
{	uae_s16 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = (uae_u16)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
	if (cnt >= 34) cnt -= 34;
	if (cnt >= 17) cnt -= 17;
	if (cnt > 0) {
	cnt--;
	{
	uae_u32 carry;
	uae_u32 loval = val >> (15 - cnt);
	carry = loval & 1;
	val = (((val << 1) | GET_XFLG ()) << cnt) | (loval >> 1);
	SET_XFLG (carry);
	val &= 0xffff;
	} }
	SET_CFLG (GET_XFLG ());
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}}}}	m68k_incpci (2);
return;
}

/* ROL.W Dn,Dn */
void REGPARAM2 CPUFUNC(op_e178_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 68;
{{	uae_s16 cnt = m68k_dreg (regs, srcreg);
{	uae_s16 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = (uae_u16)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
	if (cnt > 0) {
	uae_u32 loval;
	cnt &= 15;
	loval = val >> (16 - cnt);
	val <<= cnt;
	val |= loval;
	val &= 0xffff;
	SET_CFLG (val & 1);
}
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}}}}	m68k_incpci (2);
return;
}

/* ASLQ.L #<data>,Dn */
void REGPARAM2 CPUFUNC(op_e180_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 65;
{{	uae_u32 cnt = srcreg;
{	uae_s32 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
	if (cnt >= 32) {
		SET_VFLG (val != 0);
		SET_CFLG (cnt == 32 ? val & 1 : 0);
		COPY_CARRY ();
		val = 0;
	} else {
		uae_u32 mask = (0xffffffff << (31 - cnt)) & 0xffffffff;
		SET_VFLG ((val & mask) != mask && (val & mask) != 0);
		val <<= cnt - 1;
		SET_CFLG ((val & 0x80000000) >> 31);
		COPY_CARRY ();
		val <<= 1;
		val &= 0xffffffff;
	}
	SET_ZFLG (((uae_s32)(val)) == 0);
	SET_NFLG (((uae_s32)(val)) < 0);
	m68k_dreg (regs, dstreg) = (val);
}}}}	m68k_incpci (2);
return;
}

/* LSLQ.L #<data>,Dn */
void REGPARAM2 CPUFUNC(op_e188_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 67;
{{	uae_u32 cnt = srcreg;
{	uae_s32 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
	if (cnt >= 32) {
		SET_CFLG (cnt == 32 ? val & 1 : 0);
		COPY_CARRY ();
		val = 0;
	} else {
		val <<= (cnt - 1);
		SET_CFLG ((val & 0x80000000) >> 31);
		COPY_CARRY ();
		val <<= 1;
	val &= 0xffffffff;
	}
	SET_ZFLG (((uae_s32)(val)) == 0);
	SET_NFLG (((uae_s32)(val)) < 0);
	m68k_dreg (regs, dstreg) = (val);
}}}}	m68k_incpci (2);
return;
}

/* ROXLQ.L #<data>,Dn */
void REGPARAM2 CPUFUNC(op_e190_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 70;
{{	uae_u32 cnt = srcreg;
{	uae_s32 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
{	cnt--;
	{
	uae_u32 carry;
	uae_u32 loval = val >> (31 - cnt);
	carry = loval & 1;
	val = (((val << 1) | GET_XFLG ()) << cnt) | (loval >> 1);
	SET_XFLG (carry);
	val &= 0xffffffff;
	} }
	SET_CFLG (GET_XFLG ());
	SET_ZFLG (((uae_s32)(val)) == 0);
	SET_NFLG (((uae_s32)(val)) < 0);
	m68k_dreg (regs, dstreg) = (val);
}}}}	m68k_incpci (2);
return;
}

/* ROLQ.L #<data>,Dn */
void REGPARAM2 CPUFUNC(op_e198_24)(uae_u32 opcode)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 68;
{{	uae_u32 cnt = srcreg;
{	uae_s32 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
{	uae_u32 loval;
	cnt &= 31;
	loval = val >> (32 - cnt);
	val <<= cnt;
	val |= loval;
	val &= 0xffffffff;
	SET_CFLG (val & 1);
}
	SET_ZFLG (((uae_s32)(val)) == 0);
	SET_NFLG (((uae_s32)(val)) < 0);
	m68k_dreg (regs, dstreg) = (val);
}}}}	m68k_incpci (2);
return;
}

/* ASL.L Dn,Dn */
void REGPARAM2 CPUFUNC(op_e1a0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 65;
{{	uae_s32 cnt = m68k_dreg (regs, srcreg);
{	uae_s32 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
	if (cnt >= 32) {
		SET_VFLG (val != 0);
		SET_CFLG (cnt == 32 ? val & 1 : 0);
		COPY_CARRY ();
		val = 0;
	} else if (cnt > 0) {
		uae_u32 mask = (0xffffffff << (31 - cnt)) & 0xffffffff;
		SET_VFLG ((val & mask) != mask && (val & mask) != 0);
		val <<= cnt - 1;
		SET_CFLG ((val & 0x80000000) >> 31);
		COPY_CARRY ();
		val <<= 1;
		val &= 0xffffffff;
	}
	SET_ZFLG (((uae_s32)(val)) == 0);
	SET_NFLG (((uae_s32)(val)) < 0);
	m68k_dreg (regs, dstreg) = (val);
}}}}	m68k_incpci (2);
return;
}

/* LSL.L Dn,Dn */
void REGPARAM2 CPUFUNC(op_e1a8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 67;
{{	uae_s32 cnt = m68k_dreg (regs, srcreg);
{	uae_s32 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
	if (cnt >= 32) {
		SET_CFLG (cnt == 32 ? val & 1 : 0);
		COPY_CARRY ();
		val = 0;
	} else if (cnt > 0) {
		val <<= (cnt - 1);
		SET_CFLG ((val & 0x80000000) >> 31);
		COPY_CARRY ();
		val <<= 1;
	val &= 0xffffffff;
	}
	SET_ZFLG (((uae_s32)(val)) == 0);
	SET_NFLG (((uae_s32)(val)) < 0);
	m68k_dreg (regs, dstreg) = (val);
}}}}	m68k_incpci (2);
return;
}

/* ROXL.L Dn,Dn */
void REGPARAM2 CPUFUNC(op_e1b0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 70;
{{	uae_s32 cnt = m68k_dreg (regs, srcreg);
{	uae_s32 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
	if (cnt >= 33) cnt -= 33;
	if (cnt > 0) {
	cnt--;
	{
	uae_u32 carry;
	uae_u32 loval = val >> (31 - cnt);
	carry = loval & 1;
	val = (((val << 1) | GET_XFLG ()) << cnt) | (loval >> 1);
	SET_XFLG (carry);
	val &= 0xffffffff;
	} }
	SET_CFLG (GET_XFLG ());
	SET_ZFLG (((uae_s32)(val)) == 0);
	SET_NFLG (((uae_s32)(val)) < 0);
	m68k_dreg (regs, dstreg) = (val);
}}}}	m68k_incpci (2);
return;
}

/* ROL.L Dn,Dn */
void REGPARAM2 CPUFUNC(op_e1b8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 68;
{{	uae_s32 cnt = m68k_dreg (regs, srcreg);
{	uae_s32 data = m68k_dreg (regs, dstreg);
{	uae_u32 val = data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV ();
	if (cnt > 0) {
	uae_u32 loval;
	cnt &= 31;
	loval = val >> (32 - cnt);
	val <<= cnt;
	val |= loval;
	val &= 0xffffffff;
	SET_CFLG (val & 1);
}
	SET_ZFLG (((uae_s32)(val)) == 0);
	SET_NFLG (((uae_s32)(val)) < 0);
	m68k_dreg (regs, dstreg) = (val);
}}}}	m68k_incpci (2);
return;
}

/* ASLW.W (An) */
void REGPARAM2 CPUFUNC(op_e1d0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 73;
{{	uaecptr dataa;
	dataa = m68k_areg (regs, srcreg);
{	uae_s16 data = x_get_word (dataa);
{	uae_u32 val = (uae_u16)data;
	uae_u32 sign = 0x8000 & val;
	uae_u32 sign2;
	val <<= 1;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	sign2 = 0x8000 & val;
	SET_CFLG (sign != 0);
	COPY_CARRY ();
	SET_VFLG (GET_VFLG () | (sign2 != sign));
	x_put_word (dataa, val);
}}}}	m68k_incpci (2);
return;
}

/* ASLW.W (An)+ */
void REGPARAM2 CPUFUNC(op_e1d8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 73;
{{	uaecptr dataa;
	dataa = m68k_areg (regs, srcreg);
{	uae_s16 data = x_get_word (dataa);
	m68k_areg (regs, srcreg) += 2;
{	uae_u32 val = (uae_u16)data;
	uae_u32 sign = 0x8000 & val;
	uae_u32 sign2;
	val <<= 1;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	sign2 = 0x8000 & val;
	SET_CFLG (sign != 0);
	COPY_CARRY ();
	SET_VFLG (GET_VFLG () | (sign2 != sign));
	x_put_word (dataa, val);
}}}}	m68k_incpci (2);
return;
}

/* ASLW.W -(An) */
void REGPARAM2 CPUFUNC(op_e1e0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 73;
{{	uaecptr dataa;
	dataa = m68k_areg (regs, srcreg) - 2;
{	uae_s16 data = x_get_word (dataa);
	m68k_areg (regs, srcreg) = dataa;
{	uae_u32 val = (uae_u16)data;
	uae_u32 sign = 0x8000 & val;
	uae_u32 sign2;
	val <<= 1;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	sign2 = 0x8000 & val;
	SET_CFLG (sign != 0);
	COPY_CARRY ();
	SET_VFLG (GET_VFLG () | (sign2 != sign));
	x_put_word (dataa, val);
}}}}	m68k_incpci (2);
return;
}

/* ASLW.W (d16,An) */
void REGPARAM2 CPUFUNC(op_e1e8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 73;
{{	uaecptr dataa;
	dataa = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 data = x_get_word (dataa);
{	uae_u32 val = (uae_u16)data;
	uae_u32 sign = 0x8000 & val;
	uae_u32 sign2;
	val <<= 1;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	sign2 = 0x8000 & val;
	SET_CFLG (sign != 0);
	COPY_CARRY ();
	SET_VFLG (GET_VFLG () | (sign2 != sign));
	x_put_word (dataa, val);
}}}}	m68k_incpci (4);
return;
}

/* ASLW.W (d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_e1f0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 73;
{{	uaecptr dataa;
	m68k_incpci (2);
{	dataa = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s16 data = x_get_word (dataa);
{	uae_u32 val = (uae_u16)data;
	uae_u32 sign = 0x8000 & val;
	uae_u32 sign2;
	val <<= 1;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	sign2 = 0x8000 & val;
	SET_CFLG (sign != 0);
	COPY_CARRY ();
	SET_VFLG (GET_VFLG () | (sign2 != sign));
	x_put_word (dataa, val);
}}}}}return;
}

/* ASLW.W (xxx).W */
void REGPARAM2 CPUFUNC(op_e1f8_24)(uae_u32 opcode)
{
	OpcodeFamily = 73;
{{	uaecptr dataa;
	dataa = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 data = x_get_word (dataa);
{	uae_u32 val = (uae_u16)data;
	uae_u32 sign = 0x8000 & val;
	uae_u32 sign2;
	val <<= 1;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	sign2 = 0x8000 & val;
	SET_CFLG (sign != 0);
	COPY_CARRY ();
	SET_VFLG (GET_VFLG () | (sign2 != sign));
	x_put_word (dataa, val);
}}}}	m68k_incpci (4);
return;
}

/* ASLW.W (xxx).L */
void REGPARAM2 CPUFUNC(op_e1f9_24)(uae_u32 opcode)
{
	OpcodeFamily = 73;
{{	uaecptr dataa;
	dataa = get_ilong_cache_040 (2);
{	uae_s16 data = x_get_word (dataa);
{	uae_u32 val = (uae_u16)data;
	uae_u32 sign = 0x8000 & val;
	uae_u32 sign2;
	val <<= 1;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	sign2 = 0x8000 & val;
	SET_CFLG (sign != 0);
	COPY_CARRY ();
	SET_VFLG (GET_VFLG () | (sign2 != sign));
	x_put_word (dataa, val);
}}}}	m68k_incpci (6);
return;
}

/* LSRW.W (An) */
void REGPARAM2 CPUFUNC(op_e2d0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 74;
{{	uaecptr dataa;
	dataa = m68k_areg (regs, srcreg);
{	uae_s16 data = x_get_word (dataa);
{	uae_u32 val = (uae_u16)data;
	uae_u32 carry = val & 1;
	val >>= 1;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (carry);
	COPY_CARRY ();
	x_put_word (dataa, val);
}}}}	m68k_incpci (2);
return;
}

/* LSRW.W (An)+ */
void REGPARAM2 CPUFUNC(op_e2d8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 74;
{{	uaecptr dataa;
	dataa = m68k_areg (regs, srcreg);
{	uae_s16 data = x_get_word (dataa);
	m68k_areg (regs, srcreg) += 2;
{	uae_u32 val = (uae_u16)data;
	uae_u32 carry = val & 1;
	val >>= 1;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (carry);
	COPY_CARRY ();
	x_put_word (dataa, val);
}}}}	m68k_incpci (2);
return;
}

/* LSRW.W -(An) */
void REGPARAM2 CPUFUNC(op_e2e0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 74;
{{	uaecptr dataa;
	dataa = m68k_areg (regs, srcreg) - 2;
{	uae_s16 data = x_get_word (dataa);
	m68k_areg (regs, srcreg) = dataa;
{	uae_u32 val = (uae_u16)data;
	uae_u32 carry = val & 1;
	val >>= 1;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (carry);
	COPY_CARRY ();
	x_put_word (dataa, val);
}}}}	m68k_incpci (2);
return;
}

/* LSRW.W (d16,An) */
void REGPARAM2 CPUFUNC(op_e2e8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 74;
{{	uaecptr dataa;
	dataa = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 data = x_get_word (dataa);
{	uae_u32 val = (uae_u16)data;
	uae_u32 carry = val & 1;
	val >>= 1;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (carry);
	COPY_CARRY ();
	x_put_word (dataa, val);
}}}}	m68k_incpci (4);
return;
}

/* LSRW.W (d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_e2f0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 74;
{{	uaecptr dataa;
	m68k_incpci (2);
{	dataa = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s16 data = x_get_word (dataa);
{	uae_u32 val = (uae_u16)data;
	uae_u32 carry = val & 1;
	val >>= 1;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (carry);
	COPY_CARRY ();
	x_put_word (dataa, val);
}}}}}return;
}

/* LSRW.W (xxx).W */
void REGPARAM2 CPUFUNC(op_e2f8_24)(uae_u32 opcode)
{
	OpcodeFamily = 74;
{{	uaecptr dataa;
	dataa = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 data = x_get_word (dataa);
{	uae_u32 val = (uae_u16)data;
	uae_u32 carry = val & 1;
	val >>= 1;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (carry);
	COPY_CARRY ();
	x_put_word (dataa, val);
}}}}	m68k_incpci (4);
return;
}

/* LSRW.W (xxx).L */
void REGPARAM2 CPUFUNC(op_e2f9_24)(uae_u32 opcode)
{
	OpcodeFamily = 74;
{{	uaecptr dataa;
	dataa = get_ilong_cache_040 (2);
{	uae_s16 data = x_get_word (dataa);
{	uae_u32 val = (uae_u16)data;
	uae_u32 carry = val & 1;
	val >>= 1;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (carry);
	COPY_CARRY ();
	x_put_word (dataa, val);
}}}}	m68k_incpci (6);
return;
}

/* LSLW.W (An) */
void REGPARAM2 CPUFUNC(op_e3d0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 75;
{{	uaecptr dataa;
	dataa = m68k_areg (regs, srcreg);
{	uae_s16 data = x_get_word (dataa);
{	uae_u16 val = data;
	uae_u32 carry = val & 0x8000;
	val <<= 1;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (carry >> 15);
	COPY_CARRY ();
	x_put_word (dataa, val);
}}}}	m68k_incpci (2);
return;
}

/* LSLW.W (An)+ */
void REGPARAM2 CPUFUNC(op_e3d8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 75;
{{	uaecptr dataa;
	dataa = m68k_areg (regs, srcreg);
{	uae_s16 data = x_get_word (dataa);
	m68k_areg (regs, srcreg) += 2;
{	uae_u16 val = data;
	uae_u32 carry = val & 0x8000;
	val <<= 1;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (carry >> 15);
	COPY_CARRY ();
	x_put_word (dataa, val);
}}}}	m68k_incpci (2);
return;
}

/* LSLW.W -(An) */
void REGPARAM2 CPUFUNC(op_e3e0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 75;
{{	uaecptr dataa;
	dataa = m68k_areg (regs, srcreg) - 2;
{	uae_s16 data = x_get_word (dataa);
	m68k_areg (regs, srcreg) = dataa;
{	uae_u16 val = data;
	uae_u32 carry = val & 0x8000;
	val <<= 1;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (carry >> 15);
	COPY_CARRY ();
	x_put_word (dataa, val);
}}}}	m68k_incpci (2);
return;
}

/* LSLW.W (d16,An) */
void REGPARAM2 CPUFUNC(op_e3e8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 75;
{{	uaecptr dataa;
	dataa = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 data = x_get_word (dataa);
{	uae_u16 val = data;
	uae_u32 carry = val & 0x8000;
	val <<= 1;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (carry >> 15);
	COPY_CARRY ();
	x_put_word (dataa, val);
}}}}	m68k_incpci (4);
return;
}

/* LSLW.W (d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_e3f0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 75;
{{	uaecptr dataa;
	m68k_incpci (2);
{	dataa = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s16 data = x_get_word (dataa);
{	uae_u16 val = data;
	uae_u32 carry = val & 0x8000;
	val <<= 1;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (carry >> 15);
	COPY_CARRY ();
	x_put_word (dataa, val);
}}}}}return;
}

/* LSLW.W (xxx).W */
void REGPARAM2 CPUFUNC(op_e3f8_24)(uae_u32 opcode)
{
	OpcodeFamily = 75;
{{	uaecptr dataa;
	dataa = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 data = x_get_word (dataa);
{	uae_u16 val = data;
	uae_u32 carry = val & 0x8000;
	val <<= 1;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (carry >> 15);
	COPY_CARRY ();
	x_put_word (dataa, val);
}}}}	m68k_incpci (4);
return;
}

/* LSLW.W (xxx).L */
void REGPARAM2 CPUFUNC(op_e3f9_24)(uae_u32 opcode)
{
	OpcodeFamily = 75;
{{	uaecptr dataa;
	dataa = get_ilong_cache_040 (2);
{	uae_s16 data = x_get_word (dataa);
{	uae_u16 val = data;
	uae_u32 carry = val & 0x8000;
	val <<= 1;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (carry >> 15);
	COPY_CARRY ();
	x_put_word (dataa, val);
}}}}	m68k_incpci (6);
return;
}

/* ROXRW.W (An) */
void REGPARAM2 CPUFUNC(op_e4d0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 79;
{{	uaecptr dataa;
	dataa = m68k_areg (regs, srcreg);
{	uae_s16 data = x_get_word (dataa);
{	uae_u16 val = data;
	uae_u32 carry = val & 1;
	val >>= 1;
	if (GET_XFLG ()) val |= 0x8000;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (carry);
	COPY_CARRY ();
	x_put_word (dataa, val);
}}}}	m68k_incpci (2);
return;
}

/* ROXRW.W (An)+ */
void REGPARAM2 CPUFUNC(op_e4d8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 79;
{{	uaecptr dataa;
	dataa = m68k_areg (regs, srcreg);
{	uae_s16 data = x_get_word (dataa);
	m68k_areg (regs, srcreg) += 2;
{	uae_u16 val = data;
	uae_u32 carry = val & 1;
	val >>= 1;
	if (GET_XFLG ()) val |= 0x8000;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (carry);
	COPY_CARRY ();
	x_put_word (dataa, val);
}}}}	m68k_incpci (2);
return;
}

/* ROXRW.W -(An) */
void REGPARAM2 CPUFUNC(op_e4e0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 79;
{{	uaecptr dataa;
	dataa = m68k_areg (regs, srcreg) - 2;
{	uae_s16 data = x_get_word (dataa);
	m68k_areg (regs, srcreg) = dataa;
{	uae_u16 val = data;
	uae_u32 carry = val & 1;
	val >>= 1;
	if (GET_XFLG ()) val |= 0x8000;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (carry);
	COPY_CARRY ();
	x_put_word (dataa, val);
}}}}	m68k_incpci (2);
return;
}

/* ROXRW.W (d16,An) */
void REGPARAM2 CPUFUNC(op_e4e8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 79;
{{	uaecptr dataa;
	dataa = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 data = x_get_word (dataa);
{	uae_u16 val = data;
	uae_u32 carry = val & 1;
	val >>= 1;
	if (GET_XFLG ()) val |= 0x8000;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (carry);
	COPY_CARRY ();
	x_put_word (dataa, val);
}}}}	m68k_incpci (4);
return;
}

/* ROXRW.W (d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_e4f0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 79;
{{	uaecptr dataa;
	m68k_incpci (2);
{	dataa = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s16 data = x_get_word (dataa);
{	uae_u16 val = data;
	uae_u32 carry = val & 1;
	val >>= 1;
	if (GET_XFLG ()) val |= 0x8000;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (carry);
	COPY_CARRY ();
	x_put_word (dataa, val);
}}}}}return;
}

/* ROXRW.W (xxx).W */
void REGPARAM2 CPUFUNC(op_e4f8_24)(uae_u32 opcode)
{
	OpcodeFamily = 79;
{{	uaecptr dataa;
	dataa = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 data = x_get_word (dataa);
{	uae_u16 val = data;
	uae_u32 carry = val & 1;
	val >>= 1;
	if (GET_XFLG ()) val |= 0x8000;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (carry);
	COPY_CARRY ();
	x_put_word (dataa, val);
}}}}	m68k_incpci (4);
return;
}

/* ROXRW.W (xxx).L */
void REGPARAM2 CPUFUNC(op_e4f9_24)(uae_u32 opcode)
{
	OpcodeFamily = 79;
{{	uaecptr dataa;
	dataa = get_ilong_cache_040 (2);
{	uae_s16 data = x_get_word (dataa);
{	uae_u16 val = data;
	uae_u32 carry = val & 1;
	val >>= 1;
	if (GET_XFLG ()) val |= 0x8000;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (carry);
	COPY_CARRY ();
	x_put_word (dataa, val);
}}}}	m68k_incpci (6);
return;
}

/* ROXLW.W (An) */
void REGPARAM2 CPUFUNC(op_e5d0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 78;
{{	uaecptr dataa;
	dataa = m68k_areg (regs, srcreg);
{	uae_s16 data = x_get_word (dataa);
{	uae_u16 val = data;
	uae_u32 carry = val & 0x8000;
	val <<= 1;
	if (GET_XFLG ()) val |= 1;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (carry >> 15);
	COPY_CARRY ();
	x_put_word (dataa, val);
}}}}	m68k_incpci (2);
return;
}

/* ROXLW.W (An)+ */
void REGPARAM2 CPUFUNC(op_e5d8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 78;
{{	uaecptr dataa;
	dataa = m68k_areg (regs, srcreg);
{	uae_s16 data = x_get_word (dataa);
	m68k_areg (regs, srcreg) += 2;
{	uae_u16 val = data;
	uae_u32 carry = val & 0x8000;
	val <<= 1;
	if (GET_XFLG ()) val |= 1;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (carry >> 15);
	COPY_CARRY ();
	x_put_word (dataa, val);
}}}}	m68k_incpci (2);
return;
}

/* ROXLW.W -(An) */
void REGPARAM2 CPUFUNC(op_e5e0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 78;
{{	uaecptr dataa;
	dataa = m68k_areg (regs, srcreg) - 2;
{	uae_s16 data = x_get_word (dataa);
	m68k_areg (regs, srcreg) = dataa;
{	uae_u16 val = data;
	uae_u32 carry = val & 0x8000;
	val <<= 1;
	if (GET_XFLG ()) val |= 1;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (carry >> 15);
	COPY_CARRY ();
	x_put_word (dataa, val);
}}}}	m68k_incpci (2);
return;
}

/* ROXLW.W (d16,An) */
void REGPARAM2 CPUFUNC(op_e5e8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 78;
{{	uaecptr dataa;
	dataa = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 data = x_get_word (dataa);
{	uae_u16 val = data;
	uae_u32 carry = val & 0x8000;
	val <<= 1;
	if (GET_XFLG ()) val |= 1;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (carry >> 15);
	COPY_CARRY ();
	x_put_word (dataa, val);
}}}}	m68k_incpci (4);
return;
}

/* ROXLW.W (d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_e5f0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 78;
{{	uaecptr dataa;
	m68k_incpci (2);
{	dataa = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s16 data = x_get_word (dataa);
{	uae_u16 val = data;
	uae_u32 carry = val & 0x8000;
	val <<= 1;
	if (GET_XFLG ()) val |= 1;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (carry >> 15);
	COPY_CARRY ();
	x_put_word (dataa, val);
}}}}}return;
}

/* ROXLW.W (xxx).W */
void REGPARAM2 CPUFUNC(op_e5f8_24)(uae_u32 opcode)
{
	OpcodeFamily = 78;
{{	uaecptr dataa;
	dataa = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 data = x_get_word (dataa);
{	uae_u16 val = data;
	uae_u32 carry = val & 0x8000;
	val <<= 1;
	if (GET_XFLG ()) val |= 1;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (carry >> 15);
	COPY_CARRY ();
	x_put_word (dataa, val);
}}}}	m68k_incpci (4);
return;
}

/* ROXLW.W (xxx).L */
void REGPARAM2 CPUFUNC(op_e5f9_24)(uae_u32 opcode)
{
	OpcodeFamily = 78;
{{	uaecptr dataa;
	dataa = get_ilong_cache_040 (2);
{	uae_s16 data = x_get_word (dataa);
{	uae_u16 val = data;
	uae_u32 carry = val & 0x8000;
	val <<= 1;
	if (GET_XFLG ()) val |= 1;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (carry >> 15);
	COPY_CARRY ();
	x_put_word (dataa, val);
}}}}	m68k_incpci (6);
return;
}

/* RORW.W (An) */
void REGPARAM2 CPUFUNC(op_e6d0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 77;
{{	uaecptr dataa;
	dataa = m68k_areg (regs, srcreg);
{	uae_s16 data = x_get_word (dataa);
{	uae_u16 val = data;
	uae_u32 carry = val & 1;
	val >>= 1;
	if (carry) val |= 0x8000;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (carry);
	x_put_word (dataa, val);
}}}}	m68k_incpci (2);
return;
}

/* RORW.W (An)+ */
void REGPARAM2 CPUFUNC(op_e6d8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 77;
{{	uaecptr dataa;
	dataa = m68k_areg (regs, srcreg);
{	uae_s16 data = x_get_word (dataa);
	m68k_areg (regs, srcreg) += 2;
{	uae_u16 val = data;
	uae_u32 carry = val & 1;
	val >>= 1;
	if (carry) val |= 0x8000;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (carry);
	x_put_word (dataa, val);
}}}}	m68k_incpci (2);
return;
}

/* RORW.W -(An) */
void REGPARAM2 CPUFUNC(op_e6e0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 77;
{{	uaecptr dataa;
	dataa = m68k_areg (regs, srcreg) - 2;
{	uae_s16 data = x_get_word (dataa);
	m68k_areg (regs, srcreg) = dataa;
{	uae_u16 val = data;
	uae_u32 carry = val & 1;
	val >>= 1;
	if (carry) val |= 0x8000;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (carry);
	x_put_word (dataa, val);
}}}}	m68k_incpci (2);
return;
}

/* RORW.W (d16,An) */
void REGPARAM2 CPUFUNC(op_e6e8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 77;
{{	uaecptr dataa;
	dataa = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 data = x_get_word (dataa);
{	uae_u16 val = data;
	uae_u32 carry = val & 1;
	val >>= 1;
	if (carry) val |= 0x8000;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (carry);
	x_put_word (dataa, val);
}}}}	m68k_incpci (4);
return;
}

/* RORW.W (d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_e6f0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 77;
{{	uaecptr dataa;
	m68k_incpci (2);
{	dataa = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s16 data = x_get_word (dataa);
{	uae_u16 val = data;
	uae_u32 carry = val & 1;
	val >>= 1;
	if (carry) val |= 0x8000;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (carry);
	x_put_word (dataa, val);
}}}}}return;
}

/* RORW.W (xxx).W */
void REGPARAM2 CPUFUNC(op_e6f8_24)(uae_u32 opcode)
{
	OpcodeFamily = 77;
{{	uaecptr dataa;
	dataa = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 data = x_get_word (dataa);
{	uae_u16 val = data;
	uae_u32 carry = val & 1;
	val >>= 1;
	if (carry) val |= 0x8000;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (carry);
	x_put_word (dataa, val);
}}}}	m68k_incpci (4);
return;
}

/* RORW.W (xxx).L */
void REGPARAM2 CPUFUNC(op_e6f9_24)(uae_u32 opcode)
{
	OpcodeFamily = 77;
{{	uaecptr dataa;
	dataa = get_ilong_cache_040 (2);
{	uae_s16 data = x_get_word (dataa);
{	uae_u16 val = data;
	uae_u32 carry = val & 1;
	val >>= 1;
	if (carry) val |= 0x8000;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (carry);
	x_put_word (dataa, val);
}}}}	m68k_incpci (6);
return;
}

/* ROLW.W (An) */
void REGPARAM2 CPUFUNC(op_e7d0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 76;
{{	uaecptr dataa;
	dataa = m68k_areg (regs, srcreg);
{	uae_s16 data = x_get_word (dataa);
{	uae_u16 val = data;
	uae_u32 carry = val & 0x8000;
	val <<= 1;
	if (carry)  val |= 1;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (carry >> 15);
	x_put_word (dataa, val);
}}}}	m68k_incpci (2);
return;
}

/* ROLW.W (An)+ */
void REGPARAM2 CPUFUNC(op_e7d8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 76;
{{	uaecptr dataa;
	dataa = m68k_areg (regs, srcreg);
{	uae_s16 data = x_get_word (dataa);
	m68k_areg (regs, srcreg) += 2;
{	uae_u16 val = data;
	uae_u32 carry = val & 0x8000;
	val <<= 1;
	if (carry)  val |= 1;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (carry >> 15);
	x_put_word (dataa, val);
}}}}	m68k_incpci (2);
return;
}

/* ROLW.W -(An) */
void REGPARAM2 CPUFUNC(op_e7e0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 76;
{{	uaecptr dataa;
	dataa = m68k_areg (regs, srcreg) - 2;
{	uae_s16 data = x_get_word (dataa);
	m68k_areg (regs, srcreg) = dataa;
{	uae_u16 val = data;
	uae_u32 carry = val & 0x8000;
	val <<= 1;
	if (carry)  val |= 1;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (carry >> 15);
	x_put_word (dataa, val);
}}}}	m68k_incpci (2);
return;
}

/* ROLW.W (d16,An) */
void REGPARAM2 CPUFUNC(op_e7e8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 76;
{{	uaecptr dataa;
	dataa = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 data = x_get_word (dataa);
{	uae_u16 val = data;
	uae_u32 carry = val & 0x8000;
	val <<= 1;
	if (carry)  val |= 1;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (carry >> 15);
	x_put_word (dataa, val);
}}}}	m68k_incpci (4);
return;
}

/* ROLW.W (d8,An,Xn) */
void REGPARAM2 CPUFUNC(op_e7f0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 76;
{{	uaecptr dataa;
	m68k_incpci (2);
{	dataa = x_get_disp_ea_040 (m68k_areg (regs, srcreg), 0);
{	uae_s16 data = x_get_word (dataa);
{	uae_u16 val = data;
	uae_u32 carry = val & 0x8000;
	val <<= 1;
	if (carry)  val |= 1;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (carry >> 15);
	x_put_word (dataa, val);
}}}}}return;
}

/* ROLW.W (xxx).W */
void REGPARAM2 CPUFUNC(op_e7f8_24)(uae_u32 opcode)
{
	OpcodeFamily = 76;
{{	uaecptr dataa;
	dataa = (uae_s32)(uae_s16)get_iword_cache_040 (2);
{	uae_s16 data = x_get_word (dataa);
{	uae_u16 val = data;
	uae_u32 carry = val & 0x8000;
	val <<= 1;
	if (carry)  val |= 1;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (carry >> 15);
	x_put_word (dataa, val);
}}}}	m68k_incpci (4);
return;
}

/* ROLW.W (xxx).L */
void REGPARAM2 CPUFUNC(op_e7f9_24)(uae_u32 opcode)
{
	OpcodeFamily = 76;
{{	uaecptr dataa;
	dataa = get_ilong_cache_040 (2);
{	uae_s16 data = x_get_word (dataa);
{	uae_u16 val = data;
	uae_u32 carry = val & 0x8000;
	val <<= 1;
	if (carry)  val |= 1;
	CLEAR_CZNV ();
	SET_ZFLG (((uae_s16)(val)) == 0);
	SET_NFLG (((uae_s16)(val)) < 0);
	SET_CFLG (carry >> 15);
	x_put_word (dataa, val);
}}}}	m68k_incpci (6);
return;
}

/* BFTST.L #<data>.W,Dn */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_e8c0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 88;
{{	uae_s16 extra = get_iword_cache_040 (2);
{{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp = m68k_dreg(regs, dstreg);
	offset &= 0x1f;
	tmp = (tmp << offset) | (tmp >> (32 - offset));
	bdata[0] = tmp & ((1 << (32 - width)) - 1);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
}}}}	m68k_incpci (4);
return;
}

#endif
/* BFTST.L #<data>.W,(An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_e8d0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 88;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
}}}}	m68k_incpci (4);
return;
}

#endif
/* BFTST.L #<data>.W,(d16,An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_e8e8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 88;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
}}}}	m68k_incpci (6);
return;
}

#endif
/* BFTST.L #<data>.W,(d8,An,Xn) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_e8f0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 88;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	m68k_incpci (4);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
}}}}}return;
}

#endif
/* BFTST.L #<data>.W,(xxx).W */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_e8f8_24)(uae_u32 opcode)
{
	OpcodeFamily = 88;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
}}}}	m68k_incpci (6);
return;
}

#endif
/* BFTST.L #<data>.W,(xxx).L */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_e8f9_24)(uae_u32 opcode)
{
	OpcodeFamily = 88;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (4);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
}}}}	m68k_incpci (8);
return;
}

#endif
/* BFTST.L #<data>.W,(d16,PC) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_e8fa_24)(uae_u32 opcode)
{
	uae_u32 dstreg = 2;
	OpcodeFamily = 88;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_getpci () + 4;
	dsta += (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
}}}}	m68k_incpci (6);
return;
}

#endif
/* BFTST.L #<data>.W,(d8,PC,Xn) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_e8fb_24)(uae_u32 opcode)
{
	uae_u32 dstreg = 3;
	OpcodeFamily = 88;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr tmppc;
	uaecptr dsta;
	m68k_incpci (4);
{	tmppc = m68k_getpci ();
	dsta = x_get_disp_ea_040 (tmppc, 0);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
}}}}}return;
}

#endif
/* BFEXTU.L #<data>.W,Dn */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_e9c0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 89;
{{	uae_s16 extra = get_iword_cache_040 (2);
{{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp = m68k_dreg(regs, dstreg);
	offset &= 0x1f;
	tmp = (tmp << offset) | (tmp >> (32 - offset));
	bdata[0] = tmp & ((1 << (32 - width)) - 1);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	m68k_dreg (regs, (extra >> 12) & 7) = tmp;
}}}}	m68k_incpci (4);
return;
}

#endif
/* BFEXTU.L #<data>.W,(An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_e9d0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 89;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	m68k_dreg (regs, (extra >> 12) & 7) = tmp;
}}}}	m68k_incpci (4);
return;
}

#endif
/* BFEXTU.L #<data>.W,(d16,An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_e9e8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 89;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	m68k_dreg (regs, (extra >> 12) & 7) = tmp;
}}}}	m68k_incpci (6);
return;
}

#endif
/* BFEXTU.L #<data>.W,(d8,An,Xn) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_e9f0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 89;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	m68k_incpci (4);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	m68k_dreg (regs, (extra >> 12) & 7) = tmp;
}}}}}return;
}

#endif
/* BFEXTU.L #<data>.W,(xxx).W */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_e9f8_24)(uae_u32 opcode)
{
	OpcodeFamily = 89;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	m68k_dreg (regs, (extra >> 12) & 7) = tmp;
}}}}	m68k_incpci (6);
return;
}

#endif
/* BFEXTU.L #<data>.W,(xxx).L */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_e9f9_24)(uae_u32 opcode)
{
	OpcodeFamily = 89;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (4);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	m68k_dreg (regs, (extra >> 12) & 7) = tmp;
}}}}	m68k_incpci (8);
return;
}

#endif
/* BFEXTU.L #<data>.W,(d16,PC) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_e9fa_24)(uae_u32 opcode)
{
	uae_u32 dstreg = 2;
	OpcodeFamily = 89;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_getpci () + 4;
	dsta += (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	m68k_dreg (regs, (extra >> 12) & 7) = tmp;
}}}}	m68k_incpci (6);
return;
}

#endif
/* BFEXTU.L #<data>.W,(d8,PC,Xn) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_e9fb_24)(uae_u32 opcode)
{
	uae_u32 dstreg = 3;
	OpcodeFamily = 89;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr tmppc;
	uaecptr dsta;
	m68k_incpci (4);
{	tmppc = m68k_getpci ();
	dsta = x_get_disp_ea_040 (tmppc, 0);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	m68k_dreg (regs, (extra >> 12) & 7) = tmp;
}}}}}return;
}

#endif
/* BFCHG.L #<data>.W,Dn */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_eac0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 90;
{{	uae_s16 extra = get_iword_cache_040 (2);
{{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp = m68k_dreg(regs, dstreg);
	offset &= 0x1f;
	tmp = (tmp << offset) | (tmp >> (32 - offset));
	bdata[0] = tmp & ((1 << (32 - width)) - 1);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = tmp ^ (0xffffffffu >> (32 - width));
	tmp = bdata[0] | (tmp << (32 - width));
	m68k_dreg(regs, dstreg) = (tmp >> offset) | (tmp << (32 - offset));
}}}}	m68k_incpci (4);
return;
}

#endif
/* BFCHG.L #<data>.W,(An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_ead0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 90;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = tmp ^ (0xffffffffu >> (32 - width));
	x_put_bitfield(dsta, bdata, tmp, offset, width);
}}}}	m68k_incpci (4);
return;
}

#endif
/* BFCHG.L #<data>.W,(d16,An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_eae8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 90;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = tmp ^ (0xffffffffu >> (32 - width));
	x_put_bitfield(dsta, bdata, tmp, offset, width);
}}}}	m68k_incpci (6);
return;
}

#endif
/* BFCHG.L #<data>.W,(d8,An,Xn) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_eaf0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 90;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	m68k_incpci (4);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = tmp ^ (0xffffffffu >> (32 - width));
	x_put_bitfield(dsta, bdata, tmp, offset, width);
}}}}}return;
}

#endif
/* BFCHG.L #<data>.W,(xxx).W */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_eaf8_24)(uae_u32 opcode)
{
	OpcodeFamily = 90;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = tmp ^ (0xffffffffu >> (32 - width));
	x_put_bitfield(dsta, bdata, tmp, offset, width);
}}}}	m68k_incpci (6);
return;
}

#endif
/* BFCHG.L #<data>.W,(xxx).L */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_eaf9_24)(uae_u32 opcode)
{
	OpcodeFamily = 90;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (4);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = tmp ^ (0xffffffffu >> (32 - width));
	x_put_bitfield(dsta, bdata, tmp, offset, width);
}}}}	m68k_incpci (8);
return;
}

#endif
/* BFEXTS.L #<data>.W,Dn */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_ebc0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 91;
{{	uae_s16 extra = get_iword_cache_040 (2);
{{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp = m68k_dreg(regs, dstreg);
	offset &= 0x1f;
	tmp = (tmp << offset) | (tmp >> (32 - offset));
	bdata[0] = tmp & ((1 << (32 - width)) - 1);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp = (uae_s32)tmp >> (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	m68k_dreg (regs, (extra >> 12) & 7) = tmp;
}}}}	m68k_incpci (4);
return;
}

#endif
/* BFEXTS.L #<data>.W,(An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_ebd0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 91;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp = (uae_s32)tmp >> (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	m68k_dreg (regs, (extra >> 12) & 7) = tmp;
}}}}	m68k_incpci (4);
return;
}

#endif
/* BFEXTS.L #<data>.W,(d16,An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_ebe8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 91;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp = (uae_s32)tmp >> (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	m68k_dreg (regs, (extra >> 12) & 7) = tmp;
}}}}	m68k_incpci (6);
return;
}

#endif
/* BFEXTS.L #<data>.W,(d8,An,Xn) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_ebf0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 91;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	m68k_incpci (4);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp = (uae_s32)tmp >> (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	m68k_dreg (regs, (extra >> 12) & 7) = tmp;
}}}}}return;
}

#endif
/* BFEXTS.L #<data>.W,(xxx).W */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_ebf8_24)(uae_u32 opcode)
{
	OpcodeFamily = 91;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp = (uae_s32)tmp >> (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	m68k_dreg (regs, (extra >> 12) & 7) = tmp;
}}}}	m68k_incpci (6);
return;
}

#endif
/* BFEXTS.L #<data>.W,(xxx).L */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_ebf9_24)(uae_u32 opcode)
{
	OpcodeFamily = 91;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (4);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp = (uae_s32)tmp >> (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	m68k_dreg (regs, (extra >> 12) & 7) = tmp;
}}}}	m68k_incpci (8);
return;
}

#endif
/* BFEXTS.L #<data>.W,(d16,PC) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_ebfa_24)(uae_u32 opcode)
{
	uae_u32 dstreg = 2;
	OpcodeFamily = 91;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_getpci () + 4;
	dsta += (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp = (uae_s32)tmp >> (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	m68k_dreg (regs, (extra >> 12) & 7) = tmp;
}}}}	m68k_incpci (6);
return;
}

#endif
/* BFEXTS.L #<data>.W,(d8,PC,Xn) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_ebfb_24)(uae_u32 opcode)
{
	uae_u32 dstreg = 3;
	OpcodeFamily = 91;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr tmppc;
	uaecptr dsta;
	m68k_incpci (4);
{	tmppc = m68k_getpci ();
	dsta = x_get_disp_ea_040 (tmppc, 0);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp = (uae_s32)tmp >> (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	m68k_dreg (regs, (extra >> 12) & 7) = tmp;
}}}}}return;
}

#endif
/* BFCLR.L #<data>.W,Dn */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_ecc0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 92;
{{	uae_s16 extra = get_iword_cache_040 (2);
{{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp = m68k_dreg(regs, dstreg);
	offset &= 0x1f;
	tmp = (tmp << offset) | (tmp >> (32 - offset));
	bdata[0] = tmp & ((1 << (32 - width)) - 1);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = 0;
	tmp = bdata[0] | (tmp << (32 - width));
	m68k_dreg(regs, dstreg) = (tmp >> offset) | (tmp << (32 - offset));
}}}}	m68k_incpci (4);
return;
}

#endif
/* BFCLR.L #<data>.W,(An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_ecd0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 92;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = 0;
	x_put_bitfield(dsta, bdata, tmp, offset, width);
}}}}	m68k_incpci (4);
return;
}

#endif
/* BFCLR.L #<data>.W,(d16,An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_ece8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 92;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = 0;
	x_put_bitfield(dsta, bdata, tmp, offset, width);
}}}}	m68k_incpci (6);
return;
}

#endif
/* BFCLR.L #<data>.W,(d8,An,Xn) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_ecf0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 92;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	m68k_incpci (4);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = 0;
	x_put_bitfield(dsta, bdata, tmp, offset, width);
}}}}}return;
}

#endif
/* BFCLR.L #<data>.W,(xxx).W */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_ecf8_24)(uae_u32 opcode)
{
	OpcodeFamily = 92;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = 0;
	x_put_bitfield(dsta, bdata, tmp, offset, width);
}}}}	m68k_incpci (6);
return;
}

#endif
/* BFCLR.L #<data>.W,(xxx).L */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_ecf9_24)(uae_u32 opcode)
{
	OpcodeFamily = 92;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (4);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = 0;
	x_put_bitfield(dsta, bdata, tmp, offset, width);
}}}}	m68k_incpci (8);
return;
}

#endif
/* BFFFO.L #<data>.W,Dn */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_edc0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 93;
{{	uae_s16 extra = get_iword_cache_040 (2);
{{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 offset2 = offset;
	uae_u32 tmp = m68k_dreg(regs, dstreg);
	offset &= 0x1f;
	tmp = (tmp << offset) | (tmp >> (32 - offset));
	bdata[0] = tmp & ((1 << (32 - width)) - 1);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	{ uae_u32 mask = 1 << (width - 1);
	while (mask) { if (tmp & mask) break; mask >>= 1; offset2++; }}
	m68k_dreg (regs, (extra >> 12) & 7) = offset2;
}}}}	m68k_incpci (4);
return;
}

#endif
/* BFFFO.L #<data>.W,(An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_edd0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 93;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 offset2 = offset;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	{ uae_u32 mask = 1 << (width - 1);
	while (mask) { if (tmp & mask) break; mask >>= 1; offset2++; }}
	m68k_dreg (regs, (extra >> 12) & 7) = offset2;
}}}}	m68k_incpci (4);
return;
}

#endif
/* BFFFO.L #<data>.W,(d16,An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_ede8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 93;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 offset2 = offset;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	{ uae_u32 mask = 1 << (width - 1);
	while (mask) { if (tmp & mask) break; mask >>= 1; offset2++; }}
	m68k_dreg (regs, (extra >> 12) & 7) = offset2;
}}}}	m68k_incpci (6);
return;
}

#endif
/* BFFFO.L #<data>.W,(d8,An,Xn) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_edf0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 93;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	m68k_incpci (4);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 offset2 = offset;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	{ uae_u32 mask = 1 << (width - 1);
	while (mask) { if (tmp & mask) break; mask >>= 1; offset2++; }}
	m68k_dreg (regs, (extra >> 12) & 7) = offset2;
}}}}}return;
}

#endif
/* BFFFO.L #<data>.W,(xxx).W */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_edf8_24)(uae_u32 opcode)
{
	OpcodeFamily = 93;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 offset2 = offset;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	{ uae_u32 mask = 1 << (width - 1);
	while (mask) { if (tmp & mask) break; mask >>= 1; offset2++; }}
	m68k_dreg (regs, (extra >> 12) & 7) = offset2;
}}}}	m68k_incpci (6);
return;
}

#endif
/* BFFFO.L #<data>.W,(xxx).L */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_edf9_24)(uae_u32 opcode)
{
	OpcodeFamily = 93;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (4);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 offset2 = offset;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	{ uae_u32 mask = 1 << (width - 1);
	while (mask) { if (tmp & mask) break; mask >>= 1; offset2++; }}
	m68k_dreg (regs, (extra >> 12) & 7) = offset2;
}}}}	m68k_incpci (8);
return;
}

#endif
/* BFFFO.L #<data>.W,(d16,PC) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_edfa_24)(uae_u32 opcode)
{
	uae_u32 dstreg = 2;
	OpcodeFamily = 93;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_getpci () + 4;
	dsta += (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 offset2 = offset;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	{ uae_u32 mask = 1 << (width - 1);
	while (mask) { if (tmp & mask) break; mask >>= 1; offset2++; }}
	m68k_dreg (regs, (extra >> 12) & 7) = offset2;
}}}}	m68k_incpci (6);
return;
}

#endif
/* BFFFO.L #<data>.W,(d8,PC,Xn) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_edfb_24)(uae_u32 opcode)
{
	uae_u32 dstreg = 3;
	OpcodeFamily = 93;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr tmppc;
	uaecptr dsta;
	m68k_incpci (4);
{	tmppc = m68k_getpci ();
	dsta = x_get_disp_ea_040 (tmppc, 0);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 offset2 = offset;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	{ uae_u32 mask = 1 << (width - 1);
	while (mask) { if (tmp & mask) break; mask >>= 1; offset2++; }}
	m68k_dreg (regs, (extra >> 12) & 7) = offset2;
}}}}}return;
}

#endif
/* BFSET.L #<data>.W,Dn */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_eec0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 94;
{{	uae_s16 extra = get_iword_cache_040 (2);
{{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp = m68k_dreg(regs, dstreg);
	offset &= 0x1f;
	tmp = (tmp << offset) | (tmp >> (32 - offset));
	bdata[0] = tmp & ((1 << (32 - width)) - 1);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = 0xffffffffu >> (32 - width);
	tmp = bdata[0] | (tmp << (32 - width));
	m68k_dreg(regs, dstreg) = (tmp >> offset) | (tmp << (32 - offset));
}}}}	m68k_incpci (4);
return;
}

#endif
/* BFSET.L #<data>.W,(An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_eed0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 94;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = 0xffffffffu >> (32 - width);
	x_put_bitfield(dsta, bdata, tmp, offset, width);
}}}}	m68k_incpci (4);
return;
}

#endif
/* BFSET.L #<data>.W,(d16,An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_eee8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 94;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = 0xffffffffu >> (32 - width);
	x_put_bitfield(dsta, bdata, tmp, offset, width);
}}}}	m68k_incpci (6);
return;
}

#endif
/* BFSET.L #<data>.W,(d8,An,Xn) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_eef0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 94;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	m68k_incpci (4);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = 0xffffffffu >> (32 - width);
	x_put_bitfield(dsta, bdata, tmp, offset, width);
}}}}}return;
}

#endif
/* BFSET.L #<data>.W,(xxx).W */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_eef8_24)(uae_u32 opcode)
{
	OpcodeFamily = 94;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = 0xffffffffu >> (32 - width);
	x_put_bitfield(dsta, bdata, tmp, offset, width);
}}}}	m68k_incpci (6);
return;
}

#endif
/* BFSET.L #<data>.W,(xxx).L */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_eef9_24)(uae_u32 opcode)
{
	OpcodeFamily = 94;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (4);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = 0xffffffffu >> (32 - width);
	x_put_bitfield(dsta, bdata, tmp, offset, width);
}}}}	m68k_incpci (8);
return;
}

#endif
/* BFINS.L #<data>.W,Dn */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_efc0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 95;
{{	uae_s16 extra = get_iword_cache_040 (2);
{{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp = m68k_dreg(regs, dstreg);
	offset &= 0x1f;
	tmp = (tmp << offset) | (tmp >> (32 - offset));
	bdata[0] = tmp & ((1 << (32 - width)) - 1);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = m68k_dreg (regs, (extra >> 12) & 7);
	tmp = tmp & (0xffffffffu >> (32 - width));
	SET_NFLG (tmp & (1 << (width - 1)) ? 1 : 0);
	SET_ZFLG (tmp == 0);
	tmp = bdata[0] | (tmp << (32 - width));
	m68k_dreg(regs, dstreg) = (tmp >> offset) | (tmp << (32 - offset));
}}}}	m68k_incpci (4);
return;
}

#endif
/* BFINS.L #<data>.W,(An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_efd0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 95;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = m68k_dreg (regs, (extra >> 12) & 7);
	tmp = tmp & (0xffffffffu >> (32 - width));
	SET_NFLG (tmp & (1 << (width - 1)) ? 1 : 0);
	SET_ZFLG (tmp == 0);
	x_put_bitfield(dsta, bdata, tmp, offset, width);
}}}}	m68k_incpci (4);
return;
}

#endif
/* BFINS.L #<data>.W,(d16,An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_efe8_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 95;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = m68k_dreg (regs, (extra >> 12) & 7);
	tmp = tmp & (0xffffffffu >> (32 - width));
	SET_NFLG (tmp & (1 << (width - 1)) ? 1 : 0);
	SET_ZFLG (tmp == 0);
	x_put_bitfield(dsta, bdata, tmp, offset, width);
}}}}	m68k_incpci (6);
return;
}

#endif
/* BFINS.L #<data>.W,(d8,An,Xn) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_eff0_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 95;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	m68k_incpci (4);
{	dsta = x_get_disp_ea_040 (m68k_areg (regs, dstreg), 0);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = m68k_dreg (regs, (extra >> 12) & 7);
	tmp = tmp & (0xffffffffu >> (32 - width));
	SET_NFLG (tmp & (1 << (width - 1)) ? 1 : 0);
	SET_ZFLG (tmp == 0);
	x_put_bitfield(dsta, bdata, tmp, offset, width);
}}}}}return;
}

#endif
/* BFINS.L #<data>.W,(xxx).W */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_eff8_24)(uae_u32 opcode)
{
	OpcodeFamily = 95;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = (uae_s32)(uae_s16)get_iword_cache_040 (4);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = m68k_dreg (regs, (extra >> 12) & 7);
	tmp = tmp & (0xffffffffu >> (32 - width));
	SET_NFLG (tmp & (1 << (width - 1)) ? 1 : 0);
	SET_ZFLG (tmp == 0);
	x_put_bitfield(dsta, bdata, tmp, offset, width);
}}}}	m68k_incpci (6);
return;
}

#endif
/* BFINS.L #<data>.W,(xxx).L */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_eff9_24)(uae_u32 opcode)
{
	OpcodeFamily = 95;
{{	uae_s16 extra = get_iword_cache_040 (2);
{	uaecptr dsta;
	dsta = get_ilong_cache_040 (4);
{	uae_u32 bdata[2];
	uae_s32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	uae_u32 tmp;
	dsta += offset >> 3;
	tmp = x_get_bitfield (dsta, bdata, offset, width);
	SET_NFLG_ALWAYS (((uae_s32)tmp) < 0 ? 1 : 0);
	tmp >>= (32 - width);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = m68k_dreg (regs, (extra >> 12) & 7);
	tmp = tmp & (0xffffffffu >> (32 - width));
	SET_NFLG (tmp & (1 << (width - 1)) ? 1 : 0);
	SET_ZFLG (tmp == 0);
	x_put_bitfield(dsta, bdata, tmp, offset, width);
}}}}	m68k_incpci (8);
return;
}

#endif
/* MMUOP030.L Dn,#<data>.W */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f000_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 118;
{	op_illg (opcode);
}	m68k_incpci (2);
return;
}

#endif
/* MMUOP030.L An,#<data>.W */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f008_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 118;
{	op_illg (opcode);
}	m68k_incpci (2);
return;
}

#endif
/* MMUOP030.L (An),#<data>.W */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f010_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 118;
{	op_illg (opcode);
}	m68k_incpci (2);
return;
}

#endif
/* MMUOP030.L (An)+,#<data>.W */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f018_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 118;
{	op_illg (opcode);
}	m68k_incpci (2);
return;
}

#endif
/* MMUOP030.L -(An),#<data>.W */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f020_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 118;
{	op_illg (opcode);
}	m68k_incpci (2);
return;
}

#endif
/* MMUOP030.L (d16,An),#<data>.W */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f028_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 118;
{	op_illg (opcode);
}	m68k_incpci (2);
return;
}

#endif
/* MMUOP030.L (d8,An,Xn),#<data>.W */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f030_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 118;
{	op_illg (opcode);
}	m68k_incpci (2);
return;
}

#endif
/* MMUOP030.L (xxx).W,#<data>.W */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f038_24)(uae_u32 opcode)
{
	OpcodeFamily = 118;
{	op_illg (opcode);
}	m68k_incpci (2);
return;
}

#endif
/* MMUOP030.L (xxx).L,#<data>.W */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f039_24)(uae_u32 opcode)
{
	OpcodeFamily = 118;
{	op_illg (opcode);
}	m68k_incpci (2);
return;
}

#endif
/* FPP.L #<data>.W,Dn */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f200_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 104;
{
#ifdef FPUEMU
{	uae_s16 extra = get_iword_cache_040 (2);
	m68k_incpci (4);
	fpuop_arithmetic(opcode, extra);
	if (regs.fp_exception) goto l_241797;
}
#endif
}l_241797: ;
return;
}

#endif
/* FPP.L #<data>.W,An */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f208_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 104;
{
#ifdef FPUEMU
{	uae_s16 extra = get_iword_cache_040 (2);
	m68k_incpci (4);
	fpuop_arithmetic(opcode, extra);
	if (regs.fp_exception) goto l_241798;
}
#endif
}l_241798: ;
return;
}

#endif
/* FPP.L #<data>.W,(An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f210_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 104;
{
#ifdef FPUEMU
{	uae_s16 extra = get_iword_cache_040 (2);
	m68k_incpci (4);
	fpuop_arithmetic(opcode, extra);
	if (regs.fp_exception) goto l_241799;
}
#endif
}l_241799: ;
return;
}

#endif
/* FPP.L #<data>.W,(An)+ */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f218_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 104;
{
#ifdef FPUEMU
{	uae_s16 extra = get_iword_cache_040 (2);
	m68k_incpci (4);
	fpuop_arithmetic(opcode, extra);
	if (regs.fp_exception) goto l_241800;
}
#endif
}l_241800: ;
return;
}

#endif
/* FPP.L #<data>.W,-(An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f220_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 104;
{
#ifdef FPUEMU
{	uae_s16 extra = get_iword_cache_040 (2);
	m68k_incpci (4);
	fpuop_arithmetic(opcode, extra);
	if (regs.fp_exception) goto l_241801;
}
#endif
}l_241801: ;
return;
}

#endif
/* FPP.L #<data>.W,(d16,An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f228_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 104;
{
#ifdef FPUEMU
{	uae_s16 extra = get_iword_cache_040 (2);
	m68k_incpci (4);
	fpuop_arithmetic(opcode, extra);
	if (regs.fp_exception) goto l_241802;
}
#endif
}l_241802: ;
return;
}

#endif
/* FPP.L #<data>.W,(d8,An,Xn) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f230_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 104;
{
#ifdef FPUEMU
{	uae_s16 extra = get_iword_cache_040 (2);
	m68k_incpci (4);
	fpuop_arithmetic(opcode, extra);
	if (regs.fp_exception) goto l_241803;
}
#endif
}l_241803: ;
return;
}

#endif
/* FPP.L #<data>.W,(xxx).W */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f238_24)(uae_u32 opcode)
{
	OpcodeFamily = 104;
{
#ifdef FPUEMU
{	uae_s16 extra = get_iword_cache_040 (2);
	m68k_incpci (4);
	fpuop_arithmetic(opcode, extra);
	if (regs.fp_exception) goto l_241804;
}
#endif
}l_241804: ;
return;
}

#endif
/* FPP.L #<data>.W,(xxx).L */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f239_24)(uae_u32 opcode)
{
	OpcodeFamily = 104;
{
#ifdef FPUEMU
{	uae_s16 extra = get_iword_cache_040 (2);
	m68k_incpci (4);
	fpuop_arithmetic(opcode, extra);
	if (regs.fp_exception) goto l_241805;
}
#endif
}l_241805: ;
return;
}

#endif
/* FPP.L #<data>.W,(d16,PC) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f23a_24)(uae_u32 opcode)
{
	uae_u32 dstreg = 2;
	OpcodeFamily = 104;
{
#ifdef FPUEMU
{	uae_s16 extra = get_iword_cache_040 (2);
	m68k_incpci (4);
	fpuop_arithmetic(opcode, extra);
	if (regs.fp_exception) goto l_241806;
}
#endif
}l_241806: ;
return;
}

#endif
/* FPP.L #<data>.W,(d8,PC,Xn) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f23b_24)(uae_u32 opcode)
{
	uae_u32 dstreg = 3;
	OpcodeFamily = 104;
{
#ifdef FPUEMU
{	uae_s16 extra = get_iword_cache_040 (2);
	m68k_incpci (4);
	fpuop_arithmetic(opcode, extra);
	if (regs.fp_exception) goto l_241807;
}
#endif
}l_241807: ;
return;
}

#endif
/* FPP.L #<data>.W,#<data>.L */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f23c_24)(uae_u32 opcode)
{
	OpcodeFamily = 104;
{
#ifdef FPUEMU
{	uae_s16 extra = get_iword_cache_040 (2);
	m68k_incpci (4);
	fpuop_arithmetic(opcode, extra);
	if (regs.fp_exception) goto l_241808;
}
#endif
}l_241808: ;
return;
}

#endif
/* FScc.L #<data>.W,Dn */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f240_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 106;
{
#ifdef FPUEMU
{	uae_s16 extra = get_iword_cache_040 (2);
	m68k_incpci (4);
	fpuop_scc (opcode, extra);
	if (regs.fp_exception) goto l_241809;
}
#endif
}l_241809: ;
return;
}

#endif
/* FDBcc.L #<data>.W,Dn */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f248_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 105;
{
#ifdef FPUEMU
{	uae_s16 extra = get_iword_cache_040 (2);
	m68k_incpci (4);
	fpuop_dbcc (opcode, extra);
	if (regs.fp_exception) goto l_241810;
	if (regs.fp_branch) {
		regs.fp_branch = false;
		fill_prefetch();
		goto l_241810;
	}
}
#endif
}l_241810: ;
return;
}

#endif
/* FScc.L #<data>.W,(An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f250_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 106;
{
#ifdef FPUEMU
{	uae_s16 extra = get_iword_cache_040 (2);
	m68k_incpci (4);
	fpuop_scc (opcode, extra);
	if (regs.fp_exception) goto l_241811;
}
#endif
}l_241811: ;
return;
}

#endif
/* FScc.L #<data>.W,(An)+ */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f258_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 106;
{
#ifdef FPUEMU
{	uae_s16 extra = get_iword_cache_040 (2);
	m68k_incpci (4);
	fpuop_scc (opcode, extra);
	if (regs.fp_exception) goto l_241812;
}
#endif
}l_241812: ;
return;
}

#endif
/* FScc.L #<data>.W,-(An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f260_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 106;
{
#ifdef FPUEMU
{	uae_s16 extra = get_iword_cache_040 (2);
	m68k_incpci (4);
	fpuop_scc (opcode, extra);
	if (regs.fp_exception) goto l_241813;
}
#endif
}l_241813: ;
return;
}

#endif
/* FScc.L #<data>.W,(d16,An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f268_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 106;
{
#ifdef FPUEMU
{	uae_s16 extra = get_iword_cache_040 (2);
	m68k_incpci (4);
	fpuop_scc (opcode, extra);
	if (regs.fp_exception) goto l_241814;
}
#endif
}l_241814: ;
return;
}

#endif
/* FScc.L #<data>.W,(d8,An,Xn) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f270_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 106;
{
#ifdef FPUEMU
{	uae_s16 extra = get_iword_cache_040 (2);
	m68k_incpci (4);
	fpuop_scc (opcode, extra);
	if (regs.fp_exception) goto l_241815;
}
#endif
}l_241815: ;
return;
}

#endif
/* FScc.L #<data>.W,(xxx).W */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f278_24)(uae_u32 opcode)
{
	OpcodeFamily = 106;
{
#ifdef FPUEMU
{	uae_s16 extra = get_iword_cache_040 (2);
	m68k_incpci (4);
	fpuop_scc (opcode, extra);
	if (regs.fp_exception) goto l_241816;
}
#endif
}l_241816: ;
return;
}

#endif
/* FScc.L #<data>.W,(xxx).L */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f279_24)(uae_u32 opcode)
{
	OpcodeFamily = 106;
{
#ifdef FPUEMU
{	uae_s16 extra = get_iword_cache_040 (2);
	m68k_incpci (4);
	fpuop_scc (opcode, extra);
	if (regs.fp_exception) goto l_241817;
}
#endif
}l_241817: ;
return;
}

#endif
/* FTRAPcc.L #<data>.W */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f27a_24)(uae_u32 opcode)
{
	OpcodeFamily = 107;
{
#ifdef FPUEMU
	uaecptr oldpc = m68k_getpci ();
	uae_u16 extra = get_iword_cache_040 (2);
{	uae_s16 dummy = get_iword_cache_040 (4);
	m68k_incpci (6);
	fpuop_trapcc (opcode, oldpc, extra);
	if (regs.fp_exception) goto l_241818;
}
#endif
}l_241818: ;
return;
}

#endif
/* FTRAPcc.L #<data>.L */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f27b_24)(uae_u32 opcode)
{
	OpcodeFamily = 107;
{
#ifdef FPUEMU
	uaecptr oldpc = m68k_getpci ();
	uae_u16 extra = get_iword_cache_040 (2);
{	uae_s32 dummy;
	dummy = get_ilong_cache_040 (4);
	m68k_incpci (8);
	fpuop_trapcc (opcode, oldpc, extra);
	if (regs.fp_exception) goto l_241819;
}
#endif
}l_241819: ;
return;
}

#endif
/* FTRAPcc.L  */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f27c_24)(uae_u32 opcode)
{
	OpcodeFamily = 107;
{
#ifdef FPUEMU
	uaecptr oldpc = m68k_getpci ();
	uae_u16 extra = get_iword_cache_040 (2);
	m68k_incpci (4);
	fpuop_trapcc (opcode, oldpc, extra);
	if (regs.fp_exception) goto l_241820;

#endif
}l_241820: ;
return;
}

#endif
/* FBccQ.L #<data>,#<data>.W */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f280_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 63);
	OpcodeFamily = 108;
{
#ifdef FPUEMU
	m68k_incpci (2);
{	uaecptr pc = m68k_getpci ();
{	uae_s16 extra = get_iword_cache_040 (0);
	m68k_incpci (2);
	fpuop_bcc (opcode, pc,extra);
	if (regs.fp_exception) goto l_241821;
	if (regs.fp_branch) {
		regs.fp_branch = false;
		fill_prefetch();
		goto l_241821;
	}
}}
#endif
}l_241821: ;
return;
}

#endif
/* FBccQ.L #<data>,#<data>.L */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f2c0_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 63);
	OpcodeFamily = 108;
{
#ifdef FPUEMU
	m68k_incpci (2);
{	uaecptr pc = m68k_getpci ();
{	uae_s32 extra;
	extra = get_ilong_cache_040 (0);
	m68k_incpci (4);
	fpuop_bcc (opcode, pc,extra);
	if (regs.fp_exception) goto l_241822;
	if (regs.fp_branch) {
		regs.fp_branch = false;
		fill_prefetch();
		goto l_241822;
	}
}}
#endif
}l_241822: ;
return;
}

#endif
/* FSAVE.L (An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f310_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 109;
{if (!regs.s) { Exception (8); goto l_241823; }
{
#ifdef FPUEMU
	m68k_incpci (2);
	fpuop_save (opcode);
	if (regs.fp_exception) goto l_241823;

#endif
}}l_241823: ;
return;
}

#endif
/* FSAVE.L -(An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f320_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 109;
{if (!regs.s) { Exception (8); goto l_241824; }
{
#ifdef FPUEMU
	m68k_incpci (2);
	fpuop_save (opcode);
	if (regs.fp_exception) goto l_241824;

#endif
}}l_241824: ;
return;
}

#endif
/* FSAVE.L (d16,An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f328_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 109;
{if (!regs.s) { Exception (8); goto l_241825; }
{
#ifdef FPUEMU
	m68k_incpci (2);
	fpuop_save (opcode);
	if (regs.fp_exception) goto l_241825;

#endif
}}l_241825: ;
return;
}

#endif
/* FSAVE.L (d8,An,Xn) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f330_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 109;
{if (!regs.s) { Exception (8); goto l_241826; }
{
#ifdef FPUEMU
	m68k_incpci (2);
	fpuop_save (opcode);
	if (regs.fp_exception) goto l_241826;

#endif
}}l_241826: ;
return;
}

#endif
/* FSAVE.L (xxx).W */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f338_24)(uae_u32 opcode)
{
	OpcodeFamily = 109;
{if (!regs.s) { Exception (8); goto l_241827; }
{
#ifdef FPUEMU
	m68k_incpci (2);
	fpuop_save (opcode);
	if (regs.fp_exception) goto l_241827;

#endif
}}l_241827: ;
return;
}

#endif
/* FSAVE.L (xxx).L */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f339_24)(uae_u32 opcode)
{
	OpcodeFamily = 109;
{if (!regs.s) { Exception (8); goto l_241828; }
{
#ifdef FPUEMU
	m68k_incpci (2);
	fpuop_save (opcode);
	if (regs.fp_exception) goto l_241828;

#endif
}}l_241828: ;
return;
}

#endif
/* FRESTORE.L (An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f350_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 110;
{if (!regs.s) { Exception (8); goto l_241829; }
{
#ifdef FPUEMU
	m68k_incpci (2);
	fpuop_restore (opcode);
	if (regs.fp_exception) goto l_241829;

#endif
}}l_241829: ;
return;
}

#endif
/* FRESTORE.L (An)+ */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f358_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 110;
{if (!regs.s) { Exception (8); goto l_241830; }
{
#ifdef FPUEMU
	m68k_incpci (2);
	fpuop_restore (opcode);
	if (regs.fp_exception) goto l_241830;

#endif
}}l_241830: ;
return;
}

#endif
/* FRESTORE.L (d16,An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f368_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 110;
{if (!regs.s) { Exception (8); goto l_241831; }
{
#ifdef FPUEMU
	m68k_incpci (2);
	fpuop_restore (opcode);
	if (regs.fp_exception) goto l_241831;

#endif
}}l_241831: ;
return;
}

#endif
/* FRESTORE.L (d8,An,Xn) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f370_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 110;
{if (!regs.s) { Exception (8); goto l_241832; }
{
#ifdef FPUEMU
	m68k_incpci (2);
	fpuop_restore (opcode);
	if (regs.fp_exception) goto l_241832;

#endif
}}l_241832: ;
return;
}

#endif
/* FRESTORE.L (xxx).W */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f378_24)(uae_u32 opcode)
{
	OpcodeFamily = 110;
{if (!regs.s) { Exception (8); goto l_241833; }
{
#ifdef FPUEMU
	m68k_incpci (2);
	fpuop_restore (opcode);
	if (regs.fp_exception) goto l_241833;

#endif
}}l_241833: ;
return;
}

#endif
/* FRESTORE.L (xxx).L */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f379_24)(uae_u32 opcode)
{
	OpcodeFamily = 110;
{if (!regs.s) { Exception (8); goto l_241834; }
{
#ifdef FPUEMU
	m68k_incpci (2);
	fpuop_restore (opcode);
	if (regs.fp_exception) goto l_241834;

#endif
}}l_241834: ;
return;
}

#endif
/* FRESTORE.L (d16,PC) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f37a_24)(uae_u32 opcode)
{
	OpcodeFamily = 110;
{if (!regs.s) { Exception (8); goto l_241835; }
{
#ifdef FPUEMU
	m68k_incpci (2);
	fpuop_restore (opcode);
	if (regs.fp_exception) goto l_241835;

#endif
}}l_241835: ;
return;
}

#endif
/* FRESTORE.L (d8,PC,Xn) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f37b_24)(uae_u32 opcode)
{
	OpcodeFamily = 110;
{if (!regs.s) { Exception (8); goto l_241836; }
{
#ifdef FPUEMU
	m68k_incpci (2);
	fpuop_restore (opcode);
	if (regs.fp_exception) goto l_241836;

#endif
}}l_241836: ;
return;
}

#endif
/* CINVLQ.L #<data>,An */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f408_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 6) & 3);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 111;
{if (!regs.s) { Exception (8); goto l_241837; }
{	flush_cpu_caches_040(opcode);
	if (opcode & 0x80)
		flush_icache(m68k_areg (regs, opcode & 3), (opcode >> 6) & 3);
}}	m68k_incpci (2);
l_241837: ;
return;
}

#endif
/* CINVPQ.L #<data>,An */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f410_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 6) & 3);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 112;
{if (!regs.s) { Exception (8); goto l_241838; }
{	flush_cpu_caches_040(opcode);
	if (opcode & 0x80)
		flush_icache(m68k_areg (regs, opcode & 3), (opcode >> 6) & 3);
}}	m68k_incpci (2);
l_241838: ;
return;
}

#endif
/* CINVAQ.L #<data> */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f418_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 6) & 3);
	OpcodeFamily = 113;
{if (!regs.s) { Exception (8); goto l_241839; }
{	flush_cpu_caches_040(opcode);
	if (opcode & 0x80)
		flush_icache(m68k_areg (regs, opcode & 3), (opcode >> 6) & 3);
}}	m68k_incpci (2);
l_241839: ;
return;
}

#endif
/* CINVAQ.L #<data> */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f419_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 6) & 3);
	OpcodeFamily = 113;
{if (!regs.s) { Exception (8); goto l_241840; }
{	flush_cpu_caches_040(opcode);
	if (opcode & 0x80)
		flush_icache(m68k_areg (regs, opcode & 3), (opcode >> 6) & 3);
}}	m68k_incpci (2);
l_241840: ;
return;
}

#endif
/* CINVAQ.L #<data> */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f41a_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 6) & 3);
	OpcodeFamily = 113;
{if (!regs.s) { Exception (8); goto l_241841; }
{	flush_cpu_caches_040(opcode);
	if (opcode & 0x80)
		flush_icache(m68k_areg (regs, opcode & 3), (opcode >> 6) & 3);
}}	m68k_incpci (2);
l_241841: ;
return;
}

#endif
/* CINVAQ.L #<data> */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f41b_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 6) & 3);
	OpcodeFamily = 113;
{if (!regs.s) { Exception (8); goto l_241842; }
{	flush_cpu_caches_040(opcode);
	if (opcode & 0x80)
		flush_icache(m68k_areg (regs, opcode & 3), (opcode >> 6) & 3);
}}	m68k_incpci (2);
l_241842: ;
return;
}

#endif
/* CINVAQ.L #<data> */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f41c_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 6) & 3);
	OpcodeFamily = 113;
{if (!regs.s) { Exception (8); goto l_241843; }
{	flush_cpu_caches_040(opcode);
	if (opcode & 0x80)
		flush_icache(m68k_areg (regs, opcode & 3), (opcode >> 6) & 3);
}}	m68k_incpci (2);
l_241843: ;
return;
}

#endif
/* CINVAQ.L #<data> */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f41d_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 6) & 3);
	OpcodeFamily = 113;
{if (!regs.s) { Exception (8); goto l_241844; }
{	flush_cpu_caches_040(opcode);
	if (opcode & 0x80)
		flush_icache(m68k_areg (regs, opcode & 3), (opcode >> 6) & 3);
}}	m68k_incpci (2);
l_241844: ;
return;
}

#endif
/* CINVAQ.L #<data> */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f41e_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 6) & 3);
	OpcodeFamily = 113;
{if (!regs.s) { Exception (8); goto l_241845; }
{	flush_cpu_caches_040(opcode);
	if (opcode & 0x80)
		flush_icache(m68k_areg (regs, opcode & 3), (opcode >> 6) & 3);
}}	m68k_incpci (2);
l_241845: ;
return;
}

#endif
/* CINVAQ.L #<data> */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f41f_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 6) & 3);
	OpcodeFamily = 113;
{if (!regs.s) { Exception (8); goto l_241846; }
{	flush_cpu_caches_040(opcode);
	if (opcode & 0x80)
		flush_icache(m68k_areg (regs, opcode & 3), (opcode >> 6) & 3);
}}	m68k_incpci (2);
l_241846: ;
return;
}

#endif
/* CPUSHLQ.L #<data>,An */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f428_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 6) & 3);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 114;
{if (!regs.s) { Exception (8); goto l_241847; }
{	flush_cpu_caches_040(opcode);
	if (opcode & 0x80)
		flush_icache(m68k_areg (regs, opcode & 3), (opcode >> 6) & 3);
}}	m68k_incpci (2);
l_241847: ;
return;
}

#endif
/* CPUSHPQ.L #<data>,An */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f430_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 6) & 3);
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 115;
{if (!regs.s) { Exception (8); goto l_241848; }
{	flush_cpu_caches_040(opcode);
	if (opcode & 0x80)
		flush_icache(m68k_areg (regs, opcode & 3), (opcode >> 6) & 3);
}}	m68k_incpci (2);
l_241848: ;
return;
}

#endif
/* CPUSHAQ.L #<data> */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f438_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 6) & 3);
	OpcodeFamily = 116;
{if (!regs.s) { Exception (8); goto l_241849; }
{	flush_cpu_caches_040(opcode);
	if (opcode & 0x80)
		flush_icache(m68k_areg (regs, opcode & 3), (opcode >> 6) & 3);
}}	m68k_incpci (2);
l_241849: ;
return;
}

#endif
/* CPUSHAQ.L #<data> */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f439_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 6) & 3);
	OpcodeFamily = 116;
{if (!regs.s) { Exception (8); goto l_241850; }
{	flush_cpu_caches_040(opcode);
	if (opcode & 0x80)
		flush_icache(m68k_areg (regs, opcode & 3), (opcode >> 6) & 3);
}}	m68k_incpci (2);
l_241850: ;
return;
}

#endif
/* CPUSHAQ.L #<data> */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f43a_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 6) & 3);
	OpcodeFamily = 116;
{if (!regs.s) { Exception (8); goto l_241851; }
{	flush_cpu_caches_040(opcode);
	if (opcode & 0x80)
		flush_icache(m68k_areg (regs, opcode & 3), (opcode >> 6) & 3);
}}	m68k_incpci (2);
l_241851: ;
return;
}

#endif
/* CPUSHAQ.L #<data> */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f43b_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 6) & 3);
	OpcodeFamily = 116;
{if (!regs.s) { Exception (8); goto l_241852; }
{	flush_cpu_caches_040(opcode);
	if (opcode & 0x80)
		flush_icache(m68k_areg (regs, opcode & 3), (opcode >> 6) & 3);
}}	m68k_incpci (2);
l_241852: ;
return;
}

#endif
/* CPUSHAQ.L #<data> */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f43c_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 6) & 3);
	OpcodeFamily = 116;
{if (!regs.s) { Exception (8); goto l_241853; }
{	flush_cpu_caches_040(opcode);
	if (opcode & 0x80)
		flush_icache(m68k_areg (regs, opcode & 3), (opcode >> 6) & 3);
}}	m68k_incpci (2);
l_241853: ;
return;
}

#endif
/* CPUSHAQ.L #<data> */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f43d_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 6) & 3);
	OpcodeFamily = 116;
{if (!regs.s) { Exception (8); goto l_241854; }
{	flush_cpu_caches_040(opcode);
	if (opcode & 0x80)
		flush_icache(m68k_areg (regs, opcode & 3), (opcode >> 6) & 3);
}}	m68k_incpci (2);
l_241854: ;
return;
}

#endif
/* CPUSHAQ.L #<data> */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f43e_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 6) & 3);
	OpcodeFamily = 116;
{if (!regs.s) { Exception (8); goto l_241855; }
{	flush_cpu_caches_040(opcode);
	if (opcode & 0x80)
		flush_icache(m68k_areg (regs, opcode & 3), (opcode >> 6) & 3);
}}	m68k_incpci (2);
l_241855: ;
return;
}

#endif
/* CPUSHAQ.L #<data> */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f43f_24)(uae_u32 opcode)
{
	uae_u32 srcreg = ((opcode >> 6) & 3);
	OpcodeFamily = 116;
{if (!regs.s) { Exception (8); goto l_241856; }
{	flush_cpu_caches_040(opcode);
	if (opcode & 0x80)
		flush_icache(m68k_areg (regs, opcode & 3), (opcode >> 6) & 3);
}}	m68k_incpci (2);
l_241856: ;
return;
}

#endif
/* PFLUSHN.L (An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f500_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 119;
{if (!regs.s) { Exception (8); goto l_241857; }
{	m68k_incpci (2);
	mmu_op (opcode, 0);
}}l_241857: ;
return;
}

#endif
/* PFLUSH.L (An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f508_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 120;
{if (!regs.s) { Exception (8); goto l_241858; }
{	m68k_incpci (2);
	mmu_op (opcode, 0);
}}l_241858: ;
return;
}

#endif
/* PFLUSHAN.L (An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f510_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 121;
{if (!regs.s) { Exception (8); goto l_241859; }
{	m68k_incpci (2);
	mmu_op (opcode, 0);
}}l_241859: ;
return;
}

#endif
/* PFLUSHA.L (An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f518_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 122;
{if (!regs.s) { Exception (8); goto l_241860; }
{	m68k_incpci (2);
	mmu_op (opcode, 0);
}}l_241860: ;
return;
}

#endif
/* PTESTW.L (An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f548_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 126;
{if (!regs.s) { Exception (8); goto l_241861; }
{	m68k_incpci (2);
	mmu_op (opcode, 0);
}}l_241861: ;
return;
}

#endif
/* PTESTR.L (An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f568_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 125;
{if (!regs.s) { Exception (8); goto l_241862; }
{	m68k_incpci (2);
	mmu_op (opcode, 0);
}}l_241862: ;
return;
}

#endif
/* PLPAW.L (An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f588_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 124;
{if (!regs.s) { Exception (8); goto l_241863; }
{	m68k_incpci (2);
	mmu_op (opcode, 0);
}}l_241863: ;
return;
}

#endif
/* PLPAR.L (An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f5c8_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 123;
{if (!regs.s) { Exception (8); goto l_241864; }
{	m68k_incpci (2);
	mmu_op (opcode, 0);
}}l_241864: ;
return;
}

#endif
/* MOVE16.L (An)+,(xxx).L */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f600_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 117;
{	uae_u32 v[4];
{	uaecptr memsa;
	memsa = m68k_areg (regs, srcreg);
{	uaecptr memda;
	memda = get_ilong_cache_040 (2);
	memsa &= ~15;
	memda &= ~15;
	v[0] = x_get_long (memsa);
	v[1] = x_get_long (memsa + 4);
	v[2] = x_get_long (memsa + 8);
	v[3] = x_get_long (memsa + 12);
	x_put_long (memda , v[0]);
	x_put_long (memda + 4, v[1]);
	x_put_long (memda + 8, v[2]);
	x_put_long (memda + 12, v[3]);
	m68k_areg (regs, srcreg) += 16;
}}}	m68k_incpci (6);
return;
}

#endif
/* MOVE16.L (xxx).L,(An)+ */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f608_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 117;
{	uae_u32 v[4];
{	uaecptr memsa;
	memsa = get_ilong_cache_040 (2);
{	uaecptr memda;
	memda = m68k_areg (regs, dstreg);
	memsa &= ~15;
	memda &= ~15;
	v[0] = x_get_long (memsa);
	v[1] = x_get_long (memsa + 4);
	v[2] = x_get_long (memsa + 8);
	v[3] = x_get_long (memsa + 12);
	x_put_long (memda , v[0]);
	x_put_long (memda + 4, v[1]);
	x_put_long (memda + 8, v[2]);
	x_put_long (memda + 12, v[3]);
	m68k_areg (regs, dstreg) += 16;
}}}	m68k_incpci (6);
return;
}

#endif
/* MOVE16.L (An),(xxx).L */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f610_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	OpcodeFamily = 117;
{	uae_u32 v[4];
{	uaecptr memsa;
	memsa = m68k_areg (regs, srcreg);
{	uaecptr memda;
	memda = get_ilong_cache_040 (2);
	memsa &= ~15;
	memda &= ~15;
	v[0] = x_get_long (memsa);
	v[1] = x_get_long (memsa + 4);
	v[2] = x_get_long (memsa + 8);
	v[3] = x_get_long (memsa + 12);
	x_put_long (memda , v[0]);
	x_put_long (memda + 4, v[1]);
	x_put_long (memda + 8, v[2]);
	x_put_long (memda + 12, v[3]);
}}}	m68k_incpci (6);
return;
}

#endif
/* MOVE16.L (xxx).L,(An) */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f618_24)(uae_u32 opcode)
{
	uae_u32 dstreg = opcode & 7;
	OpcodeFamily = 117;
{	uae_u32 v[4];
{	uaecptr memsa;
	memsa = get_ilong_cache_040 (2);
{	uaecptr memda;
	memda = m68k_areg (regs, dstreg);
	memsa &= ~15;
	memda &= ~15;
	v[0] = x_get_long (memsa);
	v[1] = x_get_long (memsa + 4);
	v[2] = x_get_long (memsa + 8);
	v[3] = x_get_long (memsa + 12);
	x_put_long (memda , v[0]);
	x_put_long (memda + 4, v[1]);
	x_put_long (memda + 8, v[2]);
	x_put_long (memda + 12, v[3]);
}}}	m68k_incpci (6);
return;
}

#endif
/* MOVE16.L (An)+,(An)+ */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f620_24)(uae_u32 opcode)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = 0;
	OpcodeFamily = 117;
{	uae_u32 v[4];
	uaecptr mems = m68k_areg (regs, srcreg) & ~15, memd;
	dstreg = (get_iword_cache_040 (2) >> 12) & 7;
	memd = m68k_areg (regs, dstreg) & ~15;
	v[0] = x_get_long (mems);
	v[1] = x_get_long (mems + 4);
	v[2] = x_get_long (mems + 8);
	v[3] = x_get_long (mems + 12);
	x_put_long (memd , v[0]);
	x_put_long (memd + 4, v[1]);
	x_put_long (memd + 8, v[2]);
	x_put_long (memd + 12, v[3]);
	if (srcreg != dstreg)
		m68k_areg (regs, srcreg) += 16;
	m68k_areg (regs, dstreg) += 16;
}	m68k_incpci (4);
return;
}

#endif
/* LPSTOP.L #<data>.W */
#ifndef CPUEMU_68000_ONLY
void REGPARAM2 CPUFUNC(op_f800_24)(uae_u32 opcode)
{
	OpcodeFamily = 127;
{if (!regs.s) { Exception (8); goto l_241870; }
{	uae_u16 sw = x_get_iword (2);
	uae_u16 sr;
	if (sw != (0x100|0x80|0x40)) { Exception (4); goto l_241870; }
	sr = x_get_iword (4);
	if (!(sr & 0x8000)) { Exception (8); goto l_241870; }
	regs.sr = sr;
	MakeFromSR();
	m68k_setstopped();
	m68k_incpci (6);
}}l_241870: ;
return;
}

#endif
#endif


#if !defined(PART_1) && !defined(PART_2) && !defined(PART_3) && !defined(PART_4) && !defined(PART_5) && !defined(PART_6) && !defined(PART_7) && !defined(PART_8)
#define PART_1 1
#define PART_2 1
#define PART_3 1
#define PART_4 1
#define PART_5 1
#define PART_6 1
#define PART_7 1
#define PART_8 1
#endif

#ifdef PART_1
#endif

#ifdef PART_2
#endif

#ifdef PART_3
#endif

#ifdef PART_4
#endif

#ifdef PART_5
#endif

#ifdef PART_6
#endif

#ifdef PART_7
#endif

#ifdef PART_8
#endif

