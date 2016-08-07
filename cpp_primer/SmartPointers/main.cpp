#include <iostream>
#include <vector>
#include <memory>

using namespace std;

void set(vector<int> *);
void print(vector<int> *);
bool b();
void process(shared_ptr<int> sp);
int main() {
    //shared_ptr<int> p = make_shared<int>(40);
    //cout<<*p<<endl;
    int a = 20;
    auto at = new auto(a);
    const int *p = new(nothrow) const int(22);
    //*p = 20;
    cout<<*p<<endl;

    vector<int> *vp = new vector<int>;//normal
    shared_ptr<vector<int>> sp = make_shared<vector<int> >();
    set(vp);
    print(vp);
    delete vp;
    vp = nullptr;
    /*
     * 普通指针和智能指针最好不要混用
     */
    int *x(new int(40));
    //process(x);错误不能将int*转换为shared_ptr
    process(shared_ptr<int>(x));
    //int j = *x;//不能这样因为内存已被释放
    //int *y(new int(40));
    int *y = new int(40);
    cout<<"y addr: "<<y<<endl;
    //cout<<*shared_ptr<int>(y)<<endl;
    //cout<<"shared_ptr<int>(y).get addr: "<<shared_ptr<int>(y).get()<<endl;
    shared_ptr<int> t(y);
    cout<<"t :"<<*t<<endl;
    //shared_ptr<int > p (shared_ptr<int>(y).get());//括号里执行完后被释放，同时释放了y,接下来对其调用都是未定义
    shared_ptr<int > pc (t.get());//这样就不会被释放
    cout<<*pc<<endl;
    cout<<"end"<<endl;
    unique_ptr<int> up(new int(20));
    unique_ptr<int> up2(new int(30));
    //up = up2;
    /*
     * 动态数组
     */
    string word;
    unique_ptr<char[]> auto_array;
    cin>>word;
    auto_array = unique_ptr<char[]>(new char[word.size()]);//不用自己释放
    char *normal_array = new char[word.size()];//需要自己释放
    for(int i=0;i<word.size();i++) {
        normal_array[i] = word[i];
        auto_array[i] = word[i];
    }
    for(int i=0;i<word.size();i++) {
        cout <<auto_array[i] << " ";
    }
    cout<<endl;
    for(int i=0;i<word.size();i++) {
        cout <<normal_array[i] << " ";
    }
    delete []normal_array;

    return 0;
}
void process(shared_ptr<int> sp) {//引用计数+1

}//引用计数-1，释放内存
