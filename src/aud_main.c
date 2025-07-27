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

#define MAX_LINE_LENGTH 100

int main(int argc, char *argv[]) 
{
    LOG_INFO("Command Processor Initialized.", __func__);

    if (argc < 2) 
    {
        LOG_ERROR("Usage: %s <commands.txt>", argv[0]);
        return 1;
    }

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
    return 0;
}
