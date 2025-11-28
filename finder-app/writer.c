#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h> 

int main(int argc, char** argv) {
  openlog(argv[0], 0, LOG_USER);

  if (argc != 3) {
    syslog(LOG_ERR, "Wrong number of arguments, provide filename and content to write");
    closelog();
    exit(1);
  }

  FILE *fptr;
  fptr = fopen(argv[1], "w");
  if (!fptr) {
    syslog(LOG_ERR, "Failed to create file, errno: %d", errno);
    closelog();
    exit(1);
  }

  syslog(LOG_INFO, "Writing %s to %s", argv[2], argv[1]);

  size_t len = strlen(argv[2]);
  size_t written = fwrite(argv[2], sizeof(char), strlen(argv[2]), fptr);
  int r = 0;
  if (len != written) {
    syslog(LOG_ERR, "Failed to write to file");
    r = 1;
  } 
  
  fclose(fptr);
  closelog();
  return r;
}
