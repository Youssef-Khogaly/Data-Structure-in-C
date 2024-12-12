#include "singleLinkedList.h"

static void delete_node(node ***node, list **ptr)
{
    list *temp = (**node)->front;
    list *temp_free = NULL;
    if (!(**node))
        return;
    else if ((**node)->front == 0)
        return;
    else
    {
        if (*ptr == (**node)->front)
        {
            temp_free = *ptr;
            (**node)->front = (**node)->front->link;
            free(temp_free);
            temp_free = NULL;
            return;
        }
        else if (*ptr == (**node)->rear)
        {
            while ((temp)->link != *ptr)
            {
                (temp) = (temp)->link;
            }
            temp_free = *ptr;
            (**node)->rear = temp;
            (**node)->rear->link = NULL;
            free(temp_free);
            temp_free = NULL;
            return;
        }
        else
        {
            while ((temp)->link != *ptr)
                temp = (temp)->link;

            temp_free = *ptr;
            temp->link = (*ptr)->link;
            free(temp_free);
            temp_free = NULL;
            return;
        }
    }
}

// function swapping only for sorting , only 2 nodes in row
static void swap_node(list *node1, list *node2, node **node)
{
    if ((NULL == node1) || (NULL == node2) || (NULL == *node))
        return;
    if ((*node)->front == NULL)
        return;

    list *front0 = (*node)->front;
    list *prev1 = front0;
    if (node1 == front0)
    {
        node1->link = node2->link;
        node2->link = node1;
        (*node)->front = node2;
        return;
    }
    else
    {
        while (prev1->link != node1)
        {
            prev1 = prev1->link;
        }
        if (prev1)
        {
            node1->link = node2->link;
            node2->link = node1;
            prev1->link = node2;
            if (node1->link == NULL)
            {
                (*node)->rear = node1;
            }
            if (node2->link == NULL)
            {
                (*node)->rear = node2;
            }
            return;
        }
        return;
    }
}
static list *create_node(void **data)
{
    if (!data)
    {
        return NULL;
    }
    else
    {
        list *ptr = (list *)calloc(1, sizeof(list));
        ptr->data = *data;
        ptr->flag = 0;
        ptr->link = NULL;
        return ptr;
    }
}
static list *create_node_int(int data)
{
    if (!data)
    {
        return NULL;
    }
    else
    {
        list *ptr = (list *)calloc(1, sizeof(list));
        ptr->data = (void *)data;
        ptr->flag = 0;
        ptr->link = NULL;
        return ptr;
    }
}
sint64 get_length(node *node)
{
    if (!node)
    {
        return 0;
    }
    sint64 return_val = 0;
    list *ptr = node->front;
    while (ptr != NULL)
    {
        return_val++;
        ptr = ptr->link;
    }
    return return_val;
}
uint8 node_inis(node **ptr)
{
    *ptr = (node *)calloc(1, sizeof(node));
    if (!ptr)
    {
        return N_Null;
    }

    (*ptr)->front = NULL;
    (*ptr)->rear = NULL;
    return N_OK;
}

void node_print(node *node)
{
    if (!node)
    {
        printf("Passing Null pointer or empty list to print function\n");
        return;
    }

    list *ptr = node->front;
    while (ptr != NULL)
    {
        printf("%d ", *((int *)ptr->data));
        ptr = ptr->link;
    }
    printf("\n");
    free(ptr);
    ptr = NULL;
    return;
}

uint8 node_insert_end(node **node, void *data)
{
    list *pointer = create_node(&data);
    // check null pointers
    if ((NULL == node) || (NULL == data) || (NULL == pointer))
    {
        free(pointer);
        pointer = NULL;
        return N_Null;
    }
    else
    {
        /* check if linked list is empty if front == null */
        if (!(*node)->front)
        {
            (*node)->front = pointer;
            (*node)->rear = pointer;
            return N_OK;
        }
        else
        {
            (*node)->rear->link = pointer;
            (*node)->rear = pointer;
            return N_OK;
        }
    }
}

