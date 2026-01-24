
void readbatterycapacity() {
  FILE *file;
  int capacitybat = 0;

  file = fopen(BATTERY_PATH,"r");

  if (file && fscanf(file, "%d", &capacitybat) == 1) {
                                                         
    FILE *status_file;
    status_file = fopen(BATTERY_STATE_PATH,"r");
    char status[25];

    if (status_file && fscanf(status_file, "%24s",status) == 1){
      if (strcmp("Discharging",status) == 0){
          printf("BAT:%d%%-", capacitybat);
      }
      else {
          printf("BAT:%d%%+", capacitybat);
      }
    }
  } 
  else {
    printf("error: BATTERY_PATH; file not found.\n");
  }

  if (file){
    fclose(file);
  }
}
