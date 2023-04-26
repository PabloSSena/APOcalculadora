#include"CpuPablo.hpp"
#include <iostream>
#include <cmath>
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
    printf("\nthis->pos_decimalSeparator_1 = %d\n",this->pos_decimalSeparator_1);

    if(this->pos_decimalSeparator_1 > 8 && registrador == 1){ //Caso o número seja inteiro
        printf("Entra aqui?\n");

        return numero_inteiro(digits,size);
    }
    if(this->pos_decimalSeparator_2 > 8 && registrador == 2){ //Caso o número seja inteiro
        printf("Entra aqui?\n");
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


// int CpuPablo::converter_em_decimal(float numero){
//     while (numero > 0){
        
//     }
    
// }

// int CpuPablo::pegar_numero(Digit digit, int size, int num_registrador){
//     float decimals = 0;
//     this->contador_registro_1;
//     if(num_registrador == 1){
//         if(this->pos_decimalSeparator_1 < 0){
//             result = result * 10 + static_cast<float>(digit);
//             this->contador_registro_1++;
//         }
//         else{
//             decimals = decimals * 10 + static_cast<float>(digit);
            

//         }
//     }
// }

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
            printf("digito 1 = %d\n", digito_1);
            printf("digito 2 = %d\n", digito_2);

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
        if(this->display)
            this->display->addDecimalSeparator();

        if(this->flagOperador == 0)
            this->pos_decimalSeparator_1 = this->contador_registro_1;
        else
            this->pos_decimalSeparator_2 = this->contador_registro_2;
        break;
    default:
        break;
    }
}
void CpuPablo::setDisplay(Display *display) { 
    this->display = display; 
}