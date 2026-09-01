
if(Readline_FOUND)
	include_directories(${READLINE_INCLUDE_DIR})
endif(Readline_FOUND)

if(ENABLE_DSP_EMU)
	set(DSPDBG_C debugdsp.c)
endif(ENABLE_DSP_EMU)

set(DEBUG_SOURCES
	log.c debugui.c breakcond.c debugcpu.c debugInfo.c
	${DSPDBG_C} evaluate.c history.c symbols.c vars.c
	profile.c profilecpu.c profiledsp.c stacktrace.c
	natfeats.c console.c 68kDisass.c)

add_library(Debug OBJECT ${DEBUG_SOURCES})

if(ENABLE_LIBRETRO)
	if(NOT LIBRETRO_STATIC)
		set_target_properties(Debug PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
	endif(NOT LIBRETRO_STATIC)

	# Separate object files compiled with -DLIBRETRO for log.c
	add_library(DebugRetro OBJECT ${DEBUG_SOURCES})
	target_compile_definitions(DebugRetro PRIVATE LIBRETRO)
	if(NOT LIBRETRO_STATIC)
		set_target_properties(DebugRetro PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
	endif(NOT LIBRETRO_STATIC)
endif(ENABLE_LIBRETRO)