uint8 node_insert_beg(node **node, void *data)
{
    list *ptr = create_node(&data);

    if ((NULL == node) || (NULL == data) || (NULL == ptr))
    {
        free(ptr);
        ptr = NULL;
        return N_Null;
    }
    else
    {
        /* if list is empty  front == null!*/
        if (!(*node)->front)
        {
            (*node)->front = ptr;
            (*node)->rear = ptr;
            return N_OK;
        }
        else
        {
            ptr->link = (*node)->front;
            (*node)->front = ptr;
            return N_OK;
        }
    }
}

uint8 node_insert_pos(node **node, void *data, uint64 pos)
{
    if ((NULL == node) || (NULL == data))
    {
        return N_Null;
    }
    else if (pos > (get_length(*node)) || (pos <= 0))
    {
        return N_NOTOK;
    }
    else
    {
        list *current = (*node)->front;
        list *ptr = create_node(&data);
        if (!ptr)
        {
            return N_Null;
        }
        if (pos == 1)
        {
            ptr->link = current->link;
            current->link = ptr;
            return N_OK;
        }
        else
        {
            for (int i = 2; i <= pos; i++)
            {
                current = current->link;
            }
            if (current != NULL)
            {
                ptr->link = current->link;
                current->link = ptr;
                return N_OK;
            }
            else
            {
                return N_NOTOK;
            }
        }
        return N_NOTOK;
    }
    return N_NOTOK;
}
uint8 node_delete_beg(node **node)
{
    if (!node)
    {
        return N_Null;
    }
    /* check if node is empty*/
    else if ((*node)->front == NULL)
    {
        return N_NOTOK;
    }
    else
    {
        if ((get_length(*node)) == 1)
        {
            free(*node);
            *node = NULL;
            return N_OK;
        }
        list *ptr = (*node)->front;
        (*node)->front = (*node)->front->link;
        free(ptr);
        ptr = NULL;
        return N_OK;
    }
    return N_NOTOK;
}

uint8 node_delete_end(node **node)
{
    if (!node)
    {
        return N_Null;
    }
    else if ((get_length(*node)) == 0)
    {
        printf("ERROR passing empty list to delete list function , ret = %i\n", N_NOTOK);
        return N_NOTOK;
    }
    else
    {
        // check if the list have only one element
        if ((get_length(*node)) == 1)
        {
            free(*node);
            *node = NULL;
        }
        else
        {
            list *ptr = (*node)->front;
            while (ptr->link->link != NULL)
            {
                ptr = ptr->link;
            }
            free((*node)->rear);
            (*node)->rear = NULL;
            (*node)->rear = ptr;
            (*node)->rear->link = NULL;
            return N_OK;
        }
    }
}

uint8 node_delete_pos(node **node, uint64 pos)
{
    sint64 length = get_length(*node);
    if (!node)
    {
        return N_Null;
    }
    else if (length == 0)
    {
        printf("empty LIST!! passed to Delete_pos func\n");
        return N_NOTOK;
    }
    else
    {
        if ((length == 1) || (pos >= length))
        {
            printf("please use delete_beg  function \n");
            return N_NOTOK;
        }
        else
        {
            list *ptr = (*node)->front;
            list *ptr_del = NULL;
            for (int i = 2; i < pos; i++)
            {
                ptr = ptr->link;
            }
            ptr_del = ptr->link;
            ptr->link = ptr_del->link;
            free(ptr_del->link);
            ptr_del->link = NULL;
            free(ptr_del);
            ptr_del = NULL;
            return N_OK;
        }
    }
}

uint8 node_rev(node **node)
{
    sint64 length = get_length(*node);
    if (!node)
    {
        return N_Null;
    }
    else if (length == 0)
    {
        return N_NOTOK;
    }
    else
    {
        list *front = (*node)->front;
        list *temp = NULL;
        list *temp2;
        while (front != NULL)
        {
            temp2 = front->link;
            front->link = temp;
            if (front->link == NULL)
            {
                (*node)->rear = front;
            }
            temp = front;
            front = temp2;
        }
        (*node)->front = temp;
        return N_OK;
    }
}

