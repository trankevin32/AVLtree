//
//  AVLtree.h
//  Homework 2 Version 2
//
//  Created by Kevin Tran on 6/26/19.
//  Copyright © 2019 Kevin Tran. All rights reserved.
//
#include <iostream>
#include <string>
#include <cassert>


using namespace std;

#ifndef AVL_TREE_H
#define AVL_TREE_H


class index
{
private:
    string value;
    int pos;
public:
    index(string v = "", int p = 0):value(v), pos(p) {};
    string getValue() {  return value; };
    int getPos() { return pos; };
    /*
    void setPos(const int p){
        pos = p;
    }
     */
    bool operator>(const index &other)
    {
        return value > other.value;
    };
    bool operator==(const index &other)
    {
        return value == other.value;
    };
    bool operator<(const index &other)
    {
        return value < other.value;
    };
    friend std::ostream& operator<<(std::ostream& osObject, const index& other){
        osObject << other.value;
        return osObject;
    };
};



template<class elemType>
struct AVLNode
{
    elemType info;
    int bfactor; //balance factor
    AVLNode<elemType> *llink;
    AVLNode<elemType> *rlink;
};

template <class elemType>
class AVLTree {
private:
    AVLNode<elemType> *root;
    int height(AVLNode<elemType> *p) const;
    int max(int x, int y) const;
    void inorder(AVLNode<elemType> *p) const;
    void preorder(AVLNode<elemType> *p) const;
    void postorder(AVLNode<elemType> *p) const;
    void copyTree(AVLNode<elemType>* &copiedTreeRoot, AVLNode<elemType>* otherTreeRoot);
    void destroy(AVLNode<elemType>* &p);
    void rotateToLeft(AVLNode<elemType>* &root);
    void rotateToRight(AVLNode<elemType>* &root);
    void balanceFromLeft(AVLNode<elemType>* &root);
    void balanceFromRight(AVLNode<elemType>* &root);
    void insertIntoAVL(AVLNode<elemType>* &root, AVLNode<elemType> *newNode, bool& isTaller);
    
public:
    AVLTree();
    AVLTree(const AVLTree&);
    const AVLTree<elemType>& operator=(const AVLTree<elemType>&);
    bool isEmpty() const;
    void inorderTraversal() const;
    void preorderTraversal() const;
    void postorderTraversal() const;
    int treeHeight() const;
    bool search(elemType& searchItem) const;
    void destroyTree();
    ~AVLTree();
    void insert(const elemType &newItem);
};

#endif

template <class elemType>
AVLTree<elemType>::AVLTree()
{
    root = NULL;
}

template <class elemType>
AVLTree<elemType>::AVLTree(const AVLTree<elemType>& otherTree)
{
    if (otherTree.root == NULL) //otherTree is empty
        root = NULL;
    else
        copyTree(root, otherTree.root);
}

template <class elemType>
const AVLTree<elemType>& AVLTree<elemType>::operator=(const AVLTree<elemType>& otherTree)
{
    if (this != &otherTree) //avoid self-copy
    {
        if (root != NULL) //if the binary tree is not empty, destroy the binary tree
            destroy(root);
        if (otherTree.root == NULL) //otherTree is empty
            root = NULL;
        else
            copyTree(root, otherTree.root);
    }
    return *this;
}

template <class elemType>
void AVLTree<elemType>::copyTree(AVLNode<elemType>* &copiedTreeRoot, AVLNode<elemType>* otherTreeRoot)
{
    if (otherTreeRoot == NULL)
        copiedTreeRoot = NULL;
    else
    {
        copiedTreeRoot = new AVLNode<elemType>;
        copiedTreeRoot->info = otherTreeRoot->info;
        copyTree(copiedTreeRoot->llink, otherTreeRoot->llink);
        copyTree(copiedTreeRoot->rlink, otherTreeRoot->rlink);
    }
}

