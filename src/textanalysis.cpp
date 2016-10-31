/*

  description: This class gets text from in between multiple patterns.

  author: Yann Herklotz <ymherklotz@gmail.com>
  date created: 10-08-2016
  filename: cardeval.hpp

 */

#include "../include/cardeval.hpp"

using namespace cardeval;
using namespace std;

TextAnalysis::TextAnalysis() {
    
}

TextAnalysis::~TextAnalysis() {
    
}

void TextAnalysis::get_limited_text(string &lim_text, string &text_limiter_open, string &text_limiter_close) {   
    const unsigned int OPEN_LEN = text_limiter_open.length();
    const unsigned int CLOSE_LEN = text_limiter_close.length();

    bool found_start = true;
    bool found_end = true;
    
    for(unsigned int text_i = 0; text_i < lim_text.length(); ++text_i) {
        for(unsigned int open_i = 0; open_i < OPEN_LEN; ++open_i) {
            if(lim_text[text_i + open_i] != text_limiter_open[open_i]) {
                found_start = false;
            }
        }
    }
}
