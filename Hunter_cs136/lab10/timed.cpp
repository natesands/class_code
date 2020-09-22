/*

Author: Nathaniel Sands
Course: CSCI-136
Instructor: Gwenael Gatto
Assignment: Lab10D

implements struct data type to work with
time variables

program assigns movies to timeslots
and prints out their name, genre,
duration, start and endtime

introduces scheduling function scheduleAfter
to create new timeslot
*/

#include <iostream>
using namespace std;


enum Genre {ACTION, COMEDY, DRAMA, ROMANCE, THRILLER};

struct Time {
  int h;
  int m;
};
struct Movie {
  string title;
  Genre genre;
  int duration;
};
struct TimeSlot {
  Movie movie;
  Time startTime;
};
  

void printTime(Time time) {
  cout << time.h << ":" << time.m;
}


int minutesSinceMidnight(Time time) {
  int minutes;
  minutes = time.m + time.h*60;
  return(minutes);
}
int minutesUntil(Time earlier, Time later) {
  int minutes;
  minutes = minutesSinceMidnight(later) -
    minutesSinceMidnight(earlier);  
  return(minutes);
}
Time addMinutes(Time time0, int min) {
  Time laterTime;
  int minsTotal = minutesSinceMidnight(time0) + min;
  laterTime.h = minsTotal / 60;
  laterTime.m = minsTotal % 60;
  return(laterTime); 
}  


void printMovie(Movie mv) {
  string g;
  switch (mv.genre) {
    case ACTION   : g = "ACTION"; break;
    case COMEDY   : g = "COMEDY"; break;
    case DRAMA    : g = "DRAMA"; break;
    case ROMANCE  : g = "ROMANCE"; break;
    case THRILLER : g = "THRILLER"; break;
  }
  cout << mv.title << " " << g << " (" << mv.duration << 
    " min)";
}

void printTimeSlot(TimeSlot ts) {
  printMovie(ts.movie);
  Time endtime;
  endtime = addMinutes(ts.startTime, ts.movie.duration);
  cout << " ";
  cout << "[starts at ";
  printTime(ts.startTime);
  cout << ", ends by ";
  printTime(endtime);
  cout << "]" << endl;  
}

TimeSlot scheduleAfter(TimeSlot ts,Movie nextMovie) {
  TimeSlot newSlot;
  newSlot.movie = nextMovie;
  newSlot.startTime = addMinutes(ts.startTime,ts.movie.duration);
  return (newSlot);
}
int main() {

  TimeSlot slots[5];

  //populate fields in Movie struct variables
  Movie movie1 = {"Back to the Future", COMEDY, 116};
  Movie movie2 = {"Black Panther", ACTION, 134};
  Movie movie3 = {"The Big Lebowski", COMEDY, 117};
  Movie movie4 = {"Downfall", DRAMA, 156};
  Movie movie5 = {"Wait Until Dark", THRILLER, 108};
  //populate fields in TimeSlot variables
  TimeSlot morning = {movie1, {9,15}};
  TimeSlot daytime = {movie2, {12,15}};
  TimeSlot afternoon = {movie3, {15,15}};
  TimeSlot evening = {movie4, {18,15}};
  TimeSlot midnight;
  midnight = scheduleAfter(evening, movie5);
  //populate array of slots
  slots[0] = morning;
  slots[1] = daytime;
  slots[2] = afternoon;
  slots[3] = evening;
  slots[4] = midnight;
  //print array
  for (int i = 0; i < 5; i++)  
    printTimeSlot(slots[i]);

  return 0;
} 
