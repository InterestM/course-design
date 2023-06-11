#ifndef OPERATE_HPP
#define OPERATE_HPP

#include <string>
#include <vector>

class Database {
  static inline std::vector<std::vector<std::string>> data;

public:
  static std::vector<std::vector<std::string>> LoadRecord();
  static void QueryRecord();
  static void QueryRecord(const std::string &, const std::string &,
                          const std::string &, const std::string &);
  static void InsertRecord(std::string (&)[6]);
  static void DeleteRecord(const std::string &);
  static int calcSum(const std::string);
};
#endif // !OPERATE_HPP
