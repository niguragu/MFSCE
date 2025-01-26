# MFSCE
This is an emulator created to deepen the understanding of RISC-V. It can only execute arithmetic instructions of the RV32I subset.

It extracts and executes the `.text`, `.rodata`, and `.data` sections from ELF files compiled for Newlib using the
[riscv-gnu-toolchain](https://github.com/riscv-collab/riscv-gnu-toolchain)
Programs that place data outside of the `.rodata` and `.data` sections cannot be executed.

Since MMIO is implemented, it is possible to pseudo-output characters via the terminal.

## Testcode Build

### Using Make Build

```
cd testcode
make
```

clean
```
make clean
```
### Manual Build

```
riscv64-unknown-elf-gcc -march=rv32imac -mabi=ilp32 -c -o start.o start.S
riscv64-unknown-elf-gcc -march=rv32imac -mabi=ilp32 -c -o test.o test.c
riscv64-unknown-elf-gcc -march=rv32imac -mabi=ilp32 -T link.ld -static -nostartfiles -o test.elf start.o test.o
riscv64-unknown-elf-objcopy -O binary --only-section=.text test.elf test_text.bin
riscv64-unknown-elf-objcopy -O binary --only-section=.rodata test.elf test_rodata.bin
riscv64-unknown-elf-objcopy -O binary --only-section=.data test.elf test_data.bin
```

## Software Build

```
cd build
cmake -GNinja -DCMAKE_CXX_COMPILER=/usr/bin/g++ ..
```

## LICENSE

[MIT License](https://github.com/niguragu/MFSCE/blob/main/LICENSE)
