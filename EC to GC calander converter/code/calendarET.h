#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
using namespace std;

class calendarET: public Calendar {
  private:
    friend class calendarGC;
    int ethipianMonthdays[15] = {0, 30, 30, 30, 30, 30, 30, 30, 30, 30, 5, 30, 30, 30, 30};
    string calendarType = "Ethiopian";
  public:
    calendarET(){
      days = new string[7]{"እሁድ (S)","ሰኞ (M)","ማክሰኞ (T)", "ረቡዕ (W)", "ሀሙስ (Th)","አርብ (F)","ቅዳሜ (Sa)"};
      months = new string[13] {"መስከረም","ጥቅምት","ህዳር","ታህሳስ","ጥር","የካቲት","መጋቢት","ሚያዝያ","ግንቦት","ሰኔ","ሃምሌ","ነሃሴ","ፑዋግሜ"};
      Date *GC = new Date;
      GC->CurrentDate();
      Date *EC = Greg_to_Ethio(GC);
    }
    Date* Greg_to_Ethio(Date* d){
            calendarGC c;
            int year = d->getYear();
            int month_num = d->getMonth();
            int day_num = d->getDay();
            checkForLeap(year);
            int tahissas; // Variable to store first of January 
            int newYearDay = EthioFirstDay(year-8);
            int until = 0;
            for (int i = 1; i< month_num; i++){
                until+=c.gregorianMonths[i];
            }
            until+=day_num;
            tahissas = (year-8) % 4 == 0 ? 26 : 25;
            // take into account the 1582 change
            if (year < 1582) {
                ethipianMonthdays[1] = 0;
                ethipianMonthdays[2] = tahissas;
            } else if (until <= 277 && year == 1582) {
                ethipianMonthdays[1] = 0;
                ethipianMonthdays[2] = tahissas;
            } else {
                tahissas = newYearDay - 3;
                ethipianMonthdays[1] = tahissas;
            }
            
            year -= 8;
            int m =0;
            for (m=1; m<15; m++) {
                if (until <= ethipianMonthdays[m]) {
                    day_num = m == 1 || ethipianMonthdays[m] == 0 ? (until + (30 - tahissas)) : (until);
                    break;
                    } else {
                    until -= ethipianMonthdays[m];
                    }
            }
            if (m > 10) {
                year += 1;
            }
            // int day = days[(c.day_of_week(*d) + d->getDay())%7;
            // Ethiopian months ordered according to Gregorian
            int order[15] = {0, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 1, 2, 3, 4};
            month_num = (order[m]);
            Date *d_new = new Date(day_num, month_num, year, "Ethiopian");
            d_new->setWeekDay(days[d->getWeekDay()]);
            d_new -> setMonthName(months[month_num-1]);
            return d_new;
        }
        int EthioFirstDay(int year) {
            int newYearDay = floor(year/100) - floor(year/400) -4;
            return (year-1)%4 == 3 ? newYearDay +1 : newYearDay;
        }
        
        void checkForLeap(int year){
            if (year % 4 == 3){
                ethipianMonthdays[10] = 6;
            }
        }
        Date* Hijri_to_Ethio(Date* d){
            calendarGC c;
            Date *GC = c.Hijri_to_Greg(d);
            return Greg_to_Ethio(GC);
          }
  ~calendarET(){
  }
};