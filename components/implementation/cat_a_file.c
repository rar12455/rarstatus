/*
 * See LICENSE file for copyright and license details.
 */

#include <stdio.h>
#include <string.h>

#include "../../config.h"

void
cat_a_file(void)
{
        FILE *file;
        file = fopen(CAT_FILE_PATH, "r");
        char buffer[CAT_FILE_LENGTH];

        if (!file)
        {
                printf("file not found!: %s", CAT_FILE_PATH);
                return;
        }

        fgets(buffer, sizeof(buffer), file);

        size_t len = strcspn(buffer, "\r\n");

        if (len < sizeof(buffer))
        {
                buffer[len] = '\0';
        }

        printf("%s", buffer);

        fclose(file);
}
