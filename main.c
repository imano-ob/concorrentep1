#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_t *atletas;
pthread_t anunciador;
int *PortalT1Ent, *PortalT1Sai, *PortalT2Ent, *PortalT2Sai, *estrada[180];

typedef struct{
  int velmin_nado;
  int velmax_nado;
  int velmin_corrida;
  int velmax_corrida;
  int velmin_descida_ciclismo;
  int velmax_descida_ciclismo;
  int velmin_plano_ciclismo;
  int velmax_plano_ciclismo;
  int velmin_subida_ciclismo;
  int velmax_subida_ciclismo;
}velocidades;

void correr(void *args){
  velocidades *vels;
  vels = (velocidades *)args;
  /*do stuff*/
}

void anunciar(void *args){
  /*do stuff*/
}

int main(int argc, char **argv){
  int i, homens_pro, mulheres_pro, homens_amadores, mulheres_amadoras, atletas_inicializados = 0;
  /*Readfiles*/
  /*Inicializar coisas*/
  if(pthread_create(anunciador), NULL, &anunciar, NULL){
    fprintf(stderr, "Erro ao criar thread do anunciador\n");
    exit(EXIT_FAILURE);
  }
  for (i = 0; i < homens_pro; i++){
    if(pthread_create(atletas[atletas_inicalizados], NULL, correr, vels_homem_pro)){
      fprintf(stderr, "Erro ao criar thread do atleta\n");
      exit(EXIT_FAILURE);
    }
    atletas_inicializados++;
  }
  for (i = 0; i < mulheres_pro; i++){
    if(pthread_create(atletas[atletas_inicalizados], NULL, correr, vels_mulher_pro)){
      fprintf(stderr, "Erro ao criar thread do atleta\n");
      exit(EXIT_FAILURE);
    }
    atletas_inicializados++;
  }
    for (i = 0; i < homens_amadores; i++){
      if(pthread_create(atletas[atletas_inicalizados], NULL, correr, vels_homem_amador)){
      fprintf(stderr, "Erro ao criar thread do atleta\n");
      exit(EXIT_FAILURE);
    }
    atletas_inicializados++;
  }
  for (i = 0; i < mulheres_amadoras; i++){
    if(pthread_create(atletas[atletas_inicalizados], NULL, correr, vels_mulher_amadora)){
      fprintf(stderr, "Erro ao criar thread do atleta\n");
      exit(EXIT_FAILURE);
    }
    atletas_inicializados++;
  }
}
