#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <map>
#include <utility>

using namespace::std;
using std::map;
using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move;

class Student{
public:
  Student(string firstName, string lastName):
    firstName_(firstName), lastName_(lastName) {}


  // move constructor, not really needed, generated automatically
  Student(Student && org):
    firstName_(move(org.firstName_)),
    lastName_(move(org.lastName_))
  {}


  // force generation of default copy constructor
  Student(const Student & org) = default;

  string print() const {return firstName_ + ' ' + lastName_ ;}

  // needed for sort()
  friend bool operator< (Student left, Student right){
      return left.lastName_ < right.lastName_ ||
                              (left.lastName_ == right.lastName_ &&
                               left.firstName_ < right.firstName_);
  }

private:
  string firstName_;
  string lastName_;
};

//a map of Student and vector<string> was too hard i couldnt figure it out this is easier
// reading a list from a fileName
void readRoster(map<Student, string>& roster, string fileName);
// printing a list out
void printRoster(const map<Student, string>& roster);

string getName(string fileName);

int main(int argc, char* argv[]){
  if (argc <= 1){
    cout << "usage: " << argv[0] << " list of courses, dropouts last" << endl; exit(1);
  }

  map<Student, string> roster;

  for(int i=1; i < argc; ++i){
    readRoster(roster, argv[i]);
  }

  cout<<"last name, \t "<<" first name: \t"<<"  course enrolled \t"<<"\n";
  printRoster(roster);
}

void readRoster(map<Student, string>& roster, string fileName){
  ifstream course(fileName);
  string first, last;
  while(course >> first >> last){
    Student s (first, last);
    int flag=0;
    auto it = roster.find(s); // iterator
    if(it != roster.end()){
      it->second=it->second+'\t' + fileName;
    }
    else{
      roster.emplace(std::make_pair(s,fileName));
    }
  }
  course.close();
}

// printing a list out
void printRoster(const map<Student,string>& roster){
  for(auto it=roster.cbegin(); it != roster.cend(); ++it){
    cout << it->first.print()<< ' ' << it->second << endl;
  }
}

