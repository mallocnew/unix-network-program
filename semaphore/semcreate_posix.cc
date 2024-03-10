// Copyright 2024 JOK Inc. All Rights Reserved.
// Author: easytojoin@163.com (jok)

#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

int main(int argc, char** argv) {
  int flags = O_CREAT | O_RDWR;
  int c;
  unsigned int value = 1;
  while ((c = getopt(argc, argv, "ei:")) != -1) {
    switch (c) {
      case 'e':
        flags |= O_EXCL;
        break;
      case 'i':
        value = atoi(optarg);
        break;
      default:
        break;
    }
  }
  if (optind != argc - 1)
    printf("usage: semcreate [-e] [-i initalvalue] <name>");
  sem_t* sem = sem_open(argv[optind], flags, FILE_MODE, value);
  sem_close(sem);
  return 0;
}
