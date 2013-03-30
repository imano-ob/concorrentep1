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
  ordem_atletas  = malloc(num_atletas * sizeof *ordem_atletas);
  for (i = 1; i < NUM_ETAPAS; i++){
    for(j = 0; j < num_atletas; j++){
      switch(i){
      case ETAPA_T1: 
        lista_atletas = PortalT1Ent; break;
      case ETAPA_CICLISMO:
        lista_atletas = PortalT1Sai; break;
      case ETAPA_T2:
        lista_atletas = PortalT2Ent; break;
      case ETAPA_CORRIDA:
        lista_atletas = PortalT2Sai; break;
      default: break;
      }
      while(!lista_atletas[j])
        sleep(1);
      ordem_atletas[j] = j;   
    }
    qsort(ordem_atletas, num_atletas, sizeof(int), compara_tempo);
    for (j = 1; j < num_atletas; j++)
      if (tempo_corrido[ordem_atletas[j]] == tempo_corrido[ordem_atletas[j - 1]])
        tempo_corrido[ordem_atletas[j]] += 3;
    go[i] = 1;
  }
  while(!done[j])
    sleep(1);
  todos_done = 1;
  return NULL;
}
