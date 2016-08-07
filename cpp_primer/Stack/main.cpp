#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;
string digts = "0123456789";
void change(string &, string &);
string makeName(string name, string pre, string post);
string::size_type stoim(char);
int main() {
    //cout << "Hello, World!" << endl;
//    string n = "sb";
//    string m = "bs";
//    change(n,m);
//    cout<<n<<endl;
//    string pre = "Mr.";
//    string name = "sb";
//    string post = "III";
//    cout<<makeName(name, pre, post)<<endl;
//    string a = "abc123s5wq98d2";
//    string number = "0123456789";
//    string::size_type pos = 0;
//    while ((pos = a.find_first_of(number,pos)) != string::npos) {
//        cout<<"find number at"<<pos<<" "
//            <<a[pos]<<endl;
//        pos++;
//    }
//    pos = 0;
//    while ((pos = a.find_first_not_of(number,pos)) != string::npos) {
//        cout<<"find char at"<<pos<<" "
//        <<a[pos]<<endl;
//        pos++;
//    }
//    cout<<a;
//    return 0;

    string form = "(((1+2)*3)/5)";
    string ops = "+-*/";
    stack<char> opstack;
    stack<double> num;
    auto it = form.cbegin();
    auto end = form.cend();
    double val = 0;
    while (it != end) {
        if(isdigit(*it)) {
            num.push(stoim(*it));
        }
        else if(ops.find(*it) != string::npos) {
            opstack.push(*it);
        }
        else if (*it == ')') {
            auto num1 = num.top();
            num.pop();
            auto num2 = num.top();
            num.pop();
            auto op = opstack.top();
            opstack.pop();
            switch (op) {
                case '+':
                    num.push(num1+num2);
                    break;
                case '-':
                    num.push(num2-num1);
                    break;
                case '*':
                    num.push(num1*num2);
                    break;
                case '/':
                    num.push(num2/num1);
                    break;
                default:
                    cerr<<"ilegal op"<<endl;
            }
        }
        it++;
    }
    cout<<num.top()<<endl;
}

string::size_type stoim(const char c) {
    return digts.find(c);
}
void change(string &oldVal, string &newVal) {
    oldVal.replace(0,oldVal.size(),newVal);
}
//string makeName(string name, string pre, string post) {
//    string result(name);
//    result.insert(result.begin(), pre.begin(),pre.end());
//    result.append(post);
//    return result;
//}
string makeName(string name, string pre, string post) {
    string result(name);
    result.insert(0,pre);
    result.insert(result.size(),post);
    return result;
}