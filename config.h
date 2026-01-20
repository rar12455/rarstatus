/* Configuration for rarstatus */

/* Update interval in seconds */
#define INTERVAL 1

/* Formatting preferences */
const bool show_newline = true;
const bool no_newline = false;

/* iso_format */
const bool iso_format   = true;

/* Separator string */
const char *separator = " | ";

/* disk partition mount point for disk usage look-up */

char partition[30] = "/"; // by default it shows / i.e: root partition, type: df -h in terminal to see details.
