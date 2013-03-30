#include "sync.h"

#include <stdlib.h>

#include "globals.h"

int compara_tempo(int *i, int*j){
  return tempo_corrido[*i] - tempo_corrido[*j];
}

void sync(){
  int i;
  int *lista_atletas, *ordem_atletas;
  for (i = 1; i < NUM_ETAPAS; i++){
    for(j = 0; j < NUM_ATLETAS; j++){
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
}
