#ifndef LINESTRUCT_H_INCLUDED
#define LINESTRUCT_H_INCLUDED
#include "common.h"
#include "Series.h"      
#include "DataAccess.h"     
#include "Array.h"      


template <class Element>
class LineStruct : virtual public Series<Element>,virtual public DataAccess<Element>
{
public:

 
 LineStruct();
 
 LineStruct(const LineStruct<Element>& that);
 
 virtual void Clear();
 
 virtual ~LineStruct();
 
 const LineStruct<Element>& operator= (const LineStruct<Element>& that);
 
 bool operator== (const LineStruct<Element>& that)const;
public:

 
 virtual bool First()const;
 
 virtual bool Last()const;
 
 virtual bool Prior()const;
 
 virtual bool Next()const;
 
 virtual Element& GetCurrent();
 virtual const Element& GetCurrent()const;
public:

 
 virtual bool SearchFirst(Element& data);
 
 virtual bool SearchNext(Element& data);
 
 virtual bool Modify(Element old_data,Element new_data);
public:

public:

 
 virtual bool IsEmpty()const;
 
 virtual SIZE_TYPE Length()const;

 virtual Element& operator [] (SIZE_TYPE i);
 virtual const Element& operator[] (SIZE_TYPE i)const;
protected:

    Array<Element> array;               
 SIZE_TYPE length;     
 mutable SIZE_TYPE current_pos;  
 SIZE_TYPE search_pos;    
protected:
 
 void Copy(const LineStruct<Element>& that);
};



 
template<class Element>
LineStruct<Element>::LineStruct()
{
 this->Clear();
 
}
 
template<class Element>
LineStruct<Element>::LineStruct(const LineStruct<Element>& that)
{
 this->Copy(that);
}
 
template<class Element>
void LineStruct<Element>::Clear()
{
 this->length=0;
 this->current_pos=0;
 this->search_pos=0;
 
}
 
template<class Element>
LineStruct<Element>::~LineStruct()
{
 this->Clear();
 
}
 
template<class Element>
void LineStruct<Element>::Copy(const LineStruct<Element>& that)
{
 this->Clear();
 this->array=that.array;
 this->length=that.length;
}
 
template<class Element>
const LineStruct<Element>& LineStruct<Element>::operator= (const LineStruct<Element>& that)
{
 this->Copy(that);
 return (*this);
}

 
template<class Element>
bool LineStruct<Element>::IsEmpty()const
{
 return this->Length()==0;
}
 
template<class Element>
SIZE_TYPE LineStruct<Element>::Length()const
{
 return this->length;
}
 
template<class Element>
Element& LineStruct<Element>::operator [] (SIZE_TYPE i)
{
    
    if(1<=i && i<=this->Length())
    {
        
        return this->array[i-1];
    }
    else
    {
        
        throw this;
    }
}
 
template<class Element>
const Element& LineStruct<Element>::operator [] (SIZE_TYPE i)const
{
    
    if(1<=i && i<=this->Length())
    {
        
        return this->array[i-1];
    }
    else
    {
        
        throw this;
    }
}

 
template<class Element>
bool LineStruct<Element>::First()const
{
 if(this->IsEmpty()) return false;
 this->current_pos=1;
 return true;
}
 
template<class Element>
bool LineStruct<Element>::Last()const
{
 if(this->IsEmpty()) return false;
 this->current_pos=this->Length();
 return true;
}
 
template<class Element>
bool LineStruct<Element>::Prior()const
{
 
 if(this->current_pos>1)
 {
  --this->current_pos;
  return true;
 }
 return false;
}
 
template<class Element>
bool LineStruct<Element>::Next()const
{
 
 if(this->current_pos<this->Length() && this->current_pos!=0)
 {
   ++this->current_pos;
  return true;
 }
 return false;
}
 
template<class Element>
Element& LineStruct<Element>::GetCurrent()
{
 
 return this->operator [](this->current_pos);
}
 
template<class Element>
const Element& LineStruct<Element>::GetCurrent()const
{
 
 return this->operator [](this->current_pos);
}

template<class Element>
bool LineStruct<Element>::SearchFirst(Element& data)
{
 
 this->search_key=data;
    
    for(this->search_pos=1; this->search_pos<=this->Length(); this->search_pos++)
 {
        
        if(this->search_key==this->operator[](this->search_pos))
  {
   data=this->operator[](this->search_pos);
   return true;
  }
 }
    this->search_pos=0;
    return false;
}


template<class Element>
bool LineStruct<Element>::SearchNext(Element& data)
{
 
 if(this->search_pos==0) return false;
    
    for(this->search_pos++; this->search_pos<=this->Length(); this->search_pos++)
 {
        
        if(this->search_key==this->operator[](this->search_pos))
  {
   data=this->operator[](this->search_pos);
   return true;
  }
 }
 this->search_pos=0;
    return false;
}


template<class Element>
bool LineStruct<Element>::Modify(Element old_data,Element new_data)
{
    
    for(SIZE_TYPE i=1; i<=this->Length(); i++)
 {
        
        if(old_data==this->operator[](i))
  {
   this->operator[](i)=new_data;
   return true;
  }
 }
    return false;
}


template<class Element>
bool LineStruct<Element>::operator== (const LineStruct<Element>& that)const
{
 if(this->Length()!=that.Length()) return false;
 for(SIZE_TYPE i=1; i<=this->Length(); i++)
  if(!(this->operator[](i)==that[i])) return false;
 return true;
}



#endif 
