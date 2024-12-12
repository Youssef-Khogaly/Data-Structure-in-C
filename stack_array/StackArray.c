
#include "StackArray.h"
/**
 * @brief check if stack is empty
 *
 * @param pointer to the stack
 * @return stack_status_t  ENUM S_EMPTY if stack empty
 */
static stack_status_t check_status_empty(stack_ls_t *ptr)
{
    if (ptr->stack_pointer == -1)
        return S_EMPTY;
    else
        return S_NOT_FULL;
}
/**
 * @brief check if stack is full
 *
 * @param pointer to the stack
 * @return stack_status_t  S_FULL if stack is full
 */
static stack_status_t check_status_full(stack_ls_t *ptr)
{
    if (ptr->stack_pointer == ARRAY_MAX_SIZE - 1)
        return S_FULL;
    else
        return S_NOT_FULL;
}

static void swap(uint32_t *x, uint32_t *y)
{
    *x ^= *y;
    *y ^= *x;
    *x ^= *y;
}

return_status_t push(stack_ls_t *ptr, uint32_t value)
{
    if (NULL == ptr)
        return R_NOTOK;

    if (S_FULL == (check_status_full(ptr)))
        return R_NOTOK;

    ptr->stack_pointer += 1;
    ptr->array[ptr->stack_pointer] = value;
    return R_OK;

    return R_NOTOK;
}
return_status_t pop(stack_ls_t *ptr, stack_ls_t *pop_value)
{
    uint8_t i = ptr->stack_pointer;
    return_status_t ret;

    if (S_EMPTY == check_status_empty(ptr))
        return R_NOTOK;

    ret = push(pop_value, ptr->array[ptr->stack_pointer]);

    swap(&ptr->array[i], &ptr->array[ARRAY_MAX_SIZE + i]);
    ptr->stack_pointer--;

    return ret;
}
return_status_t stack_top(stack_ls_t *ptr)
{
    if (S_EMPTY == (check_status_empty(ptr)))
        return R_NOTOK;

    printf("Stack top: %u\n", ptr->array[ptr->stack_pointer]);
    return R_OK;
}
return_status_t stack_init(stack_ls_t *ptr)
{
    if (NULL == ptr)
    {
        return R_NOTOK;
    }
    ptr->stack_pointer = -1;
    return R_OK;
}
return_status_t stack_dis(stack_ls_t *ptr)
{
    if (S_EMPTY == (check_status_empty(ptr)))
        return R_NOTOK;

    for (int i = ptr->stack_pointer; i >= 0; i--)
        printf("%u ", ptr->array[i]);

    printf("\n");

    return R_OK;
}
return_status_t repush(stack_ls_t *ptr, stack_ls_t *pop)
{
    if ((S_FULL == (check_status_full(ptr))) || (S_EMPTY == (check_status_empty(pop))))
    {
        printf("cant repush main stack full or second stack empty\n");
        return R_NOTOK;
    }

    return_status_t ret = R_NOTOK;
    ret = push(ptr, pop->array[pop->stack_pointer]);
    pop->stack_pointer--;
    return ret;
}
return_status_t bubble_sort_stack(stack_ls_t *ptr)
{

    if (S_EMPTY == (check_status_empty(ptr)))
        return R_NOTOK;

    bool swapped = false;
    do
    {
        for (int i = 0; i <= ptr->stack_pointer; i++)
        {
            swapped = false;
            for (int j = 0; j <= ptr->stack_pointer - i; j++)
            {
                if (ptr->array[j] > ptr->array[j + 1])
                {
                    swap(&ptr->array[j], &ptr->array[j + 1]);
                    swapped = true;
                }
            }
        }
    } while (swapped);

    return R_OK;
}
return_status_t stack_binarys(stack_ls_t *ptr, uint32_t value)
{
    if (S_EMPTY == (check_status_empty(ptr)))
        return R_NOTOK;

    uint8_t low = 0, high = ptr->stack_pointer, mid;
    if (value <= ptr->array[ptr->stack_pointer])
    {
        bubble_sort_stack(ptr);
        while (high >= low)
        {
            mid = (low + high) / 2;
            if (ptr->array[mid] == value)
            {
                printf("index of %d = %d \n", value, mid);
                return R_OK;
            }
            if (ptr->array[mid] > value)
            {
                high = mid - 1;
            }
            else if (ptr->array[mid] < value)
            {
                low = mid + 1;
            }
        }
    }

    printf("element not found\n");
    return R_NOTOK;
}
static return_status_t stack_binary_index(stack_ls_t *ptr, uint32_t value, uint8_t *return_index)
{
    if (S_EMPTY == (check_status_empty(ptr)))
        return R_NOTOK;
    if (R_NOTOK == (bubble_sort_stack(ptr)))
        return R_NOTOK;

    uint8_t low = 0, high = ptr->stack_pointer, mid;
    while (high >= low)
    {
        mid = (low + high) / 2;
        if (ptr->array[mid] == value)
        {
            printf("%d\n", ptr->array[mid]);
            *return_index = mid;
            return R_OK;
        }
        if (ptr->array[mid] > value)
            high = mid - 1;
        if (ptr->array[mid] < value)
            low = mid + 1;
    }
    return R_NOTOK;
}
return_status_t stack_swap(stack_ls_t *stack, uint32_t value_stack, uint32_t new_value)
{
    uint8_t value_index = -1;
    if (S_EMPTY == (check_status_empty(stack)))
        return R_NOTOK;
    if (R_NOTOK == (stack_binary_index(stack, value_stack, &value_index)))
        return R_NOTOK;
    if ((value_stack && new_value) <= 0)
        return R_NOTOK;

    if (value_index != -1)
    {
        swap(&stack->array[value_index], &new_value);
        return R_OK;
    }
    return R_NOTOK;
}
return_status_t stack_size(stack_ls_t *stack, uint8_t *stack_size)
{
    if (S_EMPTY == (check_status_empty(stack)))
    {
        *stack_size = 0;
        return R_OK;
    }
    if (S_FULL == (check_status_full(stack)))
    {
        *stack_size = ARRAY_MAX_SIZE;
        return R_OK;
    }
    *stack_size = stack->stack_pointer + 1;
    return R_OK;
}