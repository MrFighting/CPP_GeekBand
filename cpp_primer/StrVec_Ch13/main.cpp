#include <iostream>
#include "StrVec.h"
#include <algorithm>
int main() {
    StrVec words;
    words.push_back("ss");
    words.push_back("sb");
    words.push_back("asf");
    words.push_back("safasfd");
    words.push_back("asfas");
    std::cout<<words.size()<<std::endl;
    //words = StrVec();
    //words = words;
    std::cout<<"cap "<<words.capacity()<<std::endl;
    std::cout<<"sz "<<words.size()<<std::endl;
    for_each(words.begin(), words.end(), [](const std::string &s){std::cout<<s<<std::endl;});
    std::cout<<"exit"<<std::endl;
}