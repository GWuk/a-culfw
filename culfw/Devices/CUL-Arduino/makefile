
FORMAT = ihex
OBJDIR = .

F_CPU = 16000000

SRC =           CUL.c\
		../../clib/Descriptors.c                             \
		../../clib/cc1100.c                                  \
		../../clib/cc1101_pllcheck.c                         \
		../../clib/cdcLUFA.c                                 \
		../../clib/clock.c                                   \
		../../clib/belfox.c                                  \
		../../clib/delay.c                                   \
		../../clib/display.c                                 \
		../../clib/stringfunc.c                              \
		../../clib/fncollection.c                            \
		../../clib/ringbuffer.c                              \
		../../clib/fband.c                                   \
		../../clib/helper.c                                  \
		../../clib/rf_send.c                                 \
		../../clib/rf_receive.c                              \
		../../clib/rf_receive_bucket.c                       \
		../../clib/rf_receive_it.c                           \
		../../clib/rf_receive_tcm97001.c                     \
		../../clib/rf_receive_tx3.c                          \
		../../clib/rf_receive_revolt.c                       \
		../../clib/rf_receive_esa.c                          \
		../../clib/rf_receive_hms.c                          \
		../../clib/rf_receive_oregon.c                       \
		../../clib/rf_native.c                               \
		../../clib/lacrosse.c                                \
		../../clib/rf_router.c                               \
		../../clib/rf_asksin.c                               \
		../../clib/rf_moritz.c                               \
		../../clib/rf_rwe.c                                  \
		../../clib/intertechno.c                             \
		../../clib/somfy_rts.c                               \
		../../clib/kopp-fc.c				                				 \
		../../clib/fht.c                                     \
		../../clib/fastrf.c                                  \
		../../clib/ttydata.c                                 \
		../../clib/spi.c                                     \
		../../clib/memory.c                                  \
		../../lufa/Drivers/USB/LowLevel/DevChapter9.c        \
		../../lufa/Drivers/USB/LowLevel/Endpoint.c           \
		../../lufa/Drivers/USB/LowLevel/Host.c               \
		../../lufa/Drivers/USB/LowLevel/HostChapter9.c       \
		../../lufa/Drivers/USB/LowLevel/LowLevel.c           \
		../../lufa/Drivers/USB/LowLevel/Pipe.c               \
		../../lufa/Drivers/USB/HighLevel/Events.c            \
		../../lufa/Drivers/USB/HighLevel/USBInterrupt.c      \
		../../lufa/Drivers/USB/HighLevel/USBTask.c           \
		../../lufa/Drivers/USB/HighLevel/ConfigDescriptor.c  \


LUFA_OPTS  = -D USE_NONSTANDARD_DESCRIPTOR_NAMES
LUFA_OPTS += -D NO_STREAM_CALLBACKS
LUFA_OPTS += -D USB_DEVICE_ONLY
LUFA_OPTS += -D FIXED_CONTROL_ENDPOINT_SIZE=8
LUFA_OPTS += -D FIXED_NUM_CONFIGURATIONS=1
LUFA_OPTS += -D USE_FLASH_DESCRIPTORS
LUFA_OPTS += -D F_CLOCK=$(F_CPU)UL
LUFA_OPTS += -D USE_STATIC_OPTIONS="(USB_DEVICE_OPT_FULLSPEED | USB_OPT_REG_ENABLED | USB_OPT_AUTO_PLL)"
CFLAGS  = -D$(TARGET)
CFLAGS += -D$(FREQUENCE)
CFLAGS += -DF_CPU=$(F_CPU)UL
CFLAGS += -DLUFA $(LUFA_OPTS)
CFLAGS += -Os
CFLAGS += -funsigned-char       #   12 Byte (shorter code)
CFLAGS += -funsigned-bitfields  #    0
CFLAGS += -ffunction-sections   # 2600
CFLAGS += -fpack-struct         #    0
CFLAGS += -fshort-enums         #    0
CFLAGS += -mcall-prologues      #  130
CFLAGS += -finline-limit=20     # 0=>150 10=>12 20=>0 (0: RFR won't work!)
CFLAGS += -Wall
CFLAGS += -Wstrict-prototypes
CFLAGS += -Wundef
CFLAGS += -Wa,-adhlns=$(<:%.c=$(OBJDIR)/%.lst)
CFLAGS += -I../../lufa -I../../clib
CFLAGS += -std=gnu99
#CFLAGS += -Wunreachable-code
GENDEPFLAGS = -MMD -MP -MF .dep/$(@F).d
ALL_CFLAGS = -mmcu=$(MCU) -I. $(CFLAGS) $(GENDEPFLAGS)

EXTMEMOPTS =
LDFLAGS = -Wl,-Map=$(TARGET)$(FREQUENCE).map,--cref
LDFLAGS += -Wl,--relax
LDFLAGS += -Wl,--gc-sections
LDFLAGS += $(EXTMEMOPTS)

CC = avr-gcc
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
SIZE = avr-size
AR = avr-ar rcs
NM = avr-nm
REMOVE = rm -f
REMOVEDIR = rm -rf
COPY = cp

