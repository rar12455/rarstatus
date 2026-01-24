
void getuseddiskinfo(char partition[30]) {

  struct statvfs ds;

  if (statvfs(partition, &ds) == 0) {
    unsigned long long total = (unsigned long long)ds.f_blocks * ds.f_frsize;
    unsigned long long available =
        (unsigned long long)ds.f_bavail * ds.f_frsize;
    unsigned long long used = total - available;
    printf("DISK:");
    print_human_readable_data(used / 1024);
  } else {
    printf("DISK: unexpected error");
  }
}

