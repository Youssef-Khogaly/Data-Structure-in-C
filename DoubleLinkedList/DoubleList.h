#ifndef _DOUBLELIST_H_
#define _DOUBLELIST_H_
#include <stdio.h>
#include <stdlib.h>
#include "Types.h"
#define lIST_NULL 2
#define LIST_OK 1
#define LIST_NOK 0
typedef struct Doulbe_list{
    sint32 data;
    struct Doulbe_list* left;
    struct Doulbe_list* right;
}DLL;

typedef struct
{
    DLL* head;
    DLL* tail;
}list_ptr;

list_ptr *node_inis(void);
DLL *create_node(uint32 data);
void printList_forward(list_ptr *list);
void printList_reverse(list_ptr *list);
uint8 insert_end(list_ptr **list, sint32 data);
uint8 insert_beg(list_ptr **list, uint32 data);
sint32 list_length(list_ptr *list);
uint8 insert_after(list_ptr **list, uint32 data, uint32 nth);
uint8 delete_beg(list_ptr **list);
uint8 delete_end(list_ptr **list);
uint8 delete_pos(list_ptr **list, uint32 pos);
uint8 swap_nodes_pos(list_ptr **list, uint32 pos1, uint32 pos2);
void swap_nodes_ptr(list_ptr **list, DLL *curr1, DLL *curr2);
uint8 list_bubble_sort(list_ptr **list);
uint8 list_selection_sort(list_ptr **list);
uint8 list_search(list_ptr **list, uint32 data);
uint8 list_search_sorted(list_ptr **list, uint32 data);
uint8 reverse_list(list_ptr **list);
void print_middle(list_ptr *list);
uint8 delete_duplicated(list_ptr **list);
uint8 delete_duplicated_sorted(list_ptr **list);
void delete_node_ptr(list_ptr **list, DLL *delete_node);
uint8 delete_two_sum_zero_unsorted(list_ptr** list);
uint8 delete_two_sum_zero_sorted(list_ptr** list);
uint8 merge_list_alternate(list_ptr** list , list_ptr** list2);
uint8 detect_loop_and_remove(list_ptr** list);
uint8 delete_list(list_ptr** list);

#endif