//
// Created by abc84 on 2016/4/10.
//

#ifndef COPYANDDESTRUCT_HASPTR_H
#define COPYANDDESTRUCT_HASPTR_H

#include <string>

using namespace std;

class HasPtr {
public:
    HasPtr():s(new string()), i(0), use(new size_t(1)){};
    HasPtr(const HasPtr&);//copy constructor
    HasPtr &operator=(const HasPtr&);
    ~HasPtr();
private:
    int i;
    string *s;
    size_t *use;
};


#endif //COPYANDDESTRUCT_HASPTR_H
