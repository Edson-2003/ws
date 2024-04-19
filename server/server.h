#ifndef SERVER_H_
#define SERVER_H_

#define MAX 512
#define MAXSIZE MAX * sizeof(char)
#define PORT 9002
#define BACKLOG 5

struct client;
struct list;

struct server;

int start();




#endif
