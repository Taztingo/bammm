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
 * JSONParser cpp file.
 */

#include "JSONParser.h"
#include "../Resources/DynamicArray.h"
#include "JSON.h"
#include "JSONArray.h"
#include <stdlib.h>

using namespace std;

namespace bammm
{

	JSONParser::JSONParser()
	{

	}

	void JSONParser::addRoot(JSON & newNode)
	{
		cout << "adding root \n";
		_rootMap.add(newNode.getName(), &newNode);
		cout << "root added \n";
	}

	void JSONParser::addChild(JSON & rootNode, JSON & newNode)
	{
		rootNode.addChild(newNode);
	}

	HashMap<JSON*>* JSONParser::getMap()
	{
		return &_rootMap;
	}

	JSON* JSONParser::getRootNode(string key)
	{
		return _rootMap.getValue(key);
	}

	bool JSONParser::parseFile(string fileName)
	{

		ifstream input;
		char current;
		bool isKey = false;
		bool isValue = false;
		bool isDouble = false;
		JSON *currentNode = NULL;
		JSON *parentNode = NULL;
		string name = "";
		string value = "";

		input.open(fileName.c_str());

		if (!input.is_open())
		{
			cout << "Failed to open file: " << fileName << " does not exist."
					<< endl;
			return false;
		}

		cout << "File found and opened. Beginning parse. \n";
		cout.flush();

		while (!input.eof())
		{

			current = (char) input.get();

			switch (current)
			{

				case '{':
					cout << "Parsing { \n";
					cout.flush();

					if (currentNode == NULL)
					{
						currentNode = new JSON("root");
						addRoot(*currentNode);
						cout << "addRoot function complete \n";
						cout.flush();
					}

					isValue = false;
					isKey = true;

					break;

				case '}':
					cout << "Parsing } \n";
					cout.flush();

					if (parentNode == NULL)
					{
						/* This will be the final output of the parser. This should not output before completion. */
						cout << "Completed parsing " << fileName << ". \n";
						input.close();

						currentNode = NULL;
					}
					else
					{
						currentNode = currentNode->getParent();
						parentNode = parentNode->getParent();

						isKey = true;
					}

					break;

				case '[':
					cout << "Parsing [ \n";
					cout.flush();

					if (currentNode == NULL)
					{
						currentNode = new JSONArray(name);
						addRoot(*currentNode);
					}
					else
					{
						parentNode = currentNode;
						currentNode = new JSONArray(name);
						parentNode->addChild(*currentNode);
					}
					break;

				case ']':
					cout << "Parsing ] \n";
					cout.flush();

					currentNode = currentNode->getParent();
					parentNode = parentNode->getParent();

					isKey = true;

					break;

				case '"':
					cout << "Parsing \" \n";
					cout.flush();

					/*if (currentNode == NULL)
					 {
					 cout << "Error: JSON Object not created";
					 return false;
					 }*/

					/* Parse name within quotations
					 * The Object with the name will be created after we find JSON type
					 * JSON type will be determined after parsing a colon
					 */
					current = (char) input.get();
					name = "";
					value = "";
					while (!input.eof() && current != '"')
					{
						if (isValue == false && isKey == true)
						{
							name += current;
						}
						else if (isValue == true && isKey == false)
						{
							value += current;
						}
						current = (char) input.get();
					}

					cout << "Name : " << name << "\nValue: " << value << endl;

					break;

				case ':':
					cout << "Parsing : \n";
					cout.flush();

					isKey = false;
					isValue = true;

					value = "";

					cout << "WHAT'S THE COUNT?!?!?! ---- " << current << endl;

					/* check  what comes after colon so we may determine type */
					current = (char) input.peek();
					while (!input.eof() && current == ' ')
					{
						current = (char) input.get();
					}
					cout << "WHAT'S THE COUNT 2?!?!?! ---- " << current << endl;

					/* Now that we know the value, we may confirm the type of the JSON Node and create it. */

					parentNode = currentNode;

					cout << name << endl;

					if (current == '{')
					{
						currentNode = new JSON(name);

						isKey = true;
						isValue = false;
						cout << "New JSON Object found and created \n";
						cout.flush();
					}
					else if (current == '[')
					{
						currentNode = new JSONArray(name);

						isKey = true;
						isValue = false;
						cout << "New JSON Array found and created \n";
						cout.flush();
					}
					else if (current == '"')
					{

						current = (char) input.get();
						current = (char) input.get();
						cout << "the goddamn character is  ------  " << current << endl;
						while (!input.eof() && current != '"')
						{
							value += current;
							current = (char) input.get();
						}

						cout << "the goddamn value is  ------  " << value << endl;
						currentNode = new JSONPrimitive(name, value,
								JSON_STRING);

						cout << "New JSON_STRING found and created \n";
						cout.flush();
					}
					else if (current == 'f' || current == 't')
					{

						while (!input.eof() && current != ' ')
						{
							value += current;
							current = (char) input.get();
						}

						if (value == "false")
						{
							currentNode = new JSONPrimitive(name, false,
									JSON_BOOL);
							cout << "New JSON_BOOL false found and created \n";
							cout.flush();
						}
						else if (value == "true")
						{
							currentNode = new JSONPrimitive(name, true,
									JSON_BOOL);
							cout << "New JSON_BOOL true found and created \n";
							cout.flush();
						}
						else
						{
							cout << "Error parsing string or bool value \n";
							cout.flush();
							return false;
						}
					}
					else if (isdigit(current))
					{

						while (!input.eof() && current != ' ')
						{
							value += current;
							current = (char) input.get();
						}

						/* Determine whether value has a decimal. If so, make DOUBLE. Else INT */

						for (unsigned int i; i < value.size(); i++)
						{
							if (value[i] == '.')
							{
								isDouble = true;
								break;
							}
							isDouble = false;
						}

						if (isDouble == false)
						{
							currentNode = new JSONPrimitive(name,
									atoi(value.c_str()), JSON_INT);
							cout << "New JSON_INT found and created \n";
							cout.flush();
						}
						else
						{
							currentNode = new JSONPrimitive(name,
									atof(value.c_str()), JSON_DOUBLE);
							cout << "New JSON_DOUBLE found and created \n";
							cout.flush();
						}
					}
					else
					{
						cout
								<< "Error parsing value. Invalid character found. \n";
						return false;
					}

					cout << "setting parent" << endl;
					currentNode->setParent(*parentNode);
					cout << "parent set" << endl;

					if (parentNode == NULL)
					{
						addRoot(*currentNode);
					}
					else
					{
						parentNode->addChild(*currentNode);
					}

					cout << "Added object to map \n";
					cout.flush();

					cout << "Name: " << currentNode->getName() << " Type: " << currentNode->getType() << " Value: " << value << endl;

					break;

				case ',':
					cout << "Parsing , \n" << endl;
					cout.flush();

					/* reset node to parent so next key/value may be added as a child to parent */
					currentNode = currentNode->getParent();
					parentNode = parentNode->getParent();

					isKey = true;

					break;

			}
		}

		cout << "End of file reached \n";
		cout.flush();

		currentNode = NULL;
		parentNode = NULL;
		delete currentNode;
		delete parentNode;

		return true;
	}
}
