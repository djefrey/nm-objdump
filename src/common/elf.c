/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-jeffrey.winkler
** File description:
** elf
*/

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include "common.h"

Elf64_Ehdr *open_elf_file(const char *path)
{
    int fd = open(path, O_RDONLY);
    Elf64_Ehdr *hdr = NULL;
    struct stat s;

    if (fd == -1)
        return NULL;
    fstat(fd, &s);
    hdr = mmap(NULL, s.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (hdr == (void*) -1)
        return NULL;
    return hdr;
}

int is_valid_elf(Elf64_Ehdr *hdr)
{
    u_char *magic = hdr->e_ident;

    return (magic[0] == ELFMAG0 && magic[1] == ELFMAG1
         && magic[2] == ELFMAG2 && magic[3] == ELFMAG3);
}