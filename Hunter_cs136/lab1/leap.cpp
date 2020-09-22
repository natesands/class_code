/*
Author: Nathaniel Sands
Course: CSCI-136
Instructor: Amina Bashir
Assignment: Lab1C

Asks the user to input an integer representing a year number.
If the year is a leap year it will print 'Leap year', otherwise 'Common year'
*/

#include <iostream>
using namespace std;

int main(){

	int year;
	int flag; /* 0 for common year, 1 for leap year */
	
	cout << "Enter year: ";
	cin >> year;

	if ((year % 4) != 0)
		flag = 0;
	else if ((year % 100) != 0)
		flag =1;
	else if ((year % 400) != 0)
		flag = 0;
	else 
		flag = 1;

	if (flag == 0)
		cout << "Common year" << endl;
	else
		cout << "Leap year" << endl;

return 0;
}
		

	
