#define _POSIX_C_SOURCE 200112L

#include <stdio.h>

#include "../config.h"

void
run_command()
{
                FILE *fp = popen(COMMAND_NAME, "r");
                char  buffer[256];
                while (fgets(buffer, sizeof(buffer), fp))
                {
                                printf("%s", buffer);
                }
                pclose(fp);
}
