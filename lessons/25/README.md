# Lesson 25: Toy Forth 03 [:video_camera:] [:video_camera:](https://youtu.be/-1ZhCgaIPOk?si=3DbtTca--zI2gB9N)

This lesson continues developing the Toy Forth lexer by adding symbol recognition and introduces a recursive function for printing the resulting program structure.

## Lexical Analysis for Symbols
- **`toyforth.c`** - Implements **symbol tokenization** (`parseSymbol`), enabling the lexer to recognize words and common arithmetic operators (like `+`, `-`, `*`).
- Introduces the helper function `is_symbol_char` to check character validity.

## Object Print by Recursion
- **`toyforth.c`** - Develops the **recursive printing function** (`print_object`) to visually inspect the parsed program list, demonstrating how to use recursion.
