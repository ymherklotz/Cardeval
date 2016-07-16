/*

  description:

  author: Yann Herklotz <ymherklotz@gmail.com>
  date created: DD-MM-YYYY

 */

#include <iostream>

int main(int argc, char** argv) {
    std::cout << "executing " << argv[0] << std::endl;
    std::cout << "arguments given: " << argc-1 << std::endl;
    return 0;
}
