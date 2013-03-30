/*Renan Teruo Carneiro - Numero USP 6514157*/
/*EP2: Make*/
/*Header das funções de fila*/

#ifndef _QUEUE_
#define _QUEUE_

#define element int

typedef struct queue *Queue;

/*Inicializa fila que comporta até n elementos*/
Queue queueInit(int n);
/*Enfila o cara*/
void queuePut(Queue q, element e);
/*Tira um cara da fila*/
element queueTake(Queue q);
/*Fila vazia?*/
int queueEmpty(Queue q);
/*Fila cheia?*/
int queueFull(Queue q);
/*You are no longer needed. Goodbye.*/
void queueFree(Queue q);

#endif /*_QUEUE_*/
