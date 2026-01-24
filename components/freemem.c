
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
