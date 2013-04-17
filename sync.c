#include "sync.h"

#include <stdlib.h>
#include <unistd.h>

#include "globals.h"

void *sincroniza(void *arg){
  int i;
  while(!todos_done){
    for(i = 0; i < num_atletas; i++)
      if(!done[i])
	sem_wait(&arrive[i]);
    for(i = 0; i < num_atletas; i++)
      if(!done[i])
	sem_post(&libera[i]);
  }
  return NULL;
}
