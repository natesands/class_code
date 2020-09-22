/*

Author: Nathaniel Sands
Course: CSCI-136
Instructor: Gwenael Gatto
Assignment: Lab13D

implements class Profile to store username and display
name
implements class Network to
store users

adds ability to store friendship relations
between users and to print dot file format

adds msg posting and timeline functions

*/
#include <iostream>
#include <string>
#include <assert.h>
using namespace std;

struct Post {
  string username;
  string message;
};

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
  static const int MAX_POSTS = 100; 
  static const int MAX_USERS = 20;
  int numPosts;
  int numUsers; 
  Post posts[MAX_POSTS];
  Profile profiles[MAX_USERS];
  bool following[MAX_USERS][MAX_USERS];
  int findID(string usrn);
public:
  Network();
  bool addUser(string usrn, string dspn);
  bool follow(string usrn1, string usrn2);
  void printDot();
  bool writePost(string usrn, string msg);
  bool printTimeline(string usrn);
};
//prints posts of users and
//ppl they follow
bool Network::printTimeline(string usrn) {
  bool msgFound = false;
 
  for (int post = numPosts-1; post >=0; post--) {
    if (posts[post].username == usrn || 
        following[findID(usrn)][findID(posts[post].username)]) {
    msgFound = true;
    cout << profiles[findID(posts[post].username)].getFullName()    
         << ": " << posts[post].message << endl;
    }
  }
  return msgFound;
} 

//adds new post to posts array if usrn is
//found and posts is not full, returns true;
//else return return false
bool Network::writePost(string usrn, string msg) {
  if (numPosts == MAX_POSTS) return false; 
  bool userFound = false;
  int id = 0;
  while (!userFound && id < numUsers) {
    if (profiles[id].getUsername() == usrn) {
      userFound = true;
    }
    id++;
  }
  if (!userFound) return false;
  posts[numPosts].username = usrn;
  posts[numPosts].message = msg;
  numPosts++; 
  return true;
} 


//Network constructor
//sets numusers = 0,numPosts = 0 and initizalizes
//friendship matrix (all false)
Network::Network() {
  numUsers = 0;
  numPosts = 0;
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
   
  nw.follow("mario", "luigi");
  nw.follow("luigi", "mario");
  nw.follow("luigi", "yoshi");
  nw.follow("yoshi", "mario");

  // write some posts
  nw.writePost("mario", "It's a-me, Mario!");
  nw.writePost("luigi", "Hey hey!");
  nw.writePost("mario", "Hi Luigi!");
  nw.writePost("yoshi", "Test 1");
  nw.writePost("yoshi", "Test 2");
  nw.writePost("luigi", "I just hope this crazy plan of yours works!");
  nw.writePost("mario", "My crazy plans always work!");
  nw.writePost("yoshi", "Test 3");
  nw.writePost("yoshi", "Test 4");
  nw.writePost("yoshi", "Test 5");

  cout << endl;
  cout << "======= Mario's timeline =======" << endl;
  nw.printTimeline("mario");
  cout << endl;

  cout << "======= Yoshi's timeline =======" << endl;
  nw.printTimeline("yoshi");
  cout << endl;
}

