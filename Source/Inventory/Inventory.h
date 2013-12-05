/*
 * CS585
 *
 * Team Bammm
 * 	Alvaro Home
 * 	Matt Konstantinou
 * 	Michael Abramo
 *	Matt Witkowski
 *  Bradley Crusco
 * Description:
 * Inventory header file.
 *
 */

#ifndef INVENTORY_H_
#define INVENTORY_H_

#include "../Resources/Constant.h"
#include "Item.h"
#include "../Resources/DynamicArray.h"
using namespace std;
namespace bammm
{
	class Inventory
	{
		private:
			DynamicArray<Item*> _inventory;
			uint _slots;
			uint _usedSlots;
			
			/**
			 getInventoryIndex
			 @Pre-Condition- Reference to an item
			 @Post-Condition- Returns the index of the found item
			 */
			int getInventoryIndex(Item& item);

		public:
			Inventory();
			Inventory(uint slots);
			virtual ~Inventory();
			
			/**
			 addItem
			 @Pre-Condition- A pointer to an item
			 @Post-Condition- Returns if the add was successful
			 */
			bool addItem(Item* item);
			
			/**
			 removeItem
			 @Pre-Condition- A reference to an item
			 @Post-Condition- Returns the removed item if found
			 */
			Item* removeItem(Item& item);
			
			/**
			 contains
			 @Pre-Condition- A reference to an item
			 @Post-Condition- Returns true if the item was found
			 */
			bool contains(Item& item);
			
			/**
			 contains
			 @Pre-Condition- A reference to an item, and an amount
			 @Post-Condition- Returns true if all items are found
			 */
			bool contains(Item& item, uint amount);
			
			/**
			 setSlots
			 @Pre-Condition- A uint for the amount of slots
			 @Post-Condition- Changes the amount of slots
			 */
			void setSlots(uint slots);
			
			/**
			 getSlots
			 @Pre-Condition- None
			 @Post-Condition- Returns the amount of slots
			 */
			uint getSlots();
			
			/**
			 getUsedSlots
			 @Pre-Condition- None
			 @Post-Condition- Returns the amount of used slots
			 */
			uint getUsedSlots();
			
			/**
			 toString
			 @Pre-Condition- None
			 @Post-Condition- Returns the sring representation of the inventory
			 */
			string toString();
	};
}

#endif
