//Nafees Mahmood
//CS3 Lab8 Dice Game implementation

// Games, Template Method example
// Mikhail Nesterenko
// 2/4/2014

#include <ctime>
#include <cstdlib>
#include <iostream>

using std::cout; using std::endl;
using std::cin;
// template for any game where players take
// turns to make moves
// and there is a winner
class Game{
public:
  Game():playersCount_(0), movesCount_(0),
         playerWon_(noWinner){}

  // template method
  void playGame(const int playersCount = 0) {
    playersCount_ = playersCount;
    movesCount_=0;

    initializeGame();

    for(int i=0; !endOfGame();
        i = (i+1) % playersCount_ ){
      makeMove(i);
      if (i==playersCount_-1)
        ++movesCount_;
    }
    printWinner();
  }

  virtual ~Game(){}

protected:
  // primitive operations
  virtual void initializeGame() = 0;
  virtual void makeMove(int player) = 0;
  virtual void printWinner() = 0;
  virtual bool endOfGame() {
    return playerWon_ != noWinner;} // this is a hook
  // returns true if winner is decided
  static const int noWinner=-1;

  int playersCount_;
  int movesCount_;
  int playerWon_;
};

class Dice: public Game {

public:
  void initializeGame(){
    playersCount_ = 2; // initalize players                                                 \
                                                                                            \

    for(int i=0; i < numPlayers_; ++i)
      score[i] = 0 ;
  }

  void makeMove(int player){
    static int csum = 0;
    static int hsum= 0;
    static int chigh= 0;
    static int hhigh= 0;
    char ch;

    for(int j = 0; j < 3; ++j){

      if(j == 0){
	cout<<"Computer Rolled : ";
	for (int i = 0; i<5; ++i){
	  int roll = rand() % 6 + 1;
	  cout<< roll <<" ";
	  csum = csum + roll ;
	}
	cout <<"Computer Scored = " << csum << " ";
	if(csum > chigh) chigh = csum;
	csum = 0;
	cout << "Computer's Highest Score = " << chigh << endl;

	cout<<"Human Rolled : ";
	for (int i = 0; i<5; ++i){
	  int roll = rand() % 6 + 1;
	  cout<< roll << " ";
	  hsum = hsum + roll ;
	}
	cout<<"Human Scored = " << hsum << " ";
	if(hsum > hhigh) hhigh = hsum;
	hsum = 0;
	cout << "Human's Highest Score = " << hhigh << endl;
      }
      else if(j==1){
        // after 1st turn is completed
        cout << "Roll again? [y/n] ";
        int a = rand()%2;
        if (a==1){   // 1 for y and 0 for n
          cout << 'y' <<endl;
          cout<<"Computer Rolled : ";
	  for (int i = 0; i<5; ++i){
            int roll = rand() % 6 + 1;
            cout<< roll <<" ";
            csum = csum + roll ;
          }
          cout <<"Computer Scored = " << csum << " ";
          if(csum > chigh) chigh = csum;
          csum = 0;
          cout << "Computer's Highest Score = " << chigh << endl;

          cout<<"Human Rolled : ";
          for (int i = 0; i<5; ++i){
            int roll = rand() % 6 + 1;
            cout<< roll << " ";
            hsum = hsum + roll ;
          }
          cout<<"Human Scored = " << hsum << " ";
          if(hsum > hhigh) hhigh = hsum;
          hsum = 0;
          cout << "Human's Highest Score = " << hhigh << endl;
        }
        else{
          cout << 'n' << endl;
          cout<<"Computer Rolled : Passed ";
	  cout<<"Computer's Highest Score = " << chigh << endl;

          cout<<"Human Rolled : ";
          for (int i = 0; i<5; ++i){
            int roll = rand() % 6 + 1;
            cout<< roll << " ";
            hsum = hsum + roll ;
          }
          cout<<"Human Scored = " << hsum << " ";
          if(hsum > hhigh) hhigh = hsum;
          hsum = 0;
          cout << "Human's Highest Score = " << hhigh << endl;

        }
      }
      else if(j == 2){    // after 2nd turn is completed human is given the option
        cout << "Roll again? [y/n] ";
        cin >> ch;
        cout<<"Computer Rolled : ";
        for (int i = 0; i<5; ++i){
          int roll = rand() % 6 + 1;
          cout<< roll <<" ";
          csum = csum + roll ;
        }
        cout <<"Computer Scored = " << csum << " ";
	if(csum > chigh) chigh = csum;
        csum = 0;
        cout << "Computer's Highest Score = " << chigh << endl;

        if(ch == 'y'){
	  cout<<"Human Rolled : ";
	  for (int i = 0; i<5; ++i){
	    int roll = rand() % 6 + 1;
	    cout<< roll << " ";
	    hsum = hsum + roll ;
	  }
	  cout<<"Human Scored = " << hsum << " ";
	  if(hsum > hhigh) hhigh = hsum;
	  hsum = 0;
	  cout << "Human's Highest Score = " << hhigh << endl;
        }
        else{
          cout<<"Human Rolled : Passed ";
          cout<< "Human's Highest Score = " << hhigh << endl;
        }
      }
      else{
        continue;
      }
    }
    if (chigh > hhigh) playerWon_ = player;
    else playerWon_ = player + 1;
  }

  void printWinner(){
    if(playerWon_==0){
      cout<<"Computer Wins"<<endl;
    }
    else{//playerWon_=11
      cout <<"Human Wins"<<endl;
    }
  }

private:
  static const int numPlayers_ = 2; // max number of players                                \
                                                                                            \

  static const int minMoves_ = 1; // nobody wins before minMoves_                           \
                                                                                            \

  static const int maxMoves_ = 3; // somebody wins before maxMoves_
  int score[numPlayers_];  // 0 is for computer 1 is for human player
};


int main() {
  srand(time(nullptr));
  Game* gp = nullptr;

  // play Dice 1 times                                                                      \
                                                                                            \

  for (int i = 0; i < 1; ++i){
    gp = new Dice;
    gp->playGame();
    delete gp;
  }
}


