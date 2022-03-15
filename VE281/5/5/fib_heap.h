
//
// Created by 69009 on 2019/11/3.
//

#ifndef FIB_HEAP_H
#define FIB_HEAP_H

#include <algorithm>
#include <cmath>
#include "priority_queue.h"
using namespace std;

// OVERVIEW: A specialized version of the 'heap' ADT implemented as a
//           Fibonacci heap.
template<typename TYPE, typename COMP = std::less<TYPE> >
class fib_heap: public priority_queue<TYPE, COMP> {
public:
    typedef unsigned size_type;

    // EFFECTS: Construct an empty heap with an optional comparison functor.
    //          See test_heap.cpp for more details on functor.
    // MODIFIES: this
    // RUNTIME: O(1)
    fib_heap(COMP comp = COMP());

    // EFFECTS: Deconstruct the heap with no memory leak.
    // MODIFIES: this
    // RUNTIME: O(n)
    ~fib_heap();

    // EFFECTS: Add a new element to the heap.
    // MODIFIES: this
    // RUNTIME: O(1)
    virtual void enqueue(const TYPE &val);

    // EFFECTS: Remove and return the smallest element from the heap.
    // REQUIRES: The heap is not empty.
    // MODIFIES: this
    // RUNTIME: Amortized O(log(n))
    virtual TYPE dequeue_min();

    // EFFECTS: Return the smallest element of the heap.
    // REQUIRES: The heap is not empty.
    // RUNTIME: O(1)
    virtual const TYPE &get_min() const;

    // EFFECTS: Get the number of elements in the heap.
    // RUNTIME: O(1)
    virtual size_type size() const;

    // EFFECTS: Return true if the heap is empty.
    // RUNTIME: O(1)
    virtual bool empty() const;

private:
    // Note: compare is a functor object
    COMP compare;

private:
    // Add any additional member functions or data you require here.
    // You may want to define a strcut/class to represent nodes in the heap and a
    // pointer to the min node in the heap.

    size_type n;
    void Make_Fibonacci_Heap();
    struct node_t{
        int degree;
        node_t *parent;
        node_t *child;
        node_t *r_sibling;
        node_t *l_sibling;
        TYPE key;
    };
    node_t *min;
    void add_to_root(node_t *node);
    void remove_root(node_t *node);
    void Consolidate();
    void Fibonacci_Heap_Link(node_t *y, node_t *x);
    void destroy(node_t *node);
};

// Add the definitions of the member functions here. Please refer to
// binary_heap.h for the syntax.

template<typename TYPE, typename COMP>
fib_heap<TYPE, COMP> :: fib_heap(COMP comp) {
    compare = comp;
    // Fill in the remaining lines if you need.
    Make_Fibonacci_Heap();
}

template<typename TYPE, typename COMP>
void fib_heap<TYPE,COMP>::Make_Fibonacci_Heap(){
    n = 0;
    min = nullptr;
}

template<typename TYPE, typename COMP>
void fib_heap<TYPE,COMP>::add_to_root(fib_heap<TYPE,COMP>::node_t *node){
     node_t *temp = min->l_sibling;
    temp->r_sibling = node;
    node->l_sibling = temp;
    min->l_sibling = node;
    node->r_sibling = min;
}

template<typename TYPE, typename COMP>
void fib_heap<TYPE,COMP>::enqueue(const TYPE &val){
    //Create a new node
    node_t *node = new node_t;
    node->degree = 0;
    node->parent = nullptr;
    node->child = nullptr;
    node->l_sibling = nullptr;
    node->r_sibling = nullptr;
    node->key = val;

    if(min == nullptr){
        //CREATE A NEW ROOT
        min = node;
        node->l_sibling=node;
        node->r_sibling=node;
    }
    else{
        //INSERT NEW_NODE INTO THE ROOT
        add_to_root(node);
        if(compare(node->key,min->key)) min = node;
    }
    n = n + 1;
}

template<typename TYPE, typename COMP>
void fib_heap<TYPE, COMP>::remove_root(fib_heap<TYPE, COMP>::node_t *node) {
    node_t *l_temp = node->l_sibling;
    node_t *r_temp = node->r_sibling;
    r_temp->l_sibling = l_temp;
    l_temp->r_sibling = r_temp;
    if(min == node){
        //Update min
        min = node->l_sibling;
        if(min != nullptr){
            for(node_t *begin = min->l_sibling; begin != node->l_sibling; begin = begin->l_sibling){
                if(begin == nullptr) break;
                if(compare(begin->key,min->key)) min = begin;
            }}
    }
}


