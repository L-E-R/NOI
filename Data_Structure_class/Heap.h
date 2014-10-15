#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED
#include "common.h"
#include "SeriesSetAlgorithms.h"
#include "DataAccess.h"
#include "Series.h"

template <class TYPE>
class MaxHeap : virtual public DataAccess<TYPE>, virtual public Series<TYPE>
{
public:
        
        MaxHeap();
        
        MaxHeap(TYPE X[],SIZE_TYPE n);
        
        MaxHeap(const MaxHeap<TYPE>& that);
        
        ~MaxHeap();
public:
 
 virtual bool SearchFirst(TYPE& data);
 
 virtual bool SearchNext(TYPE& data);
 
 virtual bool Insert(TYPE data);
 
 virtual bool Delete(TYPE& data);
 
 virtual bool Modify(TYPE old_data,TYPE new_data);
public:

 
 virtual bool First()const;
 
 virtual bool Last()const;
 
 virtual bool Prior()const;
 
 virtual bool Next()const;
 
 virtual TYPE& GetCurrent();
 virtual const TYPE& GetCurrent()const;
public:
        
        SIZE_TYPE Length()const { return this->length; }
        
        bool IsEmpty()const { return (this->Length()==0); }
public:
        
        bool GetTop(TYPE& data){ return this->IsEmpty()?false:data=this->X[0],true; }
protected:
        TYPE* X;                
        SIZE_TYPE length;       
        SIZE_TYPE size;         
protected:
        SSIZE_TYPE search_pos;  
        mutable SSIZE_TYPE current_pos;  
protected:
        
        SSIZE_TYPE Locate(TYPE data);
};




        

template <class TYPE>
MaxHeap<TYPE>::MaxHeap()
{
        this->X=0;
        this->length=0;
        this->size=0;
        this->search_pos=-1;
        this->current_pos=-1;
}

        

template <class TYPE>
MaxHeap<TYPE>::MaxHeap(TYPE X[],SIZE_TYPE n)
{
        this->size=this->length=(n>0?n:0);
        if(this->size>0)
        {
                this->X=new TYPE[this->size];
                if(this->X)
                {
                        CopyArray(X,this->X,this->length);
                        CreateMaxHeap(this->X,this->length);
                }
                else
                {
                        throw this;
                }
        }
        this->search_pos=-1;
        this->current_pos=-1;
}

        

template <class TYPE>
MaxHeap<TYPE>::MaxHeap(const MaxHeap<TYPE>& that)
{
        this->~MaxHeap();
        this->size=that.size;
        this->X=new TYPE[this->size];
        if(this->X)
        {
                this->length=that.length;
                CopyArray(that.X,this->X,this->length);
        }
        else
        {
                throw this;
        }
        this->search_pos=-1;
        this->current_pos=-1;
}

        

template <class TYPE>
MaxHeap<TYPE>::~MaxHeap()
{
        if(this->X)
        {
                delete []this->X;
        }
        this->size=this->length=0;
        this->search_pos=-1;
        this->current_pos=-1;
}

 

template <class TYPE>
bool MaxHeap<TYPE>::SearchFirst(TYPE& data)
{
        this->search_key=data;
        for(this->search_pos=0; this->search_pos<this->length; this->search_pos++)
        {
                if(this->X[this->search_pos]==this->search_key)
                {
                        data=this->X[this->search_pos];
                        return true;
                }
        }
        this->search_pos=-1;
        return false;
}

 

template <class TYPE>
bool MaxHeap<TYPE>::SearchNext(TYPE& data)
{
        if(this->search_pos==-1) return false;
        for(this->search_pos++; this->search_pos<this->length; this->search_pos++)
        {
                if(this->X[this->search_pos]==this->search_key)
                {
                        data=this->X[this->search_pos];
                        return true;
                }
        }
        this->search_pos=-1;
        return false;
}

 

template <class TYPE>
bool MaxHeap<TYPE>::Insert(TYPE data)
{
        this->length++;
        
        if(this->length>this->size)
        {
                TYPE* p=0;
                this->size+=this->length;
                p=new TYPE[this->size];
                if(p)
                {
                        if(this->X)
                        {
                                CopyArray(this->X,p,this->length-1);
                                delete []this->X;
                        }
                        this->X=p;
                }
                else
                {
                        return false;
                }
        }
        InsertToMaxHeap(this->X,this->length-1,data);
        return true;
}

 

