#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>

/* Update interval in seconds */
#define INTERVAL 1

/* Define the "unknown" string, will be used for unknown data */
#define UNKNOWN_STR "n/a"

/* Brightness file paths */
#define BRIGHTNESS_FILE_PATH "/sys/class/backlight/intel_backlight/brightness"
#define MAX_BRIGHTNESS_FILE_PATH                                               \
        "/sys/class/backlight/intel_backlight/max_brightness"

/* Battery paths */
#define BATTERY_PATH "/sys/class/power_supply/BAT0/capacity"
#define BATTERY_STATE_PATH "/sys/class/power_supply/BAT0/status"

/* cat_a_file settings */
#define CAT_FILE_PATH "/home/USER/foo.txt"
#define CAT_FILE_LENGTH 64

/* run_command setting */
#define COMMAND_NAME "echo 'hello world!' "

/* Variables defined in config.c */
extern const bool  iso_format;
extern const char *separator;
extern char        partition[30];

#endif
