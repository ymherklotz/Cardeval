/*

  description: This is the main cpp file for the cardeval project.

  author: Yann Herklotz <ymherklotz@gmail.com>
  date created: 18-07-2016
  filename: main.cpp

 */

#include <iostream>
#include <string>

#include <tinyxml2.h>

using namespace std;
using namespace tinyxml2;

int main(int argc, char** argv) {
    cout << "executing " << argv[0] << endl;
    cout << "arguments given: " << argc-1 << endl;

    XMLDocument doc;
    doc.LoadFile("resources/CardDefs.xml");

    XMLElement* entityElement = doc.FirstChildElement("CardDefs");
    for(XMLElement* elIterator = entityElement->FirstChildElement("Entity"); elIterator != NULL; elIterator = elIterator->NextSiblingElement("Entity")) {
        bool setCardName = false;
        bool setCollectible = false;
        bool setMinion = false;
        bool written = false;
        string cardName = "";
        for(XMLElement* tagIterator = elIterator->FirstChildElement("Tag"); tagIterator != NULL; tagIterator = tagIterator->NextSiblingElement("Tag")) {
            if(tagIterator->Attribute("name", "CardName")) {
                setCardName = true;
                cardName = tagIterator->FirstChildElement("enUS")->GetText();
            } else if(tagIterator->Attribute("name", "Collectible") && tagIterator->Attribute("value", "1")) {
                setCollectible = true;
            } else if(tagIterator->Attribute("name", "CardType") && tagIterator->Attribute("value", "10")) {
                setMinion = true;
            }

            if(setCardName && setCollectible && setMinion && !written) {
                cout << cardName << endl;
                written = true;
            } if(tagIterator == nullptr) {
                
            }
        }
    }

    return 0;
}
