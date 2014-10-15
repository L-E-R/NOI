#ifndef GRAPHALGORITHMS_H_INCLUDED
#define GRAPHALGORITHMS_H_INCLUDED
#include "common.h"
#include "List.h"
#include "Queue.h"
#include "Graph.h"
#include "Tree.h"
#include "Array.h"
#include "Heap.h"





template<class NODE_TYPE, class EDGE_TYPE>
PUBLIC List<SIZE_TYPE> TopologicalSorting(const Graph<NODE_TYPE,EDGE_TYPE> &graph);






template<class WEIGHT_TYPE>
PUBLIC TreeNode<SIZE_TYPE>* SingleSourceShortestPath(Graph<WEIGHT_TYPE,WEIGHT_TYPE>& graph,SIZE_TYPE start_node_index);





template<class NODE_TYPE,class COST_TYPE,class GRAPH_TYPE>
PRIVATE void MinCostSubTreeTemplate(const GRAPH_TYPE& graph,GRAPH_TYPE& mcst);


template<class NODE_TYPE,class COST_TYPE>
PUBLIC void MinCostSubTree(const LinkGraph<NODE_TYPE,COST_TYPE>& graph,LinkGraph<NODE_TYPE,COST_TYPE>& mcst);


template<class NODE_TYPE,class COST_TYPE>
PUBLIC void MinCostSubTree(const PhalanxGraph<NODE_TYPE,COST_TYPE>& graph,PhalanxGraph<NODE_TYPE,COST_TYPE>& mcst);





template <class NODE_TYPE,class WEIGHT_TYPE>
void AllPairsShortestPaths(Graph<NODE_TYPE,WEIGHT_TYPE>& graph);





template<class NODE_TYPE, class EDGE_TYPE>
PUBLIC List<SIZE_TYPE> TopologicalSorting(const Graph<NODE_TYPE,EDGE_TYPE> &graph)
{
 Array<SIZE_TYPE> indegrees(graph.GetNodesLength()); 
 Queue<SIZE_TYPE> queue;
 List<SIZE_TYPE> result;
 
 for(SIZE_TYPE i=0; i<graph.GetNodesLength(); i++)
 {
  if(!graph.IsNodeIndexUsed(i))
   indegrees[i]=-1;
  else
  {
   indegrees[i]=graph.GetInDegree(i);
   if(indegrees[i]==0)
    queue.Enter(i);
  }
 }
 
 while(!queue.IsEmpty())
 {
  SIZE_TYPE node_index;
  
  queue.Exit(node_index);
  result.Insert(node_index);
  
  const List<Edge<EDGE_TYPE> >* edges=graph.GetOutEdgesOfNode(node_index);
  if(edges)
  {
   if(edges->First())
   {
    do{
     
     if(--indegrees[edges->GetCurrent().to]==0)
      queue.Enter(edges->GetCurrent().to);
    }while(edges->Next());
   }
  }
 }
 return result;
}






template<class WEIGHT_TYPE>
PUBLIC TreeNode<SIZE_TYPE>* SingleSourceShortestPath(Graph<WEIGHT_TYPE,WEIGHT_TYPE>& graph,SIZE_TYPE start_node_index)
{
 Array<bool> marks(graph.GetNodesLength());                 
 Array<SSIZE_TYPE> parents(graph.GetNodesLength());         
        Array<TreeNode<SIZE_TYPE>* > tree_nodes(graph.GetNodesLength());
 TreeNode<SIZE_TYPE>* root=0;
 
 for(SIZE_TYPE i=0; i<graph.GetNodesLength(); i++)
 {
         
  graph.SetNodeData(i,-1);          
  marks[i]=(graph.IsNodeIndexUsed(i))?false:true;
  
  parents[i]=-1;                                  
  
  tree_nodes[i]=0;                                
 }
 
 graph.SetNodeData(start_node_index,0);
 
 while(true)
 {
  
  WEIGHT_TYPE min=-1;
  SSIZE_TYPE min_i=-1;
  SSIZE_TYPE selected_node_index;
  
  for(SIZE_TYPE i=0; i<graph.GetNodesLength(); i++)
  {
   
   if(!marks[i])
   {
    
    
    if(graph.GetNodeData(i)!=-1&&(min==-1||graph.GetNodeData(i)<min))
    {
     
     min=graph.GetNodeData(i);
     min_i=i;
    }
   }
  }
  
  if(min_i==-1) break;
  selected_node_index=min_i;
  
  marks[selected_node_index]=true;
  
  tree_nodes[selected_node_index]=new TreeNode<SIZE_TYPE>(selected_node_index);
  if(tree_nodes[selected_node_index]==0)
  {
    printf("Can not malloc memory in SingSourceShortestPath!");
    exit(1);
  }
  if(parents[selected_node_index]==-1)
    {
      tree_nodes[selected_node_index]->parent=0;
    }
  else
    {
      Tree<SIZE_TYPE>::InsertChild(tree_nodes[parents[selected_node_index]],1,tree_nodes[selected_node_index]);
    }
  
  const List<Edge<WEIGHT_TYPE> >* out_edges=graph.GetOutEdgesOfNode(selected_node_index);
  if(out_edges)
  {
   if(out_edges->First())
   {
    do{
     Edge<WEIGHT_TYPE> edge=out_edges->GetCurrent();
     
     if(!marks[edge.to]&&(graph.GetNodeData(edge.to)==-1 || graph.GetNodeData(selected_node_index)+edge.data<graph.GetNodeData(edge.to)))
     {
      graph.SetNodeData(edge.to,graph.GetNodeData(selected_node_index)+edge.data);
      
      parents[edge.to]=selected_node_index;
     }
    }while(out_edges->Next());
   }
  }
 }
 return (root=tree_nodes[start_node_index]);
}




















































































