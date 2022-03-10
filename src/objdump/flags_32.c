/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-jeffrey.winkler
** File description:
** flags_32
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "common.h"
#include "objdump.h"

static void check_hdr_type_32(Elf32_Ehdr *hdr, int *flags)
{
    switch (hdr->e_type) {
        case ET_EXEC:
            *flags |= EXEC_P;
            break;
        case ET_DYN:
            *flags |= DYNAMIC;
            break;
    }
}

int get_flags_32(Elf32_Ehdr *hdr)
{
    int nb_sections = hdr->e_shnum;
    int flags = 0;
    Elf32_Shdr *shdr;

    check_hdr_type_32(hdr, &flags);
    for (int i = 0; i < nb_sections; i++) {
        shdr = get_section_header_32(hdr, i);
        if (shdr->sh_type == SHT_REL
        || (!(flags & EXEC_P) && shdr->sh_type == SHT_RELA))
            flags |= HAS_RELOC;
        if (shdr->sh_type == SHT_SYMTAB)
            flags |= HAS_SYMS;
    }
    return flags;
}
