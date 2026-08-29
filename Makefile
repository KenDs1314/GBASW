#---------------------------------------------------------------------------------
# Makefile base para homebrew de Nintendo Switch (libnx)
#---------------------------------------------------------------------------------
ifeq ($(strip $(DEVKITPRO)),)
$(error "Please set DEVKITPRO in your environment. export DEVKITPRO=<path to>/devkitpro")
endif

TOPDIR ?= $(CURDIR)
include $(DEVKITPRO)/libnx/switch_rules

#---------------------------------------------------------------------------------
# TARGET   : nombre del .nro resultante
# BUILD    : carpeta intermedia de compilación
# SOURCES  : carpetas con codigo fuente
# DATA     : carpetas con datos crudos
# INCLUDES : carpetas con headers
# ROMFS    : carpeta que se empaqueta dentro del .nro (iconos, assets, NO roms)
#---------------------------------------------------------------------------------
TARGET      := gba-emu-switch
BUILD       := build
SOURCES     := source source/core source/platform
DATA        := data
INCLUDES    := source source/core source/platform
ROMFS       := romfs

APP_TITLE       := GBA Emu Switch
APP_AUTHOR      := TuNombre
APP_VERSION     := 0.1.0
# APP_ICON      := icon.jpg   # descomentar cuando tengas un icono de 256x256

#---------------------------------------------------------------------------------
ARCH    := -march=armv8-a -mtune=cortex-a57 -mtp=soft -fPIE

CFLAGS  := -g -Wall -O2 -ffunction-sections \
           $(ARCH) $(DEFINES)

CFLAGS  += $(INCLUDE) -D__SWITCH__

CXXFLAGS    := $(CFLAGS) -fno-rtti -fno-exceptions -std=gnu++20

ASFLAGS := -g $(ARCH)
LDFLAGS := -specs=$(DEVKITPRO)/libnx/switch.specs -g $(ARCH) -Wl,-Map,$(notdir $*.map)

LIBS := -lnx

LIBDIRS := $(PORTLIBS) $(LIBNX)

#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------

export OUTPUT   :=  $(CURDIR)/$(TARGET)
export TOPDIR   :=  $(CURDIR)

export VPATH    :=  $(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
                     $(foreach dir,$(DATA),$(CURDIR)/$(dir))

export DEPSDIR  :=  $(CURDIR)/$(BUILD)

CFILES      :=  $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES    :=  $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES      :=  $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
BINFILES    :=  $(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.*)))

export LD   :=  $(CXX)

export OFILES_BIN  :=  $(addsuffix .o,$(BINFILES))
export OFILES_SRC   :=  $(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(SFILES:.s=.o)
export OFILES   :=  $(OFILES_BIN) $(OFILES_SRC)
export HFILES_BIN   :=  $(addsuffix .h,$(subst .,_,$(BINFILES)))

export INCLUDE  :=  $(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \
                     $(foreach dir,$(LIBDIRS),-I$(dir)/include) \
                     -I$(CURDIR)/$(BUILD)

export LIBPATHS :=  $(foreach dir,$(LIBDIRS),-L$(dir)/lib)

ifeq ($(strip $(ROMFS)),)
else
	export NROFLAGS += --romfsdir=$(CURDIR)/$(ROMFS)
endif

ifneq ($(APP_TITLE),)
	NROFLAGS += --nacp=$(CURDIR)/$(TARGET).nacp
endif

.PHONY: $(BUILD) clean all

all: $(BUILD)

$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

clean:
	@echo clean ...
	@rm -fr $(BUILD) $(TARGET).nro $(TARGET).nacp $(TARGET).elf

else

DEPENDS :=  $(OFILES:.o=.d)

all : $(OUTPUT).nro

ifeq ($(strip $(APP_TITLE)),)
$(OUTPUT).nro : $(OUTPUT).elf
else
$(OUTPUT).nro : $(OUTPUT).elf $(OUTPUT).nacp
endif

$(OUTPUT).elf : $(OFILES)

%.nacp:
	nacptool --create "$(APP_TITLE)" "$(APP_AUTHOR)" "$(APP_VERSION)" $@

-include $(DEPENDS)

endif
