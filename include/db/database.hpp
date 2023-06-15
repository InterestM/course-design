#ifndef _DATABASE_HPP
#define _DATABASE_HPP

#include <string>
#include <vector>

#include <SQLiteCpp/Database.h>

#include "data/record.hpp"

class Database {
private:
  static SQLite::Database db;
  static std::vector<Record> *cache; // 暂存数据
  static void UpdateCache();         // 更新Cache

public:
  static std::vector<Record> &QueryRecord(); // 从Cache中获取记录
  static std::vector<Record> &
  QueryRecord(const std::string &s_type, // 获取记录，查询条件变化时更新Cache
              const std::string &s_spec, const std::string &s_ads,
              const std::string &s_status);
  static void InsertRecord(const Record &); // 插入记录
  static void DeleteRecord(int id);         // 删除记录
  static void UpdateRecord(const Record &); // 编辑记录
  static int
  CalcSum(const std::string &targetType,
          const std::string &targetADS); // 计算目标类型目标所属的装备数量
  static std::vector<std::string> QueryType(); // 获取当前表内所有类型
  static bool Init();                          // 初始化
  static bool ClearRecord();                   // 清除所有数据
};
#endif
