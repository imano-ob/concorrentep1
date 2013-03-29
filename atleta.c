#include "globals.h"

void correr(void *arg){
  int categoria;
  int id;
  info_atleta *info;
  int etapa_atual = 0;
  int ultimo_anuncio = 0;
  int vel_atual;
  int dist_etapa = 0;
  velocidades velocidades_ref;
  tmpname3 = (tmpname *)arg;
  categoria = tmpname3->categoria;
  id = tmpname3->id;
  initialized = 1;
  while(!done[id]){
    while( distancia_percorrida[id] < distancia_etapa[etapa_atual]){
      if (etapa_atual == etapa_ciclismo){
	terreno_atual = estrada[(distancia_percorrida/1000)].terreno;
	vel_ref = velocidades_etapa[etapa_ciclismo][terreno_atual];
      }
      else
	vel_ref = velocidades_etapa[etapa_atual][0];
      random_variance = (float)rand()/RAND_MAX;
      vel_dif = vel_ref.max[categoria] - vel_ref.min[categoria];
      vel_atual = vel_ref.min[categoria] + (int)(vel_dif * random_variance);
      dist = (etapa_atual == etapa_ciclismo ? 1000: (etapa_atual == etapa_T1 || 
						     etapa_atual == etapa_T2)? 0: 100); 
      tempo_corrido[id] += vel_atual;
      while (tempo_corrido[id] >= ultimo_anuncio + 1800){
       	vel = (float)dist/(float)vel_atual;
	dist_anuncio = distancia_percorrida[id] + (int)(vel * (ultimo_anuncio + 1800));
	/*Await poder anunciar*/
        /*Anuncia*/
	ultimo_anuncio += 1800;
      }
      dist_etapa += dist;
      distancia_percorrida[id] += dist;
      /*TODO: Atualizar posicao na estrada se for ciclismo*/
    }
    etapa_atual++;
    /*Toda transicao tem que syncar*/
    if( etapa_atual < num_etapas ){
      dist_etapa = 0;
      /*Sync*/
      /*Await go*/
    }
    else
      done[id] = 1;
  }
}
