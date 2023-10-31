/*
Author: Tyler Tran, Dalton Michiels, Colby Women 
Date: 10-23-2023
Description: CSC222 Programming Project - A small shell with I/O redirections
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// COLORS
#define DEF "\e[0;0m"
#define RED "\e[1;31m"
#define GRN "\e[1;32m"
#define YEL "\e[1;33m"
#define BLU "\e[1;34m"
#define MAG "\e[1;35m"
#define CYN "\e[1;36m"
#define WHT "\e[1;37m"

// GLOBAL VARIABLES
int SIZE = 1024;


// Gets the current directory and stores it in allocated sized memory string
char* GetCurrentDirectory() {
    char* directory = malloc(SIZE);     // String to store the current directory
    getcwd(directory, SIZE);            // Get current working directory and store it in "directory"
    return directory;
};

// Sets the approiate colors for directory and $, then prints them out
void PromptLayout(char* directory) {
    printf(GRN "%s" DEF, directory);    // Makes the text green, prints out the directory, then reset the color
    printf(" $ ");                      // Prints $ at the end
};

// Gets input from stdin and formats it without the newline character
char* PromptInput() {
    char* user_input = malloc(SIZE);                // Allocates memory for "user_input"        
    fgets(user_input, SIZE, stdin);                 // Gets input from stdin and stores it to "user_input"
    user_input[strcspn(user_input, "\n")] = 0;      // Finds the location of newline character and sets it to null, removing it from "user_input"
    return user_input;
};

// Displays the current directory and a prompt
char* CommandPrompt() {
    char* user_directory = GetCurrentDirectory();

    PromptLayout(user_directory);

    return PromptInput();
};

// Makes a struct for the command and its arguments; struct is a user-defined data type
struct ShellCommand {
    char* command;
    char** arguments;
};

struct ShellCommand ParseCommandLine(char* input) {

};

void ExecuteCommand(struct ShellCommand command);

int main() {
    char* input;
    struct ShellCommand command;

    for(;;) {
        input = CommandPrompt();
        //command = ParseCommandLine(input);
        //ExecuteCommand(command);
    }

    exit(0);
}
