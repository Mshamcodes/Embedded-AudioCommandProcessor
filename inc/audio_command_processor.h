/**
 * @brief Processor Header File
 * This file contains the declaration of the command processor functions and data structures.
*/

#ifndef COMMAND_PROCESSOR_H
#define COMMAND_PROCESSOR_H

#include <stdint.h>

/**
 * @brief Command handler function type
 *
 * This type defines the signature for command handler functions.
 * It takes a const char pointer as an argument, which represents the command to be processed.
 */
typedef void (*command_handler_t)(const char *command);

/**
 * @brief Audio command node structure
 *
 * This structure represents a node in the linked list of audio commands.
 */
typedef struct aud_command_node{
    const char* command_name;               // Name of the command being processed
    command_handler_t handler;              // Pointer to the command handler function
    struct aud_command_node *next;          // Pointer to the next command node in the linked list
} aud_command_node_t;

/**
 * @brief Dispatches a command to the appropriate handler.
 *
 * This function takes a command string, splits it into the command name and its arguments,
 * and calls the corresponding handler function if the command is recognized.
 *
 * @param audio_command The input command line to process.
 */
void dispatch_command(const char *audio_command);

/**
 * @brief Registers a command with its handler.
 *
 * This function creates a new command node and adds it to the command linked list.
 *
 * @param command_name The name of the command to register.
 * @param handler The function to handle the command.
 */
void register_command(const char *command_name, command_handler_t handler);

/**
 * @brief Frees the resources used by the command processor.
 *
 * This function traverses the command linked list and frees each node.
 * It should be called when the command processor is no longer needed.
 */
void free_command_processor(void);

#endif // COMMAND_PROCESSOR_H
