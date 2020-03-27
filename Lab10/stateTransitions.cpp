//Nafees Mahmood
//State Transition Part of Lab10

// demonstrates state design pattern
// Mikhail Nesterenko
// 2/23/2014

#include <iostream>
#include <string>
#include <queue>

using std::cin; using std::cout; using std::endl; using std::string;
using std::queue;

class State;

//context
class Process{
public:

  Process();
  //virtual Process clone() =0;
  //behaviors
  void admitted();
  void interrupt();
  void exitP();
  void IOeventCompletion();
  void schedulerDispatch();
  void IOeventWait();

  string report();

  //part of implementation of state pattern
  void changeState(State* s){state_=s;}
private:
  State* state_;
};

//abstract state
class State{
public:
  
  virtual string report() =0;
  //default implementations
  virtual void admitted(Process*) {}
  virtual void interrupt(Process*) {}
  virtual void exitP(Process*) {}
  virtual void IOeventCompletion(Process*) {}
  virtual void schedulerDispatch(Process*) {}
  virtual void IOeventWait(Process*) {}
  void changeState(Process* c, State* s){
    c->changeState(s);
  }
};

//clone returns base class type
//Process* clone() {return new Process();}

//states
class newProcess: public State{ //new process
public:
  static State* instance(){
    static State* onlyInstance = new newProcess;
    return onlyInstance;
  }
  void admitted(Process *c) override;  //goes to ready
  string report() override {return "new";}
};

class ready: public State{ // ready process
public:
  static State* instance(){
    static State* onlyInstance = new ready;
    return onlyInstance;
  }
  void schedulerDispatch(Process* c) override; // goes to running
  string report() override {return "ready";}
};


class waiting: public State{
public:
  static State* instance(){
    static State* onlyInstance = new waiting;
    return onlyInstance;
  }
  void IOeventCompletion(Process* c) override; // goes to ready
  string report() override {return "waiting";}
};

class running: public State{
public:
  static State* instance(){
    static State* onlyInstance = new running;
    return onlyInstance;
  }
  void interrupt(Process* c) override;  // goes to ready
  void IOeventWait(Process* c) override;// goes to waiting
  void exitP(Process* c) override;      // process gets terminated
  string report() override {return "running";}
};

class terminated: public State{
public:
  static State* instance(){
    static State* onlyInstance = new terminated;
    return onlyInstance;
  }
  string report() override {return "terminated";}
};

// State transitions member functions
// Ready
void ready::schedulerDispatch(Process *c)
{changeState(c, running::instance());}
// new process
void newProcess::admitted(Process *c)
{changeState(c, ready::instance());}

// Running
void running::interrupt(Process *c)
{changeState(c, ready::instance());}
void running::IOeventWait(Process *c)
{changeState(c, waiting::instance());}
void running::exitP(Process *c)
{changeState(c, terminated::instance());}

// Waiting
void waiting::IOeventCompletion(Process *c)
{changeState(c, ready::instance());}

// Process  member functions
Process::Process(){state_= newProcess::instance();}

// handles/behaviors
void Process::admitted(){state_->admitted(this);}
void Process::interrupt(){state_->interrupt(this);}
void Process::exitP(){state_->exitP(this);}
void Process::IOeventCompletion(){state_->IOeventCompletion(this);}
void Process::schedulerDispatch(){state_->schedulerDispatch(this);}
void Process::IOeventWait(){state_->IOeventWait(this);}

string Process::report(){return state_->report();}

int main(){
  cout << "Admit(A) takes process from new to ready" <<endl;
  cout << "schedulerDispatch(D) takes process from ready to running" <<endl;
  cout << "Interrupt(I) takes process from running to ready" <<endl;
  cout << "IOeventWait(W) takes process from running to waiting" <<endl;
  cout << "Exit(E) takes process from running to terminated" <<endl;
  cout << "IOeventCompletion(X) takes process from waiting to ready" <<endl;

  Process p1;
  cout << "Process is " << p1.report() << endl;

  while(p1.report() != "terminated"){

    cout << "Process Commands: Admit(A),Interrupt(I),Exit(E),IOevenCompletion(X),scheduleDis\
patch(D),IOeventWait(W) [A,I,E,X,D,W] : ";
    char action; cin >> action;
    if(action == 'A'){
      p1.admitted(); // gets the process to ready from new
    }
    else if(action == 'D'){
      p1.schedulerDispatch(); // gets the process to running from ready
    }
    else if(action == 'I'){
      p1.interrupt();// gets the process to ready from running
    }
    else if(action == 'E'){
      p1.exitP(); // gets he process to terminated from running
    }
    else if(action == 'W'){
      p1.IOeventWait(); // gets the process to waiing from running
    }
    else if(action == 'X'){
      p1.IOeventCompletion(); // gets the process to ready from waiting
    }

    cout << "Process is " << p1.report() << endl;
  }
  // demonstrates that two Characters may be in two different states
  Process p2;
  cout << "Process 1 is " << p1.report() << " while "
       << "Process 2 is " << p2.report() << endl;

  Process p3;
  Process p4;
  Process p5;
  Process p6;

  queue<Process>ready;
  queue<Process>running;
  queue<Process>waiting;
  // getting all processes to ready
  p3.admitted();
  p4.admitted();
  p5.admitted();
  p6.admitted();

  cout<< "Making all the processes ready" << endl;
  cout<< "p1 " <<p3.report() << endl;
  cout<< "p2 " <<p4.report() << endl;
  cout<< "p3 " <<p5.report() << endl;
  cout<< "p4 " <<p6.report() << endl;
  // putting all the ready processes in ready queue


  ready.push(p3);
  ready.push(p4);
  ready.push(p5);
  ready.push(p6);

  //  while((p3.report() != "terminated") && (p4.report() != "terminated") && (p5.report() != "terminated") && (p6.report() != "terminated")){
  while(!ready.empty()){
    running.push(ready.front());// getting the first element of ready in running
    ready.pop(); // deleting the first element from ready
    (running.front()).schedulerDispatch(); // making the first element of running queue running from ready
    cout<<"Converting the process to running : now "<<(running.front()).report()<<endl;
    int v = rand() % 3 + 1; // getting a random number from 1 - 3
    if(v == 1){ // if 1 then exit from running
      (running.front()).exitP(); // the process is terminated now so we remove it from the running
      cout<<"Terminating the process. Process "<< (running.front()).report()<<endl;
      //destroy the process here
      running.pop();
    }
    else if(v == 2){  // if 2 then interrupt
      (running.front()).interrupt(); // makes the running process ready again
      ready.push(running.front());  // transferring the ready process to ready queue
      cout<<"Convert the running process to ready again. Process "<<(ready.front()).report()<<endl;
      running.pop(); // removing from the running queue
    }
    else if(v == 3){ // if 3 then IOeventWait
      (running.front()).IOeventWait(); // makes the running process wait
      cout<<"Converting the process to waiting from running: Process "<<(running.front()).report()<<endl;
      //push the waiting process in waiting queue
      waiting.push(running.front());
      running.pop();
      (waiting.front()).IOeventCompletion(); // makes the waiting process ready again
      cout<<"Converting the waiting process to ready again: Process "<<(waiting.front()).report()<<endl;
      ready.push(waiting.front()); // putting the ready process in ready queue
      waiting.pop();
    }
  }
}

