#include "DstackArray.h"

void cleanup(stack_t **ptr)
{
    free(*ptr);
    ptr = NULL;
}

static stack_status_t Cstack_empty(stack_t *ptr)
{
    if (ptr->stack_top == -1)
        return S_EMPTY;

    return S_OK;
}

static stack_status_t Cstack_full(stack_t *ptr)
{
    if (ptr->element_count == ptr->stack_max_size)
        return S_FULL;

    return S_OK;
}

stack_t *creatStack(uint32_t max_size, stack_status_t *ret)
{
    if (NULL == ret)
    {
        *ret = S_NULL;
#ifdef DEBUGG
        printf("passing null pointer to creatstack , ret = %i", ret);
        return NULL;
#endif
    }
    stack_t *ptr = (stack_t *)calloc(1, sizeof(stack_status_t));
    if (!ptr)
    {
        *ret = S_NOTOK;
        cleanup(&ptr);
#ifdef DEBUGG
        printf(" failed to allocate stack , ret = %i\n", ret);
        return NULL;
#endif
    }

    ptr->stack_pointer = (void **)calloc(max_size, sizeof(void *));
    if (!ptr->stack_pointer)
    {
        *ret = S_NOTOK;
        free(ptr->stack_pointer);
        ptr->stack_pointer = NULL;
        cleanup(&ptr);
#ifdef DEBUGG
        printf(" failed to allocate stack , ret = %i\n", ret);
        return NULL;
#endif
    }
    ptr->stack_max_size = max_size;
    ptr->element_count = 0;
    ptr->stack_top = -1;
    *ret = S_OK;
    return ptr;
}

stack_status_t push(stack_t *mystack, void *item)
{
    stack_status_t ret = S_NOTOK;
    if ((NULL == item) || (NULL == mystack) || (NULL == mystack->stack_pointer))
    {
        ret = S_NULL;
#ifdef DEBUGG
        printf("passing Null pointer to push function , ret = %i\n", ret);
#endif
        return ret;
    }
    if (S_FULL == (Cstack_full(mystack)))
    {
        ret = S_NULL;
#ifdef DEBUGG
        printf("stack is full cant push value !! , ret = %i\n", ret);
#endif
        return ret;
    }

    (mystack->stack_top)++;
    (mystack->element_count)++;
    (mystack->stack_pointer[mystack->stack_top]) = item;
    return S_OK;
}

stack_status_t pop(stack_t *mystack, stack_t *pop)
{
    stack_status_t ret = S_NOTOK;
    void *poped_data = mystack->stack_pointer[mystack->stack_top];
    if (NULL == mystack || NULL == pop)
    {
        ret = S_NULL;
#ifdef DEBUGG
        printf("passing null pointer to pop function  , ret = %i\n", ret);
#endif
        return ret;
    }
    if (S_EMPTY == (Cstack_empty(mystack)))
    {
        ret = S_EMPTY;
#ifdef DEBUGG
        printf("passing empty stack to pop function , ret = %i\n", ret);
#endif
        return ret;
    }
    ret = push(pop, poped_data);
    (mystack->element_count)--;
    (mystack->stack_top)--;
    return ret;
}

void *stackTop(stack_t *mystack, stack_status_t *ret)
{
    *ret = S_NOTOK;
    if (NULL == mystack)
    {
        *ret = S_NULL;
#ifdef DEBUGG
        printf("passing null pointer to stacktop function !! , ret = %i\n", ret);
#endif
    }
    if (S_EMPTY == (Cstack_empty(mystack)))
    {
        *ret = S_EMPTY;
#ifdef DEBUGG
        printf("passing empty stack to stacktop function !! , ret = %i\n", ret);
        return NULL;
#endif
    }

#ifdef DEBUGG
    printf("stack top = %d\n", *((uint32_t *)mystack->stack_pointer[mystack->stack_top]));
#endif
    *ret = S_OK;
    return mystack->stack_pointer[mystack->stack_top];
}

stack_status_t Stack_dis(stack_t *mystack)
{
    sint32_t i;
    stack_status_t ret = S_NOTOK;
    if (NULL == mystack)
    {
        ret = S_NULL;
#ifdef DEBUGG
        printf("passing null pointer to stackdis function !! , ret = %i\n", ret);
#endif
    }
    if (S_EMPTY == (Cstack_empty(mystack)))
    {
        ret = S_EMPTY;
#ifdef DEBUGG
        printf("passing empty stack to stackdis function !! , ret = %i\n", ret);
        return ret;
#endif
    }

    for (i = 0; i <= mystack->stack_top; i++)
        printf("%d\n", *((uint32_t *)mystack->stack_pointer[mystack->stack_top - i]));

    ret = S_OK;
    return ret;
}

stack_t *Stack_destroy(stack_t *mystack, stack_status_t *ret)
{
    *ret = S_NOTOK;
    if (NULL == mystack || ret == NULL)
    {
#ifdef DEBUGG
        printf("passing null pointer to stack destroy function ret = %i\n", ret);
        return NULL;
#endif
    }
    free(mystack->stack_pointer);
    mystack->stack_pointer = NULL;
    free(mystack);
    mystack = NULL;
    *ret = S_OK;
    return NULL;
}