template<class NODE_TYPE,class COST_TYPE,class GRAPH_TYPE>
PRIVATE void MinCostSubTreeTemplate(const GRAPH_TYPE& graph,GRAPH_TYPE& mcst)
{












        
        Array<bool> Vt_marks(graph.GetNodesLength());   
        SIZE_TYPE n=graph.GetNodesCount();              
  


  mcst=graph;
  mcst.RemoveAllEdges();

        for(SIZE_TYPE i=0; i<graph.GetNodesLength(); i++)
        {
                if(graph.IsNodeIndexUsed(i))
                {
                        Vt_marks[i]=false;
                }
    else
    {
      Vt_marks[i]=true;
    }
                
        }
        
        if(n)
        {
                
                SIZE_TYPE start_node=0;
                while(!graph.IsNodeIndexUsed(start_node)) start_node++;
                
                Vt_marks[start_node]=true;
                
                MinHeap<Edge<COST_TYPE> > min_heap;
                const List<Edge<COST_TYPE> >* out_edges=graph.GetOutEdgesOfNode(start_node);
                if(out_edges)
                {
                        if(out_edges->First())
                        {
                                do{
                                        Edge<COST_TYPE> edge=out_edges->GetCurrent();
                                        min_heap.Insert(edge);
                                }while(out_edges->Next());
                        }
                }

                n--;
                while( n && !min_heap.IsEmpty())
                {

                        Edge<COST_TYPE> min_edge;
                        min_heap.Delete(min_edge);

                        if(Vt_marks[min_edge.to]) continue;
                        mcst.InsertEdge(min_edge);
                        n--;

                        Vt_marks[min_edge.to]=true;



                        const List<Edge<COST_TYPE> >* out_edges=graph.GetOutEdgesOfNode(min_edge.to);
                        if(out_edges)
                        {
                                if(out_edges->First())
                                {
                                        do{
                                                Edge<COST_TYPE> edge=out_edges->GetCurrent();

                                                if(!Vt_marks[edge.to])
                                                        min_heap.Insert(edge);
                                        }while(out_edges->Next());
                                }
                        }
                }
        }
}

template <class NODE_TYPE,class COST_TYPE>
PUBLIC void MinCostSubTree(const LinkGraph<NODE_TYPE,COST_TYPE> &graph,LinkGraph<NODE_TYPE,COST_TYPE> &mcst)
{
 MinCostSubTreeTemplate<NODE_TYPE,COST_TYPE,LinkGraph<NODE_TYPE,COST_TYPE>>(graph,mcst);
}


template <class NODE_TYPE,class COST_TYPE>
PUBLIC void MinCostSubTree(const PhalanxGraph<NODE_TYPE,COST_TYPE> &graph, PhalanxGraph<NODE_TYPE,COST_TYPE>& mcst)
{
 MinCostSubTreeTemplate<NODE_TYPE,COST_TYPE,PhalanxGraph<NODE_TYPE,COST_TYPE>>(graph,mcst);
}

















template <class NODE_TYPE,class WEIGHT_TYPE>
void AllPairsShortestPaths(Graph<NODE_TYPE,WEIGHT_TYPE>& graph)
{
 SIZE_TYPE n=graph.GetNodesLength();
 for(SIZE_TYPE k=0; k<n; k++)
 {
  for(SIZE_TYPE i=0; i<n; i++)
  {
   for(SIZE_TYPE j=0; j<n; j++)
   {
    
    if(i!=j && graph.IsEdgeExist(i,k) && graph.IsEdgeExist(k,j))
    {
     WEIGHT_TYPE w1=graph.GetEdgeData(i,k);
     WEIGHT_TYPE w2=graph.GetEdgeData(k,j);
     WEIGHT_TYPE w3;
     if(graph.IsEdgeExist(i,j))
     {
      w3=graph.GetEdgeData(i,j);
      if(w1+w2<w3)
       graph.SetEdgeData(i,j,w1+w2);
     }
     else
     {
      Edge<WEIGHT_TYPE> edge(i,j,w1+w2);
      graph.InsertEdge(edge);
     }
    }
   }
  }
 }
}


#endif 
