/*
** EPITECH PROJECT, 2020
** my_add_in_sorted_list
** File description:
** add element into a list as the list stay in order
*/

#include "my_list.h"
#include <stdlib.h>

static void merge_element(list_t **begin1, list_t *prev,
list_t *actual, list_t *selected)
{
    list_t *tmp_sel_next = NULL;

    tmp_sel_next = selected->next;
    if (prev != NULL)
        prev->next = selected;
    else
        *begin1 = selected;
    selected->next = actual;
    prev = selected;
    selected = tmp_sel_next;
}

void my_merge(list_t **begin1, list_t *begin2, int (*cmp)())
{
    list_t *prev = NULL;
    list_t *actual = *begin1;
    list_t *selected = begin2;

    while (actual->next != NULL) {
        if ((*cmp)(actual->data, selected->data) > 0) {
            merge_element(begin1, prev, actual, selected);
        } else {
            prev = actual;
            actual = actual->next;
        }
    }
    if (selected != NULL)
        prev->next = selected;
}