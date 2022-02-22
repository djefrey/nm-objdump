/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-jeffrey.winkler
** File description:
** strtab
*/

#include <string.h>
#include "nm.h"

const char *get_section_strtab(Elf64_Ehdr *hdr)
{
    if (hdr->e_shoff == SHN_UNDEF)
        return NULL;
    return ((void*) hdr) + get_section_header(hdr, hdr->e_shstrndx)->sh_offset;
}

const char *get_strtab(Elf64_Ehdr *hdr)
{
    return ((void*) hdr) + get_section_by_name(hdr, ".strtab")->sh_offset;
}
