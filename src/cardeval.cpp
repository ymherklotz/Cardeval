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

void CardEval::getCards(std::vector<cardStruct> &cardDeck) {
    // load root node from the file into memory
    XMLElement* root_el = card_doc.FirstChildElement("CardDefs");

    // loops through the root node, which means it loops through the cards
    for(XMLElement* ent_iterator = root_el->FirstChildElement("Entity"); ent_iterator != NULL;
        ent_iterator = ent_iterator->NextSiblingElement("Entity")) {

        cardStruct card_info;

        // iterates through the card information in tags
        for(XMLElement* tag_iterator = ent_iterator->FirstChildElement("Tag");
            tag_iterator != NULL; tag_iterator = tag_iterator->NextSiblingElement("Tag")) {

            // add information to the cardinfo
            if(tag_iterator->Attribute("name", "CardName")) {
                // if tag is cardname
                card_info.card_name = tag_iterator->FirstChildElement("enUS")->GetText();
                
            } else if(tag_iterator->Attribute("name", "Collectible") &&
                      tag_iterator->Attribute("value", "1")) {
                card_info.is_collectible = true;
                
            } else if(tag_iterator->Attribute("name", "CardType")) {
                get_type(tag_iterator->Attribute("value"));
                
            } else if(tag_iterator->Attribute("name", "Class")) {
                get_class(tag_iterator->Attribute("value"));
            }
        }
    }
}

void CardEval::exit_with_error() {
    std::exit(EXIT_FAILURE);
}

char CardEval::get_type(std::string type_str) {
    int type_int = std::stoi(type_str);

    switch(type_int) {
    case 4:
        return 'm';
    case 5:
        return 's';
    case 7:
        return 'w';
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
