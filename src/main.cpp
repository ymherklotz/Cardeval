/*

  description: This is the main cpp file for the cardeval project.

  author: Yann Herklotz <ymherklotz@gmail.com>
  date created: 18-07-2016
  filename: main.cpp

 */

#include <tinyxml2.h>

#include <iostream>
#include <string>

#include "../include/cardeval.hpp"

using namespace std;
using namespace tinyxml2;
using namespace cardeval;

int main(int argc, char** argv) {
    CardEval ce(argc, argv);

    vector<card_struct> minions;
    vector<atk_health> avg_stats;

    ce.set_minions(minions);
    ce.set_avg_stats(avg_stats);

    for(unsigned int i = 0; i < minions.size(); i++) {
        if(minions[i].is_collectible){
            double atk_diff, health_diff;
            
            atk_diff = double(minions[i].attack) - avg_stats[minions[i].cost].atk;
            health_diff = double(minions[i].health) - avg_stats[minions[i].cost].health;

            minions[i].value = health_diff - atk_diff;
        }
    }

    for(card_struct cards : minions) {
        if(cards.is_collectible) {
            cout << cards.card_print_format();
        }
    }

    for(atk_health card_avg : avg_stats) {
        cout << card_avg.prnt_str() << endl;
    }
    
    return 0;
}
