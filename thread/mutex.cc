// Copyright 2024 JOK Inc. All Rights Reserved.
// Author: easytojoin@163.com (jok)

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t mutex;
static int shared_data = 0;

void* increment(void*) {
  for (int i = 0; i < 100000; i++) {
    pthread_mutex_lock(&mutex);
    shared_data++;
    pthread_mutex_unlock(&mutex);
  }
  return nullptr;
}

int main(int argc, char** argv) {
  pthread_t thread_1, thread_2;
  pthread_mutex_init(&mutex, NULL);
  if (pthread_create(&thread_1, NULL, increment, NULL) != 0) {
    return -1;
  }
  if (pthread_create(&thread_2, NULL, increment, NULL) != 0) {
    return -1;
  }
  pthread_join(thread_1, NULL);
  pthread_join(thread_2, NULL);
  printf("Final res: %d\n", shared_data);
  pthread_mutex_destroy(&mutex);
  return 0;
}
