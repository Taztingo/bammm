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
 * Item header file.
 *
 */

#ifndef ITEM_H_
#define ITEM_H_

#include <iostream>
#include "../Resources/Constant.h"
//#include "../Interfaces/IAction.h"
//#include "../Actors/Actor.h"
using namespace std;

namespace bammm
{
	class Item
	{
		private:
			string _name;
			//IAction* _action;
			uint _amount;
			DynamicArray<Item> _ingredients;

		public:
			Item();
			Item(string name);
			Item(string name, int amount);
			virtual ~Item();

			/**
			 action
			 Pre-Condition- A pointer to an Actor, and an int amount
			 Post-Condition- Uses the item's action
			 */
			//void action(Actor* target, int amount);

			/**
			 getAmount
			 Pre-Condition- None
			 Post-Condition- Gets the amount of the item
			 */
			uint getAmount();

			/**
			 setAmount
			 Pre-Condition- A uint to set the amount of the item
			 Post-Condition- Sets the amount of the item
			 */
			void setAmount(uint amount);

			/**
			 getName
			 Pre-Condition- None
			 Post-Condition- Gets the name of the item
			 */
			string getName();

			/**
			 setName
			 Pre-Condition- A string for the new name
			 Post-Condition- Sets the name of the item
			 */
			void setName(string name);

			/**
			 operator==
			 Pre-Condition- A reference to an Item
			 Post-Condition- Returns true if two items have same name
			 */
			bool operator==(const Item& item2);

			DynamicArray<Item>& getIngredients();

			void setIngredients(DyanmicArray<Item> ingredients);

			void addIngredient(Item ingredient);


	};
}

#endif
