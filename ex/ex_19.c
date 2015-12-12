#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ex_19.h"

int monster_attack(void *self, int damage)
{
  monster *monster = self;

  printf("You attack %s!\n", monster->_(description));
  monster->hit_points -= damage;

  if(monster->hit_points > 0)
  {
    printf("It is still alive.\n");
    return 0;
  }
  else
  {
    printf("It is dead!\n");
    return 1;
  }
}

int monster_init(void *self)
{
  monster *monster = self;
  monster->hit_points = 10;
  return 1;
}

object monster_proto = { .init = monster_init, .attack = monster_attack };

void* roome_move(void *self, direction direction)
{
  room *room = self;
  room *next = NULL;

  if(direction == NORTH && room->north)
  {
    printf("You go north, into:\n");
    next = room->north;
  }
  else if(direction == SOUTH && room->south)
  {
    printf("You go south, into:\n");
    next = room->south;
  }
  else if(direction == EAST  && room->east)
  {
    printf("You go east, into:\n");
    next = room->east;
  }
  else if(direction == WEST  && room->west)
  {
    printf("You go west, into:\n");
    next = room->west;
  }
  else
  {
    printf("You can't go that direction.\n");
    next = NULL;
  }

  if(next)
    next->_(describe)(next);

  return next;
}

int room_attack(void *self, int damage)
{
  room *room = self;
  monster *monster = room->bad_guy;

  if(monster)
  {
    monster->_(attack)(monster, damage);
    return 1;
  }
  else
  {
    printf("You fail int the air at nothing. Idiot.\n");
    retutn 0;
  }
}

object room_proto = { .move = room_move, .attack = room_attack };

void* map_move(void *self, direction direction)
{
  map *map = self;
  room *location = map->location;
  room *next = NULL;

  next = location->_(move)(location, direction);

  if(next)
    map->location = next;

  return next;
}

int map_attack(void *self, int damage)
{
  map *map = self;
  room *location = map->location;

  return location->_(attack)(location, damage);
}

int map_init(void *self)
{
  map *map = self;

  room *hall = NEW(room, "The great hall");
  room *throne = NEW(room, "The throne room");
  room *arena = NEW(room, "The arena, with minotaur");
  room *kitchen = NEW(room, "Kitchen, you have the knife now");

  arena->bad_guy = NEW(monster, "The evil minotaur");

  hall->north = throne;
  throne->west = arena;
  throne->east = kitchen;
  throne->south = hall;
  arena->east = throne;
  kitchen->west = throne;

  map->start = hall;
  map->location = hall;

  return 1;
}

object map_proto = { .init = map_init, .move = map_move, .attack = map_attack };

int process_input(map *game)
{
  printf("\n> ");

  char ch = getchar();
  getchar();

  int damage = rand() % 4;

  switch(ch)
  {
    case -1:
      printf("Giving up? You suck.\n");
      return 0;      
      break;

    case 'n':
      game->_(move)(game, NORTH);
      break;

    case 's':
      game->_(move)(game, SOUTH);
      break;

    case 'e':
      game->_(move)(game, EAST);
      break;

    case 'w':
      game->_(move)(game, WEST);
      break;

    case 'a':
      game->_(attack)(game, damage);
      break;

    case 'l':
      printf("You can go:\n");
      if(game->location->north)
	printf("NORTH\n");
      if(game->location->south)
	printf("SOUTH\n");
      if(game->location->east)
	printf("EAST\n");
      if(game->location->west)
	printf("WEST\n");
      break;

    default:
      printf("What?: %i\n", ch);
  }

  return 1;
}

int main()
{
  srand(time(NULL));

  map *game = NEW(map, "The Hall of Minotaur.");

  printf("You enter the ");
  game->location->_(describe)(game->location);

  while(process_input(game))
  {}

  exit(EXIT_SUCCESS);
}
