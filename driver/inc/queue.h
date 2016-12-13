//Jeremy Benedek and Brad Jones
//Driver for Final Project

#define QUEUE_SIZE 32

typedef struct queue {
  int head;
  int tail;
  int buffer[QUEUE_SIZE];
} queue_t;

void init_queue(queue_t *);
int enqueue(queue_t *, int);
int dequeue(queue_t *, int *);            
int queue_empty(queue_t *);            
int queue_full(queue_t*);
/* queue.h ends here */
