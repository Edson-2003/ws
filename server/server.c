#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>

#include <sys/socket.h>
#include <netinet/in.h>


#include "server.h"

struct client 
{
  struct client *next;
  struct client *prev;
  int fd;
  char buffer[MAX];
};

struct list
{
  struct client *head;
};

struct server
{
  struct list *clients;
  int socket;
  struct sockaddr_in *s_address;
};


static struct server *server = NULL

static pthread_rwlock_t rw = PTHREAD_RWLOCK_INITIALIZER;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int
start_S()
{
  pthread_mutex_lock(&mutex);
  pthread_rwlock_wrlock(&rw);
  pthread_mutex_unlock(&mutex);
  if(server == NULL)
  {
    printf("creating and start the server ...\n");
    int s_sock;
    s_sock = socket(AF_INET, SOCK_STREAM, 0);
    
    if(s_sock < 0) exit(EXIT_FAILURE);
    
    struct sockaddr_in s_address;
    s_address.sin_family = AF_INET;
    s_address.sin_port = htons(PORT);
    s_address.sin_addr.s_addr = INADDR_ANY;
    
    if(bind(s_sock, (struct sockaddr*) &s_address, sizeof(s_address)) < 0) exit(EXIT_FAILURE);
    if(listen(s_sock, BACKLOG) < 0) exit(EXIT_FAILURE);


    server = (struct server *) malloc(sizeof(struct server));
    server->socket = s_sock;
    server->s_address = &s_address;
    server->clients = (struct list *) malloc(sizeof(struct list));
    printf("the server is created and running, avalible to connect... \n");
    
    pthread_rwlock_unlock(&rw);
    return 0;
  }
  pthread_rwlock_unlock(&rw);
  return -1;
  }

