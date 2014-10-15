#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include "common.h"
#include "List.h"
#include "Stack.h"
#include "Queue.h"
#include "LineStruct.h"
#include "Array.h"
#include "Phalanx.h"


template <class TYPE>
struct Edge
{
public:
 SIZE_TYPE from; 
 SIZE_TYPE to; 
 TYPE data;  
public:
 Edge(){}
 Edge(SIZE_TYPE from,SIZE_TYPE to,TYPE data)
 {
  this->from=from;
  this->to=to;
  this->data=data;
 }
 Edge(SIZE_TYPE from,SIZE_TYPE to)
 {
  this->from=from;
  this->to=to;
 }
 Edge(const Edge<TYPE>& that)
 {
  this->from=that.from;
  this->to=that.to;
  this->data=that.data;
 }
 const Edge<TYPE>& operator= (const Edge<TYPE>& that)
 {
  this->from=that.from;
  this->to=that.to;
  this->data=that.data;
  return (*this);
 }
 
 virtual bool operator== (const Edge<TYPE>& that)const
 {
  return (this->data==that.data);
 }
    virtual bool operator< (const Edge<TYPE>& that)const
    {
            return this->data<that.data;
    }
    virtual bool operator> (const Edge<TYPE>& that)const
    {
            return that.data<this->data;
    }
    virtual bool operator!= (const Edge<TYPE>& that)const
    {
            return !this->operator==(that);
    }
    virtual bool operator<= (const Edge<TYPE>& that)const
    {
            return !this->operator>(that);
    }
    virtual bool operator>= (const Edge<TYPE>& that)const
    {
            return !this->operator<(that);
    }
};










template <class NODE_TYPE,class EDGE_TYPE>
class Graph
{
public:
 
 virtual SIZE_TYPE GetNodesCount()const{ return this->node_count; }
 
 virtual SIZE_TYPE GetNodesLength()const{ return this->nodes.length(); }
 
 virtual bool IsEmpty()const{ return this->GetNodesCount()==0; }
    
    virtual void Clear(){ this->RemoveAllEdges(); this->RemoveAllNodes(); }
    
    virtual void RemoveAllEdges()=0;
protected:
    
    void RemoveAllNodes()
    {
        this->nodes.Clear();
        this->node_count=0;
    }
public:
 
 virtual bool InsertNode(SIZE_TYPE index,NODE_TYPE data)=0;
 
 virtual bool InsertEdge(Edge<EDGE_TYPE> edge)=0;
 
 virtual bool RemoveNode(SIZE_TYPE node_index)=0;
 
 virtual bool RemoveEdge(Edge<EDGE_TYPE>& edge)=0;
public:
 
 virtual const List<Edge<EDGE_TYPE> >* GetOutEdgesOfNode(SIZE_TYPE node_index)const=0;
 
 virtual SSIZE_TYPE GetOutDegree(SIZE_TYPE node_index)const=0;
 
 virtual const List<Edge<EDGE_TYPE> >* GetInEdgesOfNode(SIZE_TYPE node_index)const=0;
 
 virtual SSIZE_TYPE GetInDegree(SIZE_TYPE node_index)const=0;
public:
 
 virtual EDGE_TYPE GetEdgeData(SIZE_TYPE from,SIZE_TYPE to)const=0;
 
 virtual bool SetEdgeData(SIZE_TYPE from,SIZE_TYPE to,EDGE_TYPE data)=0;
 
 virtual bool IsEdgeExist(SIZE_TYPE from,SIZE_TYPE to)const=0;
public:
 
 virtual NODE_TYPE GetNodeData(SIZE_TYPE node_index)const
 {
  if(this->IsNodeIndexUsed(node_index))
   return this->nodes[node_index].data;
  else
   throw this;
 }
 
 virtual bool SetNodeData(SIZE_TYPE node_index, NODE_TYPE data){ return(this->IsNodeIndexUsed(node_index)?(this->nodes[node_index]=data,true):false); }
 
