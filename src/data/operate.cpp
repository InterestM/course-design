#include "include/operate.hpp"
#include "SQLiteCpp/Database.h"
#include "SQLiteCpp/SQLiteCpp.h"
#include <string>
#include <vector>
std::vector<std::vector<std::string>> Database::LoadRecord() {
  std::vector<std::vector<std::string>> file = {
      {"ID", "类型", "型号", "归属", "数量", "状态", "证据"}};
  try {
    SQLite::Database db("data.db3",
                        SQLite::OPEN_CREATE | SQLite::OPEN_READWRITE);
    SQLite::Transaction transaction(db);
    db.exec("CREATE TABLE IF NOT EXISTS data (id INTEGER PRIMARY KEY "
            "AUTOINCREMENT,type TEXT,specification TEXT,adscription "
            "TEXT,amout INTEGER,status TEXT,evidence TEXT)");
    SQLite::Statement query(db, "SELECT * FROM data");
    while (query.executeStep()) {
      std::vector<std::string> tmp;
      tmp.push_back(query.getColumn(0));
      tmp.push_back(query.getColumn(1));
      tmp.push_back(query.getColumn(2));
      tmp.push_back(query.getColumn(3));
      tmp.push_back(std::to_string(int{query.getColumn(4)}));
      tmp.push_back(query.getColumn(5));
      tmp.push_back(query.getColumn(6));
      file.push_back(tmp);
    }
    transaction.commit();
  } catch (std::exception &e) {
    return std::vector<std::vector<std::string>>{{"wrong"}};
  }
  return file;
}
void Database::InsertRecord(std::vector<std::string> tmp) {
  SQLite::Database db("data.db3", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
  SQLite::Transaction transaction(db);
  SQLite::Statement query{
      db, "INSERT INTO data "
          "(id,type,specification,adscription,amout,status,evidence) "
          "VALUES (NULL,?,?,?,?,?,?)"};

  transaction.commit();
}
