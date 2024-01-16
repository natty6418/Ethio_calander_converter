#include <iostream>
#include <string>
#include <ctime>
#include <sstream>

using namespace std;


class Date {
protected:
    string day;
    int day_num;
    string month;
    int month_num;
    int year;
    string calendarType;
    string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    string months[12]={"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    typedef unsigned long ul;
    typedef unsigned int ui;
    int gregorianMonths[13] = {31, 28,31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
public:
    Date(int day_num = 0, int mon = 1, int year = 0, string calendarType = "") {
        this->day_num = day_num;
        this->month_num = mon;
        this ->month = months[mon-1];
        this->year = year;
        this->calendarType = calendarType;
        this->day = CalcDayOfWeek(year, mon, day_num);
    }
    void CurrentDate(){
            string *t=new string[5];
            time_t now = time(0);
            string date_time = ctime(&now);
            stringstream date_stream(date_time);
            int ctr = 0;
            string item;
            while(getline(date_stream, item, ' ')){
                if(item!=""){
                  t[ctr] = item;
                  ctr++;
                }
            }
            this->day = t[0];
            this->day_num=stoi(t[2]);
            this->month_num = getMonthNum(t[1]);
            this -> month = months[month_num];
            this->year = stoi(t[4]);
            this->calendarType = "Gregorian";
        }
    friend ostream& operator<<(ostream& os, const Date& dt);
    friend istream& operator>>(istream& is, Date& d);
    friend Date operator+(const Date& d1, const Date& d2);
    friend Date operator-(const Date& d1, const Date& d2);
    ul CalcDayNumFromDate(ui y, ui m, ui d){
        m = (m + 9) % 12;
        y -= m / 10;
        ul dn = 365*y + y/4 - y/100 + y/400 + (m*306 + 5)/10 + (d - 1);
        return dn+3;
      }
    string CalcDayOfWeek(int y, ul m, ul d){
        ul dn = CalcDayNumFromDate(y, m, d);
        return days[(dn % 7)];
      }
    int const getDayidx(string day) {
            for(int i = 0; i<7; i++) {
                if(day == days[i]){
                    return i;
                }
            }
            return -1;
        }
    int getMonthNum(string month) {
            for(int i = 0; i<12; i++) {
                if(month == months[i]){
                    return i;
                }
            }
            return -1;
        }
    int getYear() const { return year; }
    int getMonth() const { return month_num; }
    string getMonthName() {return month; }
    int getDay() const { return day_num; }
    int const getWeekDay()  { 
      return getDayidx(day); }
    string getType() const { return calendarType; }
    void print() const {
      cout<<"Your converted date is: "<<day<<", "<<month<< " "<<day_num<<", "<<year<<" ("<<to_string(day_num)+"/"+to_string(month_num) + "/"+ to_string(year)<<")"<<endl;
    }
    
    void setYear(int year) { this->year = year; }
    void setMonth(int month) { this->month_num = month; }
    void setDay(int day) { this->day_num = day; }
    void setWeekDay(string day) { this->day = day; }
    void setType(string calendarType) { this->calendarType = calendarType; }
    void setMonthName (string mon) {
      this -> month = mon;
      }
    string getDate() {
        return (to_string(day_num)+"/"+to_string(month_num) + "/"+ to_string(year));
    }
    ~Date() {
        // destructor implementation
    }
};
ostream& operator <<(ostream& os, const Date& dt) {
        os <<dt.day<<", "<<dt.month<< " "<<dt.day_num<<", "<<dt.year
        <<" ("<<to_string(dt.day_num)+"/"+to_string(dt.month_num) + "/"+ to_string(dt.year)<<")"<<endl;
        return os;
    }
istream& operator>>(istream& is, Date& d) {
    int day, month, year;
    cout << "Enter day: ";
    is >> day;
    cout << "Enter month: ";
    is >> month;
    cout << "Enter year: ";
    is >> year;
    
    d = Date(day, month, year);
    return is;
}
Date operator+(const Date& d1, const Date& d2) {
    int day_sum = d1.getDay()+d2.getDay();
    
    int month_sum = d1.getMonth() + d2.getMonth();
    
    int year_sum = d1.getYear()+d2.getYear();
    if(day_sum > d1.gregorianMonths[d1.getMonth()+d2.getMonth()-1]){
        month_sum+=1;
        day_sum -= d1.gregorianMonths[d1.getMonth()+d2.getMonth()-1];
    }
    if(month_sum >12){
        year_sum +=1;
        month_sum = 1;
    }
    // Handle carry-over from days to months
    
    return Date(day_sum, month_sum, year_sum, "Gregorian");
}
Date operator-(const Date& d1, const Date& d2) {
    int day_diff = d1.getDay() - d2.getDay();
    int month_diff = d1.getMonth() - d2.getMonth();
    int year_diff = d1.getYear() - d2.getYear();
    if (day_diff <= 0) {
        month_diff--;
        day_diff += d1.gregorianMonths[d1.getMonth()-2];
    }
    if (month_diff <= 0) {
        year_diff--;
        month_diff += 12;
    }
    // Handle borrow from days to months
    
    return Date(day_diff, month_diff, year_diff, "Gregorian");
}