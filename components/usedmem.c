
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
    } else if (strncmp(line, "MemAvailable:", 13) == 0) {
      sscanf(line, "MemAvailable: %d", &MemAvailable); // NOLINT
      found_count++;
    }
  }
  fclose(file);

  if (found_count == 2) {
    int UsedMemory = MemTotal - MemAvailable;
    printf("RAM:");
    print_human_readable_data((long long)UsedMemory);
  } else {
    printf("Error: Could not parse all required memory fields.\n");
  }
}

