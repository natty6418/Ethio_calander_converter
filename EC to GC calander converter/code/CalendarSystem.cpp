#include <iostream>
#include <iomanip>
#include "Calendar.h"
#include "calendarGC.h"
#include "calendarET.h"
#include "calendarIS.h"
#include "BookMark.h"
#include <stdlib.h>
using namespace std;

void AdderSubtractor();
void conversionPrompt();
void Greeting();
void BookmarkPrompt(BookMark& B, Date* d1, Date* d2);
void restart();
// #include "Date.h"
inline void UserInput(Date& d){
  cout<<"Please enter the date in numbers only."<<endl;
  cin>>d;
}
int main(){ 
  while (true) {
  Greeting();
  restart();
  }
  return 0;
}
void Greeting() {
  int choice;
  cout<< setw(3)<<setfill(' ')<<""<<"\U0001F4C5"<<" CALENDAR Arithmetic"<<endl;
  calendarGC GC;
  GC.printCalendar();
  // cout<<setw(5)<<setfill(' ')<<""<<setw(20)<<setfill('_')<<""<<endl;
  cout<<"This program has two functionalities:\n"
      <<"1. Add or subtract any number of days, months or years given a start date\n"
      <<"2. Convert dates between three different calendar systems.\n"<<endl;
  cout<<"What would you like to do? \n \033[92m Input 1/2 \033[0m>>";
  cin>>choice;
  while(choice!= 1 && choice!= 2){
    cout<<"\033[91m Incorrect Input\n \033[0m";
    cout<<"What do you want to do? \n \033[92m Input 1/2>> \033[0m";
    cin>>choice;
  }
  if(choice == 1){
    AdderSubtractor();
  } else if(choice ==2){
    conversionPrompt();
  }
}
void AdderSubtractor(){
    Date d;
    Date Interval;
    string choice;
    cout<<"Would you like to Add (A) or Subtract (S) dates?\n \033[92m Input A/S >> \033[0m";
    cin>>choice;
    while (choice != "A" && choice !="S")
    {
      cout<<"\033[91m Incorrect choice. Please input \"A\"or \"S\" \033[0m \n \033[92mInput A/S >> \033[0m";
      cin>>choice;
    }
    
    if (choice == "A"){
      cout<<"Enter the start date in numbers only\n";
      cin>>d;
      cout<<"Enter the days, months, years to be added in numbers. (0 if not applicable)\n";
      cin>> Interval;
      cout<<"The new date is: "<<d+Interval<<endl;
    } else if (choice == "S") {
      cout<<"Enter the start date in numbers only\n";
      cin>>d;
      cout<<"Enter the days, months, years to be subtracted in numbers. (0 if not applicable)\n";
      cout<<"\033[91m Note: This should be greater less than start date \033[0m\n";
      cin>> Interval;
      cout<<"The new new date is: "<<d-Interval<<endl;
    }
    
}
void conversionPrompt(){
  Date d;
  Date* d_conv;
  calendarGC GC;
  calendarET EC;
  calendarIS IC;
  BookMark B;
  int choice;
  cout<<"Would you like to convert: \n"
      <<"1. Form Gregorian to Ethiopian\n"
      <<"2. From Gregorian to Islamic\n"
      <<"3. From Islamic to Gregorian\n"
      <<"4. Form Ethiopian to Gregorian\n"
      <<"5. From Ethiopian to Hijri\n"
      <<"6. From Hijri to Ethiopian\n"
      <<"7. View Bookmarked Date\n\n";
  cout<<"Input 1/2/3/4/5/6 >>";
  cin>>choice;
  while (choice){
    try {
  switch (choice)
  {
  case 1:
    UserInput(d);
    d_conv=EC.Greg_to_Ethio(&d);
    cout<<"Your converted date is: "<<*d_conv;
    break;
  case 2:
    UserInput(d);
    d_conv=IC.Greg_to_Hijri(&d);
    cout<<"Your converted date is: "<<*d_conv;
    break;
  case 3:
    UserInput(d);
    d_conv=GC.Hijri_to_Greg(&d);
    cout<<"Your converted date is: "<<*d_conv;
    break;
  case 4:
    UserInput(d);
    d_conv=GC.Ethio_to_Greg(&d);
    cout<<"Your converted date is: "<<*d_conv;
    break;
  case 5:
    UserInput(d);
    d_conv=IC.Ethio_to_Hijri(&d);
    cout<<"Your converted date is: "<<*d_conv;
    break;
  case 6:
    UserInput(d);
    d_conv=EC.Hijri_to_Ethio(&d);
    cout<<"Your converted date is: "<<*d_conv;
    break;
  case 7:
    B.viewBookmarkedDates();
    break;
  default:
    throw("");
    break;
  }
  break;
  }
  catch(...) {
    cout<<"\033[91mIncorrect input.\033[0m\n";
    cout<<"\033[92m Input 1/2/3/4/5/6 >> \033[0m";
    cin>> choice;
  } 
  }
  if(choice != 7) BookmarkPrompt(B, &d, d_conv);
}
void BookmarkPrompt(BookMark& B, Date* d1, Date* d2){
  char response;
  cout<<"Would You like to bookmark this date? (Y/N)"<<endl;
  cin>>response;
    while (response != 'N' && response !='Y')
    {
      cout<<"\033[91m Incorrect Response \033[0m"<<endl;
      cout<<"Would You like to bookmark this date? (Y/N) \n \033[92m>>\033[0m"<<endl;
      cin>>response;
    }
    if (response == 'Y'){
    B.addBookMark(*d1, *d2);
    cout<<"Bookmarked\n";
  } else if(response == 'N'){
  }
}
void restart() {
  string input;
  cout<<"Would you like to restart (R) or exit (E)? (R/E)\n";
  cin>>input;
  while(input!="R" && input!="E"){
    cout<<"\033[91m Please enter a valid input.\033[0m \n \"R\"- Restart. \n \"E\"- Exit.\n\033[92m>> \033[0m";
    cin>>input;
  }
  if(input == "R"){
    system("clear");
  }else if (input =="E"){
    exit(-1);
  }
}