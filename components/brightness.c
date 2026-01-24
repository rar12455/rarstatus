
void brightness(int argc) {

  /* modes:
   * 0 = see brightness value
   * 1 = see brightness percentage
   */

  if (argc == 0) {

    FILE *file;
    int brightness_val = 0;
    file = fopen(BRIGHTNESS_FILE_PATH, "r");

    if (!file) {
      printf("file not found: %s\n", BRIGHTNESS_FILE_PATH);
      return;
    }

    fscanf(file, "%d", &brightness_val); // NOLINT

    printf("BRI:%d", brightness_val);

    fclose(file);
  } 
  else {

    FILE *file;
    FILE *max_brightness_file;
    float brightness_val = 0;
    float max_brightness_val = 0;
    float brightness_perc = 0;

    // FILE 1

    file = fopen(BRIGHTNESS_FILE_PATH, "r");

    if (!file) {
      printf("file not found: %s\n", BRIGHTNESS_FILE_PATH);
      return;
    }

    fscanf(file, "%f", &brightness_val); // NOLINT

    fclose(file);

    // FILE 2

    max_brightness_file = fopen(MAX_BRIGHTNESS_FILE_PATH, "r");

    if (!max_brightness_file) {
      printf("file not found: %s\n", MAX_BRIGHTNESS_FILE_PATH);
      return;
    }

    fscanf(max_brightness_file, "%f", &max_brightness_val); // NOLINT
    fclose(max_brightness_file);

    brightness_perc = brightness_val / max_brightness_val * 100;
    printf("BRI:%.0f%%", brightness_perc);
  }
}

