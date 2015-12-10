#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_DATA 512
#define MAX_ROWS 100

struct address
{
  int id;
  int set;
  char name[MAX_DATA];
  char email[MAX_DATA];
};

struct database
{
  struct address rows[MAX_ROWS];
};

struct connection
{
  FILE *file;
  struct database *db;
};

struct connection *CONN;

void database_close()
{
  if(CONN)
  {
    if(CONN->file)
      fclose(CONN->file);
    if(CONN->db)
      free(CONN->db);
    
    free(CONN);
  }
}

void die(const char *message)
{
  database_close();
  
  if(errno)
    perror(message);
  else
    fprintf(stderr, "ERROR: %s.\n", message);

  exit(EXIT_FAILURE);
}

void address_print(struct address *addr)
{
  printf("%i %s %s\n", addr->id, addr->name, addr->email);
}

void database_load()
{
  int rc = fread(CONN->db, sizeof(struct database), 1, CONN->file);
  
  if(rc != 1)
    die("Failed to load database");
}

void database_open(const char *filename, char mode)
{
  CONN = malloc(sizeof(struct connection));
  if(!CONN)
    die("Memmory error");

  CONN->db = malloc(sizeof(struct database));
  if(!CONN->db)
    die("Memmory error");

  if(mode == 'c')
    CONN->file = fopen(filename, "w");
  else
  {
    CONN->file = fopen(filename, "r+");

    if(CONN->file)
      database_load();
  }

  if(!CONN->file)
    die("Failed to open the file");
}

void database_write()
{
  rewind(CONN->file);

  int rc = fwrite(CONN->db, sizeof(struct database), 1, CONN->file);
  if(rc != 1)
    die("Failed to write database");

  rc = fflush(CONN->file);
  if(rc == -1)
    die("Cannot flush database");
}

void database_create()
{
  int i;

  for(i = 0; i < MAX_ROWS; ++i)
  {
    struct address addr = {.id = i, .set = 0};
    CONN->db->rows[i] = addr;
  }
}

void database_set(int id, const char *name, const char *email)
{
  struct address *addr = &CONN->db->rows[id];
  if(addr->set)
    die("Already set, delete it first");

  addr->set = 1;
  char *res = strncpy(addr->name, name, MAX_DATA);
  addr->name[MAX_DATA - 1] = '\0';
  if(!res)
    die("Name copy failed");

  res = strncpy(addr->email, email, MAX_DATA);
  addr->email[MAX_DATA - 1] = '\0';
  if(!res)
    die("Email copy failed");
}

void database_get(int id)
{
  struct address *addr = &CONN->db->rows[id];
  if(addr->set)
    address_print(addr);
  else
    die("Id is not set");
}

void database_delete(int id)
{
  struct address addr = {.id = id, .set = 0};
  CONN->db->rows[id] = addr;
}

void database_list()
{
  struct database *db = CONN->db;
  int i;
  for(i = 0; i < MAX_ROWS; ++i)
  {
    struct address *curr = &db->rows[i];

    if(curr->set)
      address_print(curr);
  }
}

int main(int argc, char **argv)
{
  if(argc < 3)
    die("USAGE: ex_17 <dbfile> <action> [action params]");

  char *filename = argv[1];
  char action = argv[2][0];
  database_open(filename, action);
  int id = 0;

  if(argc > 3)
    id = atoi(argv[3]);
  if(id >= MAX_ROWS)
    die("There's not that many records");

  switch(action)
  {
    case 'c':
      database_create();
      database_write();
      break;

    case 'g':
      if(argc != 4)
	die("Need an id to get");

      database_get(id);
      break;

    case 's':
      if(argc != 6)
	die("Need id, name, email to set");

      database_set(id, argv[4], argv[5]);
      database_write();
      break;

    case 'd':
      if(argc != 4)
	die("Need id to delete");

      database_delete(id);
      database_write();
      break;

    case 'l':
      database_list();
      break;

    default:
      die("Invalid action, only: c=create, g=get, s=set, d=delete, l=list");
  }

  database_close();
  
  exit(EXIT_SUCCESS);
}
