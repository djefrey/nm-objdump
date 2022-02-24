/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-jeffrey.winkler
** File description:
** symbols
*/

#include <stdio.h>
#include <string.h>
#include "nm.h"
#include "my_list.h"

static int symbol_cmp(symbol_data_t *sym1, symbol_data_t *sym2)
{
    const char *str1 = sym1->name;
    const char *str2 = sym2->name;
    int cmp;

    for (; *str1 && *str1 == '_'; str1++);
    for (; *str2 && *str2 == '_'; str2++);
    cmp = strcasecmp(str1, str2);
    return cmp != 0 ? cmp : strcasecmp(sym1->name, sym2->name);
}

void print_symbols_from_elf(Elf64_Ehdr *hdr)
{
    const char *strtab = get_strtab(hdr);
    Elf64_Shdr *symtab = get_section_by_name(hdr, ".symtab");
    Elf64_Sym *symbols = ((void*) hdr) + symtab->sh_offset;
    size_t nb_symbols = symtab->sh_size / symtab->sh_entsize;
    list_t *list = get_symbols(symbols, nb_symbols, strtab);

    print_symbols(hdr, list);
}

list_t *get_symbols(Elf64_Sym *symbols, size_t nb_symbols, const char *strtab)
{
    Elf64_Sym *symbol = symbols;
    symbol_data_t *symdata = NULL;
    list_t *list = NULL;

    for (size_t i = 0; i < nb_symbols; i++, symbol++) {
        if (symbol->st_name == SHN_UNDEF || symbol->st_shndx == SHN_ABS)
            continue;
        if (!(symdata = malloc(sizeof(symbol_data_t))))
            return NULL;
        symdata->name = strtab + symbol->st_name;
        symdata->symbol = symbol;
        my_add_in_sorted_list(&list, symdata, &symbol_cmp);
    }
    return list;
}

void print_symbols(Elf64_Ehdr *hdr, list_t *symbols)
{
    symbol_data_t *symdata = NULL;
    char icon;

    for (; symbols; symbols = symbols->next) {
        symdata = symbols->data;
        icon = get_symbol_icon(hdr, symdata->symbol);
        if (symdata->symbol->st_value == 0)
            printf("                 %c %s\n", icon, symdata->name);
        else
            printf("%016x %c %s\n", symdata->symbol->st_value, icon, symdata->name);
    }
}