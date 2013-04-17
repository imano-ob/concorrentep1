#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#include "classificacao.h"
#include "atleta.h"
#include "sync.h"
#include "globals.h"

velocidades inicializa_vels(int hp_min, int hp_max, int mp_min, int mp_max, int ha_min, int ha_max,
                           int ma_min, int ma_max){
  velocidades vel;
  vel.min[CAT_HOMEM_PRO] = hp_min;
  vel.max[CAT_HOMEM_PRO] = hp_max;
  vel.min[CAT_MULHER_PRO] = mp_min;
  vel.max[CAT_MULHER_PRO] = mp_max;
  vel.min[CAT_HOMEM_AMADOR] = ha_min;
  vel.max[CAT_HOMEM_AMADOR] = ha_max;
  vel.min[CAT_MULHER_AMADORA] = ma_min;
  vel.max[CAT_MULHER_AMADORA] = ma_max;
  return vel;
}

void readfile(char filename[50]){
  char buf[50];
  int option, terrain_type, i, j, kms;
  FILE *file;
  num_atletas = 0;
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
  fclose(file);
}

void aloca_globais(){
  int i, j;
  for (i = 0; i < NUM_CATEGORIAS; i++)
    num_atletas += participantes_categoria[i];
  for (i = 0; i < 180; i++){
    for (j = 0; j < 3; j++){
      estrada[i].atletas[j] = -1;
    }
  }
  atleta = malloc(num_atletas * sizeof *atleta);
  categoria_atleta = malloc(num_atletas * sizeof *categoria_atleta);
  done = malloc(num_atletas * sizeof *done);
  memset(done, 0, num_atletas * sizeof *done);
  tempo_corrido = malloc(num_atletas * sizeof *tempo_corrido);
  memset(tempo_corrido, 0, num_atletas * sizeof *tempo_corrido);
  em_portal = malloc(num_atletas * sizeof *em_portal);
  memset(tempo_corrido, 0, num_atletas * sizeof *em_portal);
  for (i = 0; i < NUM_ETAPAS; i++){
    distancia_percorrida[i] = malloc(num_atletas * sizeof *distancia_percorrida);
    memset(distancia_percorrida[i], 0, num_atletas * sizeof *distancia_percorrida);
    if(i == ETAPA_CICLISMO)
      velocidades_etapa[i] = malloc(3 * sizeof *velocidades_etapa[i]);
    else
      velocidades_etapa[i] = malloc(sizeof *velocidades_etapa[i]);
  }
  velocidades_etapa[ETAPA_NATACAO][0] = inicializa_vels(6000 /100, 6000 /75, 
							6000 /120, 6000 / 90, 
							6000/240, 6000/120, 
							6000/300, 6000/150);
  velocidades_etapa[ETAPA_CICLISMO][CICLISMO_PLANO] = inicializa_vels(500 / .6, 550 /.6,
								      450/.6, 500/.6,
								      300/.6, 450/.6,
								      250/.6, 400/.6);
  velocidades_etapa[ETAPA_CICLISMO][CICLISMO_SUBIDA] = inicializa_vels(300/.6, 400/.6,
								       200/.6, 300/.6,
								       120/.6, 200/.6,
								       100/.6, 200/.6);
  velocidades_etapa[ETAPA_CICLISMO][CICLISMO_DESCIDA] = inicializa_vels(800/.6, 1000/.6,
									700/.6, 900/.6,
									500/.6, 700/.6,
									500/.6, 650/.6);
  velocidades_etapa[ETAPA_CORRIDA][0] = inicializa_vels(60000/260, 60000/240, 
							60000/290, 60000/260, 
							60000/420, 60000/300, 
							60000/420, 60000/330);
  velocidades_etapa[ETAPA_T1][0] = inicializa_vels(90, 150,
						   90, 150,
						   150, 330,
						   150, 390);
  velocidades_etapa[ETAPA_T2][0] = inicializa_vels(120, 180,
						   150, 360,
						   240, 600,
						   270, 720);
  arrive = malloc(num_atletas * sizeof *arrive);
  for (i = 0; i < num_atletas; i++)
    sem_init(&arrive[i], 0 , 0);
  libera = malloc(num_atletas * sizeof *libera);
  for (i = 0; i < num_atletas; i++)
    sem_init(&libera[i], 0 , 0);
  classificacao_posicao = malloc(num_atletas * sizeof *classificacao_posicao);
  for (i = 0; i < num_atletas; i++)
    sem_init(&classificacao_posicao[i], 0 , 0);
}

int main(int argc, char **argv){
  int i, j, id_atleta = 0;
  info_atleta info;
  char file[50];
  void **retval;
  if (!strcmp("-debug", argv[1]))
    strncpy(file, argv[2], 50);
  else
    strncpy(file, argv[1], 50);
  tempo_anuncio = 30;
  readfile(file);
  aloca_globais();
  /*mais init*/ 
  srand(time(NULL));
  todos_done = 0;
  retval = malloc(sizeof *retval);
  distancia_etapa[ETAPA_NATACAO] = 3800;
  distancia_etapa[ETAPA_T1] = 0;
  distancia_etapa[ETAPA_CICLISMO] = 180000;
  distancia_etapa[ETAPA_T2] = 0;
  distancia_etapa[ETAPA_CORRIDA] = 42000;
  sem_init(&pt1e, 0, 1);
  sem_init(&pt1s, 0, 1);
  sem_init(&pt2e, 0, 1);
  sem_init(&pt2s, 0, 1);
  for(i = 0; i < 180; i++)
    sem_init(&mutex_estrada[i], 0, 1);
  sem_init(&init, 0, 0);
  if(pthread_create(&classificacao, NULL, &anunciar, NULL)){
    fprintf(stderr, "Erro ao criar thread da classificacao\n");
    exit(EXIT_FAILURE);
  }
  for (i = 0; i < NUM_CATEGORIAS; i++){
    for (j = 0; j < participantes_categoria[i]; j++){
      info.categoria = i;
      info.id = id_atleta;
      if(pthread_create(&atleta[id_atleta], NULL, &correr, &info)){
	fprintf(stderr, "Erro ao criar thread do atleta\n");
	exit(EXIT_FAILURE);
      }
      sem_wait(&init);
      id_atleta++;
    }
  }
  if(pthread_create(&sync_thread, NULL, &sincroniza, NULL)){
    fprintf(stderr, "Erro ao criar thread de sincronizacao\n");
    exit(EXIT_FAILURE);
  }
  /*anuncia?*/
  pthread_join(sync_thread, retval);
  pthread_join(classificacao, retval);
  for(i = 0; i < num_atletas; i++)
    pthread_join(atleta[i], retval);
  return 0;
}
