//
//  main.cpp
//  deposit_project
//
//  Created by Sophia Mikhaylova on 04.08.2023.
//
 
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct date {
       int day;
       int month;
       int year;
   };

struct range {
       date from;
       date to;
   };

struct depo {
       date start;
       date end;
       double sum;
       double rate;
   };



int getYear(string date)
{
    string year;
    int last_dot = date.rfind(".");
    year.assign(date, last_dot + 1, 4);

    return stoi(year);
}

int getMonth(string date)
{
    string month;
    int first_dot = date.find(".");
    int last_dot = date.rfind(".");
    month.assign(date, first_dot + 1, last_dot - first_dot - 1);

    return stoi(month);
}

int getDay(string date)
{
    string day;
    int first_dot = date.find(".");
    day.assign(date, 0, first_dot);

    return stoi(day);
}

bool isLeapYear(int year)
{
     bool isLeap = false;
    
     if(year % 4 == 0){
         
         if(year % 100 != 0){
            return isLeap = true;
             
         }
         if(year % 100 == 0 and year % 400 == 0){
            return isLeap = true;
         }
         
     }
     return isLeap;
}

int number_of_days_in_month(int month, int year)
{
   switch(month)
   {
       case 1:
           return 31;
       case 2:
           return (isLeapYear(year)) ? 29 : 28;
       case 3:
           return 31;
       case 4:
           return 30;
       case 5:
           return 31;
       case 6:
           return 30;
       case 7:
           return 31;
       case 8:
           return 31;
       case 9:
           return 30;
       case 10:
           return 31;
       case 11:
           return 30;
       case 12:
           return 31;
       default:
           return -1;
   }
}

double calculationInMonth(int dayS, int dayE, double sum, double rate)
{
   double day_rate = rate/((isLeapYear(2023)) ? 366 : 365);
   int count_of_days = dayE - dayS;
   double result = count_of_days * ((day_rate * sum) / 100);

   return result;
}

double calculation(range r, double sum, double rate)
{
    int monthStart = r.from.month;
    int monthEnd = r.to.month;
    int dayS = r.from.day;
    int dayE = r.to.day;
    double result = 0;

    for(int m = monthStart; m <= monthEnd; m++)
    {
    if(m == monthStart and m != monthEnd)
    {
       result += calculationInMonth(dayS, number_of_days_in_month(monthStart, 2023), sum, rate);
    }
    if(m != monthStart and m == monthEnd)
    {
       result += calculationInMonth(1, dayE , sum, rate);
    }
    if(m != monthStart and m != monthEnd)
    {
       result += calculationInMonth(1, number_of_days_in_month(monthStart, 2023), sum, rate);
    }
    if(m == monthStart and m == monthEnd)
    {
       result += calculationInMonth(dayS, dayE, sum, rate);
    }
       sum += result;
    }

    return result;
}

date getDate(string date) {
   return {
       getDay(date),
       getMonth(date),
       getYear(date)
   };
}
range getRange(date start, date end, int y) {
       if(y == start.year and y == end.year) {
           return {start, end};
       }
       if(y != start.year and y != end.year) {
           return {{1, 1, y}, {31, 12, y}};
       }
       if(y != start.year and y == end.year) {
           return {{1, 1, y}, end};
       }
       if(y == start.year and y != end.year)
       {
           return {start, {31, 12, y}};
       }
       // Exception !!!! TODO
       return {{0, 0, 0}, {0, 0, 0}};
}

depo getDepo() {
   string dateStart, dateEnd;
   double sum, rate;

   cout << "Start date: ";
   cin >> dateStart;
   cout << "End date: ";
   cin >> dateEnd;
   cout << "Sum: ";

   date start = getDate(dateStart);
   date end = getDate(dateEnd);

   cin >> sum;
   cout << "Rate: ";
   cin >> rate;

   return {start, end, sum, rate};
}
depo getDepoFromFile(string file_name) {
   ifstream depo_file(file_name);
   string dateStart;
   string dateEnd;
   string sum;
   string rate;

   if (depo_file.is_open()) {
      getline(depo_file, dateStart);
      getline(depo_file, dateEnd);
      getline(depo_file, sum);
      getline(depo_file, rate);
   } else {
       cout << "Unable to open file" << endl;
   }
   depo_file.close();

   return {getDate(dateStart), getDate(dateEnd), stod(sum), stod(rate)};
}

void calculateDepo(depo newDepo) {
    
   double result = 0;
   for(int y = newDepo.start.year; y <= newDepo.end.year; y++) {
      result += calculation(
                              getRange(newDepo.start, newDepo.end, y),
                              newDepo.sum,
                              newDepo.rate
                            );
   }
    
    cout << "-------------------------" << endl;

    cout << "Amount on deposit together with interest: " << result + newDepo.sum <<endl;
    cout << "Income: " << result << endl;
    
    cout << "-------------------------" << endl;
    
}

int main()
{

    // from: 12.12.2012 to 12.12.2013 sum: 10000 rate: 10
    // 12000 + 523%% =
    char resumption = 'y';
    while(resumption == 'y')
    {
        depo newDepo = getDepo();
        //depo newDepo = getDepoFromFile("depo.txt");
        calculateDepo(newDepo);
        cout << "Would you like to continue? Enter ""y"" if yes and ""n"" if no" << endl;
        cout << "- ";
        cin >> resumption;
    }
    
      // newDepo = getDepoFromFile("depo2.txt");
      // calculateDepo(newDepo);
    
    return 0;
}

