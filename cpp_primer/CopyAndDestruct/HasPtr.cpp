//
// Created by abc84 on 2016/4/10.
//
#include <iostream>
#include "HasPtr.h"
using namespace std;

HasPtr::HasPtr(const HasPtr &ptr):s(ptr.s), i(0), use(ptr.use) {
    ++*use;//increase the counter
    cout<<"copy from constructor and increase use"<<endl;
}

HasPtr& HasPtr::operator=(const HasPtr & rhs) {
    cout<<"copy from ="<<endl;
    ++*rhs.use;//if rhs = this then first do this will protect this from being deleted from next step
    if (--*use == 0) {//counter becom 0 so that only this point to that
        cout<<"delete s and use because use became 0 from ="<<endl;
        delete s;
        delete use;
    }
    s = rhs.s;
    i = rhs.i;
    use = rhs.use;
    return *this;
}

HasPtr::~HasPtr() {
    cout<<"~HasPtr executed"<<endl;
    if (--*use == 0) {//no ref delete
        cout<<"delete s and use because use became 0"<<endl;
        delete s;
        delete use;
    }
}
