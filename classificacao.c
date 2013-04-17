#include "classificacao.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "globals.h"
#include "queue.h"

typedef struct{
  int distancia;
  int id;
}cur_atleta_info;


/*Funcao de comparacao pro qsort*/
static int compare_info(const void *atleta1, const void *atleta2){
  if (etapa_atual[((cur_atleta_info *)atleta2)->id] != etapa_atual[((cur_atleta_info *)atleta1)->id])
    return etapa_atual[((cur_atleta_info *)atleta2)->id] - etapa_atual[((cur_atleta_info *)atleta1)->id];
  return ((cur_atleta_info *)atleta2)->distancia - ((cur_atleta_info*)atleta1)->distancia;
}

void *anunciar(void *args){
  int i, categoria, cur_local_id[NUM_CATEGORIAS];
  cur_atleta_info *info[NUM_CATEGORIAS];
  for(i = 0; i < NUM_CATEGORIAS; i++)
    info[i] = malloc(participantes_categoria[i] * sizeof (*(info[i])));
  while (!todos_done){
    for(i = 0; i < NUM_CATEGORIAS; i++)
      cur_local_id[i] = 0;
    for (i = 0; i < num_atletas; i++){
      if(!done[i]){
	sem_wait(&classificacao_posicao);
	categoria = categoria_atleta[i];
	info[categoria][cur_local_id[categoria]].distancia =
	  distancia_percorrida[etapa_atual[i]][i];
	info[categoria][cur_local_id[categoria]].id = i;
	cur_local_id[categoria] += 1;
      }
    }
    for(i = 0; i < NUM_CATEGORIAS; i++){
      qsort((void*)info[i], participantes_categoria[categoria], sizeof(cur_atleta_info), compare_info);
      fprintf(stdout, "%s :\n\n 1 %d\n2 %d\n3 %d\n\n", "Categoria", info[i][0].id, info[i][1].id, info[i][2].id);
      /*anuncia top 3 ou top everyone no debug*/
    }
  }
  return NULL;
}
