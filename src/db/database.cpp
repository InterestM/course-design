
#include "db/database.hpp"

#include <string>
#include <vector>

#include "SQLiteCpp/Database.h"
#include "SQLiteCpp/SQLiteCpp.h"
#include "SQLiteCpp/Statement.h"

const std::vector<std::string> Database::title = {
    "ID", "类型", "型号", "归属", "数量", "状态", "来源"};

SQLite::Database Database::db{"data.db3",
                              SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE};
std::vector<std::vector<std::string>> Database::data{};

bool Database::Init() {
  try {
    SQLite::Transaction transaction(db);
    db.exec("CREATE TABLE IF NOT EXISTS data (id INTEGER PRIMARY KEY "
            "AUTOINCREMENT,type TEXT,specification TEXT,adscription "
            "TEXT,amout INTEGER,status TEXT,evidence TEXT)");
    transaction.commit();
  } catch (std::exception &e) {
    return false;
  }

  data = {title};
  return true;
}

void Database::QueryRecord() {
  std::vector<std::vector<std::string>> table = {title};
  try {
    SQLite::Transaction transaction(db);
    SQLite::Statement query(db, "SELECT * FROM data");
    while (query.executeStep()) {
      std::vector<std::string> tmp;

      for (int i = 0; i < title.size(); i++)
        tmp.push_back(query.getColumn(i));
      table.push_back(tmp);
    }
    transaction.commit();
  } catch (std::exception &e) {
    table = std::vector<std::vector<std::string>>{
        {"something unexpected happened while loading"}};
  }
  data = table;
}

void Database::QueryRecord(const std::string &s_type, const std::string &s_spec,
                           const std::string &s_ads,
                           const std::string &s_status) {

  std::vector<std::vector<std::string>> table = {title};
  try {
    SQLite::Transaction transaction(db);
    SQLite::Statement query(
        db, "SELECT * FROM data WHERE type LIKE ? AND specification LIKE ? AND "
            "adscription LIKE ? AND status LIKE ?");
    if (s_type.length() > 0) {
      query.bind(1, "%" + s_type + "%");
    } else {
      query.bind(1, "%");
    }
    if (s_spec.length() > 0) {
      query.bind(2, "%" + s_spec + "%");
    } else {
      query.bind(2, "%");
    }
    if (s_ads.length() > 0) {
      query.bind(3, "%" + s_ads + "%");
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

      for (int i = 0; i < title.size(); i++)
        tmp.push_back(query.getColumn(i));
      table.push_back(tmp);
    }
    transaction.commit();
  } catch (std::exception &e) {
    table = std::vector<std::vector<std::string>>{
        {"something unexpected happened while loading"}};
  }
  data = table;
}

std::vector<std::vector<std::string>> Database::LoadRecord() { return data; }

void Database::InsertRecord(const std::string (&tmp)[6]) {
  try {
    SQLite::Database db("data.db3",
                        SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
    SQLite::Transaction transaction(db);
    SQLite::Statement query{
        db, "INSERT INTO data "
            "(id,type,specification,adscription,amout,status,evidence) "
            "VALUES (NULL,?,?,?,?,?,?)"};
    for (int i = 1; i < title.size(); i++) {
      query.bind(i, tmp[i - 1]);
    }
    query.exec();
    transaction.commit();
  } catch (std::exception &e) {
    data = {{"something unexpected happened while Inserting"}};
  }
}

void Database::DeleteRecord(const std::string &id) {
  try {
    SQLite::Database db("data.db3", SQLite::OPEN_READWRITE);
    SQLite::Transaction transaction(db);
    SQLite::Statement query{db, "DELETE FROM data WHERE ID = ?;"};
    query.bind(1, id);
    query.exec();
    transaction.commit();
  } catch (std::exception &e) {
    data = {{"something unexpected happened while Deleting"}};
  }
}

int Database::CalcSum() {
  try {
    SQLite::Database db("data.db3", SQLite::OPEN_READONLY);
    return db.execAndGet("SELECT sum(amount) FROM data ");
  } catch (std::exception &e) {
    return 0;
  }
}

int Database::CalcSum(const std::string targetType,
                      const std::string targetADS) {
  try {
    SQLite::Database db("data.db3", SQLite::OPEN_READONLY);
    SQLite::Statement query{
        db, "SELECT sum(amount) FROM data WHERE type LIKE ? AND "
            "adscription LIKE ?"};
    query.bind(1, targetType);
    query.bind(2, targetADS);
    query.exec();
    return query.getColumn(0);
  } catch (std::exception &e) {
    return -1;
  }
}

std::vector<std::string> Database::QueryType() {
  std::vector<std::string> types;
  try {
    SQLite::Database db("data.db3", SQLite::OPEN_READONLY);
    SQLite::Statement query{db, "SELECT DISTINCT type FROM data"};
    while (query.executeStep()) {
      types.push_back(query.getColumn(0));
    }
  } catch (std::exception &e) {
    return {"something unexpected happened while QueryType"};
  }
  return types;
}
