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
#include "logger.h"

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

    char line[MAX_LINE_LENGTH];

    while (fgets(line, sizeof(line), file)) 
    {
        // Remove trailing newline characters
        line[strcspn(line, "\r\n")] = 0;

        if (strlen(line) == 0) continue;

        LOG_INPUT("Received: \"%s\"", line);
        LOG_WARNING("Unknown command received: \"%s\"", line);
    }

    fclose(file);
    return 0;
}
