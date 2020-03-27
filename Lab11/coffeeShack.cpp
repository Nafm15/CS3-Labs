#include <queue>
#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <vector>
#include <map>
#include <algorithm>

using std::queue;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::set;
using std::map;

enum class DrinkType {small, large, medium};
class Barista;
class Customer;

class Drink{
public:
  Drink(DrinkType type=DrinkType::small):type_(type) {}

  virtual double getPrice() const
  {
    if(type_ == DrinkType::small)
      {
	return sPrice;
      }
    else if(type_ == DrinkType::medium)
      {
	return mPrice;
      }
    else
      {
	return lPrice;
      }
  }

  virtual std::string getIngredients() const {return "";}

private:
  int price_;
  DrinkType type_;
  const double sPrice=1.00;
  const double mPrice=2.00;
  const double lPrice=3.00;
};

class AddSprinkles: public Drink {
public:
  AddSprinkles(const Drink* wrapped): wrapped_(wrapped) {}
  double getPrice() const override {return 0.50 + wrapped_->getPrice();}
  string getIngredients() const override
  {
    if (wrapped_->getIngredients()=="")
      {
	return wrapped_->getIngredients() + " Sprinkles";
      }
    else
      {
	return wrapped_->getIngredients() + ", Sprinkles";
      }
  }
private:
  const Drink *wrapped_;
};


class AddCaramel: public Drink {
public:
  AddCaramel(const Drink* wrapped): wrapped_(wrapped) {}
  double getPrice() const override {return 0.20 + wrapped_->getPrice();}

  string getIngredients() const override
  {
    if (wrapped_->getIngredients()=="")
      {
	return wrapped_->getIngredients() + " Caramel" ;
      }
    else
      {
	return wrapped_->getIngredients() + ", Caramel" ;
      }
  }
private:
  const Drink *wrapped_;
};


class AddMilkFoam: public Drink {
public:
  AddMilkFoam(const Drink* wrapped): wrapped_(wrapped) {}
  double getPrice() const override {return 0.40 + wrapped_->getPrice();}
  string getIngredients() const override
  {
    if (wrapped_->getIngredients()=="")
      {
	return wrapped_->getIngredients() + " Foam";
      }
    else
      {
	return wrapped_->getIngredients() + ", Foam";
      }
  }
private:
  const Drink *wrapped_;
};


class AddIce: public Drink {
public:
  AddIce(const Drink* wrapped): wrapped_(wrapped) {}
  double getPrice() const override {return 0.10 + wrapped_->getPrice();}
  string getIngredients() const override
  {
    if (wrapped_->getIngredients()=="")
      {
	return wrapped_->getIngredients() + " Ice";
      }
    else
      {
	return wrapped_->getIngredients() + ", Ice";
      }
  }
private:
  const Drink *wrapped_;
};

//start of part 2

class Customer;
class Barista;

class EventRegistry{
public:
  static void registerCustomer(Barista*, Customer*);
  static void deregisterCustomer(Barista*, Customer*);
  static void handleMessage(Barista*);
private:
  static map<Barista*, set<Customer*>> customerMap_;
};


//initialize the static map


map<Barista*, set<Customer*>>
  EventRegistry::customerMap_;


class Customer{
public:
  Customer(const string &name): name_(name) {}
  string getName() const {return name_;}
  void subscribe(Barista *s){
    EventRegistry::registerCustomer(s, this);}
  void unsubscribe(Barista *s){
    EventRegistry::deregisterCustomer(s, this);}
  void handleMessage(Barista*);
private:
  string name_;
};


class Barista{
public:
  Barista(const string &name): name_(name) {}
  string getName() const {return name_;}
  void generateMessage(){
    //cout << name_ << "dummy message" << endl;
    EventRegistry::handleMessage(this);}
private:
  string name_;
};


void EventRegistry::registerCustomer(Barista *s, Customer* o){
  customerMap_[s].insert(o);
  //cout << o->getName() << " subscribe to " << s->getName() << endl;
}

void EventRegistry::deregisterCustomer(Barista* s, Customer* o){
  customerMap_[s].erase(o);
  //cout << o->getName() << " unsubscribe from " << s->getName() << endl;
}

void EventRegistry::handleMessage(Barista *s){
  for (auto e: customerMap_[s])
    e->handleMessage(s);
}

void Customer::handleMessage(Barista *s){
  cout << name_ << ", your drink is ready." << endl;
}


//start of part 3


class Admin {
public:
  Admin(Admin *successor=nullptr):successor_(successor) {}
  virtual void handleRequest (int authority) {
    if (successor_ != nullptr)
      successor_ -> handleRequest(authority);
  }
private:
  Admin *successor_;
};

//derived classes


