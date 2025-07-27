/**
 * @brief Dispatches a command to the appropriate handler.
 *
 * @param command The command to dispatch.
 */

#include "audio_command_processor.h"
#include "audio_logger.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ================================================
// Audio command handlers

// Implementation for handling play command
static void handle_play(const char *command) 
{
    LOG_INFO("Handling play command: %s", command);
}

// Implementation for handling stop command
static void handle_stop(const char *command) 
{
    LOG_INFO("Handling stop command: %s", command);
}

// Implementation for handling volume up command
static void handle_volume_up(const char *command)
{
    LOG_INFO("Handling volume up command: %s", command);
}


// Implemnentation for handling volume down command
static void handle_volume_down(const char *command)
{
    LOG_INFO("Handling volume down command: %s", command);
}

// Implementation for handling reset command
static void handle_reset(const char *command)   
{
    LOG_INFO("Handling reset command: %s", command);
}

// Implementation for handling invalid command
static void handle_invalid_command(const char *command)
{
    LOG_ERROR("Invalid command received: %s", command);
}

// ================================================


/**
     * @brief Dispatches a command to the appropriate handler based on the command name.
     *
     * @param command The command to dispatch.
     */
static const command_processor_t command_table[] = {
    {"play", handle_play},
    {"stop", handle_stop},
    {"volume up", handle_volume_up},
    {"volume down", handle_volume_down},
    {"reset", handle_reset},
    {"invalid_command", handle_invalid_command}
};


// Size of the command table
// This is used to iterate through the command table
static const size_t command_table_size = sizeof(command_table) / sizeof(command_processor_t);

/**
 * @brief Dispatches a command to the appropriate handler.
 *
 * This function takes a command string, splits it into the command name and its arguments,
 * and calls the corresponding handler function if the command is recognized.
 *
 * @param line The input command line to process.
 */
void dispatch_command(const char *audio_command)
{
    if (audio_command == NULL || strlen(audio_command) == 0) {
        LOG_ERROR("Received empty command");
        return;
    }

    char buffer[100];
    strncpy(buffer, audio_command, sizeof(buffer));
    buffer[sizeof(buffer) - 1] = '\0';

    // Trim newline at end
    buffer[strcspn(buffer, "\r\n")] = '\0'; 

    for (size_t i = 0; i < command_table_size; ++i) 
    {
        const char *cmd_name = command_table[i].command_name;
        size_t len = strlen(cmd_name);

        // Check if input starts with the command name
        if (strncmp(buffer, cmd_name, len) == 0 && (buffer[len] == ' ' || buffer[len] == '\0')) {

            const char *args = (buffer[len] == ' ') ? buffer + len + 1 : "";
            command_table[i].handler(args);
            return;
        }
    }
    LOG_WARNING("Unknown command received: \"%s\"", buffer);
}
