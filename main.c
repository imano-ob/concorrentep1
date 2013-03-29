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

void readfiles(char filename[50]){
  char buf[50];
  int option, terrain_type, i, j, kms;
  FILE *file;
  file = fopen(filename, "r");
  fgets(buf, 50, file);
  participantes_categoria[CAT_HOMEM_PRO] = atoi(buf);
  fgets(buf, 50, file);
  participantes_categoria[CAT_MULHER_PRO] = atoi(buf);
  fgets(buf, 50, file);
  participantes_categoria[CAT_HOMEM_AMADOR] = atoi(buf);
  fgets(buf, 50, file);
  participantes_categoria[CAT_MULHER_AMADORA] = atoi(buf);
  while((option = getchar())!= EOF){
    i = 0;
    switch(option){
    case 'P':
      terrain_type = CICLISMO_PLANO; break;
    case 'S':
      terrain_type = CICLISMO_SUBIDA; break;
    case 'D':
      terrain_type = CICLISMO_DESCIDA; break;
    }
    fgets(buf, 50, file);
    kms = atoi(buf);
    j = i;
    for(; i < j + kms; i++)
      estrada[i].terreno = terrain_type;
  }
}

int main(int argc, char **argv){
  int i, j, id_atleta = 0;
  info_atleta info;
  char file[50];
  /*achar nome do arquvivo*/
  readfile(file);
  for (i = 0; i < NUM_CATEGORIAS; i++)
    num_atletas += participantes_categoria[i];
  PortalT1Ent = malloc(num_atletas * sizeof *PortalT1Ent);
  memset(PortalT1Ent, 0, num_atletas * sizeof *PortalT1Ent);
  PortalT1Sai = malloc(num_atletas * sizeof *PortalT1Sai);
  memset(PortalT1Sai, 0, num_atletas * sizeof *PortalT1Sai);
  PortalT2Ent = malloc(num_atletas * sizeof *PortalT2Ent);
  memset(PortalT2Ent, 0, num_atletas * sizeof *PortalT2Ent);
  PortalT2Sai = malloc(num_atletas * sizeof *PortalT2Sai);
  memset(PortalT2Sai, 0, num_atletas * sizeof *PortalT2Sai);
  for (i = 0; i < 180; i++){
    estrada[i].atletas = malloc(num_atletas * sizeof *(estrada[i].atletas));
    memset(estrada[i].atletas, 0, num_atletas * sizeof *(estrada[i].atletas));
  }
  atleta = malloc(num_atletas * sizeof *atleta);
  categoria_atleta = malloc(num_atletas * sizeof *categoria_atleta);
  done = malloc(num_atletas * sizeof *done);
  memset(done, 0, num_atletas * sizeof *done);
  tempo_corrido = malloc(num_atletas * sizeof *tempo_corrido);
  memset(tempo_corrido, 0, num_atletas * sizeof *tempo_corrido;
  distancia_percorrida = malloc(num_atletas * sizeof *distancia_percorrida);
  memset(distancia_percorrida, 0, num_atletas * sizeof *distancia_percorrida);
  /*mais init*/ 
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
