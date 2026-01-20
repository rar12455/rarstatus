#define _POSIX_C_SOURCE 200112L
#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <sys/utsname.h>
#include <sys/statvfs.h>
#include <limits.h> // For HOST_NAME_MAX
#include <sys/sysinfo.h>

#include "config.h"

/* rarstatus - slstatus but better:
 * DS agnostic
 * lightweight
 * customizable
 */ 

void uptime() {

   struct sysinfo info;

    if (sysinfo(&info) != 0) {
        printf("UP:err");
        return;
    }

    long total_seconds = info.uptime; 

    if (total_seconds >= 3600) {
        int hours = total_seconds / 3600;
        int minutes = (total_seconds % 3600) / 60;
        printf("UP:%dh %dm", hours, minutes);
    } 
    else {
        int minutes = total_seconds / 60;
        printf("UP:%dm", minutes);
    }
}

void readbatterycapacity() {
    FILE *file;
    int capacitybat = 0;

    file = fopen("/sys/class/power_supply/BAT0/capacity", "r");
    if (file && fscanf(file, "%d", &capacitybat) == 1) { // NOLINT
        printf("BAT:%d%%", capacitybat);
    }
    else {
        printf("error: /sys/class/power_supply/BAT0/capacity; file not found.\n");
    }
    
    if (file) fclose(file);
}

void datetime(int iso_format_val) {
    time_t raw_time;
    struct tm *local_time;
    time(&raw_time);
    local_time = localtime(&raw_time);

    if (iso_format_val == 0) {
        printf("Local time: %s", asctime(local_time));
    }
    else if (iso_format_val == 1) {
        printf("%d-%02d-%02d %02d:%02d",
            local_time->tm_year + 1900, //year
            local_time->tm_mon + 1, //month
            local_time->tm_mday, // day
            local_time->tm_hour, // hour
            local_time->tm_min); // minutes
    }
    else {
        printf("error: format error\n");
    }
}

void print_human_readable_data(long long kib) {
    const char* units[] = {"Ki", "Mi", "Gi", "Ti", "Pi"};
    double value = (double)kib;
    int i = 0;

    while (value >= 1024 && i < 4) {
        value /= 1024;
        i++;
    }

    printf("%.2f %sB", value, units[i]);
}

void getusedmeminfo() {
    char line[128];
    FILE *file = fopen("/proc/meminfo", "r");
    int MemTotal = 0;
    int MemAvailable = 0;
    int found_count = 0;

    if (!file) {
        perror("Error opening: /proc/meminfo");
        return;
    }

    while (fgets(line, sizeof(line), file) && found_count < 2) {
        if (strncmp(line, "MemTotal:", 9) == 0) {
            sscanf(line, "MemTotal: %d", &MemTotal); // NOLINT
            found_count++;
        } 
	else if (strncmp(line, "MemAvailable:", 13) == 0) {
            sscanf(line, "MemAvailable: %d", &MemAvailable); // NOLINT
            found_count++;
        }
    }
    fclose(file);

    if (found_count == 2) {
        int UsedMemory = MemTotal - MemAvailable;
	printf("RAM:");
        print_human_readable_data((long long)UsedMemory);
    } 
    else {
        printf("Error: Could not parse all required memory fields.\n");
    }
}

void getfreememoryinfo() {
    char line[128];
    FILE *file = fopen("/proc/meminfo", "r");
    int MemAvailable = 0;

    if (!file) {
        perror("Error opening: /proc/meminfo");
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "MemAvailable:", 13) == 0) {
            sscanf(line, "MemAvailable: %d", &MemAvailable); // NOLINT
        }
    }
    fclose(file);
    printf("RAM:");
    print_human_readable_data((long long)MemAvailable);
}

void getkernelversion(){
     struct utsname name;
     if (uname(&name) == 0){
	     printf("KERN:%s",name.release);
     }
     else {
	     printf("error: Kernel version not found.");
     }
}

void getuseddiskinfo(char partition[30]){

	struct statvfs ds;

	if (statvfs(partition,&ds) == 0){
		unsigned long long total = (unsigned long long)ds.f_blocks * ds.f_frsize;
		unsigned long long available = (unsigned long long)ds.f_bavail * ds.f_frsize;
		unsigned long long used = total - available;
		printf("DISK:");
		print_human_readable_data(used / 1024);
	}
	else {
		printf("DISK: unexpected error");
	}
}

void decorate(bool show_newline) {
    if (show_newline) {
        putchar('\n');
    } 
    else {
        fputs(separator, stdout);
    }
}

void print_Hostname() {
    #ifndef HOST_NAME_MAX
        #define HOST_NAME_MAX 64
    #endif

    char hostname[HOST_NAME_MAX];

    if (gethostname(hostname, sizeof(hostname)) == 0) {
        printf("HOST:%s", hostname);
    } else {
        printf("unknown-host");
    }
}

void main_loop(){

    while (1) {
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

        fflush(stdout); // needed for print STDOUT
        sleep(INTERVAL); /// sleep value
    }

}



int main(int argc, char *argv[]) {

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-v") == 0) {
            printf("rarstatus beta\n");
            return 0;
        } else if (argv[i][0] == '-') {
            printf("undefined argument: %s\n", argv[i]);
            return 1;
        } else {
            printf("not an argument: %s\n", argv[i]);
            return 1;
        }
    }

    main_loop();
    return 0;
}
