//Nafees Mahmood
//CS3 Lab1

#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using std::cout; using std::endl;


int main(int argc, char* argv[]){
  
  int line = 0;

  ifstream myfile1("file1.txt");
  ifstream myfile2("file2.txt");

  if (myfile1.is_open() && myfile2.is_open()){
    while (!myfile1.eof() &&  !myfile2.eof()){       //counting no. of lines
      string str1;
      string str2;
      int space = 13;
      int loc = 0;
      getline(myfile1, str1);
      getline(myfile2, str2);
      line++;

      if (str1 == str2){
	continue;
      }

      else{
	for (int i = 0; i < str1.length() && str2.length(); ++i){  //comparing 2 strings
	  
	  if (str1.at(i) == str2.at(i)){  //finding where characters are different
	  }
	  else{
	    loc = i;
	  }
	}

	if (line > 9){
	  loc++;
	}

	cout << argv[1] << ": " << ": " << str1 << endl;
	cout << argv[2] << ": " << ": " << str2 << endl;
	for (int i = 0; i <= space + loc; ++i){
	  cout << ' ';
	}

	cout << '^' << endl;
      }
    }

    if (myfile1.eof()){
      string str2;
      int space = 14;
      getline(myfile2, str2);
      cout << argv[1] << ": " << line << ": " << endl;
      cout << argv[2] << ": " << line << ": " << str2  << endl;
      for (int i = 0; i <= space; ++i){
	cout << ' ';
      }
      cout << '^' << endl;
    }
    
    else if (myfile2.eof()){
      string str1;
      int space = 14;
      getline(myfile1, str1);
      cout << argv[1] << ": " << line << ": " << str1 << endl;
      cout << argv[2] << ": " << line << ": " << endl;
      for (int i = 0; i <= space; ++i){
	cout << ' ';
      }
      cout << '^' << endl;
    }
  }

  else{
    cout << "Unable to open files" << endl;
  }

  myfile1.close();
  myfile2.close();

  return 0;
}
