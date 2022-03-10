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
    int flags = is_elf_64(hdr)
    ? get_flags_64(hdr) : get_flags_32((Elf32_Ehdr*) hdr);
    char *format = is_elf_64(hdr) ? "elf-x86-64" : "elf-x86";

    printf("\n%s:     file format %s\n", name, format);
    printf("architecture: i386:x86-64, flags %0#10hx:\n", flags);
    print_flags(flags);
    printf("start adress %0#19x\n\n", hdr->e_entry);
}