uint8 sort_list(node **node)
{
    boolean swapped = 0;
    list *ptr = NULL;
    list *last_ptr = NULL;
    if (!node)
    {
        return N_Null;
    }
    // check if list is empty
    else if ((*node)->front == NULL)
    {
        return N_NOTOK;
    }
    else
    {
        do
        {
            swapped = 0;
            ptr = (*node)->front;

            while (ptr->link != last_ptr)
            {

                if (*((int *)ptr->data) > *((int *)ptr->link->data))
                {
                    swap_node(ptr, ptr->link, node);
                    swapped = 1;
                    continue; // continue  to avoid ptr = ptr->link line when nodes swapped , bucsae swap_node function swap nodes not data
                }
                ptr = ptr->link;
            }
            last_ptr = ptr; //  l

        } while (swapped);
        return N_OK;
    }
}
uint8 selection_sort(node **node)
{
    if (!node)
    {
        return N_Null;
    }
    else if ((*node)->front == NULL)
        return N_NOTOK;
    else
    {
        list *ptr;
        boolean swapped;
        do
        {
            ptr = (*node)->front;
            swapped = 0;
            if (!ptr)
            {
                break;
            }
            while (ptr->link != NULL)
            {
                if (!ptr)
                {
                    break;
                }
                if (*((int *)ptr->data) > *((int *)ptr->link->data))
                {
                    swap_node(ptr, ptr->link, node);
                    swapped = 1;
                    continue; // continue to avoid ptr = ptr->link line bucsae swap function swap nodes not data
                }
                ptr = ptr->link;
            }
        } while (swapped);
        return N_OK;
    }
}

uint8 swap_node_pos(node **node, uint32 pos1, uint32 pos2)
{
    sint32 max_pos = get_length(*node);
    list *front = (*node)->front;
    list *temp = front;
    list *prev1 = NULL;
    list *prev2 = NULL;
    list *curr1 = NULL;
    list *curr2 = NULL;
    if (!node)
        return N_Null;
    else if ((pos1 > max_pos) || (pos2 > max_pos))
    {
        return N_NOTOK;
    }
    else if (pos1 == pos2)
    {
        return N_OK;
    }
    else
    {

        for (int i = 1; (i <= max_pos) && (temp != NULL); i++)
        {

            if (i == (pos1 - 1))
            {
                prev1 = temp;
            }
            if (i == (pos1))
            {
                curr1 = temp;
            }
            if (i == (pos2 - 1))
            {
                prev2 = temp;
            }
            if (i == (pos2))
            {
                curr2 = temp;
            }

            temp = temp->link;
        }

        if ((NULL == curr1) || (NULL == curr2))
            return N_Null;
        // prev1 not equal null , curr1 not a head
        if (prev1)
        {
            prev1->link = curr2;
        }
        // curr1 a head;
        else
        {
            (*node)->front = curr2;
        }
        // prev2 not equal null , curr2 not a head
        if (prev2)
        {
            prev2->link = curr1;
        }
        // curr2 a head
        else
        {
            (*node)->front = curr1;
        }

        temp = curr1->link;
        curr1->link = curr2->link;
        curr2->link = temp;

        if (curr2->link == NULL)
        {
            (*node)->rear = curr2;
        }
        if (curr1->link == NULL)
            (*node)->rear = curr1;

        return N_OK;
    }
}

void print_middle(node **node)
{
    sint32 length = get_length(*node);
    sint32 mid;
    list *temp = (*node)->front;
    sint32 i = 1;
    if (!node)
        return;
    if (length <= 0)
        return;
    if (length % 2 == 0)
    {
        mid = (length) / 2;
    }
    else
    {
        mid = (length + 1) / 2;
    }
    while (i < mid)
    {
        temp = temp->link;
        i++;
    }
    printf("middle of the list = %i\n", *((int *)temp->data));
    return;
}
uint8 delete_sum_zero(node **node)
{
    list *ptr = (*node)->front;
    list *ptr2 = (*node)->front;
    if (!node)
        return N_Null;
    if ((*node)->front == NULL)
        return N_NOTOK;

    for (int i = 1; (ptr != NULL); i++)
    {
        if (i == 1)
        {
            ptr = (*node)->front;
            ptr2 = ptr->link;
        }
        else
        {
            ptr = ptr->link;
            if (!ptr)
                break;
            ptr2 = ptr->link;
        }
        while ((ptr2 != NULL))
        {

            if (*((int *)ptr->data) + *((int *)ptr2->data) == 0)
            {
                delete_node(&node, &ptr);
                delete_node(&node, &ptr2);
                ptr = (*node)->front;
                ptr2 = ptr->link;
            }
            else
                ptr2 = ptr2->link;
        }
    }
    return N_OK;
}
uint8 delete_sum_zero_sorted(node **node)
{
    list *ptr = (*node)->front;
    list *ptr2 = NULL;
    int data_ptr, data_ptr2;
    int i = 1;
    if (!(*node))
        return N_Null;

    else if ((*node)->front == NULL)
        return N_Null;

    else
    {
        while (ptr != NULL)
        {
            if (i)
            {
                i--;
                ptr = (*node)->front;
                ptr2 = (*node)->front->link;
            }
            else
            {
                ptr = ptr->link;
                if (!ptr)
                    return N_OK;
                ptr2 = ptr->link;
            }
            if (*((int *)ptr->data) > 0)
                return N_OK;

            while (ptr2 != NULL)
            {
                data_ptr = *((int *)ptr->data);
                data_ptr2 = *((int *)ptr2->data);

                if ((data_ptr2 > 0) && (data_ptr > 0))
                    return N_OK;
                else if (data_ptr2 > (-data_ptr))
                {
                    break;
                }
                else if (data_ptr + data_ptr2 == 0)
                {
                    delete_node(&node, &ptr);
                    delete_node(&node, &ptr2);
                    ptr = (*node)->front;
                    ptr2 = ptr->link;
                }
                else
                    ptr2 = ptr2->link;
            }
        }
        return N_OK;
    }
}

