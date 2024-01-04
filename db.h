#ifndef DB_H
#define DB_H

#include <sqlite3.h>

extern sqlite3 *db;

void init_db();
void save_last_page(int page);
int load_last_page();
void close_db();

#endif // DB_H