/* 
Author: Nathaniel Sands
Course: CSCI-136
Instructor: Gwenael Gatto
Assignment: Lab3D

Program asks the user to input two dates (earlier then
later date).  Reports the West basin elevation for all days 
in the interval in the reverse chronological order.

*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
using namespace std;

int main(){
  ifstream fin("Current_Reservoir_Levels.tsv");

  if (fin.fail()) {
    cerr << "File cannot be opened for reading." << endl;
    exit(1);
  }

  string junk;
  getline(fin,junk); //skips the first line in file

  string date, dateStart,dateEnd;
  string eastSt, eastEl, westSt, westEl;
  bool inRange = false;
  int i, lines;

  string data[1000][2];
  
  cout << "Enter starting date: ";  //gets start and end date
  cin >> dateStart;                 //from user
  cout << "Enter ending date: ";
  cin >> dateEnd; 

  i = 0;
  lines = 0;

  while (fin >> date >> eastSt >> eastEl >> westSt >> westEl) {
    if (date == dateStart) {
      inRange = true;
    }
    if (inRange) { //populates array with date range data
      data[i][0] = date;
      data[i][1] = westEl;
      i++;
      lines++;
    } 
    if (date == dateEnd){
      inRange = false;
    }
  }
  //print out data that was put in array
  for (i = lines-1 ; i >= 0; i--) {
    cout << data[i][0] << " " << data[i][1] << " ft" << endl;
  }

 fin.close();

return 0;
} 
