# Lesson 24: Interpreter Lexing: Program Loading and Number Tokenization [:video_camera:](https://youtu.be/NEW_VIDEO_LINK)

This lesson advances the Toy Forth interpreter development, demonstrating essential file I/O for reading the program source, dynamic array management for parsing, and fundamental lexical analysis (lexing) of number tokens.

## File I/O and Program Loading
- **`toyforth.c`** - Uses functions like `fopen()`, `fseek()`, and `fread()` to efficiently load the entire program source code from a file into a memory buffer.

## Dynamic List and Lexical Analysis
- **`toyforth.c`** - Implements robust **dynamic list management** (`listPush`) using `realloc()` to grow the list of parsed tokens on demand.
- Details the process of **number tokenization** (`parseNumber`), including handling leading spaces, signs, and character-by-character consumption of the input stream.
- Shows basic **program compilation flow** (`compile`), converting the raw text into a structured `tfobj` list of tokens.