uint8 delete_duplicated_sorted(node **node)
{
    list *temp = NULL;    // traverse pointer
    list *nxt_nxt = NULL; // pointer to point to the next of the node that will be deleted
    int data, data_nxt;   // to store nodes data for better readable code
    int i = 1;
    if (!(*node))
        return N_Null;

    // check if list is empty
    else if ((*node)->front == NULL)
        return N_NOTOK;

    // only one element in the list
    else if ((*node)->front == (*node)->rear)
        return N_OK;
    else
    {

        temp = (*node)->front;
        while (temp->link != NULL)
        {
            data = *((int *)temp->data);
            data_nxt = *((int *)temp->link->data);

            if (data == data_nxt)
            {
                nxt_nxt = temp->link->link;
                free(temp->link);
                temp->link = nxt_nxt;
                // check if temp pointer  is the rear of the list
                if (temp->link == NULL)
                    (*node)->rear = temp;
            }
            else
            {

                temp = temp->link;
            }
        }
        return N_OK;
    }
}

uint8 merg_nodes(node **node1, node **node2)
{
    list *current_1 = (*node1)->front;
    list *current_2 = (*node2)->front;
    list *next_1 = NULL;
    list *next_2 = NULL;
    if ((*node1 == NULL) || (*node2 == NULL))
        return N_Null;
    else if (((*node1)->front == NULL) || ((*node2)->front == NULL))
        return N_NOTOK;
    else
    {
        if ((current_1 == NULL) || (current_2 == NULL))
            return N_NOTOK;
        else
        {
            while ((current_1 != NULL) && (current_2 != NULL))
            {
                next_1 = current_1->link; // save the next node
                next_2 = current_2->link; // save the next node

                current_1->link = current_2;
                current_2->link = next_1;
                if (current_2->link == NULL) // check if the current pointer point to the rear of the list
                {
                    (*node1)->rear = current_2; // make rear pointer point to current_2
                }
                current_1 = next_1;
                current_2 = next_2;
            }

            (*node2)->front = next_2;

            return N_OK;
        }
    }
}

boolean detect_loop(node *ptr)
{
    list *temp = ptr->front;
    if (!ptr)
        return 0;
    if (ptr->front == NULL)
        return 0;

    while (temp != NULL)
    {
        if (temp->flag == 0)
        {
            temp->flag = 1;
            temp = temp->link;
        }
        else
        {
            return 1;
        }
    }
    return 0;
}

boolean detect_loop_Floys_Cycle(node *ptr)
{
    list *p_slow = ptr->front;
    list *p_fast = ptr->front;

    while ((p_fast != NULL) && (p_slow != NULL) && (p_fast->link != NULL))
    {
        p_fast = p_fast->link->link;
        p_slow = p_slow->link;
        if (p_fast == p_slow)
            return 1;
    }
    return 0;
}

