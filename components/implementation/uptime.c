/*
 * See LICENSE file for copyright and license details.
 */

#include <stdio.h>
#include <sys/sysinfo.h>

void
uptime(void)
{
        struct sysinfo info;

        if (sysinfo(&info) != 0)
        {
                printf("UP:err");
                return;
        }

        long total_seconds = info.uptime;

        if (total_seconds >= 3600)
        {
                int hours   = total_seconds / 3600;
                int minutes = (total_seconds % 3600) / 60;
                printf("UP:%dh %dm", hours, minutes);
        }
        else
        {
                int minutes = total_seconds / 60;
                printf("UP:%dm", minutes);
        }
}
