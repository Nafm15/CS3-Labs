// filled/hollow figures demonstrates Bridge Design Pattern,
// square is either hollow or square and is painted with a particular character,
// it is bridged over Figure --> Fill abstract body/handle
// Mikhail Nesterenko
// 2/12/2014

#include <iostream>

using std::cout; using std::endl; using std::cin;

// abstract body
class Fill{
public:
  Fill(char fillChar, char borderChar):fillChar_(fillChar),borderChar_(borderChar){}
  virtual char getBorder()=0;
  virtual char getInternal()=0;
  virtual ~Fill() {}
protected:
  char fillChar_;
  char borderChar_;
};

// concrete body
class Hollow: public Fill{
public:
  Hollow(char borderChar):Fill(' ',borderChar){}
  char getBorder() override {return borderChar_;}
  char getInternal() override {return ' ';}
  ~Hollow(){}
};



// another concrete body
class Filled: public Fill {
public:
  // Filled(char fillChar,char borderChar):Fill(fillChar,borderChar){}
  Filled(char fillChar):Fill(fillChar,fillChar){}
  char getBorder() override {return borderChar_;}
  char getInternal() override {return fillChar_;}
  ~Filled(){}
};


// Enhanced Filled
class EnhancedFilled: public Fill {
public:
  EnhancedFilled(char fillChar,char borderChar):Fill(fillChar,borderChar){}
  char getBorder() override {return borderChar_;}
  char getInternal() override {return fillChar_;}
  ~EnhancedFilled(){}
};

// abstract handle
class Figure {
public:
  Figure(int size, Fill* fill): size_(size),
                                fill_(fill){}
  virtual void draw() =0;
  virtual ~Figure(){}
  void changeFill(const Fill*);
protected:
  int size_;
  Fill *fill_;
};


void Figure::changeFill(const Fill* fill)
{
  fill_ = const_cast<Fill*>(fill);
}

// concrete handle
class Square: public Figure{
public:
  Square(int size, Fill* fill): Figure(size, fill){}
  void draw() override;

};

void Square::draw(){
  for(int i=0; i < size_; ++i){
    for(int j=0; j < size_; ++j)
      if(i==0 || j==0 || i==size_-1 || j==size_-1 )
        cout << fill_ -> getBorder();
      else
        cout << fill_ -> getInternal();
    cout << endl;
  }
}


int main(){
  
  // ask user for figure parameters
  cout << "Enter fill character: ";
  char fchar; cin >> fchar;
  cout << "Enter border character: ";
  char bchar; cin >> bchar;

  cout << "Filled or hollow? [f/h] ";
  char ifFilled; cin >> ifFilled;
  cout << "Enter size: "; int size; cin >> size;

  Figure *userBox = new Square(size, ifFilled == 'f'?static_cast<Fill *>(new Filled(fchar)):\
			       static_cast<Fill *>(new Hollow(bchar)));
  cout<<"Filled Box = "<<endl;
  userBox -> draw();
  cout << endl;
  cout<<"Enter change fill char : "<<endl;
  char c;
  cin>>c;
  cout<<"Enter change fill char : "<<endl;
  userBox-> changeFill(new Filled(c));
  userBox->draw();
  cout<<endl;

  Figure *userBox1 = new Square(size,static_cast<Fill *>(new EnhancedFilled(fchar,bchar)));
  cout<<"Enhanced Filled:"<<endl;
  userBox1-> draw();
  cout<<endl;

}
