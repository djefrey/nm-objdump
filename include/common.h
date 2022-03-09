/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-jeffrey.winkler
** File description:
** common
*/

#pragma once

#include <stdlib.h>
#include <elf.h>
#include <ar.h>
#include "my_list.h"

typedef struct file_s {
    int fd;
    void *data;
    uint64_t size;
} file_t;

typedef struct ar_hdr ar_hdr_t;

file_t open_file(const char *path);
void close_file(file_t *file);
int is_valid_elf(void *file);

list_t *get_archive_files(file_t *file);
int is_valid_archive(file_t *file);
Elf64_Ehdr *get_elf_from_archive(ar_hdr_t *hdr);
void extract_archive_name(char buf[17], ar_hdr_t *hdr);

Elf64_Shdr *get_section_header(Elf64_Ehdr *hdr, Elf64_Half idx);
const char *get_section_name(Elf64_Shdr *shdr, const char *sec_strtab);
Elf64_Shdr *get_section_by_name(Elf64_Ehdr *hdr, const char *name);

const char *get_section_strtab(Elf64_Ehdr *hdr);
const char *get_strtab(Elf64_Ehdr *hdr);

const char *get_program_name(void);

void print_errno(const char *file);
void print_no_such_file(const char *file);
void print_invalid_format(const char *file);