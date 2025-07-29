/** 
     * @file audio_command_regsistry.c
     * @brief Audio Command Registry Implementation
     * This file implements the command registration and processing functionality for the audio command processor.
     * It includes functions to register commands, dispatch them, and manage the command linked list.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "audio_command_processor.h"
#include "audio_logger.h"
#include "audio_command_registery.h"
#include "audio_systemState.h"
#include "audio_buffer.h"

audio_buffer_t audio_buffer;  // Global audio buffer instance

// ====================================================================================
// Audio command handlers

// Implementation for handling help command
static void handle_help_command(const char *command)
{
    printf("\nAvailable Commands:\n");
    printf(" - play       : Start playing audio\n");
    printf(" - pause      : Pause audio playback and clear buffer\n");
    printf(" - volumeUp   : Increase volume by 10 units (max 100)\n");
    printf(" - volumeDown : Decrease volume by 10 units (min 0)\n");
    printf(" - mute       : Mute the audio\n");
    printf(" - unmute     : Unmute the audio\n");
    printf(" - reset      : Reset system state and buffer\n");
    printf(" - help       : Show the list of commands supported\n\n");

    LOG_INFO("Displayed help information.");
}

// Implementation for handling play command
static void handle_play_command(const char *command)
{
    audioState *state = get_audio_state();
    if (!state->flags.is_muted) 
    {
        state->flags.is_playing = 1;                   // Set playing flag
        LOG_INFO("Playing audio: %s", command);

        // Simulate enqueueing 5 chunks
        for (int i = 1; i <= 5; i++) {
            char dummy_chunk[AUDIO_BUFFER_SIZE];
            snprintf(dummy_chunk, AUDIO_BUFFER_SIZE, "AUDIO_CHUNK_%d", i);
            enqueue_audio_command(&audio_buffer, dummy_chunk);
        }

        // Show buffer state after enqueue
        print_audio_buffer_state(&audio_buffer);

        // Simulate dequeuing 2 chunks (playback)
        for (int i = 0; i < 2; i++) {
            char out_chunk[AUDIO_BUFFER_SIZE];
            if (dequeue_audio_command(&audio_buffer, out_chunk)) 
            {
                printf("[AUDIO] Playing chunk: %s\n", out_chunk);
            }
        }

        // Show buffer state after dequeue
        print_audio_buffer_state(&audio_buffer);
    }
    LOG_INFO("Handling play command: %s", command);
    print_audio_state();
}

// Implementation for handling stop command
static void handle_pause_command(const char *command) 
{
    audioState *state = get_audio_state();
    state->flags.is_playing = 0;                        // Clear playing flag

    // Reset the audio buffer
    reset_audio_buffer(&audio_buffer);

    LOG_INFO("Handling pause command: %s", command);
    print_audio_state();
}

// Implementation for handling volume up command
static void handle_volume_up_command(const char *command)
{
    audioState *state = get_audio_state();
    if (state->volume < 100) 
    {
        state->volume += 10;                            // Increase volume by 10
        if (state->volume > 100) 
        {
            state->volume = 100;                        // Cap volume at 100
        }
    }
    LOG_INFO("Handling volume up command: %s", command);
    print_audio_state();
}

// Implementation for handling volume down command
static void handle_volume_down_command(const char *command)
{
    audioState *state = get_audio_state();
    if (state->volume > 0) 
    {
        state->volume -= 10;                             // Decrease volume by 10
        if (state->volume < 0) 
        {
            state->volume = 0;                           // Cap volume at 0
        }
    }
    LOG_INFO("Handling volume down command: %s", command);
    print_audio_state();
}

// Implementation for handling reset command
static void handle_reset_command(const char *command)
{
    reset_audio_system();                                // Reset the audio system state
    LOG_INFO("Handling reset command: %s", command);
    print_audio_state();
}

// Implementation for handling mute command
static void handle_mute_command(const char *command)
{
    audioState *state = get_audio_state();
    state->flags.is_muted = 1;                           // Set muted flag
    LOG_INFO("Handling mute command: %s", command);
    print_audio_state();
}

// Implementation for handling unmute command
static void handle_unmute_command(const char *command)
{
    audioState *state = get_audio_state();
    state->flags.is_muted = 0;                           // Clear muted flag
    LOG_INFO("Handling unmute command: %s", command);
    print_audio_state();
}

// Implementation for handling invalid command
static void handle_invalid_command(const char *command)
{
    LOG_ERROR("Invalid command received: %s", command);
}

// ====================================================================================


/**
 * @brief Registers all audio commands.
 *
 * This function is called at startup to register all available audio commands
 * with the command processor.
 */
void register_audio_commands(void) 
{
    // Registering commands with their respective handlers
    register_command("help", handle_help_command);
    register_command("play", handle_play_command);
    register_command("pause", handle_pause_command);
    register_command("volumeUp", handle_volume_up_command);
    register_command("volumeDown", handle_volume_down_command);
    register_command("reset", handle_reset_command);
    register_command("mute", handle_mute_command);
    register_command("unmute", handle_unmute_command);
    register_command("invalid", handle_invalid_command); 
}