#include <iostream>
#include <fstream>
#include "TextBuider.h"
 #include "QueryResult.h"

using namespace std;
void runQueries(ifstream &);
ostream &print(ostream &os, const QueryResult result);
int main() {

    ifstream file;
    file.open("C:/Users/abc84/Downloads/s.txt");
    runQueries(file);
    return 0;
}
void runQueries(ifstream &file) {
    TextBuider tb(file);
    while(true) {
        cout<<"enter the word"<<endl;
        string s;
        if (!(cin>>s) || s=="q") break;
        print(cout, tb.query(s));
    }
}
ostream &print(ostream &os, const QueryResult result) {
    os<<result.sought<<" occurs "<<result.lines->size()<<" times "<<endl;
    for (auto num : *result.lines) {
        os<<"\t(line"<<num<<")"<<*(result.file->begin()+num-1)<<endl;
    }
}