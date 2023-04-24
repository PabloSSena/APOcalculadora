#include "calculatorPablo.hpp"
#include <iostream>

CalculatorErrorPablo::CalculatorErrorPablo(char const *message) {
  this->message = message;
}
char const *CalculatorErrorPablo::getMessage() { return this->message; }

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

void DisplayPablo::setSignal(Signal signal) { std::cout << (signal==NEGATIVE?"-":""); }

void DisplayPablo::addDecimalSeparator() { std::cout << "."; }

void DisplayPablo::clear() { std::cout << "\n"; }

void CpuPablo::number_to_digits(int num) {
    Digit digits[8];
    int counter = 0;
    int i = 0;
    if (num == 0) {
        this->vet_digit_1[0] = ZERO;
        this->vet_digit_1_number = 1;
    }
    while (num != 0) {
        int digit = num % 10;
        this->vet_digit_1[counter] = static_cast<Digit>(digit);
        counter++;
        num /= 10;
    }
    this->vet_digit_1_number = counter;
}

void CpuPablo::receive(Digit digit) { 
    if(this->flagOperador == 0){
        this->vet_digit_1[this->vet_digit_1_number] = digit;
        this->vet_digit_1_number++;
    }
    else{
        this->vet_digit_2[this->vet_digit_2_number] = digit;
        this->vet_digit_2_number++;
    }
    if(this->display)
        this->display->add(digit); 
}

void CpuPablo::receive(Operator op) { 
    this->op = op;
    this->flagOperador++;
}

int CpuPablo::translate_digit(const Digit* digits, int size){
    int result = 0;
    for (int i = 0; i < size; i++){

        result = result * 10 + static_cast<int>(digits[i]);
    }
    return result;
}

void CpuPablo::receive(Control control) {
    int digito_1, digito_2;
    switch (control){
    case EQUAL:
            digito_1 = this->translate_digit(this->vet_digit_1,this->vet_digit_1_number);
            digito_2 = this->translate_digit(this->vet_digit_2,this->vet_digit_2_number);
            switch (this->op){
            case SUM:
                this->result = digito_1 + digito_2;
                this->number_to_digits(result);
                for(int i = this->vet_digit_1_number; i >= 0;i--){
                    this->display->add(this->vet_digit_1[i]);
                }
                break;
            case SUBTRACTION:
                this->result = digito_1 - digito_2;
                break;
            case DIVISION:
                this->result = digito_1 / digito_2;
                break;
            case MULTIPLICATION:
                this->result = digito_1 * digito_2;
                break;
            default:
                break;
            }
        break;;
    default:
        break;
    }
}
void CpuPablo::setDisplay(Display *display) { 
    this->display = display; 
}

void KeyboardPablo::receive(Digit digit) { if(this->cpu)this->cpu->receive(digit);else std::cerr << "Keyboard without cpu!\n"; }
void KeyboardPablo::receive(Operator operator_) { if(this->cpu)this->cpu->receive(operator_);else std::cerr << "Keyboard without cpu!\n"; }

void KeyboardPablo::receive(Control control) { 
    if(this->cpu)
    this->cpu->receive(control);
    else std::cerr << "Keyboard without cpu!\n"; 
}

Key *KeyboardPablo::getKey(Digit digit) { 
    for(Key* key: this->keys) 
        if(dynamic_cast<KeyDigit*>(key) && ((KeyDigit*)key)->getDigit() == digit) 
            return key; 
    throw new CalculatorErrorPablo("Key with digit not found!"); }

Key *KeyboardPablo::getKey(Operator operator_) { 
    for(Key* key: this->keys) 
        if(dynamic_cast<KeyOperator*>(key) && ((KeyOperator*)key)->getOperator() == operator_) 
            return key; 
    throw new CalculatorErrorPablo("Key with operator not found!"); }

Key *KeyboardPablo::getKey(Control control) { for(Key* key: this->keys) if(dynamic_cast<KeyControl*>(key) && ((KeyControl*)key)->getControl() == control) return key; throw new CalculatorErrorPablo("Key with control not found!"); }
Key *KeyboardPablo::getKey(Symbol symbol) { for(Key* key: this->keys) if(key->getSymbol() == symbol) return key; throw new CalculatorErrorPablo("Key with symbol not found!"); }
void KeyboardPablo::add(Key *key) {
  if (key != NULL){
    this->keys.push_back(key);
    key->setKeyboard(this);
  }
}
void KeyboardPablo::setCpu(Cpu *cpu) { this->cpu = cpu; }

KeyDigitPablo::KeyDigitPablo(Symbol symbol, Digit digit) {
  this->symbol = symbol;
  this->digit = digit;
}
void KeyDigitPablo::press() {
  if (this->keyboard != NULL)
    this->keyboard->receive(this->digit);
}
Symbol KeyDigitPablo::getSymbol() { return this->symbol; }
void KeyDigitPablo::setKeyboard(Keyboard *keyboard) {
  this->keyboard = keyboard;
}
Digit KeyDigitPablo::getDigit() { return this->digit; }

KeyControlPablo::KeyControlPablo(Symbol symbol, Control control) {
  this->symbol = symbol;
  this->control = control;
}
void KeyControlPablo::press() {
  if (this->keyboard != NULL)
    this->keyboard->receive(this->control);
}
Symbol KeyControlPablo::getSymbol() { return this->symbol; }
void KeyControlPablo::setKeyboard(Keyboard *keyboard) {
  this->keyboard = keyboard;
}
Control KeyControlPablo::getControl() { return this->control; }

KeyOperatorPablo::KeyOperatorPablo(Symbol symbol, Operator operator_) {
  this->symbol = symbol;
  this->operator_ = operator_;
}
void KeyOperatorPablo::press() {
  if (this->keyboard != NULL)
    this->keyboard->receive(this->operator_);
}
Symbol KeyOperatorPablo::getSymbol() { return this->symbol; }
void KeyOperatorPablo::setKeyboard(Keyboard *keyboard) {
  this->keyboard = keyboard;
}
Operator KeyOperatorPablo::getOperator() { return this->operator_; }

void CalculatorPablo::setDisplay(Display* display) { this->display = display; }
Display* CalculatorPablo::getDisplay() { return this->display; }
void CalculatorPablo::setCpu(Cpu* cpu) { this->cpu = cpu; }
Cpu* CalculatorPablo::getCpu() { return this->cpu; }
void CalculatorPablo::setKeyboard(Keyboard* keyboard) { this->keyboard = keyboard;}
Keyboard* CalculatorPablo::getKeyboard() { return this->keyboard; }