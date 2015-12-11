#ifndef _object_h
#define _object_h

typedef enum { NORTH, SOUTH, EAST, WEST} direction;

typedef struct
{
  char *description;
  int (*init)(void *self);
  void (*describe)(void *self);
  void (*destroy)(void *self);
  void (*move)(void *self, direction direction);
  int object_attack(void *self, int damage);
  void *object_new(size_t size, object proto, char *description);
} object;

int object_init(void *self);
void object_destroy(void *self);
void object_describe(void *self);
void *object_move(void *self, direction direction);
int object_attack(void *self, int damage);
void object_new(size_t size, object proto, char *description);

#define NEW(T, N) object_new(sizeof(T), T##_proto, N)
#define _(N) proto.N

#endif
