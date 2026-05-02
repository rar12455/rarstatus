/*
 * See LICENSE file for copyright and license details.
 */

#include <stdio.h>
#include <string.h>

#include "../print_human_readable_data.h"

void
getusedmeminfo(void)
{
        char               line[128];
        FILE              *file         = fopen("/proc/meminfo", "r");
        unsigned long long MemTotal     = 0;
        unsigned long long MemAvailable = 0;
        unsigned long long found_count  = 0;

        if (!file)
        {
                perror("Error opening: /proc/meminfo");
                return;
        }

        while (fgets(line, sizeof(line), file) && found_count < 2)
        {
                if (strncmp(line, "MemTotal:", 9) == 0)
                {
                        sscanf(line, "MemTotal: %llu", &MemTotal);
                        found_count++;
                }
                else if (strncmp(line, "MemAvailable:", 13) == 0)
                {
                        sscanf(line, "MemAvailable: %llu", &MemAvailable);
                        found_count++;
                }
        }

        fclose(file);

        if (found_count == 2)
        {
                unsigned long long UsedMemory = MemTotal - MemAvailable;
                printf("RAM:");
                print_human_readable_data((unsigned long long)UsedMemory);
        }
        else
        {
                printf("Error: Could not parse all required memory fields.\n");
                return;
        }
}
