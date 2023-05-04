#include"calculator.hpp"
#include"calculatorPablo.hpp"
#include"console.hpp"
class DisplayPablo: public Display{
  // CpuPablo cpu;
  Console console;
  
  public:
    void add(Digit digit);
    void setSignal(Signal);
    void addDecimalSeparator();
    void clear();
    void refresh();

};