 virtual bool IsNodeIndexUsed(SIZE_TYPE node_index)const{ return (0<=node_index && node_index<this->nodes.length() && this->nodes[node_index].used); }
public:
 virtual bool DeepTraverse(bool (*visitor)(NODE_TYPE data))const
 {
  Stack<SIZE_TYPE> stack;
  return Traverse(visitor,stack);
 }
 virtual bool LevelTraverse(bool (*visitor)(NODE_TYPE data))const
 {
  Queue<SIZE_TYPE> queue;
  return Traverse(visitor,queue);
 }
protected:
 virtual bool Traverse(bool (*visitor)(NODE_TYPE data),LineStruct<SIZE_TYPE>& back_list)const
 {
  
  List<bool> nodes_visited;
  for(SIZE_TYPE i=0; i<this->nodes.length(); i++)
   if(this->nodes[i].used)
    nodes_visited.Insert(false);
   else
    nodes_visited.Insert(true);
  
  SIZE_TYPE start_node_index=nodes_visited.Locate(false);
  
  while(start_node_index)
  {
   
    
   back_list.Insert(start_node_index-1);
    
            nodes_visited[start_node_index]=true;
   while(!back_list.IsEmpty())
   {
    SIZE_TYPE node_index;   
     
    back_list.Delete(node_index);
     
    if(!visitor(this->nodes[node_index].data)) return false;
     
    
     
    const List<Edge<EDGE_TYPE> >* out_edges_list=this->GetOutEdgesOfNode(node_index);
                if(out_edges_list)
                {
        for(SIZE_TYPE i=1; i<=out_edges_list->Length(); i++)
        {
      
         SIZE_TYPE dest_node_index=(*out_edges_list)[i].to;
         if(nodes_visited[dest_node_index+1]==false)
                        {
          back_list.Insert(dest_node_index);
                            nodes_visited[dest_node_index+1]=true;
                        }
        }
                }
   }
   
   start_node_index=nodes_visited.Locate(false);
  }
  return true;
 }
protected:
 SIZE_TYPE node_count; 
 struct Node
 {
  NODE_TYPE data;  
  bool used;   
  
  Node(): used(false) {}
  
  Node(NODE_TYPE node_data):data(node_data),used(true){}
  
  Node(const Node& that):data(that.data),used(that.used){}
  
  const Node& operator=(const Node& that) { this->data=that.data; this->used=that.used; return(*this); }
 };
 Array<Node> nodes;  
protected:
 
 Graph():node_count(0){}
 
 Graph(const Graph<NODE_TYPE,EDGE_TYPE>& that):node_count(that.node_count),nodes(that.nodes){ }
};


template <class NODE_TYPE,class EDGE_TYPE>
class LinkGraph : public Graph<NODE_TYPE,EDGE_TYPE>
{
protected:
 struct EdgeLink
 {
 public:
  List<Edge<EDGE_TYPE> > *out_edges; 
  List<Edge<EDGE_TYPE> > *in_edges; 
 public:
  
  EdgeLink():out_edges(0),in_edges(0){}
  
  EdgeLink(const EdgeLink& that)
  {
   this->Copy(that);
  }
  
  const EdgeLink& operator= (const EdgeLink& that)
  {
   this->~EdgeLink();
   this->Copy(that);
   return (*this);
  }
  
  ~EdgeLink()
  {
   if(this->out_edges)
   {
    delete this->out_edges;
    this->out_edges=0;
   }
   if(this->in_edges)
   {
    delete this->in_edges;
    this->in_edges=0;
   }
  }
 protected:
  
  void Copy(const EdgeLink& that)
  {
   if(that.out_edges==0)
    this->out_edges=0;
   else
   {
    this->out_edges=new List<Edge<EDGE_TYPE> >(*that.out_edges);
    
   }
   if(that.in_edges==0)
    this->in_edges=0;
   else
   {
    this->in_edges=new List<Edge<EDGE_TYPE> >(*that.in_edges);
    
   }
  }
 };
 Array<EdgeLink> edge_links;  
public:
 
