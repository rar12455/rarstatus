#include <stdbool.h>
/* #include <stdio.h> */
/* #include <string.h> */
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

/*
 * See LICENSE file for copyright and license details.
 */

/* #include <stdio.h> */
/* #include <time.h> */

/* const char * */
/* datetime_local(int iso_format_val) */
/* { */
/*         time_t     raw_time; */
/*         struct tm *local_time; */
/*         time(&raw_time); */
/*         local_time = localtime(&raw_time); */

/*         if (iso_format_val == 0) */
/*         { */
/*                 printf("Local time: %s", asctime(local_time)); */
/*         } */
/*         else if (iso_format_val == 1) */
/*         { */
/*                 /1* const char date = local_time->tm_mon; *1/ */
/*                 /1* printf("%d-%02d-%02d %02d:%02d", local_time->tm_year +
 * 1900, */
/*                  *1/ */
/*                 /1*        local_time->tm_mon + 1, local_time->tm_mday, *1/
 */
/*                 /1*        local_time->tm_hour, local_time->tm_min); *1/ */
/*                 return (const char *)(local_time->tm_min); */
/*         } */
/*         else */
/*         { */
/*                 printf("error: format error\n"); */
/*         } */
/* } */
/* /1* function signature *1/ */
/* void bfprintf(const char *str); */

/* /1* function implementation *1/ */
/* void */
/* bfprintf(const char *str) */
/* { */
/*         /1* write to STDOUT *1/ */
/*         write(1, str, strlen(str)); */
/* } */

/* void */
/* bfprintfln(const char *str) */
/* { */
/*         /1* Create a new buffer: +1 for '\n', +1 for the null terminator '\0'
 * *1/ */
/*         char strln[strlen(str) + 2]; */

/*         /1* format the new string *1/ */
/*         snprintf(strln, sizeof(strln), "%s\n", str); */

/*         /1* write to STDOUT *1/ */
/*         write(1, strln, strlen(strln)); */
/* } */

/* int */
/* main() */
/* { */
/*         const char *date = datetime_local(1); */
/*         /1* const char *date = "hi"; *1/ */
/*         /1* const char *dat = "hi"; *1/ */
/*         bfprintf(date); */
/*         return 0; */
/* } */
