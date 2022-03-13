/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-jeffrey.winkler
** File description:
** icon_2
*/

#include <string.h>
#include "nm.h"

static char get_section_progbits_icon_32(Elf32_Shdr *shdr, int is_local)
{
    if (shdr->sh_flags & SHF_ALLOC) {
        if (shdr->sh_flags & SHF_WRITE)
            return is_local ? 'd' : 'D';
        else if (shdr->sh_flags & SHF_EXECINSTR)
            return is_local ? 't' : 'T';
        else
            return is_local ? 'r' : 'R';
    }
    return 0;
}

static char get_symbol_ndx_icon_32(Elf32_Sym *symbol, int is_local)
{
    switch (symbol->st_shndx) {
        case SHN_ABS:
            return 'A';
        case SHN_COMMON:
            return is_local ? 'c' : 'C';
        case SHN_UNDEF:
            return 'U';
    }
    return 0;
}

static char check_section_flags_bss_32(Elf32_Shdr *shdr, int is_local)
{
    if (shdr->sh_flags == SHF_ALLOC | SHF_WRITE)
        return is_local ? 'b' : 'B';
    return 0;
}

static char get_section_type_icon_32(Elf32_Shdr *shdr, int is_local)
{
    switch (shdr->sh_type) {
        case SHT_DYNAMIC:
            return is_local ? 'd' : 'D';
        case SHT_NOBITS:
            return check_section_flags_bss_32(shdr, is_local);
        case SHT_PROGBITS:
            return get_section_progbits_icon_32(shdr, is_local);
        default:
            return 0;
    }
}

char get_section_icon_32(Elf32_Ehdr *hdr, Elf32_Sym *symbol, int is_local)
{
    const char *sec_strtab = get_section_strtab_32(hdr);
    Elf32_Shdr *shdr;
    const char *name;
    char c = 0;

    if ((c = get_symbol_ndx_icon_32(symbol, is_local)))
        return c;
    shdr = get_section_header_32(hdr, symbol->st_shndx);
    name = get_section_name_32(shdr, sec_strtab);
    if ((c = get_section_type_icon_32(shdr, is_local)))
        return c;
    if (!strcmp(name, ".init_array") || !strcmp(name, ".fini_array"))
        return is_local ? 't' : 'T';
    return 0;
}