 LinkGraph(){}
 
 LinkGraph(const LinkGraph<NODE_TYPE,EDGE_TYPE>& that):Graph<NODE_TYPE,EDGE_TYP>(that),edge_links(that.edge_links){}
 
 const LinkGraph<NODE_TYPE,EDGE_TYPE>& operator= (const LinkGraph<NODE_TYPE,EDGE_TYPE>& that)
 {
  this->node_count=that.node_count;
  this->nodes=that.nodes;
  this->edge_links=that.edge_links;
  return (*this);
 }
public:
 
 virtual bool InsertEdge(Edge<EDGE_TYPE> edge)
 {
  
  if(!this->IsNodeIndexUsed(edge.from) || !this->IsNodeIndexUsed(edge.to)) return false;
  
  if(this->IsEdgeExist(edge.from,edge.to)) return false;
  
  if(this->edge_links[edge.from].out_edges==0)
   this->edge_links[edge.from].out_edges=new List<Edge<EDGE_TYPE> >;
  this->edge_links[edge.from].out_edges->Insert(edge);
  
  if(this->edge_links[edge.to].in_edges==0)
   this->edge_links[edge.to].in_edges=new List<Edge<EDGE_TYPE> >;
  this->edge_links[edge.to].in_edges->Insert(edge);
  return true;
 }
  
 virtual bool InsertNode(SIZE_TYPE index,NODE_TYPE node_data)
 {
  if(this->IsNodeIndexUsed(index)) return false;
  
  this->nodes[index]=Node(node_data);
  
  this->edge_links[index].out_edges=0;
  this->edge_links[index].in_edges=0;
  
  this->node_count++;
  return true;
 }
 
 virtual bool RemoveEdge(Edge<EDGE_TYPE>& edge)
 {
  List<Edge<EDGE_TYPE> > *out_edges,*in_edges;
  SIZE_TYPE i;
  
  if(!this->IsNodeIndexUsed(edge.from) || !this->IsNodeIndexUsed(edge.to) || (out_edges=this->edge_links[edge.from].out_edges)==0 || (in_edges=this->edge_links[edge.to].in_edges)==0) return false;
  
  

  
  for(i=1; i<=out_edges->Length(); i++)
  {
   if(edge.to==(*out_edges)[i].to)
   {
    
    edge=(*out_edges)[i];
    break;
   }
  }
  
  if(i>out_edges->Length()) return false;
  
  out_edges->Remove(i);

  
  for(i=1; i<=in_edges->Length(); i++)
  {
   if(edge.from==(*in_edges)[i].from)
   {
    edge=(*in_edges)[i];
    break;
   }
  }
  
  if(i>in_edges->Length()) return false;
  
  in_edges->Remove(i);

  return true;
 }
 
 virtual bool RemoveNode(SIZE_TYPE node_index)
 {
  List<Edge<EDGE_TYPE>> *in_edges,*out_edges;
  if(!this->IsNodeIndexUsed(node_index)) return false;
  
  in_edges=this->edge_links[node_index].in_edges;
  if(in_edges)
  {
   
   for(SIZE_TYPE i=1; i<=in_edges->Length(); i++)
   {
    Edge<EDGE_TYPE> edge=(*in_edges)[i];
    List<Edge<EDGE_TYPE>> *out_edges=this->edge_links[edge.from].out_edges;
    SIZE_TYPE j;
    for(j=1; j<=out_edges->Length(); j++)
     if(edge.to==(*out_edges)[j].to) break;
    if(j<=out_edges->Length()) out_edges->Remove(j);
   }
   delete this->edge_links[node_index].in_edges;
   this->edge_links[node_index].in_edges=0;
  }
  out_edges=this->edge_links[node_index].out_edges;
  if(out_edges)
  {
   
   for(SIZE_TYPE i=1; i<=out_edges->Length(); i++)
   {
    Edge<EDGE_TYPE> edge=(*out_edges)[i];
    List<Edge<EDGE_TYPE>> *in_edges=this->edge_links[edge.to].in_edges;
    SIZE_TYPE j;
    for(j=1; j<=in_edges->Length(); j++)
     if(edge.from==(*in_edges)[j].from) break;
    if(j<=in_edges->Length()) in_edges->Remove(j);
   }
   delete this->edge_links[node_index].out_edges;
   this->edge_links[node_index].out_edges=0;
  }
  
  this->nodes[node_index].used=false;
  
  this->node_count--;
  return true;
 }
    
