#include "sync.h"

#include <stdlib.h>
#include <unistd.h>

#include "globals.h"

static int compara_tempo(const void *i, const void *j){
  int k, l;
  k =  * (int *)i;
  l =  * (int *)j;
  return tempo_corrido[k] - tempo_corrido[l];
}

void *sincroniza(void *arg){
  int i, j;
  int *lista_atletas, *ordem_atletas;
  return NULL;
}
