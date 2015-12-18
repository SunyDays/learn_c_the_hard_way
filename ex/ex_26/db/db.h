#ifndef _db_h
#define _db_h

#define DB_FILE "/usr/local/.devpkg/db"
#define DB_DIR "/usr/local/.devpkg"

int db_init();
int db_list();
int db_update(const char *url);
int db_find(const char *url);

#endif
