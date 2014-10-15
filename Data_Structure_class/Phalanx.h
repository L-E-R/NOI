#ifndef PHALANX_H_INCLUDED
#define PHALANX_H_INCLUDED
#include "common.h"
#include "Array.h"

template <class TYPE>
class Phalanx
{
public:
 
 Phalanx():size(0){};
 
 Phalanx(SIZE_TYPE N):datas(N*N),size(N){};
 
 Phalanx(const Phalanx<TYPE>& that):datas(that.datas),size(that.size){};
 
 const Phalanx<TYPE>& operator= (const Phalanx<TYPE>& that)
 {
  this->datas=that.datas;
  this->size=that.size;
  return (*this);
 };
    bool operator== (const Phalanx<TYPE>& that)const
    {
        return (this->size==that.size && this->datas==that.datas);
    }
public:
 
 TYPE& operator()(SIZE_TYPE row,SIZE_TYPE column)
 {
  this->size=(this->size < row+1) ? row+1 : this->size;
  this->size=(this->size < column+1) ? column+1 : this->size;
  return this->datas[this->GetAddress(row,column)];
 };
 const TYPE& operator() (SIZE_TYPE row,SIZE_TYPE column)const
 {
  if(row<0 || row>=this->size || column<0 || column>=this->size) throw this;
  
  return this->datas[this->GetAddress(row,column)];
 };
 
 SIZE_TYPE length()const
 {
  return this->size;
 };
protected:
 Array<TYPE> datas; 
 SIZE_TYPE size;  
protected:
 
 SIZE_TYPE GetAddress(SIZE_TYPE row,SIZE_TYPE column)const
 {
  
  
  
  
  return ((row<column)?(column*(column+1)+column-row):(row*(row+1)+column-row));
 };
};


#endif 