    virtual void RemoveAllEdges()
    {
        for(SIZE_TYPE i=0; i<this->edge_links.length(); i++)
        {
            if(this->IsNodeIndexUsed(i))
            {
                EdgeLink& edge_link=this->edge_links[i];
                edge_link.~EdgeLink();
            }
        }
    }
 
    virtual void Clear()
    {
        this->edge_links.Clear();
        this->RemoveAllNodes();
    }
public:
 
 virtual const List<Edge<EDGE_TYPE> >* GetOutEdgesOfNode(SIZE_TYPE node_index)const
 {
  if(this->IsNodeIndexUsed(node_index))
   return this->edge_links[node_index].out_edges;
  return 0;
 }
 
 virtual const List<Edge<EDGE_TYPE> >* GetInEdgesOfNode(SIZE_TYPE node_index)const
 {
  if(this->IsNodeIndexUsed(node_index))
   return this->edge_links[node_index].in_edges;
  return 0;
 }
 
 virtual SSIZE_TYPE GetOutDegree(SIZE_TYPE node_index)const
 {
  if(this->IsNodeIndexUsed(node_index))
  {
   const List<Edge<EDGE_TYPE> >* out_edges=(this->GetOutEdgesOfNode(node_index));
   return out_edges?(SSIZE_TYPE)(out_edges->Length()):0;
  }
  else
   return -1;
 }
 
 virtual SSIZE_TYPE GetInDegree(SIZE_TYPE node_index)const
 {
  if(this->IsNodeIndexUsed(node_index))
  {
   const List<Edge<EDGE_TYPE> >* in_edges=(this->GetInEdgesOfNode(node_index));
   return in_edges?(SSIZE_TYPE)(in_edges->Length()):0;
  }
  else
   return -1;
 }
public:
 
 virtual EDGE_TYPE GetEdgeData(SIZE_TYPE from,SIZE_TYPE to)const
 {
  
  if(!this->IsNodeIndexUsed(from) || !this->IsNodeIndexUsed(to)) throw this;
  const List<Edge<EDGE_TYPE> >* out_edges=this->GetOutEdgesOfNode(from);
  
  if(!out_edges) throw this;
  for(SIZE_TYPE i=1; i<=out_edges->Length(); i++)
  {
   
   if(to==(*out_edges)[i].to) return (*out_edges)[i].data;
  }
  
  throw this;
 }
 
 virtual bool SetEdgeData(SIZE_TYPE from,SIZE_TYPE to,EDGE_TYPE data)
 {
  
  if(!this->IsNodeIndexUsed(from) || !this->IsNodeIndexUsed(to)) throw this;

  List<Edge<EDGE_TYPE> >* out_edges=this->edge_links[from].out_edges;
  
  if(!out_edges) return false;
  SIZE_TYPE i;
  for(i=1; i<=out_edges->Length(); i++)
  {
   
   if(to==(*out_edges)[i].to)
   {
    (*out_edges)[i].data=data;
    break;
   }
  }
  
  if(i>out_edges->Length()) return false;

  List<Edge<EDGE_TYPE> >*in_edges=this->edge_links[to].in_edges;
  
  if(!in_edges) return false;
  for(i=1; i<=in_edges->Length(); i++)
  {
   
   if(from==(*in_edges)[i].from)
   {
    (*in_edges)[i].data=data;
    break;
   }
  }
  
  if(i>in_edges->Length()) return false;

  return true;
 }
 
