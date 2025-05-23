# Lesson 01

## Coding

### hello_world.c

`hello_world.c` contains a simple C program that prints "Hello world" to the terminal.

To execute the code, you first need to compile it using a suitable compiler for your system (e.g., `gcc`, `cc`). For instance, running `gcc hello_world.c` generates a binary file, usually named `a.out`.

You can then execute the binary using `./a.out`.

To get more information about the binary file, use the `file a.out` command. You can view the contents of the file with the `hexdump` command. For better readability, run `hexdump -C a.out | less`.

You can also generate the assembly code with the `-S` flag: `gcc -S hello_world.c`. This produces a file named `hello_world.s`, which contains the assembly instructions corresponding to the original C code.

The compiler optimization level can be set using the `-On` flag, where `n` is an integer from 0 to 3. For example, compiling with `gcc -O2 -S hello_world.c` might result in using the `puts` function instead of `printf` to enhance performance. This is because `puts` is generally more efficient and automatically appends a newline (`
`), so the compiler removes `\n` from the end of the string when `puts` is used.

The directive `#include <stdio.h>` ensures that the standard input/output library is loaded before compilation. C code has a minimal set of core keywords (e.g., `int`, `return`); all other functionalities must be included through appropriate libraries. Typically, header files (`.h`) are used to store code that provides auxiliary functions and utilities, which can be shared across multiple C files.

### hello_world2.c

`hello_world2.c` demonstrates a simple example of using the `#include` directive.

Although the output is identical to that of `hello_world.c`, this version invokes the print function via `#include "file.c"`.

### file.c

`file.c` simply prints the string `Hello world\n`.

---

- The `man` command followed by a C function name (e.g., `man printf`) displays its documentation.
- The `#include` directive replaces the corresponding line with the contents of the specified file before compilation.
