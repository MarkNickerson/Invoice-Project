// Project_Driver.cpp
// Mark A. Nickerson
// Term Project
// May 19th, 2016
// COMSC 210

#include "stdafx.h" // precompiler directive

#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include <iomanip>

#include <string>

#include <sstream>

#include "Invoice.hpp"

#include "HashTable.hpp"

int hashFunction(const Invoice &obj);

int main()
{
  cout << "\nMark A. Nickerson\t\t\t" << __FILE__ << endl << endl;

  //----BEGIN DRIVER----//

  // BEGIN MENU
  cout << std::setfill('-') << std::setw(65) << '-' << endl;
  for (int i = 0; i < 2; i++){
    cout << "|" << std::setfill(' ') << std::setw(64) << "|" << endl;
  }
  cout << "|" << std::setfill(' ') << std::setw(46) << "Welcome to the Invoice Manager" << std::setfill(' ') << std::setw(18) << "|" << endl;
  cout << "|" << std::setfill(' ') << std::setw(64) << "|" << endl;
  for (int i = 0; i < 3; i++){
    cout << "|" << std::setfill(' ') << std::setw(64) << "|" << endl;
  }
  cout << "|" << std::setfill(' ') << std::setw(30);
  cout << "-" << std::setfill('-') << std::setw(34) << "|" << endl;
  cout << "| 1 - Import from file        |\n";
  cout << "| 2 - Manually enter invoices |\n";
  cout << std::setfill('-') << std::setw(31) << "-" << endl;
  cout << "  ";
  // END MENU

  // BEGIN USER INPUT
  std::string myStr; // used for general input
  int num; // used to take integer input
  bool exit = true; // condition for external do while loops
  bool innerExit = true;

  getline(cin, myStr);
  std::stringstream(myStr) >> num;

  // create HashTable and Invoice objects
  HashTable<Invoice> myInvoices(hashFunction);
  Invoice invoice;

  if (num == 1){
    std::string myFile;
    cout << "| What is the name of the file you would like to open? \n ";
    getline(cin, myFile);

    myInvoices.importTable(myFile);  // checking HashTable::importTable

    do{
      cout << "\n| 1 - Print Invoices\n";
      cout << "| 2 - Empty Invoices\n";
      cout << "| 3 - Search Invoices\n";
      cout << "| 4 - Exit\n  ";
      getline(cin, myStr);
      std::stringstream(myStr) >> num;

      switch (num){
      case 1:
        myInvoices.printTable(); // checking HashTable::printTable
        break;
      case 2:
        {
              myInvoices.empty(); // checking HashTable::empty
              cout << "| Would you like to update your database? [Y/N] \n ";
              getline(cin, myStr);
              if (myStr == "Y"){
                myInvoices.exportTable(myFile); // checking HashTable::exportTable
                cout << "\nYour file has been updated\n";
              }
              else if (myStr == "N"){
                cout << "\nYour file has not been updated\n";
              }
              else
              {
                cout << "\nThat is an unknown command\n";
              }
        }
        break;
      case 3:
        {
              do{
                cout << "| Enter the shipping number of the invoice you are looking for \n ";
                getline(cin, myStr);

                invoice.setShipNumber(myStr); // checking Invoice::setShipNumber
                myInvoices.retrieve(invoice); // checking HashTable::retrieve
                cout << "\n";
                invoice.outputInvoice(); // checking Invoice::outputInvoice

                cout << "\n| 1 - Remove Invoice\n";
                cout << "| 2 - Update Invoice\n";
                cout << "| 3 - Exit\n  ";
                getline(cin, myStr);
                std::stringstream(myStr) >> num;
                cout << "\n";
                switch (num){
                case 1:
                  myInvoices.remove(invoice); // checking HashTable::remove
                  cout << "Invoice removed\n";
                  break;
                case 2:
                {
                        std::string shipNum, shipType, dest, date, shDate;
                        double weight;

                        shipNum = invoice.getShippingNumber(); // checking Invoice::getShippingNumber
                        shDate = invoice.getShipDate(); // checking Invoice::getShipDate

                        cout << "| Enter invoice values:\n";
                        cout << "| Shipping type: ";
                        getline(cin, shipType);
                        cout << "| Destination: ";
                        getline(cin, dest);
                        cout << "| Purchase Date: ";
                        getline(cin, date);
                        cout << "| Weight: ";
                        getline(cin, myStr);
                        std::stringstream(myStr) >> weight;

                        Invoice temp(shipNum, shipType, dest, date, shDate, weight);

                        myInvoices.update(invoice, temp);
                        cout << "| Invoice updated\n";
                }
                  break;
                case 3:
                  cout << "| Exiting. . .\n";
                  innerExit = false;
                  break;
                default:
                  cout << "| That is an unknown command\n";
                  break;
                }

                cout << "\n| Finished? [Y/N] \n ";
                getline(cin, myStr);

                (myStr == "Y") ? (innerExit = false) : (innerExit = true);

              } while (innerExit);

              cout << "| Would you like to update your database? [Y/N] \n ";
              getline(cin, myStr);
              if (myStr == "Y"){
                myInvoices.exportTable(myFile); // checking HashTable::exportTable
                cout << "\nYour file has been updated\n";
              }
              else if (myStr == "N"){
                cout << "\n| Your file has not been updated\n";
              }
              else
              {
                cout << "\n| That is an unknown command\n";
              }
        }
        break;
      case 4:
        cout << "\n| exiting Invoice Manager. . .\n";
        exit = false;
        break;
      default:
        cout << "\n| That is an unknown command\n";
        break;
      }

    } while (exit);
  }
  else if (num == 2){
    do{
      std::string shType, dest, date, lbs;
      double weight;

      cout << "| Enter invoice values \n";

      cout << "| Shipping type: ";
      getline(cin, shType);

      cout << "| Destination: ";
      getline(cin, dest);

      cout << "| Purchase Date: ";
      getline(cin, date);

      cout << "| Weight: ";
      getline(cin, lbs);
      std::stringstream(lbs) >> weight;

      invoice.fillInvoice(shType, dest, date, weight);
      myInvoices.insert(invoice); // checking HashTable::insert

      // check for loop continuation
      cout << "\n| Finished? [Y/N] \n ";
      getline(cin, myStr);

      (myStr == "Y") ? (innerExit = false) : (innerExit = true);

    } while (innerExit);

    cout << "| Would you like to export these values into a file? [Y/N] \n ";
    getline(cin, myStr);

    if (myStr == "Y"){
      cout << "| What is the name of the file you would like to save to? \n ";
      getline(cin, myStr);
      myInvoices.exportTable(myStr); // checking HashTable::exportTable
      cout << "| Invoices saved to " << myStr << "\n| Exiting. . .";
    }
    else if (myStr == "N")
    {
      cout << "| Okay, these invoices will be lost.\n ";
    }
    else
    {
      cout << "| That is an unknown command\n";
    }
  }
  else
  {
    cout << "| That is an unknown command\n";
  }
  // END USER INPUT

  system("pause");
  return 0;
}


int hashFunction(const Invoice &obj){
  unsigned int sum = 0;
  int seed = 107;
  std::string shipNumber = obj.getShippingNumber(); // checking Invoice::getShippingNumber
  for (int i = 0; i < int(shipNumber.length()); i++){
    sum = (sum * seed) + shipNumber[i];
  }
  
  return sum % 53;
}