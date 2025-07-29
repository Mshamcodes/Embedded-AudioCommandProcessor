/**
 * @file src/audio_buffer.c
 * @brief Audio Buffer Implementation 
 */

#include "audio_buffer.h"
#include <stdio.h>
#include <string.h>

/**
 * @brief Initializes the audio buffer.
 *
 * This function sets the head, tail, and count of the audio buffer to zero.
 *
 * @param aud_buffer Pointer to the audio buffer to initialize.
 */
void init_audio_buffer(audio_buffer_t *buffer)
{
    buffer->buffer_head = 0;
    buffer->buffer_tail = 0;
    buffer->buffer_count = 0;
}

/**
 * @brief Adds a command to the audio buffer.
 *
 * This function adds a command to the audio buffer if it is not full.
 *
 * @param aud_buffer Pointer to the audio buffer.
 * @param command The command to add to the buffer.
 */
bool enqueue_audio_command(audio_buffer_t *buffer, const char *command)
{
    if(is_audio_buffer_full(buffer)) 
    {
        printf("Audio buffer is full. Cannot enqueue command: %s\n", command);
        return false;
    }

    // Copy the command into the buffer at the tail index
    strncpy(buffer->audio_buffer_chunks[buffer->buffer_tail], command, AUDIO_BUFFER_SIZE - 1);
    buffer->buffer_tail = (buffer->buffer_tail + 1) % AUDIO_BUFFER_CAPACITY; // Move tail to next position
    buffer->buffer_count++; // Increment the count of commands in the buffer

    return true;
}


/**
 * @brief Checks if the audio buffer is empty.
 *
 * This function checks if the audio buffer has no commands.
 *
 * @param aud_buffer Pointer to the audio buffer.
 * @return true if the buffer is empty, false otherwise.
 */
bool dequeue_audio_command(audio_buffer_t *buffer, char *command)
{
    if(is_audio_buffer_empty(buffer)) 
    {
        printf("Audio buffer is empty. Cannot dequeue command.\n");
        return false;
    }

    // Copy the command from the head index to the provided command buffer
    strncpy(command, buffer->audio_buffer_chunks[buffer->buffer_head], AUDIO_BUFFER_SIZE - 1);
    command[AUDIO_BUFFER_SIZE - 1] = '\0'; // Ensure null termination
    buffer->buffer_head = (buffer->buffer_head + 1) % AUDIO_BUFFER_CAPACITY; // Move head to next position
    buffer->buffer_count--; // Decrement the count of commands in the buffer

    return true;
}

/**
 * @brief Checks if the audio buffer is empty.
 *
 * This function checks if the audio buffer has no commands.
 *
 * @param aud_buffer Pointer to the audio buffer.
 * @return true if the buffer is empty, false otherwise.
 */
bool is_audio_buffer_empty(const audio_buffer_t *buffer)
{
    return buffer->buffer_count == 0;
}

/**
 * @brief Checks if the audio buffer is full.
 *
 * This function checks if the audio buffer has reached its capacity.
 *
 * @param aud_buffer Pointer to the audio buffer.
 * @return true if the buffer is full, false otherwise.
 */
bool is_audio_buffer_full(const audio_buffer_t *buffer)
{
    return buffer->buffer_count == AUDIO_BUFFER_CAPACITY;
}

/**
 * @brief Resets the audio buffer.
 *
 * This function clears the audio buffer by resetting the head, tail, and count.
 *
 * @param aud_buffer Pointer to the audio buffer to reset.
 */
void reset_audio_buffer(audio_buffer_t *buffer)
{
    buffer->buffer_head = 0;
    buffer->buffer_tail = 0;
    buffer->buffer_count = 0;
    printf("Audio buffer has been reset.\n");
    print_audio_buffer_state(buffer);
}

/**
 * @brief Prints the current state of the audio buffer.
 *
 * This function prints the contents of the audio buffer, including the head, tail, and count.
 *
 * @param aud_buffer Pointer to the audio buffer to print.
 */
void print_audio_buffer_state(const audio_buffer_t *buffer)
{
    printf("[INFO] Audio Buffer - Chunks: %d / %d | Front: %d | Rear: %d\n",
           buffer->buffer_count, AUDIO_BUFFER_CAPACITY, buffer->buffer_head, buffer->buffer_tail);

    printf("Buffer View: ");
    for (int i = 0; i < AUDIO_BUFFER_CAPACITY; i++) 
    {
        bool isFilled = ((buffer->buffer_head <= buffer->buffer_tail && i >= buffer->buffer_head && i < buffer->buffer_tail) ||
                         (buffer->buffer_head > buffer->buffer_tail && (i >= buffer->buffer_head || i < buffer->buffer_tail)));

        if (i == buffer->buffer_head && i == buffer->buffer_tail && buffer->buffer_count != 0) 
        {
            // Front == Rear but buffer not empty => Full buffer wrap-around
            printf("[FR🟩]");
        } 
        else if (i == buffer->buffer_head && buffer->buffer_count != 0) 
        {
            printf("[F🟩]");
        } 
        else if (i == buffer->buffer_tail && buffer->buffer_count != 0) 
        {
            printf("[R🟩]");
        } 
        else if (isFilled) 
        {
            printf("[🟩]");
        } 
        else 
        {
            printf("[⬜]");
        }
    }
    printf("\n\n");
}