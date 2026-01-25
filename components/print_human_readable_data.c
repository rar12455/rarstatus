
void print_human_readable_data(long long kib) {  /* NEEDED for Memory and Disk componenet(s) */
  const char *units[] = {"Ki", "Mi", "Gi", "Ti", "Pi"};
  double value = (double)kib;
  int i = 0;

  while (value >= 1024 && i < 4) {
    value /= 1024;
    i++;
  }

  printf("%.2f %sB", value, units[i]);
}
