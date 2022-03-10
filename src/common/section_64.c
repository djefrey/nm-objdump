/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-jeffrey.winkler
** File description:
** section
*/

#include <unistd.h>
#include <string.h>
#include "nm.h"

Elf64_Shdr *get_section_header_64(Elf64_Ehdr *hdr, Elf64_Half idx)
{
    Elf64_Shdr *start_shdr = ((void*) hdr) + hdr->e_shoff;

    if (idx >= hdr->e_shnum) {
        write(2, "Invalid idx\n", 12);
        return NULL;
    }
    return &start_shdr[idx];
}

const char *get_section_name_64(Elf64_Shdr *shdr, const char *sec_strtab)
{
    if (shdr->sh_name == SHN_UNDEF)
        return NULL;
    return sec_strtab + shdr->sh_name;
}

Elf64_Shdr *get_section_by_name_64(Elf64_Ehdr *hdr, const char *name)
{
    const char *sec_strtab = get_section_strtab_64(hdr);
    const char *shdr_name = NULL;
    Elf64_Shdr *shdr = NULL;

    for (Elf64_Half idx = 0; idx < hdr->e_shnum; idx++) {
        shdr = get_section_header_64(hdr, idx);
        shdr_name = get_section_name_64(shdr, sec_strtab);
        if (shdr_name != NULL && !strcmp(shdr_name, name))
            return shdr;
    }
    return NULL;
}
