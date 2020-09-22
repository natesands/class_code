/*
Author: Nathaniel Sands
Course: CSCI-136
Instructor: Amina Bashir
Assignment: Lab1D

Asks the user to input the year and the month (1-12).
Prints the number of days in the month, taking into account leap
years.
*/

#include <iostream>
using namespace std;

int main(){

  int year, month, days;
  int flag; /* 0 for common year, 1 for leap year */

  cout << "Enter year: ";
  cin >> year;
  cout << "Enter month: ";
  cin >> month;


  if ((year % 4) != 0)
  	flag = 0;
  else if ((year % 100) != 0)
  	flag =1;
  else if ((year % 400) != 0)
		flag = 0;
	else
		flag = 1;

  if (month == 2 && flag == 1)
    days = 29;
  else if (month == 2 && flag ==0)
    days = 28;
  else if ( month == 1 || month == 3 || month == 5 || month == 7
              || month == 8 || month == 10 || month == 12)
    days = 31;
  else
    days = 30;

  cout << days << " days" << endl;

  return 0;
}
