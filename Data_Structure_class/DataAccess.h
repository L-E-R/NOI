#ifndef DATAACCESS_H_INCLUDED
#define DATAACCESS_H_INCLUDED

template <class TYPE>
class DataAccess
{
public:
 
 virtual bool SearchFirst(TYPE& data)=0;
 
 virtual bool SearchNext(TYPE& data)=0;
 
 virtual bool Insert(TYPE data)=0;
 
 virtual bool Delete(TYPE& data)=0;
 
 virtual bool Modify(TYPE old_data,TYPE new_data)=0;
protected:
 TYPE search_key;  
};


#endif 
