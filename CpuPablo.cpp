#include"CpuPablo.hpp"
#include <iostream>
#include <cmath>

// Declaracoes de funções
void processa_decimal_separator();
void processa_equal(Control control);


void CpuPablo::number_to_digits(float num) {
    Digit digits[8], vetor_organizador[8];
    int counter = 0,digits_counter = 0, counter_vetor_organizador = 0;
    int parte_inteira = (int)num;
    float parte_decimal = num - parte_inteira; // pegando parte decimal
    if (num == 0) {
        this->vet_registro_1[0] = ZERO;
        this->contador_registro_1 = 1;
    }

    if(num < 0){ 
        parte_inteira = parte_inteira * (-1);
    }
    while (parte_inteira > 0 && digits_counter < 7){
        int digito = parte_inteira % 10;
        parte_inteira = parte_inteira / 10;
        digits[digits_counter] = static_cast<Digit>(digito);
        digits_counter++;
    }

    for(int i = digits_counter-1; i >=0 ;i--){
        vetor_organizador[counter_vetor_organizador] = digits[i];
        counter_vetor_organizador++;
    }
    // Dentro desse bloco cuida do decimal
    if(parte_decimal > 0 ){
        this->resultado_decimal_separator = digits_counter;
        this->flag_decimal_result++;

        while (parte_decimal > 0 && digits_counter < 7){
            parte_decimal = parte_decimal * 10; // por exemplo: 0,45 vira 4,5 aí conseguimos pegar o 4
            int digito = (int)parte_decimal;    // cast pra int pra vir só o numero antes da virgula
            digits[digits_counter] = static_cast<Digit>(digito);
            digits_counter++;
            parte_decimal = parte_decimal - digito; // parte decimal nesse momento é 4,5 fazemos -4 para nos sobrar só o 5
        }
        for(int i = 8 - counter_vetor_organizador; i > 0;i--){ //Organizando a parte decimal
            vetor_organizador[i+1] = digits[i+1]; 
            counter_vetor_organizador++;                    
        }
    }
    for(int i = 0; i <= counter_vetor_organizador; i++){
      this->vet_digit_display[counter] = vetor_organizador[i];
      counter++;
    }
    this->contador_registro_1 = digits_counter;
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

float CpuPablo::numero_real(const float* digits,int size, int registrador){
    float result = 0;
    float decimals = 0;

    switch (registrador){
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
        decimals = 0;
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
    if(this->pos_decimalSeparator_1 > 0 && registrador == 1){  //Caso o número seja inteiro       
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
    // aqui tem que ver se o segundo operador está pronto pra ver qual operador será utilizado
    //tipo se eu tenho 1 + 2 e aperto + dnv vou fazer o resultado da conta somado com o segundo registro
    //se eu tiver 1 + 2 - eu preciso abrir o segundo registro pra ele me dizer - qual número
    // 1 + 1 + 1 aparece 2 mas seu eu apertar + dnv acontece nada
    // então precisamos fazer que depois de resolver uma operação o registrador 1 fica com o resultado
    // e o 2 fica meio alugado para receber um novo numero
    if(this->flagOperador > 0){
        processa_equal();
        this->contador_registro_2 = 0;
    }
    this->receiveOperator = op;
    this->flagOperador++;
}

void CpuPablo::receive(Control control) {
    switch (control){ //Fazer um método para lidar com o igual para ficar mais bonito, exemplo processaOperacao
    case EQUAL: // fazer uma maneira de que quando eu aperto o operador mais de uma vez fazer o display tambem, exemplo 1+1 +  tem que mostrar 2
        processa_equal();
        break;

    case DECIMAL_SEPARATOR:
        processa_decimal_separator();
        break;
    default:
        break;
    }
}
void CpuPablo::setDisplay(Display *display) { 
    this->display = display; 
}

void CpuPablo::processa_equal(){
    float digito_1, digito_2;
    digito_1 = this->pegar_numero(this->vet_registro_1,this->contador_registro_1, 1);
    digito_2 = this->pegar_numero(this->vet_registro_2,this->contador_registro_2, 2);

    // if(this->flag_signal_1 == 1)
    //     digito_1 = digito_1 * (-1);

    switch (this->receiveOperator){
        case SUM:
            this->result = digito_1 + digito_2;
            break;
        case SUBTRACTION:
            this->result = digito_1 - digito_2; // -1
            break;
        case DIVISION:
            this->result = digito_1 / digito_2;
            break;
        case MULTIPLICATION:
            this->result = digito_1 * digito_2;
            break;
        default:
            printf("Operador não encontrado\n");
            break;
    }

    this->number_to_digits(this->result);

    printf("\n");
    if(this->result < 0) this->display->setSignal(NEGATIVE);
    
    for(int i = 0; i < this->contador_registro_1;i++){
        if(i == this->resultado_decimal_separator && this->flag_decimal_result > 0){
            this->display->addDecimalSeparator();
        }
        this->display->add(this->vet_digit_display[i]);
    }
    //Tem que implementar uma forma do registrador 1 receber o resultado da conta
    passar_resultado_registrador_1(this->result);

}

void CpuPablo::processa_decimal_separator(){
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
}

void CpuPablo::passar_resultado_registrador_1(float numero){
    int parte_inteira = static_cast<int>(numero);
    float parte_decimal = numero - parte_inteira;
    float vetor_aux[8];
    int counter_aux = 0, contador_registro = 0, counter_vetor_organizado = 0;
    int recebe = parte_inteira;

    if(numero < 0){ 
        parte_inteira = parte_inteira * (-1);
        this->flag_signal_1 = 1;
    }
    
    while(parte_inteira > 0){
        int recebe = parte_inteira % 10;
        parte_inteira = parte_inteira / 10;
        vetor_aux[counter_aux] = recebe;
        counter_aux++;
    } 
    for(int i = counter_aux-1; i >= 0; i-- ){
        this->vet_registro_1[contador_registro] = vetor_aux[i];
        contador_registro++;
        counter_vetor_organizado++;
    }
    this->contador_registro_1 = contador_registro;
        
    if(parte_decimal > 0 ){
        this->resultado_decimal_separator = contador_registro;
        this->flag_decimal_result++;

        while (parte_decimal > 0){
            parte_decimal = parte_decimal * 10; // por exemplo: 0,45 vira 4,5 aí conseguimos pegar o 4
            int digito = (int)parte_decimal;    // cast pra int pra vir só o numero antes da virgula
            vetor_aux[counter_aux] = static_cast<float>(digito);
            counter_aux++;
            parte_decimal = parte_decimal - digito; // parte decimal nesse momento é 4,5 fazemos -4 para nos sobrar só o 5
        }

        for(int i = counter_aux - counter_vetor_organizado; i > 0; i-- ){
            this->vet_registro_1[i+1] = vetor_aux[i+1];
            contador_registro++;
        }
        this->contador_registro_1 = contador_registro;
    }

}