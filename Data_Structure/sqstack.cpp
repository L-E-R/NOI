#include <iostream>
using namespace std;
const int MAXSIZE=50;
struct Elem{
 int data;
};
typedef int ElemType;
struct SqStack{
 ElemType base[MAXSIZE];
 int top;
};
void initStack(SqStack& s);
void clearStack(SqStack& s);
bool isEmpty(SqStack& s);
bool isFull(SqStack& s);
ElemType peek(SqStack& s);
void push(SqStack& s,const ElemType& e);
ElemType pop(SqStack& s);

void initStack(SqStack& s){
 s.top=0;
}
void clearStack(SqStack& s){
 s.top=0;
}
bool isEmpty(SqStack& s){
 return s.top==0;
}
bool isFull(SqStack& s){
 return s.top==MAXSIZE;
}
ElemType peek(SqStack& s){
 if(s.top==0){
  cerr<<"Stack is empty!"<<endl;
  exit(1);
 }
 return s.base[s.top-1];
}
void push(SqStack& s,const ElemType& e){
 if(s.top==MAXSIZE){
  cerr<<"Stack overflow!"<<endl;
  exit(1);
 }
 s.base[s.top]=e;
 ++s.top;
}
ElemType pop(SqStack& s){
 if(s.top==0){
  cerr<<"Stack is empty!"<<endl;
  exit(1);
 }
 --s.top;
 ElemType temp=s.base[s.top];
 return temp;
}


   
int main(){
 SqStack a;
 ElemType b='s',c='g';
 initStack(a);
 //////////
 return 0;
}