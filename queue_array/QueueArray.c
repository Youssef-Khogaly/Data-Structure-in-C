#include "QueueArray.h"
/**
 * @brief check if the queue empty
 *
 * @param ptr  pointer to the queue
 * @return queue_status_t  return R_OK if queue not empty
 */
static void swap(void **x, void **y)
{
  void *temp = NULL;
  temp = *x;
  *x = *y;
  *y = temp;
}

static queue_status_t queue_shifting(queue_t *ptr)
{
  queue_status_t ret = Q_NOTOK;
  sint32_t front = (ptr->front);
  if (!ptr)
  {
    ret = Q_NULL;
#ifdef DEBUGG
    printf(
        "ERROR !! passing null pointer to queue_SHIFTING function , ret = %i\n",
        ret);
#endif
    return ret;
  }
  if ((ptr->front == ptr->queue_maxsize) && (ptr->rear == ptr->queue_maxsize))
  {
    ptr->front = -1;
    ptr->rear = -1;
    ret = Q_OK;
    return ret;
  }
  if (ptr->front == ptr->rear)
  {
    swap(&ptr->queue[front], &ptr->queue[0]);
    ptr->front = 0;
    ptr->rear = 0;
    ptr->queue_count = 1;
    ret = Q_OK;
  }
  else
  {
    for (int i = 0; i < ptr->queue_count; i++) // i = 0 ' i = 1
    {
      swap(&ptr->queue[(front + i)], &ptr->queue[i]);
    }
    ptr->front = 0;
    ptr->rear = (ptr->queue_count) - 1;
    ret = Q_OK;
  }

  return ret;
}

static queue_status_t queue_empty(queue_t *ptr)
{
  queue_status_t return_value = Q_NOTOK;
  if (NULL == ptr)
  {
    return_value = Q_NULL;
#ifdef DEBUGG
    printf("ERROR!! pass null pointer to queue_empty function , return_value = "
           "%i\n",
           return_value);
#endif

    return return_value;
  }
  if (ptr->queue_count == 0)
  {
    return_value = Q_EMPTY;
    return return_value;
  }
  return_value = Q_OK;
  return return_value;
}
static queue_status_t queue_liner(queue_t *ptr)
{
  queue_status_t ret = Q_NOTOK;
  if (NULL == ptr)
  {
    ret = Q_NULL;
#ifdef DEBUGG
    printf("passing null pointer to queue_liner function , ret = %i\n", ret);
#endif
    return ret;
  }
  if (ptr->front == (ptr->queue_maxsize))
  {
    ret = Q_liner;
    return Q_liner;
  }
  else
  {
    ret = Q_OK;
    return ret;
  }
}

static queue_status_t queue_full(queue_t *ptr)
{
  queue_status_t return_value = Q_NOTOK;
  if (NULL == ptr)
  {
    return_value = Q_NULL;
#ifdef DEBUGG
    printf("ERROR!! pass null pointer to queue_empty function , return_value = "
           "%i\n",
           return_value);
#endif
    return return_value;
  }
  if ((ptr->rear == (ptr->queue_maxsize) - 1))
  {
    return_value = Q_FULL;
    return return_value;
  }
  return_value = Q_OK;
  return return_value;
}

queue_t *queue_inis(queue_t *ptr, uint32_t max_size,
                    queue_status_t *return_value)
{
  *return_value = Q_NOTOK;

  ptr = (queue_t *)calloc(1, sizeof(queue_t));
  if (NULL == ptr)
  {
    *return_value = Q_NOTOK;
    printf("failed to inisialized the pointer to the queue , ret = %i\n",
           return_value);
    return NULL;
  }
  ptr->queue_maxsize = max_size;
  ptr->front = -1;
  ptr->rear = -1;
  ptr->queue_count = 0;
  ptr->queue = (void **)calloc(max_size, sizeof(void **));
  if (!ptr->queue)
  {
    *return_value = Q_NOTOK;
    printf("failed to inisialized the pointer in the queue , ret = %i\n",
           return_value);
    return NULL;
  }
  *return_value = Q_OK;
  return ptr;
}

