/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-jeffrey.winkler
** File description:
** icon_2
*/

#include <string.h>
#include "nm.h"

const int SECTIONS_COUNT = 5;
const char *SECTIONS_NAME[] = {
    ".bss",
    ".data",
    ".text",
    ".rodata",
    ".debug",
};
const char SECTIONS_ICON[] = {
    'B',
    'D',
    'T',
    'R',
    'N',
};

static char get_section_progbits_icon(Elf64_Shdr *shdr, int is_local)
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

static char get_symbol_ndx_icon(Elf64_Sym *symbol, int is_local)
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

static char get_section_type_icon(Elf64_Shdr *shdr, int is_local)
{
    switch (shdr->sh_type) {
        case SHT_DYNAMIC:
            return is_local ? 'd' : 'D';
        case SHT_NOBITS:
            if (shdr->sh_flags == SHF_ALLOC | SHF_WRITE)
                return is_local ? 'b' : 'B';
            break;
        case SHT_PROGBITS:
            return get_section_progbits_icon(shdr, is_local);
    }
    return 0;
}

char get_section_icon(Elf64_Ehdr *hdr, Elf64_Sym *symbol, int is_local)
{
    const char *sec_strtab = get_section_strtab(hdr);
    Elf64_Shdr *shdr;
    const char *name;
    char c = 0;

    if ((c = get_symbol_ndx_icon(symbol, is_local)))
        return c;
    shdr = get_section_header(hdr, symbol->st_shndx);
    name = get_section_name(shdr, sec_strtab);
    if ((c = get_section_type_icon(shdr, is_local)))
        return c;
    if (!strcmp(name, ".init_array") || !strcmp(name, ".fini_array"))
        return is_local ? 't' : 'T';
    return 0;
}
