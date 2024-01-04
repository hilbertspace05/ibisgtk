#include <sqlite3.h>

sqlite3 *db;

void init_db() {
    if (sqlite3_open("mydb.db", &db) != SQLITE_OK) {
        // Tratar erro
    }

    char *errMsg;
    const char *sql = "CREATE TABLE IF NOT EXISTS LastPage (id INTEGER PRIMARY KEY, page INTEGER);";
    if (sqlite3_exec(db, sql, 0, 0, &errMsg) != SQLITE_OK) {
        // Tratar erro
    }
}

void save_last_page(int page) {
    const char *sql = "INSERT OR REPLACE INTO LastPage (id, page) VALUES (1, ?);";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, page);
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            // Tratar erro
        }
        sqlite3_finalize(stmt);
    }
}

int load_last_page() {
    const char *sql = "SELECT page FROM LastPage WHERE id = 1;";
    sqlite3_stmt *stmt;
    int last_page = 0; // Página padrão se nenhuma foi salva

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            last_page = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
    }

    return last_page;
}

void close_db() {
    sqlite3_close(db);
}

//#include <sqlite3.h>
//#include <gtk/gtk.h>
//#include "viewer.h"
//#include "gtkviewertry.h"
//
//sqlite3 *db;
//
//void init_db() {
//    int rc = sqlite3_open("mydb.db", &db);
//
//    if (rc != SQLITE_OK) {
//        printf("Cannot open database: %s\n", sqlite3_errmsg(db));
//        return;
//    }
//
//    const char *sql = "CREATE TABLE IF NOT EXISTS LastPage (PageNumber INT);";
//    char *err_msg = 0;
//
//    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
//
//    if (rc != SQLITE_OK ) {
//        printf("Failed to create table\n");
//        sqlite3_free(err_msg);
//        sqlite3_close(db);
//    }
//}
//
//void save_current_page(int page_number) {
//    const char *sql = "INSERT OR REPLACE INTO LastPage (rowid, PageNumber) VALUES (1, ?);";
//    sqlite3_stmt *stmt;
//
//    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
//        sqlite3_bind_int(stmt, 1, page_number);
//        if (sqlite3_step(stmt) != SQLITE_DONE) {
//            printf("Failed to save page\n");
//        }
//    }
//
//    sqlite3_finalize(stmt);
//}
//
//int load_last_page() {
//    const char *sql = "SELECT PageNumber FROM LastPage WHERE rowid = 1;";
//    sqlite3_stmt *stmt;
//    int page_number = 0;
//
//    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
//        int step = sqlite3_step(stmt);
//        if (step == SQLITE_ROW) {
//            page_number = sqlite3_column_int(stmt, 0);
//        }
//    }
//
//    sqlite3_finalize(stmt);
//
//    return page_number;
//}
//
//void close_db() {
//    sqlite3_close(db);
//}