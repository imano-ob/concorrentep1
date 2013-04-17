#include "atleta.h"

#include <stdlib.h>
#include <unistd.h>

#include "queue.h"
#include "globals.h"

void sync_atleta(const int id){
  portal P, tmp, aux;
  sem_t *lock;
  int tempo_no_portal;
  sem_post(&arrive[id]);
  sem_wait(&libera[id]);
  if (em_portal[id]){
    switch(em_portal[id]){
    case(1):
      P = PortalT1Ent; lock = &pt1e; break;
    case(2):
      P = PortalT2Ent; lock = &pt2e; break;
    case(3):
      P = PortalT1Sai; lock = &pt1s; break;
    case(4):
      P = PortalT2Sai; lock = &pt2s; break;
    }
    sem_wait(lock);
    for(tmp = P; tmp->next != NULL; tmp=tmp->next)
      if(tmp->next->id == id){
	tempo_no_portal = tmp->next->tempo;
	aux = tmp->next;
	tmp->next = tmp->next->next;
	free(aux);
	break;
      }
    for(tmp = P; tmp->next != NULL; tmp=tmp->next)
      if(tmp->next->tempo == tempo_no_portal)
	tempo_corrido[id] += 3;
    sem_post(lock);
    em_portal[id] = 0;
  }
}

void anuncia(const int id){
  sem_post(&classificacao_posicao[id]);
}

int nat_cor(const int id, const int etapa, int minutos_anuncio){
  double vel, vel_var, distancia_ultima_mudanca = 0;
  const double distancia_mudanca = etapa == ETAPA_NATACAO? 100.0: 1000.0;
  const int categoria = categoria_atleta[id];
  int segundos_resto, segundos_calc;
  const velocidades vel_ref = velocidades_etapa[etapa][0];
  const double vel_min = vel_ref.min[categoria];
  const double vel_max = vel_ref.max[categoria];
  const double vel_dif = vel_max - vel_min;
  double distancia;
  vel_var = ((double)rand()) * vel_dif/RAND_MAX;
  vel = vel_min + vel_var;
  /*vel em metros/min */
  if((segundos_resto = tempo_corrido[id] % 60)){
    segundos_calc = 60 - segundos_resto;
    distancia = ((double)segundos_calc / 60.0) * vel;
    distancia_percorrida[etapa][id] += distancia;
    tempo_corrido += segundos_calc;
    minutos_anuncio++;
    if (minutos_anuncio == tempo_anuncio){
      anuncia(id);
      minutos_anuncio = 0;
    }
    sync_atleta(id);
  }
  while(distancia_percorrida[etapa][id] < distancia_etapa[etapa]){
    distancia = vel;
    if (distancia_ultima_mudanca + distancia >= distancia_mudanca){
      segundos_resto = (distancia_mudanca - distancia_ultima_mudanca) / vel;
      segundos_calc = 60 - segundos_resto;
      distancia_percorrida[etapa][id] = distancia_mudanca - distancia_ultima_mudanca;
      vel_var = ((double)rand()) * vel_dif/RAND_MAX;
      vel = vel_min + vel_var;
      distancia = vel * (double)segundos_calc / 60.0;
      distancia_ultima_mudanca = 0;
    }
    if(distancia_percorrida[etapa][id] >= distancia_etapa[etapa]){
      tempo_corrido[id] += segundos_resto;
    }
    else{
      tempo_corrido[id] += 60;
      minutos_anuncio++;
	if (minutos_anuncio == tempo_anuncio){
	  anuncia(id);
	  minutos_anuncio = 0;
	}
      distancia_ultima_mudanca += distancia;
      distancia_percorrida[etapa][id] += distancia;
      sync_atleta(id);
    }
  }
  return minutos_anuncio;
}

int natacao(const int id, int minutos_anuncio){
  return nat_cor(id, ETAPA_NATACAO, minutos_anuncio);
}

int corrida(const int id, int minutos_anuncio){
  return nat_cor(id, ETAPA_CORRIDA, minutos_anuncio);
}

int tem_espaco(int pos){
  if(estrada[pos].atletas[0] == -1 || estrada[pos].atletas[1] == -1 || estrada[pos].atletas[2] == -1)
    return 1;
  else
    return 0;
}

