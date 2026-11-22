#ifndef APTPKG_SQLITE_H
#define APTPKG_SQLITE_H

#ifdef WITH_SQLITE3

#include <sqlite3.h>
#include <string>
#include <map>

using std::map;
using std::string;

class SqliteQuery {
  protected:
    sqlite3 *DB;
    sqlite3_stmt *stmt;

    map<string, int> ColNames;

  public:
    bool Exec(const string &SQL);
    bool Bind(int index, int val);

    bool Rewind();
    bool Step();

    bool Get(const string &ColName, string &Val);
    bool Get(const string &ColName, unsigned long &Val);

    string GetCol(const string &ColName);
    unsigned long GetColI(const string &ColName);

    SqliteQuery(sqlite3 *DB);
    ~SqliteQuery();
};

class SqliteDB {
  protected:
    sqlite3 *DB;
    string DBPath;

  public:
    SqliteQuery *Query(const string &SQL);
    bool Exclusive(bool mode);

    SqliteDB(string DBPath);
    ~SqliteDB();
};

#endif /* WITH_SQLITE3 */

#endif
// vim:ts=4:sw=4:et
