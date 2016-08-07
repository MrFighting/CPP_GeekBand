#include <iostream>
#include <algorithm>
#include <string>
#include <list>

using namespace std;
void elimDups(vector<double> &a);
bool predicate(const string&);
int main() {
    vector<int> vec;list<int> ls;int i;
    ls.push_back(1);
    ls.push_back(2);
    ls.push_back(3);
    for (int a : ls) {
        cout<<a;
    }
    copy(ls.cbegin(), ls.cend(), back_inserter(vec));
    cout<<vec[0]<<vec[1]<<vec[2]<<endl;
//    vector<int> vec;
//    vec.reserve(10);
//    fill_n(vec.begin(),10,11);
//    cout<<vec[0]<<vec[9];
//    vector<double> dous{1.1,1.2,1.3,1.1,1.1};
//    elimDups(dous);
//    for (double d : dous) {
//        cout<<d<<"  ";
//    }
    int sz = 3;
    vector<string> word{"a","ag","g","AWE","bkih","zgjih","grr","QO"};
    sort(word.begin(), word.end(),
         [](const string &a, const string &b){return a.size()>b.size();});
    //auto par = partition(word.begin(), word.end(), [sz](const string &a){ return a.length()>=sz;});
    for (auto it = word.begin(); it != word.end(); it++) {
        cout<<*it<<" ";
    }
}

bool predicate(const string &a) {
    return a.size()>=3;
}
//void elimDups(vector<double> &a) {
//    sort(a.begin(), a.end());
//    auto end_unique = unique(a.begin(), a.end());
//    cout<<*end_unique<<endl;
//    a.erase(end_unique, a.end());
//}