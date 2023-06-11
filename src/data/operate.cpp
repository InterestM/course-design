#include "SQLiteCpp/Database.h"
#include "SQLiteCpp/SQLiteCpp.h"
#include "SQLiteCpp/Statement.h"
#include "data/database.hpp"
#include <string>
#include <vector>

void Database::QueryRecord() {
  std::vector<std::vector<std::string>> file = {
      {"ID", "类型", "型号", "归属", "数量", "状态", "来源"}};
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
      for (int i = 0; i < 7; i++)
        tmp.push_back(query.getColumn(i));
      file.push_back(tmp);
    }
    transaction.commit();
  } catch (std::exception &e) {
    file = std::vector<std::vector<std::string>>{
        {"something unexpected happened while loading"}};
  }
  data = file;
}

void Database::QueryRecord(const std::string &s_type, const std::string &s_spec,
                           const std::string &s_ads,
                           const std::string &s_status) {
  std::vector<std::vector<std::string>> file = {
      {"ID", "类型", "型号", "归属", "数量", "状态", "来源"}};
  try {
    SQLite::Database db("data.db3",
                        SQLite::OPEN_CREATE | SQLite::OPEN_READWRITE);
    SQLite::Transaction transaction(db);
    db.exec("CREATE TABLE IF NOT EXISTS data (id INTEGER PRIMARY KEY "
            "AUTOINCREMENT,type TEXT,specification TEXT,adscription "
            "TEXT,amout INTEGER,status TEXT,evidence TEXT)");
    SQLite::Statement query(
        db, "SELECT * FROM data WHERE type LIKE ? AND specification LIKE ? AND "
            "adscription LIKE ? AND status LIKE ?");
    if (s_type.length() > 0) {
      query.bind(1, s_type);
    } else {
      query.bind(1, "%");
    }
    if (s_spec.length() > 0) {
      query.bind(2, s_spec + "%");
    } else {
      query.bind(2, "%");
    }
    if (s_ads.length() > 0) {
      query.bind(3, s_ads);
    } else {
      query.bind(3, "%");
    }
    if (s_status.length() > 0) {
      query.bind(4, "%" + s_status + "%");
    } else {
      query.bind(4, "%");
    }
    while (query.executeStep()) {
      std::vector<std::string> tmp;
      for (int i = 0; i < 7; i++)
        tmp.push_back(query.getColumn(i));
      file.push_back(tmp);
    }
    transaction.commit();
  } catch (std::exception &e) {
    file = std::vector<std::vector<std::string>>{
        {"something unexpected happened while loading"}};
  }
  data = file;
}

std::vector<std::vector<std::string>> Database::LoadRecord() { return data; }

void Database::InsertRecord(std::string (&tmp)[6]) {
  SQLite::Database db("data.db3", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
  SQLite::Transaction transaction(db);
  SQLite::Statement query{
      db, "INSERT INTO data "
          "(id,type,specification,adscription,amout,status,evidence) "
          "VALUES (NULL,?,?,?,?,?,?)"};
  for (int i = 0; i < 6; i++) {
    query.bind(i + 1, tmp[i]);
  }
  query.exec();
  transaction.commit();
}

void Database::DeleteRecord(const std::string &id) {
  SQLite::Database db("data.db3", SQLite::OPEN_READWRITE);
  SQLite::Transaction transaction(db);
  SQLite::Statement query{db, "DELETE FROM data WHERE ID = ?;"};
  query.bind(1, id);
  query.exec();
  transaction.commit();
}
