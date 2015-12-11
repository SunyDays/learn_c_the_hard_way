#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "object.h"

void object_destroy(void *self)
{
  object *obj = self;

  if(obj)
  {
    if(obj->description)
      free(obj->description);
    free(obj);
  }  
}

void object_describe(void *self)
{
  object *obj = self;
  printf("%s.\n", obj->description);
}

int object_init(void *self)
{
  return 1;
}

void* object_move(void *self, direction direction)
{
  printf("You can't go that direction.\n");
  return NULL;
}

int object_attack(void *self, int damage)
{
  printf("You can't attack that.\n");
  return 0;
}

void* object_new(size_t size, object proto, char *description)
{
  if(!proto.init)
    proto.init = object_init;
  if(!proto.describe)
    proto.describe = object_describe;
  if(!proto.destroy)
    proto.destroy = object_destroy; 
  if(!proto.attack)
    proto.attack = object_attack;
  if(!proto.move)
    proto.move = object_move;

  object *el = calloc(1, size);
  *el = proto;
  el->description = strdup(description);

  if(!el->init(el))
  {
    el->destroy(el);
    return NULL;
  }
  else
    return el;
}
