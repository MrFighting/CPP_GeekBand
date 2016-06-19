## 关联容器：
**set, multiset, map, multimap**  是一种非线性的树结构，具体的说采用的是一种比较高效的特殊的平衡检索二叉树—— 红黑树结构。
set  又称集合，实际上就是一组元素的集合，但其中所包含的元素的值是唯一的，且是按一定顺序排列的，集合中的每个元素被称作集合中的实例。因为其内部是通过链表的方式来组织，所以在插入的时候比vector  快，但在查找和末尾添加上比vector  慢。 
multiset  是多重集合，其实现方式和set  是相似的，只是它不要求集合中的元素是唯一的，也就是说集合中的同一个元素可以出现多次。 
map 提供一种“键- 值”关系的一对一的数据存储能力。其“键”在容器中不可重复，且按一定顺序排列（其实我们可以将set  也看成是一种键- 值关系的存储，只是它只有键没有值。它是map 的一种特殊形式）。由于其是按链表的方式存储，它也继承了链表的优缺点。   
multimap  和map 的原理基本相似，它允许“键”在容器中可以不唯一。 

基于以上特点，   
>1. 关联容器对元素的插入和删除操作比vector 要快，因为vector 是顺序存储，而关联容器是链式存储；比list  要慢，是因为即使它们同是链式结构，但list是线性的，而关联容器是二叉树结构，其改变一个元素涉及到其它元素的变动比list  要多，并且它是排序的，每次插入和删除都需要对元素重新排序；   
>2. 关联容器对元素的检索操作比vector 慢，但是比list  要快很多。vector  是顺序的连续存储，当然是比不上的，但相对链式的list  要快很多是因为list  是逐个搜索，它搜索的时间是跟容器的大小成正比，而关联容器 查找的复杂度基本是Log(N)  ，比如如果有1000 个记录，最多查找10 次，1,000,000 个记录，最多查找20  次。容器越大，关联容器相对list  的优越性就越能体现；   
>3. 使用上set  区别于vector,deque,list  的最大特点就是set  是内部排序的，这在查询上虽然逊色于vector ，但是却大大的强于list  。   
>4. 在使用上map 的功能是不可取代的，它保存了“键- 值”关系的数据，而这种键值关系采用了类数组的方式。数组是用数字类型的下标来索引元素的位置，而 ap 是用字符型关键字来索引元素的位置。在使用上map 也提供了一种类数组操作的方式，即它可以通过下标来检索数据，这是其他容器做不到的，当然也包括set  。（STL  中只有vector  和map 可以通过类数组的方式操作元素，即如同ele[1]  方式） 

### set与multiset  

```c++
//增：
set.insert() //添加

//删：
set.erase(value)
set.erase(iterator)；//删除某值
set.clear()；//删除所有

//改：查：
set.empty(); //是否为空
set.size()；//元素个数
set.count(value) 返回某个值元素的个数 

iterator find( const key_type &key ); //返回key的位置
pair equal_range(const Key& key) const: //回容器中元素值等于key的迭代指针[first, last)， *p.first,*p.second，获取迭代器值

iterator lower_bound( const key_type &key ); //返回一个指向大于或者等于key值的第一个元素的迭代器 
iterator upper_bound( const key_type &key ); //返回一个指向大于key值的第一个元素的迭代器 

//map和multimap  
map<..> lt;
lt.insert(make_pair("**", *));
map>::iterator it;  it->first;;;it->second ；获取指针的键值对
```
---

## 仿函数（functor）
functor的英文解释为something that performs a function，即其行为类似函数的东西。C++中的仿函数是通过在类中重载()运算符实现，使你可以像使用函数一样来创建类的对象。

#### 仿函数（functor）的实现及使用


```c++
// this is a functor
struct add_x {
  add_x(int x) : x(x) {}
  int operator()(int y) { return x + y; }
private:
  int x;
};
// usage:
add_x add42(42); // create an instance of the functor class
int i = add42(8); // and "call" it
assert(i == 50); // and it added 42 to its argument
std::vector<int> in; // assume this contains a bunch of values)
std::vector<int> out;
// Pass a functor to std::transform, which calls the functor on every element 
// in the input sequence, and stores the result to the output sequence
std::transform(in.begin(), in.end(), out.begin(), add_x(1)); 
assert(out[i] == in[i] + 1); // for all i
```