 virtual bool IsEdgeExist(SIZE_TYPE from,SIZE_TYPE to)const
 {
  
  if(!this->IsNodeIndexUsed(from) || !this->IsNodeIndexUsed(to)) return false;
  const List<Edge<EDGE_TYPE> >* out_edges=this->GetOutEdgesOfNode(from);
  
  if(!out_edges) return false;
  for(SIZE_TYPE i=1; i<=out_edges->Length(); i++)
  {
   
   if(to==(*out_edges)[i].to) return true;
  }
  
  return false;
 }
};

template <class NODE_TYPE,class EDGE_TYPE>
class PhalanxGraph : public Graph<NODE_TYPE,EDGE_TYPE>
{
public:
 
 virtual bool InsertNode(SIZE_TYPE index,NODE_TYPE node_data)
 {
  if(this->IsNodeIndexUsed(index)) return false;
  
  this->nodes[index]=Node(node_data);
  
  for(SIZE_TYPE i=0; i<this->GetNodesLength(); i++)
  {
   this->edge_links(index,i)=0;
   this->edge_links(i,index)=0;
  }
  
  this->node_count++;
  return true;
 }
 
 virtual bool InsertEdge(Edge<EDGE_TYPE> edge)
 {
  
  if(!this->IsNodeIndexUsed(edge.from) || !this->IsNodeIndexUsed(edge.to)) return false;
  
  if(this->IsEdgeExist(edge.from,edge.to)) return false;
  
  Edge<EDGE_TYPE>* edge_pointer=new Edge<EDGE_TYPE>(edge);
  
  if(edge_pointer==0) throw this;
  
  this->edge_links(edge.from,edge.to)=edge_pointer;
  return true;
 }
 
 virtual bool RemoveNode(SIZE_TYPE node_index)
 {
  
  if(!this->IsNodeIndexUsed(node_index)) return false;
  
  for(SIZE_TYPE i=0; i<this->GetNodesLength(); i++)
  {
   if(this->edge_links(node_index,i))
   {
    delete this->edge_links(node_index,i);
    this->edge_links(node_index,i)=0;
   }
   if(this->edge_links(i,node_index))
   {
    delete this->edge_links(i,node_index);
    this->edge_links(i,node_index)=0;
   }
  }
  
  this->nodes[node_index].used=false;
  
  this->node_count--;

  return true;
 }
 
 virtual bool RemoveEdge(Edge<EDGE_TYPE>& edge)
 {
  if(!this->IsEdgeExist(edge.from,edge.to)) return false;
  
  edge=*(this->edge_links(edge.from,edge.to));
  
  delete (this->edge_links(edge.from,edge.to));
  this->edge_links(edge.from,edge.to)=0;
  return true;
 }
public:
 
 virtual const List<Edge<EDGE_TYPE> >* GetOutEdgesOfNode(SIZE_TYPE node_index)const
 {
  static List<Edge<EDGE_TYPE> > out_edges;
  if(!this->IsNodeIndexUsed(node_index)) return 0;
  
  out_edges.Clear();
  
  for(SIZE_TYPE i=0; i<this->GetNodesLength(); i++)
  {
   if(this->IsNodeIndexUsed(i))
   {
    Edge<EDGE_TYPE>* edge_pointer=this->edge_links(node_index,i);
    if(edge_pointer)
    {
     out_edges.Insert(*edge_pointer);
    }
   }
  }
  return &out_edges;
 }
 
 virtual SSIZE_TYPE GetOutDegree(SIZE_TYPE node_index)const
 {
  if(!this->IsNodeIndexUsed(node_index)) return -1;
  SSIZE_TYPE out_degree=0;
  for(SIZE_TYPE i=0; i<this->GetNodesLength(); i++)
  {
   if(this->edge_links(node_index,i)) out_degree++;
  }
  return out_degree;
 }
 
