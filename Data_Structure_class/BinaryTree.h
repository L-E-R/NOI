#ifndef BINARYTREE_H_INCLUDED
#define BINARYTREE_H_INCLUDED
#include "common.h"
#include "Array.h"
#include "Stack.h"
#include "Queue.h"
#include <stdlib.h>
#include <iostream>


template <class TYPE>
struct BinaryTreeNode
{
public:
 BinaryTreeNode<TYPE> *parent;   
 BinaryTreeNode<TYPE> *l_child;   
 BinaryTreeNode<TYPE> *r_child;   
 TYPE data;
public:
 
 BinaryTreeNode();
 
 BinaryTreeNode(TYPE data);
 
 BinaryTreeNode(BinaryTreeNode<TYPE>* l_child,BinaryTreeNode<TYPE>* r_child);
 
 BinaryTreeNode(BinaryTreeNode<TYPE>* parent,BinaryTreeNode<TYPE>* l_child,BinaryTreeNode<TYPE>* r_child);
 
 BinaryTreeNode(TYPE data,BinaryTreeNode<TYPE>* l_child,BinaryTreeNode<TYPE>* r_child);
 
 BinaryTreeNode(TYPE data,BinaryTreeNode<TYPE>* parent,BinaryTreeNode<TYPE>* l_child,BinaryTreeNode<TYPE>* r_child);
protected:
 
 inline void Initalize(TYPE data,BinaryTreeNode<TYPE>* parent,BinaryTreeNode<TYPE>* l_child,BinaryTreeNode<TYPE>* r_child);
};


template <class TYPE>
BinaryTreeNode<TYPE>::BinaryTreeNode()
{
 this->parent=this->l_child=this->r_child=0;
}

template <class TYPE>
BinaryTreeNode<TYPE>::BinaryTreeNode(TYPE data)
{
 this->Initalize(data,0,0,0);
}

template <class TYPE>
BinaryTreeNode<TYPE>::BinaryTreeNode(BinaryTreeNode<TYPE>* l_child,BinaryTreeNode<TYPE>* r_child)
{
 this->parent=0;
 this->l_child=l_child;
 this->r_child=r_child;
}

template <class TYPE>
BinaryTreeNode<TYPE>::BinaryTreeNode(BinaryTreeNode<TYPE>* parent,BinaryTreeNode<TYPE>* l_child,BinaryTreeNode<TYPE>* r_child)
{
 this->parent=parent;
 this->l_child=l_child;
 this->r_child=r_child;
}

template <class TYPE>
BinaryTreeNode<TYPE>::BinaryTreeNode(TYPE data,BinaryTreeNode<TYPE>* l_child,BinaryTreeNode<TYPE>* r_child)
{
 this->Initalize(data,0,l_child,r_child);
}

template <class TYPE>
BinaryTreeNode<TYPE>::BinaryTreeNode(TYPE data,BinaryTreeNode<TYPE>* parent,BinaryTreeNode<TYPE>* l_child,BinaryTreeNode<TYPE>* r_child)
{
 this->Initalize(data,parent,l_child,r_child);
}

template <class TYPE>
inline void BinaryTreeNode<TYPE>::Initalize(TYPE data,BinaryTreeNode<TYPE>* parent,BinaryTreeNode<TYPE>* l_child,BinaryTreeNode<TYPE>* r_child)
{
 this->data=data;
 this->parent=parent;
 this->l_child=l_child;
 this->r_child=r_child;
}

template <class TYPE>
class BinaryTree
{
public:
 
 BinaryTree();
 
 BinaryTree(const BinaryTreeNode<TYPE> *tree);
 
 BinaryTree(const BinaryTree<TYPE>& tree);
 
 const BinaryTree<TYPE>& operator= (const BinaryTree<TYPE>& that);
 
 virtual ~BinaryTree();
public:
 
 bool Construct(Array<TYPE>& datas,TYPE null);
 
 void LinkParentField();
 
 void Destroy();
public:
 
 static void Copy(const BinaryTreeNode<TYPE>* oldtree,BinaryTreeNode<TYPE>*& newtree);
 
 static void LinkParentField(BinaryTreeNode<TYPE>* tree);
 
