# Lesson 26: Toy Forth 04 [:video_camera:] [:video_camera:](https://youtu.be/oMj3N6jYIUU?si=uMguhWqvldvB4FXm)

This lesson builds the core foundation of the Toy Forth interpreter's runtime, implementing essential memory management via **reference counting** and defining the main program execution loop.

## Runtime Context and Function Table
- **`toyforth.c`** - Defines the full `tfctx` (context) structure, which holds the **data stack** and the **function table** (`FunctionTableEntry`), enabling lookup for executable words.
- Implements `createContext` to properly initialize the runtime environment.

## Comprehensive Memory Management (Reference Counting)
- **`toyforth.c`** - Implements the fundamental **reference counting** functions: `retain`, `release`, and `freeObject`. This system ensures objects are only destroyed when no longer referenced, crucial for a garbage-collection-free language.

## Interpreter Execution Loop
- **`toyforth.c`** - Implements the main `exec` function, which iterates over the parsed program.
- Establishes the core **interpreter logic**: if a word is a **literal** (like a number), it's pushed onto the `ctx->stack` and retained; if it's a **symbol** (like a command), a placeholder `callSymbol` function is executed.
