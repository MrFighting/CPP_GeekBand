//
// Created by abc84 on 2016/4/11.
//

#include "StrVec.h"
#include <memory>
#include <algorithm>
#include <iostream>
using namespace std;
void StrVec::reallocate() {
    cout<<"realloc: now size"<<size()<<endl;
    size_t newcap = size() ? 2*size() : 1;
    auto data = alloc.allocate(newcap);
    auto temp = data;
    for_each(elements, first_free, [this, &temp](std::string &s){alloc.construct(temp++, s);});
    free();
    elements = data;
    first_free = temp;
    cap = elements + newcap;
    cout<<"after realloc: size"<<size()<<endl;

}

void StrVec::free() {
    cout<<"free"<<endl;
    if (elements) { //若分配了
        for_each(elements, first_free,
                 [this](std::string &rhs){ alloc.destroy(&rhs); });//must capture this
        alloc.deallocate(elements, cap - elements);
    }
}

StrVec::StrVec(const StrVec &vec) {
    //auto data = allocate_n_copy(vec.elements, vec.first_free);
    auto data = allocate_n_copy(vec.begin(), vec.end());
    elements = data.first;
    first_free = data.second;
    cap = first_free;
}

StrVec::~StrVec() {
    cout<<"~StrVec()"<<endl;
    free();
}

StrVec &StrVec::operator=(const StrVec &vec) {
    cout<<"operator=()"<<endl;
    auto data = allocate_n_copy(vec.begin(), vec.end());//prevent from free this it self
    free();
    elements = data.first;
    first_free = data.second;
    cap = first_free;
    return *this;
}

void StrVec::push_back(const std::string & s) {
    cout<<"push_back"<<endl;

    chk_size();
    alloc.construct(first_free++, s);
}

std::pair<std::string *, std::string *>

    StrVec::allocate_n_copy(std::string *b, std::string *e) {//used in copy cons and oper=
    auto start = alloc.allocate(e - b);
    cout<<"allocate_n_copy"<<endl;
    return {start, std::uninitialized_copy(b, e, start)};
}
