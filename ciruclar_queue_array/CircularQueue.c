#include "CircularQueue.h"

Queue_t *Qeueu_inis(uint32_t max_size, QueueStatus_t *return_val)
{

    if (max_size <= 0)
    {
        *return_val = Q_negative;
#ifndef DEBUGG
        printf("ERROR!! invaild max_szie of queue , ret = %i", *return_val);
#endif
        return NULL;
    }
    if (NULL == return_val)
    {
        *return_val = Q_NULL;

#ifdef DEBUGG
        printf(
            "ERROR!! Passing Null return_val pointer to Qeueue_inis , ret = %i \n",
            *return_val);
#endif
        return NULL;
    }
    else
    {
        Queue_t *ptr = (Queue_t *)calloc(1U, sizeof(Queue_t));
        if (!ptr)
        {
            *return_val = Q_NULL;
#ifdef DEBUGG
            printf("ERROR!! failed to calloc pointer in qeueu_inis , ret = %i \n",
                   *return_val);
#endif
            return NULL;
        }
        else
        {
            ptr->queue_obj = (void **)calloc(max_size, sizeof(void *));
            if (!ptr->queue_obj)
            {
                *return_val = Q_NULL;
#ifdef DEBUGG
                printf("ERROR!! failed to calloc Queue_obj , ret=  %i", *return_val);
#endif
                return NULL;
            }

            else
            {
                ptr->front = -1;
                ptr->rear = -1;
                ptr->element_count = 0;
                ptr->max_size = max_size;
                *return_val = Q_OK;
                return ptr;
            }
        }
    }
}

static QueueStatus_t Qeueu_empty(Queue_t *Q_ptr)
{
    QueueStatus_t return_val = Q_NOTOK;
    if (NULL == Q_ptr)
    {
        return_val = Q_NULL;
#ifdef DEBUGG
        printf("ERROR!! passing null pointer to Qeueue_empty , ret = %i",
               return_val);
#endif
        return return_val;
    }
    else
    {
        if (Q_ptr->element_count == 0)
        {
            return_val = Q_EMPTY;
            return return_val;
        }
        else
        {
            return_val = Q_OK;
            return return_val;
        }
    }
}
static QueueStatus_t Qeueu_full(Queue_t *Q_ptr)
{
    QueueStatus_t return_val = Q_NOTOK;
    if (NULL == Q_ptr)
    {
        return_val = Q_NULL;
#ifdef DEBUGG
        printf("ERROR!! passing null pointer to Qeueue_empty , ret = %i",
               return_val);
#endif
    }
    else
    {
        if (Q_ptr->element_count == Q_ptr->max_size)
        {
            return_val = Q_FULL;
            return return_val;
        }
        else
        {
            return_val = Q_OK;
            return return_val;
        }
    }
}

QueueStatus_t Enqueue(Queue_t *queue_ptr, void *element)
{
    QueueStatus_t ret = Q_NOTOK;
    if (!queue_ptr)
    {
        ret = Q_NULL;
#ifdef DEBUGG
        printf("ERROR!! pasing null pointer to enqueue , ret = %i\n", ret);
#endif
        return ret;
    }
    else
    {
        if (!element)
        {
            ret = Q_NULL;
#ifdef DEBUGG
            printf("ERROR!! pasing null pointer to enqueue , ret = %i\n", ret);
#endif
            return ret;
        }
        else
        {
            if (Q_FULL == (Qeueu_full(queue_ptr)))
            {
                ret = Q_FULL;
#ifdef DEBUGG
                printf("ERROR!! cant enqueue a full queue , ret = %i \n", ret);
#endif
                return ret;
            }
            else
            {
                if (Q_EMPTY == (Qeueu_empty(queue_ptr)))
                {
                    (queue_ptr->front) += 1;
                    (queue_ptr->rear) += 1;
                    (queue_ptr->element_count) += 1;
                    (queue_ptr->queue_obj[queue_ptr->front]) = element;
                    ret = Q_OK;
                    return ret;
                }
                else
                {
                    /* circular queue condition */
                    if (queue_ptr->rear == (queue_ptr->max_size) - 1)
                    {
                        queue_ptr->rear = 0;
                        (queue_ptr->element_count) += 1;
                        queue_ptr->queue_obj[queue_ptr->rear] = element;
                        ret = Q_OK;
                        return ret;
                    }
                    else
                    {
                        (queue_ptr->rear) += 1;
                        (queue_ptr->element_count) += 1;
                        (queue_ptr->queue_obj[queue_ptr->rear]) = element;
                        ret = Q_OK;
                        return ret;
                    }
                }
            }
        }
    }
    return ret;
}

