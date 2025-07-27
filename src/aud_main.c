/** 
* @file main.c
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

#define MAX_LINE_LENGTH 100                           // Maximum length of a command line

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
int main(int argc, char *argv[]) 
{
    LOG_INFO("Command Processor Initialized.", __func__);

    if (argc < 2) 
    {
        LOG_ERROR("Usage: %s <commands.txt>", argv[0]);
        return 1;
    }

    register_audio_commands();  // Register all commands dynamically

    FILE *file = fopen(argv[1], "r");
    if (!file) 
    {
        LOG_ERROR("Failed to open file: %s", argv[1]);
        return 1;
    }

    LOG_INFO("Reading commands from file: %s", argv[1]);

    char audio_command[MAX_LINE_LENGTH];

    while (fgets(audio_command, sizeof(audio_command), file)) 
    {
        // Remove trailing newline characters
        audio_command[strcspn(audio_command, "\r\n")] = 0;

        if (strlen(audio_command) == 0) continue;

        LOG_INPUT("Received: \"%s\"", audio_command);
        dispatch_command(audio_command);
    }

    fclose(file);
    free_command_processor();  // clean up

    return 0;
}
