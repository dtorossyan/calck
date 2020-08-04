//
// Created by oem on 23.06.2020.
//

#ifndef UNTITLED1_STACKNUMS_H
#define UNTITLED1_STACKNUMS_H

#include <cstddef>

class StackNums {
    struct element {
        float d;
        element* next;
    };
private:
    element* ptr;
public:
    StackNums(void) : ptr(nullptr) {size = 0;}
    ~StackNums() {
        this->clear();
    }
    float look(float i);
    void push(float d);
    float pop(void);
    size_t size;
    bool empty(void) const ;
    void clear(void);
};



#endif //UNTITLED1_STACKNUMS_H