void *Dequeue(Queue_t *q_ptr, QueueStatus_t *ret)
{
    void *poped_data = NULL;
    *ret = Q_NOTOK;
    if ((NULL == q_ptr) || (NULL == ret))
    {
        *ret = Q_NULL;
#ifdef DEBUGG
        printf("ERROR!! passing null pointer to dequeue func  ret = %i \n", *ret);
#endif
        return NULL;
    }
    else
    {
        if (Q_EMPTY == (Qeueu_empty(q_ptr)))
        {
            *ret = Q_EMPTY;
#ifdef DEBUGG
            printf("ERROR!! cant dequeue empty queue , ret = %i\n", *ret);
#endif
            return NULL;
        }
        else
        { /*  if queue have 1 element  */
            if (q_ptr->element_count == 1)
            {
                poped_data = q_ptr->queue_obj[q_ptr->front];
                q_ptr->front = -1;
                q_ptr->rear = -1;
                (q_ptr->element_count)--;
                *ret = Q_OK;
                return poped_data;
            }
            else
            {
                poped_data = q_ptr->queue_obj[q_ptr->front];
                (q_ptr->element_count)--;
                (q_ptr->front)++;
                // ciruclar queue condition
                if (q_ptr->front == q_ptr->max_size)
                {
                    q_ptr->front = 0;
                }
                *ret = Q_OK;
                return poped_data;
            }
        }
    }
}

void Queue_dis(Queue_t *ptr)
{
    if (!ptr)
    {
        printf("passing null pointer\n");
    }
    sint32_t front = ptr->front;
    int index = 0;
    for (int i = 0; i < ptr->element_count; i++)
    {
        index = front + i;
        if (index >= ptr->max_size)
        {
            index -= ((ptr->max_size));
        }
        printf("%i ", *((uint32_t *)ptr->queue_obj[index]));
    }
    printf("\n");
    return;
}

void *Qfront(Queue_t *ptr, QueueStatus_t *ret)
{
    *ret = Q_NOTOK;
    void *return_val = NULL;
    if ((NULL == ptr) || (NULL == ret))
    {
        *ret = Q_NULL;
#ifdef DEBUGG
        printf("ERROR PASSING NULL POINTER TO Qfront , ret = %i \n", *ret);
#endif
        return NULL;
    }
    else if (Q_EMPTY == (Qeueu_empty(ptr)))
    {
        *ret = Q_EMPTY;
#ifdef DEBUGG
        printf("ERROR PASSING empty queue to Qfront , ret= %i \n", *ret);
#endif
        return NULL;
    }
    else
    {
        return_val = ptr->queue_obj[ptr->front];
        *ret = Q_OK;
        return return_val;
    }
    *ret = Q_NOTOK;
    return NULL;
}

void *Qrear(Queue_t *ptr, QueueStatus_t *ret)
{
    void *return_val = NULL;
    *ret = Q_NOTOK;
    if ((NULL == ptr) || (NULL == ret))
    {
        *ret = Q_NULL;
#ifdef DEBUGG
        printf("ERROR PASSING NULL POINTER TO Qfront , ret = %i \n", *ret);
#endif
        return NULL;
    }
    else if (Q_EMPTY == (Qeueu_empty(ptr)))
    {
        *ret = Q_EMPTY;
#ifdef DEBUGG
        printf("ERROR PASSING empty queue to Qfront , ret= %i \n", *ret);
#endif
        return NULL;
    }
    else
    {
        return_val = ptr->queue_obj[ptr->front];
        *ret = Q_OK;
        return return_val;
    }
    *ret = Q_NOTOK;
    return NULL;
}

QueueStatus_t Qdestroy(Queue_t **ptr)
{
    QueueStatus_t ret = Q_NOTOK;
    if (NULL == ptr)
    {
        ret = Q_NULL;
        printf("passing null pointer to queue destroy , ret = %i \n", ret);
        return ret;
    }
    else
    {
        free((*ptr)->queue_obj);
        (*ptr)->queue_obj = NULL;
        free(*ptr);
        *ptr = NULL;
        ret = Q_OK;
        return ret;
    }
}
