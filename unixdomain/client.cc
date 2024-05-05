// Copyright 2024 JOK Inc. All Rights Reserved.
// Author: easytojoin@163.com (jok)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

int main(int argc, char **argv) {
  int server_socket;
  struct sockaddr_un server_addr;
  int connection_result;

  char ch = 'C';

  server_socket = socket(AF_UNIX, SOCK_STREAM, 0);

  server_addr.sun_family = AF_UNIX;
  strncpy(server_addr.sun_path, argv[1], strlen(argv[1]));

  connection_result = connect(server_socket, (struct sockaddr *)&server_addr,
                              sizeof(server_addr));

  if (connection_result == -1) {
    perror("Error:");
    exit(1);
  }
  while (1) {
    write(server_socket, &ch, 1);
    read(server_socket, &ch, 1);
    printf("Client: I recieved %c from server!\n", ch);
  }
  close(server_socket);
  exit(0);
}
