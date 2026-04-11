#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "util.h"

int        print_one_time = 0;
const bool show_newline   = 1;
const bool no_newline     = 0;

/* bfprintf - bufferless printf
 * for solving:
 * simplicity and performance concerns,
 * everytime when you use 'printf',
 * Buffering occurs, which is not performant,
 * for this 'suckless' utility.
 * to solve this, i'm writing bfprintf.
 * - rar
 */

/* function signature */
void bfprintf(const char *str);

/* function implementation */
void
bfprintf(const char *str)
{
        /* write to STDOUT */
        write(1, str, strlen(str));
}

void
bfprintfln(const char *str)
{
        /* Create a new buffer: +1 for '\n', +1 for the null terminator '\0' */
        char strln[strlen(str) + 2];

        /* format the new string */
        snprintf(strln, sizeof(strln), "%s\n", str);

        /* write to STDOUT */
        write(1, strln, strlen(strln));
}

/* tmp main() for testing */
/* int */
/* main(int argc, const char **argv) */
/* { */
/*         /1* if no arg is given,exit. *1/ */
/*         if (argc == 1) */
/*         { */
/*                 bfprintfln("error: no argument is given."); */
/*                 return -1; */
/*         } */

/*         static const char *buf = "CPU:20% | UP:20m\n"; */

/*         write(1, buf, strlen(buf)); */

/*         /1* bfprintfln(argv[1]); *1/ */
/* } */
