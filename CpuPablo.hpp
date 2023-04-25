#include "calculator.hpp"

class CpuPablo: public Cpu{
    Display* display;
    Keyboard* keyboard;
    int flagOperador = 0; // quando for 1 ja foi passsado um operdador
    int contador_registro_1 = 0;
    int contador_registro_2 = 0;
    Digit vet_digit_display[8];
    float vet_registro_1[8];
    float vet_registro_2[8];
    Operator op;
    int result;
    int translate_digit(const float* digits, int size); // traduz os digitos para fazer operações aritméticas
    void number_to_digits(int num);
  public:
    void receive(Digit);
    void receive(Operator);
    void receive(Control);
    void setDisplay(Display*);
};