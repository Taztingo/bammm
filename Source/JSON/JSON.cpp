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
 * JSON cpp file.
 *
 */

#include <sstream>
#include <iostream>
#include "JSON.h"

using namespace std;

namespace bammm
{
	JSON::JSON()
	{
		_name = "empty";
		_type = JSON_OBJECT;
		_parent = NULL;
	}

	JSON::JSON(string newName)
	{
		_name = newName;
		_type = JSON_OBJECT;
		_parent = NULL;
	}

	JSON::~JSON()
	{
		cout << "Deleting JSON \n";
	}

	string JSON::getName()
	{
		return _name;
	}

	JSON_TYPE JSON::getType()
	{
		return _type;
	}

	JSON * JSON::getParent()
	{
		if (_parent == NULL)
		{
			cout << "Parent is null\n";
			cout.flush();
		}
		return _parent;
	}

	void JSON::setName(string newName)
	{
		_name = newName;
	}

	void JSON::setType(JSON_TYPE newType)
	{
		_type = newType;
	}

	void JSON::setParent(JSON & newParent)
	{
		if (&newParent == NULL)
		{
			cout << "Error: Attempting to add NULL as a parent \n";
			cout.flush();
			return;
		}
		_parent = &newParent;
	}

	void JSON::addChild(JSON & newNode)
	{
		if (&newNode == NULL)
		{
			cout << "Error: Attempting to add NULL as a child \n";
			cout.flush();
			return;
		}
		cout << "Adding Child \n";
		_children.add(newNode.getName(), &newNode);
	}
}