template <class TYPE>
bool MaxHeap<TYPE>::Delete(TYPE& data)
{
        if(this->IsEmpty()) return false;
        data=DeleteFromMaxHeap(this->X,this->length);
        this->length--;
        return true;
}

 

template <class TYPE>
bool MaxHeap<TYPE>::Modify(TYPE old_data,TYPE new_data)
{
        SSIZE_TYPE i=this->Locate(old_data);
        if(i==-1) return false;
        this->X[i]=new_data;
        DownUpAdjustMaxHeap(this->X,i+1);
        UpDownAdjustMaxHeap(this->X,i+1,this->length);
        return true;
}

 

template <class TYPE>
bool MaxHeap<TYPE>::First()const
{
        if(this->IsEmpty()) return false;
        this->current_pos=0;
        return true;
}

 

template <class TYPE>
bool MaxHeap<TYPE>::Last()const
{
        if(this->IsEmpty()) return false;
        this->current_pos=this->length-1;
        return true;
}



template <class TYPE>
bool MaxHeap<TYPE>::Prior()const
{
        if(this->current_pos==-1 || this->current_pos==0)
        {
                this->current_pos=-1;
                return false;
        }
        else
        {
                this->current_pos--;
                return true;
        }
}

 

template <class TYPE>
bool MaxHeap<TYPE>::Next()const
{
        if(this->current_pos==-1 || this->current_pos>=this->length-1)
        {
                this->current_pos=-1;
                return false;
        }
        else
        {
                this->current_pos++;
                return true;
        }
}

 

template <class TYPE>
TYPE& MaxHeap<TYPE>::GetCurrent()
{
        if(this->current_pos==-1) throw this;
        return this->X[this->current_pos];
}

template <class TYPE>
const TYPE& MaxHeap<TYPE>::GetCurrent()const
{
        if(this->current_pos==-1) throw this;
        return this->X[this->current_pos];
}

        

template <class TYPE>
SSIZE_TYPE MaxHeap<TYPE>::Locate(TYPE data)
{
        SSIZE_TYPE i;
        for(i=0; i<this->length && !(this->X[i]==data); i++);
        return (i<this->length?i:-1);
}






template <class TYPE>
class MinHeap : virtual public DataAccess<TYPE>, virtual public Series<TYPE>
{
public:
        
        MinHeap();
        
        MinHeap(TYPE X[],SIZE_TYPE n);
        
        MinHeap(const MinHeap<TYPE>& that);
        
        ~MinHeap();
public:
 
 virtual bool SearchFirst(TYPE& data);
 
 virtual bool SearchNext(TYPE& data);
 
 virtual bool Insert(TYPE data);
 
 virtual bool Delete(TYPE& data);
 
 virtual bool Modify(TYPE old_data,TYPE new_data);
public:

 
 virtual bool First()const;
 
 virtual bool Last()const;
 
 virtual bool Prior()const;
 
 virtual bool Next()const;
 
 virtual TYPE& GetCurrent();
 virtual const TYPE& GetCurrent()const;
public:
        
        SIZE_TYPE Length()const { return this->length; }
        
        bool IsEmpty()const { return (this->Length()==0); }
public:
        
        bool GetTop(TYPE& data){ return this->IsEmpty()?false:data=this->X[0],true; }
protected:
        TYPE* X;                
        SIZE_TYPE length;       
        SIZE_TYPE size;         
protected:
        SSIZE_TYPE search_pos;  
        mutable SSIZE_TYPE current_pos;  
protected:
        
        SSIZE_TYPE Locate(TYPE data);
};




        

template <class TYPE>
MinHeap<TYPE>::MinHeap()
{
        this->X=0;
        this->length=0;
        this->size=0;
        this->search_pos=-1;
        this->current_pos=-1;
}

        

template <class TYPE>
MinHeap<TYPE>::MinHeap(TYPE X[],SIZE_TYPE n)
{
        this->size=this->length=(n>0?n:0);
        if(this->size>0)
        {
                this->X=new TYPE[this->size];
                if(this->X)
                {
                        CopyArray(X,this->X,this->length);
                        CreateMinHeap(this->X,this->length);
                }
                else
                {
                        throw this;
                }
        }
        this->search_pos=-1;
        this->current_pos=-1;
}

        

