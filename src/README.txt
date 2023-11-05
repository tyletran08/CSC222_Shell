NAMES : TYLER TRAN
        COLBY WILLMAN
        DALTON MICHIELS

READ ME For TechShell Project
This program is a simple shell implemented in C. It provides a command line interface for the user to interact with the operating system.

Program Stucture
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

Functionality
The program runs in an infinite loop, continuously prompting the user for input, parsing that input into a command and its arguments, and then executing the command.

Here's a brief description of the main functions:
- CommandPrompt(): This function displays a command prompt to the user and returns the command that the user enters.
- ParseCommandLine(char* input): This function takes the user's input as an argument, parses it into a command and its arguments, and returns a struct ShellCommand representing this.
- ExecuteCommand(struct ShellCommand command): This function takes a struct ShellCommand as an argument and executes the command.

Usage
To use the program, simply run it in your terminal. You will be presented with a command prompt where you can enter commands. The program will continue to prompt for and execute commands until it is manually terminated.

Note
This is a simple shell program and may not support all the features of a full-fledged shell, such as piping, or background processes. It's intended as a basic example of how a shell works.