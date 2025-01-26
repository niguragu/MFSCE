# MFSCE
This is an emulator created to deepen the understanding of RISC-V. It can only execute arithmetic instructions of the RV32I subset.

It extracts and executes the `.text`, `.rodata`, and `.data` sections from ELF files compiled for Newlib using the
[riscv-gnu-toolchain](https://github.com/riscv-collab/riscv-gnu-toolchain)
Programs that place data outside of the `.rodata` and `.data` sections cannot be executed.

Since MMIO is implemented, it is possible to pseudo-output characters via the terminal.

## Testcode Build

```
cd testcode
make
```

clean
```
make clean
```

## Software Build

```
cd build
cmake -GNinja -DCMAKE_CXX_COMPILER=/usr/bin/g++ ..
```

## LICENSE

[MIT License](https://github.com/niguragu/MFSCE/blob/main/LICENSE)
