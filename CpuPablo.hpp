#include "calculator.hpp"

class CpuPablo: public Cpu{
    Display* display;
    Keyboard* keyboard;
    Operator op;
    Digit vet_digit_display[8];

    int flag_decimalSeparator1 = 0;
    int flag_decimalSeparator2 = 0;

    int pos_decimalSeparator_1 = -1;
    int pos_decimalSeparator_2 = -1;

    int flagOperador = 0; // quando for 1 ja foi passsado um operdador
    int contador_registro_1 = 0;
    int contador_registro_2 = 0;
    float vet_registro_1[8];
    float vet_registro_2[8];
    float result;
    float pegar_numero(const float* digits, int size, int registrador); // traduz os digitos para fazer operações aritméticas
    void number_to_digits(float num);
    float pegar_decimal(float number); // pega a parte decimal do numero

    float numero_inteiro(const float* digits,int size);
    float numero_real(const float* digits,int size, int operador);

  public:
    void receive(Digit);
    void receive(Operator);
    void receive(Control);
    void setDisplay(Display*);
};