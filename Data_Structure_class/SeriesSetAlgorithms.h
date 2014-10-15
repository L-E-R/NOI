#ifndef SERIESSETALGORITHMS_H_INCLUDED
#define SERIESSETALGORITHMS_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include "common.h"


#define NotFound -1




template <class TYPE>
PUBLIC void CopyArray(TYPE source[],TYPE destination[],SSIZE_TYPE n);



template <class TYPE>
PUBLIC void Swap(TYPE* a,TYPE* b);













template <class TYPE>
PUBLIC SSIZE_TYPE BinarySearch(TYPE X[],SSIZE_TYPE n,TYPE key);




template <class TYPE>

PUBLIC SSIZE_TYPE InterpolationSearch(TYPE X[],SSIZE_TYPE n,TYPE key);












template <class TYPE>
PUBLIC void SinkSort(TYPE X[],SSIZE_TYPE n);




template <class TYPE>

PUBLIC void InsertSort(TYPE X[],SSIZE_TYPE n);



template <class TYPE>

PUBLIC void SelectSort(TYPE X[],SSIZE_TYPE n);



template <class TYPE>
PUBLIC void MergeSort(TYPE X[],SSIZE_TYPE n);

template <class TYPE>
PRIVATE void M_Sort(TYPE X[],SSIZE_TYPE left,SSIZE_TYPE right);

template <class TYPE>
PRIVATE void Merge(TYPE X[],SSIZE_TYPE left,SSIZE_TYPE middle,SSIZE_TYPE right);




template <class TYPE>

PUBLIC void QuickSort(TYPE X[],SSIZE_TYPE n);

template <class TYPE>

PRIVATE void Q_Sort(TYPE X[],SSIZE_TYPE left,SSIZE_TYPE right);

template <class TYPE>
PRIVATE SSIZE_TYPE Partition(TYPE X[],SSIZE_TYPE left,SSIZE_TYPE right);



template <class TYPE>

PUBLIC void HeapSort(TYPE X[],SSIZE_TYPE n);

template <class TYPE>
PUBLIC TYPE DeleteFromMaxHeap(TYPE X[],SSIZE_TYPE n);

template <class TYPE>
PUBLIC void InsertToMaxHeap(TYPE X[],SSIZE_TYPE n,TYPE e);

template <class TYPE>
PUBLIC void CreateMaxHeap(TYPE X[],SSIZE_TYPE n);

template <class TYPE>

PUBLIC void UpDownAdjustMaxHeap(TYPE X[],SSIZE_TYPE top,SSIZE_TYPE bottom);

template <class TYPE>
PUBLIC void DownUpAdjustMaxHeap(TYPE X[],SSIZE_TYPE n);

template <class TYPE>
PUBLIC TYPE DeleteFromMinHeap(TYPE X[],SSIZE_TYPE n);

template <class TYPE>
PUBLIC void InsertToMinHeap(TYPE X[],SSIZE_TYPE n,TYPE e);

template <class TYPE>
PUBLIC void CreateMinHeap(TYPE X[],SSIZE_TYPE n);

template <class TYPE>
PUBLIC void UpDownAdjustMinHeap(TYPE X[],SSIZE_TYPE top,SSIZE_TYPE bottom);

template <class TYPE>
PUBLIC void DownUpAdjustMinHeap(TYPE X[],SSIZE_TYPE n);



template <class TYPE>
PUBLIC void RadixSort(TYPE X[],SSIZE_TYPE n,SSIZE_TYPE bits,SSIZE_TYPE radix);



template <class TYPE>

PUBLIC SSIZE_TYPE Max(TYPE X[],SSIZE_TYPE n);

template <class TYPE>
PUBLIC SSIZE_TYPE Min(TYPE X[],SSIZE_TYPE n);


template <class TYPE>
PUBLIC TYPE Select(TYPE X[],SSIZE_TYPE n,SSIZE_TYPE k);

template <class TYPE>
PRIVATE TYPE B_Select(TYPE X[],SSIZE_TYPE left,SSIZE_TYPE right,SSIZE_TYPE k);



template <class TYPE>
PUBLIC void GetLongestIncrementSubSeries(TYPE X[],SSIZE_TYPE n,TYPE Y[],SSIZE_TYPE* m);



