# This is the Developmental Branch, used to put new things and break things!

# CSC222 Final Project

### Tyler Tran, Colby Willman, Dalton Michiels

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
    - External application commands like "neofetch", "lolcat", "git", etc.

- Has simple I/O redirection:
    - "<" input from file
    - ">" output from file

- Has built-in error handling

- Always shows current directory

- Looping shell via main and fork command in C

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

# README.txt

### TechShell Project
This program is a simple shell implemented in C. It provides a command line interface for the user to interact with the operating system.

### Program Stucture
The main function of the program is structured as follows:
```C
int main() {
    char* input;
    struct ShellCommand command;

    // Infinite loop
    for(;;) {
        input = CommandPrompt();
        command = ParseCommandLine(input);
        ExecuteCommand(command);
    }

    exit(0);
}
```

### Functionality
The program runs in an infinite loop, continuously prompting the user for input, parsing that input into a command and its arguments, and then executing the command.

Here's a brief description of the main functions:
- CommandPrompt(): This function displays a command prompt to the user and returns the command that the user enters.
- ParseCommandLine(char* input): This function takes the user's input as an argument, parses it into a command and its arguments, and returns a struct ShellCommand representing this.
- ExecuteCommand(struct ShellCommand command): This function takes a struct ShellCommand as an argument and executes the command.

### Usage
To use the program, simply run it in your terminal. You will be presented with a command prompt where you can enter commands. The program will continue to prompt for and execute commands until it is manually terminated.

### Note
This is a simple shell program and may not support all the features of a full-fledged shell, such as piping, or background processes. It's intended as a basic example of how a shell works.