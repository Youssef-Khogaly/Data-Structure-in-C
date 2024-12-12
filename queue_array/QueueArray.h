#ifndef _DATA_H_
#define _DATA_H_
#include <stdio.h>
#include <stdlib.h>
#include "Type_def.h"
#define DEBUGG 1

typedef struct
{
    void **queue;
    uint32_t queue_maxsize;
    sint32_t front;
    sint32_t rear;
    sint32_t queue_count;
} queue_t;

typedef enum
{
    Q_NOTOK,
    Q_OK,
    Q_EMPTY,
    Q_FULL,
    Q_NULL,
    Q_liner
} queue_status_t;
/**
 * @brief  inistaliszed my queue element
 *
 * @param ptr  pointer to  my queue
 * @param max_size max size of the
 * @param return_value pointer to queue_status_t to change check function if worked well value = Q_OK
 * @return  return pointer to queue_t
 */
queue_t *queue_inis(queue_t *ptr, uint32_t max_size, queue_status_t *return_value);
/**
 * @brief enqueue element in the stack
 *
 * @param ptr pointer to the stack
 * @param value void pointer
 * @return queue_status_t return Q_OK if function goes well
 */
queue_status_t enqeue(queue_t *ptr, void *value);
/**
 * @brief dequeue from the front of the queue
 *
 * @param ptr pointer to queue_t
 * @param value void pointer have the address of the value
 * @return queue_status_t  return Q_OK if goes fine
 */
void *deqeue(queue_t *ptr, queue_status_t *ret);
/**
 * @brief print the top of the queue
 *
 * @param ptr  pointer to the queue
 * @return queue_status_t  return Q_OK if worked well
 */
void *queue_front(queue_t *ptr, queue_status_t *ret);

void *queue_rear(queue_t *ptr, queue_status_t *ret);
/**
 * @brief destroy the queue
 * 
 * @param queue pointer to queue
 * @return queue_status_t return 1 if worked fine
 */
queue_status_t queue_destory(queue_t *queue);

#endif