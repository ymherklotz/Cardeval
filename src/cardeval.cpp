/*

  description: This is the class file for the header file that includes
               all the functions.

  author: Yann Herklotz <ymherklotz@gmail.com>
  date created: 18-07-2016
  filename: cardeval.cpp
  
 */

#include "../include/cardeval.hpp"

using namespace tinyxml2;

CardEval::CardEval() {
    card_doc.LoadFile("resources/CardDefs.xml");
}

CardEval::CardEval(int &argc, char** &argv) {
    // if only one argument is given
    if(argc == 1) {
        // use strncmp to compare parts of the string
        if(std::strncmp(argv[0], "bin/xxx", 4) || std::strncmp(argv[0], "./bin/xxx", 6)) {
            // if program is executed from main program directory
            card_doc.LoadFile("resources/CardDefs.xml");
        } else if(std::strncmp(argv[0], "./xxx", 2)) {
            // when program is executed directly
            card_doc.LoadFile("../resources/CardDefs.xml");
        }
    } else if(argc == 2) {
        // if arguments are given to the program
        card_doc.LoadFile(argv[1]);
    } else {
        // otherwise exit with errorcode
        exit_with_error();
    }
}

CardEval::~CardEval() {
    
}

void CardEval::get_cards() {
    // load root node from the file into memory
    XMLElement* root_el = card_doc.FirstChildElement("CardDefs");

    // loops through the root node, which means it loops through the cards
    for(XMLElement* ent_iterator = root_el->FirstChildElement("Entity"); ent_iterator != NULL;
        ent_iterator = ent_iterator->NextSiblingElement("Entity")) {

        card_struct card_info;

        // iterates through the card information in tags
        for(XMLElement* tag_iterator = ent_iterator->FirstChildElement("Tag");
            tag_iterator != NULL; tag_iterator = tag_iterator->NextSiblingElement("Tag")) {

            card_info = set_card_info(tag_iterator);
        }
    }
}

void CardEval::exit_with_error() {
    // exit the program with an error message
    std::exit(EXIT_FAILURE);
}

void CardEval::add_card_to_vec(card_struct &in_card) {
    // just adds the card to the respective vector
    if(in_card.card_type == 'm') {
        minions.push_back(in_card);
    } else if(in_card.card_type == 's') {
        spells.push_back(in_card);
    } else if(in_card.card_type == 'w') {
        weapons.push_back(in_card);
    } else {
        random.push_back(in_card);
    }
}

char CardEval::get_type(std::string type_str) {
    int type_int = std::stoi(type_str);

    switch(type_int) {
        // when it is a minion
    case 4:
        return 'm';
        // when the card is a spell
    case 5:
        return 's';
        // when the card is a weapon
    case 7:
        return 'w';
        // otherwise return null
    default:
        return '\0';
    }
}

std::string CardEval::get_class(std::string class_str) {
    int class_int = std::stoi(class_str);
    
    switch(class_int) {
    case 2:
        return "druid";
    case 3:
        return "hunter";
    case 4:
        return "mage";
    case 5:
        return "paladin";
    case 6:
        return "priest";
    case 7:
        return "rogue";
    case 8:
        return "shaman";
    case 9:
        return "warlock";
    case 10:
        return "warrior";
    default:
        return "";
    }
}

card_struct CardEval::set_card_info(XMLElement* tag_it) {
    card_struct tmp_card;
    
    // add information to the cardinfo
    if(tag_it->Attribute("name", "CardName")) {
        // if tag is cardname
        tmp_card.card_name = tag_it->FirstChildElement("enUS")->GetText();
    } else if(tag_it->Attribute("name", "Collectible") &&
              tag_it->Attribute("value", "1")) {
        tmp_card.is_collectible = true;

    } else if(tag_it->Attribute("name", "CardType")) {
        tmp_card.card_type = get_type(tag_it->Attribute("value"));

    } else if(tag_it->Attribute("name", "Class")) {
        tmp_card.class_name = get_class(tag_it->Attribute("value"));

    } else if(tag_it->Attribute("name", "Cost")) {
        tmp_card.cost = std::stoi(tag_it->Attribute("value"));

    } else if(tag_it->Attribute("name", "Atk")) {
        tmp_card.attack = std::stoi(tag_it->Attribute("value"));

    } else if(tag_it->Attribute("name", "Health")) {
        tmp_card.health = std::stoi(tag_it->Attribute("value"));

    } else if(tag_it->Attribute("name", "Rarity")) {
        tmp_card.rarity = std::stoi(tag_it->Attribute("value"));

    } else if(tag_it->Attribute("name", "Durability")) {
        tmp_card.durability = std::stoi(tag_it->Attribute("value"));
    } else{
        
    }

    return tmp_card;
}
