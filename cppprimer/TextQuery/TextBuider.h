//
// Created by abc84 on 2016/4/8.
//

#ifndef TEXTQUERY_TEXTBUIDER_H
#define TEXTQUERY_TEXTBUIDER_H

#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include <set>

using namespace std;
class QueryResult;
class TextBuider {
public:
    TextBuider(ifstream &);
    QueryResult query(const string &);
private:
    map<string,shared_ptr<set<int>>> word_map;
    shared_ptr<vector<string>> file;
};


#endif //TEXTQUERY_TEXTBUIDER_H
