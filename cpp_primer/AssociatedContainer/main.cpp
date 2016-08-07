#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;
string ch = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

void stoupper(string &a);
int main() {
/*
 * word counter
 */
//    map<string, size_t > counter;
//    string word;
//    multiset<int> s;
//    s.begin();
//    while(cin >> word) {
//        if (word == "end")break;
//        auto pos = word.find_first_not_of(ch);
//        if (pos != string::npos)
//            word.erase(pos,word.size()-pos);//substr(0,pos);
//        //cout<<word<<endl;
//        stoupper(word);
//        counter[word]++;
//    }
//    for (const auto &w : counter) {
//        cout<<w.first<<" : "<<w.second<<endl;
//    }
//    return 0;

/*
 * copy
 */
//    vector<int>a{1,2,3,4};
//    multiset<int> ms(a.begin(),a.end());
//    //multiset<int>::const_iterator it = ms.begin();
//    //copy(a.begin(),a.end(),inserter(ms, it));
//    for (int i : ms) {
//        cout<<i<<endl;
//    }

    /*
     * multimap(1)
     */
//    multimap<string,string> author;
//    author.insert({"lee","book1"});
//    author.insert({"lee","book2"});
//    auto count = author.count("lee");
//    auto it = author.find("lee");
//    while(count) {
//        cout<<it->second<<endl;
//        it++;
//        count--;
//    }
    /*
     * multimap(2)与上面功能一一致使用upperbound，lowerbound
     */
//    multimap<string,string> author;
//    author.insert({"lee","book1"});
//    author.insert({"lee","book2"});
//    auto beg = author.lower_bound("lee");
//    auto end = author.upper_bound("lee");
//    for (;beg != end; beg++) {
//        cout<<beg->second<<endl;
//    }
    /*
     * multimap(3)与上面功能一一致，使用equal_bound
     */
    multimap<string,string> author;
    author.insert({"lee","book1"});
    author.insert({"lee","book2"});
    pair<multimap<string,string>::iterator,multimap<string,string>::iterator>
            bound = author.equal_range("lee");
    for(auto beg = bound.first; beg != bound.second; beg++) {
        cout<<beg->second<<endl;
    }


}

void stoupper(string &a) {
    for (char &c : a) {
        c = toupper(c);
    }
    cout<<"after"<<a<<endl;
}
