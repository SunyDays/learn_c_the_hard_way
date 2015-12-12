#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "object.h"

void object_destroy(void *self)
{
  assert(self);
  
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
  assert(self);
  
  object *obj = self;
  assert(obj->description);
    
  printf("%s.\n", obj->description);
}

int object_init(void *self)
{
  assert(self);
  return 1;
}

void* object_move(void *self, direction direction)
{
  assert(self);
  
  printf("You can't go that direction.\n");
  return NULL;
}

int object_attack(void *self, int damage)
{
  assert(self);
  assert(damage >= 0);
  
  printf("You can't attack that.\n");
  return 0;
}

void* object_new(size_t size, object proto, char *description)
{
  assert(size > 0);
  assert(description);
  
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
  assert(el);
  
  *el = proto;
  el->description = strdup(description);
  assert(el->description);

  if(!el->init(el))
    el->destroy(el);
    
  assert(el);
  return el;
}
