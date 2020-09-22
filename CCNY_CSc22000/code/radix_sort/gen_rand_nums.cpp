#include <iostream>
#include <cstdlib> /* srand, rand */
#include <ctime> /* time */
using namespace std;

int main()
{

  srand (time(NULL));
  for (int i=0; i < 15; i++) 
    cout << rand() % 100000 + 9999 << endl;

  return 0;

}
