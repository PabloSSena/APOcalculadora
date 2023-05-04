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

#include <vector>
class KeyboardPablo: public Keyboard{
    std::vector<Key*> keys;
    char keysCount = 0;
    Cpu* cpu;
  public:
    void receive(Digit);
    void receive(Operator);
    void receive(Control);
    Key* getKey(Signal);
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
