// HashTable.cpp
// Mark A. Nickerson
// Term Project
// May 19th, 2016
// COMSC 210

#include "stdafx.h" // precompiler directive

#include <fstream>

#include <sstream>

template<class T>
HashTable<T>::HashTable(int(*hashFunc)(const T &))
{
  hashFunction = hashFunc;
}

template<class T>
HashTable<T>::~HashTable()
{
  empty();
}

template<class T>
bool HashTable<T>::insert(const T &element)
{
  int index = hashFunction(element);
  if (index < 0 || index >= SIZE){
    return false;
  }
  table[index].push(element);
  return true;
}

//------------------BEGIN FILE MANAGEMENT------------------//
template<class T>
void HashTable<T>::exportTable(const std::string fileName)
{
  std::streambuf *buf, *backup; //create two new buffers
  backup = std::cout.rdbuf(); // save current cout buffer to backup buffer
  std::ofstream file;
  file.open(fileName, std::ios::trunc);

  buf = file.rdbuf(); // set buffer to the file's buffer
  std::cout.rdbuf(buf); // redirect buffer of cout to buf

  for (int i = 0; i < SIZE; i++){
    table[i].print(); // prints to cout and thusly the file
  }
  
  std::cout.rdbuf(backup); // redirects cout buffer to backup (the original cout buffer)
  file.close();
}

template<class T>
bool HashTable<T>::importTable(const std::string fileName)
{
  std::string str, token;
  std::string delimiter = ",";

  // values to store file generated input and construct object
  std::string val1, val2, val3, val4, val5;
  double val6;

  std::ifstream file(fileName);
  int i = 0;

  if (file.is_open()){
    while (getline(file, str)){

      // populate shipNumber
      token = str.substr(0, str.find(delimiter));
      val1 = token;
      str.erase(0, str.find(delimiter) + delimiter.length());

      //populate shipType
      token = str.substr(0, str.find(delimiter));
      val2 = token;
      str.erase(0, str.find(delimiter) + delimiter.length());

      //populate destination (street/city)
      token = str.substr(0, str.find(delimiter));
      val3 = token + ",";
      str.erase(0, str.find(delimiter) + delimiter.length());

      // populate destination (state/zip)
      token = str.substr(0, str.find(delimiter));
      val3 += token;
      str.erase(0, str.find(delimiter) + delimiter.length());

      // populate buyDate
      token = str.substr(0, str.find(delimiter));
      val4 = token;
      str.erase(0, str.find(delimiter) + delimiter.length());

      // populate shipDate
      token = str.substr(0, str.find(delimiter));
      val5 = token;
      str.erase(0, str.find(delimiter) + delimiter.length());

      //populate weight
      token = str.substr(0, str.find(delimiter));
      std::stringstream(token) >> val6;
      str.erase(0, str.find(delimiter) + delimiter.length());

      T data(val1, val2, val3, val4, val5, val6);
      insert(data);
      i++;
    }
    file.close();
    return true;
  }
  return false;
}

//-------------------END FILE MANAGEMENT-------------------//

template<class T>
bool HashTable<T>::retrieve(T &element)
{
  int index = hashFunction(element);
  if (index < 0 || index >= SIZE){
    return false;
  }
  if (!table[index].peek(element) || table[index].isEmpty()){
    return false;
  }
  return true;
}

template<class T>
bool HashTable<T>::remove(T &element)
{
  int index = hashFunction(element);
  if (index < 0 || index >= SIZE){
    return false;
  }
  if (!table[index].pop(element) || table[index].isEmpty()){
    return false;
  }
  return true;
}

template<class T>
bool HashTable<T>::update(T &oldEle, T &newEle)
{
  int index = hashFunction(oldEle);
  if (index < 0 || index >= SIZE){
    return false;
  }
  if (!table[index].update(oldEle)){
    return false;
  }
  if (!insert(newEle)){
    return false;
  }

  return true;
}

template<class T>
void HashTable<T>::empty()
{
  for (int i = 0; i < SIZE; i++){
    table[i].makeEmpty();
  }
}

template<class T>
void HashTable<T>::printTable()
{
  std::cout << std::endl;
  for (int i = 0; i < SIZE; i++){
    std::cout << "AT INDEX [" << i << "]:\n";
    table[i].print();
    std::cout << std::endl;
  }
}

template<class T>
bool HashTable<T>::printBox(T &element)
{
  int index = hashFunction(element);
  if (index < 0 || index >= SIZE){
    return false;
  }
  
  table[index].print();
  return true;
}