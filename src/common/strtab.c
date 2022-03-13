/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-jeffrey.winkler
** File description:
** strtab
*/

#include <string.h>
#include "nm.h"

const char *get_section_strtab_32(Elf32_Ehdr *hdr)
{
    Elf32_Off off;

    if (hdr->e_shoff == SHN_UNDEF)
        return NULL;
    off = get_section_header_32(hdr, hdr->e_shstrndx)->sh_offset;
    return ((void*) hdr) + off;
}

const char *get_strtab_32(Elf32_Ehdr *hdr)
{
    Elf32_Off off = get_section_by_name_32(hdr, ".strtab")->sh_offset;

    return ((void*) hdr) + off;
}

const char *get_section_strtab_64(Elf64_Ehdr *hdr)
{
    Elf64_Off off;

    if (hdr->e_shoff == SHN_UNDEF)
        return NULL;
    off = get_section_header_64(hdr, hdr->e_shstrndx)->sh_offset;
    return ((void*) hdr) + off;
}

const char *get_strtab_64(Elf64_Ehdr *hdr)
{
    Elf64_Off off = get_section_by_name_64(hdr, ".strtab")->sh_offset;

    return ((void*) hdr) + off;
}
