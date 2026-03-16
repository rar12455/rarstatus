#include <stdio.h>

void
print_human_readable_data(long long kib)
{
                const char *units[] = {"Ki", "Mi", "Gi", "Ti", "Pi"};
                double      value   = (double)kib;
                int         i       = 0;

                while (value >= 1024 && i < 4)
                {
                                value /= 1024;
                                i++;
                }

                printf("%.2f %sB", value, units[i]);
}
