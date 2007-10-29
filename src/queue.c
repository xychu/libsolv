/*
 * queue.c
 *
 */

#include <stdlib.h>
#include <string.h>

#include "queue.h"
#include "util.h"

void
queue_clone(Queue *t, Queue *s)
{
  t->alloc = t->elements = xmalloc((s->count + 8) * sizeof(Id));
  if (s->count)
    memcpy(t->alloc, s->elements, s->count * sizeof(Id));
  t->count = s->count;
  t->left = 8;
}

void
queue_init(Queue *q)
{
  q->alloc = q->elements = 0;
  q->count = q->left = 0;
}

void
queue_init_buffer(Queue *q, Id *buf, int size)
{
  q->alloc = 0;
  q->elements = buf;
  q->count = 0;
  q->left = size;
}

void
queue_free(Queue *q)
{
  if (q->alloc)
    free(q->alloc);
  q->alloc = q->elements = 0;
  q->count = q->left = 0;
}

void
queue_alloc_one(Queue *q)
{
  if (q->alloc && q->alloc != q->elements)
    {
      memmove(q->alloc, q->elements, q->count * sizeof(Id));
      q->left += q->elements - q->alloc;
      q->elements = q->alloc;
    }
  else if (q->alloc)
    {
      q->elements = q->alloc = realloc(q->alloc, (q->count + 8) * sizeof(Id));
      q->left += 8;
    }
  else
    {
      q->alloc = xmalloc((q->count + 8) * sizeof(Id));
      if (q->count)
	memcpy(q->alloc, q->elements, q->count * sizeof(Id));
      q->elements = q->alloc;
      q->left += 8;
    }
}

