#pragma once
#include "calculator.hpp"

class KeyOperatorPablo: public KeyOperator{
    Symbol symbol;
    Operator operator_;
    Keyboard* keyboard;
  public:
    KeyOperatorPablo(Symbol, Operator);
    void press();
    Symbol getSymbol();
    void setKeyboard(Keyboard*);
    Operator getOperator();
};

class DisplayPablo: public Display{
  public:
    void add(Digit digit);
    void setSignal(Signal);
    void addDecimalSeparator();
    void clear();
};

class CpuPablo: public Cpu{
    Display* display;
    Keyboard* keyboard;
    int flagOperador = 0; // quando for 1 ja foi passsado um operdador
    int vet_digit_1_number = 0;
    int vet_digit_2_number = 0;
    Digit vet_digit_1[8];
    Digit vet_digit_2[8];
    Operator op;
    int result;
    int translate_digit(const Digit* digits, int size); // traduz os digitos para fazer operações aritméticas
    void number_to_digits(int num);
  public:
    void receive(Digit);
    void receive(Operator);
    void receive(Control);
    void setDisplay(Display*);
};
#include <vector>
class KeyboardPablo: public Keyboard{
    std::vector<Key*> keys;
    char keysCount = 0;
    Cpu* cpu;
  public:
    void receive(Digit);
    void receive(Operator);
    void receive(Control);
    Key* getKey(Digit);
    Key* getKey(Operator);
    Key* getKey(Control);
    Key* getKey(Symbol);
    void add(Key*); 
    void setCpu(Cpu*);
};

class KeyDigitPablo: public KeyDigit{
    Symbol symbol;
    Digit digit;
    Keyboard* keyboard;
  public:
    KeyDigitPablo(Symbol, Digit);
    void press();
    Symbol getSymbol();
    void setKeyboard(Keyboard*);
    Digit getDigit();
};


class KeyControlPablo: public KeyControl{
    Symbol symbol;
    Control control;
    Keyboard* keyboard;
  public:
    KeyControlPablo(Symbol, Control);
    void press();
    Symbol getSymbol();
    void setKeyboard(Keyboard*);
    Control getControl();
};


class CalculatorPablo: public Calculator{
    Display *display;
    Cpu *cpu;
    Keyboard *keyboard;
  public:
    void setDisplay(Display*);
    Display* getDisplay();
    void setCpu(Cpu*);
    Cpu* getCpu();
    void setKeyboard(Keyboard*);
    Keyboard* getKeyboard();
};

class CalculatorErrorPablo: public CalculatorError{
  char const* message;
  public:
    CalculatorErrorPablo(char const* message);
    char const* getMessage();
};