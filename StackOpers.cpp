//
// Created by oem on 23.06.2020.
//

#include "StackOpers.h"

char StackOpers::look(float i) {
    element *res = ptr;
    for(int j=0;j<i;j++){
        res = res->next;
    }
    return res->d;
}

void StackOpers::push(char d) {
    element* e = new element();
    e->d = d;
    if(ptr == nullptr){
        ptr = e;
    }else{
        e->next = ptr;
        ptr = e;
    }
    ++StackOpers::size;
}
char StackOpers::pop() {
    if(ptr!= nullptr) {
        char ret = ptr->d;
        StackOpers::size--;
        if (StackOpers::size == 0) {
            delete ptr;
            ptr = nullptr;
            return ret;
        }
        ptr = ptr->next;
        return ret;
    }
    return '!';
}

bool StackOpers::empty(void) const {
    return (size==0);
}

void StackOpers::clear(void) {
    while (!this->empty())
        this->pop();
}