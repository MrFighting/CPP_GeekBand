#### 享元模式

**作用:** 享元式是为了应对大量细粒度对象重复的问题。程序中存在大量细粒度的对象，每次要使用时都必须创建一个新的对象，既影响了运行效率又增加了内存消耗。于是有了享元模式，享元模式提取出这些细粒度对象中间公共的状态（属性，我的理解），只生成一个实例对象，所有用到这些公共属性对象的地方，都指向这一个实例。

**常用场景:**:
当系统中有大量的细粒度对象实例，而且这些对象实例中有一些属性是重复的情况下，考虑使用。

文本编辑器，输入法之类的常用应用。

**例子:**

```c++
#ifndef _FLYWEIGHT_H_
#define _FLYWEIGHT_H_


class FlyWeight
{
public:
    FlyWeight(){};
    virtual ~FlyWeight(){};

    virtual void operation() = 0;

};


class ConcreteFlyWeight: public FlyWeight
{
public:
    ConcreteFlyWeight(){};
    ~ConcreteFlyWeight(){};
    
    void operation();
    
};



#endif

FlyWeight.h


#include "FlyWeight.h"
#include <stdio.h>


void ConcreteFlyWeight::operation()
{
    printf("I'm ConcreteFlyWeight!\n");
}

FlyWeight.cpp

#include "FlyWeight.h"
#include <stdio.h>


void ConcreteFlyWeight::operation()
{
    printf("I'm ConcreteFlyWeight!\n");
}

FlyWeight.cpp


#include "FlyWeightFactory.h"

FlyWeightFactory::FlyWeightFactory()
{
    FlyWeight* tmp = new ConcreteFlyWeight();
    m_flyWeights.push_back(tmp);
}




FlyWeightFactory::~FlyWeightFactory()
{
    FlyWeight* tmp = m_flyWeights.at(0);
    delete tmp;
    tmp = NULL;
}




FlyWeight* FlyWeightFactory::GetFlyWeight(int key)
{
    //简单点表示
    return m_flyWeights.at(key);
}

FlyWeightFactory.cpp

#include "FlyWeightFactory.h"

FlyWeightFactory::FlyWeightFactory()
{
    FlyWeight* tmp = new ConcreteFlyWeight();
    m_flyWeights.push_back(tmp);
}




FlyWeightFactory::~FlyWeightFactory()
{
    FlyWeight* tmp = m_flyWeights.at(0);
    delete tmp;
    tmp = NULL;
}




FlyWeight* FlyWeightFactory::GetFlyWeight(int key)
{
    //简单点表示
    return m_flyWeights.at(key);
}

```

---

#### 组合模式

**何时使用组合模式：**
当你发现需求中是体现部分与整体层次的结构时，以及你希望用户可以忽略组合对象与单个对象的不同，统一地使用组合结构中的所有对象时，就应该考虑用组合模式了。

基本对象可以被组合成更复杂的组合对象，而这个组合对象又可以被组合，这样不断地递归下去，客户代码中，任何用到基本对象的地方都可以使用组合对象了。

用户不用关心到底是处理一个叶节点还是处理一个组合组件，也就用不着为定义组合二写一些选择判断语句了。

组合模式让客户可以一致地使用组合结构和单个对象。

**抽象基类:**
1. Component:为组合中的对象声明接口，声明了类共有接口的缺省行为(如这里的Add,Remove,GetChild函数)，声明一个接口函数可以访问Component的子组件.

接口函数:
1. Component:: Operatation:定义了各个组件共有的行为接口，由各个组件的具体实现.
2. Component::Add添加一个子组件
3. Component::Remove::删除一个子组件.
4. Component::GetChild:获得子组件的指针.

**说明:**
Component模式是为解决组件之间的递归组合提供了解决的办法，它主要分为两个派生类：

1)、Leaf是叶子结点,也就是不含有子组件的结点

2)、Composite是含有子组件的类.

举一个例子来说明这个模式，在UI的设计中,最基本的控件是诸如Button、Edit这样的控件，相当于是这里的Leaf组件，而比较复杂的控件比如Panel则可也看做是由这些基本的组件组合起来的控件，相当于这里的Composite，它们之间有一些行为含义是相同的，比如在控件上作一个点击,移动操作等等的，这些都可以定义为抽象基类中的接口虚函数，由各个派生类去实现之，这些都会有的行为就是这里的Operation函数，而添加、删除等进行组件组合的操作只有非叶子结点才可能有，所以虚拟基类中只是提供接口而且默认的实现是什么都不做。

