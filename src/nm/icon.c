/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-jeffrey.winkler
** File description:
** icon
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

static char get_section_icon(Elf64_Ehdr *hdr, Elf64_Sym *symbol, int is_local)
{
    const char *sec_strtab = get_section_strtab(hdr);
    Elf64_Shdr *shdr;
    const char *name;

    /*
    for (int i = 0; i < SECTIONS_COUNT; i++) {
        if (!strcmp(name, SECTIONS_NAME[i]))
            return is_local ? SECTIONS_ICON[i] + 32 : SECTIONS_ICON[i];
    }
    return 0;*/
    switch (symbol->st_shndx) {
        case SHN_ABS:
            return 'A';
        case SHN_COMMON:
            return is_local ? 'c' : 'C';
        case SHN_UNDEF:
            return 'U';
    }
    shdr = get_section_header(hdr, symbol->st_shndx);
    name = get_section_name(shdr, sec_strtab);
    //puts(name);
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
    if (!strcmp(name, ".init_array") || !strcmp(name, ".fini_array"))
        return is_local ? 't' : 'T';
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