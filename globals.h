#ifndef __GLOBALS__
#define __GLOBALS__

#define CAT_HOMEM_PRO 0;
#define CAT_MULHER_PRO 1;
#define CAT_HOMEM_AMADOR 2;
#define CAT_MULHER_AMADORA 3;

#define NUM_CATEGORIAS 4

#define ETAPA_NATACAO 0;
#define ETAPA_T1 1;
#define ETAPA_CICLISMO 2;
#define ETAPA_T2 3;
#define ETAPA_CORRIDA 4;

#define NUM_ETAPAS 5;

#define CICLISMO_SUBIDA 0;
#define CICLISMO_PLANO 1;
#define CICLISMO_DESCIDA 2;

typedef struct{
  int min[4], max[4];
}velocidades;

typedef struct{
    int categoria;
    int id;
}tmpname2;

pthread_t *atleta;
pthread_t classificacao;
int *PortalT1Ent, *PortalT1Sai, *PortalT2Ent, *PortalT2Sai, *estrada[180];

int **posicao_atleta;

velocidades *velocidades_etapa[5];

int num_atletas;
int homens_pro, mulheres_pro, homens_amadores, mulheres_amadoras;

int initialized;

#endif /*__GLOBALS__*/
