AS := as
CC := gcc
LD := ld

# -mgeneral-regs-only -mno-red-zone are for interrupt handlers and perhaps
# those flags should be set specifically for that compilation unit only
CFLAGS = -m32 -std=gnu99 -ffreestanding -O2 -Wall -Wextra -mgeneral-regs-only -mno-red-zone

SRC_DIR = src
BUILD_DIR = build
KERNEL = discoveryos-kernel

all: $(KERNEL)

C_SOURCES := $(wildcard $(SRC_DIR)/*.c)
ASM_SOURCES := $(wildcard $(SRC_DIR)/*.s)

OBJS = $(C_SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
OBJS += $(ASM_SOURCES:$(SRC_DIR)/%.s=$(BUILD_DIR)/%.o)
DEPENDS := $(patsubst %.o,%.d,$(OBJS))
-include $(DEPENDS)

$(KERNEL): $(OBJS)
	ld -m elf_i386 -T linker.ld $(OBJS) -o $(KERNEL) -nostdlib
	grub-file --is-x86-multiboot $(KERNEL)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/%.h
	@mkdir -p $(@D)
	$(CC) -MMD -MP -c -o $@ $< $(CFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.s
	@mkdir -p $(@D)
	$(AS) --32 $< -o $@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(KERNEL)

.PHONY: run
run: $(KERNEL)
	scripts/discoveryos-run.sh

.PHONY: debug
debug: $(KERNEL)
	scripts/discoveryos-debug.sh
