#include "SQLiteCpp/Database.h"
#include "include/database.hpp"

int Database::calcSum(const std::string target) {
  SQLite::Database db("data.db3");
  return int{db.exec("SELECT sum(salary) FROM COMPANY;")};
}