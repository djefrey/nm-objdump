/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-jeffrey.winkler
** File description:
** common
*/

#pragma once

#include <stdlib.h>
#include <elf.h>

Elf64_Ehdr *open_elf_file(const char *path);
int is_valid_elf(Elf64_Ehdr *hdr);

Elf64_Shdr *get_section_header(Elf64_Ehdr *hdr, Elf64_Half idx);
const char *get_section_name(Elf64_Shdr *shdr, const char *sec_strtab);
Elf64_Shdr *get_section_by_name(Elf64_Ehdr *hdr, const char *name);

const char *get_section_strtab(Elf64_Ehdr *hdr);
const char *get_strtab(Elf64_Ehdr *hdr);