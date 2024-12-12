#ifndef _DSTACKARRAY_H_
#define _DSTACKARRAY_H_
#include <stdio.h>
#include <stdlib.h>
#include "Type_def_includes.h"
#define DEBUGG 1 // ifdef  print for debugging work

typedef enum{
    S_NOTOK ,
    S_OK,
    S_FULL ,
    S_EMPTY,
    S_NULL

}stack_status_t;
typedef struct{
    void **stack_pointer;
    sint32_t element_count;
    uint32_t stack_max_size;
    sint32_t stack_top;
}stack_t;
/**
 * @brief create stack
 * 
 * @param max_size max element of the stack
 * @param ret  return stack status R_OK if function works finne
 * @return stack_t* return pointer to the stack
 */
stack_t* creatStack(uint32_t max_size , stack_status_t * ret);
/**
 * @brief push element to the top of the stack
 * 
 * @param mystack pointer to the stack
 * @param item  item to be pushed
 * @return stack_status_t  R_OK if function goes well
 */
stack_status_t push(stack_t *mystack , void* item);
/**
 * @brief  pop the top of the stack and save poped value to the pop stack
 * 
 * @param mystack  stack to be poped
 * @param pop  stack to save poped value
 * @return stack_status_t  return S_OK if function goes well
 */
stack_status_t pop(stack_t *mystack , stack_t *pop);
/**
 * @brief print the top of the stack
 * 
 * @param mystack  pointer to the stack
 * @return stack_status_t  S_OK = 1 if function goes well
 */
void* stackTop(stack_t *mystack , stack_status_t *ret);
/**
 * @brief return  the top
 * 
 * @param mystack  pointer to the stack
 * @return stack_status_t  return S_OK if worked well
 */
stack_status_t Stack_dis(stack_t *mystack);
/**
 * @brief destroy all the stack
 * 
 * @param mystack pointer to stack
 * @return stack_status_t  S_ok if worked well
 */
stack_t* Stack_destroy(stack_t* mystack , stack_status_t * ret);


#endif