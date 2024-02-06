#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
    char *userInput;

    // Main loop to process commands
    do {
        char *commandArgs[100]; // Array to hold arguments for the command to be executed
        
        // Allocate memory for the command input
        userInput = (char *)malloc(100 * sizeof(char)); 
        
        // Initialize userInput with null characters
        strncpy(userInput, "\0", 100); 
        int inputLength = 0, argumentCount = 0, inputChar, backgroundFlag;

        printf("Your Command> "); // Prompt the user for a command

        // Read the command from standard input, character by character
        while ((inputChar = getchar()) != '\n') {
            if (inputLength == 0) {
                
                // First character of a new argument
                commandArgs[argumentCount] = userInput + inputLength;
                *(userInput + inputLength) = inputChar;
                
                inputLength++;
                argumentCount++;
            } 
            else if (inputChar == ' ') {
                
                // Space character, indicates end of an argument
                commandArgs[argumentCount] = userInput + inputLength + 1;
                *(userInput + inputLength) = '\0';
                
                inputLength++;
                argumentCount++;
            } 
            else {
                // Part of an argument
                *(userInput + inputLength) = inputChar;
                inputLength++;
            }
        }

        // Null-terminate the last argument
        *(userInput + inputLength) = '\0';
        commandArgs[argumentCount] = NULL;

        // Check if the command should be executed in the background
        if (*(userInput + inputLength - 1) == '&') {
            *(userInput + inputLength - 1) = '\0';
            backgroundFlag = 1;
        } else {
            backgroundFlag = 0;
        }

        // Fork a new process to execute the command
        pid_t childPID = fork();
        if (childPID < 0) {
            fprintf(stderr, "Error in creating child process\n");
        }
        if (childPID > 0) {
            
            // Parent process
            if (!backgroundFlag) {
                wait(NULL); // Wait for the child process to finish if not in background
            }
        } 
        else {
            
            // Child process
            int executionResult = execvp(userInput, commandArgs);
            exit(executionResult);
        }

        // Free allocated memory for userInput to prevent memory leak
        free(userInput);

    } while (strncmp(userInput, "exit", 4) != 0);    // Exit the loop if the command is 'exit'

    printf("Goodbye\n");
    return EXIT_SUCCESS;
}
