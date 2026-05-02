/*
 * See LICENSE file for copyright and license details.
 */

#define _POSIX_C_SOURCE 200112L

#include <stdio.h>

#include "../../config.h"

void
run_command(void)
{
        FILE *fp = popen(COMMAND_NAME, "r");

        if (!fp)
        {
                perror("error: unable to run command");
                return;
        }

        char buffer[256];
        while (fgets(buffer, sizeof(buffer), fp))
        {
                printf("%s", buffer);
        }
        pclose(fp);
}
