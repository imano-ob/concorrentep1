#include "globals.h"

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
  /*init*/
  while (!todos_done){
    for(i = 0; i < NUM_CATEGORIAS; i++)
      cur_local_id[i] = 0;
    for (i = 0; i < num_atletas; i++){
      while(isEmpty(queue[i]))
        sleep(1);
      categoria = categoria_atleta[i];
      info[categoria][cur_local_id[categoria]].distancia =
        distancia_percorrida[i];
      info[categoria][cur_local_id[categoria]].id = i;
      cur_local_id[categoria] += 1;
    }
    for(i = 0; i < NUM_CATEGORIAS; i++){
      qsort((void*)info, participantes_categoria[categoria], sizeof(cur_atleta_info), compare_info);
      /*anuncia top 3 ou top everyone no debug*/
    }
  }
}
