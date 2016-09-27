#include <iostream>
#include <map>
#include <vector>
using namespace std;

map<string, string> mkmap();
const string &wtransform(const string &,map<string, string> &);
const string stransform(const string&, map<string, string> &);
vector<string> split(const string &, char c);

int main() {
    string to_be_trans = "where r u y dont u send me a pic k thk 18r";
    map<string, string> rule = mkmap();
    cout<<stransform(to_be_trans, rule)<<endl;
    //auto it = rule.cbegin();
//    for ( ; it != rule.cend() ; it++) {
//        cout<<it->first<<" : "<<it->second<<endl;
//    }
    return 0;
}

map<string, string> mkmap() {
    string key;
    string val;
    map<string, string> ret;
    while(cin >> key >> val) {
        if (key == "end" && val == "end")break;
        ret[key] = val;
    }
    return ret;
};
const string stransform(const string &a, map<string, string> &rule) {
    vector<string> vec = split(a, ' ');
    string ret;
    for (const string &s : vec) {
        ret += wtransform(s,rule) + " ";
    }
    return ret;
}

const string& wtransform(const string &origin, map<string, string> &rule) {
    auto pos = rule.find(origin);
    if (pos != rule.cend()) {//if word in the rule
        return rule[origin];
    }
    return origin;
}

vector<string> split(const string &a, char c) {
    vector<string> ret;
    string cpy = a;
    unsigned int pos = 0;
    while((pos = cpy.find_first_of(c)) != string::npos) {
        string word = cpy.substr(0,pos);
        cpy = cpy.substr(pos+1,cpy.size());
        ret.push_back(word);
    }
    ret.push_back(cpy);//last word
    return ret;
}
