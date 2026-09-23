# NasmMakeC

A small Linux x86-64 command-line project manager for NASM assembly programs. NasmMakeC (`nmc`) creates an assembly project layout, assembles and links the project, runs the resulting executable, and can decode the output as integers, floating-point values, or a bitwise dump from the binary output file.

The project is implemented primarily in C, with low-level helper routines written in NASM assembly.

## Features

- Initialize a new assembly project with `src/` and `build/` directories.
- Generate a starter `src/main.asm` program.
- Assemble and link a program with NASM and `ld`.
- Measure a program's execution time.
- Save program output to `build/out.bin`.
- Read binary output as integers, `double` values, or a bitwise byte dump.
- Check whether the expected project files and directories exist.
- Provide assembly helpers for writing 64-bit values, allocating memory, integer square roots, and prime-sieve routines through Linux syscalls.

## Requirements

NasmMakeC currently targets Linux x86-64 and expects the following tools:

- GCC
- NASM
- GNU `ld`
- Standard Linux utilities such as `mkdir`, `touch`, `echo`, and `rm`

The runtime currently uses absolute library paths (`~/nmc/libs/...` and `/root/nmc/libs/`). Clone or install the project as `~/nmc`, or update the paths in `run_config.c` before building.

## Building

From the repository root, compile the C sources into the `nmc` executable:

```bash
gcc -Wall -Wextra -std=c11 \
  main.c arg_interpretation.c print.c read_from_bin.c run_config.c validate.c \
  -o nmc
```

To make the command available from anywhere, place the executable in a directory on your `PATH`, for example:

```bash
sudo install -m 755 nmc /usr/local/bin/nmc
```

If you keep the repository at `~/nmc`, the built-in library paths used by `nmc run` will resolve automatically:

```bash
git clone https://github.com/DataTrashHenri/NASM-Make-Compile.git ~/nmc
cd ~/nmc
gcc -Wall -Wextra -std=c11 \
  main.c arg_interpretation.c print.c read_from_bin.c run_config.c validate.c \
  -o nmc
```

## Usage

Run `nmc help` to display the available commands:

```text
nmc init
nmc run [int|float|bit|all]
nmc status
nmc fuckitall
```

### Initialize a project

```bash
mkdir my-asm-project
cd my-asm-project
nmc init
```

This creates `src/` and `build/`, and writes a sample `src/main.asm` program that exits with status code `42`.

### Check project status

```bash
nmc status
```

This checks for the `src/` and `build/` directories, verifies that `src/main.asm` exists, and lists the available helper libraries.

### Assemble, link, and run

```bash
nmc run
```

The command assembles `src/main.asm` and the helper libraries, links them into `out`, measures one execution, then runs the executable again and stores its output in `build/out.bin`.

To interpret the output file after execution:

```bash
nmc run int
nmc run float
nmc run bit
nmc run all
```

- `int` reads the binary payload as 64-bit integer values.
- `float` reads the binary payload as `double` values.
- `bit` prints each byte as its 8-bit binary representation and marks which bit positions are set.
- `all` runs all three conversions in sequence.

## Project layout

```text
.
├── main.c                 # CLI entry point
├── arg_interpretation.c   # Command validation and dispatch
├── run_config.c           # init, run, status, help, and cleanup operations
├── read_from_bin.c        # Integer, floating-point, and bitwise output decoding
├── validate.c             # Input and project validation
├── print.c                # Console logging and directory listing helpers
├── *.h                    # C interfaces
└── libs/
    ├── alloc.asm          # mmap/munmap allocation helpers
    ├── pout.asm           # 64-bit output helpers
    ├── sieve.asm          # bitset-based sieve routines
    └── sqrt.asm           # integer square root helper
```

## Assembly library API

The bundled NASM libraries export these symbols:

- `alloc_n` — allocate memory using Linux `mmap`.
- `free_n` — release memory using Linux `munmap`.
- `pout64_from_buffer` — write eight bytes from a buffer to standard output.
- `pout64_from_arg` — write an eight-byte value passed in `rdi` to standard output.
- `isqrt` — integer square root helper.
- `sieve_init` — initialize the sieve bitset buffer.
- `generate_base` — generate the base prime set for sieve operations.
- `sieve_chunk` — process a chunk of numbers for primality marking.

## Notes

- The generated executable is named `out` and generated binary output is stored in `build/out.bin`.
- `nmc run` expects the assembly source at `src/main.asm`.
- `nmc run bit` can be used to inspect the binary file bitwise when debugging raw output data.
- The `fuckitall` command removes `build`, `src`, and `out` from the current project. Use it carefully.
- This project directly uses Linux syscalls and is not intended to be portable to Windows or macOS without changes.

## License

No license has been specified for this repository yet.
