// Copyright 2024 JOK Inc. All Rights Reserved.
// Author: easytojoin@163.com (jok)

#include <semaphore.h>
#include <stdio.h>

int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf(stderr, "usage: %s <semaphore name> to unlink!", argv[0]);
    return 1;
  }
  int ret;
  if ((ret = sem_unlink(argv[1])) != 0) {
    fprintf(stderr, "unlink semaphore %s err: %d\n", argv[1], ret);
    return 1;
  }
  fprintf(stdout, "unlink semaphore %s\n", argv[1]);
  return 0;
}
