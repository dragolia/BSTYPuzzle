#include "BSTY.hpp"
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

BSTY::BSTY() {
	root = NULL;
}

// You write:  insert a new node with data x (a string) into the 
// binary search tree
// This method should return true if a new node is inserted and 
// false if the data x is already in the tree
// Remember to check whether the new node will be the root
// (meaning the root is currently NULL) and if so, set the root
// to be the new node.
// Note: Make sure you make the new node point to its parent!!! 
// Note2: after you've inserted a new node, you should call the 
// adjustHeights method that will update the heights of all the 
// ancestors of the node that was just inserted.
bool BSTY:: insertit(string x ) {
	if (root==NULL){ //If list is empty, new node starts list and is set to root
		root= new NodeT(x);
		return true;
	}
	else{ // if root not null add either the left or right child
		NodeT *n =root;
		while(n!=NULL){
			if(x<n->data){//if new node data is less than current node, move to the left child
				if(n->left==NULL){// if no left child, new node becomes left child
					n->left=new NodeT(x);
					n->left->parent=n; //New node's parent set to previous node
					adjustHeights(n); //heights of ancestors are adjusted
					return true;
				}
				else{
					n=n->left;
				}
			}
			else if(x>n->data){ // if new node data is greater than current node data, move to right child
				if(n->right==NULL){//if no right child, new node becomes right child
					n->right=new NodeT(x);
					n->right->parent=n; //New node's parent set to previous node
					adjustHeights(n); //heights of ancestors are adjusted
					return true;
				}
				else{
					n=n->right;
				}
			}
			else{ //if function fails, returns false.
				return false;
			}
		}
	}
    //cout<<"insertit 1"<<endl;
}

// the adjustHeights method updates the heights of every ancestor of the node n.
// This method will be massively useful with our next lab, so make sure you have 
// this working now.  It should be called whenever you change the height of a 
// a particular node.  So, for instance, when a new node is inserted as a leaf, 
// its height is 1.  The adjustHeights method should then check the parent to see
// if the height of the parent changes (the height of each node is the maximum of 
// the height of the left child and the height of the right child, plus 1).  If 
// the parent's height changes, then the grandparent's height should be checked and,
// if necessary, adjusted.  If the grandparent's height is updated, then the great-
// grandparent's height should be adjusted, etc.  The checking stops when either 
// the loop has worked its way up to the root, or until the currently being checked
// ancestor is not changed.  
void BSTY::adjustHeights(NodeT *n) {
	while(n!=NULL){ //While the node pointer is not pointing to nothing, i.e., past the root.
        if(n->right==NULL&&n->left!=NULL){//If the node in question has no right child but it does have a left
            n->height=n->left->height+1; //The node is set to the height of its child plus one.
            n=n->parent; //pointer points to parent node to contnue the process
        }
        else if(n->left==NULL&&n->right!=NULL){ //If the node in question has no left child but it does have a right
            n->height=n->right->height+1; //See above
            n=n->parent; //See above
        }
        else if(n->left==NULL&&n->right==NULL){ //If the node in question has no children.
            n->height=1; //Height is set to 1
            n=n->parent; //See above
        }
        else{ //Node has both left and right children
            if(n->left->height>=n->right->height){  //If left node's height is greater than  or equal to right node's
                if(n->height!=(n->left->height)+1){ //If current node's height is not left node's height plus one
                    n->height=(n->left->height)+1; //Change the node's height
                    n=n->parent; //See above
                }
                else{ //If node height not needing adjustment.
                    return; //Stop the function
                }
            }
            else{ //If right node' height is greater than left node's
                if(n->height>=n->right->height+1){ //If node is in need of adjusting
                    n->height=n->right->height+1; //Adjust the height
                    n=n->parent; //See above
                }
                else{ //If node is not in need of adjusting
                    return; //Stop the function
                }
            }

        }

	}
}

void BSTY::printTreeIO() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		printTreeIO(root);
	}
}

// Print the tree in order (left child, then parent, then right child).
// Use the slides, but make sure you can understand how the tree is 
// traversed in order
void BSTY::printTreeIO(NodeT *n) {
	if(n==NULL){
		return;
	}
	else{
		printTreeIO(n->left);//print the left child of the node
		n->printNode();//print the node
		printTreeIO(n->right);//print the right child of the node
	}
}

void BSTY::printTreePre() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		printTreePre(root);
	}
}

