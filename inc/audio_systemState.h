/* Define the audio system header file
 * This file contains the declarations for the audio system functions and data structures.
 */

#ifndef AUDIO_SYSTEM_H
#define AUDIO_SYSTEM_H

#include <stdint.h>


// Define Bitfield for audio system control
typedef struct {
    unsigned is_playing : 1;        // Bit 0: Is audio currently playing
    unsigned is_muted : 1;          // Bit 1: Is audio muted
    unsigned reserved : 6;          // Bits 2-7: Reserved for future use
} audioFlags;


// Complete audio system state
typedef struct {
    audioFlags flags;
    int volume;                // Volume level (0-100)
} audioState;


// Audio system state instance
audioState* get_audio_state(void);


// Utility audio state functions 
void reset_audio_system(void);
void print_audio_state(void);



#endif // AUDIO_SYSTEM_H