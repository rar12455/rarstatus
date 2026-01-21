/* Configuration for rarstatus */

/* Update interval in seconds */
#define INTERVAL 1

/* Formatting preferences */
const bool show_newline = 1;
const bool no_newline = 0;

/* iso_format */
const bool iso_format = 1;

/* Separator string */
const char *separator = " | ";

/* disk partition mount point for disk usage look-up */

char partition[30] = "/"; // by default it shows / i.e: root partition, type: df
                          // -h in terminal to see details.

#define BRIGHTNESS_FILE_PATH "/sys/class/backlight/intel_backlight/brightness"
#define MAX_BRIGHTNESS_FILE_PATH                                               \
  "/sys/class/backlight/intel_backlight/max_brightness"
