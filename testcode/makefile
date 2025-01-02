CC = riscv64-unknown-linux-gnu-gcc
LD = riscv64-unknown-linux-gnu-ld
OBJCOPY = riscv64-unknown-elf-objcopy

CFLAGS = -march=rv32ima -mabi=ilp32 -O2
ASFLAGS = -march=rv32i -mabi=ilp32

START_S = start.S
TEST_C = test.c

START_O = start.o
TEST_O = test.o

OBJS = $(START_O) $(TEST_O)

LINK_SCRIPT = link.ld

ELF = test.elf
TEXT_BIN = test_text.bin
RODATA_BIN = test_rodata.bin
DATA_BIN = test_data.bin

all: $(TEXT_BIN) $(RODATA_BIN) $(DATA_BIN)

$(START_O): $(START_S)
	$(CC) $(ASFLAGS) -c -o $@ $<

$(TEST_O): $(TEST_C)
	$(CC) $(CFLAGS) -c -o $@ $<

$(ELF): $(OBJS) $(LINK_SCRIPT)
	$(LD) $(OBJS) -T $(LINK_SCRIPT) -static -o $@

$(TEXT_BIN): $(ELF)
	$(OBJCOPY) -O binary --only-section=.text $< $@

$(RODATA_BIN): $(ELF)
	$(OBJCOPY) -O binary --only-section=.rodata $< $@

$(DATA_BIN): $(ELF)
	$(OBJCOPY) -O binary --only-section=.data $< $@

clean:
	rm -f $(START_O) $(TEST_O) $(ELF) $(TEXT_BIN) $(RODATA_BIN) $(DATA_BIN)

.PHONY: all clean
