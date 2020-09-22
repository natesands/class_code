#include <iostream>
using namespace std;


class Item {
public:
  Item() {};
  Item(string itemName,int itemCost, Item* theLink)
    :name(itemName),cost(itemCost), link(theLink) {}
  int getCost() {return cost;}
  string getName() {return name;}
  Item* getLink() {return link;}
private:
  string name;
  int cost;
  Item * link;
};
typedef Item* ItemPtr;

Item * returnCost(Item* list, string itemName) {
  Item* head = list;
  while ((head != nullptr) && (head->getName() != itemName)) {
    head = head->getLink();
  }
  return head;
}

int main() {

  ItemPtr myList;

  myList = new Item("milk",3,nullptr);

  cout << myList->getName() << " " << (*myList).getCost() << endl;

  myList = new Item("cheese",4,myList);

  cout << myList->getName() << " " << (*myList).getCost() << endl;

  Item* nextItem;
  nextItem = myList->getLink();
  cout << nextItem->getName() << " " << nextItem->getCost() << endl;

  if (returnCost(myList,"butter") == nullptr) cout << "item not found" << endl;
  else cout << returnCost(myList,"milk")->getCost() << " for milk." << endl;
}
   