#ifdef DEBUG
template <class TYPE>
PRIVATE void Display(TYPE X[],SSIZE_TYPE n)
{
        SSIZE_TYPE i;
        for(i=0; i<n; i++)
                printf("%d ",X[i]);
        printf("\n");
}
#endif 

template <class TYPE>
PUBLIC void CopyArray(TYPE source[],TYPE destination[],SSIZE_TYPE n)
{
 if(source<destination && destination<source+n)
  for(source+=n,destination+=n; n; n--)
   *--destination=*--source;
 else
  for(;n;n--)
   *destination++=*source++;
}

template <class TYPE>
PUBLIC void Swap(TYPE* a,TYPE* b)
{
 TYPE t=*a;
 *a=*b;
 *b=t;
}



template <class TYPE>
PUBLIC SSIZE_TYPE BinarySearch(TYPE X[],SSIZE_TYPE n,TYPE key)
{
 SSIZE_TYPE left=0,right=n-1;
 SSIZE_TYPE middle;
 while(left<=right)
 {
  middle=(left+right)/2;
  if(key==X[middle]) return middle;
        else if(key<X[middle]) right=middle-1;
  else  left=middle+1;
 }
 return left;
}



template <class TYPE>
PUBLIC SSIZE_TYPE InterpolationSearch(TYPE X[],SSIZE_TYPE n,TYPE key)
{
 SSIZE_TYPE left=0,right=n-1;
 SSIZE_TYPE middle;
    if(key<=X[left]) return left;
    if(key>X[right]) return right+1;
 while(right-left>1)
 {
  
  middle = left + ((key-X[left])*(right-left))/(X[right]-X[left]);
  
  if(middle==left || middle==right) middle=(left+right)/2;
  if(key<=X[middle]) right=middle;
  else  left=middle;
 }
 return right;
}



template <class TYPE>
PUBLIC void SinkSort(TYPE X[],SSIZE_TYPE n)
{
        int ordered=0;
        SSIZE_TYPE i,j;
        for(i=n-1; i && !ordered; i--)
        {
                ordered=1;
                for(j=0; j<i; j++)
                {
                        if(X[j]>X[j+1])
                        {
                                Swap(X+j,X+j+1);
                                ordered=0;
                        }
                }
        }
}



template <class TYPE>
PUBLIC void InsertSort(TYPE X[],SSIZE_TYPE n)
{
        SSIZE_TYPE i,j;
        for(i=1; i<n; i++)
        {
                TYPE t;
                
   #ifdef DEBUG
    for(j=i-1; j>=0 && X[i]<X[j]; j--);
    j++;
   #else
    j=BinarySearch(X,i,X[i]);
   #endif 
    
    t=X[i];
    CopyArray(X+j,X+j+1,i-j);
                X[j]=t;
        }
}



template <class TYPE>
PUBLIC void SelectSort(TYPE X[],SSIZE_TYPE n)
{
        SSIZE_TYPE i,j;
        for(i=0; i<n-1; i++)
        {
                SSIZE_TYPE min=i+Min(X+i,n-i);
                Swap(X+i,X+min);
        }
}



template <class TYPE>
PUBLIC void MergeSort(TYPE X[],SSIZE_TYPE n)
{
 M_Sort(X,0,n-1);
}

template <class TYPE>
PRIVATE void M_Sort(TYPE X[],SSIZE_TYPE left,SSIZE_TYPE right)
{
 SSIZE_TYPE middle;
 if(left<right)
 {
  middle=(left+right)/2;
  M_Sort(X,left,middle);
  M_Sort(X,middle+1,right);
  Merge(X,left,middle,right);
 }
}

template <class TYPE>
PRIVATE void Merge(TYPE X[],SSIZE_TYPE left,SSIZE_TYPE middle,SSIZE_TYPE right)
{
 SSIZE_TYPE i=left;  
 SSIZE_TYPE j=middle+1; 
 SSIZE_TYPE k=0;   
 
 TYPE* tmp=(TYPE*)malloc(sizeof(TYPE)*(right-left+1)); 
 
 while(i<=middle&&j<=right)
 {
  if(X[i]<=X[j])
   tmp[k++]=X[i++];
  else
   tmp[k++]=X[j++];
 }
 
 if(j>right)
 {
  
  while(i<=middle)
  {
   X[right+i-middle]=X[i];
   i++;
  }
 }
 
 for(j=0; j<k; j++)
  X[left+j]=tmp[j];
 
 free(tmp);
}



