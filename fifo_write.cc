// Copyright 2024 JOK Inc. All Rights Reserved.
// Author: easytojoin@163.com (jok)

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char** argv) {
  if (mkfifo("myfifo", 0600) == -1 && errno != EEXIST) {
    printf("mkfifo failed\n");
    return -1;
  }
  char buf[30] = "this is a message";
  int fd = open("./myfifo", O_WRONLY);
  if (fd < 0) {
    printf("write open failed\n");
    return -1;
  } else {
    printf("write open success\n");
  }
  while (1) {
    sleep(1);
    write(fd, buf, strlen(buf));
  }
  close(fd);
  return 0;
}
