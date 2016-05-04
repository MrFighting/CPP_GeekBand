//
// Created by abc84 on 2016/5/4.
//

#include "Date.h"
bool Date::operator>(const Date &r) const {
    if (year > r.year) return true;
    if (year == r.year && month > r.month)return true;//年相等比较月
    return year == r.year && month == r.month && day > r.day;//年月相等比较天，否则就是不大于
}
//小于判断
bool Date::operator<(const Date &r) const {
    return !operator>(r)&&!operator==(r);//既不大于r也不等于r，就是小于
}
//等值判断
bool Date::operator==(const Date &r) const {
    return year == r.year &&
           month == r.month &&
           day == r.day;
}

//如打印日期 2015-10-1
ostream& operator << (ostream& os, const Date& r) {
    return os << r.year << "-" << r.month << "-" << r.day;
}
