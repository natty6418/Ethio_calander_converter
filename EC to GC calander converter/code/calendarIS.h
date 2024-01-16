#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
using namespace std;

class calendarIS: public Calendar {
private:
    const int IslamicEpoch = 227014; // Absolute date of start of Islamic calendar
public:
    calendarIS() {
      days = new string[7]{"ٱلْأَحَد(S)", "الاِثْنَيْن (M)","ٱلثُّلَاثَاء (T)", "ٱلْأَرْبِعَاء (W)", "ٱلْخَمِيس (Th)","ٱلْجُمْعَة (F)","ٱلسَّبْت (Sa)"};
      months = new string[12]{"ٱلْمُحَرَّم","صَفَر","رَبِيع ٱلْأَوَّل","رَبِيع ٱلْآخِر","جُمَادَىٰ ٱلْأُولَىٰ","جُمَادَىٰ ٱلْآخِرَة","رَجَب","شَعْبَان","رَمَضَان","شَوَّال","ذُو ٱلْقَعْدَة","ذُو ٱلْحِجَّة"};
      Date *GC = new Date;
      GC->CurrentDate();
      Date *IC = Greg_to_Hijri(GC);
    }


    Date *Greg_to_Hijri(Date *d) {
      int absDay = calcAbsGregorianDays(d->getDay(), d->getMonth(), d->getYear());
      int month, day, year;
      year = (absDay - IslamicEpoch) / 365;
    
    while (absDay >= islamicDate(1, 1, year))
        year++;
    year--;
     month = 1;
    while (absDay > islamicDate(month, lastDayOfIslamicMonth(month, year), year))
        month++;
    day = absDay - islamicDate(month, 1, year) + 2;
    Date *d_new = new Date(day, month, year, "Hijri");
    d_new-> setWeekDay(days[d->getWeekDay()]);
    d_new -> setMonthName(months[month-1]);
    return d_new;
    }

    int lastDayOfGregorianMonth(int month, int year) {
        // Compute the last date of the month for the Gregorian calendar.
        switch (month) {
        case 2:
            if ((((year % 4) == 0) && ((year % 100) != 0))
                || ((year % 400) == 0))
                return 29;
            else
                return 28;
        case 4:
        case 6:
        case 9:
        case 11: return 30;
        default: return 31;
        }
    }

    int calcAbsGregorianDays(int d, int m, int y) {
        int N = d;
        for (int i = m - 1; i > 0; i--)
            N += lastDayOfGregorianMonth(i, y);
        N+= ((y - 1) * 365
            + (y - 1) / 4
            - (y - 1) / 100
            + (y - 1) / 400);
        
        return N;
    }

    bool isIslamicLeapYear(int year) {
        // True if year is an Islamic leap year

        if ((((11 * year) + 14) % 30) < 11)
            return true;
        else
            return false;
    }

    int lastDayOfIslamicMonth(int month, int year) {
        // Last day in month during year on the Islamic calendar.

        if (((month % 2) == 1) || ((month == 12) && isIslamicLeapYear(year)))
            return 30;
        else
            return 29;
    }
    int islamicDate(int month, int day, int year) {
        return (day                      // days so far this month
            + 29 * (month - 1)       // days so far...
            + month / 2                //            ...this year
            + 354 * (year - 1)       // non-leap days in prior years
            + (3 + (11 * year)) / 30 // leap days in prior years
            + IslamicEpoch);                // days before start of calendar
    }
    Date* Ethio_to_Hijri(Date* d){
        calendarGC c;
        Date *GC = c.Ethio_to_Greg(d);
        return Greg_to_Hijri(GC);
    }
    ~calendarIS(){
    }
};