 static void Destroy(BinaryTreeNode<TYPE>* tree);
public:
 
 BinaryTreeNode<TYPE>* GetRoot();
 
 void SetRoot(BinaryTreeNode<TYPE>* root);
public:
 
 static bool PriorTraverse(BinaryTreeNode<TYPE>* tree,bool (* visitor)(TYPE data));
 
 static bool MiddleTraverse(BinaryTreeNode<TYPE>* tree,bool (* visitor)(TYPE data));
 
 static bool PostTraverse(BinaryTreeNode<TYPE>* tree,bool (* visitor)(TYPE data));
 
 static bool LevelTraverse(BinaryTreeNode<TYPE>* tree,bool (* visitor)(TYPE data));
public:
 
 bool PriorTraverse(bool (* visitor)(TYPE data));
 
 bool MiddleTraverse(bool (* visitor)(TYPE data));
 
 bool PostTraverse(bool (* visitor)(TYPE data));
 
 bool LevelTraverse(bool (* visitor)(TYPE data));
protected:
 BinaryTreeNode<TYPE> *root;  
};

template <class TYPE>
BinaryTree<TYPE>::BinaryTree()
{
 
 this->root=0;
};

template <class TYPE>
BinaryTree<TYPE>::BinaryTree(const BinaryTreeNode<TYPE> *tree)
{
 BinaryTree<TYPE>::Copy(tree,this->root);
}

template <class TYPE>
BinaryTree<TYPE>::BinaryTree(const BinaryTree<TYPE>& tree)
{
 BinaryTree<TYPE>::Copy(tree.root,this->root);
}

template <class TYPE>
const BinaryTree<TYPE>& BinaryTree<TYPE>::operator= (const BinaryTree<TYPE>& that)
{
 this->Destroy();
 BinaryTree<TYPE>::Copy(that.root,this->root);
 return (*this);
}

template <class TYPE>
BinaryTree<TYPE>::~BinaryTree()
{
 
 this->Destroy();
}

template <class TYPE>
void BinaryTree<TYPE>::Copy(const BinaryTreeNode<TYPE>* oldtree,BinaryTreeNode<TYPE>*& newtree)
{
 if(oldtree)
 {
  
  newtree=new BinaryTreeNode<TYPE>;
  
  if(!newtree)
  {
   cout<<"Malloc memory failed in BinaryTree<TYPE>::Copy(const BinaryTreeNode<TYPE>* oldtree,BinaryTreeNode<TYPE>*& newtree)"<<endl;
   exit(1);
  }
  
  BinaryTree<TYPE>::Copy(oldtree->l_child,newtree->l_child);
  
  if(newtree->l_child) newtree->l_child->parent=newtree;
  
  BinaryTree<TYPE>::Copy(oldtree->r_child,newtree->r_child);
  
  if(newtree->r_child) newtree->r_child->parent=newtree;
  
  newtree->data=oldtree->data;
 }
 else
  newtree=0;
}

template <class TYPE>
void BinaryTree<TYPE>::Destroy()
{
 
 BinaryTree<TYPE>::Destroy(this->root);
 this->root=0;
};

template <class TYPE>
void BinaryTree<TYPE>::Destroy(BinaryTreeNode<TYPE> *tree)
{
 
 if(tree)
 {
  
  if(tree->l_child)
   BinaryTree<TYPE>::Destroy(tree->l_child);
  
  if(tree->r_child)
   BinaryTree<TYPE>::Destroy(tree->r_child);
  
  delete tree;
 }
}

template <class TYPE>
bool BinaryTree<TYPE>::PriorTraverse(BinaryTreeNode<TYPE>* tree,bool (*visitor)(TYPE data))
{
 
 if(tree)
 {
  
  if((*visitor)(tree->data))
   
   if(BinaryTree<TYPE>::PriorTraverse(tree->l_child,visitor))
    
    return(BinaryTree<TYPE>::PriorTraverse(tree->r_child,visitor));
   else
    return false;
  else
   return false;
 }
 return true;
}

