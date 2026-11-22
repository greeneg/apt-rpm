/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

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