template <class TYPE>
PUBLIC void QuickSort(TYPE X[],SSIZE_TYPE n)
{
        Q_Sort(X,0,n-1);
}

template <class TYPE>
PRIVATE void Q_Sort(TYPE X[],SSIZE_TYPE left,SSIZE_TYPE right)
{
        if(left<right)
        {
                SSIZE_TYPE middle=Partition(X,left,right);
                
            #ifdef DEBUG
                SSIZE_TYPE i;
                for(i=0; i<left; i++)
                        printf("%c ",'*');
                for(i=left; i<=right; i++)
                        printf("%d ",X[i]);
                printf("\n");
            #endif 
                Q_Sort(X,left,middle-1);
                Q_Sort(X,middle+1,right);
        }
}

template <class TYPE>
PRIVATE SSIZE_TYPE Partition(TYPE X[],SSIZE_TYPE left,SSIZE_TYPE right)
{
        SSIZE_TYPE L=left,R=right;
        TYPE key=X[left];
        
        while(L<R)
        {
                
                while(L<=right && X[L]<=key) L++;
                
                while(R>=left && X[R]>key) R--;
                
                if(L<R) Swap(X+L,X+R);
        }
        
        Swap(X+left,X+R);
        return R;
}



template <class TYPE>
PUBLIC void HeapSort(TYPE X[],SSIZE_TYPE n)
{
        SSIZE_TYPE i;
        CreateMaxHeap(X,n);
    #ifdef DEBUG
        printf("Heap created:\n");
        Display(X,n);
        printf("Delete Max elements and Ajust...\n");
    #endif 
        for(i=n; i>1; i--)
        {
         #ifndef DEBUG
                
                Swap(X,X+i-1);
                
                UpDownAdjustMaxHeap(X,1,i-1);
                printf("i=%d :",i);
                Display(X,n);
            #else
    X[i-1]=DeleteFromMaxHeap(X,i);
            #endif
        }
}

template <class TYPE>
PUBLIC void CreateMaxHeap(TYPE X[],SSIZE_TYPE n)
{
        SSIZE_TYPE i;
    #ifdef DEBUG
        printf("In CreateMaxHeap:\n");
        for(i=2; i<=n; i++)
        {
         
         InsertToMaxHeap(X,i-1,X[i-1]);
        }
    #else 
        for(i=n/2; i>0; i--)
        {
            UpDownAdjustMaxHeap(X,i,n);
        }
    #endif 
}

template <class TYPE>
PUBLIC TYPE DeleteFromMaxHeap(TYPE X[],SSIZE_TYPE n)
{
   TYPE max=X[0];
   if(n==1) return max;
   X[0]=X[n-1];
   UpDownAdjustMaxHeap(X,1,n-1);
   return max;
}

template <class TYPE>
PUBLIC void InsertToMaxHeap(TYPE X[],SSIZE_TYPE n,TYPE e)
{
   X[n]=e;
   DownUpAdjustMaxHeap(X,n+1);
}




template <class TYPE>
PUBLIC void UpDownAdjustMaxHeap(TYPE X[],SSIZE_TYPE top,SSIZE_TYPE bottom)
{
        SSIZE_TYPE parent=top;
        TYPE tmp=X[top-1];
        SSIZE_TYPE child=2*parent;
        while(child<=bottom)
        {
         if(child+1<=bottom && X[child]>X[child-1]) child=child+1;
  if(tmp<X[child-1])
  {
   X[parent-1]=X[child-1];
   parent=child;
   child*=2;
  }
  else
   break;
        }
        X[parent-1]=tmp;
}



