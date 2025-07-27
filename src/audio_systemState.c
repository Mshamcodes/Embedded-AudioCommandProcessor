/**
 * @brief System State Management
 * This file contains the implementation of the audio system state functions.
 */

#include <stdio.h>
#include "audio_systemState.h"
#include "audio_logger.h"

// Static instance of audioState to hold the current state
static audioState system_state = {
    .flags = {0},
    .volume = 50  // Start at mid-level volume
};

// Function to get the current audio system state
audioState* get_audio_state(void) {
    return &system_state;
}

// Function to reset the audio system state
void reset_audio_system(void) 
{
    system_state.flags.is_playing = 0;
    system_state.flags.is_muted = 0;
    system_state.volume = 50;
    LOG_INFO("System reset: volume = %d | playing = %d | muted = %d", 
             system_state.volume, 
             system_state.flags.is_playing,
             system_state.flags.is_muted);
}

// Function to print the current audio system status
void print_audio_state(void) 
{
    LOG_INFO("System Status: Volume: %d | Playing: %s | Muted: %s",
             system_state.volume,
             system_state.flags.is_playing ? "Yes" : "No",
             system_state.flags.is_muted ? "Yes" : "No");
}

