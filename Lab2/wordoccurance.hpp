//Nafees Mahmood
//CS3 Lab2
//Word coccurance header file

#ifndef CS3_wdoccurance_HPP
#define CS3_wdoccurance_HPP

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


class WordOccurance{
public:
  WordOccurance(const string& word ="" , int num=0);
  bool matchWord(const string &);  //returns true if word matches stored
  void increment();  //increments number of occurances
  string getWord() const;
  int getNum() const;

private:
  string word_;
  int num_;
};

class WordList{
public:
  //add copy constructor, destructor, and overloaded assignment

  WordList();  //default
  ~WordList();  //destructor
  WordList(const WordList&);  //copy constructor
  WordList& operator=(WordList);  //overloaded assignment
  //implement comparision as friend
  
  friend bool equal(const WordList&, const WordList&);  //comparision as friend

  void addWord(const string &);
  void print();

private:
  WordOccurance *wordArray_;  //a dynamically allocated array of WordOccurances may or may not be sorted

  int size_;
};

#endif
