#include <stdio.h>
#include <stdlib.h>
#include "server.h"






int
main(int *argc, char **argv)
{
  if(argc <= 0) exit(EXIT_FAILURE);
  
  if(argv[1] == start)
  {
    if(start() < 0)
    {

      printf("the server is running\n\n")
      exit(EXIT_SUCCESS);
    }
    
    printf("the server is started\n\n");
  }
  return 0;
}
