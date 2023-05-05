#include"displayPablo.hpp"
#include <iostream>

void DisplayPablo::add(Digit digit) {
  switch (digit) {
  case ZERO: std::cout << "0"; break;
  case ONE: std::cout << "1"; break;
  case TWO: std::cout << "2"; break;
  case THREE: std::cout << "3"; break;
  case FOUR: std::cout << "4"; break;
  case FIVE: std::cout << "5"; break;
  case SIX: std::cout << "6"; break;
  case SEVEN: std::cout << "7"; break;
  case EIGHT: std::cout << "8"; break;
  case NINE: std::cout << "9"; break;
  default:
    std::cout << "E";
    throw new CalculatorErrorPablo("Digit not implemented!!!");
  }
}
void DisplayPablo::refresh(){
      console.setColorBg256(Color::BG_Red);
      console.setColorFg256(Color::FG_White);
      // console.clear_screen();


      // if(signal==NEGATIVE){
      //   this->showDigitShape("    ","    ", "████", "    ","    ",0);
      // } else {
      //   // this->showDigitShape("    ","  █ ", " ███", "  █ ","    ",0);
      //   this->showDigitShape("    ","    ", "    ", "    ","    ",0);
      // }
      
      // for(int i = 1; i <= this->digitsCount; i++){
      //   switch(this->digits[i-1]){
      //   case ZERO:
      //     this->console.set_cursor(1, 1+i * 5);printf("0000");
      //     this->console.set_cursor(2, 1+i * 5);printf("0  0");
      //     this->console.set_cursor(3, 1+i * 5);printf("0  0");
      //     this->console.set_cursor(4, 1+i * 5);printf("0  0");
      //     this->console.set_cursor(5, 1+i * 5);printf("0000");
      //     break;
      //   case ONE:
      //     this->console.set_cursor(1, 1+i * 5);printf("   1");
      //     this->console.set_cursor(2, 1+i * 5);printf("   1");
      //     this->console.set_cursor(3, 1+i * 5);printf("   1");
      //     this->console.set_cursor(4, 1+i * 5);printf("   1");
      //     this->console.set_cursor(5, 1+i * 5);printf("   1");
      //     break;
      //   case TWO:
      //     this->showDigitShape("2222","   2","2222","2  ","2222",i);
      //     break;
      //   case THREE:
      //     this->showDigitShape("😀😀","  😀","😀😀","  😀","😀😀",i);
      //     break;
      //   case FOUR:
      //     this->showDigitShape("█  █","█  █", "████", "   █","   █",i);
      //     break;
      //   default:
      //     this->showDigitShape(" ██ ","█  █", "  █ ", "    ","  █ ",i);
      //   }
      //   printf(dots[i-1]?"█":" ");
      
    }
void DisplayPablo::setSignal(Signal signal) { 
  // if(this->cpu.flagOperador == 0)
  //   this->cpu.flag_signal_1 = 1;
  // else 
  //   this->cpu.flag_signal_2 = 1;
  std::cout << (signal==NEGATIVE?"-":"");
}

void DisplayPablo::addDecimalSeparator() { 
  std::cout << "."; 
}

void DisplayPablo::clear() { std::cout << "\n"; }