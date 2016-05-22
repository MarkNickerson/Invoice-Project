// List.hpp
// Mark A. Nickerson
// Term Project
// May 19th, 2016
// COMSC 210

#ifndef LIST_HPP
#define LIST_HPP

template <class T>
struct Node{
  T element;
  Node<T> *next;
};

template <class T>
class List
{
public:
  List();
  ~List();
  void push(T element);
  bool pop(T &element);
  bool peek(T &element);
  bool update(T &element);
  inline bool getNext(T &element);
  bool isEmpty() const;
  void makeEmpty();
  bool print();
private:
  Node<T> *top;
  Node<T> *current;
};
#include "List.cpp"
#endif