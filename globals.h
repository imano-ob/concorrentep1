#ifndef __GLOBALS__
#define __GLOBALS__

#include <pthread.h>
#include <semaphore.h>

#include "queue.h"

#define CAT_HOMEM_PRO 0
#define CAT_MULHER_PRO 1
#define CAT_HOMEM_AMADOR 2
#define CAT_MULHER_AMADORA 3

#define NUM_CATEGORIAS 4

#define ETAPA_NATACAO 0
#define ETAPA_T1 1
#define ETAPA_CICLISMO 2
#define ETAPA_T2 3
#define ETAPA_CORRIDA 4

#define NUM_ETAPAS 5

#define CICLISMO_SUBIDA 0
#define CICLISMO_PLANO 1
#define CICLISMO_DESCIDA 2

typedef struct{
  int min[NUM_CATEGORIAS], max[NUM_CATEGORIAS];
}velocidades;

typedef struct{
  int categoria;
  int id;
}info_atleta;

typedef struct{
  int terreno;
  int atletas[3];
}km_estrada;


typedef struct portalnode *portal; 

struct portalnode{
  int id;
  int tempo;
  portal next;
};


pthread_t *atleta;
pthread_t classificacao;
pthread_t sync_thread;
sem_t *arrive;
sem_t *libera;
portal PortalT1Ent, PortalT1Sai, PortalT2Ent, PortalT2Sai;
sem_t pt1e, pt1s, pt2e, pt2s;
km_estrada estrada[180];
sem_t mutex_estrada[180];

sem_t *classificacao_posicao;

int *categoria_atleta;
int todos_done;

int *em_portal;

int distancia_etapa[NUM_ETAPAS];

int *tempo_corrido;
int *distancia_percorrida[NUM_ETAPAS];
int *etapa_atual;

int tempo_anuncio;

velocidades *velocidades_etapa[NUM_ETAPAS];

int num_atletas;
int participantes_categoria[NUM_CATEGORIAS];

int *done;

sem_t init;

#endif /*__GLOBALS__*/
