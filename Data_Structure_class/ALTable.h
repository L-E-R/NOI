


 #define MAX_VERTEX_NUM 20
 typedef enum{DG,DN,UDG,UDN}GraphKind; 
 typedef struct ArcNode
 {
   int adjvex; 
   struct ArcNode *nextarc; 
   InfoType *info; 
 }ArcNode; 
 typedef struct
 {
   VertexType data; 
   ArcNode *firstarc; 
 }VNode,AdjList[MAX_VERTEX_NUM]; 
 typedef struct
 {
   AdjList vertices;
   int vexnum,arcnum; 
   GraphKind kind; 
 }ALGraph;
 
 
 #include"bo2-8.c" 
 #include"func2-1.c" 
 int LocateVex(ALGraph G,VertexType u)
 { 
   
   int i;
   for(i=0;i<G.vexnum;++i)
     if(strcmp(u,G.vertices[i].data)==0)
       return i;
   return -1;
 }
 
 void CreateGraph(ALGraph *G)
 { 
   int i,j,k,w; 
   VertexType va,vb; 
   ElemType e;
   printf("请输入图的类型(有向图:0,有向网:1,无向图:2,无向网:3): ");
   scanf("%d",&(*G).kind);
   printf("请输入图的顶点数,边数: ");
   scanf("%d,%d",&(*G).vexnum,&(*G).arcnum);
   printf("请输入%d个顶点的值(<%d个字符):\n",(*G).vexnum,MAX_NAME);
   for(i=0;i<(*G).vexnum;++i) 
   {
     scanf("%s",(*G).vertices[i].data);
     (*G).vertices[i].firstarc=NULL; 
   }
   if((*G).kind%2) 
     printf("请输入每条弧(边)的权值、弧尾和弧头(以空格作为间隔):\n");
   else 
     printf("请输入每条弧(边)的弧尾和弧头(以空格作为间隔):\n");
   for(k=0;k<(*G).arcnum;++k) 
   {
     if((*G).kind%2) 
       scanf("%d%s%s",&w,va,vb);
     else 
       scanf("%s%s",va,vb);
     i=LocateVex(*G,va); 
     j=LocateVex(*G,vb); 
     e.info=NULL; 
     e.adjvex=j; 
     if((*G).kind%2) 
     {
       e.info=(int *)malloc(sizeof(int)); 
       *(e.info)=w;
     }
     ListInsert(&(*G).vertices[i].firstarc,1,e); 
     if((*G).kind>=2) 
     {
       e.adjvex=i; 
       ListInsert(&(*G).vertices[j].firstarc,1,e); 
     }
   }
 }
 
 void CreateGraphF(ALGraph *G)
 { 
   int i,j,k,w; 
   VertexType va,vb; 
   ElemType e;
   char filename[13];
   FILE *graphlist;
   printf("请输入数据文件名(f7-1.txt或f7-2.txt)：");
   scanf("%s",filename);
   printf("请输入图的类型(有向图:0,有向网:1,无向图:2,无向网:3): ");
   scanf("%d",&(*G).kind);
   graphlist=fopen(filename,"r"); 
   fscanf(graphlist,"%d",&(*G).vexnum);
   fscanf(graphlist,"%d",&(*G).arcnum);
   for(i=0;i<(*G).vexnum;++i) 
   {
     fscanf(graphlist,"%s",(*G).vertices[i].data);
     (*G).vertices[i].firstarc=NULL; 
   }
   for(k=0;k<(*G).arcnum;++k) 
   {
     if((*G).kind%2) 
       fscanf(graphlist,"%d%s%s",&w,va,vb);
     else 
       fscanf(graphlist,"%s%s",va,vb);
     i=LocateVex(*G,va); 
     j=LocateVex(*G,vb); 
     e.info=NULL; 
     e.adjvex=j; 
     if((*G).kind%2) 
     {
       e.info=(int *)malloc(sizeof(int)); 
       *(e.info)=w;
     }
     ListInsert(&(*G).vertices[i].firstarc,1,e); 
     if((*G).kind>=2) 
     {
       e.adjvex=i; 
       ListInsert(&(*G).vertices[j].firstarc,1,e); 
     }
   }
   fclose(graphlist); 
 }
 
 void DestroyGraph(ALGraph *G)
 { 
   int i;
   ElemType e;
   for(i=0;i<(*G).vexnum;++i) 
     if((*G).kind%2) 
       while((*G).vertices[i].firstarc) 
       {
	 ListDelete(&(*G).vertices[i].firstarc,1,&e); 
         if(e.adjvex>i) 
           free(e.info);
       }
     else 
       DestroyList(&(*G).vertices[i].firstarc); 
   (*G).vexnum=0; 
   (*G).arcnum=0; 
 }
 
 VertexType* GetVex(ALGraph G,int v)
 { 
   if(v>=G.vexnum||v<0)
     exit(ERROR);
   return &G.vertices[v].data;
 }
 
 Status PutVex(ALGraph *G,VertexType v,VertexType value)
 { 
   int i;
   i=LocateVex(*G,v);
   if(i>-1) 
   {
     strcpy((*G).vertices[i].data,value);
     return OK;
   }
   return ERROR;
 }
 
 int FirstAdjVex(ALGraph G,VertexType v)
 { 
   
   LinkList p;
   int v1;
   v1=LocateVex(G,v); 
   p=G.vertices[v1].firstarc;
   if(p)
     return p->data.adjvex;
   else
     return -1;
 }
 
 Status equalvex(ElemType a,ElemType b)
 { 
   if(a.adjvex==b.adjvex)
     return OK;
   else
     return ERROR;
 }
 
 int NextAdjVex(ALGraph G,VertexType v,VertexType w)
 { 
   
   LinkList p,p1; 
   ElemType e;
   int v1;
   v1=LocateVex(G,v); 
   e.adjvex=LocateVex(G,w); 
   p=Point(G.vertices[v1].firstarc,e,equalvex,&p1); 
   if(!p||!p->next) 
     return -1;
   else 
     return p->next->data.adjvex; 
 }
 
 void InsertVex(ALGraph *G,VertexType v)
 { 
   
   strcpy((*G).vertices[(*G).vexnum].data,v); 
   (*G).vertices[(*G).vexnum].firstarc=NULL;
   (*G).vexnum++; 
 }
 
 Status DeleteVex(ALGraph *G,VertexType v)
 { 
   int i,j,k;
   ElemType e;
   LinkList p,p1;
   j=LocateVex(*G,v); 
   if(j<0) 
     return ERROR;
   i=ListLength((*G).vertices[j].firstarc); 
   (*G).arcnum-=i; 
   if((*G).kind%2) 
     while((*G).vertices[j].firstarc) 
     {
       ListDelete(&(*G).vertices[j].firstarc,1,&e); 
       free(e.info); 
     }
   else 
     DestroyList(&(*G).vertices[i].firstarc); 
   (*G).vexnum--; 
   for(i=j;i<(*G).vexnum;i++) 
     (*G).vertices[i]=(*G).vertices[i+1];
   for(i=0;i<(*G).vexnum;i++) 
   {
     e.adjvex=j;
     p=Point((*G).vertices[i].firstarc,e,equalvex,&p1); 
     if(p) 
     {
       if(p1) 
         p1->next=p->next; 
       else 
         (*G).vertices[i].firstarc=p->next; 
       if((*G).kind<2) 
       {
         (*G).arcnum--; 
         if((*G).kind==1) 
           free(p->data.info); 
       }
       free(p); 
     }
     for(k=j+1;k<=(*G).vexnum;k++) 
     {
       e.adjvex=k;
       p=Point((*G).vertices[i].firstarc,e,equalvex,&p1); 
       if(p)
         p->data.adjvex--; 
     }
   }
   return OK;
 }
 
 Status InsertArc(ALGraph *G,VertexType v,VertexType w)
 { 
   
   ElemType e;
   int i,j;
   i=LocateVex(*G,v); 
   j=LocateVex(*G,w); 
   if(i<0||j<0)
     return ERROR;
   (*G).arcnum++; 
   e.adjvex=j;
   e.info=NULL; 
   if((*G).kind%2) 
   {
     e.info=(int *)malloc(sizeof(int)); 
     printf("请输入弧(边)%s→%s的权值: ",v,w);
     scanf("%d",e.info);
   }
   ListInsert(&(*G).vertices[i].firstarc,1,e); 
   if((*G).kind>=2) 
   {
     e.adjvex=i; 
     ListInsert(&(*G).vertices[j].firstarc,1,e); 
   }
   return OK;
 }
 
 Status DeleteArc(ALGraph *G,VertexType v,VertexType w)
 { 
   
   int i,j;
   Status k;
   ElemType e;
   i=LocateVex(*G,v); 
   j=LocateVex(*G,w); 
   if(i<0||j<0||i==j)
     return ERROR;
   e.adjvex=j;
   k=DeleteElem(&(*G).vertices[i].firstarc,&e,equalvex); 
   if(k) 
   {
     (*G).arcnum--; 
     if((*G).kind%2) 
       free(e.info);
     if((*G).kind>=2) 
     {
       e.adjvex=i;
       DeleteElem(&(*G).vertices[j].firstarc,&e,equalvex);
     }
     return OK;
   }
   else 
     return ERROR;
 }
 
 Boolean visited[MAX_VERTEX_NUM]; 
 void(*VisitFunc)(char* v); 
 void DFS(ALGraph G,int v)
 { 
   int w;
   visited[v]=TRUE; 
   VisitFunc(G.vertices[v].data); 
   for(w=FirstAdjVex(G,G.vertices[v].data);w>=0;w=NextAdjVex(G,G.vertices[v].data,G.vertices[w].data))
     if(!visited[w])
       DFS(G,w); 
 }
 
 void DFSTraverse(ALGraph G,void(*Visit)(char*))
 { 
   int v;
   VisitFunc=Visit; 
   for(v=0;v<G.vexnum;v++)
     visited[v]=FALSE; 
   for(v=0;v<G.vexnum;v++)
     if(!visited[v])
       DFS(G,v); 
   printf("\n");
 }
 
 typedef int QElemType; 

 void BFSTraverse(ALGraph G,void(*Visit)(char*))
 {
   int v,u,w;
   LinkQueue Q;
   for(v=0;v<G.vexnum;++v)
     visited[v]=FALSE; 
   InitQueue(&Q); 
   for(v=0;v<G.vexnum;v++) 
     if(!visited[v]) 
     {
       visited[v]=TRUE;
       Visit(G.vertices[v].data);
       EnQueue(&Q,v); 
       while(!QueueEmpty(Q)) 
       {
         DeQueue(&Q,&u); 
         for(w=FirstAdjVex(G,G.vertices[u].data);w>=0;w=NextAdjVex(G,G.vertices[u].data,G.vertices[w].data))
           if(!visited[w]) 
           {
             visited[w]=TRUE;
             Visit(G.vertices[w].data);
             EnQueue(&Q,w); 
           }
       }
     }
   printf("\n");
 }
 
 void DFS1(ALGraph G,int v,void(*Visit)(char*))
 { 
   ArcNode *p; 
   visited[v]=TRUE; 
   Visit(G.vertices[v].data); 
   for(p=G.vertices[v].firstarc;p;p=p->next) 
     if(!visited[p->data.adjvex])
       DFS1(G,p->data.adjvex,Visit); 
 }
 
 void DFSTraverse1(ALGraph G,void(*Visit)(char*))
 { 
   int v;
   for(v=0;v<G.vexnum;v++)
     visited[v]=FALSE; 
   for(v=0;v<G.vexnum;v++) 
     if(!visited[v]) 
       DFS1(G,v,Visit); 
   printf("\n");
 }
 
 void BFSTraverse1(ALGraph G,void(*Visit)(char*))
 { 
   int v,u;
   ArcNode *p; 
   LinkQueue Q; 
   for(v=0;v<G.vexnum;++v)
     visited[v]=FALSE; 
   InitQueue(&Q); 
   for(v=0;v<G.vexnum;v++) 
     if(!visited[v]) 
     {
       visited[v]=TRUE; 
       Visit(G.vertices[v].data); 
       EnQueue(&Q,v); 
       while(!QueueEmpty(Q)) 
       {
         DeQueue(&Q,&u); 
         for(p=G.vertices[u].firstarc;p;p=p->next) 
           if(!visited[p->data.adjvex]) 
           {
             visited[p->data.adjvex]=TRUE; 
             Visit(G.vertices[p->data.adjvex].data); 
             EnQueue(&Q,p->data.adjvex); 
           }
       }
     }
   printf("\n");
 }
 
 void Display(ALGraph G)
 { 
   int i;
   LinkList p;
   switch(G.kind)
   {
     case DG: printf("有向图\n");
	      break;
     case DN: printf("有向网\n");
              break;
     case UDG:printf("无向图\n");
              break;
     case UDN:printf("无向网\n");
   }
   printf("%d个顶点：\n",G.vexnum);
   for(i=0;i<G.vexnum;++i)
     printf("%s ",G.vertices[i].data);
   printf("\n%d条弧(边):\n",G.arcnum);
   for(i=0;i<G.vexnum;i++)
   {
     p=G.vertices[i].firstarc;
     while(p)
     {
       if(G.kind<=1||i<p->data.adjvex) 
       {
         printf("%s→%s ",G.vertices[i].data,G.vertices[p->data.adjvex].data);
	 if(G.kind%2) 
           printf(":%d ",*(p->data.info));
       }
       p=p->nextarc;
     }
     printf("\n");
   }
 }
