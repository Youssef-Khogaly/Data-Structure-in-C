#include "DoubleList.h"

list_ptr *node_inis(void)
{
    list_ptr *ptr = NULL;
    ptr = (list_ptr *)calloc(1, sizeof(list_ptr));
    if (!ptr)
        return NULL;
    ptr->head = NULL;
    ptr->tail = NULL;
    return ptr;
}

DLL *create_node(uint32 data)
{
    DLL *temp = (DLL *)calloc(1, sizeof(DLL));
    if (!temp)
        return NULL;
    temp->left = NULL;
    temp->right = NULL;
    temp->data = data;
    return temp;
}
void printList_forward(list_ptr *list)
{

    if (!list)
        return;
    else if (list->head == NULL)
        return;
    else
    {
        DLL *temp = list->head;
        while (temp != NULL)
        {
            printf("%i ", temp->data);
            temp = temp->right;
        }
        printf("\n");
        return;
    }
}
void printList_reverse(list_ptr *list)
{
    DLL *temp = list->tail;
    if (!list)
        return;
    else if (list->tail == NULL)
        return;
    else
    {
        while (temp != NULL)
        {
            printf("%u ", temp->data);
            temp = temp->left;
        }
        printf("\n");
        return;
    }
    return;
}
uint8 insert_end(list_ptr **list, sint32 data)
{
    DLL *temp = create_node(data);
    DLL *old_tail = (*list)->tail;
    if (!(*list))
        return lIST_NULL;
    else
    {

        if ((*list)->head == NULL)
        {
            (*list)->head = temp;
            (*list)->tail = (*list)->head;
            return LIST_OK;
        }
        else
        {
            old_tail->right = temp;
            temp->left = old_tail;
            (*list)->tail = temp;
            return LIST_OK;
        }
    }
    return LIST_NOK;
}
uint8 insert_beg(list_ptr **list, uint32 data)
{
    DLL *temp = create_node(data);
    DLL *old_head = (*list)->head;
    if (!(*list))
        return lIST_NULL;
    else
    {
        if ((*list)->head == NULL)
        {
            (*list)->head = temp;
            (*list)->tail = temp;
            return LIST_OK;
        }
        else
        {
            old_head->left = temp;
            temp->right = old_head;
            (*list)->head = temp;
            return LIST_OK;
        }
    }
    return LIST_NOK;
}
sint32 list_length(list_ptr *list)
{
    DLL *ptr = list->head;
    sint32 size = 0;
    if (!list)
        return -1;
    else
    {
        while (ptr != NULL)
        {
            ptr = ptr->right;
            size++;
        }
        return size;
    }
}
uint8 insert_after(list_ptr **list, uint32 data, uint32 nth)
{
    sint32 list_size = list_length(*list);
    DLL *next = (*list)->head; // to save the next of nth node
    DLL *prev = (*list)->head; // to traverse to nth node aka new prev
    DLL *temp = create_node(data);
    int count;
    if (!(*list))
        return lIST_NULL;
    else if (nth >= list_size)
        return LIST_NOK;
    else if (nth <= 0)
        return LIST_NOK;
    else
    {
        for (count = 1; count < nth && (prev != NULL); count++)
        {
            prev = prev->right;
        }
        if (!prev)
            return LIST_NOK;

        next = prev->right;
        // add the new node
        prev->right = temp;
        temp->right = next;
        temp->left = prev;
        return LIST_OK;
    }
    return LIST_NOK;
}
uint8 delete_beg(list_ptr **list)
{
    DLL *temp = (*list)->head;
    if (!(*list))
        return lIST_NULL;
    else if ((*list)->head == NULL)
        return LIST_NOK;
    else if ((*list)->head->right == NULL)
    {
        free((*list)->head);
        (*list)->head = NULL;
        (*list)->tail = NULL;
        return LIST_OK;
    }
    else
    {
        (*list)->head = (*list)->head->right;
        (*list)->head->left = NULL;
        // delete the first node
        temp->right = NULL;
        free(temp);
        temp = NULL;
        return LIST_OK;
    }
    return LIST_NOK;
}
uint8 delete_end(list_ptr **list)
{
    DLL *temp = (*list)->tail;
    if (!(*list))
        return lIST_NULL;
    else if ((*list)->tail == NULL)
        return LIST_NOK;
    else if ((*list)->tail->left == NULL)
    {
        free((*list)->tail);
        (*list)->tail = NULL;
        (*list)->head = NULL;

        return LIST_OK;
    }
    else
    {

        (*list)->tail = (*list)->tail->left;
        (*list)->tail->right = NULL;
        // delete node
        temp->left = NULL;
        free(temp);
        temp = NULL;
        return LIST_OK;
    }
    return LIST_NOK;
}
uint8 delete_pos(list_ptr **list, uint32 pos)
{
    sint32 size = list_length(*list);
    DLL *curr = (*list)->head;
    DLL *prev = NULL;
    DLL *next = NULL;
    sint32 count;
    if (!(*list))
        return lIST_NULL;
    else if ((*list)->head == NULL)
        return LIST_NOK;
    else if ((pos <= 1) || (pos >= size))
        return LIST_NOK;
    else
    {
        for (count = 1; count < pos && (curr != NULL); count++)
        {
            curr = curr->right;
        }
        if (!curr)
            return lIST_NULL;
        // saving left and right nodes
        prev = curr->left;
        next = curr->right;
        // delete the node
        curr->left = NULL;
        curr->right = NULL;
        prev->right = next;
        next->left = prev;
        free(curr);
        curr = NULL;
        return LIST_OK;
    }
    return LIST_NOK;
}
uint8 swap_nodes_pos(list_ptr **list, uint32 pos1, uint32 pos2)
{
    sint32 list_size = list_length(*list);
    DLL *curr1 = (*list)->head;
    DLL *curr2 = (*list)->head;
    DLL *prev1 = NULL;
    DLL *next1 = NULL;
    DLL *prev2 = NULL;
    DLL *next2 = NULL;
    sint32 count;
    if (!(*list))
        return lIST_NULL;
    else if ((*list)->head == NULL)
        return LIST_NOK;
    else if ((pos1 > list_size) || (pos1 <= 0) || (pos2 > list_size) || (pos2 <= 0))
        return LIST_NOK;
    else
    {
        for (count = 1; count < pos1 && (curr1 != NULL); count++)
        {
            curr1 = curr1->right;
        }
        for (count = 1; count < pos2 && (curr2 != NULL); count++)
        {
            curr2 = curr2->right;
        }
        if ((!curr1) || (!curr2))
            return lIST_NULL;
        // saving prev1 and next1
        prev1 = curr1->left;
        next1 = curr1->right;
        prev2 = curr2->left;
        next2 = curr2->right;
        // swap nodes
        curr1->right = next2;
        curr1->left = prev2;
        curr2->right = next1;
        curr2->left = prev1;
        // change left and right of prev and next
        if (prev1 != NULL)
            prev1->right = curr2;
        if (next1 != NULL)
            next1->left = curr2;
        if (prev2 != NULL)
            prev2->right = curr1;
        if (next2 != NULL)
            next2->left = curr1;
        if ((*list)->head == curr1)
        {
            (*list)->head = curr2;
        }
        else if ((*list)->head == curr2)
        {
            (*list)->head = curr1;
        }
        if ((*list)->tail == curr1)
            (*list)->tail = curr2;

        else if ((*list)->tail == curr2)
            (*list)->tail = curr1;

        return LIST_OK;
    }
    return LIST_NOK;
}