template <class elemType>
bool AVLTree<elemType>::isEmpty() const
{
    return(root == NULL);
}

template <class elemType>
int AVLTree<elemType>::height(AVLNode<elemType> *p) const
{
    if (p == NULL)
        return 0;
    else
        return 1 + max(height(p->llink), height(p->rlink));
}

template <class elemType>
int AVLTree<elemType>::max(int x, int y) const
{
    if (x >= y)
        return x;
    else
        return y;
}

template <class elemType>
int AVLTree<elemType>::treeHeight() const
{
    return height(root);
}

template <class elemType>
void AVLTree<elemType>::inorderTraversal() const
{
    inorder(root);
}

template <class elemType>
void AVLTree<elemType>::preorderTraversal() const
{
    preorder(root);
}

template <class elemType>
void AVLTree<elemType>::postorderTraversal() const
{
    postorder(root);
}

template <class elemType>
void AVLTree<elemType>::inorder(AVLNode<elemType> *p) const
{
    if (p != NULL)
    {
        inorder(p->llink);
        cout << p->info << " ";
        inorder(p->rlink);
    }
}

template <class elemType>
void  AVLTree<elemType>::preorder(AVLNode<elemType> *p) const
{
    if (p != NULL)
    {
        cout << p->info << " ";
        preorder(p->llink);
        preorder(p->rlink);
    }
}

template <class elemType>
void AVLTree<elemType>::postorder(AVLNode<elemType> *p) const
{
    if (p != NULL)
    {
        postorder(p->llink);
        postorder(p->rlink);
        cout << p->info << " ";
    }
}


template <class elemType>
bool AVLTree<elemType>::search(elemType& searchItem) const
{
    
    int count = 0;
    AVLNode<elemType> *current;
    bool found = false;
    if (root == NULL)
        cerr << "Cannot search the empty tree." << endl;
    else
    {
        current = root;
        while (current != NULL && !found)
        {
            count++;
            if (current->info == searchItem.getValue())
                found = true;
            else if (current->info > searchItem.getValue())
                current = current->llink;
            else
                current = current->rlink;
        }
    }
    
    if(found == true){
        cout << "Found with indexes after " << count << " accesses." << endl;
        //cout << "Index " << current->info.getPos() << " in array list." << endl;
        //searchItem.setPos(current->info.getPos());
        //searchItem(current->info.getValue(), current->info.getPos());
        class index temp(current->info.getValue(), current->info.getPos());
        searchItem = temp;
        
    }
    else{
        cout << "Item not found." << endl;
        
    }
    //exit(0);
    return found;
}

template <class elemType>
void AVLTree<elemType>::destroy(AVLNode<elemType>* &p)
{
    if (p != NULL)
    {
        destroy(p->llink);
        destroy(p->rlink);
        delete p;
        p = NULL;
    }
}

template <class elemType>
void AVLTree<elemType>::destroyTree()
{
    destroy(root);
}

template <class elemType>
AVLTree<elemType>::~AVLTree()
{
    destroy(root);
}

template <class elemType>
void AVLTree<elemType>::rotateToLeft(AVLNode<elemType>* &root)
{
    AVLNode<elemType> *p; //pointer to the root of the right subtree of root
    if (root == NULL)
        cerr << "Error in the tree" << endl;
    else if (root->rlink == NULL)
        cerr << "Error in the tree: no right subtree to rotate." << endl;
    else
    {
        p = root->rlink;
        root->rlink = p->llink; //the left subtree of p becomes the right subtree of root
        p->llink = root;
        root = p; //make p the new root node
    }
}

template <class elemType>
void AVLTree<elemType>::rotateToRight(AVLNode<elemType>* &root)
{
    AVLNode<elemType> *p; //pointer to the root of the left subtree of root
    if (root == NULL)
        cerr << "Error in the tree" << endl;
    else if (root->llink == NULL)
        cerr << "Error in the tree: no left subtree to rotate." << endl;
    else
    {
        p = root->llink;
        root->llink = p->rlink; //the right subtree of p becomes the left subtree of root
        p->rlink = root;
        root = p; //make p the new root node
    }
}

