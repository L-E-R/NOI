#ifndef ORDEREDLIST_H_INCLUDED
#define ORDEREDLIST_H_INCLUDED
#include "common.h"
#include "List.h"      

template <class Element>
class OrderedList : public List<Element>
{
public:
 OrderedList(){};
 
 OrderedList(const OrderedList<Element>& that);
 
 const OrderedList<Element>& operator= (const OrderedList<Element>& that);
public:


 
 virtual bool SearchFirst(Element& e);
 
 virtual bool SearchNext(Element& e);
 
 virtual bool Insert(Element e);
 
 virtual bool Delete(Element& e);
 
 virtual bool Modify(Element olde,Element newe);

 
 virtual SIZE_TYPE Locate(Element e)const;
 
 virtual SIZE_TYPE Locate(Element e,bool (*compare)(Element a,Element b))const;
protected:
    
    

 
 virtual bool Insert(SIZE_TYPE i,Element e);
 
 virtual bool Remove(SIZE_TYPE i);
 
 virtual bool Update(SIZE_TYPE i,Element e);
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
private:
    
    SIZE_TYPE BSearch(Element e,SIZE_TYPE low,SIZE_TYPE high)const;
};



template <class Element>
OrderedList<Element>::OrderedList(const OrderedList<Element>& that)
{
 this->Copy(that);
}


template <class Element>
const OrderedList<Element>& OrderedList<Element>::operator= (const OrderedList<Element>& that)
{
 this->Copy(that);
 return (*this);
}


template <class Element>
bool OrderedList<Element>::SearchFirst(Element& e)
{
 
    
 
 this->search_key=e;
 SIZE_TYPE i=this->BSearch(e,1,this->Length());
 if(1<=i && i<=this->Length())
 {
  if(this->search_key==this->operator[](i))
  {
   while(i-1>=1 && this->search_key==this->operator[](i-1)) i--;
   this->search_pos=i;
   e=this->operator[](i);
   return true;
  }
  else
  {
   return false;
  }
 }
 else
 {
  return false;
 }
}


template <class Element>
bool OrderedList<Element>::SearchNext(Element& e)
{
 
 if(this->search_pos==0) return false;
    
 this->search_pos++;
    
    if(this->search_pos<=this->Length() && this->search_key==this->operator[](this->search_pos))
 {
  e=this->operator[](this->search_pos);
  return true;
 }
 else
 {
  this->search_pos=0;
  return false;
 }
}


template <class Element>
bool OrderedList<Element>::Insert(Element e)
{
    
 SIZE_TYPE i;
 


 i=this->BSearch(e,1,this->Length());
    
 return this->Insert(i,e);
}


template <class Element>
bool OrderedList<Element>::Delete(Element& e)
{
 
    SIZE_TYPE i=this->Locate(e);
 
 if(i!=0)
  return this->Remove(i);
 else
  return false;
}


template <class Element>
bool OrderedList<Element>::Modify(Element olde,Element newe)
{
    
    
    if(this->Delete(olde))
  return this->Insert(newe);
 else
  return false;
}


template <class Element>
SIZE_TYPE OrderedList<Element>::Locate(Element e)const
{
 
 
 SIZE_TYPE i=this->BSearch(e,1,this->Length());
 return ((e==this->operator[](i))?i:0);
}

template<class Element>
SIZE_TYPE OrderedList<Element>::Locate(Element e,bool (*compare)(Element a,Element b))const
{
    
    for(SIZE_TYPE i=1; i<=this->Length(); i++)
        
        if((*compare)(e,this->operator[](i))) return i;
    return 0;
}

template <class Element>
inline bool OrderedList<Element>::Insert(SIZE_TYPE i,Element e)
{
 return List<Element>::Insert(i,e);
}


template <class Element>
inline bool OrderedList<Element>::Remove(SIZE_TYPE i)
{
 return List<Element>::Remove(i);
}


template <class Element>
inline bool OrderedList<Element>::Update(SIZE_TYPE i,Element e)
{
 return List<Element>::Update(i,e);
}


template <class Element>
SIZE_TYPE OrderedList<Element>::BSearch(Element e,SIZE_TYPE low,SIZE_TYPE high)const
{
    
    if(low<=high)
    {
        
        SIZE_TYPE mid=(low+high)/2;
        
        Element mide=this->operator[](mid);
        
        if(e==mide)
            
            return mid;
        else if(e>mide)
            
            return this->BSearch(e,mid+1,high);
        else 
            
            return this->BSearch(e,low,mid-1);
    }
    
 
 
 
 return low;
}


#endif 
