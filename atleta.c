#include "globals.h"

void correr(void *arg){
  int categoria;
  int id;
  tmpname2 *tmpname3;
  int etapa_atual = 0;
  int distancia_percorrida = 0;
  int tempo_atual = 0;
  int ultimo_anuncio = 0;
  //  int done = 0;
  int vel_atual;
  velocidades velocidades_ref;
  while(!done[i]){
    while( distancia_percorrida < distancia_etapa[etapa_atual]){
      if (etapa_atual == etapa_ciclismo){
	terreno_atual = 1; /*TODO: Verificar se subida, descida ou plano*/
	vel_ref = velocidades_etapa[etapa_ciclismo][terreno_atual];
      }
      else
	vel_ref = velocidades_etapa[etapa_atual][0];
      random_variance = (float)rand()/RAND_MAX;
      vel_dif = vel_ref.max[categoria] = vel_ref.max[categoria];
      vel_atual = vel_ref.min[categoria] + (int)(vel_dif * random_variance);
      dist = (etapa_atual == etapa_ciclismo ? 1000: (etapa_atual == etapa_T1 || 
						     etapa_atual == etapa_T2)? 0: 100); 
      tempo_atual += vel_atual;
      if (tempo_atual >= ultimo_anuncio + /*30min*/ 1800){
       	vel = (float)dist/(float)vel_atual;
	dist_anuncio = distancia_percorrida + (int)(vel * (ultimo_anuncio + 1800));
	/*Await poder anunciar*/
        /*Anuncia*/
      }
      distancia_percorria += dist;
      /*TODO: Atualizar posicao na estrada se for ciclismo*/
    }
    etapa_atual++;
    /*Toda transicao tem que syncar*/
    if( etapa_atual < num_etapas ){
      /*Sync*/
      /*Await go*/
    }
    else
      done[i] = 1;
  }
  /*Anuncia terminado*/
}
