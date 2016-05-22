// Invoice.hpp
// Mark A. Nickerson
// Term Project
// May 19th, 2016
// COMSC 210

#ifndef INVOICE_HPP
#define INVOICE_HPP

#include <string>

class Invoice
{
public:
  Invoice();
  // copy constructor
  Invoice(std::string shipNum, std::string type, std::string dest, std::string date, std::string shDate, double lbs);
  ~Invoice();
  bool fillInvoice(const std::string &type, const std::string &dest, const std::string &date, const double &lbs);
  void outputInvoice();
  void setShipNumber(const std::string &shipNum); // mutator
  std::string getShippingNumber() const; // accessor
  std::string getShipDate() const; // accessor
  Invoice getInvoice() const; // accessor
  // begin overloaded operators:
  bool operator==(const Invoice& obj);
  friend std::ostream& operator<< (std::ostream &out, const Invoice &invoice);
private:
  void createShipNumber(const std::string &type, const std::string &date, const double &lbs);
  void createShipDate();
  std::string shipNumber;
  std::string shipType;
  std::string destination;
  std::string buyDate;
  std::string shipDate;
  double weight = 0.0;
};
#endif