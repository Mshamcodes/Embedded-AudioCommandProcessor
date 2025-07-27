/**
     * @brief Processor Header File
     * This file contains the declaration of the command processor functions and data structures.
*/

#ifndef COMMAND_PROCESSOR_H
#define COMMAND_PROCESSOR_H

#include <stdint.h>


// Typedef for command handler function pointer
// This function will be called when a command is received
typedef void (*command_handler_t)(const char *command);


// Structure to hold command processor state
typedef struct {
    const char* command_name;          // Name of the command being processed
    command_handler_t handler;         // Pointer to the command handler function
} command_processor_t;


// Public function to dispatch commands
void dispatch_command(const char *);

#endif // COMMAND_PROCESSOR_H