class juniorBarista: public Admin{
public:
  juniorBarista(Admin *successor=nullptr):Admin(successor) {}
  void handleRequest (int authority) override {
    if (authority == 1)
      cout << "Hi I am the junior Barista here in the coffeeShack. I handled your drink. " <<endl;
    else
      Admin::handleRequest(authority);
  }
};

class seniorBarista:public Admin{
public:
  seniorBarista(Admin *successor=nullptr):Admin(successor) {}
  void handleRequest(int authority) override {
    if (authority == 2)
      cout << "Hi I am the senior Barista here in the coffeeShack. I handled your drink. " <<endl;
    else
      Admin::handleRequest(authority);
  }
};

class Manager: public Admin{
public:
  Manager(Admin *successor=nullptr):Admin(successor) {}
  void handleRequest(int authority) override {
    if (authority == 3)
      cout << "Hi I am the Manager here in the coffeeShack. I handled your drink. " << endl;
    else
      Admin::handleRequest(authority);
  }
};


//the main function

int main(){
  //authority
  //3 is for Manager
  //2 is for seniorBarista
  //1 is for juniorBarista

  Admin *tp = new
    juniorBarista(new seniorBarista(new Manager));

  int authority = 0;

  Drink* d;
  char input;
  string size;
  string state = "notReady"; //notReady,Ready
  string flag = "Y";
  string drink;
  map<string,string>::iterator it;  //iterator to iterate through map
  queue<string> names;
  queue<string> nameforChecking;
  queue<Customer> c;
  map<string,string> CustomerDrink;
  Barista s1("Manager");
  Barista s2("SeniorBarista");
  Barista s3("Juniorbarista");

  do{
    while(flag == "Y"){
      cout << "Welcome to the Coffee Shack. Can I get you a [l]arge, [m]edium, or [s]mall coffee? ";
      cin >> input;

      if (input == 'l') {d = new Drink(DrinkType::large), size = "large";}
      else if (input == 'm') {d = new Drink(DrinkType::medium), size = "medium";}
      else if (input == 's') {d = new Drink(DrinkType::small), size = "small";}
      else cout << "\tInvalid. Options are: [s,m,l]" << endl;

      while(true){
	cout << "Would you like to add [s]prinkles, [c]aramel, milk [f]oam, [i]ce, or [n]ot?" << endl;
	cin >> input;

	if (input == 's') d = new AddSprinkles(d);
	else if (input == 'c') d = new AddCaramel(d);
	else if (input == 'f') d = new AddMilkFoam(d);
	else if (input == 'i') d = new AddIce(d);
	else if (input == 'n') break;
	else cout << "\tInvalid. Options are: [s,c,f,i,n]" << endl;
      }

      //get customer's name

      cout << "Can I get your name?" <<endl;
      string name;
      cin >> name;
      cout << name;
      names.push(name);  //adds name to the queue

      nameforChecking.push(name);  //different queue for checking drinks for customers

      cout << ", your ";
      cout << size;
      cout << "coffee ";
      
      if(d->getIngredients()!="")
        {
          cout<<" with"<<d->getIngredients();
        }

      cout << " is ready. It will be ";
      string priceStr = std::to_string(d->getPrice());
      priceStr = priceStr.substr(0,4);
      cout<< "$" << priceStr << " please." << endl;
      state = "Ready";
      drink = size + " with" + d->getIngredients() ;

      if (drink == "large with" || drink == "medium with" || drink == "small with"){
        authority = 1;
        tp->handleRequest(authority);
        authority = 4;
      }
      else if(drink.find("Foam") == std::string::npos){
        authority = 2;
        tp->handleRequest(authority);
        authority = 4;
      }
      else{
        authority = 3;
        tp->handleRequest(authority);
        authority = 4;
      }

      CustomerDrink.insert({name,drink});
      Customer o1(name);// create a customer

      c.push(o1);//push the customer in a queue of customer objects

      int r = rand() % 2; // random number between 0 and 1

      if (r == 0){
        while(!names.empty()){
	  (c.front()).subscribe(&s1);//customer subscribes

	  s1.generateMessage();//barista sends a message to the customer

	  (c.front()).unsubscribe(&s1);//customer subscribes

	  names.pop();// remove the name after adding it to the cusomer object queue

	  c.pop();// remove  the customer from the queue

        }
        flag = "N";
      }
      else if( r == 1 ){
        flag = "Y";
      }
      delete d;
    }
    
    while(!nameforChecking.empty()){
      for (it = CustomerDrink.begin(); it != CustomerDrink.end(); ++it){
	if (nameforChecking.front() == it->first){  //looking for the drink
	  cout << "Hi I am " << it->first << "That " << it->second << "is mine. Thanks for the drink." <<endl;
	}

	nameforChecking.pop();
      }
    }
  }while(authority<=3);
}
