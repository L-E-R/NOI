#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include "common.h"
#include "LineStruct.h"     

template <class Element>
class Stack : public LineStruct<Element>
{
public:
 
 Stack(){};
 
 Stack(const Stack<Element>& that);
 
 const Stack<Element>& operator= (const Stack<Element>& that);
public:

 
 virtual bool Insert(Element e);
 
 virtual bool Delete(Element& e);
protected:
 
 virtual Element& operator [] (SIZE_TYPE i)
 {
  return LineStruct<Element>::operator[](i);
 }
public:
 virtual const Element& operator [] (SIZE_TYPE i)const
 {
  return LineStruct<Element>::operator[](i);
 }
public:
 
 virtual bool Push(Element e);
 
 virtual bool Pop(Element& e);
 
 virtual Element& GetTop(void);
};



template <class Element>
Stack<Element>::Stack(const Stack<Element>& that)
{
 this->Copy(that);
}

template <class Element>
const Stack<Element>& Stack<Element>::operator= (const Stack<Element>& that)
{
 this->Copy(that);
 return (*this);
}

template <class Element>
bool Stack<Element>::Insert(Element e)
{
 return this->Push(e);
}

template <class Element>
bool Stack<Element>::Delete(Element& e)
{
 return this->Pop(e);
}

template <class Element>
bool Stack<Element>::Push(Element e)
{
    this->length++;
 this->operator[](this->length)=e;
 return true;
}

template <class Element>
bool Stack<Element>::Pop(Element& e)
{
 if(this->IsEmpty()) return false;
 e=this->operator[](this->length);
    this->length--;
 return true;
}

template <class Element>
Element& Stack<Element>::GetTop()
{
 return this->operator[](this->length);
}


#endif 
