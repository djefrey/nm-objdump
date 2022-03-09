/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-jeffrey.winkler
** File description:
** nm
*/

#pragma once

#include "common.h"
#include "my_list.h"

typedef struct symbol_data_s {
    const char *name;
    Elf64_Sym *symbol;
} symbol_data_t;

void print_symbols_from_elf(Elf64_Ehdr *hdr);
list_t *get_symbols(Elf64_Sym *symbols, size_t nb_symbols, const char *strtab);
void print_symbols(Elf64_Ehdr *hdr, list_t *symbols);

char get_symbol_icon(Elf64_Ehdr *hdr, Elf64_Sym *symbol);
char get_section_icon(Elf64_Ehdr *hdr, Elf64_Sym *symbol, int is_local);