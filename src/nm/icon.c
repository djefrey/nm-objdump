/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-jeffrey.winkler
** File description:
** icon
*/

#include <string.h>
#include "nm.h"

const int SECTIONS_COUNT = 4;
const char *SECTIONS_NAME[4] = {
    ".bss",
    ".data",
    ".text",
    ".rodata",
};
const char SECTIONS_ICON[4] = {
    'B',
    'D',
    'T',
    'R',
};

static char get_bind_icon(Elf64_Sym *symbol, int is_local)
{
    switch (ELF64_ST_BIND(symbol->st_info)) {
        case STB_WEAK:
            return is_local ? 'w' : 'W';
    }
    return 0;
}

static char get_shndx_icon(Elf64_Sym *symbol, int is_local)
{
    switch (symbol->st_shndx) {
        case SHN_ABS:
            return 'A';
        case SHN_COMMON:
            return is_local ? 'c' : 'C';
        case SHN_UNDEF:
            return 'U';
        case SHN_BEFORE:
        case SHN_AFTER:
        case SHN_HIPROC:
        case SHN_HIRESERVE:
            return '?';
        default:
            return 0;
    }
}

static char get_section_icon(Elf64_Ehdr *hdr, Elf64_Sym *symbol, int is_local)
{
    const char *sec_strtab = get_section_strtab(hdr);
    Elf64_Shdr *shdr = get_section_header(hdr, symbol->st_shndx);
    const char *name = get_section_name(shdr, sec_strtab);

    for (int i = 0; i < SECTIONS_COUNT; i++) {
        if (!strcmp(name, SECTIONS_NAME[i]))
            return is_local ? SECTIONS_ICON[i] + 32 : SECTIONS_ICON[i];
    }
    return 0;
}

char get_symbol_icon(Elf64_Ehdr *hdr, Elf64_Sym *symbol)
{
    int is_local = ELF64_ST_BIND(symbol->st_info) == STB_LOCAL;
    char icon = 0;

    if ((icon = get_bind_icon(symbol, is_local))
     || (icon = get_shndx_icon(symbol, is_local))
     || (icon = get_section_icon(hdr, symbol, is_local)))
        return icon;
    return '?';
}