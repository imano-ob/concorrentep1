#include "atleta.h"

#include <stdlib.h>
#include <unistd.h>

#include "queue.h"
#include "globals.h"


int nat_cor(int id, int etapa, int minutos_anuncio){
  double vel_dif, vel_min, vel_max, vel, vel_var, distancia_ultima_mudanca = 0;
  const double distancia_mudanca = 100.0;
  int categoria, segundos_resto, segundos_calc;
  velocidades vel_ref;
  categoria = categoria_atleta[id];
  vel_ref = velocidades_etapa[etapa][0];
  vel_min = vel_ref.min[categoria];
  vel_max = vel_ref.max[categoria];
  vel_dif = max - vel_min;
  vel_var = ((double)rand()) * vel_dif/RAND_MAX;
  vel = vel_min + vel_var;
  /*vel em metros/min */

  /*1 iteracao - arredonda*/
  if(segundos_resto = tempo_corrido % 60){
    segundos_calc = 60 - segundos_resto;
    distancia = vel * (double)segundos_calc / 60.0;
    distancia_percorrida[etapa][id] += distancia;
    tempo_corrido += segundos_calc;
    minutos_anuncio++;
    if (minutos_anuncio == tempo_anuncio){
      /*anuncia*/
      minutos_anuncio = 0;
    }
    /*sync*/
  }
  while(distancia_percorrida[etapa][id] < distancia_etapa[etapa]){
    distancia = vel;
    if (distancia_ultima_mudanca + distancia >= distancia_mudanca){
      /*calcula quanto tempo demora para mudar*/
      vel_var = ((double)rand()) * vel_dif/RAND_MAX;
      vel = vel_min + vel_var;
      distancia_ultima_mudanca = 0;
    }
    if(distancia_percorrida[etapa][id] >= distancia_etapa[etapa]){
      /*calcula quanto tempo demora*/
      distancia_percorrida[etapa][id] = distancia_etapa[etapa];
    }
    else{
      tempo_corrido[id] += 60;
      minutos_anuncio++;
	if (minutos_anuncio == tempo_anuncio){
	  /*anuncia*/
	  minutos_anuncio = 0;
	}
      distancia_ultima_mudanca += distancia;
      distancia_percorrida[etapa][id] += distancia;
      /*sync*/
    }
  }
  return minutos_anuncio;
}

int natacao(int id, int minutos_anuncio){
  return nat_cor(id, ETAPA_NATACAO, minutos_anuncio);
}

int corrida(int id, int minutos_anuncio){
  return nat_cor(id, ETAPA_CORRIDA, minutos_anuncio);
}

int tem_espaco(int pos_estrada){
  // int val_retorno;
  /*lock estrada*/
  if(estrada[pos].atleta[0] == -1 || estrada[pos].atleta[1] == -1 || estrada[pos].atleta[2] == -1)
    return 1;
  else
    return 0;
}

int ciclismo(int id, int minutos_anuncio){
  double vel_dif, vel_min, vel_max, vel, vel_var, distancia_ultima_mudanca = 0;
  const double distancia_mudanca = 1000.0;
  int categoria, segundos_resto, segundos_calc;
  velocidades vel_ref;
  /*1 iteracao*/
  /*calcula dist*/
  /*if tem espaco*/
    /*entra e corre ate completar 1min*/
    /*^Ver abaixo*/
  /*else*/
    /*enrola ate completar o minuto com sadface*/
  /*sync*/
  /*anuncia se for o caso*/
  while(/*nao termina*/){
    /*calcula dist*/
    /*while remaining dist > 0*/
      /*corre min(dist, o que falta para completar um km)*/
      /*^pode ser 0*/
      /*dist -= o que correu*/
      /*if ultimo km e sobrou dist*/
        /*gg noobs, terminei aqui*/
      /*calcula tempo gasto - pode ser 0*/
      /*if tem espaco e dist > 0 */
      /*ter espaco tem que ser visto antes porque locka a estrada*/
        /*libera anterior*/
        /*entra no novo*/
        /*unlock estrada*/
        /*recalcula dist*/
      /*else*/
        /*unlock estrada*/
        /*dist = 0*/
        /*enrola ate o proximo minuto*/
    /*else*/
      /*enrola ate o proxmo minuto*/
    /*sync*/
    /*anuncia se for o caso*/
  }
}

int transicao(int id, int portal, int minutos_anuncio){
  /*lock portal*/
  /*se insere*/
  /*seta flag*/
  /*unlock*/
  /*completa minuto*/
  /*sync*/
  /*if flag*/
    /*lock portal*/
    /*se remove*/
    /*varre*/
    /*se acha alguem com mesmo tempo*/
    /*enfia 3 segundos a mais*/
    /*unlock*/
    /*^ enfiar no sync, infelizmente*/
  /*enrola*/
  /*lock portal*/
  /*se insere*/
  /*seta flag*/
  /*unlock*/
}


void *correr(void *arg){
  int id;
  info_atleta *info;
  int minutos_anuncio = 0;
  info = (info_atleta *)arg;
  id = info->id;
  categoria_atleta[id] = info->categoria;
  /*V(sem)*/
  initialized = 1;
  minutos_anuncio = natacao(id, minutos_anuncio);
  minutos_anuncio = transicao(id, 1, minutos_anuncio);
  minutos_anuncio = ciclismo(id, minutos_anuncio);
  minutos_anuncio = transicao(id, 2, minutos_anuncio);
  minutos_anuncio = corrida(id, minutos_anuncio);
  done[id] = 1;
  return NULL;
}