int ciclismo(const int id, int minutos_anuncio){
  double vel_dif, vel_min, vel_max, vel, vel_var, dist, dist_parcial;
  const int categoria = categoria_atleta[id];
  int segundos_resto, segundos_calc, km_atual = 0, km_prox, entrou = 0, resto_km;
  velocidades vel_ref;
  const int etapa = ETAPA_CICLISMO;
  segundos_calc = 60 - (tempo_corrido[id] % 60);
  while(distancia_percorrida[etapa][id] < distancia_etapa[etapa]){
    vel_ref = velocidades_etapa[etapa][estrada[km_atual].terreno];
    vel_min = vel_ref.min[categoria];
    vel_max = vel_ref.max[categoria];
    vel_dif = vel_max - vel_min;
    vel_var = ((double)rand()) * vel_dif/RAND_MAX;
    vel = vel_min + vel_var;
    dist = ((double)segundos_calc/60.0) * vel;
    while (dist > 0){
      resto_km = entrou? (1000 - ((distancia_percorrida[etapa][id] + 1) % 1000)) : 0;
      dist_parcial = resto_km > dist? dist:dist_parcial;
      distancia_percorrida[etapa][id] += dist_parcial;
      dist -= dist_parcial;
      segundos_resto = dist_parcial / (vel/60);
      segundos_calc -= segundos_resto;
      tempo_corrido[id] += segundos_resto;
      /*calcula tempo gasto - pode ser 0*/
      if (km_atual == 179 && dist >= 1){
	tempo_corrido[id] += vel/60;
	distancia_percorrida[etapa][id] = distancia_etapa[etapa];
	continue;
      }
      km_prox = entrou?km_atual + 1 : 0;
      sem_wait(&mutex_estrada[km_prox]);
      if (tem_espaco(km_prox) && dist > 0){
      	if(entrou){
	  sem_wait(&mutex_estrada[km_atual]);
	  if(estrada[km_atual].atletas[0] == id)
	    estrada[km_atual].atletas[0] = -1;
	  else if (estrada[km_atual].atletas[1] == id)
	    estrada[km_atual].atletas[1] = -1;
	  else if (estrada[km_atual].atletas[2] == id)
	    estrada[km_atual].atletas[2] = -1;
	}
	sem_post(&mutex_estrada[km_atual]);
	km_atual = km_prox;
	if(estrada[km_atual].atletas[0] == -1)
	  estrada[km_atual].atletas[0] = id;
	else if (estrada[km_atual].atletas[1] == -1)
	  estrada[km_atual].atletas[1] = id;
	else if (estrada[km_atual].atletas[2] == -1)
	  estrada[km_atual].atletas[2] = id;
	sem_post(&mutex_estrada[km_atual]);
	entrou = 1;vel_ref = velocidades_etapa[etapa][estrada[km_atual].terreno];
	vel_min = vel_ref.min[categoria];
	vel_max = vel_ref.max[categoria];
	vel_dif = vel_max - vel_min;
	vel_var = ((double)rand()) * vel_dif/RAND_MAX;
	vel = vel_min + vel_var;
	dist = ((double)segundos_calc/60.0) * vel;
      }
      else{
	sem_post(&mutex_estrada[km_prox]);
        dist = 0;
	tempo_corrido[id] += segundos_calc;
      }
    }
    sync_atleta(id);
    if(minutos_anuncio == tempo_anuncio){
      anuncia(id);
      minutos_anuncio = 0;
    }
    segundos_calc = 60;
  }
  return minutos_anuncio;
}

int transicao(const int id, const int portal_id, int minutos_anuncio){
  sem_t *lock;
  int tempo_transicao, tempo_espera, etapa;
  portal P, tmp;
  switch(portal_id){
  case(0):
    P = PortalT1Ent; lock = &pt1e; etapa = ETAPA_T1; break;
  case(1):
    P = PortalT2Ent; lock = &pt2e; etapa = ETAPA_T2; break;
  }
  sem_wait(lock);
  tmp = P->next;
  P->next = malloc(sizeof *(P->next));
  P->next->id = id;
  P->next->tempo = tempo_corrido[id];
  P->next->next = tmp;
  em_portal[id] = portal_id+1;
  sem_post(lock);
  tempo_transicao = ((double)rand()/RAND_MAX) * (velocidades_etapa[etapa][0].max[categoria_atleta[id]] -
						 velocidades_etapa[etapa][0].min[categoria_atleta[id]]) +
    velocidades_etapa[etapa][0].min[categoria_atleta[id]];

  while(tempo_transicao > 0){
    tempo_espera = 60 - (tempo_corrido[id] % 60);
    if(tempo_transicao >= tempo_espera){
      tempo_corrido[id] += tempo_espera;
      tempo_transicao -= tempo_espera;
      sync_atleta(id);
      minutos_anuncio++;
      if(minutos_anuncio == tempo_anuncio){
	anuncia(id);
	minutos_anuncio = 0;
      }
    }
    else{
      tempo_corrido[id] += tempo_transicao;
      tempo_transicao = 0;
    }
  }
  switch(portal_id){
  case(0):
    P = PortalT1Sai; lock = &pt1s; break;
  case(1):
    P = PortalT2Sai; lock = &pt2s; break;
  }
  sem_wait(lock);
  tmp = P->next;
  P->next = malloc(sizeof *(P->next));
  P->next->id = id;
  P->next->tempo = tempo_corrido[id];
  P->next->next = tmp;
  em_portal[id] = portal_id+3;
  sem_post(lock);
  return minutos_anuncio;
}


void *correr(void *arg){
  int id;
  info_atleta *info;
  int minutos_anuncio = 0;
  info = (info_atleta *)arg;
  id = info->id;
  categoria_atleta[id] = info->categoria;
  sem_post(&init);
  minutos_anuncio = natacao(id, minutos_anuncio);
  minutos_anuncio = transicao(id, 1, minutos_anuncio);
  minutos_anuncio = ciclismo(id, minutos_anuncio);
  minutos_anuncio = transicao(id, 2, minutos_anuncio);
  minutos_anuncio = corrida(id, minutos_anuncio);
  done[id] = 1;
  return NULL;
}
