// Copyright 2024 JOK Inc. All Rights Reserved.
// Author: easytojoin@163.com (jok)

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int fd = open("./myfifo", O_RDONLY);
  if (fd < 0) {
    printf("read open failed\n");
    return -1;
  } else {
    printf("read open success\n");
  }

  char buf[30] = {'\0'};
  while (1) {
    int nread = read(fd, buf, sizeof(buf));
    printf("read %d byte,context is:%s\n", nread, buf);
  }

  close(fd);
  return 0;
}