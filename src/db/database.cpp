#include <exception>
#include <string>
#include <vector>

#include <SQLiteCpp/Database.h>
#include <SQLiteCpp/SQLiteCpp.h>
#include <SQLiteCpp/Statement.h>

#include "data/record.hpp"
#include "db/database.hpp"
//// 数据库操作,use SQLite3
SQLite::Database Database::db{"data.db3",
                              SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE};
// 初始化数据库，不存在时创建数据库及表
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
// 执行查询语句，并将数据转换为std::vector<std::Record>,以转换为表
std::vector<Record> Query2Records(SQLite::Statement &&query) {
  try {
    std::vector<Record> records;
    while (query.executeStep()) {
      records.push_back(
          Record(query.getColumn("id"), query.getColumn("type"),
                 query.getColumn("specification"),
                 query.getColumn("adscription"), query.getColumn("amount"),
                 query.getColumn("status"), query.getColumn("source")));
    }
    return records;
  } catch (std::exception &e) {
    return {Record{0, "ERROT", e.what(), "ERROR", 0, "ERROR", "ERROR"}};
  }
}

} // namespace

// 更新查询语句
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

std::vector<Record> &Database::QueryRecord() {
  if (Database::cache == nullptr) {
    Database::UpdateCache();
  }
  return *Database::cache;
}
// 读取查询选项
std::vector<Record> &Database::QueryRecord(const std::string &s_type,
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
// 插入记录
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
// 删除记录
void Database::DeleteRecord(int id) {
  SQLite::Transaction transaction(Database::db);
  SQLite::Statement query{Database::db, "DELETE FROM data WHERE ID = ?;"};
  query.bind(1, id);
  query.exec();
  transaction.commit();
  Database::UpdateCache();
}
// 编辑记录
void Database::UpdateRecord(const Record &record) {
  SQLite::Transaction transaction(Database::db);
  SQLite::Statement rawQuery = {Database::db,
                                "SELECT * FROM data WHERE id LIKE ?"};
  rawQuery.bind(1, record.getId());
  Record raw = Query2Records(std::move(rawQuery)).front();
  SQLite::Statement update = {Database::db, "UPDATE data "
                                            "SET type=?,"
                                            "    specification=?, "
                                            "    adscription=?, "
                                            "    amount=?, "
                                            "    status=?, "
                                            "    source=? "
                                            "WHERE id=?"};
  if (record.getType().size() > 0)
    update.bind(1, record.getType());
  else
    update.bind(1, raw.getType());
  if (record.getSpecification().size() > 0)
    update.bind(2, record.getSpecification());
  else
    update.bind(2, raw.getSpecification());
  if (record.getAdscription().size() > 0)
    update.bind(3, record.getAdscription());
  else
    update.bind(3, raw.getAdscription());
  if (record.getAmount() > 0)
    update.bind(4, record.getAmount());
  else
    update.bind(4, raw.getAmount());
  if (record.getStatus().size() > 0)
    update.bind(5, record.getStatus());
  else
    update.bind(5, raw.getStatus());
  if (record.getSource().size() > 0)
    update.bind(6, record.getSource());
  else
    update.bind(6, raw.getSource());
  update.bind(7, record.getId());

  update.exec();
  transaction.commit();
  Database::UpdateCache();
}
// 查询某一类型下某一阵营的损失数量
int Database::CalcSum(const std::string &targetType,
                      const std::string &targetADS) {
  try {
    SQLite::Statement query{
        Database::db, "SELECT sum(amount) FROM data WHERE type        LIKE ? "
                      "                             AND   adscription LIKE ?"};
    if (targetType.size() > 0)
      query.bind(1, targetType);
    else
      query.bind(1, "%");
    query.bind(2, targetADS);
    query.executeStep();
    return query.getColumn(0);
  } catch (std::exception &e) {
    return -1;
  }
}
// 查询装备的已有种类
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
// 清除所有数据
bool Database::ClearRecord() {
  try {
    SQLite::Transaction transaction(Database::db);
    Database::db.exec("DROP TABLE data");
    Database::db.exec("CREATE TABLE IF NOT EXISTS data ("
                      "  id            INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "  type          TEXT   ,"
                      "  specification TEXT   ,"
                      "  adscription   TEXT   ,"
                      "  amount        INTEGER,"
                      "  status        TEXT   ,"
                      "  source        TEXT   )");
    transaction.commit();

    return true;
  } catch (std::exception &e) {
    return false;
  }
}
