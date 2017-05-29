//
//  trees.cpp
//  Trees
//
//  Created by bryce soto on 5/13/17.
//  Copyright © 2017 Bryce Soto. All rights reserved.
//

//#include <stdio.h>
#include<iostream>
#include "bst.h"
using namespace std;

//default constructor
Tree::Tree(){
    start = nullptr;
}

//copy constuctor
// must make the first node be nullpointer or copy constructor will never work!
Tree::Tree(const Tree& other):start(nullptr){
    //sent to private data
    copyOther(other);
}

void Tree::copyOther(const Tree& other){
    //send to private data
    copyFrom(other.start);
}

void Tree::copyFrom(TreeNode* startintPoint){
    if (startintPoint == nullptr){
        return;
    }
    push(startintPoint->value);
    copyFrom(startintPoint->left);
    copyFrom(startintPoint->right);
}

Tree::~Tree(){
    clear ();
    
}
//copy constructor
Tree& Tree::operator=(const Tree& other){
    //check to see if they equal each other
    if (this != &other){
        //delete last list
        clear();
        //copy the other list
        copyOther(other);
        
    }
    //returns pointer to object
    return *this;
    
}
void Tree::push(int value){
    //first create a new node like in bst example
    TreeNode* N1 = new TreeNode();
    N1->value = value;
    
    // if this is the first number, make it the root
    if (start == nullptr){
        start = N1;
        return;
    }
    
    //like insertNode, push value into tree with node and value
    pushFrom(start,N1);
}

void Tree::pushFrom(TreeNode* startingPoint, TreeNode* nodeToPush){
    
    if(startingPoint->value < nodeToPush->value){
        //check to seee if the left side is empty
        if (startingPoint->right == nullptr){
            startingPoint->right = nodeToPush;
        }else{
            //continue to traverse through the list
            pushFrom(startingPoint->right, nodeToPush);
        }
        
    }else {
        if (startingPoint->left == nullptr){
            startingPoint->left = nodeToPush;
        }else{
            //continue to traverse through the list
            pushFrom(startingPoint->left, nodeToPush);
        }
        
    }
    
}

TreeNode* Tree::find(int value)const{
    //implement the find FRom function
    return findFrom(start,value);
}

TreeNode* Tree::findFrom(TreeNode* startingPoint, int value) const{
    
    //check if list is empty
    if (startingPoint == nullptr) {
        //cout << "That value does not exist. \n";
        return NULL;
    }
    
    //basecase
    if (startingPoint->value == value){
        cout <<"Found " << value << endl;
        return startingPoint;
        
        //recuriseve statments
    }else if (value < startingPoint->value){
        return findFrom(startingPoint->left, value);
    }else{
        return findFrom(startingPoint->right, value);
    }
    
}

void Tree::deleteNode(int value){
    ///helper funcito of deleteFrom
    deleteFrom(start, value);
    
}


TreeNode* Tree::findMin(TreeNode* startintPoint){
    if (startintPoint==NULL){
        return;
    }
    while(startintPoint->left != NULL){
        startintPoint = startintPoint->left;
    }
    return;
}
void Tree::deleteFrom(TreeNode* startintPoint, int value){
    //from example in class, deleting a node
    
    if (startintPoint == NULL){
        return;
    }
    else if(value < startintPoint->value){
        deleteFrom(startintPoint->left, value);
        return;
    }else if(value < startintPoint->value){
        deleteFrom(startintPoint->right, value);
        return;
    }else{
        if (startintPoint->left == NULL && startintPoint->right == NULL){
            delete startintPoint;
            startintPoint = nullptr;
            return;
        }
        else if(startintPoint->left == NULL){
            TreeNode* temp = startintPoint;
            startintPoint = startintPoint->right;
            delete temp;
            return;
        }
        else if(startintPoint->right == NULL){
            TreeNode* temp = startintPoint;
            startintPoint = startintPoint->left;
            delete temp;
            return;
        }
        else{
            TreeNode* temp = findMin(startintPoint->right);
            startintPoint->value = temp->value;
            startintPoint->right = deleteFrom(startintPoint->right, temp->value);
            return;
        }
    }
}



void Tree::print() const{
    
    printFrom(start, 0);
    
}

void Tree::printFrom(TreeNode* startingPoint, int numSpaces) const
{
    //basecase
    if (startingPoint == nullptr) {
        return; // type void so we dont return anyting
    }
    
    for (int i = 0; i < numSpaces; i++) {
        cout << " ";
    }
    
    cout << startingPoint->value << endl;
    numSpaces = numSpaces+2;
    printFrom(startingPoint->left,numSpaces);
    printFrom(startingPoint->right,numSpaces);
}

void Tree::clear(){
    
    if (start == nullptr){
        return;
    }
    
    clearFrom(start);
    start = nullptr;
}

void Tree::clearFrom(TreeNode* startingPoint){
    //check if its already empty
    if (startingPoint == nullptr){
        return;
    }
    clearFrom (startingPoint->left);
    clearFrom (startingPoint->right);
    // getting an error here as a 'signal SIGBARRT' but this is how the book deleted a treeptr
    delete startingPoint;
    
    
    // print();
}
