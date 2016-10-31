/*

  description: This class gets hearthstone card information from a xml file
               and tries to calculate trends so that we can get a
               trustworthy formula.

  author: Yann Herklotz <ymherklotz@gmail.com>
  date created: 18-07-2016
  filename: cardeval.hpp

 */

#ifndef CARDEVAL_INCL
#define CARDEVAL_INCL

#define MAX_MANA 10

// necessary standard includes
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>

// test include will be removed later
#include <iostream>

// external libraries
#include <tinyxml2.h>

namespace cardeval {

struct atk_health {
    double atk;
    double health;

    atk_health() {
        atk = 0;
        health = 0;
    }

    std::string prnt_str() {
        std::stringstream ss;
        ss << "(" << atk << ", " << health << ")";
        return ss.str();
    }
};

// structure that stores card information
struct card_struct {
    // booleans to be set to determine card
    bool is_collectible;

    // variables to setup
    char card_type;

    // card properties
    int attack;
    int cost;
    int durability;
    int health;
    int rarity;

    double value;

    // extra card abilities such as charge or battlecry
    std::string abilities;
    std::string card_name;
    std::string class_name;

    card_struct() {
        // initialising the variables
        is_collectible = false;

        // null for chars
        card_type = '\0';

        // value doesnt exist in cards hence is default
        attack = -1;
        cost = -1;
        durability = -1;
        health = -1;
        rarity = -1;

        value = -1;

        // empty strings
        abilities = "";
        card_name = "";
        class_name = "neutral";
    }

    std::string card_print_format() {
        
        std::stringstream ss;
        ss << card_name << " (Rarity: " << rarity << "):\n\tCost: " << cost << ", Attack: " << attack << ", Health: " << health << ", Durability: " << durability << ", Value: " << value << "\n\tClass: " << class_name << "\n\tAbilities: " << abilities << std::endl;
        return ss.str();
    }
};

class CardEval {
public:
    // default constructor that holds initial value
    CardEval();
    // constructor that includes options to include other files
    CardEval(int &argc, char** &argv);
    
    // default deconstructor
    ~CardEval();

    void print_cards(std::string card_str);
    void print_stat_average();
    void set_minions(std::vector<card_struct> &card_info);
    void set_spells(std::vector<card_struct> &card_info);
    void set_weapons(std::vector<card_struct> &card_info);
    void set_avg_stats(std::vector<atk_health> &stat_avg);
protected:
    // gets the cards from the xml file and saves them in memory for easy usability inside the program with all the information in a struct
    void get_cards();
    void get_stat_average();
    // exits the program with an error
    void exit_with_error();
    // adds the card to a vector that it belongs to
    void add_card_to_vec(card_struct &in_card);

    // gets the type of the card and returns the appropriate char
    char get_type(std::string type_str);
    // gets the class of the card and returns the class name
    std::string get_class(std::string class_str);
    // assigns the values to the card struct which can then be added to the vectors
    void set_card_info(tinyxml2::XMLElement* tag_it, card_struct &curr_card);
private:
    // variable that holds the xml document in memory
    tinyxml2::XMLDocument card_doc;

    // vectors that load all the card information into memory
    std::vector<card_struct> minions;
    std::vector<card_struct> spells;
    std::vector<card_struct> weapons;
    std::vector<card_struct> heroes;
    std::vector<card_struct> hero_powers;
    std::vector<card_struct> random;

    // contains all the averages of the card stats
    std::vector<atk_health> card_avg_stats;
}; // Cardeval

class TextAnalysis {
public:
    TextAnalysis();
    ~TextAnalysis();
    
    void get_limited_text(std::string &lim_text, std::string &text_limiter, std::string &text_limiter_close);
protected:
private:
}; // TextAnalysis

} // cardeval

#endif
