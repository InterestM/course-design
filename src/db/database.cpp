#include "db/database.hpp"

#include <string>
#include <vector>

#include "SQLiteCpp/Database.h"
#include "SQLiteCpp/SQLiteCpp.h"
#include "SQLiteCpp/Statement.h"
#include "data/record.hpp"

SQLite::Database Database::db{"data.db3",
                              SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE};

bool Database::Init() {
  try {
    SQLite::Transaction transaction(Database::db);
    Database::db.exec("CREATE TABLE IF NOT EXISTS data ("
                      "  id            INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "  type          TEXT   ,"
                      "  specification TEXT   ,"
                      "  adscription   TEXT   ,"
                      "  amount        INTEGER,"
                      "  status        TEXT   ,"
                      "  source        TEXT   )");
    transaction.commit();
  } catch (std::exception &e) {
    return false;
  }
  return true;
}

std::vector<Record> *Database::cache = nullptr;

namespace {

std::vector<std::string> cacheParams = {"", "", "", ""};

std::vector<Record> Query2Records(SQLite::Statement &&query) {
  std::vector<Record> records;
  while (query.executeStep()) {
    records.push_back(
        Record(query.getColumn("id"), query.getColumn("type"),
               query.getColumn("specification"), query.getColumn("adscription"),
               query.getColumn("amount"), query.getColumn("status"),
               query.getColumn("source")));
  }
  return records;
}

} // namespace

void Database::UpdateCache() {
  if (cache != nullptr) {
    delete cache;
  }

  SQLite::Statement query(Database::db,
                          "SELECT * FROM data WHERE type          LIKE ?"
                          "                   AND   specification LIKE ?"
                          "                   AND   adscription   LIKE ?"
                          "                   AND   status        LIKE ?");

  query.bind(1, "%" + cacheParams[0] + "%");
  query.bind(2, "%" + cacheParams[1] + "%");
  query.bind(3, "%" + cacheParams[2] + "%");
  query.bind(4, "%" + cacheParams[3] + "%");

  cache = new std::vector{Query2Records(std::move(query))};
}

std::vector<Record> Database::QueryRecord() {
  if (Database::cache == nullptr) {
    Database::UpdateCache();
  }
  return *Database::cache;
}

std::vector<Record> Database::QueryRecord(const std::string &s_type,
                                          const std::string &s_spec,
                                          const std::string &s_ads,
                                          const std::string &s_status) {
  if (Database::cache == nullptr || cacheParams[0] != s_type ||
      cacheParams[1] != s_spec || cacheParams[2] != s_ads ||
      cacheParams[3] != s_status) {
    cacheParams = {s_type, s_spec, s_ads, s_status};
    Database::UpdateCache();
  }
  return *Database::cache;
}

void Database::InsertRecord(const Record &record) {
  SQLite::Transaction transaction(Database::db);
  SQLite::Statement query{
      Database::db,
      "INSERT INTO data "
      "(id, type, specification, adscription, amount, status, source) "
      "VALUES (NULL, ?, ?, ?, ?, ?, ?)"};

  query.bind(1, record.getType());
  query.bind(2, record.getSpecification());
  query.bind(3, record.getAdscription());
  query.bind(4, record.getAmount());
  query.bind(5, record.getStatus());
  query.bind(6, record.getSource());

  query.exec();
  transaction.commit();
  Database::UpdateCache();
}

void Database::DeleteRecord(int id) {
  SQLite::Transaction transaction(Database::db);
  SQLite::Statement query{Database::db, "DELETE FROM data WHERE ID = ?;"};
  query.bind(1, id);
  query.exec();
  transaction.commit();
  Database::UpdateCache();
}

int Database::CalcSum() {
  try {
    return Database::db.execAndGet("SELECT sum(amount) FROM data");
  } catch (std::exception &e) {
    return 0;
  }
}

int Database::CalcSum(const std::string &targetType,
                      const std::string &targetADS) {
  try {
    SQLite::Statement query{
        Database::db, "SELECT sum(amount) FROM data WHERE type LIKE ? AND "
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
    SQLite::Statement query{Database::db, "SELECT DISTINCT type FROM data"};
    while (query.executeStep()) {
      types.push_back(query.getColumn(0));
    }
  } catch (std::exception &e) {
    return {"something unexpected happened while QueryType"};
  }
  return types;
}
