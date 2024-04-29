// Copyright 2024 JOK Inc. All Rights Reserved.
// Author: easytojoin@163.com (jok)

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <atomic>

pthread_mutex_t mutex;
pthread_cond_t cond;
std::atomic_bool ready = false;

void* consumer(void*) {
  pthread_t tid = pthread_self();
  sleep(2);
  pthread_mutex_lock(&mutex);
  printf("Producer[%lu]: produce data\n", (uint64_t)tid);
  ready.store(true);
  pthread_cond_signal(&cond);
  pthread_mutex_unlock(&mutex);
  return NULL;
}

void* producer(void*) {
  pthread_t tid = pthread_self();
  pthread_mutex_lock(&mutex);
  while (!ready) {
    printf("Consumer[%lu]: wait for data ready\n", (uint64_t)tid);
    pthread_cond_wait(&cond, &mutex);
  }
  printf("Consumer[%lu]: consume data\n", (uint64_t)tid);
  pthread_mutex_unlock(&mutex);
  return NULL;
}

int main(int argc, char** argv) {
  pthread_t producer_tid, consumer_tid;
  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&cond, NULL);
  if (pthread_create(&producer_tid, NULL, producer, NULL) != 0) {
    return -1;
  }
  if (pthread_create(&consumer_tid, NULL, consumer, NULL) != 0) {
    return -1;
  }
  pthread_join(producer_tid, NULL);
  pthread_join(consumer_tid, NULL);
  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&cond);
  return 0;
}
