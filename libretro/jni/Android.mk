LOCAL_PATH := $(call my-dir)

CORE_DIR     := $(LOCAL_PATH)/../..
LIBRETRO_DIR := $(CORE_DIR)/libretro
EMU          := $(CORE_DIR)/src
CPU          := $(EMU)/uae-cpu
FALCON       := $(EMU)/falcon
DBG          := $(EMU)/debug
FLP          := $(EMU)
GUI          := $(LIBRETRO_DIR)/gui-retro
CPU_PREGEN   := $(LIBRETRO_DIR)/uae-cpu-pregen
LIBUTILS     := $(LIBRETRO_DIR)/utils

SOURCES_C :=

include $(CORE_DIR)/Makefile.common

COREFLAGS := -DANDROID -DAND -D__LIBRETRO__ $(INCFLAGS)

GIT_VERSION := " $(shell git rev-parse --short HEAD || echo unknown)"
ifneq ($(GIT_VERSION)," unknown")
  COREFLAGS += -DGIT_VERSION=\"$(GIT_VERSION)\"
endif

include $(CLEAR_VARS)
LOCAL_MODULE    := retro
LOCAL_SRC_FILES := $(SOURCES_C)
LOCAL_CFLAGS    := $(COREFLAGS) -std=gnu99
LOCAL_LDFLAGS   := -Wl,-version-script=$(LIBRETRO_DIR)/link.T
LOCAL_LDLIBS    := -lz
include $(BUILD_SHARED_LIBRARY)
