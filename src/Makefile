NAME      = app

# Source files directory
SRCS      = $(wildcard *.c)
SRCS     += $(wildcard ../core/cmsis/*.c)
SRCS     += $(wildcard ../drivers/*.c)
SRCS     += $(wildcard ../utilities/*.c)
SRCS     += $(wildcard ../startup/*.c)

# Include directories
INCDIRS   = ../src
INCDIRS  += ../core/cmsis
INCDIRS  += ../drivers
INCDIRS  += ../utilities

# Linker script
LSCRIPT   = ../linkers/gcc_linker.ld

DEFINES   = $(EXDEFINES)

BUILDDIR  = ../build/

CFLAGS    = -ffunction-sections -mlittle-endian -mthumb -mcpu=cortex-m4 -mfloat-abi=hard \
            -mfpu=fpv4-sp-d16 -std=gnu11 -ggdb

ifdef DEBUG
    CFLAGS   += -Og -g3
else
    CFLAGS   += -Os -flto
endif

LFLAGS    = --specs=nano.specs --specs=nosys.specs -nostartfiles -Wl,--gc-sections -T$(LSCRIPT) -lm

WFLAGS    = -Wall -Wextra -Wstrict-prototypes -Werror -Wno-error=unused-function \
            -Wno-error=unused-variable -Wfatal-errors -Warray-bounds -Wno-unused-parameter

GCCPREFIX = arm-none-eabi-
CC        = $(GCCPREFIX)gcc
OBJCOPY   = $(GCCPREFIX)objcopy
OBJDUMP   = $(GCCPREFIX)objdump
SIZE      = $(GCCPREFIX)size

INCLUDE   = $(addprefix -I,$(INCDIRS))

OBJS      = $(addprefix $(BUILDDIR), $(addsuffix .o, $(basename $(SRCS))))
OBJDIR    = $(sort $(dir $(OBJS)))
BIN_NAME  = $(addprefix $(BUILDDIR), $(NAME))

###########
## rules ##
###########

.PHONY: all clean install print_size

all: $(BIN_NAME).elf $(BIN_NAME).bin $(BIN_NAME).s19 $(BIN_NAME).hex $(BIN_NAME).lst print_size post-build

clean:
	@echo "Cleaning up..."
	@$(RM) -r $(wildcard $(BUILDDIR)*)
	@echo "Done cleaning."

install: $(BIN_NAME).hex
	@echo "Programming device..."
	@openocd -d0 -f board/st_nucleo_f4.cfg -c "program $<" -c "reset run" -c "shutdown"
	@echo "Programming complete."

post-build:
	@echo "Cleaning up build files..."
	@$(RM) $(OBJS) $(DEPS)
	@echo "Build files cleaned."

###########################################
# Internal Rules                          #
###########################################

$(OBJS): | $(OBJDIR)

$(OBJDIR):
	@echo "Creating directory $@"
	@mkdir -p $@

$(BUILDDIR)%.o: %.c
	@echo "Compiling $<"
	@$(CC) -MMD -c -o $@ $(INCLUDE) $(DEFINES) $(CFLAGS) $(WFLAGS) $<

$(BUILDDIR)%.o: %.s
	@echo "Assembling $<"
	@$(CC) -c -x assembler-with-cpp -o $@ $(INCLUDE) $(DEFINES) $(CFLAGS) $(WFLAGS) $<

$(BUILDDIR)%.elf: $(OBJS)
	@echo "Linking $@"
	@$(CC) -o $@ $^ $(CFLAGS) $(LFLAGS) -Wl,-Map=$(addsuffix .map, $(basename $@))

%.bin: %.elf
	@$(OBJCOPY) -O binary -S $< $@
	@echo "Binary file generated: $@"

%.s19: %.elf
	@$(OBJCOPY) -O srec -S $< $@
	@echo "S19 file generated: $@"

%.hex: %.elf
	@$(OBJCOPY) -O ihex -S $< $@
	@echo "HEX file generated: $@"

%.lst: %.elf
	@$(OBJDUMP) -d $< > $@
	@echo "LST file generated: $@"

print_size: $(BIN_NAME).elf
	@echo "Generating size..."
	@$(SIZE) $<

DEPS = $(patsubst %.o,%.d,$(OBJS))
-include $(DEPS)

$(OBJS): Makefile

ALLFLAGS=$(INCLUDE) $(DEFINES) $(CFLAGS) $(WFLAGS)
$(BUILDDIR)compiler_flags: force
	@echo '$(ALLFLAGS)' | cmp -s - $@ || echo '$(ALLFLAGS)' > $@
$(OBJS): $(BUILDDIR)compiler_flags

.PHONY: force
force: ;
