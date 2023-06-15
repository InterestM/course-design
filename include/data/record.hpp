#ifndef _RECORD_HPP
#define _RECORD_HPP

#include <string>

class Record {
public:
  Record(const int &id, const std::string &type,
         const std::string &specification, const std::string &adscription,
         const int &amount, const std::string &status,
         const std::string &source);

  const int &getId() const;                    // 获取id
  const std::string &getType() const;          //     type
  const std::string &getSpecification() const; //     specification
  const std::string &getAdscription() const;   //     adscription
  const int &getAmount() const;                //     amount
  const std::string &getStatus() const;        //     status
  const std::string &getSource() const;        //     source

private:
  const int id;
  const std::string type;
  const std::string specification;
  const std::string adscription;
  const int amount;
  const std::string status;
  const std::string source;
};

#endif
