#ifndef __GLOBALS__
#define __GLOBALS__

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

const int num_etapas = 5;

const int ciclismo_subida = 0;
const int ciclismo_plano = 1;
const int ciclismo_descida = 2;

int **posicao_atleta;
/*TODO: Ver o que eu ia fazer com a linha abaixo*/
/*int **/

typedef struct{
  int min[4], max[4];
}velocidades;

typedef struct{
    int categoria;
    int id;
}tmpname2;


velocidades *velocidades_etapa[5];

int num_atletas;
int homens_pro, mulheres_pro, homens_amadores, mulheres_amadoras;

/*Funcoes para as threads*/

#endif /*__GLOBALS__*/
