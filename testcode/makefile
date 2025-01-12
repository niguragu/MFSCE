CC       = riscv64-unknown-elf-gcc
OBJCOPY  = riscv64-unknown-elf-objcopy
CFLAGS   = -march=rv32i -mabi=ilp32
LDFLAGS  = -march=rv32i -mabi=ilp32 -T link.ld -static -nostartfiles -nostdlib

ELF      = test.elf
TEXT_BIN = test_text.bin
RO_BIN   = test_rodata.bin
DATA_BIN = test_data.bin

ASM_SRC  = start.S
C_SRC    = test.c

OBJ_ASM  = start.o
OBJ_C    = test.o

.PHONY: all clean

all: $(ELF) $(TEXT_BIN) $(RO_BIN) $(DATA_BIN)

$(OBJ_ASM): $(ASM_SRC)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_C): $(C_SRC)
	$(CC) $(CFLAGS) -c -o $@ $<

$(ELF): $(OBJ_ASM) $(OBJ_C) link.ld
	$(CC) $(LDFLAGS) -o $@ $(OBJ_ASM) $(OBJ_C)

$(TEXT_BIN): $(ELF)
	$(OBJCOPY) -O binary --only-section=.text $(ELF) $(TEXT_BIN)

$(RO_BIN): $(ELF)
	$(OBJCOPY) -O binary --only-section=.rodata $(ELF) $(RO_BIN)

$(DATA_BIN): $(ELF)
	$(OBJCOPY) -O binary --only-section=.data $(ELF) $(DATA_BIN)

clean:
	rm -f $(OBJ_ASM) $(OBJ_C) $(ELF) $(TEXT_BIN) $(RO_BIN) $(DATA_BIN)
