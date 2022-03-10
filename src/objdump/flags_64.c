/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-jeffrey.winkler
** File description:
** flags_64
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "common.h"
#include "objdump.h"

const int FLAGS_NB = 9;

const int FLAGS_VALUE[] = {
    HAS_RELOC,
    EXEC_P,
    HAS_LINENO,
    HAS_DEBUG,
    HAS_SYMS,
    HAS_LOCALS,
    DYNAMIC,
    WP_TEXT,
    D_PAGED,
};

const char *FLAGS_NAME[] = {
    "HAS_RELOC",
    "EXEC_P",
    "HAS_LINENO",
    "HAS_DEBUG",
    "HAS_SYMS",
    "HAS_LOCALS",
    "DYNAMIC",
    "WP_TEXT",
    "D_PAGED",
};

static void check_hdr_type_64(Elf64_Ehdr *hdr, int *flags)
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

int get_flags_64(Elf64_Ehdr *hdr)
{
    int nb_sections = hdr->e_shnum;
    int flags = 0;
    Elf64_Shdr *shdr;

    check_hdr_type_64(hdr, &flags);
    for (int i = 0; i < nb_sections; i++) {
        shdr = get_section_header_64(hdr, i);
        if (shdr->sh_type == SHT_REL
        || (!(flags & EXEC_P) && shdr->sh_type == SHT_RELA))
            flags |= HAS_RELOC;
        if (shdr->sh_type == SHT_SYMTAB)
            flags |= HAS_SYMS;
    }
    return flags;
}
