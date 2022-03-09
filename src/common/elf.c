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

file_t open_file(const char *path)
{
    int fd = open(path, O_RDONLY);
    void *file = NULL;
    struct stat s;

    if (fd == -1) {
        print_no_such_file(path);
        return (file_t) {-1, NULL, 0};
    }
    fstat(fd, &s);
    file = mmap(NULL, s.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (file == (void*) -1) {
        print_errno(path);
        return (file_t) {-1, NULL, 0};
    }
    return (file_t) {fd, file, s.st_size};
}

void close_file(file_t *file)
{
    munmap(file->data, file->size);
    close(file->fd);
}

int is_valid_elf(void *file)
{
    u_char *magic = ((Elf64_Ehdr*) file)->e_ident;

    return (magic[0] == ELFMAG0 && magic[1] == ELFMAG1
         && magic[2] == ELFMAG2 && magic[3] == ELFMAG3);
}
