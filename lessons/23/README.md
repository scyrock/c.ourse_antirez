# Lesson 23: Toy Forth 01 [:video_camera:](https://youtu.be/HjXBXBgfKyk?si=00UCgBEptcVozFZy)

This lesson begins the development of a Toy Forth interpreter, focusing on creating a central polymorphic object data structure, memory management helpers, and execution context definition.

## Polymorphism with Unions and Structs
- **`toyforth.c`** - Defines the core `tfobj` structure using a **union** to hold different data types (int, string, list) within a single memory space, achieving **polymorphic data structure** behavior.
- Demonstrates defining custom object types with `#define` constants.

## Interpreter Foundation
- Defines **context structures** (`tfparser` and `tfctx`) to manage the program state and execution context.
- Implements factory functions (`createIntObject`, `createStringObject`, etc.) for object creation.
- Uses **reference counting** (`refcount` field) for manual memory management, a common pattern in language runtimes.

## Defensive Memory Allocation
- Implements an **allocation wrapper** (`xmalloc`) to handle out-of-memory errors gracefully, demonstrating robust programming practice.