template <class TYPE>
bool BinaryTree<TYPE>::MiddleTraverse(BinaryTreeNode<TYPE> *tree,bool (* visitor)(TYPE data))
{
 if(tree)
 {
  
  if(BinaryTree<TYPE>::MiddleTraverse(tree->l_child,visitor))
   
   if((*visitor)(tree->data))
    
    return(BinaryTree<TYPE>::MiddleTraverse(tree->r_child,visitor));
   else
    return false;
  else
   return false;

 }
 return true;
}

template <class TYPE>
bool BinaryTree<TYPE>::PostTraverse(BinaryTreeNode<TYPE> *tree,bool (* visitor)(TYPE data))
{
 if(tree)
 {
  
  if(BinaryTree<TYPE>::PostTraverse(tree->l_child,visitor))
   
   if(BinaryTree<TYPE>::PostTraverse(tree->r_child,visitor))
    
    return((*visitor)(tree->data));
   else
    return false;
  else
   return false;
 }
 return true;
};

template <class TYPE>
bool BinaryTree<TYPE>::LevelTraverse(BinaryTreeNode<TYPE> *tree,bool (* visitor)(TYPE data))
{
 Queue<BinaryTreeNode<TYPE>* > queue;
 BinaryTreeNode<TYPE>* current;
 if(tree)
 {
  queue.Enter(tree);
  while(!queue.IsEmpty())
  {
   queue.Exit(current);
   if(!visitor(current->data)) return false;
   if(current->l_child) queue.Enter(current->l_child);
   if(current->r_child) queue.Enter(current->r_child);
  }
 }
 return true;
}

template <class TYPE>
bool BinaryTree<TYPE>::PriorTraverse(bool (* visitor)(TYPE data))
{
 return BinaryTree<TYPE>::PriorTraverse(this->root,visitor);
}

template <class TYPE>
bool BinaryTree<TYPE>::MiddleTraverse(bool (* visitor)(TYPE data))
{
 return BinaryTree<TYPE>::MiddleTraverse(this->root,visitor);
}

template <class TYPE>
bool BinaryTree<TYPE>::PostTraverse(bool (* visitor)(TYPE data))
{
 return BinaryTree<TYPE>::PostTraverse(this->root,visitor);
}

template <class TYPE>
bool BinaryTree<TYPE>::LevelTraverse(bool (* visitor)(TYPE data))
{
 return BinaryTree<TYPE>::LevelTraverse(this->root,visitor);
}


template <class TYPE>
BinaryTreeNode<TYPE>* BinaryTree<TYPE>::GetRoot()
{
 return this->root;
}
template <class TYPE>
void BinaryTree<TYPE>::SetRoot(BinaryTreeNode<TYPE>* root)
{
 this->root=root;
}

template <class TYPE>
bool BinaryTree<TYPE>::Construct(Array<TYPE>& datas,TYPE null)
{
 this->Destroy();
 
 BinaryTreeNode<TYPE>** current_p;  
 Stack<BinaryTreeNode<TYPE>** > p_stack; 
 unsigned int i;
 
 current_p=&this->root;
 
 for(i=0; i<datas.length(); i++)
 {
  
  if(datas[i]==null)
  {
   (*current_p)=0;
   
   if(p_stack.IsEmpty()) break;
   p_stack.Pop(current_p);
  }
  
  else
  {
   (*current_p)=new BinaryTreeNode<TYPE>;
   (*current_p)->data=datas[i];
   p_stack.Push(&((*current_p)->r_child));
   current_p=&((*current_p)->l_child);
  }
 }
 
 if(p_stack.IsEmpty() && i==(datas.length()-1))
 {
  
  this->LinkParentField();
  return true;
 }
 
 else
 {
  this->Destroy();
  return false;
 }
}

template <class TYPE>
void BinaryTree<TYPE>::LinkParentField()
{
 BinaryTree<TYPE>::LinkParentField(this->root);
 this->root->parent=0;
}

template <class TYPE>
void BinaryTree<TYPE>::LinkParentField(BinaryTreeNode<TYPE>* tree)
{
 if(tree)
 {
  if(tree->l_child)
  {
   BinaryTree<TYPE>::LinkParentField(tree->l_child);
   tree->l_child->parent=tree;
  }
  if(tree->r_child)
  {
   BinaryTree<TYPE>::LinkParentField(tree->r_child);
   tree->r_child->parent=tree;
  }
 }
}


#endif 
