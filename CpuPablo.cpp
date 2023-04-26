#include"CpuPablo.hpp"
#include <iostream>
#include <cmath>
void CpuPablo::number_to_digits(float num) {
    Digit digits[8], vetor_organizador[8];
    int counter = 0,digits_counter = 0, counter_vetor_organizador = 0, aux = 0;
    int parte_inteira = (int)num; // pegando parte inteira do numero
    float parte_decimal = num - parte_inteira; // pegando parte decimal

    if (num == 0) {
        this->vet_registro_1[0] = ZERO;
        this->contador_registro_1 = 1;
    }

    while (parte_inteira > 0){
        int digito = parte_inteira % 10;
        parte_inteira = parte_inteira / 10;
        digits[digits_counter] = static_cast<Digit>(digito);
        digits_counter++;
    }
    for(int i = digits_counter; i >=0 ;i--){
        vetor_organizador[aux] = digits[i];
        aux++;
    }

    while (parte_decimal > 0){
        parte_decimal = parte_decimal * 10; // por exemplo: 0,45 vira 4,5 aí conseguimos pegar o 4
        int digito = (int)parte_decimal;    // cast pra int pra vir só o numero antes da virgula
        digits[digits_counter] = static_cast<Digit>(digito);
        digits_counter++;
        parte_decimal = parte_decimal - digito; // parte decimal nesse momento é 4,5 fazemos -4 para nos sobrar só o 5
    }

    for(int i = digits_counter - aux; i >= 0;i--){ //Organizando a parte decimal
        vetor_organizador[i+1] = digits[i+1]; 
        counter_vetor_organizador++;                    
    }

    for(int i = 0; i <=counter_vetor_organizador; i++){
      this->vet_digit_display[counter] = vetor_organizador[i];
      counter++;
    }
    // this->contador_registro_1 = counter;

    // Digit digits[8];
    // int counter = 0, digitsCounter = 0;
    // int i = 0;
    // if (num == 0) {
    //     this->vet_registro_1[0] = ZERO;
    //     this->contador_registro_1 = 1;
    // }
    // float digit = num;
    // while (num != 0) {
    //     // int digit = num % 10;
    //     digits[digitsCounter] = static_cast<Digit>(digit);
    //     digitsCounter++;
    //     num /= 10;
    // }


}

float CpuPablo::pegar_decimal(float number){
    float aux = number;
    int count = 0;
    while (aux >= 1){
        aux /= 10;
        count++;
    }
    return number / pow(10,count);
}

float CpuPablo::numero_inteiro(const float* digits,int size){
    float result = 0;

    for (int i = 0; i < size; i++){
            result = result * 10 + static_cast<float>(digits[i]);
    }

    return result;
}

float CpuPablo::numero_real(const float* digits,int size, int operador){
    float result = 0;
    float decimals = 0;

    switch (operador){
    case 1:
        for (int i = 0; i < size; i++){
            if(i < this->pos_decimalSeparator_1){
                result = result * 10 + static_cast<float>(digits[i]);
            }
            else{
                decimals = decimals * 10 + static_cast<float>(digits[i]);
            }
        }
        return result += pegar_decimal(decimals);
    break;
    
    case 2: 
        for (int i = 0; i < size; i++){
            if(i < this->pos_decimalSeparator_2){
                result = result * 10 + static_cast<float>(digits[i]);
            }
            else{
                decimals = decimals * 10 + static_cast<float>(digits[i]);
            }
        }
        return result += pegar_decimal(decimals);
    default:
        break;
    }

}


float CpuPablo::pegar_numero(const float* digits, int size, int registrador){
    if(this->flag_decimalSeparator1 == 0 && registrador == 1){ //Caso o número seja inteiro
        return numero_inteiro(digits,size);
    }
    if(this->flag_decimalSeparator2 == 0  && registrador == 2){ //Caso o número seja inteiro
        return numero_inteiro(digits,size);
    }
    
    //Caso tenha decimal
    if(this->pos_decimalSeparator_1 > 0 && registrador == 1){  //Caso o número seja real       
        return numero_real(digits,size,1);
    }
    if(this->pos_decimalSeparator_2 > 0 && registrador == 2){  //Caso o número seja real        
        return numero_real(digits,size,2);
    }

    return -1;
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
    float digito_1, digito_2;
    switch (control){
    case EQUAL:
            digito_1 = this->pegar_numero(this->vet_registro_1,this->contador_registro_1, 1);
            digito_2 = this->pegar_numero(this->vet_registro_2,this->contador_registro_2, 2);

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
            // printf("Result = %f")
            this->number_to_digits(result);
            for(int i = 0; i < this->contador_registro_1;i++){
              this->display->add(this->vet_digit_display[i]);
            }
        break;
    case DECIMAL_SEPARATOR:
        if(this->display)
            this->display->addDecimalSeparator();

        if(this->flagOperador == 0){
            this->pos_decimalSeparator_1 = this->contador_registro_1;
            this->flag_decimalSeparator1++;
        }
        else{
            this->pos_decimalSeparator_2 = this->contador_registro_2;
            this->flag_decimalSeparator2++;
        }
        break;
    default:
        break;
    }
}
void CpuPablo::setDisplay(Display *display) { 
    this->display = display; 
}