
void getkernelversion() {
  struct utsname name;
  if (uname(&name) == 0) {
    printf("KERN:%s", name.release);
  } else {
    printf("error: Kernel version not found.");
  }
}
