//Nafees Mahmood
//CS3 Lab9 CarBuyer cpp code

#include <array>
#include <iostream>
#include <vector>
#include <cstdlib>
#include "CarFactory.h"

using std::vector;
using std::cout;
using std::endl;
using std::iterator;

class CarLot{
public:
  CarLot();
  Car *testDriveCar(){return car4sale_;}

  // if a car is bought, requests a new one
  Car *buyCar(){
    Car *bought = car4sale_;
    car4sale_ = factories_[rand()%factories_.size()]->requestCar();
    return bought;
  }

  //static void nextCar();
  static int lotSize(int carsTried);

  Car *firstCarPtr(){
    Car* bought1 = firstCar_;
    firstCar_ = factories_[rand()%factories_.size()] -> requestCar();
    return bought1;
  }

  Car*  next(){return firstCar_;}

private:
  Car *firstCar_; // pointer to the first car
  Car *car4sale_; // single car for sale at the lot
  vector<CarFactory *> factories_; //vector that contain all the chars with name and other d\
etails
};


CarLot::CarLot(){ // a car lot of 10 cars

  static const std::array<std::string, 2> makes = {"Ford", "Toyota"};

  //gets 10 cars in the vector factories_
  for(int i=0; i<10;++i){ // should create a lot with random Ford and Toyota cars
    std::string str = makes[rand() % makes.size()];
    if(str == "Ford"){
      factories_.push_back(new FordFactory());
    }
    else {
      factories_.push_back(new ToyotaFactory());
    }
  }

  // gets the first car for sale
  car4sale_ = factories_[rand() % factories_.size()] -> requestCar();
}

CarLot *carLotPtr = nullptr; // global pointer instantiation
CarLot *firstCarPtr1 = nullptr;

// test-drives a car
// buys it if Toyota

//void CarLot::nextCar(Car *car){ // the buyer picks the next car to test drive
//void CarLot::nextCar(){
void nextCar(){

  int tries = 0;
  //int i = CarLot::lotSize(tries);


  if (carLotPtr == nullptr)
    carLotPtr = new CarLot();

  Car *toBuy = carLotPtr -> testDriveCar();

  cout << "Buyer " << endl;
  cout << "test driving "
       << toBuy->getMake() << " "
       << toBuy->getModel();

  if (toBuy->getMake() == "Toyota"){
    cout << " love it! buying it!" << endl;
    carLotPtr -> buyCar();
    tries = CarLot::lotSize(tries);
  } else {
    cout << " did not like it!" << endl;
    tries = CarLot::lotSize(tries);
  }

  cout << "Tries taken to buy the car = " << tries << endl ;

  /*if(firstCarPtr1 == nullptr)
    firstCarPtr1 = new CarLot();

  Car* car = firstCarPtr1 -> next();// pointst to the first car
  //Car* car1 = firstCarPtr1 -> factories_[0] -> requestCar();
  //car = carLotPtr -> testDriveCar();
  cout <<"First Car = " << car -> getMake() << endl; //<< car -> getMake() << endl;
  //  delete firstCarPtr1;
  */
}

int CarLot::lotSize(int carsTried){ // returns the number of car the buyer has tried
  carsTried = carsTried+1;
  return carsTried;
}

void toyotaLover(int id){
  int tries = 0;
  //int i = CarLot::lotSize(tries);

  if (carLotPtr == nullptr)
    carLotPtr = new CarLot();

  Car *toBuy = carLotPtr -> testDriveCar();

  cout << "Buyer " << id << endl;
  cout << "test driving "
       << toBuy->getMake() << " "
       << toBuy->getModel();

  if (toBuy->getMake() == "Toyota"){
    cout << " love it! buying it!" << endl;
    carLotPtr -> buyCar();
    tries = CarLot::lotSize(tries);
  } else {
    cout << " did not like it!" << endl;
    tries = CarLot::lotSize(tries);
  }

  cout << "Tries taken to buy the car = " << tries << endl ;

}

// test-drives a car
// buys it if Ford
void fordLover(int id){

  if (carLotPtr == nullptr)
    carLotPtr = new CarLot();

  Car *toBuy = carLotPtr -> testDriveCar();

  cout << "Buyer " << id << endl;
  cout << "test driving "
       << toBuy->getMake() << " "
       << toBuy->getModel();

  int carsTried = 0;

  if (toBuy->getMake() == "Ford"){
    carsTried = carsTried+1;
    cout << " love it! buying it!" << endl;
    carLotPtr -> buyCar();
  } else {
    carsTried = carsTried+1;
    cout << " did not like it!" << endl;
  }

}


int main() {
  srand(time(nullptr));

  const int numBuyers=10;
  for(int i=0; i < numBuyers; ++i){
    if(rand()% 2 == 0){
      toyotaLover(i);
    }
    else{
      fordLover(i);
    }
  }
  nextCar();
  //CarLot::nextCar();
}
