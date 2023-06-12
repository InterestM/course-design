#include "SQLiteCpp/Database.h"
#include "db/database.hpp"

int Database::CalcSum(const std::string target) {
  return db.execAndGet("SELECT SUM(amount) FROM data WHERE type LIKE '" +
                       target + "'");
}
