#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void biggies(vector<string> &, vector<string>::size_type);

int main() {
    vector<string> words{"a","aa","aaa","aaaa","aaaaaa"};
    vector<string> null;

    //unique_copy(words.cbegin(), words.cend(), front_inserter(null));
    cout<<null[0]<<endl<<null[1]<<endl;
    auto count = count_if(words.begin(), words.end(),
                          [](const string &a){ return a.size()>=2;});
    cout<<count<<endl;
    biggies(words,3);
    return 0;
}

void biggies(vector<string> &words, vector<string>::size_type sz) {
    auto par = partition(words.begin(), words.end(),
                         [sz](const string &a){return a.size()>=sz;});//lambda expression
    for_each(words.begin(), par, [](const string &a){cout<<a<<" ";});//use for-each to print
}