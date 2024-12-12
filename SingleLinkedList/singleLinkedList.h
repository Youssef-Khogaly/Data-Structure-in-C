#ifndef _SINGLELINKEDLIST_H_
#define _SINGLELINKEDLIST_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Types.h"
#define N_OK 1
#define N_NOTOK 0
#define N_Null 2

typedef struct node
{
   struct node *link;
   void *data;
   sint8 flag;
} list;

typedef struct
{
   list *front;
   list *rear;
} node;
/**
 * @brief inis  front and rear
 *
 * @param node  pointer to ptr_struct
 * @return uint8  retutnr 1 if worked well
 */
uint8 node_inis(node **ptr);
uint8 node_insert_end(node **node, void *data);
uint8 node_insert_beg(node **node, void *data);
/**
 * @brief insert a node only between two nodes
 *
 * @param node pointer to the Struct node pass by refrence
 * @param data void pointer
 * @param pos  the postion of the node  , the new node will insert after the pos node
 * @return uint8  return 1 if goes well
 */
uint8 node_insert_pos(node **node, void *data, uint64 pos);
void node_print(node *node);
sint64 get_length(node *node);
uint8 node_delete_beg(node **node);
uint8 node_delete_end(node **node);
uint8 node_delete_pos(node **node, uint64 pos);
uint8 node_rev(node **node);
uint8 sort_list(node **node);
uint8 selection_sort(node **node);
uint8 swap_node_pos(node **node, uint32 pos1, uint32 pos2);
void print_middle(node **node);
uint8 delete_sum_zero(node **node);
uint8 delete_sum_zero_sorted(node **node);
int toggle_bit(int x, int pos);
/**
 * @brief remove duplicated number form SORTED linked  list
 *
 * @param node double pointer to the list
 * @return uint8 return 1 if goes well
 */
uint8 delete_duplicated_sorted(node **node);

uint8 merg_nodes(node **node1, node **node2);

boolean detect_loop(node *ptr);
boolean detect_loop_Floys_Cycle(node *ptr);
uint8 detect_remove_loop_1(node **node);
uint8 detect_remove_loop_opt(node **node);
list *reverse_list_group(list *head, list **rear, int k, sint32 leng);
uint8 reverse_list_group_optimal(node** linked_list , int size);
uint8 Delete_N_node_after_M_nodes(node** linked_list , int m , int n );
list* Reverse_alternate_k(list *front , list ** rear , int k );
void* getNth_end(node* our_list , sint32 node_index);
boolean checkPalindrome_list(node* head);
uint8 rotate_list(node**linked_list , int k);
uint8 delete_list(node** linked_list);
#endif