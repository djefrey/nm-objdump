/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-jeffrey.winkler
** File description:
** nm
*/

#pragma once

#include "common.h"
#include "my_list.h"

typedef struct symbol_data_32_s {
    const char *name;
    Elf64_Sym *symbol;
} symbol_data_64_t;

typedef struct symbol_data_64_s {
    const char *name;
    Elf32_Sym *symbol;
} symbol_data_32_t;

int my_nm(const char *path);
int my_nm_on_files(const char **path, int nb);

void print_symbols_from_elf_32(Elf32_Ehdr *hdr);
list_t *get_symbols_32(Elf32_Sym *symbols,
size_t nb_symbols, const char *strtab);
void print_symbols_32(Elf32_Ehdr *hdr, list_t *symbols);

char get_symbol_icon_32(Elf32_Ehdr *hdr, Elf32_Sym *symbol);
char get_section_icon_32(Elf32_Ehdr *hdr, Elf32_Sym *symbol, int is_local);

void print_symbols_from_elf_64(Elf64_Ehdr *hdr);
list_t *get_symbols_64(Elf64_Sym *symbols, size_t nb_symbols, const char *strtab);
void print_symbols_64(Elf64_Ehdr *hdr, list_t *symbols);

char get_symbol_icon_64(Elf64_Ehdr *hdr, Elf64_Sym *symbol);
char get_section_icon_64(Elf64_Ehdr *hdr, Elf64_Sym *symbol, int is_local);

extern int SECTIONS_COUNT;
extern char *SECTIONS_NAME[];
extern char SECTIONS_ICON[];