void swap_nodes_ptr(list_ptr **list, DLL *curr1, DLL *curr2)
{
    DLL *prev1 = NULL;
    DLL *next1 = NULL;
    DLL *prev2 = NULL;
    DLL *next2 = NULL;
    if (!(*list) || !(curr1) || !(curr2))
        return;
    else if ((*list)->head == NULL || ((*list)->head == (*list)->tail))
        return;
    else
    {
        prev1 = curr1->left;
        next1 = curr1->right;
        prev2 = curr2->left;
        next2 = curr2->right;
        // swapping nodes
        if ((curr2->left != curr1) && (curr1->right != curr2))
        {
            curr1->right = next2;
            curr1->left = prev2;
            curr2->right = next1;
            curr2->left = prev1;
            // swaping prev and next links
            if (prev1 != NULL)
                prev1->right = curr2;
            if (next1 != NULL)
                next1->left = curr2;
            if (prev2 != NULL)
                prev2->right = curr1;
            if (next2 != NULL)
                next2->left = curr1;
        }
        else
        {
            curr1->right = next2;
            curr1->left = curr2;
            curr2->left = prev1;
            curr2->right = curr1;
            if (prev1 != NULL)
                prev1->right = curr2;
            if (next2 != NULL)
                next2->left = curr1;
        }
        // updating head and tail if needed
        if ((*list)->head == curr1)
            (*list)->head = curr2;
        else if ((*list)->head == curr2)
            (*list)->head = curr1;

        if ((*list)->tail == curr1)
            (*list)->tail = curr2;
        else if ((*list)->tail == curr2)
            (*list)->tail = curr1;

        return;
    }
    return;
}
uint8 list_bubble_sort(list_ptr **list)
{
    DLL *temp1 = (*list)->head;
    DLL *temp2 = NULL;
    boolean swapped = 0;
    sint32 i = 0;
    sint32 count = 1;
    sint32 list_size = list_length(*list);
    if (!(*list))
        return lIST_NULL;
    else if ((*list)->head == NULL)
        return LIST_NOK;
    else if ((*list)->head == (*list)->tail)
        return LIST_OK;
    else
    {
        do
        {
            swapped = 0;
            temp1 = (*list)->head;
            temp2 = temp1->right;
            for (count = 1; count < (list_size - i) && (temp2 != NULL); count++)
            {
                if (temp1->data > temp2->data)
                {
                    swap_nodes_ptr(list, temp1, temp2);
                    swapped = 1;
                    temp2 = temp1->right;
                    continue;
                }
                temp1 = temp1->right;
                temp2 = temp1->right;
            }
            i++;

        } while (swapped);
        return LIST_OK;
    }
    return LIST_NOK;
}
uint8 list_selection_sort(list_ptr **list)
{
    DLL *head = (*list)->head;
    DLL *temp = NULL;
    DLL *min = NULL;
    if (!(*list))
        return lIST_NULL;
    else if ((*list)->head == NULL)
        return lIST_NULL;
    else if ((*list)->head == (*list)->tail)
        return LIST_OK;
    else
    {
        while (head->right != NULL)
        {
            temp = head->right;
            min = head;
            while (temp != NULL)
            {
                if (min->data > temp->data)
                    min = temp;

                temp = temp->right;
            }
            swap_nodes_ptr(list, head, min);
            head = min->right;
        }
        return LIST_OK;
    }
    return LIST_NOK;
}
uint8 list_search(list_ptr **list, uint32 data)
{
    DLL *ptr_front = (*list)->head;
    DLL *ptr_end = (*list)->tail;
    sint32 count = 1;
    sint32 size = list_length(*list);
    if (!(*list))
        return lIST_NULL;
    else if ((*list)->head == NULL)
        return LIST_NOK;
    else if (data <= 0)
        return LIST_NOK;
    else
    {
        while (((ptr_front) != (ptr_end)) && (count < (size / 2)))
        {
            if (ptr_front->data == data)
            {
                printf("data found\n");
                return LIST_OK;
            }
            else if (ptr_end->data == data)
            {
                printf("data found\n");
                return LIST_OK;
            }
            ptr_front = ptr_front->right;
            ptr_end = ptr_end->left;
            count++;
        }
        if (ptr_front->data == data)
        {
            printf("data found \n");
            return LIST_OK;
        }
        printf("data not found!!\n");
        return LIST_OK;
    }
    return LIST_NOK;
}
uint8 list_search_sorted(list_ptr **list, uint32 data)
{
    DLL *ptr_forward = (*list)->head;
    DLL *ptr_rev = (*list)->tail;
    if (!(*list))
        return LIST_OK;
    else if ((*list)->head == NULL)
        return LIST_NOK;
    else if (data <= 0)
        return LIST_NOK;
    else
    {
        while (ptr_forward != ptr_rev)
        {
            if (ptr_forward->data == data)
            {
                printf("data found\n");
                return LIST_OK;
            }
            if (ptr_rev->data == data)
            {
                printf("data found\n");
                return LIST_OK;
            }
            if (ptr_forward->data > data)
            {
                printf("data not found!!\n");
                return LIST_OK;
            }
            if (ptr_rev->data < data)
            {
                printf("data not found!!\n");
                return LIST_OK;
            }
            ptr_forward = ptr_forward->right;
            ptr_rev = ptr_rev->left;
        }
        if (ptr_forward->data == data)
        {
            printf("data found \n");
            return LIST_OK;
        }
        printf("data not found!!\n");
        return LIST_OK;
    }
}
uint8 reverse_list(list_ptr **list)
{
    DLL *ptr_forward = (*list)->head;
    DLL *ptr_rev = (*list)->tail;
    sint32 count = 1;
    sint32 size = list_length(*list);
    DLL *old_left = NULL;
    DLL *old_right = NULL;
    if (!(*list))
        return lIST_NULL;
    else if ((*list)->head == NULL)
        return LIST_NOK;
    else if ((*list)->head == (*list)->tail)
        return LIST_OK;
    else
    {
        while ((ptr_forward != ptr_rev) && (count < (size / 2)))
        {
            old_left = ptr_rev->left;
            old_right = ptr_forward->right;
            swap_nodes_ptr(list, ptr_forward, ptr_rev);
            ptr_forward = old_right;
            ptr_rev = old_left;
            count++;
        }
        return LIST_OK;
    }
}
void print_middle(list_ptr *list)
{
    sint32 size = list_length(list);
    sint32 mid = size / 2;
    sint32 data[2];
    DLL *middle = list->head;
    int count;
    if (!list)
        return;
    else if (list->head == list->tail)
    {
        printf("middle = %u \n", list->head->data);
    }
    else
    {
        if ((size % 2) == 0)
        {
            for (count = 1; count < mid && (middle != NULL); count++)
                middle = middle->right;

            data[0] = middle->data;
            middle = middle->right;
            data[1] = middle->data;
            printf("MIddle of the list = %u , %u\n", data[0], data[1]);
            return;
        }
        else
        {
            for (count = 1; count <= mid && (middle != NULL); count++)
                middle = middle->right;

            printf("middle of the list = %u \n", middle->data);
            return;
        }
    }
    return;
}
void delete_node_ptr(list_ptr **list, DLL *delete_node)
{
    DLL *prev = NULL;
    DLL *next = NULL;
    if (!(*list))
        return;
    else if ((*list)->head == NULL)
        return;
    else if ((*list)->head == (*list)->tail)
    {
        free((*list)->head);
        (*list)->head = NULL;
        (*list)->tail = NULL;
    }
    else
    {
        prev = delete_node->left;
        next = delete_node->right;

        if (prev != NULL)
            prev->right = next;
        if (next != NULL)
            next->left = prev;

        if ((*list)->head == delete_node)
            (*list)->head = next;
        if ((*list)->tail == delete_node)
            (*list)->tail = prev;

        delete_node->left = NULL;
        delete_node->right = NULL;
        free(delete_node);
        delete_node = NULL;
        return;
    }
    return;
}
uint8 delete_duplicated(list_ptr **list)
{
    DLL *head = (*list)->head;
    DLL *temp_forward = NULL;
    DLL *next_save = NULL;
    if (!(*list))
        return lIST_NULL;
    else if ((*list)->head == NULL)
        return LIST_NOK;
    else if ((*list)->head == (*list)->tail)
        return LIST_OK;
    else
    {
        while (head != NULL)
        {
            temp_forward = head->right;

            while ((temp_forward != NULL))
            {
                if (temp_forward->data == head->data)
                {
                    next_save = temp_forward->right;
                    delete_node_ptr(list, temp_forward);
                    temp_forward = next_save;
                    continue;
                }
                temp_forward = temp_forward->right;
            }
            head = head->right;
        }
        return LIST_OK;
    }
    return LIST_NOK;
}
uint8 delete_duplicated_sorted(list_ptr **list)
{
    DLL *temp = (*list)->head;
    DLL *temp2 = NULL;
    if (!(*list))
        return lIST_NULL;
    else if ((*list)->head == NULL)
        return LIST_NOK;
    else if ((*list)->head == (*list)->tail)
        return LIST_OK;
    else
    {
        while (temp != NULL && temp->right != NULL)
        {
            if (temp->data == temp->right->data)
            {
                temp2 = temp->right;
                delete_node_ptr(list, temp2);
                continue;
            }
            else
            {
                temp = temp->right;
            }
        }
        return LIST_OK;
    }
    return LIST_NOK;
}
uint8 delete_two_sum_zero_unsorted(list_ptr **list)
{
    DLL *temp1 = (*list)->head;
    DLL *temp2 = NULL;
    DLL *next_temp1 = NULL;
    DLL *next_temp2 = NULL;
    if (!(*list))
        return lIST_NULL;
    else if ((*list)->head == NULL)
        return LIST_NOK;
    else
    {
        while ((temp1 != NULL) && (temp1->right != NULL))
        {
            temp2 = temp1->right;
            while (temp2 != NULL)
            {
                if ((temp1->data + temp2->data) == 0)
                {
                    if (temp1->right == temp2)
                    {
                        next_temp1 = temp2->right;

                        if (temp2->right != NULL)
                            next_temp2 = temp2->right->right;
                        else
                        {
                            next_temp2 = NULL;
                        }
                    }
                    else
                    {
                        next_temp1 = temp1->right;
                        next_temp2 = temp2->right;
                    }
                    delete_node_ptr(list, temp1);
                    delete_node_ptr(list, temp2);
                    temp1 = next_temp1;
                    temp2 = next_temp2;
                }
                else
                {
                    temp2 = temp2->right;
                }
            }
            if (temp1 != NULL)
                temp1 = temp1->right;
        }
        return LIST_OK;
    }
    return LIST_NOK;
}
uint8 delete_two_sum_zero_sorted(list_ptr **list)
{
    DLL *temp1 = (*list)->head;
    DLL *temp2 = NULL;
    DLL *next_temp2 = NULL;
    DLL *next_temp1 = NULL;
    if (!(*list))
        return lIST_NULL;
    else if (((*list)->head == NULL) || ((*list)->head == (*list)->tail))
        return LIST_NOK;
    else
    {
        while ((temp1 != NULL) && (temp1->right != NULL))
        {
            temp2 = temp1->right;
            while (temp2 != NULL)
            {
                if (temp1->data + temp2->data == 0)
                {
                    if (temp1->right == temp2)
                    {
                        next_temp1 = temp2->right;

                        if (temp2->right != NULL)
                            next_temp2 = temp2->right->right;
                        else
                            next_temp2 = NULL;
                    }
                    else
                    {
                        next_temp1 = temp1->right;
                        next_temp2 = temp2->right;
                    }
                    delete_node_ptr(list, temp1);
                    delete_node_ptr(list, temp2);
                    temp1 = next_temp1;
                    temp2 = next_temp2;
                }
                else if ((temp1->data > 0))
                    break;
                else
                {
                    temp2 = temp2->right;
                }
            }
            if (temp1 != NULL)
                temp1 = temp1->right;
            if ((temp1 != NULL) && (temp1->data > 0))
                break;
        }
        return LIST_OK;
    }
    return LIST_NOK;
}
uint8 merge_list_alternate(list_ptr **list, list_ptr **list2)
{
    DLL *curr_1 = (*list)->head, *prev1 = NULL, *next1 = NULL;
    DLL *curr_2 = (*list2)->head, *prev2 = NULL, *next2 = NULL;
    sint32 list1_size = list_length(*list);
    sint32 list2_size = list_length(*list2);
    if (!(*list) || !(*list2))
        return lIST_NULL;
    else if ((*list)->head == NULL || (*list2)->head == NULL)
        return LIST_NOK;
    else
    {
        while ((curr_1 != NULL) && (curr_2 != NULL))
        {
            // saving prev and next nodes
            prev1 = curr_1->left;
            next1 = curr_1->right;
            prev2 = curr_2->left;
            next2 = curr_2->right;

            curr_2->left = curr_1;
            curr_2->right = next1;

            curr_1->right = curr_2;

            if (next1 != NULL)
                next1->left = curr_2;
            if (next2 != NULL)
                next2->left = prev2;
            // updating the head and tail of list 2
            if ((next2 == NULL) || next2->left == NULL)
                (*list2)->head = next2;
            if ((next2 == NULL) || next2->right == NULL)
                (*list2)->tail = next2;
            // updaing the tail of the list 1
            if ((curr_2 != NULL) && (curr_2->right == NULL))
                (*list)->tail = curr_2;

            curr_1 = next1;
            curr_2 = next2;
        }
        if ((*list2)->head == NULL)
            (*list2)->tail == NULL;

        return LIST_OK;
    }
    return LIST_NOK;
}
uint8 detect_loop_and_remove(list_ptr **list)
{
    DLL *prev = (*list)->head->left;
    DLL *temp = (*list)->head;
    DLL *rev = (*list)->tail->right;
    DLL *temp2 = (*list)->tail;
    uint8 loop = 0;
    if (!(*list))
        return lIST_NULL;
    else if ((*list)->head == NULL)
        return LIST_NOK;
    else
    {
        if ((*list)->head == (*list)->tail)
        {
            (*list)->head->left = NULL;
            (*list)->head->right = NULL;
            return LIST_OK;
        }
        if ((*list)->tail->right == (*list)->head)
        {
            (*list)->tail->right = NULL;
            return LIST_OK;
        }
        while (temp)
        {
            if ((prev) && (prev != temp->left))
            {
                printf("LOOP found!! \n");
                loop = 1;
                break;
            }
            if ((rev) && rev != temp2->right)
            {
                printf("LOOP FOUND!! \n");
                loop = 2;
                break;
            }
            rev = temp2;
            prev = temp;
            temp = temp->right;
            temp2 = temp2->left;
        }
        if (loop == 1)
        {
            temp->left = prev;
        }
        if (loop == 2)
        {
            temp2->right = rev;
        }
        return LIST_OK;
    }
    return LIST_NOK;
}
uint8 delete_list(list_ptr **list)
{
    DLL *temp = (*list)->head;
    DLL *next = NULL;
    if (!(*list))
        return LIST_OK;
    else if ((*list)->head == NULL)
    {
        free(*list);
        list = NULL;
        return LIST_OK;
    }
    else
    {
        while (temp)
        {
            next = temp->right;
            free(temp);
            temp = NULL;
            temp = next;
        }
        free(*list);
        *list = NULL;
        return LIST_OK;
    }
    return LIST_NOK;
}