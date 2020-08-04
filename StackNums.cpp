#include "StackNums.h"

float StackNums::look(float i) {
    element *res = ptr;
    for(int j=0;j<i;j++){
        res = res->next;
    }
    return res->d;
}
void StackNums::push(float d) {
    element* e = new element();
    e->d = d;
    if(ptr == nullptr){
        ptr = e;
    }else{
        e->next = ptr;
        ptr = e;
    }
    ++StackNums::size;
}
float StackNums::pop() {
    if(ptr!= nullptr) {
        float ret = ptr->d;
        StackNums::size--;
        if (StackNums::size == 0) {
            delete ptr;
            ptr = nullptr;
            return ret;
        }
        ptr = ptr->next;
        return ret;
    }
    return '!';
}

bool StackNums::empty(void) const {
    return (ptr== nullptr);
}

void StackNums::clear(void) {
    while (!this->empty())
        this->pop();
}