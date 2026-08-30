include(FetchContent)

option(ENABLE_STATIC_SDL2
	"Build and statically link SDL2"
	OFF)

option(ENABLE_STATIC_ZLIB
	"Build and statically link zlib"
	OFF)

option(ENABLE_STATIC_CAPSIMAGE
	"Build and statically link CapsImg"
	OFF)

# SDL2
if(ENABLE_STATIC_SDL2)
	set(SDL_SHARED OFF CACHE BOOL "" FORCE)
	set(SDL_STATIC ON CACHE BOOL "" FORCE)
	set(SDL_TESTS OFF CACHE BOOL "" FORCE)
	set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)
	set(SDL_EXAMPLES OFF CACHE BOOL "" FORCE)
	set(SDL_UNINSTALL OFF CACHE BOOL "" FORCE)

	FetchContent_Declare(
		SDL2
		GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
		GIT_TAG release-2.32.8
		GIT_SHALLOW TRUE
	)

	FetchContent_MakeAvailable(SDL2)

	if(TARGET SDL2::SDL2-static)
		set(SDL2_LIBRARIES SDL2::SDL2-static)
		get_target_property(SDL2_INCLUDE_DIRS
			SDL2::SDL2-static
			INTERFACE_INCLUDE_DIRECTORIES)
	elseif(TARGET SDL2-static)
		set(SDL2_LIBRARIES SDL2-static)
		get_target_property(SDL2_INCLUDE_DIRS
			SDL2-static
			INTERFACE_INCLUDE_DIRECTORIES)
	else()
		message(FATAL_ERROR "SDL2 static target was not created")
	endif()

	include_directories(${SDL2_INCLUDE_DIRS})
endif()

# zlib
if(ENABLE_STATIC_ZLIB)

	set(ZLIB_BUILD_SHARED OFF CACHE BOOL "" FORCE)

	FetchContent_Declare(
		zlib
		GIT_REPOSITORY https://github.com/madler/zlib.git
		GIT_TAG v1.3.1
		GIT_SHALLOW TRUE
	)

	FetchContent_MakeAvailable(zlib)

	if(TARGET zlibstatic)

		set(ZLIB_LIBRARY zlibstatic)

		set_target_properties(zlibstatic PROPERTIES
			POSITION_INDEPENDENT_CODE TRUE
		)

		if(NOT TARGET ZLIB::ZLIB)
			add_library(ZLIB::ZLIB ALIAS zlibstatic)
		endif()

	elseif(TARGET zlib)

		set(ZLIB_LIBRARY zlib)

	else()

		message(FATAL_ERROR "zlib static target was not created")

	endif()

	set(ZLIB_FOUND TRUE)
	set(HAVE_LIBZ 1)
	set(HAVE_ZLIB_H 1)
endif()

# CapsImg
if(ENABLE_STATIC_CAPSIMAGE)

	message(STATUS "Building CapsImg statically")

	enable_language(CXX)

	FetchContent_Declare(
		capsimg
		GIT_REPOSITORY https://github.com/rsn8887/capsimg.git
		GIT_TAG c92d17b4383ebf432788f7b5a38fdd6902376f00
		GIT_SHALLOW TRUE
	)

	if(POLICY CMP0169)
		cmake_policy(SET CMP0169 OLD)
	endif()

	FetchContent_Populate(capsimg)

	set(CAPSIMAGE_SOURCES
		${capsimg_SOURCE_DIR}/Codec/CTRawCodec.cpp
		${capsimg_SOURCE_DIR}/Codec/CTRawCodecDecompressor.cpp
		${capsimg_SOURCE_DIR}/Codec/DiskEncoding.cpp

		${capsimg_SOURCE_DIR}/Core/BaseFile.cpp
		${capsimg_SOURCE_DIR}/Core/BitBuffer.cpp
		${capsimg_SOURCE_DIR}/Core/CRC.cpp
		${capsimg_SOURCE_DIR}/Core/DiskFile.cpp
		${capsimg_SOURCE_DIR}/Core/MemoryFile.cpp

		${capsimg_SOURCE_DIR}/CAPSImg/CapsAPI.cpp
		${capsimg_SOURCE_DIR}/CAPSImg/CapsFDCEmulator.cpp
		${capsimg_SOURCE_DIR}/CAPSImg/CapsFile.cpp
		${capsimg_SOURCE_DIR}/CAPSImg/CapsFormatMFM.cpp
		${capsimg_SOURCE_DIR}/CAPSImg/CapsImage.cpp
		${capsimg_SOURCE_DIR}/CAPSImg/CapsImageStd.cpp
		${capsimg_SOURCE_DIR}/CAPSImg/CapsLoader.cpp
		${capsimg_SOURCE_DIR}/CAPSImg/DiskImage.cpp
		${capsimg_SOURCE_DIR}/CAPSImg/DiskImageFactory.cpp
		${capsimg_SOURCE_DIR}/CAPSImg/stdafx.cpp
		${capsimg_SOURCE_DIR}/CAPSImg/StreamCueImage.cpp
		${capsimg_SOURCE_DIR}/CAPSImg/StreamImage.cpp
	)

	add_library(capsimage STATIC ${CAPSIMAGE_SOURCES})

	set_target_properties(capsimage PROPERTIES
		LINKER_LANGUAGE CXX
		POSITION_INDEPENDENT_CODE TRUE
	)

	set(CAPSIMAGE_GENERATED_INCLUDE_DIR
		${CMAKE_CURRENT_BINARY_DIR}/capsimage/include
	)

	set(CAPSIMAGE_CAPS_INCLUDE_DIR
		${CAPSIMAGE_GENERATED_INCLUDE_DIR}/caps
	)

	file(MAKE_DIRECTORY
		${CAPSIMAGE_CAPS_INCLUDE_DIR}
	)

	file(GLOB CAPSIMAGE_LIBIPF_HEADERS
		${capsimg_SOURCE_DIR}/LibIPF/*.h
	)

	file(COPY
		${CAPSIMAGE_LIBIPF_HEADERS}
		${capsimg_SOURCE_DIR}/Core/CommonTypes.h
		DESTINATION ${CAPSIMAGE_CAPS_INCLUDE_DIR}
	)

	target_include_directories(capsimage
		PUBLIC
			${CAPSIMAGE_GENERATED_INCLUDE_DIR}
			${capsimg_SOURCE_DIR}/LibIPF
			${capsimg_SOURCE_DIR}/Core
			${capsimg_SOURCE_DIR}/Codec
			${capsimg_SOURCE_DIR}/Device
			${capsimg_SOURCE_DIR}/CAPSImg
	)

#	may clash with mingw headers:
#	if(WIN32)
#		target_include_directories(capsimage
#			PUBLIC
#				${capsimg_SOURCE_DIR}/Compatibility
#		)
#	endif()

	set(CAPSIMAGE_LIBRARY capsimage)
	set(CAPSIMAGE_INCLUDE_DIR
		${CAPSIMAGE_GENERATED_INCLUDE_DIR}
		${capsimg_SOURCE_DIR}/CAPSImg
	)
	set(CapsImage_FOUND TRUE)
	set(HAVE_CAPSIMAGE 1)
endif()

message(STATUS "")
message(STATUS "Built dependencies:")
message(STATUS "  SDL2:    ${SDL2_LIBRARIES}")
message(STATUS "  zlib:    ${ZLIB_LIBRARY}")
message(STATUS "  CapsImg: ${CAPSIMAGE_LIBRARY}")
message(STATUS "")
