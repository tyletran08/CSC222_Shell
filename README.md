# This is the Developmental Branch, used to put new things and break things!

# CSC222 Final Project

### Tyler Tran, Dalton Michiels, Colby Women

This is our final project for CSC222 which is making a shell!

---

## Table of Contents
* [Summary](#Summary)
* [Features](#Features)
* [Prerequisites](#Prerequisites)
* [Compiling and Running](#Compiling-and-Running)

<a name="Summary"></a>
## Summary

This C program is a basic implementation of a shell in C. It provides a pseudo command prompt and allows users to enter commands, which are then executed by the by the C program.

<a name="Features"></a>
## Features

- Can execute:
    - Basic shell commands like "cd", "exit", "wc", etc.
    - External application commands like "neofetch" or "lolcat"

- Has simple I/O redirection:
    - "<" input from file
    - ">" output from file

- Has built-in error handling

- Always shows current directory

- Looping shell via fork command in C

<a name="Prerequisites"></a>
## Prerequisites

- [**C**](https://www.w3schools.in/c-programming/install)
- [**gcc**](https://gcc.gnu.org/install/)

<a name="Compiling-and-Running"></a>
## Compiling and Running

**Clone and enter folder directory:**

```
git clone https://github.com/tyletran08/CSC222_Shell/ && cd CSC222_Shell/src
```

**Compile the C program using gcc:**

```
gcc main.c -o shell
```

**Run the C program:**

```
./shell
```