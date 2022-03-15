//
// Created by 69009 on 2019/7/20.
//

#ifndef P5_DLIST_IMPL_H
#define P5_DLIST_IMPL_H

#include "dlist.h"

template <class T>
bool Dlist<T>::isEmpty() const {
    return (first == nullptr);
}

template <class T>
void Dlist<T>::insertFront(T *op) {
    node *np = new node;
    np->next = first;
    np->prev = nullptr;
    np->op = op;
    if(isEmpty()) last = np;
    else np->next->prev = np;
    first = np;
}

template <class T>
void Dlist<T>::insertBack(T *op) {
    node *np = new node;
    np->next = nullptr;
    np->prev = last;
    np->op = op;
    if(isEmpty()) first = np;
    else np->prev->next = np;
    last = np;
}

template  <class T>
T* Dlist<T>::removeFront() {
    if(isEmpty()){
        emptyList e;
        throw e;
    }
    node *victim = first;
    T *result;
    first = victim->next;
    if(first == nullptr) last = nullptr;
    else first->prev = nullptr;
    result = victim->op;
    delete victim;
    return result;
}

template <class T>
T* Dlist<T>::removeBack() {
    if(isEmpty()){
        emptyList e;
        throw e;
    }
    node *victim = last;
    T *result;
    last = victim->prev;
    if(last == nullptr) first = nullptr;
    else last->next = nullptr;
    result = victim->op;
    delete victim;
    return result;
}

template <class T>
void Dlist<T>::removeAll() {
    while(!isEmpty()){
        T *op = removeFront();
        delete op;
    }
}

template  <class T>
void Dlist<T>::copyAll(const Dlist &l) {
    if(!l.first) return;
    node *current = l.first;
    while(current){
        T *o = new T(*current->op);
        this->insertBack(o);
        current = current->next;
    }
}

template <class T>
Dlist<T>::Dlist()
: first(nullptr),last(nullptr)
{}

template <class T>
Dlist<T>::Dlist(const Dlist &l)
: first (nullptr),last(nullptr)
{
    copyAll(l);
}

template <class T>
Dlist<T>& Dlist<T>::operator=(const Dlist<T> &l) {
    if (this != &l) {
        removeAll();
        copyAll(l);
    }
    return *this;
}

template <class T>
Dlist<T>::~Dlist() {
    removeAll();
}

#endif //P5_DLIST_IMPL_H
