#ifndef SERIES_H_INCLUDED
#define SERIES_H_INCLUDED
template <class TYPE>
class Series
{
public:
 
 Series();
public:

 
 virtual bool First()const=0;
 
 virtual bool Last()const=0;
 
 virtual bool Prior()const=0;
 inline bool operator -- (void)const{ return this->Prior(); }
 
 virtual bool Next()const=0;
 inline bool operator ++ (void)const{ return this->Next(); }
 
 virtual TYPE& GetCurrent()=0;
 virtual const TYPE& GetCurrent()const=0;
 
 virtual unsigned int Traverse(bool visit(TYPE e))const;
 virtual unsigned int Traverse(bool visit(TYPE& e));
 
 void SetTraverseDirection(bool direction)const;
protected:
 
 mutable bool traverse_direction;
};


template <class TYPE>
Series<TYPE>::Series()
{
 
 this->SetTraverseDirection(false);
}


template<class TYPE>
unsigned int Series<TYPE>::Traverse(bool visit(TYPE e))const
{
    unsigned int n=0;   
 
 if(this->traverse_direction)
 {
  
  if(this->Last())
  {
   do{
    n++;
    if(!visit(this->GetCurrent())) return n;
   }while(this->Prior());
  }
 }
 else
 {
  
  
  if(this->First())
  {
   do{
    
    n++;
    
    if(!visit(this->GetCurrent()))  return n;
   }while(this->Next());
  }
 }
    
 return 0;
}

template<class TYPE>
unsigned int Series<TYPE>::Traverse(bool visit(TYPE& e))
{
    unsigned int n=0;   
 
 if(this->traverse_direction)
 {
  
  if(this->Last())
  {
   do{
    n++;
    if(!visit(this->GetCurrent())) return n;
   }while(this->Prior());
  }
 }
 else
 {
  
  
  if(this->First())
  {
   do{
    
    n++;
    
    if(!visit(this->GetCurrent()))  return n;
   }while(this->Next());
  }
 }
    
 return 0;
}

template<class TYPE>
void Series<TYPE>::SetTraverseDirection(bool direction)const
{
 this->traverse_direction=direction;
}


#endif 
