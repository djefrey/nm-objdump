/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-jeffrey.winkler
** File description:
** archive
*/

#include <string.h>
#include "common.h"

static ar_hdr_t *get_next_ar_header(ar_hdr_t *hdr)
{
    void *data = ((void*) hdr) + sizeof(ar_hdr_t);
    uint64_t size = 0;

    for (int i = 0; i < 10 && hdr->ar_size[i] != ' '; i++)
        size = size * 10 + (hdr->ar_size[i] - '0');
    return (data + size);
}

void extract_archive_name(char buf[17], ar_hdr_t *hdr)
{
    int nullc = 0;

    for (int i = 0; i < 16; i++) {
        if (hdr->ar_name[i] == '/')
            nullc = 1;
        buf[i] = !nullc ? hdr->ar_name[i] : 0;
    }
    buf[16] = 0;
}

Elf64_Ehdr *get_elf_from_archive(ar_hdr_t *hdr)
{
    return (((void*) hdr) + sizeof(ar_hdr_t));
}

list_t *get_archive_files(file_t *file)
{
    list_t *list = NULL;
    ar_hdr_t *hdr = file->data + SARMAG;

    while (hdr < (file->data + file->size)) {
        create_list(&list, hdr);
        hdr = get_next_ar_header(hdr);
    }
    return list;
}

int is_valid_archive(file_t *file)
{
    return !strncmp(file->data, ARMAG, SARMAG);
}
