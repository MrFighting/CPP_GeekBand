## tempate method
template Method使得子类可以不改变一个算法的结构即可重定义该算法的某些特定步骤。是一种比较简单的设计模式，但却是代码复用的一项基本技术，在类库中尤其重要。使用的也比较普遍。

这里涉及到两个角色：
**抽象模版**（AbstractClass）角色：
定义了一个或多个抽象操作，以便让子类实现。这些抽象操作叫做基本操作，它们是一个顶级逻辑的组成步骤。
定义并实现了一个模版方法。这个模版方法一般是一个具体方法，它给出了一个顶级逻辑的骨架，而逻辑的组成步骤在相应的抽象操作中，推迟到子类实现。顶级逻辑也有可能调用一些具体方法。这个就是定义了我们的固定的操作顺序。
**具体模版**（ConcreteClass）角色：
实现父类所定义的一个或多个抽象方法，它们是一个顶级逻辑的组成步骤。
每一个抽象模版角色都可以有任意多个具体模版角色与之对应，而每一个具体模版角色都可以给出这些抽象方法（也就是顶级逻辑的组成步骤）的不同实现，从而使得顶级逻辑的实现各不相同。就是对我们的多个压缩文件的不同的解压缩的支持。

**实例：**


```c++
#include <iostream>  
template <typename T> class CaffeineBeverage  //咖啡因饮料  
{  
public:  
    void PrepareRecipe() //咖啡因饮料冲泡法  
    {  
        BoilWater();  //把水煮沸  
        Brew();    //冲泡  
        PourInCup();  //把咖啡因饮料倒进杯子  
        AddCondiments(); //加调料  
    }  
    void BoilWater()  
    {std::cout << "把水煮沸" << std::endl;}  
    void Brew()  
    {static_cast<T *>(this)->Brew();}  
    void PourInCup()  
    {std::cout << "把咖啡倒进杯子" << std::endl;}  
    void AddCondiments()  
    {static_cast<T *>(this)->AddCondiments();}  
};  
class Coffee : public CaffeineBeverage<Coffee>  
{  
public:  
    void Brew()  
    {std::cout << "用沸水冲泡咖啡" << std::endl;}  
    void AddCondiments()  
    {std::cout << "加糖和牛奶" << std::endl;}  
};  
class Tea : public CaffeineBeverage<Tea>  
  
{  
public:  
    void Brew()  
    {std::cout << "用沸水浸泡茶叶" << std::endl;}  
    void AddCondiments()  
    {std::cout << "加柠檬" << std::endl;}  
};  
int main(void)  
{  
    std::cout << "冲杯咖啡:" << std::endl;  
    Coffee c;  
    c.PrepareRecipe();  
    std::cout << std::endl;  
    std::cout << "冲杯茶:" << std::endl;  
    Tea t;  
    t.PrepareRecipe();  
    return 0;  
}
```

**适用性：**
>1．一次性实现一个算法的不变的部分，并将可变的行为留给子类来实现。 

>2．各子类中公共的行为应被提取出来并集中到一个公共父类中以避免代码重复。这是Opdyke和Johnson所描述过的“重分解以一般化”的一个很好的例子。首先识别现有代码中的不同之处，并且将不同之处分离为新的操作。最后，用一个调用这些新的操作的模板方法来替换这些不同的代码。 

>3．控制子类扩展。模板方法只在特定点调用“Hook”操作，这样就只允许在这些点进行扩展。
实现要点：
>1．Template Method模式是一种非常基础性的设计模式，在面向对象系统中有着大量的应用。它用最简洁的机制（虚函数的多态性）为很多应用程序框架提供了灵活的扩展点，是代码复用方面的基本实现结构。

>2．除了可以灵活应对子步骤的变化外，“不用调用我，让我来调用你”的反向控制结构是Template Method的典型应用。

>3．**在具体实现方面，被Template Method调用的虚方法可以具有实现，也可以没有任何实现（抽象方法，纯虚方法），但一般推荐将它们设置为protected方法。**

---

## 策略模式:

 策略模式（Strategy）：它定义了一系列的算法，并将每一个算法封装起来，而且使它们还可以相互替换。策略模式让算法的变化不会影响到使用算法的客户。（原文：The Strategy Pattern defines a family of algorithms,encapsulates each one,and makes them interchangeable. Strategy lets the algorithm vary independently from clients that use it.）
UML图

**优点：**
1. 简化了单元测试，因为每个算法都有自己的类，可以通过自己的接口单独测试。
2. 避免程序中使用多重条件转移语句，使系统更灵活，并易于扩展。
3. 遵守大部分GRASP原则和常用设计原则，高内聚、低偶合。
4. 
**缺点：**
1. 因为每个具体策略类都会产生一个新类，所以会增加系统需要维护的类的数量。
2. 在基本的策略模式中，选择所用具体实现的职责由客户端对象承担，并转给策略模式的Context对象

---

## 观察者模式

意图：定义对象间的一种一对多的依赖关系，当一个对象的状态发生改变时，所有依赖于它的对象都得到通知并被自动更新。

下面用一个教师-学生的例子说明观察者模式，其中学生是观察者，教师是被观察者，不过这个也适用于电器-开关的例子，可以把电器看作观察者，开关看作被观察者，当开关开始有动作的时候，观察者接收到信息：


