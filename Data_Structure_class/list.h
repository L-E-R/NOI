#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include "common.h"
#include "LineStruct.h"     


template <class Element>
class List : public LineStruct<Element>
{
public:
 
 List(){};
 
 List(const List<Element>& that);
 
 const List<Element>& operator= (const List<Element>& that);
public:


 
 virtual bool Insert(Element data);
 
 virtual bool Delete(Element& data);

 
 virtual bool Insert(SIZE_TYPE i,Element e);
 
 virtual bool Remove(SIZE_TYPE i);
 
 virtual bool Update(SIZE_TYPE i,Element e);

 
 virtual SIZE_TYPE Locate(Element e)const;

};



template<class Element>
List<Element>::List(const List<Element>& that)
{
 
 this->Copy(that);
}


template<class Element>
const List<Element>& List<Element>::operator= (const List<Element>& that)
{
 
 this->Copy(that);
 return (*this);
}

 
template<class Element>
SIZE_TYPE List<Element>::Locate(Element e)const
{
    
    for(SIZE_TYPE i=1; i<=this->Length(); i++)
        
        if(e==this->operator[](i)) return i;
    return 0;
}
 
template<class Element>
bool List<Element>::Insert(SIZE_TYPE i,Element e)
{
    
    if(1<=i && i<=this->Length()+1)
    {
        
        for(SIZE_TYPE j=this->Length(); j>=i; j--)
            
            this->array[j]=this->array[j-1];
        
        this->array[i-1]=e;
        
        this->length++;
        
        return true;
    }
    
    return false;
}
 
template<class Element>
bool List<Element>::Remove(SIZE_TYPE i)
{
    
    if(1<=i && i<=this->Length())
    {
        
        for(SIZE_TYPE j=i; j<this->Length(); j++)
            
            this->array[j-1]=this->array[j];
        
        this->length--;
        
        return true;
    }
    
    return false;
}
 
template<class Element>
bool List<Element>::Update(SIZE_TYPE i,Element e)
{
 
    if(1<=i && i<=this->Length())
    {
        
        this->operator[](i)=e;
        
        return true;
    }
    
    return false;
}

template<class Element>
bool List<Element>::Insert(Element e)
{
    
    return(this->Insert((this->Length()+1),e));
}

template<class Element>
bool List<Element>::Delete(Element& e)
{
    
 SIZE_TYPE i = this->Locate(e);
    
    if(1<=i && i<=this->Length())
 {
  
  e=this->operator[](i);
  
  this->operator[](i)=this->operator[](this->Length());
        
        this->length--;
  
  return true;
 }
 
 return false;
}

#endif 