 virtual const List<Edge<EDGE_TYPE> >* GetInEdgesOfNode(SIZE_TYPE node_index)const
 {
  static List<Edge<EDGE_TYPE> > in_edges;
  if(!this->IsNodeIndexUsed(node_index)) return 0;
  
  in_edges.Clear();
  
  for(SIZE_TYPE i=0; i<this->GetNodesLength(); i++)
  {
   if(this->IsNodeIndexUsed(i))
   {
    Edge<EDGE_TYPE> *edge_pointer=this->edge_links(i,node_index);
    if(edge_pointer)
    {
     in_edges.Insert(*edge_pointer);
    }
   }
  }
  return &in_edges;
 }
 
 virtual SSIZE_TYPE GetInDegree(SIZE_TYPE node_index)const
 {
  if(!this->IsNodeIndexUsed(node_index)) return -1;
  SSIZE_TYPE in_degree=0;
  for(SIZE_TYPE i=0; i<this->GetNodesLength(); i++)
  {
   if(this->edge_links(i,node_index)) in_degree++;
  }
  return in_degree;
 }
public:
 
 virtual EDGE_TYPE GetEdgeData(SIZE_TYPE from,SIZE_TYPE to)const
 {
  if(this->IsEdgeExist(from,to))
   return this->edge_links(from,to)->data;
  else
   throw this;
 }
 
 virtual bool SetEdgeData(SIZE_TYPE from,SIZE_TYPE to,EDGE_TYPE data)
 {
  if(this->IsEdgeExist(from,to))
  {
   this->edge_links(from,to)->data=data;
   return true;
  }
  else
   return false;
 };
 
 virtual bool IsEdgeExist(SIZE_TYPE from,SIZE_TYPE to)const
 {
  return (this->IsNodeIndexUsed(from) && this->IsNodeIndexUsed(to) && this->edge_links(from,to) );
 };
public:
 
 PhalanxGraph(){};
 
 PhalanxGraph(const PhalanxGraph<NODE_TYPE,EDGE_TYPE>& that):Graph<NODE_TYPE,EDGE_TYPE>(that)
 {
  this->CopyAllEdges(that.edge_links);
 };
 
 const PhalanxGraph<NODE_TYPE,EDGE_TYPE>& operator=(const PhalanxGraph<NODE_TYPE,EDGE_TYPE>& that)
 {
  this->nodes=that.nodes;
  this->node_count=that.node_count;
  
  
  this->RemoveAllEdges();
  
  this->CopyAllEdges(that.edge_links);
  
  return (*this);
 };
 
 ~PhalanxGraph()
 {
  
  this->RemoveAllEdges();
 }
protected:
 Phalanx<Edge<EDGE_TYPE>* > edge_links; 
public:
 
 void RemoveAllEdges()
 {
  for(SIZE_TYPE i=0; i<this->edge_links.length(); i++)
  {
   for(SIZE_TYPE j=0; j<this->edge_links.length(); j++)
   {
    if(this->edge_links(i,j))
    {
     delete this->edge_links(i,j);
     this->edge_links(i,j)=0;
    }
   }
  }
 }
protected:
 
 void CopyAllEdges(const Phalanx<Edge<EDGE_TYPE>* >& that_edge_links)
 {
  for(SIZE_TYPE i=0; i<that_edge_links.length(); i++)
  {
   for(SIZE_TYPE j=0; j<that_edge_links.length(); j++)
   {
    if(that_edge_links(i,j))
    {
     Edge<EDGE_TYPE>* edge_pointer=new Edge<EDGE_TYPE>(*that_edge_links(i,j));
     if(edge_pointer==0) throw this;
     this->edge_links(i,j)=edge_pointer;
    }
    else
    {
     this->edge_links(i,j)=0;
    }
   }
  }
 }
};


#endif 
