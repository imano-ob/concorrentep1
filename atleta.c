#include "atleta.h"

#include <stdlib.h>
#include <unistd.h>

#include "queue.h"
#include "globals.h"

void natacao(int id){
  double vel_dif, vel_min, vel_max, vel, vel_var, distancia_ultima_mudanca = 0;
  const double distancia_mudanca = 100;
  int categoria;
  velocidades vel_ref;
  categoria = categoria_atleta[id];
  vel_ref = velocidades_etapa[ETAPA_NATACAO][0];
  vel_min = vel_ref.min[categoria];
  vel_max = vel_ref.max[categoria];
  vel_var = ((double)rand())/RAND_MAX;
  vel = vel_min + vel_var;
  /*vel em metros/min */
  while(distancia_percorrida[ETAPA_NATACAO][id] < distancia_etapa[ETAPA_NATACAO]){
    if (distancia_ultima_mudanca + vel >= distancia_mudanca){
      /*calcula quanto tempo demora para mudar*/
      vel_var = ((double)rand())/RAND_MAX;
      vel = vel_min + vel_var;
      distancia_ultima_mudanca = 0;
    }
    tempo_corrido[id] += 60;
    if (tempo_corrido[id] % (tempo_anuncio * 60) == 0){
      /*anuncia*/
    }
    distancia_percorrida[ETAPA_NATACAO][id] += vel;
  }
}

void *correr(void *arg){
  int id;
  info_atleta *info;
  info = (info_atleta *)arg;
  id = info->id;
  categoria_atleta[id] = info->categoria;
  /*V(sem)*/
  initialized = 1;
  natacao(id);
  // transicao(id, 1);
  //ciclismo(id);
  //transicao(id, 2);
  //corrida(id);
  done[id] = 1;
  return NULL;
}

/*
  while(!done[id]){
    while( dist_etapa < distancia_etapa[etapa_atual] ||
	   etapa_atual == ETAPA_T1 || 
	   etapa_atual == ETAPA_T2){
      if (etapa_atual == ETAPA_CICLISMO){
        km_ant = km_atual;
        km_atual = dist_etapa/1000;
	terreno_atual = estrada[km_atual].terreno;
	vel_ref = velocidades_etapa[ETAPA_CICLISMO][terreno_atual];
      }
      else
	vel_ref = velocidades_etapa[etapa_atual][0];
      random_variance = (float)rand()/RAND_MAX;
      vel_dif = vel_ref.max[categoria_atleta[id]] - vel_ref.min[categoria_atleta[id]];
      vel_atual = vel_ref.min[categoria_atleta[id]] + (int)(vel_dif * random_variance);
      dist = (etapa_atual == ETAPA_CICLISMO ? 1000: (etapa_atual == ETAPA_T1 || 
						     etapa_atual == ETAPA_T2)? 0: 100); 
      tempo_corrido[id] += vel_atual;
      while (tempo_corrido[id] >= ultimo_anuncio + 1800){
       	vel = (float)dist/(float)vel_atual;
	dist_anuncio = distancia_percorrida[id] + (int)(vel * (ultimo_anuncio + 1800));
	while(queueFull(anuncios_posicao[id]))
          sleep(1);
        queuePut(anuncios_posicao[id], dist_anuncio);
	ultimo_anuncio += 1800;
      }
      dist_etapa += dist;
      distancia_percorrida[id] += dist;
      if(etapa_atual == ETAPA_CORRIDA && km_ant < km_atual){
        estrada[km_ant].atletas[id] = 0;
        estrada[km_atual].atletas[id] = 1;
      }
    }
    etapa_atual++;
    if( etapa_atual < NUM_ETAPAS ){
      dist_etapa = 0;
      switch(etapa_atual){
      case ETAPA_T1: 
        PortalT1Ent[id] = 1; break;
      case ETAPA_CICLISMO:
        PortalT1Sai[id] = 1; break;
      case ETAPA_T2:
        PortalT2Ent[id] = 1; break;
      case ETAPA_CORRIDA:
        PortalT2Sai[id] = 1; break;
      default:
        break;
      } 
      while(!go[etapa_atual])
        sleep(1);
    }
    else
  */

