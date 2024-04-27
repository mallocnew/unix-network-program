// Copyright 2024 JOK Inc. All Rights Reserved.
// Author: easytojoin@163.com (jok)

#include <string.h>
#include <unistd.h>

#include <iostream>

int main(int argc, char** argv) {
  int pipe_fds[2];
  int ret = pipe(pipe_fds);
  if (ret == -1) {
    std::cerr << "failed to create pipe\n";
    return -1;
  }
  int pid = fork();
  if (pid < 0) {
    std::cerr << "failed to create sub process\n";
    return -1;
  }
  if (pid == 0) {
    close(pipe_fds[1]);
    char buf[128];
    int n = read(pipe_fds[0], buf, sizeof(buf) - 1);
    std::cout << "read " << n << " from pipe\n";
    std::string msg(buf, n);
    fprintf(stdout, "sub process read[%lu]:%s\n", msg.size(), msg.c_str());
    close(pipe_fds[0]);
  } else {
    close(pipe_fds[0]);
    const char* msg = "I am from father process\n";
    std::cout << "write " << strlen(msg) << " to pipe\n";
    write(pipe_fds[1], msg, strlen(msg));
    close(pipe_fds[1]);
  }
  return 0;
}
