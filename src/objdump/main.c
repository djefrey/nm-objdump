/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-objdumpobjdump-jeffrey.winkler
** File description:
** main
*/

#include <stdio.h>
#include <ar.h>
#include "objdump.h"

static int treat_file_in_archive(ar_hdr_t *hdr)
{
    Elf64_Ehdr *ehdr;
    char name[17] = {0};

    ehdr = get_elf_from_archive(hdr);
    if (is_valid_elf(ehdr)) {
        extract_archive_name(name, hdr);
        print_infos(name, ehdr);
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

static int my_objdump(const char *path)
{
    file_t file = open_file(path);
    int ret = 0;

    if (file.data) {
        if (is_valid_elf(file.data)) {
            print_infos(path, file.data);
            dump_sections(file.data);
        } else if (is_valid_archive(&file))
            ret = my_objdump_on_archive(&file);
        else
            ret = 84;
        close_file(&file);
        return ret;
    }
    return 84;
}

static int my_objdump_on_files(const char **path, int nb)
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

int main(int ac, const char **av)
{
    if (ac == 1)
        return my_objdump("./a.out");
    else
        return my_objdump_on_files(av + 1, ac - 1);
}