```c++
#include <iostream>
#include <vector>

using namespace std;

/*
 * 针对DrawingSystem中的基类Shape和各个子类Line、Rec、Circle，
 * 请使用某种模式来支持更复杂的形状，该复杂形状是各个形状的自由组合。
 * 使用松耦合面向对象设计方法和思想,可使用伪码表示设计。
 */
class Shape {//形状基类
public:
    virtual void draw() = 0;

    virtual ~Shape() { }
};

/*
 * 几个基本形状
 */
class Line : public Shape {
public:
    virtual void draw() {
        cout << "draw line" << endl;
    }

};

class Rec : public Shape {
public:
    virtual void draw() {
        cout << "draw Rec" << endl;
    }
};

class Circle : public Shape {
public:
    virtual void draw() {
        cout << "draw Circle" << endl;
    }
};

/*
 * 复杂形状(组合形状),组合模式实现
 */

class MixedShape : public Shape {
private:
    vector<Shape *> components;//组合部件
public:
    void addShape(Shape *shape) {
        components.push_back(shape);
    }

    virtual void draw() {
        cout << "drawing MixedShape" << endl;
        for (auto &shape : components) {
            shape->draw();
        }
    }

    virtual ~MixedShape() {//析构
        for (Shape* &shape : components) {//逐一的析构各个部件
            delete shape;
            shape = nullptr;
        }
    }
};

int main() {

    MixedShape mixedShape1;
    mixedShape1.addShape(new Rec);
    mixedShape1.addShape(new Circle);
    cout << "mixedShape1:" <<endl;
    mixedShape1.draw();
    cout << "-------------------------" << endl;
    MixedShape mixedShape2;
    mixedShape2.addShape(new Line);
    mixedShape2.addShape(&mixedShape1);//将mixedShape1作为mixedShape2的部件
    cout << "mixedShape2:" <<endl;
    mixedShape2.draw();
}

输出:

mixedShape1:
drawing MixedShape
draw Rec
draw Circle
-------------------------
mixedShape2:
drawing MixedShape
draw line
drawing MixedShape
draw Rec
draw Circle




```


---

#### 责任链模式

责任链模式是一种设计模式。在责任链模式里，很多对象由每一个对象对其下家的引用而连接起来形成一条链。请求在这个链上传递，直到链上的某一个对象决定处理此请求。发出这个请求的客户端并不知道链上的哪一个对象最终处理这个请求，这使得系统可以在不影响客户端的情况下动态地重新组织和分配责任。

**责任链模式涉及到的角色如下所示：**

●　抽象处理者(Handler)角色：定义出一个处理请求的接口。如果需要，接口可以定义 出一个方法以设定和返回对下家的引用。这个角色通常由一个抽象类或者接口实现，抽象方法handleRequest()规范了子类处理请求的操作。

●　具体处理者(ConcreteHandler)角色：具体处理者接到请求后，可以选择将请求处理掉，或者将请求传给下家。由于具体处理者持有对下家的引用，因此，如果需要，具体处理者可以访问下家。
如何使用

**实现**
我们先来看不纯的职责模式：

假如在公司里，

如果你的请假时间小于0.5天，那么只需要向leader打声招呼就OK了。
如果0.5<请假天数<=3天，需要先leader打声招呼，要不然leader不知你跑哪里，然后部门经理直接签字。
如果3<请假天数 天，需要先leader打声招呼，然后到部门经理签字，最好总经经理确认签字，

当你看到这情况后你心里是不是已经有了自己的想法了?写一系列的if语句来一条条的判断.但这样的写法虽然可以实现目前的需求,可如果当流程改了呢？我请假超过3天，告诉leader和总经理签字就可以，那你又得一步一步修改程序。如果if语句的条数发生变化的话我们还必须在代码中添加必要的if判断，这对于程序的维护来说是相当麻烦的.如果我们使用职责链模式的话就可以相当简单了.

这个例子就是个list。也是个不纯的职责链，因为每个对象可能处理一部分后，就需要传给下个对象来处理。

---

#### 访问器模式

**抽象访问者（Visitor）角色**：声明了一个或者多个访问操作，形成所有的具体元素角色必须实现的接口。

**具体访问者（ConcreteVisitor）角色**：实现抽象访问者角色所声明的接口，也就是抽象访问者所声明的各个访问操作。

