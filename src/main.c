/*
Author: Tyler Tran, Colby Willman, Dalton Michiels
Date: 10-23-2023
Description: CSC222 Programming Project - A small shell with I/O redirections
*/

// LIBRARIES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>
#include <errno.h>

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

/*
    FUNCTION
*/

// Makes a struct for the command and its arguments; struct is a user-defined data type
struct ShellCommand {
    char* command;
    char** arguments;
};

// Prints out the error message and exits the program
void ErrorHandling(int errortype) {

    // errno is a global variable that stores the error code
    int error = errno;

    // strerror returns a string describing the error code
    printf(RED "Error [%d]: %s\n" DEF, error, strerror(errno));

    // if it's cd error, don't exit because it is not a child process
    if (errortype == 1) {
        return;

    }

    // Exits the child
    exit(0);
};

// Gets the current directory and stores it in allocated sized memory string
char* GetCurrentDirectory() {

    // String to store the current directory
    char* directory = malloc(SIZE);

    // Get current working directory and store it in "directory"     
    getcwd(directory, SIZE);

    return directory;
};

// Sets the approiate colors for directory and $, then prints them out
void PromptLayout(char* directory) {
    printf(GRN "%s" DEF, directory);    // Makes the text green, prints out the directory, then reset the color
    printf(" $ ");                      // Prints $ at the end
};

// Gets input from stdin and formats it without the newline character
char* PromptInput() {

    // Allocates memory for "user_input"
    char* user_input = malloc(SIZE);

    // Gets input from stdin and stores it to "user_input"                        
    fgets(user_input, SIZE, stdin);

    // Finds the location of newline character and sets it to null, removing it from "user_input"                 
    user_input[strcspn(user_input, "\n")] = 0;

    return user_input;
};

// Tries to change current directory to the given directory
void ExecuteCD(char* directory) {
    
    // If no directory is given, change directory to home directory
    if (directory == NULL) {
        chdir(getenv("HOME"));
    }
        
    // chdir changes directory, returns -1 if there was an error
    else if (chdir(directory) == -1) {
        ErrorHandling(1);
    }
};

// Redirects stdin and stdout to files
void Redirection(struct ShellCommand command) {

    // Default to stdin
    int fd_in = STDIN_FILENO;

    // Default to stdout;
    int fd_out = STDOUT_FILENO;

    // Iterate through arguments until null
    for (int i = 0; command.arguments[i] != NULL; i++) {

        // If the argument is "<", then redirect stdin to the next argument
        if (strcmp(command.arguments[i], "<") == 0) {

            // Get the argument after "<"
            char* input_file = command.arguments[i+1];

            // Opens input file as a file stream
            FILE* infile = fopen(input_file, "r");

            // If there was an error opening the file, print the error and exit
            if (infile == NULL) {
                ErrorHandling(0);
            }

            // Get the file descriptor of the file stream
            fd_in = fileno(infile);

            // Redirect stdin to the file descriptor
            dup2(fd_in, STDIN_FILENO);

            // Close the file stream
            fclose(infile);

            // Shift the arguments to the left by 2
            for (int j = i; command.arguments[j] != NULL; j++) {
                command.arguments[j] = command.arguments[j+2];
            }
            // Decrement i so that the next argument is checked
            i--;
        }

        // If the argument is ">", then redirect stdout to the next argument
        else if (strcmp(command.arguments[i], ">") == 0) {
            
            // Get the argument after ">"
            char* output_file = command.arguments[i+1];

            // Opens the output files as a file stream
            FILE* outfile = fopen(output_file, "w");

            // If there was an error opening the file, print the error and exit
            if (outfile == NULL) {
                ErrorHandling(0);
            }

            // Get the file descriptor of the file stream
            fd_out = fileno(outfile);

            // Redirect stdout to the file descriptor
            dup2(fd_out, STDOUT_FILENO);

            // Close the file stream
            fclose(outfile);

            // Shift the arguments to the left by 2
            for (int j = i; command.arguments[j] != NULL; j++) {
                command.arguments[j] = command.arguments[j+2];
            }

            // Decrement i so that the next argument is checked
            i--;
        }
    }
};

// Executes commands that are not "cd" or "exit"
void ExecuteOtherCommand(struct ShellCommand command) {

    // Forks the process
    pid_t pid = fork();

    // Child process
    if (pid == 0) {
        Redirection(command);
        execvp(command.command, command.arguments);
        ErrorHandling(0);
    }

    // If forking fails, print error
    if (pid < 0) {
        ErrorHandling(0);
    }

    // Parent process
    else {
        wait(NULL);
    }
};

// Displays the current directory and a prompt
char* CommandPrompt() {

    // Gets the current directory and stores it in "user_directory"
    char* user_directory = GetCurrentDirectory();

    PromptLayout(user_directory);

    return PromptInput();
};

// Seperates the command line into its individual arguments
struct ShellCommand ParseCommandLine(char* input) {
    struct ShellCommand struc;
    struc.command = NULL;
    struc.arguments = NULL;

    // Tokenize the input by spaces
    char* token = strtok(input, " ");

    // Check if there's a command, if not, return
    if (token == NULL) {
        return struc;
    }

    // Allocate memory for the command and arguments
    struc.command = malloc(SIZE);
    struc.arguments = malloc(SIZE);

    // Copy the first token into the command
    strcpy(struc.command, token);

    // Initalize the number of arguments to 0
    int num_args = 0;
    char** args = NULL;

    // While token is not null, keep tokenizing
    while (token != NULL) {
        num_args++;

        // Reallocate memory for the arguments
        char** new_args = realloc(args, (num_args+1) * sizeof(char*));

        // Updates args to point to the newly allocated memory set from new_args
        args = new_args;

        // Allocate memory for the new argument
        args[num_args - 1] = malloc(SIZE);

        // Copy the token into the new argument
        strcpy(args[num_args - 1], token);

        // Get the next token
        token = strtok(NULL, " ");

    }

    // Set the last argument to null
    args[num_args] = NULL;

    // Set the struct's arguments to the parsed arguments
    struc.arguments = args;

    return struc;
};

// Executes the command
void ExecuteCommand(struct ShellCommand command) {

    // If no command is given, return
    if (command.command == NULL) {
        return;
    }
    
    // If command is "exit", exit the shell
    // strcmp returns 0 if the strings are equal
    if (strcmp(command.command, "exit") == 0) {
        exit(0);
    }

    // If command is "cd", try to change directory
    // strcmp returns 0 if the strings are equal
    if (strcmp(command.command, "cd") == 0) {
        ExecuteCD(command.arguments[1]);
        return;
    }

    ExecuteOtherCommand(command);    
}

/*
    MAIN
*/

// Main function
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