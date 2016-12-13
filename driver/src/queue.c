//Jeremy Benedek and Brad Jones
//Driver for Final Project
//Originally from Jeremy Benedek and Brad Jones for Lab10

#include "queue.h"

void init_queue(queue_t *buf) {
  buf->head= 1;
  buf->tail= 0;
}

int queue_full(queue_t *buf) {
  return (((buf->tail+ 1) % QUEUE_SIZE) == buf->head);
}

int queue_empty(queue_t *buf) {
  return (buf->head== buf->tail);
}

int enqueue (queue_t *buf, int data) {
  if (queue_full(buf)) {
    return 0;
  } else {
    buf->buffer[buf->tail] = data;
    buf->tail= ((buf->tail+ 1) == QUEUE_SIZE) ? 0 : buf->tail+ 1;
  }
  return 1;
}

int dequeue (queue_t *buf, int *data) {
  if(queue_empty(buf)){
    return 0;
  } else {
    *data = buf->buffer[buf->head];
    buf->head= ((buf->head+ 1) == QUEUE_SIZE) ? 0 : buf->head+ 1;
  }
  return 1;
}



/* queue.c ends here */
