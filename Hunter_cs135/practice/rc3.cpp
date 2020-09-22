#include <iostream>
using namespace std;

void reverse(int num) {

  if (num < 10) {
    cout << num;
  }
  else {
    cout << (num % 10);
    reverse(num/10);
  }
}
void count(int num) {
  
  if (num ==1) {
    cout << 1 ;
  }
  else {
    count(num -1);
    cout << ", " << num;
  }
}
    
int power(int x, int n) {

  if (n==0) return 1;
  if (n==1) return x;

  else return x*power(x,n-1);

}
int main() {
  int num = 12345;

  reverse(num);
  cout << endl;

  count(5);
  cout << endl;

  cout << power(2,3); cout << endl;
  cout << power(6,2); cout << endl;


}

