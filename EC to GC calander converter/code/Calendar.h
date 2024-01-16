#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "Date.h"


using namespace std;
class Calendar {
    protected:
      vector<Date> Dates;
      string *days;
      string *months;
    public:
      void const printCalendar() {
            Date *d = new Date;
            d->CurrentDate();
            // HANDLE  hConsole;
            // hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            // SetConsoleTextAttribute(hConsole, 3);
            // cout<<month_num<<endl;
            cout<<setw(16)<<"\033[94m"<<months[Dates[0].getMonth()]<<"\033[0m"<<endl;
            // SetConsoleTextAttribute(hConsole, 11);
            cout<<setw(5) << "\033[94mS   M   T   W   T   F   S\033[0m" << endl;
            // SetConsoleTextAttribute(hConsole, 15);
            cout<<setw(5) << "\033[94m-------------------------\033[0m" << endl;
            // cout<<firstDay<<endl;
            for (int i=0; i<Dates.size(); i++){
                if (Dates[i].getDay() != 0){
                    if(Dates[i].getDay() == d->getDay()){
                        // SetConsoleTextAttribute(hConsole, 1);
                        cout<<""<<"\b\033[91m"<<Dates[i].getDay()<<"\033[0m"<<setw(4)<<setfill(' ');
                        // SetConsoleTextAttribute(hConsole, 15);
                        continue;
                    }
                    cout<<Dates[i].getDay()<<setw(4)<<setfill(' ');
                }
                else 
                cout<<" "<<setw(4)<<setfill(' ');
                if(i!=0 && ((i+1)%7)==0){
                    cout<<setw(0)<<endl;
                }
            }
            cout<<endl;
        }
    ~Calendar() {
        Dates.clear();
        delete [] days;
        delete [] months;
    }
};