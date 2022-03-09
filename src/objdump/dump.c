/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-jeffrey.winkler
** File description:
** dump
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "common.h"
#include "objdump.h"

static void dump_line(char *data, uint addr, uint size)
{
    char hexa[33] = {0};
    char ascii[17] = {0};
    char c;

    for (int i = 0; i < size && i < 16; i++) {
        c = *(data + addr + i);
        snprintf(hexa + i * 2, 3, "%02hhx", c);
        ascii[i] = isprint(c) ? c : '.';
    }
    hexa[32] = 0;
    ascii[16] = 0;
    printf(" %04x % -8.8s % -8.8s % -8.8s % -8.8s % -16s\n",
    addr, hexa, hexa + 8, hexa + 16, hexa + 24, ascii);
}

static void dump_section(Elf64_Ehdr *hdr, Elf64_Shdr *shdr)
{
    char *data = ((void*) hdr) + shdr->sh_offset;
    uint size = shdr->sh_size;

    for (uint i = 0; i < size; i += 16) {
        if (size - i >= 16)
            dump_line(data, i, 16);
        else
            dump_line(data, i, size - i);
    }
}

void dump_sections(Elf64_Ehdr *hdr)
{
    const char *sec_strtab = get_section_strtab(hdr);
    size_t sec_nb = hdr->e_shnum;
    Elf64_Shdr *shdr;

    for (size_t i = 0; i < sec_nb; i++) {
        shdr = get_section_header(hdr, i);
        if (shdr->sh_size == 0 || shdr->sh_type == SHT_NOBITS)
            continue;
        printf("Contends of section %s:\n", get_section_name(shdr, sec_strtab));
        dump_section(hdr, shdr);
    }
}
