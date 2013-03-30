/*Renan Teruo Carneiro - Numero USP 6514157*/
/*EP2: Make*/
/*Inplementação da fila*/


#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

struct queue{
  element *q;
  int first;
  int last;
  int max;
};

Queue queueInit(int n){
  Queue q;
  if(n <= 0){
    return NULL;
    /*Erro: usuario burro demais*/
  }
  q = malloc(sizeof *q);
  q->q = malloc((n+1) * sizeof *(q->q));
  q->first = 0;
  q->last = 1;
  q->max = n + 1;
  return q;
}

void queuePut(Queue q, element e){
  if(queueFull(q)){
    fprintf(stderr, "ERRO: Fila cheia!\n");
    return;
    /*Erro: fila cheia*/
  }
  q->q[q->last-1] = e;
  q->last = (q->last % q->max) + 1;
}

element queueTake(Queue q){
  element e;
  if(queueEmpty(q)){
    fprintf(stderr, "ERRO: Fila Vazia!");
    return -1;
    /*Erro: fila vazia*/
  }
  e = q->q[q->first];
  q->first = (q->first + 1) % q->max;
  return e;
}

int queueEmpty(Queue q){
  return (q->last % q->max == (q->first + 1) % q->max);
}

int queueFull(Queue q){
  return ((q->last % q->max) == (q->first% q->max));
}

void queueFree(Queue q){
  free(q->q);
  free(q);
}
