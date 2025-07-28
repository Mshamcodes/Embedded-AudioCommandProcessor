/**
 * @file inc/audio_buffer.h
 * @brief Audio Buffer Header
 */


#ifndef AUDIO_BUFFER_H
#define AUDIO_BUFFER_H

#include <stdbool.h>

#define AUDIO_BUFFER_SIZE 256                                                          // Define the size of the audio buffer
#define AUDIO_BUFFER_CAPACITY 10                                                       // Define the maximum number of audio commands in the buffer

typedef struct{
    char audio_buffer_chunks[AUDIO_BUFFER_CAPACITY][AUDIO_BUFFER_SIZE];                // Array to hold audio commands
    int buffer_head;                                                                   // Index of the next command to be added
    int buffer_tail;                                                                   // Index of the next command to be processed
    int buffer_count;                                                                  // Current number of commands in the buffer
} audio_buffer_t;


void init_audio_buffer(audio_buffer_t *aud_buffer);                                    // Initialize the audio buffer
bool enqueue_audio_command(audio_buffer_t *aud_buffer, const char *command);           // Add a command to the buffer
bool dequeue_audio_command(audio_buffer_t *aud_buffer, char *command);                 // Remove a command from the buffer
bool is_audio_buffer_empty(const audio_buffer_t *aud_buffer);                          // Check if the buffer is empty
bool is_audio_buffer_full(const audio_buffer_t *aud_buffer);                           // Check if the buffer is full
void reset_audio_buffer(audio_buffer_t *aud_buffer);                                   // Reset the audio buffer
void print_audio_buffer_state(const audio_buffer_t *aud_buffer);                       // Print the contents of the audio buffer

#endif // AUDIO_BUFFER_H