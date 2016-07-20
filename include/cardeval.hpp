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

        // empty strings
        abilities = "";
        card_name = "";
        class_name = "";
    }

    std::string card_print_format() {
        std::stringstream ss;
        ss << card_name << " (Rarity: " << rarity << "):\n\tCost: " << cost << ", Attack: " << attack << ", Health: " << health << ", Durability: " << durability << "\n\tClass: " << class_name << "\n\tAbilities: " << abilities << std::endl;
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

    // gets the cards from the xml file and saves them in memory for easy usability inside the program with all the information in a struct
    void get_cards();
protected:
    // exits the program with an error
    void exit_with_error();
    // adds the card to a vector that it belongs to
    void add_card_to_vec(card_struct &in_card);

    // gets the type of the card and returns the appropriate char
    char get_type(std::string type_str);
    // gets the class of the card and returns the class name
    std::string get_class(std::string class_str);
    // assigns the values to the card struct which can then be added to the vectors
    card_struct set_card_info(tinyxml2::XMLElement* tag_it);
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
};

#endif
