#include "classificacao.h"

#include <stdlib.h>
#include <stdio.h>

#include "globals.h"
#include "queue.h"

typedef struct{
  int distancia;
  int id;
}cur_atleta_info;


/*Funcao de comparacao pro qsort*/
int compare_info(cur_atleta_info *atleta1, cur_atleta_info *atleta2){
  return *atleta2.distancia - *atleta1.distancia;
}

void anunciar(void *args){
  int i, categoria, cur_local_id[NUM_CATEGORIAS];
  cur_atleta_info *info[NUM_CATEGORIAS];
  for(i = 0; i < NUM_CATEGORIAS; i++)
    info = malloc(participantes_categoria[i] * sizeof (*info));
  while (!todos_done){
    for(i = 0; i < NUM_CATEGORIAS; i++)
      cur_local_id[i] = 0;
    for (i = 0; i < num_atletas; i++){
      while(queueEmpty(anuncios_posicao[i]))
        sleep(1);
      categoria = categoria_atleta[i];
      info[categoria][cur_local_id[categoria]].distancia =
        queueTake(anuncios_posicao[i]);
      info[categoria][cur_local_id[categoria]].id = i;
      cur_local_id[categoria] += 1;
    }
    for(i = 0; i < NUM_CATEGORIAS; i++){
      qsort((void*)info[i], participantes_categoria[categoria], sizeof(cur_atleta_info), compare_info);
      fprint(stdout, "%s :\n\n 1 %d\n2 %d\n3 %d\n\n", "Categoria", info[0].id, info[1].id, info[2].id);
      /*anuncia top 3 ou top everyone no debug*/
    }
  }
}
