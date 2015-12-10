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

struct room
{
  object proto;
  monster *bad_guy;
  struct room *north;
  struct room *south;
  struct room *east;
  struct room *west;
};

typedef struct room room;

void* room_move(void *self, direction direction);
int room_attack(void *self, int damage);
int room_init(void *self);

struct map
{
  object proto;
  room *start;
  room *location;
};

typedef struct map map;

void* map_move(void *self, direction direction);
int map_attack(void *self, int damage);
int map_init(void *self);

#endif
