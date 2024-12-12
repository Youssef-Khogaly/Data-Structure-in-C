#ifndef _CIRCULARQUEUE_
#define _CIRCULARQUEUE_
#include<stdio.h>
#include<stdlib.h>
#include "Types.h"
#define DEBUGG 1

typedef enum{
    Q_NOTOK,
    Q_OK,
    Q_NULL,
    Q_EMPTY,
    Q_FULL,
    Q_negative
}QueueStatus_t;

typedef struct qeueu {
    void **queue_obj;
    sint32_t element_count;
    sint32_t front;
    sint32_t rear;
    uint32_t max_size;
}Queue_t;
/**
 * @brief inisalize the Qeueue
 * 
 * @param max_size  max size of the queue
 * @param return_val  pointer to return value return 1 if worked well 
 * @return Queue_t* return pointer to the qeueu
 */
Queue_t* Qeueu_inis(uint32_t max_size , QueueStatus_t *return_val);
/**
 * @brief enqueue element to the queue
 * 
 * @param queue_ptr  pointer to the queue
 * @param element element to be enqueue
 * @return QueueStatus_t  return 1 if funciton success
 */
QueueStatus_t Enqueue(Queue_t *queue_ptr , void *element);
void* Dequeue(Queue_t * q_ptr , QueueStatus_t *ret);
/**
 * @brief prrint all element of the queue from front to rear
 * 
 * @param ptr  pointer to the qeueue
 * @return void return
 */
void Queue_dis(Queue_t *ptr);
/**
 * @brief get the front of the queue
 * 
 * @param ptr pointer to the queue
 * @param ret pointer to QueueStatus_t  
 * @return void* return void pointer  have front address
 */
void* Qfront(Queue_t* ptr , QueueStatus_t* ret);

void *Qrear(Queue_t *ptr , QueueStatus_t *ret);

QueueStatus_t Qdestroy(Queue_t **ptr);

#endif