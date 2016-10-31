/*

  description: This is the class file for the header file that includes
               all the functions.

  author: Yann Herklotz <ymherklotz@gmail.com>
  date created: 18-07-2016
  filename: cardeval.cpp
  
 */

#include "../include/cardeval.hpp"

using namespace tinyxml2;
using namespace std;
using namespace cardeval;

/*

  Constructor

 */

CardEval::CardEval() {
    card_doc.LoadFile("resources/CardDefs.xml");
}

CardEval::CardEval(int &argc, char** &argv) {
    // if only one argument is given
    if(argc == 1) {
        // use strncmp to compare parts of the string
        if(strncmp(argv[0], "bin/xxx", 4) || strncmp(argv[0], "./bin/xxx", 6)) {
            // if program is executed from main program directory
            card_doc.LoadFile("resources/CardDefs.xml");
        } else if(strncmp(argv[0], "./xxx", 2)) {
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

    get_cards();
    get_stat_average();
}

CardEval::~CardEval() {
    
}

/*

  Public

 */

void CardEval::print_cards(string card_str) {
    if(card_str == "minions") {
        for(card_struct curr_card : minions) {
            cout << curr_card.card_print_format();
        }
    } else if(card_str == "spells") {
        for(card_struct curr_card : spells) {
            cout << curr_card.card_print_format();
        }
    } else if(card_str == "weapons") {
        for(card_struct curr_card : weapons) {
            cout << curr_card.card_print_format();
        }
    } else {
        cout << "not available" << endl;
    }
}

void CardEval::print_stat_average() {
    for(atk_health card_avg : card_avg_stats) {
        cout << card_avg.prnt_str() << endl;
    }
}

void CardEval::set_minions(vector<card_struct> &card_info) {
    for(card_struct cards : minions) {
        card_info.push_back(cards);
    }
}

void CardEval::set_spells(vector<card_struct> &card_info) {
    for(card_struct cards : spells) {
        card_info.push_back(cards);
    }
}

void CardEval::set_weapons(vector<card_struct> &card_info) {
    for(card_struct cards : weapons) {
        card_info.push_back(cards);
    }
}

void CardEval::set_avg_stats(vector<atk_health> &stat_avg) {
    for(atk_health stats : card_avg_stats) {
        stat_avg.push_back(stats);
    }
}

/*

  Protected

 */

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

            set_card_info(tag_iterator, card_info);
        }

        add_card_to_vec(card_info);
    }

    // makes the vectors smaller and fit to memory
    minions.shrink_to_fit();
    spells.shrink_to_fit();
    weapons.shrink_to_fit();
}

void CardEval::get_stat_average() {
    const int atk_health_size = MAX_MANA+1;
    atk_health atk_health_count[atk_health_size];

    int card_total[atk_health_size];
    for(int i = 0; i < atk_health_size; i++) {
        card_total[i] = 0;
    }

    for(card_struct card_info : minions) {
        if(card_info.cost >= 0 && card_info.cost < atk_health_size && card_info.is_collectible) {
            
            atk_health_count[card_info.cost].atk += double(card_info.attack);
            atk_health_count[card_info.cost].health += double(card_info.health);

            card_total[card_info.cost]++;
        }
    }

    for(int i = 0; i < atk_health_size; i++) {
        atk_health tmp_ah;

        tmp_ah.atk = atk_health_count[i].atk / double(card_total[i]);
        tmp_ah.health = atk_health_count[i].health / double(card_total[i]);

        card_avg_stats.push_back(tmp_ah);
    }
}

void CardEval::exit_with_error() {
    // exit the program with an error message
    exit(EXIT_FAILURE);
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

char CardEval::get_type(string type_str) {
    int type_int = stoi(type_str);

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

string CardEval::get_class(string class_str) {
    int class_int = stoi(class_str);
    
    // using switch to return the string of the cardtype
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
        return "\0";
    }
}

void CardEval::set_card_info(XMLElement* tag_it, card_struct &curr_card) {
    // add information to the cardinfo
    if(tag_it->Attribute("name", "CardName")) {
        // if tag is cardname
        curr_card.card_name = tag_it->FirstChildElement("enUS")->GetText();
    } else if(tag_it->Attribute("name", "Collectible") &&
              tag_it->Attribute("value", "1")) {
        curr_card.is_collectible = true;

    } else if(tag_it->Attribute("name", "CardType")) {
        curr_card.card_type = get_type(tag_it->Attribute("value"));

    } else if(tag_it->Attribute("name", "Class")) {
        curr_card.class_name = get_class(tag_it->Attribute("value"));

    } else if(tag_it->Attribute("name", "Cost")) {
        curr_card.cost = stoi(tag_it->Attribute("value"));

    } else if(tag_it->Attribute("name", "Atk")) {
        curr_card.attack = stoi(tag_it->Attribute("value"));

    } else if(tag_it->Attribute("name", "Health")) {
        curr_card.health = stoi(tag_it->Attribute("value"));

    } else if(tag_it->Attribute("name", "Rarity")) {
        curr_card.rarity = stoi(tag_it->Attribute("value"));

    } else if(tag_it->Attribute("name", "Durability")) {
        curr_card.durability = stoi(tag_it->Attribute("value"));
    } else{
        
        // do nothing
    }
}
