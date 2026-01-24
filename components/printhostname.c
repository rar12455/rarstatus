
void print_Hostname() {
  
#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 64
#endif

  char hostname[HOST_NAME_MAX];

  if (gethostname(hostname, sizeof(hostname)) == 0) {
    printf("HOST:%s", hostname);
  }
  else {
    printf("unknown-host");
  }
}

