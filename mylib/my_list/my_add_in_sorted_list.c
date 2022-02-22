/*
** EPITECH PROJECT, 2020
** my_add_in_sorted_list
** File description:
** add element into a list as the list stay in order
*/

#include "my_list.h"
#include <stdlib.h>

static void set_prev(list_t *prev, list_t *new, list_t **begin)
{
    if (prev != NULL)
        prev->next = new;
    else
        *begin = new;
}

void my_add_in_sorted_list(list_t **begin, void *data, int (*cmp)())
{
    list_t *prev = NULL;
    list_t *actual = *begin;
    list_t *new = malloc(sizeof(list_t));

    new->data = data;
    while (actual != NULL) {
        if ((*cmp)(actual->data, data) > 0) {
            new->next = actual;
            set_prev(prev, new, begin);
            return;
        }
        prev = actual;
        actual = actual->next;
    }
    new->next = NULL;
    set_prev(prev, new, begin);
}