template <class TYPE>
MinHeap<TYPE>::MinHeap(const MinHeap<TYPE>& that)
{
        this->~MinHeap();
        this->size=that.size;
        this->X=new TYPE[this->size];
        if(this->X)
        {
                this->length=that.length;
                CopyArray(that.X,this->X,this->length);
        }
        else
        {
                throw this;
        }
        this->search_pos=-1;
        this->current_pos=-1;
}

        

template <class TYPE>
MinHeap<TYPE>::~MinHeap()
{
        if(this->X)
        {
                delete []this->X;
        }
        this->size=this->length=0;
        this->search_pos=-1;
        this->current_pos=-1;
}

 

template <class TYPE>
bool MinHeap<TYPE>::SearchFirst(TYPE& data)
{
        this->search_key=data;
        for(this->search_pos=0; this->search_pos<this->length; this->search_pos++)
        {
                if(this->X[this->search_pos]==this->search_key)
                {
                        data=this->X[this->search_pos];
                        return true;
                }
        }
        this->search_pos=-1;
        return false;
}

 

template <class TYPE>
bool MinHeap<TYPE>::SearchNext(TYPE& data)
{
        if(this->search_pos==-1) return false;
        for(this->search_pos++; this->search_pos<this->length; this->search_pos++)
        {
                if(this->X[this->search_pos]==this->search_key)
                {
                        data=this->X[this->search_pos];
                        return true;
                }
        }
        this->search_pos=-1;
        return false;
}

 

template <class TYPE>
bool MinHeap<TYPE>::Insert(TYPE data)
{
        this->length++;
        
        if(this->length>this->size)
        {
                TYPE* p=0;
                this->size+=this->length;
                p=new TYPE[this->size];
                if(p)
                {
                        if(this->X)
                        {
                                CopyArray(this->X,p,this->length-1);
                                delete []this->X;
                        }
                        this->X=p;
                }
                else
                {
                        return false;
                }
        }
        InsertToMinHeap(this->X,this->length-1,data);
        return true;
}

 

template <class TYPE>
bool MinHeap<TYPE>::Delete(TYPE& data)
{
        if(this->IsEmpty()) return false;
        data=DeleteFromMinHeap(this->X,this->length);
        this->length--;
        return true;
}

 

template <class TYPE>
bool MinHeap<TYPE>::Modify(TYPE old_data,TYPE new_data)
{
        SSIZE_TYPE i=this->Locate(old_data);
        if(i==-1) return false;
        this->X[i]=new_data;
        DownUpAdjustMinHeap(this->X,i+1);
        UpDownAdjustMinHeap(this->X,i+1,this->length);
        return true;
}

 

template <class TYPE>
bool MinHeap<TYPE>::First()const
{
        if(this->IsEmpty()) return false;
        this->current_pos=0;
        return true;
}

 

template <class TYPE>
bool MinHeap<TYPE>::Last()const
{
        if(this->IsEmpty()) return false;
        this->current_pos=this->length-1;
        return true;
}



template <class TYPE>
bool MinHeap<TYPE>::Prior()const
{
        if(this->current_pos==-1 || this->current_pos==0)
        {
                this->current_pos=-1;
                return false;
        }
        else
        {
                this->current_pos--;
                return true;
        }
}

 

template <class TYPE>
bool MinHeap<TYPE>::Next()const
{
        if(this->current_pos==-1 || this->current_pos>=this->length-1)
        {
                this->current_pos=-1;
                return false;
        }
        else
        {
                this->current_pos++;
                return true;
        }
}

 

template <class TYPE>
TYPE& MinHeap<TYPE>::GetCurrent()
{
        if(this->current_pos==-1) throw this;
        return this->X[this->current_pos];
}

template <class TYPE>
const TYPE& MinHeap<TYPE>::GetCurrent()const
{
        if(this->current_pos==-1) throw this;
        return this->X[this->current_pos];
}

        

template <class TYPE>
SSIZE_TYPE MinHeap<TYPE>::Locate(TYPE data)
{
        SSIZE_TYPE i;
        for(i=0; i<this->length && !(this->X[i]==data); i++);
        return (i<this->length?i:-1);
}


#endif 
