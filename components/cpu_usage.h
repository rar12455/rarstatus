#ifndef CPU_USAGE_H
#define CPU_USAGE_H

typedef struct
{
} cpustat;

static int get_cpu_usage(cpustat *cpustat);

const char *cpu_percentage(void);

int cpu_usage(void);

#endif
