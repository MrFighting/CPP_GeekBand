### **一 、模板定义**

**1.定义函数模板：**

compare 的模板版本：

     
```c++
// implement strcmp-like generic compare function
     // returns 0 if the values are equal, 1 if v1 is larger, -1 if v1 is smaller
     template <typename T>
     int compare(const T &v1, const T &v2)
     {
         if (v1 < v2) return -1;
         if (v2 < v1) return 1;
         return 0;
     }
```

a. 模板定义以关键字 template 开始，后接模板形参表，模板形参表是用尖括号括住的一个或多个模板形参的列表，形参之间以逗号分隔。 模板形参表不能为空。

 b.模板形参表很像函数形参表，函数形参表定义了特定类型的局部变量但并不初始化那些变量，在运行时再提供实参来初始化形参。

c.模板形参可以是表示类型的类型形参，也可以是表示常量表达式的非类型形参。非类型形参跟在类型说明符之后声明,类型形参跟在关键字 class 或 typename 之后定义，例如，class T 是名为 T 的类型形参，在这里 class 和 typename 没有区别。

2.使用函数模板:使用函数模板时，编译器会推断哪个（或哪些）模板实参绑定到模板形参。一旦编译器确定了实际的模板实参，就称它实例化了函数模板的一个实例。实质上，编译器将确定用什么类型代替每个类型形参，以及用什么值代替每个非类型形参。推导出实际模板实参后，编译器使用实参代替相应的模板形参产生编译该版本的函数。编译器承担了为我们使用的每种类型而编写函数的单调工作。

 

**2.类模板:**
类模板也是模板，因此必须以关键字 template 开头，后接模板形参表。

 a.除了模板形参表外，类模板的定义看起来与任意其他类问相似。类模板可以定义数据成员、函数成员和类型成员，也可以使用访问标号控制对成员的访问，还可以定义构造函数和析构函数等等。在类和类成员的定义中，可以使用模板形参作为类型或值的占位符，在使用类时再提供那些类型或值。

b.与调用函数模板形成对比，使用类模板时，必须为模板形参显式指定实参.编译器使用实参来实例化这个类的特定类型版本。

 

**3.模板形参:**

a.像函数形参一样，程序员为模板形参选择的名字没有本质含义。

b.可以给模板形参赋予的唯一含义是区别形参是类型形参还是非类型形参。如果是类型形参，我们就知道该形参表示未知类型，如果是非类型形参，我们就知道它是一个未知值。

 

**4.模板形参作用域:**

a.模板形参的名字可以在声明为模板形参之后直到模板声明或定义的末尾处使用。

b.模板形参遵循常规名字屏蔽规则。与全局作用域中声明的对象、函数或类型同名的模板形参会屏蔽全局名字.

c.使用模板形参名字的限制: 用作模板形参的名字不能在模板内部重用(不能再次作为类型来使用)。

     
```c++
template <class T> T calc(const T &a, const T &b)
     {
         typedef double T; // error: redeclares template parameter T
         T tmp = a;
         // ...
         return tmp;
     }
```

d.这一限制还意味着模板形参的名字只能在同一模板形参表中使用一次：

     
```c++
// error: illegal reuse of template parameter name V
     template <class V, class V> V calc(const V&, const V&) ;
```

e.当然，正如可以重用函数形参名字一样，模板形参的名字也能在不同模板中重用. 

f.同一模板的声明和定义中，模板形参的名字不必相同。

     
```c++
// all three uses of calc refer to the same function template
     // forward declarations of the template
     template <class T> T calc(const T&, const T&) ;
     template <class U> U calc(const U&, const U&) ;
     // actual definition of the template
     template <class Type>
     Type calc(const Type& a, const Type& b) { /* ... */ }
```

g.每个模板类型形参前面必须带上关键字 class 或 typename，每个非类型形参前面必须带上类型名字，省略关键字或类型说明符是错误的
 
**5.typename 与 class 的区别:**
在函数模板形参表中，关键字 typename 和 class 具有相同含义，可以互换使用，两个关键字都可以在同一模板形参表中使用
 
**6.在模板定义内部指定类型:**
在类型之前指定 typename 没有害处，因此，即使 typename 是不必要的，也没有关系。
如果希望编译器将 size_type 当作类型，则必须显式告诉编译器这样做：

   
```c++
template <class Parm, class U>
     Parm fcn(Parm* array, U value)
     {
         typename Parm::size_type * p; // ok: declares p to be a pointer
     }
```

 

**7.非类型模板形参:**

a.在调用函数时非类型形参将用值代替，值的类型在模板形参表中指定。

b.模板非类型形参是模板定义内部的常量值，在需要常量表达式的时候，可使用非类型形参（例如，像这里所做的一样）指定数组的长度.

 

