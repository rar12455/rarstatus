/*
 * See LICENSE file for copyright and license details.
 */

#include "../cpu_usage.h"
#include <stdio.h>
#include <unistd.h>

void
print_cpu_usage(const int cpu_usage_percision)
{
        FILE              *file;
        unsigned long long user, nice, system, idle, iowait, irq, softirq;
        unsigned long long total_first, idle_first, total_second, idle_second;

        file = fopen("/proc/stat", "r");

        if (!file)
        {
                perror("error when opening: /proc/stat");
                return;
        }

        fscanf(file, "cpu %llu %llu %llu %llu %llu %llu %llu", &user, &nice,
               &system, &idle, &iowait, &irq, &softirq);

        idle_first  = idle;
        total_first = user + nice + system + idle + iowait + irq + softirq;

        sleep(1);

        file = fopen("/proc/stat", "r");

        fscanf(file, "cpu %llu %llu %llu %llu %llu %llu %llu", &user, &nice,
               &system, &idle, &iowait, &irq, &softirq);

        idle_second  = idle;
        total_second = user + nice + system + idle + iowait + irq + softirq;

        fclose(file);

        double cpu_usage =
            100.0 * (total_second - total_first - (idle_second - idle_first)) /
            (total_second - total_first);

        printf("CPU:%.*f%%\n", cpu_usage_percision, cpu_usage);
}
