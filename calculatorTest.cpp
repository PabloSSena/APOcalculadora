#include "calculatorTest.hpp"
#include <functional>
#include <iostream>

/**
  123 + 456 = = = = 1947
*/
void test1(Calculator *calculator) {
  calculator->getKeyboard()->getKey(ONE)->press();
  calculator->getKeyboard()->getKey(TWO)->press();
  calculator->getKeyboard()->getKey(THREE)->press();
  calculator->getKeyboard()->getKey(SUM)->press();
  calculator->getKeyboard()->getKey(FOUR)->press();
  calculator->getKeyboard()->getKey(FIVE)->press();
  calculator->getKeyboard()->getKey(SIX)->press();
  calculator->getKeyboard()->getKey(EQUAL)->press();
  // calculator->getKeyboard()->getKey(EQUAL)->press();
  // calculator->getKeyboard()->getKey(EQUAL)->press();
  // calculator->getKeyboard()->getKey(EQUAL)->press();
}

// /**
//   .1 * .1 = 0.01
// */
// void test2(Calculator *calculator) {
//   calculator->getKeyboard()->getKey(DECIMAL_SEPARATOR)->press();
//   calculator->getKeyboard()->getKey(ONE)->press();
//   calculator->getKeyboard()->getKey(SUM)->press();
//   calculator->getKeyboard()->getKey(DECIMAL_SEPARATOR)->press();
//   calculator->getKeyboard()->getKey(ONE)->press();
//   calculator->getKeyboard()->getKey(EQUAL)->press();
// }
// /**
//   .1 * .1 = 0.01
// */
// void test3(Calculator *calculator) {
//   calculator->getKeyboard()->getKey(DECIMAL_SEPARATOR)->press();
//   calculator->getKeyboard()->getKey(ONE)->press();
//   calculator->getKeyboard()->getKey(SUM)->press();
//   calculator->getKeyboard()->getKey(DECIMAL_SEPARATOR)->press();
//   calculator->getKeyboard()->getKey(ONE)->press();
//   calculator->getKeyboard()->getKey(EQUAL)->press();
// }
// /**
//   .1 * .1 = 0.01
// */
// void test4(Calculator *calculator) {
//   calculator->getKeyboard()->getKey(DECIMAL_SEPARATOR)->press();
//   calculator->getKeyboard()->getKey(ONE)->press();
//   calculator->getKeyboard()->getKey(SUM)->press();
//   calculator->getKeyboard()->getKey(DECIMAL_SEPARATOR)->press();
//   calculator->getKeyboard()->getKey(ONE)->press();
//   calculator->getKeyboard()->getKey(EQUAL)->press();
// }

/* Inclua suas implementações aqui */
#include "calculatorPablo.hpp"
Calculator *buildCalculator() {
  /* Build da calculadora */
  Calculator *calculator = new CalculatorPablo();
  Display *display = new DisplayPablo();
  Cpu *cpu = new CpuPablo();
  Keyboard *keyboard = new KeyboardPablo();

  /* ... Criar todas as teclas */
  KeyDigit *keyZero = new KeyDigitPablo("0", ZERO);
  KeyDigit *keyOne = new KeyDigitPablo("1", ONE);
  KeyDigit *keyTwo = new KeyDigitPablo("2", TWO);
  KeyDigit *keyThree = new KeyDigitPablo("3", THREE);
  KeyDigit *keyFour = new KeyDigitPablo("4", FOUR);
  KeyDigit *keyFive = new KeyDigitPablo("5", FIVE);
  KeyDigit *keySix = new KeyDigitPablo("6", SIX);
  KeyDigit *keySeven = new KeyDigitPablo("7", SEVEN);
  KeyDigit *keyEight = new KeyDigitPablo("8", EIGHT);
  KeyDigit *keyNine = new KeyDigitPablo("9", NINE);

  KeyOperator *keySum = new KeyOperatorPablo("+", SUM);
  KeyOperator *keySubtraction = new KeyOperatorPablo("-", SUBTRACTION);
  KeyOperator *keyMultiplication = new KeyOperatorPablo("*", MULTIPLICATION);
  KeyOperator *keyDivision = new KeyOperatorPablo("/", DIVISION);

  KeyControl *keyClearError = new KeyControlPablo("CE", CLEAR_ERROR);
  KeyControl *keyEqual = new KeyControlPablo("=", EQUAL);  

  /* ... Inserir todas as teclas no teclado  */
  keyboard->add(keyZero);
  keyboard->add(keyOne);
  keyboard->add(keyTwo);
  keyboard->add(keyThree);
  keyboard->add(keyFour);
  keyboard->add(keyFive);
  keyboard->add(keySix);
  keyboard->add(keySeven);
  keyboard->add(keyEight);
  keyboard->add(keyNine);

  keyboard->add(keySum);
  keyboard->add(keySubtraction);
  keyboard->add(keyMultiplication);
  keyboard->add(keyDivision);

  keyboard->add(keyClearError);
  keyboard->add(keyEqual);

  keyboard->setCpu(cpu);

  cpu->setDisplay(display);
  
  /* Conectando as partes da calculadora */
  calculator->setDisplay(display);
  calculator->setCpu(cpu);
  calculator->setKeyboard(keyboard);

  return calculator;
}

void mainTest() {
  try{
    
  std::cout << "Construindo a calculadora..." << std::endl;
  Calculator *calculator = buildCalculator();
  std::cout << "Iniciando teste1..." << std::endl;
  calculator->getKeyboard()->getKey(CLEAR_ERROR)->press();
  test1(calculator);
  // std::cout << "Iniciando teste2..." << std::endl;
  // calculator->getKeyboard()->getKey(CLEAR_ERROR)->press();
  // test2(calculator);
  // std::cout << "Iniciando teste3..." << std::endl;
  // calculator->getKeyboard()->getKey(CLEAR_ERROR)->press();
  // test3(calculator);
  // std::cout << "Iniciando teste4..." << std::endl;
  // calculator->getKeyboard()->getKey(CLEAR_ERROR)->press();
  // test4(calculator);
  // try {
  //   for(std::function<void(Calculator*)> test: calculatorTests){
  //     calculator->getKeyboard()->getKey(CLEAR_ERROR)->press();
  //     test(calculator);
  //   }
  // } catch (CalculatorError &e) {
  //   std::cout << "Algum erro aconteceu: " << e.getMessage();
  // }
  delete calculator;
  }catch(CalculatorError* error){
      std::cout << "Tests failed: " <<  error->getMessage();
  }

}