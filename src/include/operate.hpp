#ifndef OPERATE_HPP
#define OPERATE_HPP

#include <string>
#include <vector>

class Database {
  std::vector<std::vector<std::string>> data;

public:
  std::vector<std::vector<std::string>> LoadRecord();
  void QueryRecord();
  void QueryRecord(std::string, std::string, std::string, std::string);
  static void InsertRecord(std::vector<std::string>);
  static void DeleteRecord();
};
#endif // !OPERATE_HPP
