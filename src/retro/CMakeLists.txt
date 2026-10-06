
include_directories(. ../.. ../includes ../debug ../falcon libretro-common/include)

add_library(UiRetro OBJECT audio.c disk_control.c floppy_sound.c harddisk.c joy_ui.c gui_event.c keymap.c
                    main_retro.c microphone.c options.c screen.c statusbar.c timing.c vfs.c)
target_include_directories(UiRetro PRIVATE ${LIBRETRO_INCLUDE_DIR})
target_compile_definitions(UiRetro PRIVATE LIBRETRO)
if(ENABLE_LIBRETRO AND NOT LIBRETRO_STATIC)
    set_target_properties(UiRetro PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
endif(ENABLE_LIBRETRO AND NOT LIBRETRO_STATIC)