```c++
//-------------------------------------------------------------------
//   Subject.h        被观察对象
//-------------------------------------------------------------------

#ifndef SUBJECT_H
#define SUBJECT_H

#include "Observer.h"

class Observer;
class Subject
{
public:
    virtual ~Subject(){}
    virtual void Attach(Observer *aObserver) = 0;
    virtual void Talk() = 0;
    virtual char *GetContent() const = 0;
    virtual void SetContent(char *aContent) = 0;
protected:
    Subject(){};

};

#endif

//--------------------------------------------------------------------------
//     Teacher.h
//--------------------------------------------------------------------------
#ifndef TEACHER_H
#define TEACHER_H

#include "Subject.h"
#include <list>
#include <iterator>

class Teacher : public Subject
{
public:
    Teacher();
    virtual void Attach(Observer *aObserver);
    virtual void Talk();
    virtual char *GetContent() const;
    virtual void SetContent(char *aContent);
private:
    std::list<Observer *> observerList;
    char *content;
};

#endif;

//---------------------------------------------------------------------
//     Teacher.cpp
//---------------------------------------------------------------------
#include "Teacher.h"

Teacher::Teacher()
{
    content = "现在开始上课";
}

void Teacher::Attach(Observer *aObserver)
{
    observerList.push_back(aObserver);
}

void Teacher::SetContent(char *aContent)
{
    content = aContent;
}

void Teacher::Talk()
{
    std::list<Observer *>::iterator students;
    for(students = observerList.begin() ; students != observerList.end() ; ++students)
    {
        ((Observer *)(*students))->Listen(this);
    }
}

char *Teacher::GetContent() const
{
    return content;
}

//--------------------------------------------------------------------------------
//     Observer.h             观察者
//--------------------------------------------------------------------------------
#ifndef OBSERVER_H
#define OBSERVER_H

#include "Subject.h"

class Subject;
class Observer
{
public:
    virtual void Listen(Subject *aSubject) = 0;
    virtual ~Observer(){}
protected:
    Observer(){};
};

#endif

//------------------------------------------------------------------------
//    Student.h
//------------------------------------------------------------------------
#ifndef STUDENT_H
#define STUDENT_H

#include "Observer.h"

class Student : public Observer
{
public:
    Student(char* = "学生");
    char *GetName() const;
    virtual void Listen(Subject *aSubject);
private:
    char *name;
};

#endif

//----------------------------------------------------------------
//    Student.cpp
//----------------------------------------------------------------
#include <iostream>


#include "Student.h"

Student::Student(char *aName)
{
    name = aName;
}

void Student::Listen(Subject *aSubject)
{
    std::cout << GetName() << ":老师刚才说，" << aSubject->GetContent() << std::endl;
}

char *Student::GetName() const
{
    return name;
}

//-------------------------------------------------------------
//     demo.cpp
//-------------------------------------------------------------
#include "Student.h"
#include "Teacher.h"

int main()
{
    Student *student1 = new Student("张三");
    Student *student2 = new Student("李四");
    Student *student3 = new Student("王五");
    Teacher teacher;

    teacher.Attach(student1);
    teacher.Attach(student2);
    teacher.Attach(student3);
    teacher.Talk();
    teacher.SetContent("今天我们一起来学习C++");
    teacher.Talk();

    std::system("PAUSE");
}
```
**在GOF的《设计模式》一书中对观察者模式是这样说的：定义对象间的一种一对多的依赖关系，当一个对象的状态发生改变时，所有依赖于它的对象都得到通知并被自动更新。当一个对象发生了变化，关注它的对象就会得到通知；这种交互也称为发布-订阅(publish-subscribe)。目标是通知的发布者，它发出通知时并不需要知道谁是它的观察者。**

**使用场合**:

>1. 当一个抽象模型有两个方面，其中一个方面依赖于另一方面。将这二者封装在独立的对象中以使它们可以各自独立的改变和复用；
>2. 当对一个对象的改变需要同时改变其它对象，而不知道具体有多少对象有待改变；
>3. 当一个对象必须通知其它对象，而它又不能假定其它对象是谁；也就是说，你不希望这些对象是紧密耦合的。

---

## 桥模式


**适用性**

>1）. 你不希望在抽象和他的实现部分之间有一个固定的邦定关系，如在程序的运行时刻实现部分应该可以被选择或者切换。

>2）. 类的抽象以及他的视像都可以通过生成子类的方法加以扩充。这时bridge模式使你可以对不同的抽象接口和实现部分进行组合，并对他们进行扩充。

>3）. 对一个抽象的实现部分的修改应该对客户不产生影响，即客户的代码不需要重新编译。

>4）. 你想对客户完全隐藏抽象的实现部分。

>5）. 你想在多个实现间 共享实现，但同时要求客户并不知道这一点。

**实现例子(摘自网络):**

模拟毛笔：

  现需要提供大中小3种型号的画笔，能够绘制5种不同颜色，如果使用蜡笔，我们需要准备3*5=15支蜡笔，也就是说必须准备15个具体的蜡笔类。而如果使用毛笔的话，只需要3种型号的毛笔，外加5个颜料盒，用3+5=8个类就可以实现15支蜡笔的功能。

  实际上，蜡笔和毛笔的关键一个区别就在于笔和颜色是否能够分离。即将抽象化(Abstraction)与实现化(Implementation)脱耦，使得二者可以独立地变化"。关键就在于能否脱耦。蜡笔的颜色和蜡笔本身是分不开的，所以就造成必须使用15支色彩、大小各异的蜡笔来绘制图画。而毛笔与颜料能够很好的脱耦，各自独立变化，便简化了操作。在这里，抽象层面的概念是："毛笔用颜料作画"，而在实现时，毛笔有大中小三号，颜料有红绿蓝黑白等5种，于是便可出现3×5种组合。每个参与者（毛笔与颜料）都可以在自己的自由度上随意转换。

  
  蜡笔由于无法将笔与颜色分离，造成笔与颜色两个自由度无法单独变化，使得只有创建15种对象才能完成任务。

Bridge模式将继承关系转换为组合关系，从而降低了系统间的耦合，减少了代码编写量。
