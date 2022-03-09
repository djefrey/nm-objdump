/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-jeffrey.winkler
** File description:
** error
*/

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "common.h"

void print_errno(const char *file)
{
    fprintf(stderr, "%s: %s: %s\n",
    get_program_name(), file, strerror(errno));
}

void print_no_such_file(const char *file)
{
    fprintf(stderr, "%s: %s: No such file\n",
    get_program_name(), file);
}

void print_invalid_format(const char *file)
{
    fprintf(stderr, "%s: %s: file format not recognized\n",
    get_program_name(), file);
}
