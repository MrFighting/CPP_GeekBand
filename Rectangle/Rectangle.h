//
// Created by abc84 on 2016/5/17.
//

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <iostream>
/*
 * 形状类（父类）
 */
class Shape {

private:
    static int count;//计数器，每当生成一个shape（包括子类），
    // 计数器加一。(该变量不属于任何一个shape实例)
public:
    Shape():no(count){count++;}//默认构造器，将计数器递增，no为生成了第几个shape的次序
    int getNo() const { return no;}//获取编号
protected://由子类才能访问的方法和变量
    int no;
    void setNo(int n) {no = n;}//设置自己的编号
};
int Shape::count = 0;//初始化count
/*
 * 坐标类
 */
class Point {
    friend std::ostream& operator<<(std::ostream&, const Point&);//输出点
    friend Point operator-(const Point&);//坐标取反
private:
    int x;
    int y;
public:
    Point(int x = 0, int y = 0):x(x), y(y){}
    Point(const Point& p): x(p.x), y(p.y) {//拷贝构造
    }
    bool operator==(const Point& rhs){ return x == rhs.x && y == rhs.y;}//点相等
};
std::ostream& operator<<(std::ostream& os, const Point& p) {
    return os << "(" << p.x << "," << p.y << ")";
}
Point operator-(const Point& p) {
    return Point(-p.x, -p.y);
}
/*
 * 矩形类, 继承 形状类
 */
class Rectangle: public Shape {
    friend std::ostream& operator<<(std::ostream&, const Rectangle& rec);//输出
private:
    int width;
    int height;
    Point* leftUp;//左上角坐标
public:
public:
    //double Point getPosition(){ return Point(*leftUp);}
    double getArea() const { return width*height;}//面积
    Rectangle(int width, int height, int x, int y);
    Rectangle(const Rectangle& other);//拷贝构造函数
    Rectangle& operator=(const Rectangle& other);//赋值
    bool operator==(const Rectangle& rhs) const ;//矩形相等
    bool operator>(const Rectangle& rhs) const ;//比较面积大小
    bool operator<(const Rectangle& rhs) const ;
    ~Rectangle();//析构
};

/*
 * 方法实现
 */
Rectangle::Rectangle(int width, int height, int x, int y):
        width(width), height(height), leftUp(new Point(x, y)) {

}

Rectangle::Rectangle(const Rectangle &other):
        width(other.width), height(other.height), leftUp(new Point(*other.leftUp)){
}

Rectangle &Rectangle::operator=(const Rectangle &other) {
    if (this == &other) return *this;//检查自赋值
    width = other.width;
    height = other.height;
    delete leftUp;//删除自己的
    leftUp = new Point(*other.leftUp);//赋值对方的
    return *this;
}

Rectangle::~Rectangle() {
    delete leftUp;//释放资源
    //std::cout << std::endl << "no : " << no << " was deleted "<<std::endl;
}

std::ostream &operator<<(std::ostream &os, const Rectangle& rec) {
    return os << "Rec no:" << rec.no << "; width: " << rec.width
            << "; height: " << rec.height << "; position: " << *(rec.leftUp);
}

bool Rectangle::operator==(const Rectangle &rhs) const {
    if (this == &rhs) return true;//自等
    return height == rhs.height &&
           width == rhs.width &&
           *leftUp == *(rhs.leftUp);//坐标相等
}

bool Rectangle::operator>(const Rectangle &rhs) const{
    return getArea() > rhs.getArea();
}

bool Rectangle::operator<(const Rectangle &rhs) const{
    return getArea() < rhs.getArea();

}



#endif //RECTANGLE_H
