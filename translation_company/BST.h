//
//  BST.h
//  translation_company
//
//  Created by Eduardo Almeida on 19/11/13.
//  Copyright (c) 2013 Bitten Apps. All rights reserved.
//

//
//  Adapted from https://raw.github.com/jatins/Binary-Search-Tree-in--cpp/master/Binary%20Search%20Tree%20Implementation%20in%20C++.cpp
//

#ifndef __translation_company__BST__
#define __translation_company__BST__

#include <iostream>
#include <cstdio>
using namespace std;

template <class T> class Node {
    
public:
	T *item;
	Node *left;
	Node *right;
    
	Node(T *ti, Node *l = 0, Node*r = 0) {
		item = ti; left= l; right = r;
	}
};


template <class T> class Tree{
	Node<T> *root;
    
	Node<T>* search(Node<T> *q, int obj) {
        while (q->item != obj && q!=0) {
            if (obj < q->item)
                q = q->left;
            else
                q = q->right;
        }
        
        return q;
    }
    
	void insert(Node<T> *&q, int obj) {
        Node<T> *temp = q, *prev = q;
        while(temp != 0) {
            prev = temp;
            if(obj < temp->item)
                temp = temp->left;
            else
                temp = temp->right;
        }
        
        if (!q) {
            q = new Node<T>(obj);
        } else {
            if (obj < prev->item)
                prev->left = new Node<T>(obj);
            else
                prev->right = new Node<T>(obj);
        }
    }
    
	void inorder(Node<T> *q) const {
        if (q!=0) {
            inorder(q->left);
            printf("%d  ", q->item);
            inorder(q->right);
        }
    }
    
	void visit(Node<T> *p) const {
		printf("%d\t", p->item);
	}
    
	void transplant(Node<T> *u, Node<T> *v) {
		Node<T> *pa = parent(u);
		if(pa == 0)
			root = v;
		else if (u == pa->left)
			pa->left = v;
		else
            pa->right = v;
	}
    
	int minimum(Node<T> *node) {
        Node<T> *temp = node;
        
        while(temp->left != 0) {
            temp = temp->left;
        }
        
        return temp->item;
    }
    
	int maximum(Node<T> *node) {
        Node<T> *temp = node;
        
        while(temp->right != 0) {
            temp = temp->right;
        }
        
        return temp->item;
    }
    
public:
	Tree() {
		root = nullptr;
	}
    
	void inorder() {
		inorder(root);
	}
    
	void insert(T obj){
		insert(root, obj);
	}
    
	Node<T>* search(Node<T> obj){
		return search(root, obj);
	}
    
	void del(Node<T> *&q) {
        if (!q->left)
            transplant(q, q->right);
        else if (!q->right)
            transplant(q, q->left);
        else {
            Node<T> *succ = search(minimum(q->right));
            
            if (parent(succ) != q) {
                transplant(succ, succ->right);
                succ->right = q->right;
            }
            
            transplant(q, succ);
            succ->left = q->left;
        }
        
        delete q;
        
        q = 0;
    }
    
	Node<T>* parent(Node<T>* node) const{
		Node<T> *temp = root;
        
		while(temp->left!=node && temp->right!=node) {
			if(node->item < temp->item)
				temp = temp->left;
			else
				temp = temp->right;
		}
        
		return temp;
	}
    
	T maximum() {
		return maximum(root);
	}
    
	T minimum() {
		return minimum(root);
	}
    
	T successor(T obj) {
        Node<T> *temp = search(obj);
        
        if(temp->right) {
            return minimum(temp->right);
        } else {
            Node<T> *y = parent(temp);
            
            while (y!=0  &&  temp == y->right) {
                temp = y;
                y = parent(temp);
            }
            
            return y->item;
        }
    }
};

#endif /* defined(__translation_company__BST__) */