uint8 detect_remove_loop_1(node **node)
{
    list *p_fast = (*node)->front;
    list *p_slow = (*node)->front;
    list *loop_node = NULL;
    if (!(*node))
        return N_Null;
    if (((*node)->front == NULL) || ((*node)->front->link == NULL))
        return N_NOTOK;

    while ((p_fast != NULL) && (p_fast->link != NULL) && (p_slow != NULL))
    {
        p_fast = p_fast->link->link;
        p_slow = p_slow->link;
        if (p_fast == p_slow)
        {
            loop_node = p_fast;
            break;
        }
    }
    if (!loop_node)
        return 0;

    p_slow = (*node)->front;

    while (1)
    {
        p_fast = loop_node;
        while ((p_fast->link != loop_node) && (p_fast->link != p_slow))
        {
            p_fast = p_fast->link;
        }
        if (p_fast->link == p_slow->link)
        {
            p_fast->link = NULL;
            return 1;
        }
        p_slow = p_slow->link;
    }
}
uint8 detect_remove_loop_opt(node **node)
{
    list *p_fast = (*node)->front;
    list *p_slow = (*node)->front;
    list *loop_node = NULL;
    if (!(*node))
        return N_OK;
    // detect the loop node
    while ((p_fast->link != NULL) && (p_fast != NULL) && (p_slow != NULL))
    {
        p_slow = p_slow->link;
        p_fast = p_fast->link->link;
        if (p_fast == p_slow)
        {
            loop_node = p_fast;
            break;
        }
    }
    // check if loop node = null
    if (!loop_node)
        return N_OK; // there is no loop
    else
    {
        p_slow = (*node)->front;
        // to get the start of the loop
        while (p_fast->link != p_slow->link)
        {
            p_fast = p_fast->link;
            p_slow = p_slow->link;
        }
        // after loop end p_fast point to the start of the loop node
        p_fast->link = NULL;
        return N_OK;
    }
}

list *reverse_list_group(list *head, list **rear, int k, sint32 leng)
{
    list *current = head;
    list *next = NULL;
    list *prev = NULL;
    int i = 1;

    if (!(head))
        return NULL;
    if (k <= 0)
        return NULL;
    if (k > leng)
        return head;

    while ((current != NULL) && (i <= k))
    {
        next = current->link;
        current->link = prev;
        prev = current;
        current = next;

        if (prev->link == NULL)
            (*rear) = prev;
        i++;
    }
    if (next != NULL)
    {
        head->link = reverse_list_group(next, rear, k, leng);
    }

    return prev;
}
uint8 reverse_list_group_optimal(node **linked_list, int size)
{
    int count, data = -1;
    list *dummy = create_node_int(data);
    dummy->link = (*linked_list)->front;
    list *current = dummy;
    list *prev = dummy;
    list *next = dummy;

    if (!(*linked_list))
        return N_Null;
    if (size <= 0)
        return N_NOTOK;
    if ((*linked_list)->front == NULL)
        return N_NOTOK;
    while (next != NULL)
    {
        current = prev->link;
        if (current == NULL || current->link == NULL) // to break the loop if only one element remain
            break;
        next = current->link;
        for (count = 1; count < size && (next != NULL); count++)
        {
            current->link = next->link;
            next->link = prev->link;
            prev->link = next;
            next = current->link;
        }
        prev = current;
    }
    (*linked_list)->front = dummy->link;
    (*linked_list)->rear = current;
    return N_OK;
}

uint8 Delete_N_node_after_M_nodes(node **linked_list, int m, int n)
{
    list *M_node = (*linked_list)->front;
    list *N_node = NULL;
    list *temp = NULL;
    sint64 nodes_left = get_length(*linked_list);
    if (!(*linked_list))
        return N_Null;
    else if ((*linked_list)->front == NULL)
        return N_NOTOK;
    else if ((*linked_list)->front->link == NULL)
        return N_NOTOK;
    else if ((m <= 0) || (n <= 0) || (m > nodes_left) || (n > nodes_left))
        return N_NOTOK;
    else
    {
        while ((M_node != NULL) && (M_node->link != NULL) && (nodes_left >= n) && (nodes_left >= m))
        {
            // travesing the M_node to the node m.th
            for (int i = 1; i < m && (M_node != NULL); i++)
            {
                M_node = M_node->link;
            }

            if (!M_node)
                break;
            // Make N_node pointer to first node to delete
            N_node = M_node->link;

            // deleting n nodes
            for (int i = 1; (i <= n) && (N_node != NULL); i++)
            {
                temp = N_node;
                N_node = N_node->link;
                free(temp);
                temp = NULL;
            }
            // make M_node link point to the N_node
            M_node->link = N_node;

            if (M_node->link == NULL)
                (*linked_list)->rear = M_node;

            M_node = N_node;

            // for break the loop if there is no enough nodes left
            nodes_left -= n;
        }

        return N_OK;
    }
}

