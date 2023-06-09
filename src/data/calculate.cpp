#include "SQLiteCpp/Database.h"
#include "include/database.hpp"

int Database::calcSum(const std::string target) {
  SQLite::Database db("data.db3", SQLite::OPEN_READONLY);

  return db.execAndGet("SELECT SUM(amout) FROM data WHERE type LIKE '" +
                       target + "'");
}
