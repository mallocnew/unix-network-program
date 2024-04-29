// Copyright 2024 JOK Inc. All Rights Reserved.
// Author: easytojoin@163.com (jok)

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <iostream>

void* task(void* arg) {
  pthread_t tid = pthread_self();
  pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
  pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
  printf("new thread[%lu]\n", (u_int64_t)tid);
  for (int i = 0; i < 10; ++i) {
    printf("Thread working...\n");
    sleep(1);
  }
  printf("thread[%lu] exist\n", (u_int64_t)tid);
  return NULL;
}

int main(int argc, char** argv) {
  pthread_t tid;
  int ret = pthread_create(&tid, NULL, &task, NULL);
  if (ret != 0) {
    fprintf(stderr, "Error when create new thread: %s\n", strerror(ret));
    return ret;
  }
  sleep(2);
  ret = pthread_cancel(tid);
  if (ret != 0) {
    fprintf(stderr, "pthread cancel\n");
    return ret;
  }
  void* thread_result;
  ret = pthread_join(tid, &thread_result);
  if (ret != 0) {
    fprintf(stderr, "pthread join\n");
    return ret;
  }
  if (thread_result == PTHREAD_CANCELED) {
    printf("thread was canceled, ret: %ld\n", (int64_t)thread_result);
  } else {
    std::cout << "thread existed, ret" << thread_result << "\n";
  }
  pthread_t main_tid = pthread_self();
  printf("main[%lu] over\n", (u_int64_t)main_tid);
  return 0;
}
