#include <iostream>
using namespace std;
struct Node
{
    int id;
    int age;
};
typedef Node ElemType;
struct SqList
{
    ElemType* list;
    int size;
    int maxSize;
};
bool initList(SqList& L,int ms);
void clearList(SqList& L);
int getSize(SqList L);
bool isEmpty(SqList L);
bool isFull(SqList L);
void traverList(SqList L,void (*visit)(ElemType&));
ElemType& getElem(SqList L,int pos);
int locateElem(SqList& L,ElemType e,int (*compare)(ElemType,ElemType));
int findList(SqList L,ElemType e);
bool insertElem(SqList& L,ElemType e,int pos);
bool deleteElem(SqList& L,int pos);
bool createList(SqList& L,int n,void (*visit)(ElemType&));

bool initList(SqList& L,int ms)//开辟ms个空间
{
    L.list=new ElemType[ms];
    if (!L.list)
    {
        cerr<<"Memory allocation failure!"<<endl;
        exit(1);
    }
    L.size=0;
    L.maxSize=ms;
    return true;
}
void clearList(SqList& L) //清除list
{
    L.size=0;
}
int getSize(SqList L)//返回L大小
{
    return L.size;
}
bool isEmpty(SqList L)//返回L为空
{
    return L.size==0;
}
bool isFull(SqList L)//返回L大小已满
{
    return L.size==L.maxSize;
}
void traverList(SqList L,void (*visit)(ElemType&))
{
    for (int i=0;i<L.size;++i)
        visit(L.list[i]);
    cout<<endl;
}
bool createList(SqList& L,int n,void (*visit)(ElemType&))
{
    if (n>L.maxSize)
        return false;
    for (int i=0;i<n;++i)
    {
        visit(L.list[i]);
        ++L.size;
    }
    return true;
}
ElemType& getElem(SqList L,int pos)
{
    if (pos<1||pos>L.size)
    {
        cerr<<"pos is out range!"<<endl;
        exit(1);
    }
    return L.list[pos-1];
}
int locateElem(SqList& L,ElemType e,int (*compare)(ElemType,ElemType))//查找线性表中满足给定条件的元素
{
    for (int i=0;i<L.size;++i)
        if (compare(L.list[i],e)==1)
            return i+1;
    return 0;
}
bool insertElem(SqList& L,ElemType e,int pos)//向线性表中的指定位置插入一个元素
{
    if (pos<1||pos>L.size+1)
    {
        cerr<<"pos is out range!"<<endl;
        return false;
    }
    for (int i=L.size-1;i>=pos-1;--i)
        L.list[i+1]=L.list[i];
    L.list[pos-1]=e;
    ++L.size;
    return true;
}
bool deleteElem(SqList& L,int pos)//从线性表中删除指定位置的元素
{
    if (pos<1||pos>L.size)
    {
        cerr<<"pos is out range!"<<endl;
        return false;
    }
    for (int i=pos-1;i<L.size-2;++i)
        L.list[i]=L.list[i+1];
    --L.size;
    return true;
}
int equal(ElemType e1,ElemType e2)//判断是否与e相等
{
    if (e1.id==e2.id)
        return 1;
    return 0;
}
 
int compare(ElemType e1,ElemType e2)//比较大小 e2大返回1
{
    if (e1.id<=e2.id)
        return 1;
    else
        return 0;
}
SqList mergeList(SqList La,SqList Lb)//合并两个线性表
{
    SqList Lc;
    initList(Lc,20);
    int i,j,k,laSize,lbSize;
    ElemType ai,bj;
    i=j=1,k=0;
    laSize=getSize(La);
    lbSize=getSize(Lb);
    while ((i<=laSize)&&(j<=lbSize))
    {
        ai=getElem(La,i);
        bj=getElem(Lb,j);
        if (compare(ai,bj)==1)
        {
            insertElem(Lc,ai,++k);
            ++i;
        }
        else
        {
            insertElem(Lc,bj,++k);
            ++j;
        }
    }
    while (i<=laSize)
    {
        ai=getElem(La,i++);
        insertElem(Lc,ai,++k);
    }
    while (j<=lbSize)
    {
        bj=getElem(Lb,j++);
        insertElem(Lc,bj,++k);
    }
    return Lc;
}
void unionList(SqList &la,SqList lb);
void print(ElemType& e)//输出
{
    cout<<"id:"<<e.id<<"  age:"<<e.age<<endl;
}
void inputElem(ElemType& e)//插入
{
    //cout<<"input id:";
    cin>>e.id;
    //cout<<"input age:";
    cin>>e.age;
    cout<<endl;
}
int main()
{   
    SqList la,lb;
    ElemType a1,a2,a3,b1,b2,b3,b4;
    a1.id=1;
    a1.age=57;
    a2.id=3;
    a3.id=6;
    b1.id=2;
    b2.id=4;
    b3.id=5;
    b4.id=7;
    initList(la,10);
    initList(lb,10);
    insertElem(la,a1,1);
    insertElem(la,a2,2);
    insertElem(la,a3,3);
    insertElem(lb,b1,1);
    insertElem(lb,b2,2);
    insertElem(lb,b3,3);
    insertElem(lb,b4,4);
    traverList(la,print);
    traverList(lb,print);
    //unionList(la,lb);
    //traverList(la,print);
    SqList lc=mergeList(la,lb);
    traverList(lc,print);
}

void unionList(SqList &la,SqList lb)//集合A=A∪B
{
    int lbSize=getSize(lb);
    ElemType e;
    for (int i=1;i<=lbSize;++i)
    {
        e=getElem(lb,i);
        if (!locateElem(la,e,equal))
            insertElem(la,e,la.size+1);
    }
}