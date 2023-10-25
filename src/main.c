/*
This is the Developmental Branch, used to put new things and break things!

Git stuff:
After edits, save file and do "git add ."
Then do "git commit -m "message""
Then do "git push origin Developmental"

Regular C stuff:
Save file and run "gcc main.c -o shell"
To run, do "./shell"
*/

/*
Author: Tyler Tran, Dalton Michiels, Colby Women 
Date: 10-23-2023
Description: CSC222 Programming Project - A small shell with I/O redirections
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* CommandPrompt();

struct ShellCommand {};

struct ShellCommand ParseCommandLine(char* input);

void ExecuteCommand(struct ShellCommand command);

int main() {
    char* input;
    struct ShellCommand command;

    for(;;) {
        input = CommandPrompt();
        command = ParseCommandLine(input);
        ExecuteCommand(command);
    }

    exit(0);
}