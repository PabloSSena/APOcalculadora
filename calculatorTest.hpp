#pragma once

#include <iostream>
#include <functional>

#include "calculator.hpp"
#include"CpuPablo.hpp"
#include"displayPablo.hpp"

void test1(Calculator*);
void test2(Calculator*);
void test3(Calculator*);
void test4(Calculator*);
// std::function<void(Calculator*)> calculatorTests[] = {&test1, &test2, &test3, &test4}; 

void mainTest();
