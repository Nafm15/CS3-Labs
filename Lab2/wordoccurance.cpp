//Nafees Mahmood
//CS3 Lab2
//Word Occurance cpp file

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "wordoccurance.hpp"

using namespace std;

int main(){

  WordList w;

  string line;
  string word;
  ifstream myfile("text.txt");
  if (myfile.is_open()){
    while(getline(myfile,line)){
      for (int i = 0; i < line.length(); ++i){
	if(line.at(i) != ' '){
	  word = word + line.at(i);
	}
	else{
	  w.addWord(word);
	  word = "";
	}
      }
    }

    myfile.close();
  }

  
  cout << "Word List is: \n";
  w.print();

  return 0;
}

WordOccurance::WordOccurance(const string& word , int num){
  word_= word;
  num_= num;
}


bool WordOccurance::matchWord(const string &word){
  if(word_== word){
    return true;
  }
  else{
    return false;
  }

}


void WordOccurance::increment(){
  num_= num_ + 1;
}

string WordOccurance::getWord() const{
  return word_;
}

int WordOccurance::getNum() const{
  return num_;
}


//****************//

//default

WordList::WordList(){
  size_ = 0;
  wordArray_ = new WordOccurance[size_];
}


//destructor
WordList::~WordList(){
  delete [] wordArray_;
}

WordList::WordList(const WordList& rhs){ //copy

  size_ = rhs.size_;
  wordArray_ = new WordOccurance[rhs.size_];
  for(int i = 0; i < size_; ++i){
    wordArray_[i] = rhs.wordArray_[i];
  }
}


WordList& WordList::operator= (WordList rhs){ //assingment
  if(this!= &rhs){
    size_ = rhs.size_;
    delete[]wordArray_;
    wordArray_ = new WordOccurance[rhs.size_];
    for(int i = 0; i < size_; ++i)
      wordArray_[i] = rhs.wordArray_[i];
  }
  return *this;
}


bool equal(const WordList &lhs, const WordList &rhs){ //comparision
  if(lhs.size_ == rhs.size_){
    for(int i = 0; i < rhs.size_; ++i){
      if((lhs.wordArray_[i].getWord() != rhs.wordArray_[i].getWord()) && (lhs.wordArray_[i].getNum() != rhs.wordArray_[i].getNum()))
	return false;
    }
    return false;
  }
  else{
    return false;
  }
}


void WordList::addWord(const string &word){
  WordOccurance *temp;
  for(int i = 0; i < size_; ++i){
    if(wordArray_[i].getWord() == word){
      wordArray_[i].increment();
      return;
    }
  }
  
  size_ = size_ + 1;
  WordOccurance newWord(word,1);  //it's a different word
  temp = new WordOccurance[size_];
  int i;
  for(int i = 0; i < size_ - 1; ++i){
    temp[i] = wordArray_[i];
  }
  temp[size_ -1 ] = newWord;
  delete [] wordArray_;
  wordArray_ = temp;
}



void WordList::print(){
  WordOccurance obj;
  int j,k;
  for(int i = 1; i < size_; ++i){
    obj = wordArray_[i];
    k = wordArray_[i].getNum();
    j = i - 1;
    while(j >= 0 && wordArray_[i].getNum() > k){
      wordArray_[j+1] = wordArray_[j];
      j = j - 1;
    }

    wordArray_[j+1] = obj;
  }

  string str;
  int temp;
  for(int i = 0; i < size_; ++i){
    temp = wordArray_[i].getNum();
    str = wordArray_[i].getWord();
    cout << "Word: " << str << "\t" << "frequency: " << temp << endl;
  }
}
