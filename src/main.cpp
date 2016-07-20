/*

  description: This is the main cpp file for the cardeval project.

  author: Yann Herklotz <ymherklotz@gmail.com>
  date created: 18-07-2016
  filename: main.cpp

 */

#include <iostream>
#include <string>

#include <tinyxml2.h>

#include "../include/cardeval.hpp"

using namespace std;
using namespace tinyxml2;

int main(int argc, char** argv) {
    CardEval ce(argc, argv);
    ce.get_cards();
    return 0;
}
