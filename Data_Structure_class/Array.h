#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED
#include "common.h"      

const SIZE_TYPE INIT_SIZE=64;   



template<class TYPE>
struct BlockNode
{
public:
 SIZE_TYPE size;      
 TYPE *datas;      
 struct BlockNode<TYPE>* next;  
 
 BlockNode(SIZE_TYPE size);
 
 BlockNode(SIZE_TYPE size,TYPE init_data);
 
 BlockNode(const BlockNode<TYPE> &that);
 
 virtual ~BlockNode();
};




template <class TYPE>
BlockNode<TYPE>::BlockNode(SIZE_TYPE size)
{
 
 this->size=size;
 
 this->datas=new TYPE[this->size];
 
 if(!this->datas)
 {
  
  throw this;
 }
 
 this->next=0;
}


template <class TYPE>
BlockNode<TYPE>::BlockNode(SIZE_TYPE size,TYPE init_data)
{
 
 this->size=size;
 
 this->datas=new TYPE[this->size];
 
 if(!this->datas)
 {
  
  throw this;
 }
 
 for(SIZE_TYPE i=0; i<this->size; i++)
  this->datas[i]=init_data;
 
 this->next=0;
}


template <class TYPE>
BlockNode<TYPE>::BlockNode(const BlockNode<TYPE> &that)
{
 
 this->size=that.size;
 this->datas=new TYPE[this->size];
 if(!this->datas)
 {
  throw this;
 }
 
 for(SIZE_TYPE i=0; i<this->size; i++)
 {
  
  this->datas[i]=that.datas[i];
 }
 
 this->next=0;
}


template <class TYPE>
BlockNode<TYPE>::~BlockNode()
{
 
 if(this->datas)
 {
  delete []this->datas;
 }
 this->datas=0;
 this->size=0;
 this->next=0;
}



template <class TYPE>
class Array
{
public:
 


 

 Array(SIZE_TYPE init_size=0);

 
 Array(const Array<TYPE>& array);
 
 const Array<TYPE>& operator= (const Array<TYPE> &that);
 
 bool operator== (const Array<TYPE>& that)const;
 
 ~Array();
 
 TYPE& operator[] (SIZE_TYPE index);
 const TYPE& operator[](SIZE_TYPE index)const;
 
 SIZE_TYPE length()const;
    
    void Clear(){ this->Destroy(); };
protected:
 
 void Copy(const Array<TYPE>& that);
 
 void Destroy();
 
 TYPE*& GetAddress(SIZE_TYPE index)const;
protected:
 BlockNode<TYPE*> *blocks;   
 BlockNode<TYPE*> *tail;    
 SIZE_TYPE total_size;    
 SIZE_TYPE total_length;    
};






















template <class TYPE>
Array<TYPE>::Array(SIZE_TYPE init_size)
{
 
 if(init_size<=0)
 {
  this->blocks=0;
  this->tail=0;
  this->total_size=0;
 }
 else
 {
  
  this->blocks=new BlockNode<TYPE*>(init_size,0);
  
  this->tail=this->blocks;
  
  this->total_size=init_size;
 }
 
 this->total_length=0;
}


































template <class TYPE>
void Array<TYPE>::Copy(const Array<TYPE>& that)
{
 
 BlockNode<TYPE*> *p,*q;
 
 if(that.blocks)
 {
  
  p=that.blocks;
  this->blocks=new BlockNode<TYPE*>(p->size);
  for(SIZE_TYPE i=0; i<p->size; i++)
  {
   if(p->datas[i])
   {
    this->blocks->datas[i]=new TYPE;
    (*(this->blocks->datas[i]))=(*(p->datas[i]));
   }
   else
   {
    this->blocks->datas[i]=0;
   }
  }
  q=this->blocks;
  
  while(p->next!=0)
  {
   
   q->next=new BlockNode<TYPE*>(p->next->size);
   for(SIZE_TYPE i=0; i<p->next->size; i++)
   {
    if(p->next->datas[i]==0)
    {
     q->next->datas[i]=0;
    }
    else
    {
     q->next->datas[i]=new TYPE;
     (*(q->next->datas[i]))=(*(p->next->datas[i]));
    }
   }

   
   p=p->next;
   q=q->next;
  }
  
  this->tail=q;
 }
 
 else
 {
  this->blocks=0;
  this->tail=0;
 }

 
 this->total_size=that.total_size;
 this->total_length=that.total_length;
}



template <class TYPE>
Array<TYPE>::Array(const Array<TYPE>& array)
{
 
 this->Copy(array);
}


template <class TYPE>
const Array<TYPE>& Array<TYPE>::operator= (const Array<TYPE> &that)
{
 
 this->Destroy();
 
 this->Copy(that);
 
 return (*this);
}
























template <class TYPE>
void Array<TYPE>::Destroy()
{

 
 if(this->blocks)
 {
  BlockNode<TYPE*> *p;
  
  for(p=this->blocks; p!=0; p=this->blocks)
  {
   this->blocks=p->next;
   for(SIZE_TYPE i=0; i<p->size; i++)
    if(p->datas[i]!=0)
     delete p->datas[i];
   delete p;
  }
 }

 
 this->blocks=0;
 this->tail=0;
 this->total_size=0;
 this->total_length=0;
}



template <class TYPE>
Array<TYPE>::~Array()
{
 this->Destroy();
}

















































template <class TYPE>
TYPE& Array<TYPE>::operator [](SIZE_TYPE index)
{
 
 if(index>=this->total_length)
  this->total_length=index+1;

 
 if(this->blocks==0)
 {
  this->blocks=new BlockNode<TYPE*>(INIT_SIZE,0);
  this->tail=this->blocks;
  this->total_size=INIT_SIZE;
 }

 
 while(this->total_length>this->total_size)
 {
  
  SIZE_TYPE size=2*this->tail->size;
  
  BlockNode<TYPE*>* p=new BlockNode<TYPE*>(size,0);
  
  this->tail->next=p;
  this->tail=p;
  
  this->total_size+=size;
 }
 
 TYPE*& q=this->GetAddress(index);
 if(q==0)
  q=new TYPE;
 return (*q);
}


template <class TYPE>
TYPE*& Array<TYPE>::GetAddress(SIZE_TYPE index)const
{
 
 
 
 
 

 SIZE_TYPE remain=index/this->blocks->size;  
 SIZE_TYPE power,i;        
 SIZE_TYPE offset;        
 BlockNode<TYPE*>*p;        
 
 for(power=1,i=0; power-1<=remain; power<<=1,i++);
 
 offset=index - this->blocks->size*((power>>1)-1);
 
 p=this->blocks;
 for(SIZE_TYPE j=0; j<i-1; j++)
  p=p->next;
 return p->datas[offset];
};

template <class TYPE>
const TYPE& Array<TYPE>::operator[](SIZE_TYPE index)const
{
 if(index>=this->length()) throw this;
 TYPE* p=this->GetAddress(index);
 if(p==0) throw this;
 return *p;
}


template <class TYPE>
SIZE_TYPE Array<TYPE>::length()const
{
 return total_length;
}


template <class TYPE>
bool Array<TYPE>::operator== (const Array<TYPE>& that)const
{
 if(this->length()!=that.length()) return false;
 for(SIZE_TYPE i=0; i<this->length(); i++)
 {
  bool t;
  try{
   t=(this->operator[](i)==that[i]);
  }
  catch(const Array<TYPE>* e)
  {
   return false;
  }
        catch(Array<TYPE>* e)
        {
            return false;
        }
  if(!t) return false;
 }
 return true;
}


#endif 
