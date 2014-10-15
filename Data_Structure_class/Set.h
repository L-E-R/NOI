#ifndef SET_H_INCLUDED
#define SET_H_INCLUDED


















#include "common.h"
#include "DataAccess.H"
#include "Series.H"
#include "List.H"
#include "OrderedList.H"
#include <stdarg.h>


template <class TYPE>
class Set : virtual public Series<TYPE>,virtual public DataAccess<TYPE>
{

public:
 
 virtual bool SearchFirst(TYPE& data);
 
 virtual bool SearchNext(TYPE& data);
 
 virtual bool Insert(TYPE data);
 
 virtual bool Delete(TYPE& data);
 
 virtual bool Modify(TYPE old_data,TYPE new_data);

public:
 
 virtual bool First();
 
 virtual bool Last();
 
 virtual bool Prior();
 
 virtual bool Next();
 
 virtual TYPE& GetCurrent();

public:
 
 bool IsEmpty()const;
 
 void Clear();
 
 SIZE_TYPE Length()const;
 
 bool Has(TYPE element);
 
 bool IsSubSetOf(Set<TYPE>& that);
 
 bool operator== (Set<TYPE>& that);
 
 Set<TYPE> operator+ (Set<TYPE>& that);
 
 Set<TYPE> operator* (Set<TYPE>& that);
 
 Set<TYPE> operator- (Set<TYPE>& that);
 
 Set();
 Set(int len,TYPE e,...);
 
 Set(const Set<TYPE>& that);
 const Set<TYPE>& operator= (const Set<TYPE> &that);

protected:
 
 OrderedList<TYPE> datas;
};




template <class TYPE>
bool Set<TYPE>::SearchFirst(TYPE& data)
{
 return this->datas.SearchFirst(data);
}

template <class TYPE>
bool Set<TYPE>::SearchNext(TYPE& data)
{
 
 return false;
}

template <class TYPE>
bool Set<TYPE>::Insert(TYPE data)
{
 
 if(!this->Has(data))
  return this->datas.Insert(data);
 return false;
}

template <class TYPE>
bool Set<TYPE>::Delete(TYPE& data)
{
 
 if(this->Has(data))
  return this->datas.Delete(data);
 return false;
}

template <class TYPE>
bool Set<TYPE>::Modify(TYPE old_data,TYPE new_data)
{
 
 if(this->Has(old_data) && !this->Has(new_data))
 {
  this->Delete(old_data);
  this->Insert(new_data);
  return true;
 }
 return false;
}


template <class TYPE>
bool Set<TYPE>::First()
{
 return this->datas.First();
}

template <class TYPE>
bool Set<TYPE>::Last()
{
 return this->datas.Last();
}

template <class TYPE>
bool Set<TYPE>::Prior()
{
 return this->datas.Prior();
}

template <class TYPE>
bool Set<TYPE>::Next()
{
 return this->datas.Next();
}

template <class TYPE>
TYPE& Set<TYPE>::GetCurrent()
{
 return this->datas.GetCurrent();
}

template <class TYPE>
bool Set<TYPE>::IsEmpty()const
{
 return this->Length()==0;
}

template <class TYPE>
void Set<TYPE>::Clear()
{
 this->datas.Clear();
}

template <class TYPE>
SIZE_TYPE Set<TYPE>::Length()const
{
 return this->datas.Length();
}

template <class TYPE>
bool Set<TYPE>::Has(TYPE element)
{
 return this->datas.SearchFirst(element);
}

template <class TYPE>
bool Set<TYPE>::IsSubSetOf(Set<TYPE>& that)
{
 
 SIZE_TYPE i=1,j=1;
 while( i<=this->datas.Length() && j<=that.datas.Length() )
 {
  
  if(this->datas[i]==that.datas[j]) { i++; j++; }
  
  else if(this->datas[i]>that.datas[j]) { j++; }
  
  
  else  return false;
 }
 
 if(i<=this->datas.Length()) return false;
 
 return true;
}

template <class TYPE>
bool Set<TYPE>::operator== (Set<TYPE>& that)
{
 
 return this->datas==that.datas;
}

template <class TYPE>
Set<TYPE> Set<TYPE>::operator+ (Set<TYPE>& that)
{

 Set<TYPE> result;     
 List<TYPE>& list=result.datas;  
 TYPE a,b;       
 SIZE_TYPE i=1,j=1,k=1;    
 
 while( i<=this->datas.Length() && j<=that.datas.Length() )
 {
  
  a=this->datas[i];
  b=that.datas[j];
  
  if(a==b)
  {
   
   list.Insert(k++,a);
   
   i++;
   j++;
  }
  
  else if(a>b)
  {
   list.Insert(k++,b);
   j++;
  }
  else 
  {
   list.Insert(k++,a);
   i++;
  }
 }
 
 while(i<=this->datas.Length())
 {
  list.Insert(k++,this->datas[i++]);
 }
 while(j<=that.datas.Length())
 {
  list.Insert(k++,that.datas[j++]);
 }
 return result;
}

template <class TYPE>
Set<TYPE> Set<TYPE>::operator* (Set<TYPE>& that)
{

 Set<TYPE> result;     
 List<TYPE>& list=result.datas;  
 TYPE a,b;       
 SIZE_TYPE i=1,j=1,k=1;    
 
 while( i<=this->datas.Length() && j<=that.datas.Length() )
 {
  
  a=this->datas[i];
  b=that.datas[j];
  
  if(a==b)
  {
   list.Insert(k++,a);
   i++;
   j++;
  }
  
  else if(a>b)
  {
   j++;
  }
  else 
  {
   i++;
  }
 }
 return result;
}

template <class TYPE>
Set<TYPE> Set<TYPE>::operator- (Set<TYPE>& that)
{
 Set<TYPE> result;     
 List<TYPE>& list=result.datas;  
 TYPE a,b;       
 SIZE_TYPE i=1,j=1,k=1;    
 
 while( i<=this->datas.Length() && j<=that.datas.Length() )
 {
  
  a=this->datas[i];
  b=that.datas[j];
  
  if(a==b)
  {
   i++;
   j++;
  }
  
  else if(a>b)
  {
   j++;
  }
  
  else 
  {
   list.Insert(k++,a);
   i++;
  }
 }
 
 while(i<=this->datas.Length())
 {
  list.Insert(k++,this->datas[i++]);
 }
 return result;
}

template <class TYPE>
Set<TYPE>::Set()
{
 
}

template <class TYPE>
Set<TYPE>::Set(int len,TYPE e,...)
{
 va_list parameters;     
 va_start(parameters,len);   
 
 for(int i=0; i<len; i++)
 {
  
  TYPE element=va_arg(parameters,TYPE);
  
  this->Insert(element);
 }
 
 va_end(parameters);
}


template <class TYPE>
Set<TYPE>::Set(const Set<TYPE>& that)
{
 
 this->datas=that.datas;
}

template <class TYPE>
const Set<TYPE>& Set<TYPE>::operator= (const Set<TYPE>& that)
{
 
 this->datas=that.datas;
 
 return (*this);
}


#endif 
