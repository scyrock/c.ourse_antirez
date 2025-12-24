# Lesson 29: Toy Forth 06 [:video_camera:](https://youtu.be/nHzlRqPnlrE?si=x5cn5W6UbYHauTyf)

In this lesson, the Toy Forth interpreter is executed for the first time. The process involves executing the parsed program, manipulating the Data Stack, and running native C functions registered as Forth words.

## Stack Manipulation and Execution Loop
- **`toyforth.c`** - Implements the core **stack operations** (`listPopType`, `ctxStackPush`) to safely move data to and from the interpreter's stack.
- Defines the **main execution loop** (`exec`) which iterates through the parsed program list:
    - If the token is a **literal** (int, string), it is pushed onto the stack.
    - If the token is a **symbol** (like `+`), the corresponding function is looked up in the dictionary and executed via `callSymbol`.
- Implements `basicMathFunctions` to handle arithmetic operations (`+`, `-`, `*`) by popping operands, calculating results, and pushing them back, completing the cycle of a working interpreter.

## Building and Running
- **`Makefile`** - A standard build script to compile the interpreter.
- **`program.tf`** - A simple test program (`5 10 + 8 +`) to verify the arithmetic logic.
