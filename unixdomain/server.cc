// Copyright 2024 JOK Inc. All Rights Reserved.
// Author: easytojoin@163.com (jok)

#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include <iostream>

int main(int argc, char **argv) {
  sockaddr_un server_addr;
  if (argc < 2) {
    fprintf(stderr, "invalid params\n");
    return -1;
  }
  int listen_fd = socket(AF_UNIX, SOCK_STREAM, 0);
  if (listen_fd < 0) {
    fprintf(stderr, "socket error %d\n", listen_fd);
    return listen_fd;
  }
  unlink(argv[1]);
  bzero(&server_addr, sizeof(server_addr));
  server_addr.sun_family = AF_UNIX;
  strncpy(server_addr.sun_path, argv[1], strlen(argv[1]));
  if (bind(listen_fd, reinterpret_cast<sockaddr *>(&server_addr),
           SUN_LEN(&server_addr)) != 0) {
    fprintf(stderr, "bind error, errno %d\n", errno);
    return -1;
  }

  sockaddr_un addr2;
  socklen_t len = sizeof(addr2);
  if (getsockname(listen_fd, reinterpret_cast<sockaddr *>(&addr2), &len) != 0) {
    fprintf(stderr, "getsockname error, errno %d\n", errno);
    return -1;
  }
  printf("bound name = %s, returned len = %d\n", addr2.sun_path, len);

  if (listen(listen_fd, 1024) != 0) {
    fprintf(stderr, "listen error, errno %d\n", errno);
    return -1;
  }

  socklen_t clilen;
  sockaddr_un cliaddr;
  int connfd;
  for (;;) {
    clilen = sizeof(cliaddr);
    if ((connfd = accept(listen_fd, reinterpret_cast<sockaddr *>(&cliaddr),
                         &clilen)) < 0) {
      if (errno == EINTR) {
        fprintf(stdout, strerror(errno));
        fprintf(stdout, " continue accepting\n");
        continue;
      } else {
        fprintf(stderr, "accept error\n");
        return -1;
      }
    }
    pid_t child_pid;
    if ((child_pid = fork()) == 0) {
      if (close(listen_fd) == -1) {
        fprintf(stderr, "close error, errno: %d(%s)\n", errno, strerror(errno));
        return -1;
      }
      while (1) {
        char ch;
        read(connfd, &ch, 1);
        printf("\nServer: I recieved %c from client!\n", ch);
        ch++;
        write(connfd, &ch, 1);
      }
      close(connfd);
      exit(0);
    } else if (child_pid == -1) {
      fprintf(stderr, "fork error, errno: %d(%s)\n", errno, strerror(errno));
      return -1;
    }
    if (close(connfd) == -1) {
      fprintf(stderr, "close error, errno: %d(%s)\n", errno, strerror(errno));
      return -1;
    }
  }
  return 0;
}
