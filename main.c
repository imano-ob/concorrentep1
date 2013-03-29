#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "globals.h"

velocidades inicaliza_vels(int hp_min, int hp_max, int mp_min, int mp_max, int ha_min, int ha_max,
                           int ma_min, int ma_max){
  velocidades vel;
  vel.min[cat_homem_pro] = hp_min;
  vel.max[cat_homem_pro] = hp_max;
  vel.min[cat_mulher_pro] = mp_min;
  vel.max[cat_mulher_pro] = mp_max;
  vel.min[cat_homem_amador] = ha_min;
  vel.max[cat_homem_amador] = ha_max;
  vel.min[cat_mulher_amadora] = ma_min;
  vel.max[cat_mulher_amadora] = ma_max;
  return vel;
}

int main(int argc, char **argv){
  int i, j, id_atleta = 0;
  info_atleta info;
  /*Readfiles*/
  /*Inicializar coisas*/
  srand(time(NULL));
  if(pthread_create(classificacao), NULL, &anunciar, NULL){
    fprintf(stderr, "Erro ao criar thread da classificacao\n");
    exit(EXIT_FAILURE);
  }
  for (i = 0; i < NUM_CATEGORIAS; i++){
    for (j = 0; j < participantes_categoria[i]; j++){
      initialized = 0;
      tmpname.categoria = i;
      tmpname.id = id_atleta;
      if(pthread_create(atleta[id_atleta], NULL, &correr, &tmpname)){
	fprintf(stderr, "Erro ao criar thread do atleta\n");
	exit(EXIT_FAILURE);
      }
      while (!initialized) 
	sleep(1);
      id_atleta++;
    }
  }
  if(pthread_create(sync_thread, NULL, &sync, NULL)){
    fprintf(stderr, "Erro ao criar thread de sincronizacao\n");
    exit(EXIT_FAILURE);
  }    
  /*Wait...*/
}
