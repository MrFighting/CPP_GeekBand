/*
 * @author:Ruston
 * @date:2016-5-4
 *
 * 功能:日期类，生成随机十个日期，并对它们进行排序
 *
 * 要点：1.日期不是所有数都合法，要验证日期合法性（闰年要注意）
 *      2.生成的随机日期也要进行验证，否则产生的日期非法，对其进行排序无意义
 *      3.排序调用algorithm库中的sort方法，该方法原理是快速排序，根据类定义的<符号进行排序
 */

#include <iostream>
#include "Date.h"

//产生十个随机的Date对象,并返回该数组
Date* CreatePoints() {
    Date *date = new Date[10];//动态分配十个Date空间
    for (int i = 0; i < 10; ++i) {
        int Ryear = 0,Rmonth = 0,Rday = 0;//随机年月日
        while (!Date::isValidDate(Ryear, Rmonth, Rday)) {//直到产生合法的日期
            Ryear = rand() % 3000;//0~2999随机数
            Rmonth = 1 + rand() % 12;//1~12随机数
            Rday = 1 + rand() % Date::DateNum(Ryear, Rmonth);//1~(该月天数-1)随机数
        }
        date[i] = Date(Ryear, Rmonth, Rday);
    }
    return date;
}
//对随机产生的日期排序
void Sort(Date *dates,int length) {
    sort(dates, dates + length);//调用algorithm库中的sort（快速排序根据<符号进行比较）
}
//输出
void print(Date *dates, int length) {
    for (int i = 0; i < length; ++i) {
        cout<<dates[i]<<" ";
    }
    cout<<endl;
}
int main() {
    //Date d(-1,-2,-3);
    //cout<< d <<endl;
    Date * Rdates = CreatePoints();
    cout<<"unsorted : "<<endl;
    print(Rdates, 10);//打印那十个随机Date
    Sort(Rdates, 10);//对其排序
    cout<<"sorted : "<<endl;
    print(Rdates, 10);
}