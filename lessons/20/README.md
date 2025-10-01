# Lesson 21: I/O Buffering and Memory Mapping [:video_camera:](https://youtu.be/yKavhObop5I?si=TJ0Nfhkw5Cc-ZnJg)

This lesson demonstrates I/O buffering mechanisms and memory-mapped file access, understanding the difference between buffered and unbuffered output and showing how to efficiently handle files through memory mapping.

## I/O Buffering and Performance
- **`stdio.c`** - Buffering behavior in standard I/O, comparing buffered functions (`printf()`, `putchar()`) with unbuffered system calls (`write()`), and demonstrating buffer control with `fflush()`.

## Memory-Mapped Files
- **`mmap.c`** - File access through memory mapping using `mmap()`, demonstrating how to map files into process memory for efficient read/write operations.
