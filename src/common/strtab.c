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
    if (hdr->e_shoff == SHN_UNDEF)
        return NULL;
    return ((void*) hdr)
        + get_section_header_32(hdr, hdr->e_shstrndx)->sh_offset;
}

const char *get_strtab_32(Elf32_Ehdr *hdr)
{
    return ((void*) hdr)
        + get_section_by_name_32(hdr, ".strtab")->sh_offset;
}

const char *get_section_strtab_64(Elf64_Ehdr *hdr)
{
    if (hdr->e_shoff == SHN_UNDEF)
        return NULL;
    return ((void*) hdr)
        + get_section_header_64(hdr, hdr->e_shstrndx)->sh_offset;
}

const char *get_strtab_64(Elf64_Ehdr *hdr)
{
    return ((void*) hdr)
        + get_section_by_name_64(hdr, ".strtab")->sh_offset;
}