// Prints the tree using pre-order traversal (parent, then left child, then right
// child.  Use the slides, but make sure you understand how a tree is traversed in
// pre-order
void BSTY::printTreePre(NodeT *n) {
	if(n==NULL){
		return;
	}
	else{
		n->printNode();//print the node
		printTreePre(n->left);//print the left child of the node
		printTreePre(n->right);//print the right child of the node
	}
}

void BSTY::printTreePost() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		printTreePost(root);
		cout << endl;
	}
}

// Prints the tree using pre-order traversal (left child, then right, then parent)
// Use the slides, but make sure you understand how a tree is traversed in
// post-order
void BSTY::printTreePost(NodeT *n) {
	if(n==NULL){
		return;
	}
	else{
		printTreePost(n->left);//print the left child of the node
		printTreePost(n->right);//print the right child of the node
		n->printNode();//print the node
	}
	}
void BSTY::myPrint() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		myPrint(root);
		cout << endl;
	}
}
void BSTY::myPrint(NodeT *n) {
	if (n == NULL) {
		return;
	}
	else {
		myPrint(n->left);
		cout << n->data.length()-1;
		if (mine) {
			cout <<".";
			mine = false;
		}
		myPrint(n->right);
	}
}

// the find method takes as input a string, and finds whether that string is already
// in the tree or not.  If it is in the tree, that node is returned from the tree.
// If it isn't, NULL is returned.  
// NOTE: If the node can't be found, this method prints out that x can't be found.
// if it is found, the printNode method is called for the node.  
NodeT *BSTY::find(string x) {
	NodeT *n=root;
	while(n!=NULL){//while it not null
		if(x<n->data){//if x is less than the node data
			n=n->left; // n point to the left child
		}
		else if(x>n->data){//if x is greater than the node data
			n=n->right; //n point to right child
		}
		else{ // if n's data equal x
            cout<<n->data<<" found"<<endl;
			return n;
		}
	}
	cout<<"Node containing "<<x<<" not found in Tree."<<endl;
	return NULL;
}

/*************************************************************************************/
/* Extra Credit Methods                                                              */
/* Challenging: worth 35 EC pts to go towards labs                                   */
/* NOTE: IF YOU CHOOSE NOT TO IMPLEMENT THESE METHODS, YOU ARE STILL RESPONSIBLE FOR */
/* UNDERSTANDING HOW THEY WORK!!                                                     */
/*************************************************************************************/
/* When removing a node from a binary search tree, the resulting tree MUST BE a binary
/* search tree.  
/*
/* When removing a node, there are 3 conditions:
/* 1: when the node being removed has no children, in which case the node is deleted,
/* the node's parent is set to NULL, and the node's parent's height is adjusted (if
/* necessary) and heights on up are adjusted.
/* 2: when the node being removed has one child, in which case the node's parent points
/* to the node's child, and the node's child points to the node's parent, and the node
/* is deleted (and the height of the parent on up as necessary is adjusted)
/* 3: when the node has 2 children, in which case the left-most child of the node's 
/* right child replaces the node.  
/* A couple of notes about this one: you are replacing a node with a node that is lower
/* down in the tree.  That means that you are, in essence, removing the node from that
/* lower position and moving it up to the old node's location.  Thus the replacing node
/* must be removed using 1 or 2 above (why not 3?).  The heights must be adjusted after 
/* the replacing node is removed from its old location but before it is inserted into its 
/* new location.  Equally, the replacing node's height must be adjusted to be the larger of
/* its two children's heights before you adjust heights above that.  
/*****************************************************************************************/
/* remove(): takes as input a string, uses the find method to find the node in the tree that
/* holds that string, and then calls replace1, replace2, or replace3 depending on what type
/* of replacing should be done.  It adjusts the heights, deletes teh node, and returns 
/* true if the removal was successful.
*/
bool BSTY::remove(string s) {
    NodeT *n= find(s);
    if(n->right==NULL&&n->left==NULL){ // if node both children are null
        remove1(n);//call remove1
        return true;
    }
    else if(n->right!=NULL&&n->left==NULL){//if left child is null and right is not.
        remove2(n);
        return true;
    }
    else if(n->left!=NULL&&n->right==NULL){//if right child is null and left is not.
        remove2(n);
        return true;
    }
    else if(n==NULL){// if n is null
        cout<<"removal failed"<<endl;
        return false;
    }
    else{//if both children are not null.
        remove3(n);
        return true;
    }
}

