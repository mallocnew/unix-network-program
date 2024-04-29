// Copyright 2024 JOK Inc. All Rights Reserved.
// Author: easytojoin@163.com (jok)

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_rwlock_t rwlock;
static int counter = 0;

void* reader(void*) {
  for (auto i = 0; i < 10000; i++) {
    pthread_rwlock_rdlock(&rwlock);
    printf("data: %d\n", counter);
    pthread_rwlock_unlock(&rwlock);
  }
  return NULL;
}

void* writer(void*) {
  for (auto i = 0; i < 10000; i++) {
    pthread_rwlock_wrlock(&rwlock);
    counter++;
    pthread_rwlock_unlock(&rwlock);
  }
  return NULL;
}

int main(int argc, char** argv) {
  pthread_t read_thread, write_thread;
  pthread_rwlock_init(&rwlock, NULL);
  if (pthread_create(&read_thread, NULL, reader, NULL) != 0) {
    return -1;
  }
  if (pthread_create(&write_thread, NULL, writer, NULL) != 0) {
    return -1;
  }
  pthread_join(read_thread, NULL);
  pthread_join(write_thread, NULL);
  printf("counter: %d\n", counter);
  pthread_rwlock_destroy(&rwlock);
  return 0;
}