MSG_SIZE = Size:
MSG_FLASH = Creating load file for Flash:
MSG_EEPROM = Creating load file for EEPROM:
MSG_EXTENDED_LISTING = Creating Extended Listing:
MSG_SYMBOL_TABLE = Creating Symbol Table:
MSG_LINKING = Linking:
MSG_COMPILING = Compiling C:
MSG_CLEANING = Cleaning project:

OBJ = $(SRC:%.c=$(OBJDIR)/%.o)

ifeq ($(GCC_TARGET),$(filter $(GCC_TARGET), CUL_ARDUINO))
SRC += ../../clib/rf_mbus.c ../../clib/mbus/manchester.c ../../clib/mbus/3outof6.c ../../clib/mbus/mbus_packet.c ../../clib/mbus/crc.c
endif

all:
	make TARGET=CUL_ARDUINO FREQUENCE=_433MHZ MCU=atmega32u4 mostly_clean build size
	make TARGET=CUL_ARDUINO FREQUENCE=_868MHZ MCU=atmega32u4 mostly_clean build size

build: elf hex eep lss sym

elf: $(TARGET)$(FREQUENCE).elf
hex: $(TARGET)$(FREQUENCE).hex
eep: $(TARGET)$(FREQUENCE).eep
lss: $(TARGET)$(FREQUENCE).lss
sym: $(TARGET)$(FREQUENCE).sym


ELFSIZE = $(SIZE) --format=avr --mcu=$(MCU) $(TARGET)$(FREQUENCE).elf

size:
	@if test -f $(TARGET)$(FREQUENCE).elf; then echo $(MSG_SIZE); $(ELFSIZE); \
	2>/dev/null; echo; fi


usbprogram:
	@echo 'specify one of: avdude_arduino433Mhz avdude_arduino868Mhz'

avdude_arduino868Mhz: TARGET=CUL_ARDUINO
avdude_arduino868Mhz: FREQUENCE=_868MHZ
avdude_arduino868Mhz: MCU=atmega32u4
avdude_arduino868Mhz: PORT=/dev/ttyACM0
avdude_arduino868Mhz: BAUD=57600
avdude_arduino868Mhz: do_avdude

avdude_arduino433Mhz: TARGET=CUL_ARDUINO
avdude_arduino433Mhz: FREQUENCE=_433MHZ
avdude_arduino433Mhz: MCU=atmega32u4
avdude_arduino433Mhz: PORT=/dev/ttyACM0
avdude_arduino433Mhz: BAUD=57600
avdude_arduino433Mhz: do_avdude


do_avdude:
	avrdude -p$(MCU) -cavr109 -P$(PORT) -b$(BAUD) -D -Uflash:w:./$(TARGET)$(FREQUENCE).hex:i

%.hex: %.elf
	@echo $(MSG_FLASH) $@
	@$(OBJCOPY) -O $(FORMAT) -R .eeprom $< $@

%.eep: %.elf
	@echo $(MSG_EEPROM) $@
	@-$(OBJCOPY) -j .eeprom --set-section-flags=.eeprom="alloc,load" \
	--change-section-lma .eeprom=0 --no-change-warnings -O $(FORMAT) $< $@ || exit 0

%.lss: %.elf
	@echo $(MSG_EXTENDED_LISTING) $@
	@$(OBJDUMP) -h -z -S $< > $@

%.sym: %.elf
	@echo $(MSG_SYMBOL_TABLE) $@
	@$(NM) -n $< > $@



.SECONDARY : $(TARGET)$(FREQUENCE).elf
.PRECIOUS : $(OBJ)
%.elf: $(OBJ)
	@echo $(MSG_LINKING) $@
	@$(CC) $(ALL_CFLAGS) $^ --output $@ $(LDFLAGS)


$(OBJDIR)/%.o : %.c
	@echo $(MSG_COMPILING) $<
	@$(CC) -c $(ALL_CFLAGS) $< -o $@

mostly_clean:
	@echo $(MSG_CLEANING)
	@$(REMOVE) $(TARGET)$(FREQUENCE).hex
	@$(REMOVE) $(TARGET)$(FREQUENCE).eep
	@$(REMOVE) $(TARGET)$(FREQUENCE).cof
	@$(REMOVE) $(TARGET)$(FREQUENCE).elf
	@$(REMOVE) $(TARGET)$(FREQUENCE).map
	@$(REMOVE) $(TARGET)$(FREQUENCE).sym
	@$(REMOVE) $(TARGET)$(FREQUENCE).lss
	@$(REMOVE) $(SRC:%.c=$(OBJDIR)/%.o)
	@$(REMOVE) $(SRC:%.c=$(OBJDIR)/%.lst)
	@$(REMOVE) $(SRC:.c=.s)
	@$(REMOVE) $(SRC:.c=.d)
	@$(REMOVE) $(SRC:.c=.i)

clean: mostly_clean
	@$(REMOVE) *.hex
	@$(REMOVE) *.eep
	@$(REMOVE) *.cof
	@$(REMOVE) *.elf
	@$(REMOVE) *.map
	@$(REMOVE) *.sym
	@$(REMOVE) *.lss
	@$(REMOVEDIR) .dep

$(shell mkdir $(OBJDIR) 2>/dev/null)

-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)
