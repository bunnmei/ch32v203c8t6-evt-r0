NAME = hello_usart
OBJS = \
	ch32v20x_it.o \
	system_ch32v20x.o \
	main.o 

TOOLCHAIN = riscv32-unknown-elf

CH32V20X_SDK=../../SRC


SYSOBJS = \
	ch32v20x_gpio.o \
	ch32v20x_usart.o \
	ch32v20x_rcc.o \
	ch32v20x_dbgmcu.o \
	ch32v20x_misc.o \
	ch32v20x_adc.o \
	ch32v20x_dma.o \
	debug.o \
	startup_ch32v20x_D6.o

INCLUDES = \
	-I $(CH32V20X_SDK)/Core \
	-I $(CH32V20X_SDK)/Peripheral/inc \
	-I $(CH32V20X_SDK)/Debug \
	-I .

CFLAGS = \
	$(INCLUDES) \
	-fsigned-char \
	-ffunction-sections \
	-fdata-sections \
	-fno-common \
	-Os -g

# CFLAGS = $(INCLUDES) -fsigned-char -ffreestanding \
#         -Wall -g -O0

TARGET_ARCH = \
	-msmall-data-limit=8 \
	-msave-restore \
	-march=rv32imac_zicsr \
	-mabi=ilp32

LDFLAGS = \
	-nostartfiles \
	--specs=nano.specs \
	--specs=nosys.specs \
	-Wl,--gc-sections \
	-Wl,-Map,"$(NAME).map" \
	-T $(CH32V20X_SDK)/Ld/Link.ld

CC = $(TOOLCHAIN)-gcc
OBJCOPY = $(TOOLCHAIN)-objcopy
OBJDUMP = $(TOOLCHAIN)-objdump
SIZE = $(TOOLCHAIN)-size

all: $(NAME).elf $(NAME).hex $(NAME).lst $(NAME).siz

$(NAME).elf: $(OBJS) $(SYSOBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(TARGET_ARCH) $(OBJS) $(SYSOBJS) -o $@

$(NAME).hex: $(NAME).elf
	$(OBJCOPY) -O ihex $< $@

$(NAME).lst: $(NAME).elf
	$(OBJDUMP) --all-headers --demangle --disassemble $< > $@

$(NAME).siz: $(NAME).elf
	$(SIZE) --format=berkeley $< > $@

debug.o: $(CH32V20X_SDK)/Debug/debug.c
	$(COMPILE.c) $(OUTPUT_OPTION) $<

ch32v20x_misc.o: $(CH32V20X_SDK)/Peripheral/src/ch32v20x_misc.c
	$(COMPILE.c) $(OUTPUT_OPTION) $<
ch32v20x_dbgmcu.o: $(CH32V20X_SDK)/Peripheral/src/ch32v20x_dbgmcu.c
	$(COMPILE.c) $(OUTPUT_OPTION) $<
ch32v20x_rcc.o: $(CH32V20X_SDK)/Peripheral/src/ch32v20x_rcc.c
	$(COMPILE.c) $(OUTPUT_OPTION) $<
ch32v20x_gpio.o: $(CH32V20X_SDK)/Peripheral/src/ch32v20x_gpio.c
	$(COMPILE.c) $(OUTPUT_OPTION) $<
ch32v20x_usart.o: $(CH32V20X_SDK)/Peripheral/src/ch32v20x_usart.c
	$(COMPILE.c) $(OUTPUT_OPTION) $<
ch32v20x_exti.o: $(CH32V20X_SDK)/Peripheral/src/ch32v20x_exti.c
	$(COMPILE.c) $(OUTPUT_OPTION) $<
ch32v20x_adc.o: $(CH32V20X_SDK)/Peripheral/src/ch32v20x_adc.c
	$(COMPILE.c) $(OUTPUT_OPTION) $<
ch32v20x_dma.o: $(CH32V20X_SDK)/Peripheral/src/ch32v20x_dma.c
	$(COMPILE.c) $(OUTPUT_OPTION) $<

startup_ch32v20x_D6.o: $(CH32V20X_SDK)/Startup/startup_ch32v20x_D6.s
	$(CC) $(CFLAGS) $(TARGET_ARCH) -c -o $@ $<

clean:
	rm -f *.o
	rm -f *.elf *.map
	rm -f *.hex *.lst *.siz