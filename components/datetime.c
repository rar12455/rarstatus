
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
           local_time->tm_year + 1900, // year
           local_time->tm_mon + 1,     // month
           local_time->tm_mday,        // day
           local_time->tm_hour,        // hour
           local_time->tm_min);        // minutes
  }
  else {
    printf("error: format error\n");
  }
}
