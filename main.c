#define _POSIX_C_SOURCE 200112L
#define _DEFAULT_SOURCE

#include <limits.h> /* For HOST_NAME_MAX */
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/statvfs.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <time.h>
#include <unistd.h>

/* config and utility file */

#include "config.h"
#include "util.h"

/* include components that you want */

#include "components/battery.h"
#include "components/brightness.h"
#include "components/cat_a_file.h"
#include "components/datetime.h"
#include "components/freemem.h"
#include "components/getkernelversion.h"
#include "components/getuseddiskinfo.h"
#include "components/print_human_readable_data.h" /* NEEDED FOR memory and disk component(s) */
#include "components/printhostname.h"
#include "components/run_command.h"
#include "components/uptime.h"
#include "components/usedmem.h"

void
decorate(bool show_newline)
{
        if (show_newline)
        {
                putchar('\n');
        }
        else
        {
                fputs(separator, stdout);
        }
}

void
main_loop()
{

        while (1)
        {

                /* the main loop of the program,
                 * you can customize components by adding or removing them.
                 */

                run_command();
                decorate(no_newline);
                getfreememoryinfo();
                cat_a_file();
                decorate(no_newline);
                brightness(1);
                decorate(no_newline);
                print_hostname();
                decorate(no_newline);
                getuseddiskinfo(partition);
                decorate(no_newline);
                getkernelversion();
                decorate(no_newline);
                getusedmeminfo();
                decorate(no_newline);
                readbatterycapacity();
                decorate(no_newline);
                uptime();
                decorate(no_newline);
                datetime(iso_format);
                decorate(show_newline);

                if (print_one_time == 1)
                {
                        return;
                }

                fflush(stdout);  // needed for print STDOUT
                sleep(INTERVAL); /// sleep value
        }
}

int
main(int argc, char *argv[])
{

        for (int i = 1; i < argc; i++)
        {
                if (strcmp(argv[i], "-v") == 0)
                {
                        printf("rarstatus v1.0\n");
                        return 0;
                }
                else if (strcmp(argv[i], "-h") == 0)
                {
                        printf("usage: [-v = version] [-h = help] [-1 print "
                               "one time]\n");
                        return 0;
                }
                else if (strcmp(argv[i], "-1") == 0)
                {
                        print_one_time = 1;
                        main_loop();
                        return 0;
                }
                else if (argv[i][0] == '-')
                {
                        printf("undefined argument: %s\n", argv[i]);
                        return 1;
                }
                else
                {
                        printf("not an argument: %s\n", argv[i]);
                        return 1;
                }
        }
        main_loop();
        return 0;
}
