#include"CpuPablo.hpp"
#include <iostream>
void CpuPablo::number_to_digits(int num) {
    Digit digits[8];
    int counter = 0, digitsCounter = 0;
    int i = 0;
    if (num == 0) {
        this->vet_registro_1[0] = ZERO;
        this->contador_registro_1 = 1;
    }
    while (num != 0) {
        int digit = num % 10;
        digits[digitsCounter] = static_cast<Digit>(digit);
        digitsCounter++;
        num /= 10;
    }

    for(int i = digitsCounter-1; i >=0; i--){
      this->vet_digit_display[counter] = digits[i];
      counter++;
    }
    this->contador_registro_1 = counter;
}

int CpuPablo::translate_digit(const float* digits, int size){
    int result = 0;
    for (int i = 0; i < size; i++){

        result = result * 10 + static_cast<float>(digits[i]);
    }
    return result;
}

void CpuPablo::receive(Digit digit) { 
    if(this->flagOperador == 0){
        this->vet_registro_1[this->contador_registro_1] = digit;
        this->contador_registro_1++;
    }
    else{
        this->vet_registro_2[this->contador_registro_2] = digit;
        this->contador_registro_2++;
    }
    if(this->display)
        this->display->add(digit); 
}

void CpuPablo::receive(Operator op) { 
    this->op = op;
    this->flagOperador++;
}

void CpuPablo::receive(Control control) {
    int digito_1, digito_2;
    switch (control){
    case EQUAL:
            digito_1 = this->translate_digit(this->vet_registro_1,this->contador_registro_1);
            digito_2 = this->translate_digit(this->vet_registro_2,this->contador_registro_2);
            switch (this->op){
            case SUM:
                this->result = digito_1 + digito_2;
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
            this->number_to_digits(result);
            for(int i = 0; i < this->contador_registro_1;i++){
              this->display->add(this->vet_digit_display[i]);
            }
        break;
    case DECIMAL_SEPARATOR:
        printf("Entro aqui?");
        if(this->display)
            this->display->addDecimalSeparator();
        break;
    default:
        break;
    }
}
void CpuPablo::setDisplay(Display *display) { 
    this->display = display; 
}