
include_directories(. ../.. ../includes ../debug ../falcon)

add_library(UiRetro OBJECT
		audio.c
		disk_control.c
		file_retro.c
		floppy_sound.c
		harddisk.c
		joy_ui.c
		gui_event.c
		keymap.c
		main_retro.c
		microphone.c
		options.c
		screen.c
		statusbar.c
		timing.c
		vfs.c)

target_include_directories(UiRetro PRIVATE ${LIBRETRO_INCLUDE_DIR})
if(NOT LIBRETRO_STATIC)
	set_target_properties(UiRetro PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
endif(NOT LIBRETRO_STATIC)
