#include "data/record.hpp"

Record::Record(const int &id, const std::string &type,
               const std::string &specification, const std::string &adscription,
               const int &amount, const std::string &status,
               const std::string &source)
    : id(id),
      type(type),
      specification(specification),
      adscription(adscription),
      amount(amount),
      status(status),
      source(source) {}

const int &Record::getId() const { return id; }
const std::string &Record::getType() const { return type; }
const std::string &Record::getSpecification() const { return specification; }
const std::string &Record::getAdscription() const { return adscription; }
const int &Record::getAmount() const { return amount; }
const std::string &Record::getStatus() const { return status; }
const std::string &Record::getSource() const { return source; }
