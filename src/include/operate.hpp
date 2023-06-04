#ifndef OPERATE_HPP
#define OPERATE_HPP

#include <string>
#include <vector>

class Database {
public:
  static std::vector<std::vector<std::string>> LoadRecord();
  static void InsertRecord(std::vector<std::string>);
  static void DeleteRecord();
};
#endif // !OPERATE_HPP