queue_status_t enqeue(queue_t *ptr, void *value)
{
  queue_status_t return_value = Q_NOTOK;
  if ((NULL == ptr) || (NULL == value))
  {
    return_value = Q_NULL;
#ifdef DEBUGG
    printf(
        "ERROR!! pass null pointer to enqueue function , return_value = %i\n",
        return_value);
#endif
    return return_value;
  }

  if (Q_FULL == (queue_full(ptr)))
  {

    if (ptr->front > 0)
    {
      return_value = queue_shifting(ptr);
      if (return_value != Q_OK)
      {
        return return_value;
      }
    }
    else
    {
      return_value = Q_FULL;
#ifdef DEBUGG
      printf("ERROR !! cant enqueue to the full queue , ret = %i\n",
             return_value);
#endif
      return return_value;
    }
  }
  if (Q_liner == (queue_liner(ptr)))
  {
    return_value = queue_shifting(ptr);
    if (return_value != Q_OK)
    {
      return return_value;
    }
  }

  if (ptr->front == -1)
  {
    (ptr->front)++;
    (ptr->rear)++;
    (ptr->queue[ptr->front]) = value;
    (ptr->queue_count)++;
    return_value = Q_OK;
    return return_value;
  }
  else
  {
    (ptr->rear) += 1;
    (ptr->queue_count)++;
    ptr->queue[ptr->rear] = value;

    return_value = Q_OK;
    return return_value;
  }
  return_value = Q_NOTOK;
  return return_value;
}

void *deqeue(queue_t *ptr, queue_status_t *ret)
{
  *ret = Q_NOTOK;
  void *return_ptr = NULL;
  if ((NULL == ptr))
  {
    *ret = Q_NULL;
#ifdef DEBUGG
    printf("pass null pointer to dequeue function , ret = %i\n", *ret);
#endif
    return NULL;
  }
  if (Q_EMPTY == (queue_empty(ptr)))
  {
    *ret = Q_EMPTY;
#ifdef DEBUGG
    printf("Pass empty queue to dequeue function , ret = %i\n", *ret);
#endif
    return NULL;
  }
  if (ptr->front == ptr->rear)
  {
    return_ptr = ptr->queue[ptr->front];
    (ptr->queue_count)--;
    (ptr->front)++;
    (ptr->rear)++;
    *ret = Q_OK;
    return return_ptr;
  }
  return_ptr = ptr->queue[ptr->front];
  (ptr->queue_count)--;
  (ptr->front)++;

  *ret = Q_OK;
  return return_ptr;
}

void *queue_front(queue_t *ptr, queue_status_t *ret)
{
  *ret = Q_NOTOK;
  if ((NULL == ptr) || (NULL == ret))
  {
    *ret = Q_OK;
#ifdef DEBUGG
    printf(" passing null pointer to queue_front function !! , ret = %i", *ret);
#endif
    return NULL;
  }
  if (Q_EMPTY == (queue_empty(ptr)))
  {
    *ret = Q_EMPTY;
#ifdef DEBUGG
    printf("passing empty queue to queue_front , ret = %i", *ret);
#endif
    return NULL;
  }
  void *return_pointer = NULL;
  return_pointer = ptr->queue[ptr->front];
  *ret = Q_OK;

  return return_pointer;
}

void *queue_rear(queue_t *ptr, queue_status_t *ret)
{
  *ret = Q_NOTOK;
  if ((NULL == ptr) || (NULL == ret))
  {
    *ret = Q_OK;
#ifdef DEBUGG
    printf(" passing null pointer to queue_front function !! , ret = %i", *ret);
#endif
    return NULL;
  }
  if (Q_EMPTY == (queue_empty(ptr)))
  {
    *ret = Q_EMPTY;
#ifdef DEBUGG
    printf("passing empty queue to queue_front , ret = %i", *ret);
#endif
    return NULL;
  }
  void *return_value = NULL;
  return_value = ptr->queue[ptr->rear];
  *ret = Q_OK;

  return return_value;
}

queue_status_t queue_destory(queue_t *queue)
{
  queue_status_t return_value = Q_NOTOK;
  if (NULL == queue)
  {
    return_value = Q_NULL;
#ifdef DEBUGG
    printf("ERROR!! passing  null pointer to queue_destory . ret = %i \n",
           return_value);
#endif
    return return_value;
  }
  free(queue->queue);
  queue->queue = NULL;
  free(queue);
  queue = NULL;

  return_value = Q_OK;
  return return_value;
}