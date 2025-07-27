/**
 * @file audio_command_registry.h
 * @brief Audio Command Registry Header
 *
 * This header file defines the interface for the audio command registry,
 * including functions for registering and dispatching audio commands.
 */

#ifndef AUDIO_COMMAND_REGISTRY_H
#define AUDIO_COMMAND_REGISTRY_H

#include <stddef.h>

/**
 * @brief Command handler function type
 *
 * This type defines the signature for command handler functions.
 * It takes a const char pointer as an argument, which represents the command to be processed.
 */
typedef void (*command_handler_t)(const char *args);

/**
 * @brief Registers a command with its handler.
 *
 * @param command_name The name of the command to register.
 * @param handler The function to handle the command.
 */
void register_command(const char *command_name, command_handler_t handler);

/**
 * @brief Dispatches a command to the appropriate handler.
 *
 * @param command The command to dispatch.
 */
void dispatch_command(const char *command);

/**
 * @brief Frees the resources used by the command registry.
 */
void free_command_registry(void);

#endif // AUDIO_COMMAND_REGISTRY_H