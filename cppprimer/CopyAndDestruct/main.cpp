#include <iostream>
#include <memory>
#include "HasPtr.h"

using namespace std;
struct X{
    X(const string& a){cout<<"param: "<<a<<endl;s = a;}
    string s;
    X(const X &x){cout<<"X(const X &x)"<<endl;}
    //X(){cout<<"X(""<<")"<<endl;}
    ~X(){cout<<"~X("<<s<<")"<<endl;}
    X &operator=(const X &x);
};
X &X::operator=(const X &x) {
    //s = x.s;
    cout<<"&X::operator=(const X &x)"<<endl;
}
int main(){
////    cout<<"x1: ";
////    //X x1();//不会调用默认构造函数
////    cout<<endl<<"x2: ";
//      X x2("x2");//== X x2 = X();
//      X x1("x1");
//      x2 = x1;
//    cout<<x2.s<<endl;
////    cout<<endl<<"px: ";
////    X *px = new X();
////    X x(*px);
////    delete px;
////
////    return 0;
//    shared_ptr<int> x(new int(20));
//    shared_ptr<int> y(x);
//    cout<<"before delete"<<endl;
//    cout<<"x:"<<*x<<" "<<"y:"<<*y<<endl;
//    cout<<"after delete"<<endl;
//    delete y.get();
//    cout<<"x:"<<*x<<" "<<"y:"<<*y<<endl;

    HasPtr a1;
    HasPtr a2 (a1);//a2 引用a1
    //a1 = a1;
    a1 = HasPtr();//a1 中的s,use 不能释放因为a2还在引用a1，若注释掉上面那句话，将会导致a1中s,use被释放
    cout<<"end of pro"<<endl;
}