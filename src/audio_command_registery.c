/** 
     * @file audio_command_regsistry.c
     * @brief Audio Command Registry Implementation
     * This file implements the command registration and processing functionality for the audio command processor.
     * It includes functions to register commands, dispatch them, and manage the command linked list.
 */

#include "audio_command_processor.h"
#include "audio_logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ================================================
// Audio command handlers

// Implementation for handling play command
static void handle_play_command(const char *command) 
{
    LOG_INFO("Handling play command: %s", command);
}

// Implementation for handling stop command
static void handle_stop_command(const char *command) 
{
    LOG_INFO("Handling stop command: %s", command);
}

// Implementation for handling volume up command
static void handle_volume_up_command(const char *command)
{
    LOG_INFO("Handling volume up command: %s", command);
}

// Implementation for handling volume down command
static void handle_volume_down_command(const char *command)
{
    LOG_INFO("Handling volume down command: %s", command);
}

// Implementation for handling reset command
static void handle_reset_command(const char *command)
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
 * @brief Registers all audio commands.
 *
 * This function is called at startup to register all available audio commands
 * with the command processor.
 */
void register_audio_commands(void) 
{
    // Registering commands with their respective handlers
    register_command("play", handle_play_command);
    register_command("stop", handle_stop_command);
    register_command("volumeUp", handle_volume_up_command);
    register_command("volumeDown", handle_volume_down_command);
    register_command("reset", handle_reset_command);
    register_command("invalid", handle_invalid_command); 
}