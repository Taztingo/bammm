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
 * Item cpp file.
 *
 */

#include <iostream>
#include "../Resources/Constant.h"
//#include "../Actors/Actor.h"
//#include "../Interfaces/IAction.h"
#include "Item.h"
using namespace std;

namespace bammm
{
	Item::Item()
	{
		_name = "Missingno";
		_description = "L shaped thing";
		_color = "white";
		_amount = 0;
		_stackable = false;
	}

	Item::Item(string name, bool stackable)
	{
		_name = name;
		_color = "white";
		_description = "No description";
		_amount = 1;
		_stackable = stackable;
	}

	Item::Item(string name, string color, bool stackable)
	{
		_name = name;
		_color = color;
		_description = "No description";
		_amount = 1;
		_stackable = stackable;
	}

	Item::Item(string name, int amount, string color, bool stackable)
	{
		_name = name;
		_color = color;
		_amount = amount;
		_description = "No description";
		_stackable = stackable;
	}
<<<<<<< HEAD

	Item::Item(string name, int amount)
=======
	
	Item::Item(string name, int amount, bool stackable)
>>>>>>> refs/heads/master
	{
		_name = name;
		_amount = amount;
		_stackable = stackable;
	}

	Item::~Item()
	{
	}

	/*void Item::action(Actor* target, int amount)
	 {
	 _action->action(target, amount);
	 }*/

	uint Item::getAmount()
	{
		return _amount;
	}

	void Item::setAmount(uint amount)
	{
		_amount = amount;
	}

	string Item::getName()
	{
		return _name;
	}

	void Item::setName(string name)
	{
		_name = name;
	}

	string Item::getColor()
	{
		return _color;
	}

	void Item::setColor(string color)
	{
		_color = color;
	}

	string Item::getDescription()
	{
		return _description;
	}

	void Item::setDescription(string description)
	{
		_description = description;
	}

	bool Item::operator==(const Item& item)
	{
		if (_name == item._name)
		{
			return true;
		}

		return false;
	}

<<<<<<< HEAD
	DynamicArray<Item> Item::getIngredients()
	{
		return _ingredients;
	}

	void Item::setIngredients(DynamicArray<Item> ingredients)
	{
		_ingredients = ingredients;
	}

	void Item::addIngredient(Item& ingredient)
	{
		_ingredients.add(ingredient);
	}

=======
	bool Item::getStackable()
	{
		return _stackable;
	}
	
	void Item::setStackable(bool stackable)
	{
		_stackable = stackable;
	}

	Item* Item::getStackableCopy()
	{
		Item* newItem = new Item(_name, 1, _color, _stackable);
		newItem->setDescription(_description);
		return newItem;
	}
>>>>>>> refs/heads/master
}