**8.编写泛型程序:**

 a.在函数模板内部完成的操作限制了可用于实例化该函数的类型。程序员的责任是，保证用作函数实参的类型实际上支持所用的任意操作，以及保证在模板使用哪些操作的环境中那些操作运行正常。

b.编写模板代码时，对实参类型的要求尽可能少是很有益的。

c.编写泛型代码的两个重要原则：

模板的形参是 const 引用。
函数体中的测试只用 < 比较。

**9.警告：链接时的编译时错误:**

重要的是，要认识到编译模板定义的时候，对程序是否有效所知不多。类似地，甚至可能会在已经成功编译了使用模板的每个文件之后出现编译错误。只在实例化期间检测错误的情况很少，错误检测可能发生在链接时。

---

### 二 、实例化

**概述**: 模板是一个蓝图，它本身不是类或函数。编译器用模板产生指定的类或函数的特定类型版本。产生模板的特定类型实例的过程称为实例化，这个术语反映了创建模板类型或模板函数的新“实例”的概念。

模板在使用时将进行实例化，类模板在引用实际模板类类型时实例化，函数模板在调用它或用它对函数指针进行初始化或赋值时实例化。

**1.类的实例化:**

a.类模板的每次实例化都会产生一个独立的类类型。为 int 类型实例化的 Queue 与任意其他 Queue 类型没有关系，对其他 Queue 类型成员也没有特殊的访问权。

b.想要使用类模板，就必须显式指定模板实参。

c.类模板不定义类型，只有特定的实例才定义了类型。特定的实例化是通过提供模板实参与每个模板形参匹配而定义的。模板实参在用逗号分隔并用尖括号括住的列表中指定：

     
```c++
Queue<int> qi;         // ok: defines Queue that holds ints
```

d.用模板类定义的类型总是包含模板实参。例如，Queue 不是类型，而 Queue<int> 或 Queue<string> 是类型。
 
**2.函数模板实例化:**

A.使用函数模板时，编译器通常会为我们推断模板实参：
        
```c++
int main()
        {
           compare(1, 0);             // ok: binds template parameter to int
           compare(3.14, 2.7);        // ok: binds template parameter to double
           return 0;
         }
```

**B.模板实参推断**要确定应该实例化哪个函数，编译器会查看每个实参。如果相应形参声明为类型形参的类型，则编译器从实参的类型推断形参的类型。
 
**C.类型形参的实参的受限转换**:一般而论，不会转换实参以匹配已有的实例化，相反，会产生新的实例。除了产生新的实例化之外，编译器只会执行两种转换：
 a.const 转换：接受 const 引用或 const 指针的函数可以分别用非 const 对象的引用或指针来调用，无须产生新的实例化。如果函数接受非引用类型，形参类型实参都忽略 const，即，无论传递 const 或非 const 对象给接受非引用类型的函数，都使用相同的实例化。
 
b.数组或函数到指针的转换：如果模板形参不是引用类型，则对数组或函数类型的实参应用常规指针转换。数组实参将当作指向其第一个元素的指针，函数实参当作指向函数类型的指针。
 
**D.类型转换的限制**只适用于类型为模板形参的那些实参。
       用普通类型定义的形参可以使用常规转换,下面的函数模板 sum 有两个形参：

    
```c++
template <class Type> Type sum(const Type &op1, int op2)
     {
         return op1 + op2;
     }
```

**E.模板实参推断与函数指针:**

可以使用函数模板对函数指针进行初始化或赋值,这样做的时候，编译器使用指针的类型实例化具有适当模板实参的模板版本。获取函数模板实例化的地址的时候，上下文必须是这样的：它允许为每个模板形参确定唯一的类型或值。
   
```c++
// overloaded versions of func; each take a different function pointer type
     void func(int(*) (const string&, const string&));
     void func(int(*) (const int&, const int&));
     func(compare); // error: which instantiation of compare?
```

**F.在返回类型中使用类型形参:**

a.指定返回类型的一种方式是引入第三个模板形参，它必须由调用者显式指定,也就是说返回类型不能推断,必须显示指定：
    
```c++
// T1 cannot be deduced: it doesn't appear in the function parameter list
     template <class T1, class T2, class T3>
     T1 sum(T2, T3);
```

b.显式模板实参从左至右对应模板形参相匹配，第一个模板实参与第一个模板形参匹配，第二个实参与第二个形参匹配，以此类推。假如可以从函数形参推断，则结尾（最右边）形参的显式模板实参可以省略。
 
**G.显式实参与函数模板的指针**:通过使用显式模板实参能够消除二义性：
    
```c++
template <typename T> int compare(const T&, const T&);
     // overloaded versions of func; each take a different function pointer type
     void func(int(*) (const string&, const string&));
     void func(int(*) (const int&, const int&));
     func(compare<int>); // ok: explicitly specify which version of compare
```
