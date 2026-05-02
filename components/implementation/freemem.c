/*
 * See LICENSE file for copyright and license details.
 */

#include <stdio.h>
#include <string.h>

#include "../print_human_readable_data.h"

void
getfreememinfo(void)
{
        char               line[128];
        FILE              *file         = fopen("/proc/meminfo", "r");
        unsigned long long MemAvailable = 0;

        if (!file)
        {
                perror("Error opening: /proc/meminfo");
                return;
        }

        while (fgets(line, sizeof(line), file))
        {
                if (strncmp(line, "MemAvailable:", 13) == 0)
                {
                        sscanf(line, "MemAvailable: %llu", &MemAvailable);
                }
        }
        fclose(file);
        printf("RAM:");
        print_human_readable_data((unsigned long long)MemAvailable);
}
