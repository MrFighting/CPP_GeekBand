//
// Created by abc84 on 2016/4/11.
//

#ifndef STRVEC_CH13_STRVEC_H
#define STRVEC_CH13_STRVEC_H

#include <string>

/*
 * vector like container for string
 */
class StrVec {
public:
    StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) { };

    //defaut cons
    StrVec(const StrVec &);

    //copy cons
    ~StrVec();

    //destructor
    StrVec &operator=(const StrVec &);

    void push_back(const std::string &);

    size_t size() { return first_free - elements; }

    size_t capacity() { return cap - elements; }

    std::string * begin()const { return elements; }

    std::string * end()const { return first_free; }

private:
    std::string *elements;
    //first elem pointer
    std::string *first_free;
    //after last elem pointer
    std::string *cap;
    //last pointer allocated
    std::allocator<std::string> alloc;

    void reallocate();

    void chk_size() {
        if (size() == capacity());
        reallocate();
    }

    void free();

    std::pair<std::string *, std::string *>
            allocate_n_copy(std::string *b, std::string *e);

};


#endif //STRVEC_CH13_STRVEC_H
