/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-jeffrey.winkler
** File description:
** nm
*/

#pragma once

#include "common.h"

typedef struct symbol_data_s {
    const char *name;
    Elf64_Sym *symbol;
} symbol_data_t;
