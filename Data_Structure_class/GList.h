
 typedef enum{ATOM,LIST}ElemTag; 
 typedef struct GLNode
 {
   ElemTag tag; 
   union 
   {
     AtomType atom; 
     struct
     {
       struct GLNode *hp,*tp;
     }ptr; 
   }a;
 }*GList,GLNode; 
  
 typedef enum{ATOM,LIST}ElemTag; 
 typedef struct GLNode
 {
   ElemTag tag; 
   union 
   {
     AtomType atom; 
     struct
     {
       struct GLNode *hp,*tp;
     }ptr; 
   }a;
 }*GList,GLNode; 
基本操作[编辑]
 
 
 void InitGList(GList *L)
 { 
   *L=NULL;
 }
 
 void CreateGList(GList *L,SString S) 
 { 
   SString sub,hsub,emp;
   GList p,q;
   StrAssign(emp,"()"); 
   if(!StrCompare(S,emp)) 
     *L=NULL; 
   else 
   {
     *L=(GList)malloc(sizeof(GLNode));
     if(!*L) 
       exit(OVERFLOW);
     if(StrLength(S)==1) 
     {
       (*L)->tag=ATOM;
       (*L)->a.atom=S[1]; 
     }
     else 
     {
       (*L)->tag=LIST;
       p=*L;
       SubString(sub,S,2,StrLength(S)-2); 
       do
       { 
         sever(sub,hsub); 
         CreateGList(&p->a.ptr.hp,hsub);
         q=p;
         if(!StrEmpty(sub)) 
         {
           p=(GLNode *)malloc(sizeof(GLNode));
           if(!p)
             exit(OVERFLOW);
           p->tag=LIST;
           q->a.ptr.tp=p;
         }
       }while(!StrEmpty(sub));
       q->a.ptr.tp=NULL;
     }
   }
 }
 void DestroyGList(GList *L)
 { 
   GList q1,q2;
   if(*L)
   {
     if((*L)->tag==LIST) 
     {
       q1=(*L)->a.ptr.hp; 
       q2=(*L)->a.ptr.tp; 
       DestroyGList(&q1); 
       DestroyGList(&q2); 
     }
     free(*L);
     *L=NULL;
   }
 }
 
 void CopyGList(GList *T,GList L)
 { 
   if(!L) 
     *T=NULL;
   else
   {
     *T=(GList)malloc(sizeof(GLNode)); 
     if(!*T)
       exit(OVERFLOW);
     (*T)->tag=L->tag;
     if(L->tag==ATOM)
       (*T)->a.atom=L->a.atom; 
     else
     {
       CopyGList(&((*T)->a.ptr.hp),L->a.ptr.hp); 
       CopyGList(&((*T)->a.ptr.tp),L->a.ptr.tp);
     }
   }
 }
 
 int GListLength(GList L)
 { 
   int len=0;
   while(L)
   {
     L=L->a.ptr.tp;
     len++;
   }
   return len;
 }
 
 int GListDepth(GList L)
 { 
   int max,dep;
   GList pp;
   if(!L)
     return 1; 
   if(L->tag==ATOM)
     return 0; 
   for(max=0,pp=L;pp;pp=pp->a.ptr.tp)
   {
     dep=GListDepth(pp->a.ptr.hp); 
     if(dep>max)
       max=dep;
   }
   return max+1; 
 }
 
 Status GListEmpty(GList L)
 { 
   if(!L)
     return TRUE;
   else
     return FALSE;
 }
 
 GList GetHead(GList L)
 { 
   GList h,p;
   if(!L) 
     return NULL;
   p=L->a.ptr.hp; 
   CopyGList(&h,p); 
   return h;
 }
 
 GList GetTail(GList L)
 { 
   GList t;
   if(!L) 
     return NULL;
   CopyGList(&t,L->a.ptr.tp); 
   return t;
 }
 
 void InsertFirst_GL(GList *L,GList e)
 { 
   GList p=(GList)malloc(sizeof(GLNode)); 
   if(!p)
     exit(OVERFLOW);
   p->tag=LIST; 
   p->a.ptr.hp=e; 
   p->a.ptr.tp=*L; 
   *L=p; 
 }
 
 void DeleteFirst_GL(GList *L,GList *e)
 { 
   GList p=*L; 
   *e=(*L)->a.ptr.hp; 
   *L=(*L)->a.ptr.tp; 
   free(p); 
 }
 
 void Traverse_GL(GList L,void(*v)(AtomType))
 { 
   if(L) 
     if(L->tag==ATOM) 
       v(L->a.atom);
     else 
     {
       Traverse_GL(L->a.ptr.hp,v); 
       Traverse_GL(L->a.ptr.tp,v); 
     }
 }
 
