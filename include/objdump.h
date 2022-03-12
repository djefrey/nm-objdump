/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-jeffrey.winkler
** File description:
** objdump
*/

#pragma once

#include "common.h"
#include "flags.h"

int my_objdump(const char *path);
int my_objdump_on_files(const char **path, int nb);
void print_infos(const char *name, Elf64_Ehdr *hdr);

void dump_sections_32(Elf32_Ehdr *hdr);
int get_flags_32(Elf32_Ehdr *hdr);

void dump_sections_64(Elf64_Ehdr *hdr);
int get_flags_64(Elf64_Ehdr *hdr);

int get_addr_size(uint64_t addr);

extern const int FLAGS_NB;
extern const int FLAGS_VALUE[];
extern const char *FLAGS_NAME[];