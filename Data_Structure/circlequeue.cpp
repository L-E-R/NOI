#include <iostream>
using namespace std;
const int MAXSIZE=3;
struct ElemType{
 int d;
};
struct SqQueue{
 ElemType* base;
 int front;
 int rear;
};
void initQueue(SqQueue& q); 
void clearQueue(SqQueue& q);
bool isEmpty(SqQueue& q);
bool isFull(SqQueue& q);
int getLength(SqQueue& q);
ElemType getHead(SqQueue& q);
bool insertElem(SqQueue& q,ElemType e);
ElemType deleteElem(SqQueue& q);
void traverseQueue(SqQueue& q,void (*visit)(ElemType&));

void initQueue(SqQueue& q){
 q.base=new ElemType[MAXSIZE];
 if(!q.base)
  exit(1);
 q.front=q.rear=0;
}
void clearQueue(SqQueue& q){
 q.front=q.rear=0;
}
bool isEmpty(SqQueue& q){
 return q.front==q.rear;
}
bool isFull(SqQueue& q){
 return (q.rear+1)%MAXSIZE==q.front;
}
int getLength(SqQueue& q){
 return (q.rear-q.front+MAXSIZE)%MAXSIZE;
}
ElemType getHead(SqQueue& q){
 if(q.front==q.rear){
  cout<<"Queue is empty!"<<endl;
  exit(1);
 }
 return q.base[q.front];
}
bool insertElem(SqQueue& q,ElemType e){
 if((q.rear+1)%MAXSIZE==q.front){
  cout<<"Queue overflow!"<<endl;
  return false;
 }
 q.base[q.rear]=e;
 q.rear=(q.rear+1)%MAXSIZE;
 return true;
}
 
ElemType deleteElem(SqQueue& q){
 if(q.front==q.rear){
  cout<<"Queue is empty!"<<endl;
  exit(1);
 }
 ElemType e=q.base[q.front];
 q.front=(q.front+1)%MAXSIZE;
 return e;
}
void traverseQueue(SqQueue& q,void (*visit)(ElemType&)){
 if(q.front==q.rear)
  cout<<"Queue is empty!"<<endl;
 else{
  int t=q.front;
  while(t!=q.rear){
   visit(q.base[t]);
   t=(t+1)%MAXSIZE;
  }
  cout<<endl;
 }
}

void print(ElemType& e){
 cout<<e.d<<' ';
}
int main(){
 SqQueue q;
 initQueue(q);
 /* //////////debu
 cout<<isEmpty(q)<<endl;
 ElemType a={3};
 ElemType b={5};
 insertElem(q,a);
 insertElem(q,b);
 cout<<getLength(q)<<endl;
 cout<<isEmpty(q)<<endl;
 traverseQueue(q,print);
 ElemType c=getHead(q);
 cout<<"Head:"<<c.d<<endl;
 cout<<"full:"<<isFull(q)<<endl;
 deleteElem(q);
 cout<<getLength(q)<<endl;
 traverseQueue(q,print);
 deleteElem(q);
 traverseQueue(q,print);*/
 return 0;
}