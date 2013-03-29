#include "globals.h"

void correr(void *arg){
  int id;
  info_atleta *info;
  int etapa_atual = 0;
  int ultimo_anuncio = 0;
  int vel_atual;
  int dist_etapa = 0;
  velocidades velocidades_ref;
  int km_atual = 0, km_ant = 0;;
  tmpname3 = (tmpname *)arg;
  categoria_atleta[id] = tmpname3->categoria;
  id = tmpname3->id;
  initialized = 1;
  while(!done[id]){
    while( distancia_percorrida[id] < distancia_etapa[etapa_atual]){
      if (etapa_atual == etapa_ciclismo){
        km_ant = km_atual;
        km_atual = dist_etapa/1000;
	terreno_atual = estrada[km_atual].terreno;
	vel_ref = velocidades_etapa[etapa_ciclismo][terreno_atual];
      }
      else
	vel_ref = velocidades_etapa[etapa_atual][0];
      random_variance = (float)rand()/RAND_MAX;
      vel_dif = vel_ref.max[categoria_atleta[id]] - vel_ref.min[categoria_atleta[id]];
      vel_atual = vel_ref.min[categoria_atleta[id]] + (int)(vel_dif * random_variance);
      dist = (etapa_atual == etapa_ciclismo ? 1000: (etapa_atual == etapa_T1 || 
						     etapa_atual == etapa_T2)? 0: 100); 
      tempo_corrido[id] += vel_atual;
      while (tempo_corrido[id] >= ultimo_anuncio + 1800){
       	vel = (float)dist/(float)vel_atual;
	dist_anuncio = distancia_percorrida[id] + (int)(vel * (ultimo_anuncio + 1800));
	while(isFull(queue[id]))
          sleep(1);
        queueAdd(queue[id], dist_anuncio);
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
    /*Toda transicao tem que syncar*/
    if( etapa_atual < num_etapas ){
      dist_etapa = 0;
      switch(etapa){
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
      done[id] = 1;
  }
}
