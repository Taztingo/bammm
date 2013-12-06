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
		//Parse weapons
		JSONParser* weaponParser = new JSONParser();
		string weaponFilename = "JSON/weapons.json";
		weaponParser->parseFile(weaponFilename);

		JSON* weaponRoot = weaponParser->getRootNode("root");
		HashMap<JSON*>* weaponRootChildren = weaponRoot->getAllChildren();

		JSON* meleeWeapons = weaponRootChildren->getValue("meleeWeapons");
		this->parseMeleeWeaponToWeaponData(meleeWeapons, &_meleeWeaponData);

		JSON* rangedWeapons = weaponRootChildren->getValue("rangedWeapons");
		this->parseRangedWeaponToWeaponData(rangedWeapons, &_rangedWeaponData);

		//Parse craftable item database
		JSONParser* craftableParser = new JSONParser();
		string craftableFilename = "JSON/craftables.json";
		craftableParser->parseFile(craftableFilename);

		JSON* craftableRoot = craftableParser->getRootNode("root");

		//Parse craftable item database//
		JSONParser* craftableParser = new JSONParser();
		string craftableFilename = "JSON/craftables.json";
		craftableParser->parseFile(craftableFilename);

		_craftables = craftableParser->getRootNode("root");

		//Parse actors info
		JSONParser* actorParser = new JSONParser();
		string actorFilename = "JSON/actors.json";
		actorParser->parseFile(actorFilename);

		JSON* actorRoot = actorParser->getRootNode("root");
		HashMap<JSON*>* actorRootChildren = actorRoot->getAllChildren();

		JSON* orcs = actorRootChildren->getValue("orcs");
		this->parseToActorInfo(orcs, "orc", &_actorData);

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

		JSON* dock = actorRootChildren->getValue("dock");
		this->parseToActorInfo(dock, "dock", &_blockData);

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

	MeleeWeapon* Factory::getMeleeWeapon(string type)
	{
		WeaponData weaponData = _meleeWeaponData.getValue(type);
		MeleeWeapon* newWeapon = new MeleeWeapon(weaponData);

		return newWeapon;
	}

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
			int fish = 100;
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
				//Give some default weapon stats
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
					Item* item = new Item("iron", color, true);
					inventory.addItem(item);
				}
			}

			if (name.find("gold") != string::npos)
			{
				Inventory& inventory = myActor->getInventory();
				inventory.setSlots(100);

				for (int j = 0; j < gold; j++)
				{
					Item* item = new Item("gold", color, true);
					inventory.addItem(item);
				}
			}

			if (name.find("coal") != string::npos)
			{
				Inventory& inventory = myActor->getInventory();
				inventory.setSlots(100);

				for (int j = 0; j < coal; j++)
				{
					Item* item = new Item("coal", color, true);
					inventory.addItem(item);
				}
			}

			if (name.find("birch") != string::npos)
			{
				Inventory& inventory = myActor->getInventory();
				inventory.setSlots(100);

				for (int j = 0; j < birch; j++)
				{
					Item* item = new Item("wood", color, true);
					inventory.addItem(item);
				}
			}

			if (name.find("oak") != string::npos)
			{
				Inventory& inventory = myActor->getInventory();
				inventory.setSlots(100);

				for (int j = 0; j < oak; j++)
				{
					Item* item = new Item("wood", color, true);
					inventory.addItem(item);
				}
			}

			if (name.find("cedar") != string::npos)
			{
				Inventory& inventory = myActor->getInventory();
				inventory.setSlots(100);

				for (int j = 0; j < cedar; j++)
				{
					Item* item = new Item("wood", color, true);
					inventory.addItem(item);
				}
			}

			if (name.find("redwood") != string::npos)
			{
				Inventory& inventory = myActor->getInventory();
				inventory.setSlots(100);

				for (int j = 0; j < redwood; j++)
				{
					Item* item = new Item("wood", color, true);
					inventory.addItem(item);
				}
			}

			if (name.find("dock") != string::npos)
			{
				Inventory& inventory = myActor->getInventory();
				inventory.setSlots(100);

				for (int j = 0; j < fish; j++)
				{
					Item* item = new Item("fish", color, true);
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

		for (int i = 0; i < numberOfChildren; i++)
		{
			JSON* child = rootChildren->get(i);
			string type = child->getChild("type")->getStringValue();
			int damage = child->getChild("damage")->getIntValue();
			WeaponData* weaponData = new WeaponData(0, 0, damage, 0, 0, "",
					type);

			map->add(type, *weaponData);
		}
	}

	void Factory::parseRangedWeaponToWeaponData(JSON* rootNode,
			HashMap<WeaponData>* map)
	{
		int numberOfChildren = rootNode->sizeOfChildren();
		DynamicArray<JSON*>* rootChildren =
				rootNode->getAllChildren()->getAllValues();

		for (int i = 0; i < numberOfChildren; i++)
		{
			JSON* child = rootChildren->get(i);
			string type = child->getChild("type")->getStringValue();
			int range = child->getChild("range")->getIntValue();
			int clipCapacity = child->getChild("clipCapacity")->getIntValue();
			int damage = child->getChild("damage")->getIntValue();
			float reloadSpeed = child->getChild("reloadSpeed")->getFloatValue();
			uint fireRate = child->getChild("fireRate")->getUIntValue();
			WeaponData* weaponData = new WeaponData(range, clipCapacity, damage,
					reloadSpeed, fireRate, "", type);

			map->add(type, *weaponData);
		}
	}
}
