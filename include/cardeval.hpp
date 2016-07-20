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

// external libraries
#include <tinyxml2.h>

// structure that stores card information
struct cardStruct {
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

    cardStruct() {
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
    void getCards(std::vector<cardStruct> &cardDeck);
protected:
    // exits the program with an error
    void exit_with_error();
    char get_type(std::string type_str);
    std::string get_class(std::string class_str);
private:
    tinyxml2::XMLDocument card_doc;

    // vectors that load all the card information into memory
    std::vector<cardStruct> minions;
    std::vector<cardStruct> spells;
    std::vector<cardStruct> weapons;
    std::vector<cardStruct> heroes;
    std::vector<cardStruct> hero_powers;
};

#endif
