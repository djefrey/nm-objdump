/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-jeffrey.winkler
** File description:
** objdump
*/

#include <stdio.h>
#include <ar.h>
#include "objdump.h"

static void print_infos_dump(const char *name, Elf64_Ehdr *hdr)
{
    print_infos(name, hdr);
    if (is_elf_64(hdr))
        dump_sections_64(hdr);
    else
        dump_sections_32((Elf32_Ehdr*) hdr);
}

static int treat_file_in_archive(ar_hdr_t *hdr)
{
    Elf64_Ehdr *ehdr;
    char name[17] = {0};

    ehdr = get_elf_from_archive(hdr);
    if (is_valid_elf(ehdr)) {
        extract_archive_name(name, hdr);
        print_infos_dump(name, ehdr);
        return 0;
    } else
        return 1;
}

static int my_objdump_on_archive(file_t *file)
{
    list_t *files = get_archive_files(file);
    list_t *tmp;
    ar_hdr_t *hdr;
    int ret = 0;

    my_rev_list(&files);
    for (list_t *cpy = files; cpy; cpy = cpy->next) {
        hdr = cpy->data;
        if (treat_file_in_archive(hdr))
            ret = 84;
    }
    while (files) {
        tmp = files->next;
        free(files);
        files = tmp;
    }
    return ret;
}

int my_objdump(const char *path)
{
    file_t file = open_file(path);
    int ret = 0;

    if (file.data) {
        if (is_valid_elf(file.data)) {
            print_infos_dump(path, file.data);
        } else if (is_valid_archive(&file))
            ret = my_objdump_on_archive(&file);
        else {
            print_invalid_format(path);
            ret = 84;
        }
        close_file(&file);
        return ret;
    }
    return 84;
}

int my_objdump_on_files(const char **path, int nb)
{
    int ret = 0;
    int tmp;

    if (nb == 1)
        return my_objdump(path[0]);
    for (int i = 0; i < nb; i++) {
        tmp = my_objdump(path[i]);
        if (tmp > ret)
            ret = tmp;
    }
    return ret;
}
