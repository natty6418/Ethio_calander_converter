#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
using namespace std;
class calendarET;
class calendarGC:public Calendar {
  private:
    string calendarType = "Gregorian";
    friend class calendarET;
    friend class calendarIS;
    int gregorianMonths[13] = {0, 31, 28,31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
  public:
    calendarGC() {
      Date d;
      d.CurrentDate();
      checkForLeap(d.getYear());
      days = new string[7]{"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
      months = new string[12]{"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

      int firstDay = this -> day_of_week(d);
      for ( int i = 0; i< gregorianMonths[d.getMonth()+1]+firstDay; i++){
        d.setDay((i>=firstDay) ? (i-firstDay)+1 : 0);
        Dates.push_back(d);
      }
    }
    
    int getDayNumber(string day) {
            for(int i = 0; i<7; i++) {
                if(day == days[i]){
                    return i;
                }
            }
        }
    int getMonthNum(string month) {
            for(int i = 0; i<12; i++) {
                if(month == months[i]){
                    return i;
                }
            }
        }
    int GetFirstDay(int year) {
            int century = (year - 1) / 100;
            int y = (year - 1) % 100;
            int weekday = (((29 - (2 * century) + y + (y / 4) + (century / 4)) % 7) + 7) % 7;
            // 0 would be sunday and 6 would be Saturday
            return weekday;
        }
    int day_of_week(Date d) //returns first day of the month given current date
        {
            // Adjust month and year for Zeller's congruence
            int day = GetFirstDay(d.getYear());
            for (int i =0; i<d.getMonth(); i++){
                day+= gregorianMonths[i+1];
            }
            day+=1;
            return (day%7)-1;
        }
    void checkForLeap(int year){
            if (year%4==0 && year%100 != 0 || year%400 ==0){
                gregorianMonths[2] = 29;
            }
        }

    Date* Ethio_to_Greg(Date* d) {
      // calendarET c;
      int year = d->getYear();
      int month_num = d->getMonth();
      int day_num = d->getDay();
      int newYearDay = EthioFirstDay(year);
      int gregorianYear = year + 7;
      int nextYear = gregorianYear + 1;
      if ((nextYear % 4 == 0 && nextYear % 100 != 0) || nextYear % 400 == 0) {
          gregorianMonths[6] = 29;
        }
      int until = ((month_num-1)*30) +day_num;
      if (until <= 37 && year <= 1575) { 
          until += 28;
          gregorianMonths[0] = 31;
          } 
      else {
          until += newYearDay - 1;
        }
      
    if (year - 1 % 4 == 3) {
        until += 1;
    }
    int m =0;
    int gregorianDate;

    for (int i = 0; i < 13; i++) {
        if (until <= gregorianMonths[i]) {
            m = i;
            gregorianDate = until;
            break;
        }   
        else {
            m = i;
            until -= gregorianMonths[i];
        }
        }

    if (m > 4) {
      gregorianYear += 1;
    }
    int order[14] = {8, 9, 10, 11, 12, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    int gregorianMonth = order[m];
    Date *d_new = new Date(gregorianDate, gregorianMonth, gregorianYear, "Gregorian");
    d_new->setWeekDay(days[d_new->getWeekDay()]);
    d_new -> setMonthName(months[gregorianMonth-1]);
    return d_new;
    }
int EthioFirstDay(int year) {
            int newYearDay = floor(year/100) - floor(year/400) -4;
            return (year-1)%4 == 3 ? newYearDay +1 : newYearDay;
        }

  Date *Hijri_to_Greg(Date* d){
    int JulianDay = HijriToJulian(d->getYear(), d->getMonth(), d->getDay());
    int a;
    int b = 0;
    if (JulianDay > 2299160)
    {
        a = floor((JulianDay - 1867216.25) / 36524.25);
        b = 1 + a - floor(a / 4.0);
    }
    int bb = JulianDay + b + 1524;
    int cc = floor((bb - 122.1) / 365.25);
    int dd = floor(365.25 * cc);
    int ee = floor((bb - dd) / 30.6001);
    int gregorianDate = (bb - dd) - floor(30.6001 * ee);
    int gregorianMonth = ee - 1;
    if (ee > 13)
    {
        cc += 1;
        gregorianMonth = ee - 13;
    }
    int gregorianYear = cc - 4716;
    Date *d_new = new Date(gregorianDate, gregorianMonth, gregorianYear, "Gregorian");
    d_new->setWeekDay(days[d_new->getWeekDay()]);
    d_new -> setMonthName(months[gregorianMonth-1]);
    return d_new;
  }
  int HijriToJulian(int year, int month, int day){
    return floor((11 * year + 3) / 30) + floor(354 * year) + floor(30 * month)- floor((month - 1) / 2) + day + 1948440 - 386;
  }
  ~calendarGC(){
  }
};
