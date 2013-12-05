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
 * Factory cpp file.
 *
 */

#include "Factory.h"

namespace bammm
{
	Factory::Factory(SceneManager* manager)
	{
		_scene = manager;
	}

	void Factory::setup()
	{
		//Parsing weapon data in//
		JSONParser* weaponParser = new JSONParser();
		string weaponFilename = "JSON/weapons.json";
		weaponParser->parseFile(weaponFilename);

		JSON* weaponRoot = weaponParser->getRootNode("root");
		HashMap<JSON*>* weaponRootChildren = weaponRoot->getAllChildren();

		//Parse the melee weapons//
		JSON* meleeWeapons = weaponRootChildren->getValue("meleeWeapons");
		this->parseMeleeWeaponToWeaponData(meleeWeapons, &_meleeWeaponData);

		//Parse the ranged weapons//
		JSON* rangedWeapons = weaponRootChildren->getValue("rangedWeapons");
		this->parseRangedWeaponToWeaponData(rangedWeapons, &_rangedWeaponData);

		//Parse actor information//
		JSONParser* actorParser = new JSONParser();
		string actorFilename = "JSON/actors.json";
		actorParser->parseFile(actorFilename);

		JSON* actorRoot = actorParser->getRootNode("root");

		HashMap<JSON*>* actorRootChildren = actorRoot->getAllChildren();

		JSON* orcs = actorRootChildren->getValue("orcs");
		this->parseToActorInfo(orcs, "orc", &_actorData);

		//Parse craftable item database//
		JSONParser* craftableParser = new JSONParser();
		string craftableFilename ="JSON/craftables.json";
		craftableParser->parseFile(craftableFilename);

		JSON* craftableRoot = craftableParser->getRootNode("root");
		HashMap<JSON*>* craftableRootChildren = craftableRoot->getAllChildren();

		//===========MAP=========//
		JSON* wall = actorRootChildren->getValue("wall");
		this->parseToActorInfo(wall, "wall", &_blockData);

		JSON* buildings = actorRootChildren->getValue("buildings");
		this->parseToActorInfo(buildings, "building", &_blockData);

		JSON* trees = actorRootChildren->getValue("trees");
		this->parseToActorInfo(trees, "tree", &_blockData);

		JSON* ore = actorRootChildren->getValue("ore");
		this->parseToActorInfo(ore, "ore", &_blockData);

		JSON* water = actorRootChildren->getValue("water");
		this->parseToActorInfo(water, "water", &_blockData);

		JSON* dwarves = actorRootChildren->getValue("dwarves");
		this->parseToActorInfo(dwarves, "dwarf", &_actorData);
	}

	/*Actor Factory::getActor(string type, string name, int health, int stamina,
	 int attack, int defense, string behavior, bool collision)
	 {
	 Actor* newActor = new Actor(type, name, health, stamina, attack,
	 defense, behavior, AllianceType::enemy);
	 newActor->setLocation(new Vector3D(0.0f, 0.0f, 0.0f));
	 return *newActor;
	 }*/

	//NOTE: Right now there's no checking, cause of type issues. Have to know it exists.
	//TODO:^^Make this not the case.
	MeleeWeapon* Factory::getMeleeWeapon(string type)
	{
		WeaponData weaponData = _meleeWeaponData.getValue(type);
		MeleeWeapon* newWeapon = new MeleeWeapon(weaponData);

		return newWeapon;
	}

	//NOTE: Right now there's no checking, cause of type issues. Have to know it exists.
	//TODO:^^Make this not the case.
	RangedWeapon* Factory::getRangedWeapon(string type)
	{
		WeaponData weaponData = _rangedWeaponData.getValue(type);
		RangedWeapon* newWeapon = new RangedWeapon(weaponData);

		return newWeapon;
	}

