/** 
* @file aud_main.c
* @brief Main functionality for the audio command processor.
*
* This file provides the main entry point for the audio command processor,
* handling command input and processing.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "audio_logger.h"
#include "audio_command_processor.h"

#define MAX_LINE_LENGTH 256                           // Maximum length of a command line

/**
 * @brief Registers all audio commands.
 *
 * This function is called at startup to register all available audio commands
 * with the command processor.
 */
extern void register_audio_commands(void);

/**
 * @brief Main function for the audio command processor.
 *
 * This function initializes the command processor, reads commands from a file,
 * and dispatches them to the appropriate handlers.
 *
 * @param argc The number of command line arguments.
 * @param argv The array of command line arguments.
 * @return int Exit status of the program.
 */
int main() 
{
    LOG_INFO("Command Processor Initialized.", __func__);

    register_audio_commands();  // Register all commands dynamically

    char command[MAX_LINE_LENGTH];

    while(1)
    {
        printf("Enter command: ");
        if (fgets(command, sizeof(command), stdin) == NULL) {
            LOG_ERROR("Failed to read command");
            continue;
        }

        // Remove trailing newline characters
        command[strcspn(command, "\r\n")] = 0;

        if (strcmp(command, "exit") == 0) {
            LOG_INFO("Exiting interactive mode.");
            break;
        }

        LOG_INPUT("Received: \"%s\"", command);
        dispatch_command(command);
    }

    free_command_processor();  // clean up

    return 0;
}
