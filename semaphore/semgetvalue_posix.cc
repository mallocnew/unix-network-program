// Copyright 2024 JOK Inc. All Rights Reserved.
// Author: easytojoin@163.com (jok)

#include <semaphore.h>
#include <stdio.h>

int main(int argc, char** argv) {
  sem_t* sem;
  int val;
  if (argc != 2) {
    fprintf(stderr, "no semaphore name\n");
    return -1;
  }
  const char* sem_name = argv[1];
  sem = sem_open(sem_name, 0);
  //if (sem == nullptr) {
  //  fprintf(stderr, "sem_open %s failed\n", sem_name);
  //  return -1;
  //}
  int ret;
  if ((ret = sem_getvalue(sem, &val)) != 0) {
    fprintf(stderr, "sem_getvalue failed, ret %d", ret);
    return -1;
  }
  printf("get value of %s is %d \n", sem_name, val);
  return 0;
}