	void Factory::parseToActorInfo(JSON* rootNode, string type,
			HashMap<ActorInfo>* map)
	{
		int numberOfChildren = rootNode->sizeOfChildren();
		DynamicArray<JSON*>* rootChildren =
				rootNode->getAllChildren()->getAllValues();

		for (int i = 0; i < numberOfChildren; i++)
		{
			JSON* child = rootChildren->get(i);

			string name = child->getChild("name")->getStringValue();
			int health = child->getChild("health")->getIntValue();
			int stamina = child->getChild("stamina")->getIntValue();
			int attack = child->getChild("attack")->getIntValue();
			int defense = child->getChild("defense")->getIntValue();
			string behavior = child->getChild("behavior")->getStringValue();
			bool collision = child->getChild("collision")->getBoolValue();
			float x = (float) child->getChild("x")->getIntValue();
			float y = (float) child->getChild("y")->getIntValue();
			float z = (float) child->getChild("z")->getIntValue();
			int parsedAlliance = child->getChild("alliance")->getIntValue();
			string symbol = child->getChild("symbol")->getStringValue();
			string color = child->getChild("color")->getStringValue();
			int gold = 100;
			int coal = 100;
			int iron = 100;
			int birch = 100;
			int cedar = 100;
			int oak = 100;
			int redwood = 100;
			int wood = 100;

			AllianceType alliance;
			if (parsedAlliance == 0)
			{
				alliance = AllianceType::neutral;
			}
			else if (parsedAlliance == 1)
			{
				alliance = AllianceType::ally;
			}
			else
			{
				alliance = AllianceType::enemy;
			}
//
//			Behavior* behavior = new Behavior();
//			behavior->addBaseBehavior(behaviorString, behaviorValue);

			ActorInfo* info = new ActorInfo(type, name, health, stamina, attack,
					defense, behavior, collision, alliance, symbol, color, gold,
					coal, iron, wood);

			info->setLocation(new Vector3D(x, y, z));

			string i_str = "" + i;
			map->add(type + i_str, *info);

			Actor* myActor = new Actor(info);

			if (type == "dwarf" || type == "orc")
			{
				string weaponType = child->getChild("weapon")->getStringValue();
				MeleeWeapon* meleeWeapon = getMeleeWeapon(weaponType);
				myActor->setMeleeWeapon(meleeWeapon);
			}
			else
			{
				//TODO: This needs to be redone to use the factory... so we ahve to parse weapon data first?
				//The Actor JSON needs to specify what weapon it wants..?
				WeaponData weaponData(10, 2, "", "");
				MeleeWeapon* meleeWeapon = new MeleeWeapon(weaponData);
				myActor->setMeleeWeapon(meleeWeapon);
			}

			if (name.find("iron") != string::npos)
			{
				Inventory& inventory = myActor->getInventory();
				inventory.setSlots(100);
				for (int j = 0; j < iron; j++)
				{
					Item* item = new Item("Iron ore");
					inventory.addItem(item);
				}
			}

			if (name.find("gold") != string::npos)
			{
				Inventory& inventory = myActor->getInventory();
				inventory.setSlots(100);
				for (int j = 0; j < gold; j++)
				{
					Item* item = new Item("Gold");
					inventory.addItem(item);
				}
			}

			if (name.find("coal") != string::npos)
			{
				Inventory& inventory = myActor->getInventory();
				inventory.setSlots(100);
				for (int j = 0; j < coal; j++)
				{
					Item* item = new Item("Coal");
					inventory.addItem(item);
				}
			}

			if (name.find("birch") != string::npos)
			{
				Inventory& inventory = myActor->getInventory();
				inventory.setSlots(100);
				for (int j = 0; j < birch; j++)
				{
					Item* item = new Item("Birch logs");
					inventory.addItem(item);
				}
			}

			if (name.find("oak") != string::npos)
			{
				Inventory& inventory = myActor->getInventory();
				inventory.setSlots(100);
				for (int j = 0; j < oak; j++)
				{
					Item* item = new Item("Oak logs");
					inventory.addItem(item);
				}
			}

			if (name.find("cedar") != string::npos)
			{
				Inventory& inventory = myActor->getInventory();
				inventory.setSlots(100);
				for (int j = 0; j < cedar; j++)
				{
					Item* item = new Item("Cedar logs");
					inventory.addItem(item);
				}
			}

			if (name.find("redwood") != string::npos)
			{
				Inventory& inventory = myActor->getInventory();
				inventory.setSlots(100);
				for (int j = 0; j < redwood; j++)
				{
					Item* item = new Item("Redwood logs");
					inventory.addItem(item);
				}
			}

			_scene->addActor(myActor);
		}
	}

	void Factory::parseMeleeWeaponToWeaponData(JSON* rootNode,
			HashMap<WeaponData>* map)
	{
		int numberOfChildren = rootNode->sizeOfChildren();
		DynamicArray<JSON*>* rootChildren =
				rootNode->getAllChildren()->getAllValues();

		//Cycle through every weapon type
		for (int i = 0; i < numberOfChildren; i++)
		{
			JSON* child = rootChildren->get(i);

			string type = child->getChild("type")->getStringValue();
			int damage = child->getChild("damage")->getIntValue();

			//Create the data specifying this melee weapon
			WeaponData* weaponData = new WeaponData(0, 0, damage, 0, 0, "",
					type);

			map->add(type, *weaponData); //Save this data in the map.
		}
	}

	void Factory::parseRangedWeaponToWeaponData(JSON* rootNode,
			HashMap<WeaponData>* map)
	{
		int numberOfChildren = rootNode->sizeOfChildren();
		DynamicArray<JSON*>* rootChildren =
				rootNode->getAllChildren()->getAllValues();
		//Cycle through every weapon type
		for (int i = 0; i < numberOfChildren; i++)
		{
			JSON* child = rootChildren->get(i);
			string type = child->getChild("type")->getStringValue();
			int range = child->getChild("range")->getIntValue();
			int clipCapacity = child->getChild("clipCapacity")->getIntValue();
			int damage = child->getChild("damage")->getIntValue();
			float reloadSpeed = child->getChild("reloadSpeed")->getFloatValue();
			uint fireRate = child->getChild("fireRate")->getUIntValue();

			//Create the data specifying this ranged weapon
			WeaponData* weaponData = new WeaponData(range, clipCapacity, damage,
					reloadSpeed, fireRate, "", type);

			map->add(type, *weaponData); //Save this data in the map.
		}
	}

	void Factory::parseCraftables(JSON* rootNode, HashMap<Item>* map)
	{
			//take in the parser and create a map of items/ingredients
		//int numberOfChildren = rootNode->sizeOfChildren();
		//DynamicArray<JSON*>* rootChildren = rootNode->getAllChildren()->getAllValues();
	}
}
