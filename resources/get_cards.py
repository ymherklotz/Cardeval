#!/usr/bin/python2
import xml.etree.ElementTree as et

def main():
	# opens the xml file
	tree = et.parse("CardDefs.xml")
	root = tree.getroot()

	# creates the needed files

	# contains the cards that can be added to your deck
	CollectableFile = open('CollectableCards.txt', 'w')

	# contains all the cards in the game with extra information
	hsCardInfo = open('hsCardInfo.txt', 'w')

	# contains all the cards but without information
	hsCard = open('hsCard.txt', 'w')

	# contains the name of the heroes and hero powers
	hsHero = open('hsHero.txt', 'w')

	# initialises the files
	hsCardInfo.write('Name,Attack,Health,Durability,Cost,Rarity,Type\n')

	
	# This code gets all the collection

	# The for loop goes through the different levels of the xml file
	for child1 in root: # Goes through Card defs, child will be Entities

		# sets these bools when the specific value is set
		atk_added = False
		collectable = False
		cs_added = False
		ct_added = False
		hp_added = False
		name = False
		rar_added = False
		wrote = False

		# initial strings that will contain information
		card_type = ''
		cardname = ''

		# contains all the information about a card which is then zipped into a dictionary
		## the card list contains the information of the cards
		card_list = []
		## the order contains the order in which the card information is stored in the card_list list
		order = []
		
		for child2 in child1: # Goes through Entities, child will be Tag
			if child2.attrib.get('name') == 'CardName':
				# sets the name
				name = True
				
				for child3 in child2: # Goes through Tag, child will be language
					if(child3.tag == 'enUS'):
						# sets the string
						cardname = child3.text
						#### print child3.text # not an error, only python 2.7 specific
						
			# if the card is collectable set the bool
			if child2.attrib.get('name') == 'Collectable' and child2.attrib.get('value') == '1':
				collectable = True; # is true if card is collectable

			# set the cardtype of the current card being analysed
			if child2.attrib.get('name') == 'CardType' and not ct_added:
				card_list.append(int(child2.attrib.get('value')))
				order.append('CardType')
				ct_added = True

			# set the attack of the minion
			if child2.attrib.get('name') == 'Atk' and not atk_added:
				card_list.append(int(child2.attrib.get('value')))
				order.append('Attack')
				atk_added = True

			# set the health of the minion
			if child2.attrib.get('name') == 'Health' and not hp_added:
				card_list.append(int(child2.attrib.get('value')))
				order.append('Health')
				hp_added = True

			# set the cost of the card
			if child2.attrib.get('name') == 'Cost' and not cs_added:
				card_list.append(int(child2.attrib.get('value')))
				order.append('Cost')
				cs_added = True

			# set the rarity of the card
			if child2.attrib.get('name') == 'Rarity' and not rar_added:
				card_list.append(int(child2.attrib.get('value')))
				order.append('Rarity')
				rar_added = True
				
			# if the name is set and the card is collectable and it hasn't written to the file yet
			if name and collectable and not wrote:
				CollectableFile.write(cardname + '\n')
				wrote = True # so that it doesnt rewrite the same card

		# zips the two lists together into a dictionary for easy access
		card_info = dict(zip(order, card_list))

		# if the "card" is a hero
		if card_info.get('CardType') == 3: # hero
			hsHero.write(cardname)
			
		# if the card is a minion, add attack, health, cost, and rarity
		elif card_info.get('CardType') == 4 and card_info.get('Rarity') != None and card_info.get('Attack') != None and card_info.get('Health') != None and card_info.get('Cost') != None: # minion
			hsCardInfo.write(cardname + ',' + str(card_info.get('Attack')) + ',' + str(card_info.get('Health')) + ',' + str(card_info.get('Cost')) + ',' + str(card_info.get('Rarity')) + ',Minion\n')
			hsCard.write(cardname)
			
		# if the card is a spell add the rarity and cost
		elif card_info.get('CardType') == 5 and card_info.get('Rarity') != None and card_info.get('Cost') != None: # Spell
			hsCardInfo.write(cardname + ',' + str(card_info.get('Cost')) + ',' + str(card_info.get('Rarity')) + ',Spell\n')
			hsCard.write(cardname)
			
		# if card is a weapon add attack cost and rarity to card
		elif card_info.get('CardType') == 7 and card_info.get('Rarity') != None and card_info.get('Attack') != None and card_info.get('Cost') != None: # Weapon
			hsCardInfo.write(cardname + ',' + str(card_info.get('Attack')) + ',' + str(card_info.get('Cost')) + ',' + str(card_info.get('Rarity')) + ',Weapon\n')
			hsCard.write(cardname)
		# elif card_info.get('CardType') == 10: # Hero Power
			# hsCardInfo.write(cardname + ',HeroPower\n')

	# close all the files
	CollectableFile.close()
	hsCardInfo.close()
	hsCard.close()
	hsHero.close()

if __name__ == '__main__':
	main()
