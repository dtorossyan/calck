//
// Created by oem on 23.06.2020.
//

#ifndef UNTITLED1_STACKOPERS_H
#define UNTITLED1_STACKOPERS_H


#include <cstddef>

class StackOpers {
    struct element {
        char d;
        element* next;
    };
private:
    element* ptr;
    int getlen(int nom);
public:
    StackOpers(void) : ptr(nullptr) {size=0;}
    ~StackOpers() {
        this->clear();
    }
public:
    char look(float i);
    void push(char d);
    char pop(void);
    size_t size;
    bool empty(void) const ;
    void clear(void);
};



#endif //UNTITLED1_STACKOPERS_H
