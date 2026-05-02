/*
 * See LICENSE file for copyright and license details.
 */

#include <stdio.h>
#include <sys/utsname.h>

void
getkernelversion(void)
{
        struct utsname name;
        if (uname(&name) == 0)
        {
                printf("KERN:%s", name.release);
        }
        else
        {
                printf("error: Kernel version not found.");
        }
}
