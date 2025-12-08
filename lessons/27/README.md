# Lesson 27: Toy Forth 04 [:video_camera:] [:video_camera:](https://youtu.be/C4AHEK3fSjg?si=XbrZO5yu_CF27-hH)

This lesson focuses on building the interpreter's dictionary, implementing object comparison, and laying the groundwork for executing native C functions as Forth words.

## Interpreter Dictionary (Function Table)
- **`toyforth.c`** - Implements the core **Function Table management**: `registerFunction` dynamically expands the table using `xrealloc`, and `getFunctionByName` performs lookups to resolve symbolic words.
- Introduces `registerCFunction` to expose native C functions (like arithmetic operations) to the interpreter context.

## String and Symbol Comparison
- **`toyforth.c`** - Details the implementation of `compareStringObject` to compare two string or symbol objects using `memcmp`, handling length differences to maintain lexicographical order.

## Native Word Preparation
- **`toyforth.c`** - Lays out the `basicMathFunction` structure, demonstrating how native C functions will read arguments from the stack, perform an operation based on the symbolic word (e.g., `+`, `-`), and push the result back onto the stack.
