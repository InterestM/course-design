#ifndef _RECORD_HPP
#define _RECORD_HPP

#include <string>

class Record {
 public:
  Record(const int &id, const std::string &type,
         const std::string &specification, const std::string &adscription,
         const int &amount, const std::string &status,
         const std::string &source);

  const int &getId() const;
  const std::string &getType() const;
  const std::string &getSpecification() const;
  const std::string &getAdscription() const;
  const int &getAmount() const;
  const std::string &getStatus() const;
  const std::string &getSource() const;

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
