# UNIX System Programming Practice

This repository contains weekly exercises and mini-projects for learning UNIX/Linux system programming in C.

## Week 1 — File I/O and File Descriptors

This week focuses on:
- Opening, reading, writing, and closing files using system calls (`open`, `read`, `write`, and `close`).
- Understanding and using file descriptors (FDs).
- Handling errors with `errno`, `perror`, and `strerror`.
- Ensuring that copy code is binary-safe.

## Programs

### copy_file.c
A file copy tool:
- Usage:
  bash

  ./copy source destination ::     Copy to file
  
  ./copy source             ::     Output to stdout
  
### fd_info.c
Opens a file, prints its file descriptor, reads 10 bytes and prints them to standard output in hex.
- Usage:
  bash
  
  ./fd_info file

## Week 2 - Unix Hotel Project

### Features

- Reads hotel rooms from "residents.txt"
- Displays occupied and empty rooms.
- Finds the first empty room and empty room total.
- Allows booking occupants with `setoccupant`.

### Build

```bash
gcc hotel.c rooms.c globals.c -o hotel
