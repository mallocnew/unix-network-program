// Copyright 2024 JOK Inc. All Rights Reserved.
// Author: easytojoin@163.com (jok)

#include <pthread.h>
#include <stdio.h>
#include <string.h>

void* task(void* arg) {
  printf("thread\n");
  return NULL;
}

int main(int argc, char** argv) {
  pthread_t tid;
  int ret = pthread_create(&tid, NULL, &task, NULL);
  if (ret != 0) {
    fprintf(stderr, "Error when create new thread: %s\n", strerror(ret));
    return ret;
  }
  pthread_join(tid, NULL);
  printf("main over\n");
  return 0;
}
