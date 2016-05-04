//
// Created by abc84 on 2016/5/4.
//

#ifndef DATE_DATE_H
#define DATE_DATE_H

#include "iostream"
#include <cstdlib>
#include <algorithm>//后面sort会用到
using namespace std;

class Date{

    friend ostream& operator << (ostream&, const Date&);//友元函数，方便调用私有成员变量

private:
    int year;
    int month;
    int day;

public:
    //验证日期的合法性
    static bool isValidDate(int year, int month, int day) {
        return year > 0 &&
               month <=12 && month >0 &&
               day <= DateNum(year, month) && day > 0;//输入天数不大于该月的天数,也不小于0
//        if(year <= 0)return false;
//        if (month > 12 || month <= 0) return false;
//        if (day > DateNum(year, month) || day <= 0) return false;
    }
    static int DateNum(int year,int month);//，每年每月天数

    Date(int y, int m, int d):year(y), month(m), day(d){
        if(!isValidDate(y, m, d))cerr << "invalid date construct" << endl;
    }
    Date():year(0), month(0), day(0){}//默认构造器
    //比较运算符
    bool operator > (const Date&) const ;
    bool operator < (const Date&) const ;
    bool operator == (const Date&) const;
};
//每年每月的天数若为闰年2月天数为29天
inline int Date::DateNum(int year, int month) {
    if(month==2)
    {
        if((year%4==0&&year%100!=0)||year%400==0)return 29;//若为闰年29天
        else return 28;
    }
    switch(month)//其他月份天数
    {
        case 1:return 31;
        case 3:return 31;
        case 4:return 30;
        case 5:return 31;
        case 6:return 30;
        case 7:return 31;
        case 8:return 31;
        case 9:return 30;
        case 10:return 31;
        case 11:return 30;
        case 12:return 31;
        default:cerr<<"invalid month"<<endl;
    }
    return 0;
}


#endif //DATE_DATE_H
