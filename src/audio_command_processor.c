/**
 * @brief Dispatches a command to the appropriate handler.
 *
 * @param command The command to dispatch.
 */

#include "audio_command_processor.h"
#include "audio_logger.h"
#include "audio_command_registery.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


static aud_command_node_t *aud_command_table = NULL;                  // Pointer to the head of the command linked list

/**
 * @brief Registers a command with its handler.
 *
 * This function creates a new command node and adds it to the command linked list.
 *
 * @param command_name The name of the command to register.
 * @param handler The function to handle the command.
 */
void register_command(const char *command_name, command_handler_t handler)
{
    if (command_name == NULL || handler == NULL) 
    {
        LOG_ERROR("Invalid command registration attempt");
        return;
    }

    aud_command_node_t *new_aud_command = malloc(sizeof(aud_command_node_t));
    if (new_aud_command == NULL) 
    {
        LOG_ERROR("Memory allocation failed for command node");
        return;
    }

    new_aud_command->command_name = command_name;                // Set the command name
    new_aud_command->handler = handler;                          // Set the command handler
    new_aud_command->next = aud_command_table;                   // Insert at the head of the list
    aud_command_table = new_aud_command;                         // Update the head of the list

    LOG_INFO("Registered command: %s", command_name);
}


/**
 * @brief Frees the resources used by the command processor.
 *
 * This function traverses the command linked list and frees each node.
 * It should be called when the command processor is no longer needed.
 */
void free_command_processor(void)
{
    aud_command_node_t *current = aud_command_table;
    while (current != NULL) 
    {
        aud_command_node_t *next = current->next;           // Save next node
        free(current);                                      // Free current node
        current = next;                                     // Move to next node
    }
    aud_command_table = NULL;                               // Reset the head of the list
    LOG_INFO("Command processor freed");
}


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

    aud_command_node_t *curr = aud_command_table;

    while (curr != NULL) 
    {
        size_t len = strlen(curr->command_name);
        if (strncmp(buffer, curr->command_name, len) == 0 && (buffer[len] == ' ' || buffer[len] == '\0')) 
        {
            const char *args = (buffer[len] == ' ') ? buffer + len + 1 : "";
            curr->handler(args);
            return;
        }
        curr = curr->next;
    }
    LOG_WARNING("Unknown command received: \"%s\"", buffer);
}