/* remove1(): called when the node to be removed has no children. Takes as input the 
/* node to be removed, and sets the parent of the node to point to NULL.
/* helpful hint: if (n->parent->left == n) is true, then n is its parent's left child.
/* Make sure you check to whether n is the root or not.
*/
void BSTY::remove1(NodeT *n) {
    if(n->data<n->parent->data){//if the node's data less then the parent's data
        n->parent->left=NULL;//parent's left child is null and removed.
        adjustHeights(n->parent);//Height's of n's parent is adjusted
        delete n; //n is deleted
    }
    else{//if node's data is greater then parent
        n->parent->right=NULL;//parent's right child is remove
        adjustHeights(n->parent);//Height's of n's parent is adjusted
        delete n; //n is deleted
    }
}

/* remove2(): called when the node to be removed has 1 child only.  Takes as input
/* the node to be removed and bypasses it by making the parent point to the node's
/* one child, and makes the node's one child point to the node's parent.  
/* This one needs a bunch of checking - you need to see if the node is the parent's
/* left or right child, and you need to see if the node's child is its left or its
/* right child.
/* Also, make sure you check that if the node to be removed is the root, then the 
/* one child becomes the root.
*/ 
void BSTY::remove2(NodeT *n) {
    if(n->data<n->parent->data){ //If n's data is less than its parent's data
        if(n->left!=NULL){ //If n's left child is not null.
            n->parent->left=n->left; //N's left child becomes n's parent's left child
            n->left->parent=n->parent;// n's parent becomes n's child's parent
            adjustHeights(n->parent); //Adjust height of n's parent
            delete n;
        }
        else{ //If n's left child is null.
            n->parent->left=n->right;//n's right child becomes n's parent's left child
            n->right->parent=n->parent; //n's parent becomes n's right child's parent
            adjustHeights(n->parent); //Adjust height of n's parent
            delete n;
        }
    }
    else{//if n's data is greater than its parent's data
        if(n->left!=NULL){ //if n's left child is not null
            n->parent->right=n->left;//N's left child becomes n's parent's right child
            n->left->parent=n->parent;//n's parent becomes n's left child's parent
            adjustHeights(n->parent);//Adjust height of n's parent
            delete n;
        }
        else{
            n->parent->right=n->right; //N's right child becomes n's parent's right child
            n->right->parent=n->parent;//n's parent becomes n's right child's parent
            adjustHeights(n->parent);//Adjust height of n's parent
            delete n;
        }
    }

}

/* remove3(): called when the node to be removed has 2 children.  Takes as input the
/* node to be removed.  The node to replace the node to be removed should be the 
/* left-most descendent of the node's right child.  That way the binary search tree
/* properties are guaranteed to be maintained.
/* When replacing the node to be removed with the replacing node, the replacing node
/* is, in essence, being removed from its place in the tree, and thus replace1 or 
/* replace2 methods should be used.
/* The new node's parent must be set to the removed node's parent, the removed node's
/* parent must point to the new node, the new node's left child must point to the 
/* removed node's left child (and the child must point to the new node as a parent), 
/* and the same for teh right child.
/* Remember to take into account that the node being removed might be the root.
*/
void BSTY::remove3(NodeT *n) {
    NodeT *tmp=findMin(n->right); //find's the left most descendent of n's right child
    n->data=tmp->data; //n's data tmp's data
    tmp->parent->left=NULL; //tmp is removed from the tree
    adjustHeights(tmp->parent);//Adjust the height of tmp's parent
    delete tmp;
}

/* findMin(): takes as input a node, and finds the left-most descendant of its 
/* right child.  The left-most descendent is returned.
*/
NodeT *BSTY::findMin(NodeT *n) {
    NodeT *tmp=n; //tmp is equal to the input node
    while(tmp->left!=NULL){//while tmp's left child is not null
        tmp=tmp->left; //tmp is equal to tmp's left child
    }
    return tmp;
}

void BSTY::myPrintEC() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		myPrintEC(root);
		cout << endl;
	}
}
void BSTY::myPrintEC(NodeT *n) {
	if (n == NULL) {
		return;
	}
	else {
		myPrintEC(n->left);
		cout << alpha[n->data.length()-2];
		myPrintEC(n->right);
	}
}


/************************************************************************/