template<typename TYPE, typename COMP>
void fib_heap<TYPE, COMP>::Consolidate() {
    int max_degree;
    node_t *begin = min;
    max_degree = begin->degree;
    for(begin = begin->l_sibling; begin != min; begin = begin->l_sibling){
        if(begin->degree > max_degree) max_degree = begin->degree;
    }
    vector<node_t*>A((unsigned) max_degree + 2,nullptr);
    node_t *next = min;
    node_t *flag=min;
    while(1){
        node_t* circle = next;
        next = next->l_sibling;
        if(circle == nullptr) break;
        while(A[circle->degree] != nullptr){
            node_t *y = A[circle->degree];
            if(compare(y->key, circle->key)) {
                //exchange;
                node_t* temp = circle;
                circle = y;
                y = temp;
            }
            Fibonacci_Heap_Link(y,circle);
            A.push_back(nullptr);
            A[circle->degree - 1] = nullptr;
        }
        A[circle->degree] = circle;
        if(next == flag) break;
    }
    min = nullptr;
    for(int i = 0; i < A.size(); i++){
        if(A[i] != nullptr){
            if(min == nullptr){
                //Create a root list for H only containing A[i]
                min = A[i];
                A[i]->l_sibling=A[i];
                A[i]->r_sibling=A[i];
            }
            else{
                add_to_root(A[i]);
                    if(compare(A[i]->key,min->key)) min = A[i];
            }
        }
    }
}

template<typename TYPE, typename COMP>
void fib_heap<TYPE,COMP>::Fibonacci_Heap_Link(fib_heap<TYPE, COMP>::node_t *y, fib_heap<TYPE, COMP>::node_t *x) {
    //remove y;
    node_t *l_temp = y->l_sibling;
    node_t *r_temp = y->r_sibling;
    r_temp->l_sibling = l_temp;
    l_temp->r_sibling = r_temp;
    //make y a child of x
    y->parent = x;
    if(x->child == nullptr){
        x->child = y;
        y->l_sibling = y->r_sibling = y;//nullptr;
    }
    else{
        if(x->child->l_sibling == nullptr){
            x->child->l_sibling = y;
            x->child->r_sibling = y;
            y->l_sibling = x->child;
            y->r_sibling = x->child;
        }
        else{
            node_t *temp = x->child->l_sibling;
            x->child->l_sibling = y;
            temp->r_sibling = y;
            y->l_sibling = temp;
            y->r_sibling = x->child;
        }
    }
    x->degree++;

}

template<typename TYPE, typename COMP>
TYPE fib_heap<TYPE,COMP>::dequeue_min(){
    node_t *z = min;
    if(z != nullptr){
        if(z->child != nullptr){
            node_t *flag = z->child;
            z->child = nullptr;
            flag->parent = nullptr;
            node_t *begin = flag->l_sibling;
            add_to_root(flag);
            if(begin != nullptr){
                for(;begin != flag;){
                    if(begin == nullptr) break;
                    node_t *temp = begin->l_sibling;
                    begin->parent = nullptr;
                    add_to_root(begin);
                    begin = temp;
                }
            }
        }
        remove_root(z);
        n--;
        if(n == 0) min = nullptr;
        else Consolidate();
    }
    TYPE val = z->key;
    delete z;
    return val;
}

template<typename TYPE, typename COMP>
const TYPE &fib_heap<TYPE,COMP>::get_min() const{
    return min->key;
}

template<typename TYPE, typename COMP>
unsigned fib_heap<TYPE,COMP>::size() const {
    return n;
}

template<typename TYPE, typename COMP>
bool fib_heap<TYPE,COMP>::empty() const{
    return (n == 0);
}

template<typename TYPE, typename COMP>
void fib_heap<TYPE,COMP>::destroy(fib_heap<TYPE, COMP>::node_t *node) {
    if(node == nullptr) return;
    node_t *begin = node->l_sibling;
    for(;begin!=node;){
        node_t *temp = begin->l_sibling;
        destroy(begin->child);
        delete begin;
        begin = temp;
    }
    delete node;
}

template<typename TYPE, typename COMP>
fib_heap<TYPE,COMP>::~fib_heap() {
    destroy(min);
}

#endif //FIB_HEAP_H
