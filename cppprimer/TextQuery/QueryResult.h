//
// Created by abc84 on 2016/4/8.
//

#ifndef TEXTQUERY_QUREYRESULT_H
#define TEXTQUERY_QUREYRESULT_H

#include <memory>
#include <set>
#include <vector>
#include "TextBuider.h"

using namespace std;

class QueryResult {
    friend ostream& print(ostream&, const QueryResult);
public:
    QueryResult(const string &s, shared_ptr<set<int>> l,
                             shared_ptr<vector<string>> f):sought(s), lines(l), file(f){
    }
private:
    string sought;
    shared_ptr<set<int>> lines;
    shared_ptr<vector<string>> file;
};


#endif //TEXTQUERY_QUREYRESULT_H
