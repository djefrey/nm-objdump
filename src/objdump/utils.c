/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-jeffrey.winkler
** File description:
** utils
*/

#include <stdint.h>

int get_addr_size(uint64_t addr)
{
    int size = 1;
    uint64_t val = 16;

    while (val < addr) {
        val *= 16;
        size++;
    }
    return size < 4 ? 4 : size;
}