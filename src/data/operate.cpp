#include "include/operate.hpp"
#include "SQLiteCpp/Database.h"
#include "SQLiteCpp/SQLiteCpp.h"
#include <string>
#include <vector>

std::vector<std::vector<const char *>> Database::LoadRecord() {
  std::vector<std::vector<const char *>> file;
  SQLite::Database db("data.db3", SQLite::OPEN_CREATE | SQLite::OPEN_READWRITE);
  db.exec("CREATE TABLE IF NOT EXISTS data (id INTEGER PRIMARY KEY "
          "AUTOINCREMENT,type TEXT,specification TEXT,status TEXT,adscription "
          "TEXT,evidence TEXT)");
  SQLite::Statement query(db, "SELECT * FROM data");
  while (query.executeStep()) {
    std::vector<const char *> tmp;
    tmp.push_back(query.getColumn(1));
    file.push_back(tmp);
  }
  return file;
}
void Database::InsertRecord(std::vector<std::string> tmp) {
  SQLite::Database db("data.db3", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
}
