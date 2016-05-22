// Invoice.cpp
// Mark A. Nickerson
// Term Project
// May 19th, 2016
// COMSC 210

#include "stdafx.h" // precompiler directive

#include <iostream>

#include <sstream>

#include <cstdlib>

#include <ctime>

#include "Invoice.hpp"

Invoice::Invoice()
{
  srand(time(NULL)); // seeding rand
}

Invoice::Invoice(std::string shipNum, std::string type, std::string dest, std::string date, std::string shDate, double lbs)
{
  shipNumber = shipNum;
  shipType = type;
  destination = dest;
  buyDate = date;
  shipDate = shDate;
  weight = lbs;
}

Invoice::~Invoice()
{
  // default destructor
}

bool Invoice::fillInvoice(const std::string &type, const std::string &dest, const std::string &date, const double &lbs)
{
  //begin input checking
  if (type.length() != 5 || type.substr(1, 4) != "-Day"){
    std::cerr << "Error in shipping selection.\n";
    return false;
  }
  
  if (date.length() != 10 || date[2] != '/' || date[5] != '/'){
    std::cerr << "Error in date format.\n";
    return false;
  }
  // end input checking

  createShipNumber(type, date, lbs);
  createShipDate();
  shipType = type;
  destination = dest;
  buyDate = date;
  weight = lbs;
  return true;
}

void Invoice::outputInvoice()
{
  std::cout << "Shipping number: " << shipNumber << "\nShipping Type: " << shipType
    << "\nPackage destination: " << destination << "\nDate of purchase: " << buyDate
    << "\nPackage weight: " << weight << " lbs" << "\nLast day to ship package: " << shipDate << std::endl;
}

void Invoice::setShipNumber(const std::string &shipNum)
{
  shipNumber = shipNum;
}

std::string Invoice::getShippingNumber() const
{
  return shipNumber;
}

std::string Invoice::getShipDate() const
{
  return shipDate;
}

Invoice Invoice::getInvoice() const
{
  Invoice temp(shipNumber, shipType, destination, buyDate, shipDate, weight);
  return temp;
}

//------------------BEGIN PRIVATE FUNCTIONS------------------//
void Invoice::createShipNumber(const std::string &type, const std::string &date, const double &lbs)
{
  std::string tempDate = date;
  std::ostringstream oss; // will be used to convert int to string
  int tempShip = 0;

  for (int i = 0; i < type.length(); i++){
    tempShip += (int)type[i];
  }

  oss << tempShip;
  tempShip = (100 + rand() % 300);
  oss << tempShip;

  tempDate.erase(tempDate.begin() + 2); // removes first '/' in MM/DD/YYYY
  tempDate.erase(tempDate.begin() + 4, tempDate.end()); // removes second '/' in MM/DD/YYYY
  oss << tempDate; // add substring to oss buffer

  // classifies the weight of the invoice and adds to shipping number
  if (lbs <= 5.0){
    shipNumber = oss.str() + 'A';
  }
  else if (lbs <= 10.0){
    shipNumber = oss.str() + 'B';
  }
  else if (lbs <= 15.0){
    shipNumber = oss.str() + 'C';
  }
  else if (lbs <= 20.0)
  {
    shipNumber = oss.str() + 'D';
  }
  else
  {
    shipNumber = oss.str() + 'E';
  }
}

void Invoice::createShipDate()
{
  std::string date;
  std::string myStr = shipNumber.substr(0, 3); // creates substring
  std::stringstream ss; // used to convert substring to int
  int shipDays = 0;
  int month = 0;
  int day = 0;

  ss << myStr;
  ss >> shipDays; // converts string to int
  ss.clear(); // clears buffer

  // classification for type of shipping
  switch (shipDays){
  case 380: // translates to "1-Day"
    shipDays = 3; // 1 day for shiping plus 2 days for handeling
    break;
  case 381:
    shipDays = 4;
    break;
  case 382:
    shipDays = 5;
    break;
  case 383:
    shipDays = 6;
    break;
  case 384:
    shipDays = 7;
    break;
  default:
    std::cerr << "An error occured determining the last day to ship.\n";
    break;
  }

  date = shipNumber.substr(6, 10); // extracts date of purchase from shipNumber
  date.erase(date.end() - 1);

  myStr = date.substr(0, 2); // gets month from string
  ss << myStr;
  ss >> month;
  ss.clear();

  myStr = date.substr(2, 3); // gets day from string
  ss << myStr;
  ss >> day;
  ss.clear();

  day += shipDays; // the day of the month the package needs to arrive to the customer

  // begin checking to make sure months are handeled correctly
  if (day > 31 && (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)){
    month++;
    day -= 31;
  }
  else if (day > 30 && (month == 4 || month == 6 || month == 9 || month == 11)){
    month++;
    day -= 30;
  }
  else if (day > 29 && (month == 2))
  {
    month++;
    day -= 29;
  }

  // begin checking to make sure days are handeled correctly
  if (month < 10 && day < 10){
    ss << 0 << month << '/' << 0 << day << '/' << 2016;
  }
  else if (month < 10 && day >= 10){
    ss << 0 << month << '/' << day << '/' << 2016;
  }
  else if (month >= 10 && day < 10){
    ss << month << '/' << 0 << day << '/' << 2016;
  }
  else
  {
    ss << month << '/' << day << '/' << 2016;
  }
  
  ss >> date;

  shipDate = date;
}
//-------------------END PRIVATE FUNCTIONS-------------------//

bool Invoice::operator==(const Invoice& obj)
{
  if (shipNumber == obj.shipNumber){
    return true;
  }
  return false;
}

//----------------------FRIEND FUNCTION----------------------//
// used for outputting to a .csv filetype
std::ostream& operator<< (std::ostream &out, const Invoice &invoice)
{
  return out << invoice.shipNumber << "," << invoice.shipType << "," << invoice.destination << ","
    << invoice.buyDate << "," << invoice.shipDate << "," << invoice.weight;
}