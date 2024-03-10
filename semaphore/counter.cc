// Copyright 2024 JOK Inc. All Rights Reserved.
// Author: easytojoin@163.com (jok)

#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <unistd.h>

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

pid_t get_pid() {
  pid_t res = syscall(SYS_getpid);
  return res;
}

int main(int argc, char** argv) {
  const char* program = argv[0];
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <loop number>\n", program);
    return -1;
  }
  int loop = atoi(argv[1]);
  sem_t* signal = sem_open("counter", O_CREAT | O_EXCL, FILE_MODE, 1);
  sem_unlink("counter");

  int count = 0;
  int pid;
  if ((pid = fork()) == 0) {
    for (int i = 0; i < loop; i++) {
      sem_wait(signal);
      printf("child process(%d): %d\n", get_pid(), count++);
      sem_post(signal);
    }
    exit(0);
  }
  if (pid == -1) {
    fprintf(stderr, "Create child process failed!\n");
    return -1;
  }
  fprintf(stdout, "%d Create child process %d\n", get_pid(), pid);
  for (int i = 0; i < loop; i++) {
    sem_wait(signal);
    printf("parent process(%d): %d\n", get_pid(), count++);
    sem_post(signal);
  }
  return 0;
}
