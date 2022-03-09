/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-jeffrey.winkler
** File description:
** icon
*/

#include <string.h>
#include "nm.h"

static char get_bind_icon(Elf64_Sym *symbol, int is_local)
{
    if (ELF64_ST_BIND(symbol->st_info) == STB_GNU_UNIQUE)
        return is_local ? 'u' : 'U';
    if (ELF64_ST_BIND(symbol->st_info) == STB_WEAK) {
        if (ELF64_ST_TYPE(symbol->st_info) == STT_OBJECT)
            return symbol->st_shndx == SHN_UNDEF ? 'v' : 'V';
        else
            return symbol->st_shndx == SHN_UNDEF ? 'w' : 'W';
    }
    return 0;
}

static char get_type_icon(Elf64_Sym *symbol, int is_local)
{
    if (ELF64_ST_TYPE(symbol->st_info) == STT_OBJECT
     || ELF64_ST_TYPE(symbol->st_info) == STT_NOTYPE)
        return is_local ? 'd' : 'D';
    if (ELF64_ST_TYPE(symbol->st_info) == STT_FUNC)
        return is_local ? 't' : 'T';
    return 0;
}

char get_symbol_icon(Elf64_Ehdr *hdr, Elf64_Sym *symbol)
{
    int is_local = ELF64_ST_BIND(symbol->st_info) == STB_LOCAL;
    char icon = 0;

    if ((icon = get_bind_icon(symbol, is_local))
     || (icon = get_section_icon(hdr, symbol, is_local))
     || (icon = get_type_icon(symbol, is_local)))
        return icon;
    return '?';
}
