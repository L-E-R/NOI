#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED
#include "common.h"
#include "BinaryTree.h"
#include "Queue.h"

#define TreeNode BinaryTreeNode

template <class TYPE>
class Tree
{
public:
 
 Tree(){};
 
 Tree(const Tree<TYPE>& that)
 {
  this->binary_tree=that.binary_tree;
 }
 
 const Tree<TYPE>& operator= (const Tree<TYPE>& that)
 {
  this->binary_tree=that.binary_tree;
  return (*this);
 }
 
 static void Destroy(TreeNode<TYPE>* root)
 {
  if(root)
  {
   BinaryTree<TYPE>::Destroy(root->l_child);
   delete root;
  }
 }
 
 void Destroy()
 {
  this->binary_tree->Destroy();
  }
public:
 
 TreeNode<TYPE>* GetRoot()
 {
  return this->binary_tree.GetRoot();
 }
 
 void SetRoot(TreeNode<TYPE>* root)
 {
  this->binary_tree.SetRoot(root);
 }

public:
 
 static TreeNode<TYPE>* GetChild(TreeNode<TYPE>* parent,SIZE_TYPE i)
 {
  if(!(1<=i&&i<=Tree<TYPE>::GetChildNum(parent))) return 0;
  TreeNode<TYPE>* p=parent->l_child;
  for(SIZE_TYPE j=1; j<i; j++)
   p=p->r_child;
  return p;
 }
 
 static SIZE_TYPE GetChildNum(TreeNode<TYPE>* parent)
 {
  SIZE_TYPE i=0;
  if(parent==0) return 0;
  for(TreeNode<TYPE>* p=parent->l_child; p; p=p->r_child) i++;
  return i;
 }
 
 
 
 
 static TreeNode<TYPE>* GetParent(TreeNode<TYPE>* tree_node)
 {
  return tree_node->parent;
 }
        
 static void LinkParentField(TreeNode<TYPE>* tree)
 {
  if(tree)
  {
   for(TreeNode<TYPE>* p=tree->l_child; p; p=p->r_child)
   {
    LinkParentField(p);
    p->parent=tree;
   }
  }
 }
        
 void LinkParentField()
 {
  Tree<TYPE>::LinkParentField(this->GetRoot());
  this->GetRoot()->parent=0;
 }
 
 
 static bool InsertChild(TreeNode<TYPE>* parent,SIZE_TYPE i,TreeNode<TYPE>* child)
 {
  
  if(i<1 || i>(Tree<TYPE>::GetChildNum(parent)+1) || child->r_child!=0) return false;
  
  child->parent=parent;
  if(i==1)
  {
   child->r_child=parent->l_child;
   parent->l_child=child;
   
   return true;
  }
  
  else
  {
   TreeNode<TYPE>* p=Tree<TYPE>::GetChild(parent,i-1);
   child->r_child=p->r_child;
   p->r_child=child;
   
   return true;
  }
 }
 
 static bool DeleteChild(TreeNode<TYPE>* parent,SIZE_TYPE i)
 {
  if(i<1 || i>Tree<TYPE>::GetChildNum(parent)) return false;
  TreeNode<TYPE> *p,*q;
  
  if(i==1)
  {
   p=parent->l_child;
   parent->l_child=p->r_child;
  }
  
  else
  {
   q=Tree<TYPE>::GetChild(i-1);
   p=q->r_child;
   q->r_child=p->r_child;
  }
  p->r_child=0;
  Tree<TYPE>::Destroy(p);
  return true;
 }
 
 static TYPE GetData(TreeNode<TYPE>* p)
 {
  return p->data;
 }
 
 static void SetData(TreeNode<TYPE>* p,TYPE data)
 {
  p->data=data;
 }
public:
 
 static bool PriorTraverse(TreeNode<TYPE>* tree,bool (* visitor)(TYPE data))
 {
  return BinaryTree<TYPE>::PriorTraverse(tree,visitor);
 }
 
 static bool PostTraverse(TreeNode<TYPE>* tree,bool (* visitor)(TYPE data))
 {
  return BinaryTree<TYPE>::MiddleTraverse(tree,visitor);
 }
 
 static bool LevelTraverse(TreeNode<TYPE>* tree,bool (* visitor)(TYPE data))
 {
  Queue<TreeNode<TYPE>* > queue;
  TreeNode<TYPE>* current;
  if(tree)
  {
   queue.Enter(tree);
   while(!queue.IsEmpty())
   {
    queue.Exit(current);
    if(!visitor(current->data)) return false;
    for(TreeNode<TYPE>* p=current->l_child; p; p=p->r_child)
     queue.Enter(p);
   }
  }
  return true;
 }
public:
 
 bool PriorTraverse(bool (* visitor)(TYPE data))
 {
  return Tree<TYPE>::PriorTraverse(this->GetRoot(),visitor);
 }
 
 bool PostTraverse(bool (* visitor)(TYPE data))
 {
  return Tree<TYPE>::PostTraverse(this->GetRoot(),visitor);
 }
 
 bool LevelTraverse(bool (* visitor)(TYPE data))
 {
  return Tree<TYPE>::LevelTraverse(this->GetRoot(),visitor);
 }
protected:
 BinaryTree<TYPE> binary_tree;
};




#endif 
