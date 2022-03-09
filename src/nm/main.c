/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-jeffrey.winkler
** File description:
** main
*/

#include <stdio.h>
#include <string.h>
#include "nm.h"
#include "my_list.h"

static int treat_file_in_archive(ar_hdr_t *hdr)
{
    Elf64_Ehdr *ehdr;
    char name[17] = {0};

    ehdr = get_elf_from_archive(hdr);
    if (is_valid_elf(ehdr)) {
        extract_archive_name(name, hdr);
        printf("\n%s:\n", name);
        print_symbols_from_elf(ehdr);
        return 0;
    } else
        return 1;
}

static int my_nm_on_archive(file_t *file)
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

static int my_nm(const char *path)
{
    file_t file = open_file(path);
    int ret = 0;

    if (file.data) {
        if (is_valid_elf(file.data))
            print_symbols_from_elf(file.data);
        else if (is_valid_archive(&file))
            ret = my_nm_on_archive(&file);
        else {
            print_invalid_format(path);
            ret = 84;
        }
        close_file(&file);
        return ret;
    }
    return 84;
}

static int my_nm_on_files(const char **path, int nb)
{
    int ret = 0;
    int tmp;

    if (nb == 1)
        return my_nm(path[0]);
    for (int i = 0; i < nb; i++) {
        if (i == 0)
            printf("%s:\n", path[i]);
        else
            printf("\n%s:\n", path[i]);
        tmp = my_nm(path[i]);
        if (tmp > ret)
            ret = tmp;
    }
    return ret;
}

int main(int ac, const char **av)
{
    if (ac == 1)
        return my_nm("a.out");
    else
        return my_nm_on_files(av + 1, ac - 1);
}
