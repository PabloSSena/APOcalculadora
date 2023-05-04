#include <iostream>

//#include "herança/lista.hpp"
#include "calculatorTest.hpp"
#include"console.hpp"
// #include "calculator/console.hpp"

int main() {
  // srand(time(NULL)); // Inicializa a semente aleatória baseada no tempo

  Console::init(0, 0);

  for (int i = 0; i < 256; i++) {
    Console::setColor(BG_Black);
    Console::setCursor(rand() % 40,
                       rand() % 80); // Posicional aleatoriamente o cursor entre
                                     // as coordenadas [0,0] x [40,80]
                                     //    std::cout << "▶■■■◀";
    std::cout << "▶😀◀";
   }
  // std::cout << "▶😀◀";
  // Console::clearScreen();
  mainTest();
}
