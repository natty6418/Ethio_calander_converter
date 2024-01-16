#include <iostream>
// #include <windows.h> 
#include <string>
#include <sstream>
using namespace std;

class BookMark {
    private:
        ofstream of;
        ifstream f;
        string identifier = "BookMarks.txt";
        static int ID;
        bool is_empty(std::ifstream& pFile)
        {
            return pFile.peek() == std::ifstream::traits_type::eof();
        }
    public:
        BookMark(){
            of.open(this->identifier, ios::app);
            f.open(this->identifier, ios::in);
            if (is_empty(f))
                {
                    of<<"ID     Date      ConvertedDate       ConvertedFrom       ConvertedTo"<<endl;
                }            
        }
        void addBookMark(Date d1, Date d2){
            string line;
            while (getline(f, line)){
                ID = line[0];
            }
            f.clear();
            f.seekg(0);
            ID++;
            string from;
            cout<<"Date is converted from: "<<endl;
            cin>>from;
            of<<ID<<"       "<<d1.getDate()<<"      "<<d2.getDate()<<"     "<<from<<"      "<<d2.getType()<<endl; 
        }
        void viewBookmarkedDates() {
            string line;
            while(getline(f, line)){
                cout<<line<<endl;
            }
        }
        ~BookMark(){
            f.close();
        }
};
int BookMark::ID = 0;