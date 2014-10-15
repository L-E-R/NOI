#include <iostream>
#include <sstream>
#include<fstream>
using namespace std;
const int INF=INT_MAX; 
const int MAX_VERTEX_NUM=20; 
typedef int AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];


struct MGraph{
 string vexs[MAX_VERTEX_NUM]; 
 AdjMatrix arcs; 
 int vexnum,arcnum; 
};
void CreateGraph(MGraph &G); 
void CreateUDN(MGraph &G); 
int LocateVex(MGraph G,string u); 
void PrintGraph(MGraph G);
void DFSTraverse(MGraph G);
void BFSTraverse(MGraph G);

int LocateVex(MGraph G,string V){
 
 for(int i=0;i<G.vexnum;++i)
  if(V==G.vexs[i])
   return i;
 return -1;
}
void CreateGraph(MGraph &G){
 
 char filename[10];
 string s;
 //cout<<"请输入数据文件名：";
 cin>>filename;
 ifstream infile;
 infile.open(filename);  
 
 getline(infile, s); 
 istringstream ss1(s); 
 ss1>>G.vexnum>>G.arcnum; 
 
 getline(infile, s); 
 istringstream ss2(s);
 for(int i=0;i<G.vexnum;++i) 
  ss2>>G.vexs[i];
  
 for(int i=0;i<G.vexnum;++i){
  getline(infile,s);
  istringstream ss3(s);
  int a;
  char c;
  for(int j=0;j<G.vexnum;++j){
   ss3>>c;  
   if(isdigit(c)){    
    ss3.putback(c); 
    ss3>>a;  
    G.arcs[i][j]=a;
   }
   else    
    G.arcs[i][j]=INF;
  }
 } 
}
void CreateUDN(MGraph &G){
 
 //cout<<"请输入无向网G的顶点数,边数:";
 cin>>G.vexnum>>G.arcnum;
 
 //cout<<"请输入"<<G.vexnum<<"个顶点的值(以空格作为间隔)："<<endl;
 for(int i=0;i<G.vexnum;++i) 
  cin>>G.vexs[i];
 for(int i=0;i<G.vexnum;++i) 
  for(int j=0;j<G.vexnum;++j)
   G.arcs[i][j]=INF;
  
 //cout<<"请输入"<<G.arcnum<<"条边的顶点1 顶点2 权值(以空格作为间隔):"<<endl;
 string V1,V2;
 int w,m,n;
 for(int i=0;i<G.arcnum;++i){
  cin>>V1>>V2>>w;
  m=LocateVex(G,V1);
  n=LocateVex(G,V2);
  G.arcs[m][n]=G.arcs[n][m]=w; 
    }
}
void PrintGraph(MGraph G){
 cout<<endl<<"顶点数,边数:";
 cout<<G.vexnum<<' '<<G.arcnum<<endl;
 cout<<"顶点：";
 for(int i=0;i<G.vexnum;++i)
  cout<<G.vexs[i]<<' ';
 cout<<endl;
 cout<<"邻接矩阵："<<endl;
 for(int i=0;i<G.vexnum;++i){
  for(int j=0;j<G.vexnum;++j)
   if(G.arcs[i][j]==INF)
    cout<<"m"<<' ';
   else
    cout<<G.arcs[i][j]<<' ';
  cout<<endl;
 }
}
int FirstAdjVex(MGraph G,string V){
 
 int i=LocateVex(G,V); 
    for(int j=0;j<G.vexnum;++j)
  if(G.arcs[i][j]!=0 and G.arcs[i][j]!=INF)
   return j;
 return -1;
}
int NextAdjVex(MGraph G,string V1,string V2){
 
 
 
 int k1,k2;
 k1=LocateVex(G,V1); 
 k2=LocateVex(G,V2); 
 for(int i=k2+1;i<G.vexnum;i++)
  if(G.arcs[k1][i]!=0 and G.arcs[k1][i]!=INF)
   return i;
 return -1;
}
bool visited[MAX_VERTEX_NUM]; 
void DFS(MGraph G,int v){
 
 string V1=G.vexs[v];
 visited[v]=true; 
 cout<<G.vexs[v]<<' '; 
    for(int w=FirstAdjVex(G,V1);w>=0;w=NextAdjVex(G,V1,G.vexs[w]))
  if(!visited[w])
   DFS(G,w); 
 }
 
void DFSTraverse(MGraph G){
 
    for(int v=0;v<G.vexnum;v++)
  visited[v]=false; 
 for(int v=0;v<G.vexnum;v++)
  if(!visited[v])
   DFS(G,v); 
 cout<<endl;
 }
void BFSTraverse(MGraph G){
 
 
 string V;
 string Q[50]; 
 int front=0,rear=0;
 for(int i=0;i<G.vexnum;++i)
  visited[i]=false; 
  
 for(int i=0;i<G.vexnum;i++)
  if(!visited[i]){ 
   visited[i]=true; 
   cout<<G.vexs[i]<<' ';
   Q[rear]=G.vexs[i]; 
   ++rear;
   while(front!=rear){ 
    V=Q[front]; 
    ++front;
   for(int i=FirstAdjVex(G,V);i>=0;i=NextAdjVex(G,V,G.vexs[i]))
    if(!visited[i]){ 
     visited[i]=true;
     cout<<G.vexs[i]<<' ';
     Q[rear]=G.vexs[i];
     ++rear;
    }
   }
  }
  cout<<endl;
}

int main(){
 MGraph G;
 CreateGraph(G);
 PrintGraph(G);
 DFSTraverse(G);
 BFSTraverse(G);
}
