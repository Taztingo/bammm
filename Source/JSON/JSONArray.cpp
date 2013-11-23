/*
 * JSONArray.h
 *
 *  Created on: Nov 19, 2013
 *      Author: michael
 *
 *      DOCUMENTATION
 *
 *      Inherits from JSON
 *      Represents an Array in JSON
 *      May hold any JSON Object including JSONPrimitive and JSONArray
 *      Stores JSON Objects in a DynamicArray
 *
 */

#include <iostream>
#include "JSONArray.h"

using namespace bammm;

namespace bammm
{

	JSONArray::JSONArray()
	{
		_name = "empty";
		_type = JSON_ARRAY;
		_parent = NULL;
	}

	JSONArray::JSONArray(string name)
	{
		_name = name;
		_type = JSON_ARRAY;
		_parent = NULL;
	}

	JSONArray::JSONArray(string name, JSON *parent)
	{
		_name = name;
		_type = JSON_ARRAY;
		_parent = parent;
	}

	JSONArray::~JSONArray()
	{
		cout << "Deleting JSON Array \n";
	}

	void JSONArray::addChild(JSON & newNode)
	{
		_children.add(newNode);
	}

	JSON JSONArray::operator[](const unsigned int & rhs)
	{
		if (_children[rhs].getType() == JSON_NULL)
		{
			cout
					<< "Error: JSONPrimitive Object not initialized to a value or incorrect type :: JSON_NULL \n";
			return *this;
		}

		return _children[rhs];
	}

}
