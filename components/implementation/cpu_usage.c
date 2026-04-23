/*
 * See LICENSE file for copyright and license details.
 */

#include "../cpu_usage.h"
#include "../../config.h"
#include <stdio.h>
#include <unistd.h>

void
print_cpu_usage(const int cpu_usage_percision)
{

        FILE              *file;
        unsigned long long user, nice, system, idle, iowait, irq, softirq;

        /* using static variables to avoid sleep() */
        static unsigned long long total_first = 0, idle_first = 0;
        unsigned long long        total_second, idle_second;

        file = fopen("/proc/stat", "r");

        if (!file)
        {
                perror("error when opening: /proc/stat");
                return;
        }

        fscanf(file, "cpu %llu %llu %llu %llu %llu %llu %llu", &user, &nice,
               &system, &idle, &iowait, &irq, &softirq);

        fclose(file);

        total_second = user + nice + system + idle + iowait + irq + softirq;
        idle_second  = idle;

        /*
         * On the first run, the total_first would be 0,
         * to avoid any issues, check if the total_first is larger than 0.
         */
        if (total_first > 0)
        {
                double cpu_usage =
                    100.0 *
                    (total_second - total_first - (idle_second - idle_first)) /
                    (total_second - total_first);

                printf("CPU:%.*f%%", cpu_usage_percision, cpu_usage);
        }
        else
        {
                printf("CPU:" UNKNOWN_STR);
        }
        total_first = total_second;
        idle_first  = idle_second;
}
