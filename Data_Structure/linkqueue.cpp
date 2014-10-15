#include <iostream>
using namespace std;
struct ElemType{
 int d;
};
struct QNode{
 ElemType data;
 QNode* next;
};
struct LinkQueue{
 QNode* front;
 QNode* rear;
};
void initQueue(LinkQueue& q);
void destroyQueue(LinkQueue& q);
void clearQueue(LinkQueue& q);
bool isEmpty(LinkQueue q);
int getLength(LinkQueue q);
ElemType getHead(LinkQueue q);
void insertElem(LinkQueue& q,ElemType e);
ElemType deleteElem(LinkQueue& q);
void traverseQueue(LinkQueue q,void (*visit)(ElemType&));
void initQueue(LinkQueue& q){
 q.front=q.rear=new QNode;
 if(!q.front)
  exit(1);
 q.front->next=NULL;
}
 
void destroyQueue(LinkQueue& q){
 while(q.front){
  q.rear=q.front->next;
  delete q.front;
  q.front=q.rear;
 }
}
void clearQueue(LinkQueue& q){
 QNode* p=q.front->next;
 while(p){
  q.rear=p->next;
  delete p;
  p=q.rear;
 }
}
bool isEmpty(LinkQueue q){
 return q.front==q.rear;
}
int getLength(LinkQueue q){
 int n=0;
 QNode* p=q.front->next;
 while(p){
  ++n;
  p=p->next;
 }
 return n;
}
ElemType getHead(LinkQueue q){
 if(q.front==q.rear){
  cerr<<"Queue is empty!"<<endl;
  exit(1);
 }
 return q.front->next->data;
}
void insertElem(LinkQueue& q,ElemType e){
 QNode* p=new QNode;
 p->data=e;
 p->next=NULL;
 q.rear->next=p;
 q.rear=p;
}
ElemType deleteElem(LinkQueue& q){
 if(q.front==q.rear){
  cerr<<"Queue is empty!"<<endl;
  exit(1);
 }
 QNode* p=q.front->next;
 ElemType e=p->data;
 q.front->next=p->next;
 if(q.rear==p) 
  q.rear=q.front;
 delete p;
 return e;
}
 
void traverseQueue(LinkQueue q,void (*visit)(ElemType&)){
 QNode* p=q.front->next;
 while(p){
  visit(p->data);
  p=p->next;
 }
 cout<<endl;
}


void print(ElemType& e){
 cout<<e.d<<' ';
}
int main(){
 LinkQueue q;
 initQueue(q);
 return 0;
}