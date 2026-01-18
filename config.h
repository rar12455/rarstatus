/* Configuration for rarstatus */

/* Update interval in seconds */
#define INTERVAL 60

/* Formatting preferences */
static const bool show_newline = true;
static const bool no_newline = false;

/* iso_format */
static const bool iso_format   = true;

/* Separator string */
static const char *separator = " | ";

/* disk partition mount point for disk usage look-up */

char partition[30] = "/"; // by default it shows / i.e: root partition, type: df -h in terminal to see details.
