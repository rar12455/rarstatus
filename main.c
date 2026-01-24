#define _POSIX_C_SOURCE 200112L
#define _DEFAULT_SOURCE

#include <limits.h> // For HOST_NAME_MAX
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

void print_human_readable_data(long long kib) {  /* NEEDED for Memory and Disk componenet(s) */
  const char *units[] = {"Ki", "Mi", "Gi", "Ti", "Pi"};
  double value = (double)kib;
  int i = 0;

  while (value >= 1024 && i < 4) {
    value /= 1024;
    i++;
  }

  printf("%.2f %sB", value, units[i]);
}

/* include components that you want */

#include "components/battery.c"
#include "components/brightness.c"
#include "components/cat_a_file.c"
#include "components/datetime.c"
#include "components/freemem.c"
#include "components/usedmem.c"
#include "components/getkernelversion.c"
#include "components/getuseddiskinfo.c"
#include "components/printhostname.c"
#include "components/uptime.c"

void decorate(bool show_newline) {
  if (show_newline) {
    putchar('\n');
  } 
  else {
    fputs(separator, stdout);
  }
}


void main_loop() {

  while (1) {

  /* the main loop of the program,
   * you can customize components by adding or removing them.
   * if you don't use any disk or memory component(s) you can comment out print_human_readable_data function,
   * since, it is unused function in that case.
   */

    cat_a_file();
    decorate(no_newline);
    brightness(1);
    decorate(no_newline);
    print_Hostname();
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

    if (print_one_time == 1){
      return;
    }

    fflush(stdout);  // needed for print STDOUT
    sleep(INTERVAL); /// sleep value

  }
}

int main(int argc, char *argv[]) {

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-v") == 0) {
      printf("rarstatus beta\n");
      return 0;
    }
    else if (strcmp(argv[i], "-h") == 0){
      printf("usage: [-v = version] [-h = help] [-1 print one time]\n");
      return 0;
    }
    else if (strcmp(argv[i],"-1") == 0) {
      print_one_time = 1;
      main_loop();
      return 0;
    }
    else if (argv[i][0] == '-') {
      printf("undefined argument: %s\n", argv[i]);
      return 1;
    }
    else {
      printf("not an argument: %s\n", argv[i]);
      return 1;
    }
  }

  main_loop();
  return 0;
}
