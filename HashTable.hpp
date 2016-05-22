// HashTable.hpp
// Mark A. Nickerson
// Term Project
// May 19th, 2016
// COMSC 210

#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <string>

#include "List.hpp"

const int SIZE = 53;

template<class T>
class HashTable
{
public:
  HashTable(int(*hashFunc)(const T &));
  ~HashTable();
  bool insert(const T &element);
  void exportTable(const std::string fileName); // file management
  bool importTable(const std::string fileName); // file management
  bool retrieve(T &element);
  bool remove(T &element);
  bool update(T &oldEle, T &newEle);
  void empty();
  void printTable();
  bool printBox(T &element);
private:
  List<T> table[SIZE];
  int(*hashFunction)(const T &); // pointer to a function
};
#include "HashTable.cpp"
#endif