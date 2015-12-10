#ifndef _ex_19_h
#define _ex_19_h

#include "object.h"

struct monster
{
  object proto;
  int hit_points;
};

typedef struct monster monster;

int monster_attack(void *self, int damage);
int monster_init(void *self);

#endif
