#ifndef _DATABASE_HPP
#define _DATABASE_HPP

#include "SQLiteCpp/Database.h"

#include <string>
#include <vector>

class Database {
private:
  static std::vector<std::vector<std::string>> data;
  static const std::vector<std::string> title;
  static SQLite::Database db;

public:
  static std::vector<std::vector<std::string>> LoadRecord();
  static void QueryRecord();
  static void QueryRecord(const std::string &, const std::string &,
                          const std::string &, const std::string &);
  static void InsertRecord(const std::string (&)[6]);
  static void DeleteRecord(const std::string &);
  static int CalcSum();
  static int CalcSum(const std::string, const std::string);
  static std::vector<std::string> QueryType();
  static bool Init();
};
#endif
