// List.cpp
// Mark A. Nickerson
// Term Project
// May 19th, 2016
// COMSC 210

#include "stdafx.h" // precompiler directive

template <class T>
List<T>::List()
{
  top = current = NULL;
}

template <class T>
List<T>::~List()
{
  makeEmpty();
}

template <class T>
void List<T>::push(T element)
{
  current = NULL;
  Node<T> *newNode = new Node<T>;
  newNode->element = element;
  newNode->next = top;
  top = newNode;
}

template <class T>
bool List<T>::pop(T &element)
{
  if (isEmpty()){
    return false;
  }

  Node<T> *tmp = top;
  if (tmp->element == element){
    element = tmp->element;
    top = top->next;
    delete tmp;
    return true;
  }
  while (tmp->next != NULL){
    if (tmp->next->element == element){
      Node<T> *ptr = tmp->next;
      element = ptr->element;
      tmp->next = ptr->next;
      delete ptr;
      return true;
    }
    tmp = tmp->next;
  }
  return false;
}

template <class T>
bool List<T>::peek(T &element)
{
  
  if (isEmpty()){
    return false;
  }

  T temp = top->element;
  current = top;
  do{
    if (temp == element){
      element = temp;
      return true;
    }
    
  } while (getNext(temp));

  element = current->element;
  return true;
}

template <class T>
bool List<T>::update(T &element)
{
  T tmp = element;
  if (pop(tmp)){
    return true;
  }
  return false;
}

template <class T>
inline bool List<T>::getNext(T &element)
{
  if (current == NULL){
    return false;
  }
  if (current->next == NULL){
    current = NULL;
    return false;
  }
  current = current->next;
  element = current->element;
  return true;
}

template <class T>
bool List<T>::isEmpty() const
{
  if (top == NULL){
    return true;
  }
  return false;
}

template <class T>
void List<T>::makeEmpty()
{
  while (top != NULL){
    Node<T> *ptr = top;
    top = top->next;
    delete ptr;
  }
  
}

template <class T>
bool List<T>::print()
{
  if (isEmpty()){
    return false;
  }
  Node<T> *temp = top;
  while (temp != NULL){
    std::cout << temp->element << "\n";
    temp = temp->next;
  }
  return true;
}