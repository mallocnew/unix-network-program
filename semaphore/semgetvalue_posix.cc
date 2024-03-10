// Copyright 2024 JOK Inc. All Rights Reserved.
// Author: easytojoin@163.com (jok)

#include <semaphore.h>
#include <stdio.h>

int main(int argc, char** argv) {
  sem_t* sem;
  int val;
  if (argc != 2) {
    fprintf(stderr, "no semaphore name");
  }
  sem = sem_open(argv[1], 0);
  sem_getvalue(sem, &val);
  printf("get value of %s is %d \n", argv[1], val);
  return 0;
}