template <class TYPE>
PUBLIC void DownUpAdjustMaxHeap(TYPE X[],SSIZE_TYPE n)
{
        TYPE tmp=X[n-1];
        SSIZE_TYPE current=n;
        while(current!=1 && tmp>X[current/2-1])
        {
                X[current-1]=X[current/2-1];
                current/=2;
        }
        X[current-1]=tmp;
}

template <class TYPE>
PUBLIC void CreateMinHeap(TYPE X[],SSIZE_TYPE n)
{
        SSIZE_TYPE i;
    #ifdef DEBUG
        printf("In CreateMinHeap:\n");
        for(i=2; i<=n; i++)
        {
         
         InsertToMinHeap(X,i-1,X[i-1]);
        }
    #else 
        for(i=n/2; i>0; i--)
        {
            UpDownAdjustMinHeap(X,i,n);
        }
    #endif 
}

template <class TYPE>
PUBLIC TYPE DeleteFromMinHeap(TYPE X[],SSIZE_TYPE n)
{
   TYPE min=X[0];
   if(n==1) return min;
   X[0]=X[n-1];
   UpDownAdjustMinHeap(X,1,n-1);
   return min;
}

template <class TYPE>
PUBLIC void InsertToMinHeap(TYPE X[],SSIZE_TYPE n,TYPE e)
{
   X[n]=e;
   DownUpAdjustMinHeap(X,n+1);
}

template <class TYPE>
PUBLIC void UpDownAdjustMinHeap(TYPE X[],SSIZE_TYPE top,SSIZE_TYPE bottom)
{
        SSIZE_TYPE parent=top;
        TYPE tmp=X[top-1];
        SSIZE_TYPE child=2*parent;
        while(child<=bottom)
        {
         if(child+1<=bottom && X[child]<X[child-1]) child=child+1;
   if(tmp>X[child-1])
   {
    X[parent-1]=X[child-1];
    parent=child;
    child*=2;
   }
   else
    break;
        }
        X[parent-1]=tmp;
}

template <class TYPE>
PUBLIC void DownUpAdjustMinHeap(TYPE X[],SSIZE_TYPE n)
{
        TYPE tmp=X[n-1];
        SSIZE_TYPE current=n;
        while(current!=1 && tmp<X[current/2-1])
        {
                X[current-1]=X[current/2-1];
                current/=2;
        }
        X[current-1]=tmp;
}



template <class TYPE>
struct LinkNode
{
 TYPE data;
 struct LinkNode* next;
};

template <class TYPE>
PRIVATE SSIZE_TYPE GetBit(TYPE x,SSIZE_TYPE bits,SSIZE_TYPE radix)
{
 
 SSIZE_TYPE i;
 for(i=0; i<bits; i++) x/=radix;
 return x%radix;
}

template <class TYPE>
PUBLIC void RadixSort(TYPE X[],SSIZE_TYPE n,SSIZE_TYPE bits,SSIZE_TYPE radix)
{
 LinkNode<TYPE>* globe_queue=0;
 LinkNode<TYPE> **queue_heads,**queue_tails;
 SSIZE_TYPE i,j;

 
 for(i=n-1; i>=0; i--)
 {
  LinkNode<TYPE>* p=(LinkNode<TYPE>*)malloc(sizeof(LinkNode<TYPE>));
  if(!p)
  {
   printf("Malloc memory failed in function RadixSort!\n");
   exit(1);
  }
  p->next=globe_queue;
  p->data=X[i];
  globe_queue=p;
 }
 
 queue_heads=(LinkNode<TYPE>**)malloc(radix*sizeof(LinkNode<TYPE>*));
 queue_tails=(LinkNode<TYPE>**)malloc(radix*sizeof(LinkNode<TYPE>*));
 if(!queue_heads || !queue_tails)
 {
  printf("Malloc memory failed in function RadixSort!\n");
  exit(1);
 }

 
 for(j=0; j<bits; j++)
 {
  SSIZE_TYPE last;
  
  for(i=0; i<radix; i++)
  {
   queue_heads[i]=0;
   queue_tails[i]=0;
  }
  
  while(globe_queue)
  {
   SSIZE_TYPE bit=GetBit(globe_queue->data,j,radix);
   
   if(queue_tails[bit])
   {
    queue_tails[bit]->next=globe_queue;
    queue_tails[bit]=queue_tails[bit]->next;
   }
   else
   {
    queue_heads[bit]=queue_tails[bit]=globe_queue;
   }
   globe_queue=globe_queue->next;
  }
  
   
  for(i=0; i<radix && queue_heads[i]==0; i++);
  globe_queue=queue_heads[i];
   
  last=i;
  for(++i; i<radix; i++)
   if(queue_heads[i])
    queue_tails[last]->next=queue_heads[i],last=i;
  queue_tails[last]->next=0;
 }
 
 for(i=0; globe_queue; i++)
 {
  LinkNode<TYPE>* p=globe_queue;
  globe_queue=globe_queue->next;
  X[i]=p->data;
  free(p);
 }
 free(queue_heads);
 free(queue_tails);
}



