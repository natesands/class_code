/*

Author: Nathaniel Sands
Course: CSCI-136
Instructor: Gwenael Gatto
Assignment: Lab13C

implements class Profile to store username and display
name
implements class Network to
store users

adds ability to store friendship relations
between users and to print dot file format

*/
#include <iostream>
#include <string>
using namespace std;

class Profile {
private:
  string username;
  string displayname;
public:
  Profile(string usrn, string dspn);
  Profile();
  string getUsername();
  string getFullName();
  void setDisplayName(string dspn);
  void setUserName(string usrn);
};

class Network {
private:
  static const int MAX_USERS = 20;
  int numUsers; 
  Profile profiles[MAX_USERS];
  bool following[MAX_USERS][MAX_USERS];
  int findID(string usrn);
public:
  Network();
  bool addUser(string usrn, string dspn);
  bool follow(string usrn1, string usrn2);
  void printDot();
};

//Network constructor
//sets numusers = 0 and initizalizes
//friendship matrix (all false)
Network::Network() {
  numUsers = 0;
  for (int row =0; row < MAX_USERS; row++) {
    for (int col =0; col < MAX_USERS; col++) {
      following[row][col]=false;
    }
  }
}
//makes usrn1 follow usrn2 if both in network, and return
//true; else return false
bool Network::follow(string usrn1, string usrn2) {
  bool usr1Found = false;
  bool usr2Found = false;
  for (int i=0; i < numUsers; i++) {
    if (profiles[i].getUsername() == usrn1) usr1Found =true;
    if (profiles[i].getUsername() == usrn2) usr2Found = true;
  }
  if (usr1Found && usr2Found) {
    following[findID(usrn1)][findID(usrn2)] = true;
    return true;
  }
  else return false;
}
//prints dot file of friendship relations
void Network::printDot() {
  cout << "digraph {" << endl;
  //print all user names
  for (int i=0; i < numUsers; i++) {
    cout << "\t\"@" << profiles[i].getUsername() << "\"\n";
  }
  cout << endl << endl;
  //print out friendships
  for (int usr1=0; usr1 < numUsers; usr1++) {
    for (int usr2=0; usr2 < numUsers; usr2++) {
      string usrn1 = "\"@" + profiles[usr1].getUsername()  + "\"";
      string usrn2 = "\"@" + profiles[usr2].getUsername()  + "\"";
      if (following[usr1][usr2]) {
        cout << "\t" <<  usrn1 << " -> " << usrn2 << endl;
      }
    }
  }
  cout << "}" << endl;
}

//returns user ID num by their
//username or -1 if username not found
int Network::findID (string usrn) {
  int id = 0;
  while (id < numUsers) {
    if (profiles[id].getUsername() == usrn) {
      return id;
    }
    else id++;
  }
  return -1;
}

//attempts to sign up a new user
//returns true if successful, otherwise
//returns false
bool Network::addUser(string usrn, string dspn) {
  //profiles cannot be full
  if (numUsers == MAX_USERS) return false;  
  //usrn must be non-empty alphanum string
  if (usrn.empty()) return false;
  for (int i = 0; i < usrn.length(); i++) {
    if (!isalnum(usrn[i])) return false;
  }
  //usrn must be unique
  int id = 0;
  while (id < numUsers) {
    if (profiles[id].getUsername() == usrn) 
      return false;
    else id++;
  }
  //assert id = numUsers
  //Add user
  //enter new user information 
  profiles[id].setDisplayName(dspn);
  profiles[id].setUserName(usrn);
  //updte numbers of users
  numUsers++;
  return true;
} 
    
//Constructor for Profile w/ arguments
Profile::Profile(string usrn, string dspn) {
  username = usrn;
  displayname = dspn;
}
//Default constructor
Profile::Profile() : username(""), displayname("") {}
//returns username
string Profile::getUsername() {
  return username;
}
//returns display name
string Profile::getFullName() {
  return displayname + "(@" + username + ")";
}

void Profile::setDisplayName(string dspn) {
  displayname = dspn;
}

void Profile::setUserName(string usrn) {
  username = usrn;
}

int main() {
    Network nw;
    // add three users
    nw.addUser("mario", "Mario");
    nw.addUser("luigi", "Luigi");
    nw.addUser("yoshi", "Yoshi");

    // make them follow each other
    nw.follow("mario", "luigi");
    nw.follow("mario", "yoshi");
    nw.follow("luigi", "mario");
    nw.follow("luigi", "yoshi");
    nw.follow("yoshi", "mario");
    nw.follow("yoshi", "luigi");

    // add a user who does not follow others
    nw.addUser("wario", "Wario");
    
    // add clone users who follow @mario
    for(int i = 2; i < 6; i++) {
        string usrn = "mario" + to_string(i);
        string dspn = "Mario " + to_string(i);
        nw.addUser(usrn, dspn);
        nw.follow(usrn, "mario");
    }
    // additionally, make @mario2 follow @luigi
    nw.follow("mario2", "luigi");

    nw.printDot();
}

