#define _POSIX_C_SOURCE 200112L

#include <limits.h>
#include <stdio.h>
#include <unistd.h>

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 64
#endif

void
print_hostname()
{
        char hostname[HOST_NAME_MAX];

        if (gethostname(hostname, sizeof(hostname)) == 0)
        {
                printf("HOST:%s", hostname);
        }
        else
        {
                printf("unknown-host");
        }
}