template <class TYPE>
PUBLIC SSIZE_TYPE Max(TYPE X[],SSIZE_TYPE n)
{
 SSIZE_TYPE i;
 SSIZE_TYPE max_i=0;
 for(i=1;i<n;i++)
 {
  if(X[i]>X[max_i]) max_i=i;
 }
 return max_i;
}

template <class TYPE>
PUBLIC SSIZE_TYPE Min(TYPE X[],SSIZE_TYPE n)
{
 SSIZE_TYPE i;
 SSIZE_TYPE min_i=0;
 for(i=1;i<n;i++)
 {
  if(X[i]<X[min_i]) min_i=i;
 }
 return min_i;
}

template <class TYPE>
PUBLIC TYPE Select(TYPE X[],SSIZE_TYPE n,SSIZE_TYPE k)
{
 if(1<=k && k<=n)
 {
  TYPE* Y;
  TYPE result;
  Y=(TYPE*)malloc(sizeof(TYPE)*n);
  if(!Y)
  {
   printf("Can not malloc memory in function Select\n");
   exit(1);
  }
  CopyArray(X,Y,n);
 #ifdef DEBUG
  printf("Array Y:");
  Display(Y,n);
 #endif
  result=B_Select(Y,0,n-1,k);
  free(Y);
  return result;
 }
 else
    {
        printf("Invalid parameter in function Select(k should >=1 and <=n)\n");
        exit(1);
  return (TYPE)0;
    }
}

template <class TYPE>
PRIVATE TYPE B_Select(TYPE X[],SSIZE_TYPE left,SSIZE_TYPE right,SSIZE_TYPE k)
{
 if(left==right) return X[left];
 else
 {
  SSIZE_TYPE middle=Partition(X,left,right);
  if(middle-left+1>=k)
   return B_Select(X,left,middle,k);
  else
   return B_Select(X,middle+1,right,k-(middle-left+1));
 }
}



template <class TYPE>
PUBLIC void GetLongestIncrementSubSeries(TYPE X[],SSIZE_TYPE n,TYPE Y[],SSIZE_TYPE* m)
{

    SSIZE_TYPE i;
    TYPE* tails;
    TYPE* space;
    TYPE** sub_series;


    tails=(TYPE*)malloc(sizeof(TYPE)*n);
    space=(TYPE*)malloc(sizeof(TYPE)*n*(n+1)/2);
    sub_series=(TYPE**)malloc(sizeof(TYPE*)*n);
    if(!tails || !space || !sub_series)
    {
        printf("malloc memory failed in function GetLongestIncrementSubSeries!\n");
        exit(1);
    }
    for(sub_series[0]=space,i=1; i<n; i++)
    {
     sub_series[i]=sub_series[i-1]+i;
    }

    

 sub_series[0][0]=tails[0]=X[0];
    *m=1;
    for(i=1; i<n; i++)
    {
        SSIZE_TYPE j=BinarySearch(tails,*m,X[i]);
        if(j!=0) CopyArray(sub_series[j-1],sub_series[j],j);
        sub_series[j][j]=tails[j]=X[i];
        if(j==*m) (*m)++;
 #ifdef DEBUG
     for(j=0; j<(*m); j++)
     {
      Display(sub_series[j],j+1);
     }
 #endif 
    }
    CopyArray(sub_series[(*m)-1],Y,(*m));
    free(tails);
    free(space);
    free(sub_series);
}


#endif 
