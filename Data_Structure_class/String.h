#ifndef STRING_H_INCLUDED
#define STRING_H_INCLUDED
#include "common.h"
#include "Array.h"
#include "List.h"


template <class TYPE>
class String: public List<TYPE>
{
public:
 
 String(){};
 
 String(const String<TYPE>& that);
 
 String(String<TYPE>& that,SIZE_TYPE from);
 
 String(String<TYPE>& that,SIZE_TYPE from,SIZE_TYPE length);
 
 const String<TYPE>& operator= (const String<TYPE> &that);
public:
 
 int CompareString(String<TYPE>& that);
 
 int CompareString(SIZE_TYPE from,String<TYPE>& that);
 
 int CompareString(SIZE_TYPE from,String<TYPE>& that,SIZE_TYPE start);
 
 int CompareString(SIZE_TYPE from,String<TYPE>& that,SIZE_TYPE start,SIZE_TYPE length);
public:
 
 void Reverse();
 
 SIZE_TYPE SearchSubString(String<TYPE>& sub_string,SIZE_TYPE from=1);
 
 String<TYPE> operator+ (String<TYPE>& that);
 String<TYPE> operator+= (String<TYPE>& that);
public:

protected:
 
 void Copy(String<TYPE>& that,SIZE_TYPE from,SIZE_TYPE length);
    
    void ParseMode(Array<SIZE_TYPE>& next);
};


template <class TYPE>
String<TYPE>::String(const String<TYPE>& that)
{
 LineStruct<TYPE>::Copy(that);
}


template <class TYPE>
String<TYPE>::String(String<TYPE>& that,SIZE_TYPE from)
{
 this->Copy(that,from,((that.Length()>=from)?(that.Length()-from+1):0));
}


template <class TYPE>
String<TYPE>::String(String<TYPE>& that,SIZE_TYPE from,SIZE_TYPE length)
{
 this->Copy(that,from,length);
}


template <class TYPE>
void String<TYPE>::Copy(String<TYPE>& that,SIZE_TYPE from,SIZE_TYPE length)
{
 SIZE_TYPE i,j;
 this->length=(from+length>that.Length())?((from>that.Length())?0:that.Length()-from+1):length;
 for(i=1,j=from; i<=this->length; i++)
  this->operator[](i)=that[j++];
}


template <class TYPE>
const String<TYPE>& String<TYPE>::operator= (const String<TYPE>& that)
{
 LineStruct<TYPE>::Copy(that);
 return(*this);
}


template <class TYPE>
String<TYPE> String<TYPE>::operator+ (String<TYPE>& that)
{
 String<TYPE> result(*this);
 for(SIZE_TYPE i=1; i<=that.Length(); i++)
  result.Insert(that[i]);
 return result;
}
template <class TYPE>
String<TYPE> String<TYPE>::operator+= (String<TYPE>& that)
{
 for(SIZE_TYPE i=1; i<=that.Length(); i++)
  this->Insert(that[i]);
 return (*this);
}

template <class TYPE>
SIZE_TYPE String<TYPE>::SearchSubString(String<TYPE>& sub_string,SIZE_TYPE from)
{
#ifdef DEBUG
 SIZE_TYPE length=sub_string.Length();
 if(direction_reverse)
 {
  for(SIZE_TYPE i=(from<length)?:0:from-length+1; i>0; i--)
  {
   if(this->CompareString(i,sub_string,1,length)==0) return i;
  }
  return 0;
 }
 else
 {
  for(SIZE_TYPE i=from; i<=this->Length()-length+1;i++)
   if(this->CompareString(i,sub_string,1,length)==0) return i;
  return 0;
 }
#else 

    
    Array<SIZE_TYPE> next;           
    SIZE_TYPE i=from;                
    SIZE_TYPE j=1;                   
    
    sub_string.ParseMode(next);
    
    while(i<=this->Length() && j<=sub_string.Length())
    {
        if(j==0 || this->operator[](i)==sub_string[j])
        {
            i++;
            j++;
        }
        else
            j=next[j];
    }
    
    if(j>sub_string.Length())
        return i-sub_string.Length();
    
    else
        return 0;
#endif 
}


template <class TYPE>
int String<TYPE>::CompareString(String<TYPE>& that)
{
 this->CompareString(1,that);
}

template <class TYPE>
int String<TYPE>::CompareString(SIZE_TYPE from,String<TYPE>& that)
{
 this->CompareString(1,that,1);
}

template <class TYPE>
int String<TYPE>::CompareString(SIZE_TYPE from,String<TYPE>& that,SIZE_TYPE start)
{
 this->CompareString(from,that,start,(this->Length()-from>that.Length()-start)?(that.Length()-start+2):(this->Length()-from+2));
}

template <class TYPE>
int String<TYPE>::CompareString(SIZE_TYPE from,String<TYPE>& that,SIZE_TYPE start,SIZE_TYPE length)
{
 SIZE_TYPE i,j;
 for(i=from,j=start; i<=this->Length() && j<=that.Length() && length && (*this)[i]==that[j]; length--,i++,j++);
 if(length==0) return 0;
 if(i<=this->Length() && j<=that.Length()) return(((*this)[i]>that[j])?1:-1);
 if(i<=this->Length()) return(1);
 return (-1);
}

template <class TYPE>
void String<TYPE>::ParseMode(Array<SIZE_TYPE>& next)
{
    SIZE_TYPE i=1;
    SIZE_TYPE j=0;
    next[1]=0;
    while(i<this->Length())
    {
        if(j==0 || this->operator[](i)==this->operator[](j))
        {
            i++; j++;
            if(this->operator[](i)==this->operator[](j))
            {
                next[i]=next[j];
            }
            else    
            {
                next[i]=j;
            }
        }
        else
        {
            j=next[j];
        }
    }
}

template <class TYPE>
void String<TYPE>::Reverse()
{
 SIZE_TYPE i,j;
 TYPE t;
 for(i=1,j=this->Length(); i<j; i++,j--)
 {
  t=(*this)[i];
  (*this)[i]=(*this)[j];
  (*this)[j]=t;
 }
}



#endif 