template <class elemType>
void AVLTree<elemType>::balanceFromLeft(AVLNode<elemType>* &root)
{
    AVLNode<elemType> *p;
    AVLNode<elemType> *w;
    p = root->llink; //p points to the left subtree of root
    switch (p->bfactor)
    {
        case -1:
            root->bfactor = 0;
            p->bfactor = 0;
            rotateToRight(root);
            break;
        case 0:
            cerr << "Error: Cannot balance from the left." << endl;
            break;
        case 1:
            w = p->rlink;
            switch (w->bfactor) //adjust the balance factors
        {
            case -1:
                root->bfactor = 1;
                p->bfactor = 0;
                break;
            case 0:
                root->bfactor = 0;
                p->bfactor = 0;
                break;
            case 1:
                root->bfactor = 0;
                p->bfactor = -1;
        }//end switch
            w->bfactor = 0;
            rotateToLeft(p);
            root->llink = p;
            rotateToRight(root);
    }//end switch;
}

template <class elemType>
void AVLTree<elemType>::balanceFromRight(AVLNode<elemType>* &root)
{
    AVLNode<elemType> *p;
    AVLNode<elemType> *w;
    p = root->rlink; //p points to the left subtree of root
    switch (p->bfactor)
    {
        case -1:
            w = p->llink;
            switch (w->bfactor) //adjust the balance factors
        {
            case -1:
                root->bfactor = 0;
                p->bfactor = 1;
                break;
            case 0:
                root->bfactor = 0;
                p->bfactor = 0;
                break;
            case 1:
                root->bfactor = -1;
                p->bfactor = 0;
        }//end switch
            w->bfactor = 0;
            rotateToRight(p);
            root->rlink = p;
            rotateToLeft(root);
            break;
        case 0:
            cerr << "Error: Cannot balance from the left." << endl;
            break;
        case 1:
            root->bfactor = 0;
            p->bfactor = 0;
            rotateToLeft(root);
    }//end switch;
}//end balanceFromRight

template <class elemType>
void AVLTree<elemType>::insertIntoAVL(AVLNode<elemType>* &root, AVLNode<elemType> *newNode, bool& isTaller)
{
    if (root == NULL)
    {
        root = newNode;
        isTaller = true;
    }
    else if (root->info == newNode->info)
        cerr << "No duplicates are allowed." << endl;
    else if (root->info > newNode->info) //newItem goes in the left subtree
    {
        insertIntoAVL(root->llink, newNode, isTaller);
        if (isTaller) //after insertion, the subtree grew in height
            switch (root->bfactor)
        {
            case -1:
                balanceFromLeft(root);
                isTaller = false;
                break;
            case 0:
                root->bfactor = -1;
                isTaller = true;
                break;
            case 1:
                root->bfactor = 0;
                isTaller = false;
        }//end switch
    }//end else if
    else
    {
        insertIntoAVL(root->rlink, newNode, isTaller);
        if (isTaller) //after insertion, the subtree grew inheight
            switch (root->bfactor)
        {
            case -1:
                root->bfactor = 0;
                isTaller = false;
                break;
            case 0:
                root->bfactor = 1;
                isTaller = true;
                break;
            case 1:
                balanceFromRight(root);
                isTaller = false;
        }//end switch
    }//end else
}//insertIntoAVL

template <class elemType>
void AVLTree<elemType>::insert(const elemType &newItem)
{
    bool isTaller = false;
    AVLNode<elemType> *newNode;
    newNode = new AVLNode<elemType>;
    newNode->info = newItem;
    newNode->bfactor = 0;
    newNode->llink = NULL;
    newNode->rlink = NULL;
    insertIntoAVL(root, newNode, isTaller);
}
