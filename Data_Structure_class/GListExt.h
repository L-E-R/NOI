
typedef enum{ATOM,LIST}ElemTag; 
typedef struct GLNode1
{
  ElemTag tag; 
  union 
  {
    AtomType atom; 
    struct GLNode1 *hp; 
  }a;
  struct GLNode1 *tp; 
}*GList1,GLNode1; 
void InitGList(GList1 *L)
{ 
  *L=NULL;
}
void CreateGList(GList1 *L,SString S) 
{ 
  SString emp,sub,hsub;
  GList1 p;
  StrAssign(emp,"()"); 
  *L=(GList1)malloc(sizeof(GLNode1));
  if(!*L) 
    exit(OVERFLOW);
  if(!StrCompare(S,emp)) 
  {
    (*L)->tag=LIST;
    (*L)->a.hp=(*L)->tp=NULL;
  }
  else if(StrLength(S)==1) 
  {
    (*L)->tag=ATOM;
    (*L)->a.atom=S[1];
    (*L)->tp=NULL;
  }
  else 
  {
    (*L)->tag=LIST;
    (*L)->tp=NULL;
    SubString(sub,S,2,StrLength(S)-2); 
    sever(sub,hsub); 
    CreateGList(&(*L)->a.hp,hsub);
    p=(*L)->a.hp;
    while(!StrEmpty(sub)) 
    {
      sever(sub,hsub); 
      CreateGList(&p->tp,hsub);
      p=p->tp;
    };
  }
}
void DestroyGList(GList1 *L)
{ 
  GList1 ph,pt;
  if(*L) 
  { 
    if((*L)->tag) 
      ph=(*L)->a.hp;
    else 
      ph=NULL;
    pt=(*L)->tp;
    DestroyGList(&ph); 
    DestroyGList(&pt); 
    free(*L); 
    *L=NULL; 
  }
}
void CopyGList(GList1 *T,GList1 L)
{ 
  *T=NULL;
  if(L) 
  {
    *T=(GList1)malloc(sizeof(GLNode1));
    if(!*T)
      exit(OVERFLOW);
    (*T)->tag=L->tag; 
    if(L->tag==ATOM) 
      (*T)->a.atom=L->a.atom; 
    else
      CopyGList(&(*T)->a.hp,L->a.hp); 
    if(L->tp==NULL) 
      (*T)->tp=L->tp;
    else
      CopyGList(&(*T)->tp,L->tp); 
  }
}
int GListLength(GList1 L)
{ 
  int len=0;
  GList1 p=L->a.hp;  
  while(p)
  {
    len++;
    p=p->tp;
  };
  return len;
}
int GListDepth(GList1 L)
{ 
  int max,dep;
  GList1 pp;
  if(L==NULL||L->tag==LIST&&!L->a.hp)
    return 1; 
  else if(L->tag==ATOM)
    return 0; 
  else 
    for(max=0,pp=L->a.hp;pp;pp=pp->tp)
    {
      dep=GListDepth(pp); 
      if(dep>max)
        max=dep;
    }
  return max+1; 
}
Status GListEmpty(GList1 L)
{ 
  if(!L||L->tag==LIST&&!L->a.hp)
    return OK;
  else
    return ERROR;
}
GList1 GetHead(GList1 L)
{ 
  GList1 h,p;
  if(!L||L->tag==LIST&&!L->a.hp) 
    return NULL;
  p=L->a.hp->tp; 
  L->a.hp->tp=NULL; 
  CopyGList(&h,L->a.hp); 
  L->a.hp->tp=p; 
  return h;
}
GList1 GetTail(GList1 L)
{ 
  GList1 t,p;
  if(!L||L->tag==LIST&&!L->a.hp) 
   return NULL;
 p=L->a.hp; 
 L->a.hp=p->tp; 
 CopyGList(&t,L); 
 L->a.hp=p; 
 return t;
}
void InsertFirst_GL(GList1 *L,GList1 e)
{ 
  GList1 p=(*L)->a.hp;
  (*L)->a.hp=e;
  e->tp=p;
}
void DeleteFirst_GL(GList1 *L,GList1 *e)
{ 
  if(*L&&(*L)->a.hp)
  {
    *e=(*L)->a.hp;
    (*L)->a.hp=(*e)->tp;
    (*e)->tp=NULL;
  }
  else
    *e=*L;
}
void Traverse_GL(GList1 L,void(*v)(AtomType))
{ 
  GList1 hp;
  if(L) 
  {
    if(L->tag==ATOM) 
    {
      v(L->a.atom);
      hp=NULL;
    }
    else 
      hp=L->a.hp;
    Traverse_GL(hp,v);
    Traverse_GL(L->tp,v);
  }
}