**抽象节点（Element）角色**：声明一个接受操作，接受一个访问者对象作为一个参量。

**具体节点（ConcreteElement）角色**：实现了抽象元素所规定的接受操作。

**结构对象（ObiectStructure）角色**：有如下的一些责任，可以遍历结构中的所有元素；如果需要，提供一个高层次的接口让访问者对象可以访问每一个元素；如果需要，可以设计成一个复合对象或者一个聚集，如列（List）或集合（Set）。 

**访问者模式有如下的优点：**
1. 访问者模式使得增加新的操作变得很容易。如果一些操作依赖于一个复杂的结构对象的话，那么一般而言，增加新的操作会很复杂。而使用访问者模式，增加新的操作就意味着增加一个新的访问者类，因此，变得很容易。

2. 访问者模式将有关的行为集中到一个访问者对象中，而不是分散到一个个的节点类中。

3. 访问者模式可以跨过几个类的等级结构访问属于不同的等级结构的成员类。迭代子只能访问属于同一个类型等级结构的成员对象，而不能访问属于不同等级结构的对象。访问者模式可以做到这一点。

4. 积累状态。每一个单独的访问者对象都集中了相关的行为，从而也就可以在访问的过程中将执行操作的状态积累在自己内部，而不是分散到很多的节点对象中。这是有益于系统维护的优点。

**访问者模式有如下的缺点：**
1. 增加新的节点类变得很困难。每增加一个新的节点都意味着要在抽象访问者角色中增加一个新的抽象操作，并在每一个具体访问者类中增加相应的具体操作。

2. 破坏封装。访问者模式要求访问者对象访问并调用每一个节点对象的操作，这隐含了一个对所有节点对象的要求：它们必须暴露一些自己的操作和内部状态。不然，访问者的访问就变得没有意义。由于访问者对象自己会积累访问操作所需的状态，从而使这些状态不再存储在节点对象中，这也是破坏封装的。


例子:

```c++
#include <iostream>  
#include <string>  
#include <list>  
using namespace std;  
  
class Element;  
  
class Visitor  
{  
public:  
    virtual void Visit( Element *element ){};  
};  
  
// "Element"  
class Element  
{  
public:  
    // Methods  
    virtual void Accept( Visitor *visitor ){};  
};  
  
  
// "ConcreteElement"  
class Employee : public Element  
{  
public:  
    string name;  
    double income;  
    int vacationDays;  
  
public :  
    Employee( string name, double income,  
        int vacationDays )  
    {  
        this->name = name;  
        this->income = income;  
        this->vacationDays = vacationDays;  
    }  
  
    void Accept( Visitor *visitor )  
    {  
        visitor->Visit( this );  
    }  
};  
  
class IncomeVisitor : public Visitor  
{  
public:   
    void Visit( Element *element )  
    {  
        Employee *employee = ((Employee*)element);  
        employee->income *= 1.10;  
        cout<<employee->name<<" 's new income: " <<employee->income<<endl;  
  
    }  
};  
  
class VacationVisitor : public Visitor  
{  
public :  
    void Visit( Element *element )  
    {  
        Employee *employee = ((Employee*)element);  
        // Provide 3 extra vacation days  
        employee->vacationDays += 3;       
        cout<<employee->name<<" 's new vacation days: " <<employee->income<<endl;  
    }  
};  
  
// "ObjectStructure"  
class Employees  
{     
private :  
    list< Employee*> employees;  
  
public :  
  
    void Attach( Employee *employee )  
    {         
        employees.push_back(employee);        
    }  
  
    void Detach( Employee *employee )  
    {  
        employees.remove(employee);       
    }  
  
    void Accept( Visitor *visitor )  
    {         
        for (std::list<Employee*>::iterator it=employees.begin(); it != employees.end(); ++it)  
            (*it)->Accept(visitor);  
    }  
};  
  
void main( )  
{  
    Employees *e = new Employees();  
    e->Attach( new Employee( "Tom", 25000.0, 14 ) );  
    e->Attach( new Employee( "Thomas", 35000.0, 16 ) );  
    e->Attach( new Employee( "Roy", 45000.0, 21 ) );  
  
    // Create two visitors  
    IncomeVisitor *v1 = new IncomeVisitor();  
    VacationVisitor *v2 = new VacationVisitor();  
  
    // Employees are visited  
    e->Accept( v1 );  
    e->Accept( v2 );  
}  
```
