#ifndef _DATABASE_HPP
#define _DATABASE_HPP

#include <string>
#include <vector>

#include <SQLiteCpp/Database.h>

#include "data/record.hpp"

class Database {
private:
  static SQLite::Database db;
  static std::vector<Record> *cache;
  static void UpdateCache();

public:
  static std::vector<Record> &QueryRecord();
  static std::vector<Record> &QueryRecord(const std::string &s_type,
                                          const std::string &s_spec,
                                          const std::string &s_ads,
                                          const std::string &s_status);
  static void InsertRecord(const Record &);
  static void DeleteRecord(int id);
  static void UpdateRecord(const Record &);
  static int CalcSum(const std::string &, const std::string &);
  static std::vector<std::string> QueryType();
  static bool Init();
  static bool ClearRecord();
};
#endif
