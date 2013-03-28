#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_t *atleta;
pthread_t classificacao;
int *PortalT1Ent, *PortalT1Sai, *PortalT2Ent, *PortalT2Sai, *estrada[180];

const int cat_homem_pro = 0;
const int cat_mulher_pro = 1;
const int cat_homem_amador = 2;
const int cat_mulher_amadora = 3;

const int etapa_natacao = 0;
const int etapa_T1 = 1;
const int etapa_ciclismo = 2;
const int etapa_T2 = 3;
const int etapa_corrida = 4;

const int ciclismo_subida = 0;
const int ciclismo_plano = 1;
const int ciclismo_descida = 2;

int **posicao_atleta;

typedef struct{
  int min[4], max[4];
}velocidades;

velocidades *velocidades_etapa[5];

int num_atletas;
int homens_pro, mulheres_pro, homens_amadores, mulheres_amadoras;

/*Funcoes para as threads*/

void correr(void *arg){
  int categoria;
  categoria = (int *)*arg;
  int etapa_atual = 0;
  int distancia_percorrida = 0;
  int tempo_atual = 0;
  int done = 0;
  int velocidade_atual;
  velocidades velocidades_ref;
  while(!done){
    while( distancia_percorrida < distancia_etapa[etapa_atual]){
      if (etapa_atual == etapa_ciclismo){
	terreno_atual = 1; /*TODO: Verificar se subida, descida ou plano*/
	velocidades_ref = velocidades_etapa[etapa_ciclismo][terreno_atual];
      }
      else
	velocidades_ref = velocidades_etapa[etapa_atual][0];
      /*velocidade atual = random entre min e max*/
      distancia_percorrida += /*something*/ 100;
      tempo_atual += velocidade_atual /*mudar esse nome?*/
      if (/*Time elapsed since last announce > meia hora(ou minuto em debug)*/ 1){
        /*Calcula onde tava na meia hora*/
        /*Await poder anunciar*/
        /*Anuncia*/
      }
    }
    etapa_atual++;
    if( etapa_atual <= num_etapas )
    /*Sync*/
    /*Await go*/
  }
}

void anunciar(void *args){
  int i;
  while (/*prova nao termina*/ 1){
    for (i = 0; i < num_atletas; i++){
      /*Await ter um numero anunciado*/
      /*Guarda esse numero no vetor da categoria*/
      /*Zera aquele numero*/
    }
    for(i = 0; i < num_categorias; i++){
      /*sort no vetor*/
      /*anuncia top 3 ou top everyone no debug*/
    }
  }
}

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
  int i, atletas_inicializados = 0;
  /*Readfiles*/
  /*Inicializar coisas*/
  if(pthread_create(classificacao), NULL, &anunciar, NULL){
    fprintf(stderr, "Erro ao criar thread da classificacao\n");
    exit(EXIT_FAILURE);
  }
  for (i = 0; i < homens_pro; i++){
    if(pthread_create(atleta[atletas_inicalizados], NULL, correr, &cat_homem_pro)){
      fprintf(stderr, "Erro ao criar thread do atleta\n");
      exit(EXIT_FAILURE);
    }
    atletas_inicializados++;
  }
  for (i = 0; i < mulheres_pro; i++){
    if(pthread_create(atleta[atletas_inicalizados], NULL, correr, &cat_mulher_pro)){
      fprintf(stderr, "Erro ao criar thread do atleta\n");
      exit(EXIT_FAILURE);
    }
    atletas_inicializados++;
  }
    for (i = 0; i < homens_amadores; i++){
      if(pthread_create(atleta[atletas_inicalizados], NULL, correr, &cat_homem_amador)){
      fprintf(stderr, "Erro ao criar thread do atleta\n");
      exit(EXIT_FAILURE);
    }
    atletas_inicializados++;
  }
  for (i = 0; i < mulheres_amadoras; i++){
    if(pthread_create(atleta[atletas_inicalizados], NULL, correr, &cat_mulher_amadora)){
      fprintf(stderr, "Erro ao criar thread do atleta\n");
      exit(EXIT_FAILURE);
    }
    atletas_inicializados++;
  }
  /*Wait...*/
}