#### 为什么使用仿函数（functor）

**迭代和计算逻辑分离**

使用仿函数可以使迭代和计算分离开来。因而你的functor可以应用于不同场合，在STL的算法中就大量使用了functor，下面是STL中for_each中使用functor的示例：


```c++
struct sum
{
    sum(int * t):total(t){};
    int * total;
    void operator()(int element)
    {
       *total+=element;
    }
};
int main()
{
    int total = 0;
    sum s(&total);
    int arr[] = {0, 1, 2, 3, 4, 5};
    std::for_each(arr, arr+6, s);
    cout << total << endl; // prints total = 15;
}
```

**参数可设置**

可以很容易通过给仿函数（functor）设置参数，来实现原本函数指针才能实现的功能，看下面代码：


```c++
class CalculateAverageOfPowers
{
public:
    CalculateAverageOfPowers(float p) : acc(0), n(0), p(p) {}
    void operator() (float x) { acc += pow(x, p); n++; }
    float getAverage() const { return acc / n; }
private:
    float acc;
    int   n;
    float p;
};
```

这个仿函数的功能是求给定值平方或立方运算的平均值。只需要这样来声明一个对象即可：
CalculateAverageOfPowers my_cal(2);

**有状态**

与普通函数另一个区别是仿函数（functor）是有状态的，所以可以进行诸如下面这种操作：


```c++
CalculateAverage avg;
avg = std::for_each(dataA.begin(), dataA.end(), avg);
avg = std::for_each(dataB.begin(), dataB.end(), avg);
avg = std::for_each(dataC.begin(), dataC.end(), avg);
```
对多个不同的数据集进行取平均。

**性能**


```c++
std::transform(in.begin(), in.end(), out.begin(), add_x(1));
```
编译器可以准确知道std::transform需要调用哪个函数（add:: operator）。这意味着它可以内联这个函数调用。而如果使用函数指针，编译器不能直接确定指针指向的函数，而这必须在程序运行时才能得到并调用。
一个例子就是比较std:: sort 和qsort ，STL的版本一般要快5-10倍。

#### bind1st/bind2nd

**bind1st:** 绑定器binder通过把二元函数对象的第一个实参绑定到一个特殊的值上将其转换成一元函数对象

**bind2nd:** 绑定器binder通过把二元函数对象的第二个实参绑定到一个特殊的值上将其转换成一元函数对象


```c++
bool Print(int i, int j) 
{
    std::cout<< i << "---" << j << std::endl; 
    return i>j;
}

 int _tmain(int argc, char** argv)
{
    // 以下函数调用等价于调用kPrint(2,1)
     (std::bind1st(std::ptr_fun(Print), 2))(1);11     // 以下函数调用等价于调用kPrint(1,2)
    (std::bind2nd(std::ptr_fun(Print), 2))(1);
    
    return 0;
}
```

说明：std::ptr_fun是将函数指针转换为仿函数指针。



**其它应用：**

计算数组中元素小于等于10的个数


```c++
void funA()
{
    using namespace std;
    vector<int> va;
    va.push_back(5);
    va.push_back(79);
    va.push_back(23);
    va.push_back(6);
    va.push_back(1);
    va.push_back(10);       // 设c为va中的一个元素         // bind2nd(less_equal<int>(), 10) --> less_equal<int>(c, 10)
    int less10 = count_if( va.begin(), va.end(),  bind2nd(less_equal<int>(), 10));
    cout << less10 << endl;
}

 // 以下是less_equal的实现部分
 template<class _Ty>
    struct less_equal
        : public binary_function<_Ty, _Ty, bool>
    {    // functor for operator<=
     bool operator()(const _Ty& _Left, const _Ty& _Right) const
        {    // apply operator<= to operands
         return (_Left <= _Right);
        }
    };
```
