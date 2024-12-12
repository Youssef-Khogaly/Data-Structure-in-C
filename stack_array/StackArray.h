#ifndef _STACKARRAY_H_
#define _STACKARRAY_H_
#include"block_chain.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define ARRAY_MAX_SIZE 5

typedef struct {
    uint32_t array[ARRAY_MAX_SIZE];
    sint8_t stack_pointer;
}stack_ls_t;

typedef enum stack_status{
        S_EMPTY ,
        S_FULL,
        S_NOT_FULL
        
}stack_status_t;




/**
    *@brief push a value to the top of stack
    *@param a pointer to the stack 
    *@param a uint32_t value 
    *@retval status of push process R_OK = 0 if the function process successfully
 */
return_status_t push(stack_ls_t *ptr  , uint32_t value );

/**
 * @brief delete the top of the stack
 * @param a poiter to the stack
 * @param a pointer to the pop_stack 
 * @retval return R_OK = 0 if the function process successfully
 */
return_status_t pop(stack_ls_t *ptr , stack_ls_t *stack_pop_pointer);
/**
*@brief print the top of the stack 
*@param a pointer to the stack
*@retval return_statut_t R_OK = 0 if the function processed successsfully
 */

return_status_t stack_top(stack_ls_t *ptr);

/**
 * @brief inisialized the stack_pointer to -1
 * 
 * @param pointer to the stack
 * @return return_status_t  R_OK = 0 if the funciton processed successfull
 */
return_status_t stack_init(stack_ls_t *ptr);
/**
 * @brief print all element of the stack
 * 
 * @param pointer to the stack
 * @return return_status_t  0 if the function processed successfull 
 */
return_status_t stack_dis(stack_ls_t *ptr);
/**
 * @brief repush the poped_value to the main stack
 * @param pointer to the main stack
 * @param pointer to the second stack
 * @retval return_status_t 0 if the function success
 */
return_status_t repush(stack_ls_t *ptr , stack_ls_t *pop);
/**
 * @brief sorting the stack from smallest to the bigger
 * 
 * @param pointer to the stack
 * @return return_status_t R_OK if function done 
 */
return_status_t bubble_sort_stack(stack_ls_t *ptr);
/**
 * @brief binary search for element in the stack and print its index if found
 * 
 * @param  pass pointer to the stack and the value
 * @return return_status_t return R_OK if found and print element index
 */
return_status_t stack_binarys(stack_ls_t *ptr , uint32_t value);
/**
 * @brief swap specific value in the stack with new value and a pointer to the stack
 * @param value in the stack and the new value
 * @return R_OK if the the function works well
 */
return_status_t stack_swap(stack_ls_t *stack , uint32_t value_stack , uint32_t new_value);
/**
 * @brief  get a stack size
 * 
 * @param stack pointer to the stack
 * @param stack_size pointer to save stack size 
 * @return return_status_t  return R_OK 
 */
return_status_t stack_size (stack_ls_t *stack , uint8_t *stack_size);
#endif