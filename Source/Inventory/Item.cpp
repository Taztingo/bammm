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
		_amount = 0;
	}

	Item::Item(string name)
	{
		_name = name;
		_amount = 1;
	}

	Item::Item(string name, int amount)
	{
		_name = name;
		_amount = amount;
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

	bool Item::operator==(const Item& item)
	{
		if (_name == item._name)
		{
			return true;
		}

		return false;
	}

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

}

