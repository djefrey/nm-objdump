/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-jeffrey.winkler
** File description:
** infos
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "common.h"
#include "objdump.h"

static const int FLAGS_NB = 9;

static const int FLAGS_VALUE[] = {
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

static const char *FLAGS_NAME[] = {
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

static int get_flags(Elf64_Ehdr *hdr)
{
    int nb_sections = hdr->e_shnum;
    int flags = 0;
    Elf64_Shdr *shdr;

    switch (hdr->e_type) {
        case ET_EXEC:
            flags |= EXEC_P;
            break;
        case ET_DYN:
            flags |= DYNAMIC;
            break;
    }
    for (int i = 0; i < nb_sections; i++) {
        shdr = get_section_header(hdr, i);
        if (shdr->sh_type == SHT_REL || (!(flags & EXEC_P) && shdr->sh_type == SHT_RELA))
            flags |= HAS_RELOC;
        if (shdr->sh_type == SHT_SYMTAB)
            flags |= HAS_SYMS;
    }
    return flags;
}

static void print_flags(int flags)
{
    int first = 1;

    for (int i = 0; i < FLAGS_NB; i++) {
        if (flags & FLAGS_VALUE[i]) {
            printf(first ? "%s" : ", %s", FLAGS_NAME[i]);
            first = 0;
        }
    }
    puts("");
}

void print_infos(const char *name, Elf64_Ehdr *hdr)
{
    int flags = get_flags(hdr);

    printf("\n%s:     file format elf-x86-64\n", name);
    printf("architecture: i386:x86-64, flags %0#8hx:\n", flags);
    print_flags(flags);
    printf("start adress %0#16x\n\n", hdr->e_entry);
}