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

static int my_nm(const char *path)
{
    Elf64_Ehdr *hdr = open_elf_file(path);

    if (!hdr || !is_valid_elf(hdr))
        return 84;
    print_symbols_from_elf(hdr);
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
        return my_nm("./a.out");
    else
        return my_nm_on_files(av + 1, ac - 1);
}