//
// Created by abc84 on 2016/4/8.
//
#include <fstream>
#include <sstream>
#include "TextBuider.h"
#include "QueryResult.h"
TextBuider::TextBuider(ifstream &stream): file(new vector<string>) {
    int no = 0;
    string line;
    while (getline(stream, line)) {
        file->push_back(line);
        no++;
        istringstream words(line);
        string word;
        while(words>>word) {
            cout<<word<<endl;
            auto &l = word_map[word];
            if (!l) {//empty word set of lines
                l.reset(new set<int >);
            }
            l->insert(no);
        }
    }
}

QueryResult TextBuider::query(const string &sought) {
    static shared_ptr<set<int >> nodata(new set<int >);
    auto find = word_map.find(sought);
    if (find == word_map.end()) {//未找到
        //const string &s, shared_ptr<set<line_no>> l,
        //shared_ptr<vector<string>>
        return QueryResult(sought, nodata, file);
    }
    return QueryResult(sought, find->second, file);
}
