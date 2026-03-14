#include <stdint.h>
#include <stdio.h>

typedef struct
{
        uintmax_t user, nice, system, idle, iowait, irq, softirq, steal;
} cpustat;

static int
get_cpu_usage(cpustat *cpustat)
{
        FILE *file = fopen("/proc/stat", "r");
        if (!file)
        {
                perror("error when opening reqired system file.");
                return 0;
        }
        fscanf(file, "cpu %ju %ju %ju %ju %ju %ju %ju %ju", &cpustat->user,
               &cpustat->nice, &cpustat->system, &cpustat->idle,
               &cpustat->iowait, &cpustat->irq, &cpustat->softirq,
               &cpustat->steal);
        fclose(file);
        return 1;
}

const char *
cpu_percentage(void)
{
        static cpustat previous;
        cpustat        current;
        get_cpu_usage(&current);
        static char buffer[8];

        uintmax_t total_previous =
            previous.user + previous.nice + previous.system + previous.idle +
            previous.iowait + previous.irq + previous.softirq + previous.steal;

        uintmax_t total_current = current.user + current.nice + current.system +
                                  current.idle + current.iowait + current.irq +
                                  current.softirq + current.steal;

        uintmax_t idle_previous = previous.idle + previous.iowait;
        uintmax_t idle_current  = current.idle + current.iowait;

        uintmax_t delta_total = total_current - total_previous;
        uintmax_t delta_idle  = idle_current - idle_previous;

        /* update previous for next call */
        previous = current;

        if (delta_total == 0) /* avoid division by zero */
        {
                return NULL;
        }

        snprintf(buffer, sizeof(buffer), "%d",
                 (int)(100 * (1 - delta_idle / delta_total)));
        return buffer;
}

int
cpu_usage(void)
{
        const char *cpu_usage = cpu_percentage();
        cpu_usage             = cpu_percentage();
        if (cpu_usage)
        {
                printf("CPU usage: %s%%\n", cpu_usage);
        }
        return 0;
}
