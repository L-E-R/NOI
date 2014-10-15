#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED
#include "common.h"
#include "LineStruct.h"     


template <class Element>
class Queue : public LineStruct<Element>
{
public:
 
 Queue();
 
 Queue(const Queue<Element>& that);
 
 const Queue<Element>& operator= (const Queue<Element>& that);
 
 virtual void Clear(void);
public:

 
 virtual bool Insert(Element e);
 
 virtual bool Delete(Element& e);
public:
 
 virtual Element& GetTop();
 
 virtual bool Enter(Element e);
 
 virtual bool Exit(Element& e);
protected:
 
 virtual Element& operator [] (SIZE_TYPE i);
public:
 virtual const Element& operator[] (SIZE_TYPE i)const;
protected:
 SIZE_TYPE offset;    
};



template <class Element>
Queue<Element>::Queue()
{
 this->Clear();
}


template <class Element>
Queue<Element>::Queue(const Queue<Element>& that)
{
 this->Copy(that);
 this->offset=that.offset;
}


template <class Element>
const Queue<Element>& Queue<Element>::operator= (const Queue<Element>& that)
{
 this->Copy(that);
 this->offset=that.offset;
 return (*this);
}


template <class Element>
void Queue<Element>::Clear()
{
 LineStruct<Element>::Clear();
 this->offset=0;
}



template <class Element>
bool Queue<Element>::Insert(Element e)
{
 return this->Enter(e);
}

template <class Element>
bool Queue<Element>::Delete(Element& e)
{
 return this->Exit(e);
}


template <class Element>
Element& Queue<Element>::GetTop()
{
 return this->operator[](1);
}


template <class Element>
bool Queue<Element>::Enter(Element e)
{
 this->operator[](++this->length)=e;
 return true;
}


template <class Element>
bool Queue<Element>::Exit(Element& e)
{
 if(this->IsEmpty())return false;

 e=this->operator[](1);
 this->offset++;
 this->length--;
 
 if(this->offset!=0 && this->offset>=2*this->length)
 {
  for(SIZE_TYPE i=0; i<this->length; i++)
   this->array[i]=this->array[this->offset+i];
  this->offset=0;
 }
 return true;
}


template <class Element>
Element& Queue<Element>::operator [] (SIZE_TYPE i)
{
 if(i<1 || i>this->length) throw this;
 return this->array[this->offset+i-1];
}

template <class Element>
const Element& Queue<Element>::operator [] (SIZE_TYPE i)const
{
 if(i<1 || i>this->length) throw this;
 return this->array[this->offset+i-1];
}


#endif 