list *Reverse_alternate_k(list *front, list **rear, int k)
{
    int data = -1;
    list *dummy = create_node_int(data);
    list *curr = dummy;
    list *prev = dummy;
    list *next = dummy;
    if ((front == NULL) || (*rear = NULL) || (k <= 0))
        return front;
    else
    {
        dummy->link = front;
        while ((next != NULL) && (prev->link != NULL))
        {
            curr = prev->link;
            next = curr->link;
            for (int i = 1; i < k && (next != NULL); i++)
            {
                curr->link = next->link;
                next->link = prev->link;
                prev->link = next;
                next = curr->link;
            }
            prev = curr;

            for (int i = 1; i <= k && (prev->link != NULL); i++)
                prev = prev->link;

            if (prev->link == NULL)
            {
                *rear = prev;
                break;
            }
        }

        return dummy->link;
    }
}

void *getNth_end(node *our_list, sint32 node_index)
{
    sint64 size = get_length(our_list);
    list *head = our_list->front;
    sint64 index = size - node_index;
    int return_value;
    void *ret;
    if (!our_list)
        return NULL;
    else if (our_list->front == NULL)
        return NULL;
    else if (node_index > size || (node_index <= 0))
    {
        return_value = -1;
        ret = &return_value;
        return ret;
    }
    else
    {
        for (int count = 1; count <= index && (head != NULL); count++)
        {
            head = head->link;
        }
        ret = head->data;
        return ret;
    }
}
boolean checkPalindrome_list(node *head)
{
    boolean ret;
    node *stack = NULL;
    uint8 return_value = node_inis(&stack);
    list *temp = head->front;
    list *temp2 = NULL;
    if (!head)
        return 0;
    else if (head->front == NULL)
        return 0;
    else if (return_value != 1)
        return 0;
    else
    {
        while (temp != NULL && (return_value == 1))
        {
            return_value = node_insert_beg(&stack, temp->data);
            temp = temp->link;
        }
        temp = head->front;
        temp2 = stack->front;
        while ((temp != NULL) && (temp2 != NULL))
        {
            if (*((char *)temp->data) != *((char *)temp2->data))
            {
                return 0;
            }
            else
            {
                temp = temp->link;
                temp2 = temp2->link;
            }
        }
        return 1;
    }
}
uint8 rotate_list(node **linked_list, int k)
{
    sint64 size = get_length(*linked_list);
    list *old_head = (*linked_list)->front;
    list *temp = (*linked_list)->front;
    list *temp2 = NULL;
    if (!(*linked_list))
        return N_Null;
    else if ((*linked_list) == NULL)
        return N_NOTOK;
    else if (k > size || k <= 0)
        return N_NOTOK;
    else
    {
        for (int count = 1; (count < k) && (temp != NULL); count++)
        {
            temp = temp->link;
        }
        if (!temp)
            return N_Null;

        temp2 = temp->link;
        temp->link = NULL;
        (*linked_list)->rear = temp;
        (*linked_list)->front = temp2;
        while (temp2->link != NULL)
            temp2 = temp2->link;
        temp2->link = old_head;
        return N_OK;
    }
}

uint8 delete_list(node **linked_list)
{
    list *curr = (*linked_list)->front;
    list *next = NULL;
    if (!(*linked_list))
        return N_OK;
    else if ((*linked_list)->front == NULL)
    {
        free((*linked_list)->front);
        free(*linked_list);
        *linked_list = NULL;
        return N_OK;
    }
    else
    {
        while (curr != NULL)
        {
            next = curr->link;
            free(curr);
            curr = next;
        }
        (*linked_list)->front = NULL;
        (*linked_list)->rear = NULL;
        free(*linked_list);
        *linked_list = NULL;
        return N_OK;
    }
}
