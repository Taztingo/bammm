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
 * Actor cpp file.
 *
 */

#include "Actor.h"
#include "../Inventory/Inventory.h"

namespace bammm
{
	Actor::Actor()
	{
		_type = "dwarf";
		_name = "DefaultName";
		_rotation = 0;

		_velocity = new Vector3D();
		_location = new Vector3D();
		_collision = false;

		_maximumHealth = 100;
		_maximumStamina = 50;
		_health = _maximumHealth;
		_stamina = _maximumStamina;
		_health = 100;
		_stamina = 50;
		_attack = 4;
		_defense = 2;
		_symbol = "D";
		_color = "white";
		_level = 1;
		_experience = 0;
		_totalExperienceThisLevel = 1;
	}

	Actor::Actor(string name, string type, AllianceType alliance)
	{
		_name = name;
		_type = type;
		_rotation = 0;

		_velocity = new Vector3D();
		_location = new Vector3D();
		_collision = false;

		_maximumHealth = 100;
		_maximumStamina = 50;
		_health = _maximumHealth;
		_stamina = _maximumStamina;
		_health = 100;
		_stamina = 50;
		_attack = 4;
		_defense = 2;
		_alliance = alliance;
		_level = 1;
		_experience = 0;
		_totalExperienceThisLevel = 1;
	}

	Actor::Actor(string type, string name, int health, int stamina, int attack,
			int defense, string behavior, AllianceType alliance)
	{
		_type = type;
		_name = name;

		_rotation = 0;
		_velocity = new Vector3D();
		_location = new Vector3D();
		_collision = false;

		_maximumHealth = health;
		_maximumStamina = stamina;
		_health = _maximumHealth;
		_stamina = _maximumStamina;
		_health = health;
		_stamina = stamina;
		_attack = attack;
		_defense = defense;
		_alliance = alliance;
		_level = 1;
		_experience = 0;
		_totalExperienceThisLevel = 1;
		_behavior = behavior;
	}

	Actor::Actor(ActorInfo* info)
	{
		_type = info->getType();
		_name = info->getName();
		_rotation = 0;
		_velocity = new Vector3D();
		_location = info->getLocation();

		_maximumHealth = info->getHealth();
		_maximumStamina = info->getStamina();
		_health = _maximumHealth;
		_stamina = _maximumStamina;
		_health = info->getHealth();
		_stamina = info->getStamina();
		_attack = info->getAttack();
		_defense = info->getDefense();

		_behavior = info->getBehavior();
		_alliance = info->getAlliance();
		_collision = info->getCollision();
		_symbol = info->getSymbol();
		_color = info->getColor();
		_wood = info->getWood();
		_iron = info->getIron();
		_gold = info->getGold();
		_coal = info->getCoal();
		_BAC = 0;
		_level = 1;
		_experience = 0;
		_totalExperienceThisLevel = 1;
	}

	void Actor::setMeleeWeapon(MeleeWeapon* weapon)
	{
		_meleeWeapon = weapon;
	}

	void Actor::setRangedWeapon(RangedWeapon* weapon)
	{
		_rangedWeapon = weapon;
	}

	void Actor::setRotation(float myRotation)
	{
		_rotation = myRotation;
	}

	void Actor::setName(string name)
	{
		_name = name;
	}

	void Actor::setType(string type)
	{
		_type = type;
	}

	void Actor::setBehavior(string behavior)
	{
		_behavior = behavior;
	}

	void Actor::setLocation(Vector3D* location)
	{
		_location = location;
	}

	void Actor::setSymbol(string symbol)
	{
		_symbol = symbol;
	}

	void Actor::setColor(string color)
	{
		_color = color;
	}

	void Actor::setGold(int gold)
	{
		_gold = gold;
	}

	void Actor::setIron(int iron)
	{
		_iron = iron;
	}

	void Actor::setCoal(int coal)
	{
		_coal = coal;
	}

	void Actor::setWood(int wood)
	{
		_wood = wood;
	}

	void Actor::increaseHealth(int amount)
	{
		if (_health >= _maximumHealth)
		{
			_health = _maximumHealth;
			return;
		}
		else
		{
			_health += amount;
		}
	}

	void Actor::increaseStamina(int amount)
	{
		if (_stamina >= _maximumStamina)
		{
			_stamina = _maximumStamina;
			return;
		}
		else
		{
			_stamina += amount;
		}
	}

	void Actor::reduceHealth(int amount)
	{
		if (_health > 0)
		{
			_health -= amount;
		}
		else
		{
			_health = 0;
			return;
		}
	}

	void Actor::reduceStamina(int amount)
	{
		if (_stamina > 0)
		{
			_stamina -= amount;
		}
		else
		{
			_stamina = 0;
		}
	}

	bool Actor::isFullyRested()
	{
		if (_health == _maximumHealth && _stamina == _maximumStamina)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void Actor::incrementBAC()
	{
		_BAC += .01;
		return;
	}

	int Actor::addGold(int amount)
	{
		_gold += amount;
		return _gold;
	}

	bool Actor::spendGold(int amount)
	{
		if (_gold < amount)
		{
			return false;
		}
		else
		{
			_gold -= amount;
			return true;
		}
	}

	int Actor::getGold()
	{
		return _gold;
	}

	int Actor::getWood()
	{
		return _wood;
	}

	int Actor::getCoal()
	{
		return _coal;
	}

	int Actor::getIron()
	{
		return _iron;
	}

	bool Actor::getCollision()
	{
		return _collision;
	}

	MeleeWeapon* Actor::getMeleeWeapon()
	{
		return _meleeWeapon;
	}

	RangedWeapon* Actor::getRangedWeapon()
	{
		return _rangedWeapon;
	}

	float Actor::getBAC()
	{
		return _BAC;
	}

	float Actor::getRotation()
	{
		return _rotation;
	}

	string Actor::getName()
	{
		return _name;
	}

	string Actor::getVelocity()
	{
		return _velocity->toString();
	}

	Vector3D* Actor::getLocation()
	{
		return _location;
	}

	int Actor::getHealth()
	{
		return _health;
	}

	void Actor::setHealth(int health)
	{
		_health = health;
	}

	int Actor::getStamina()
	{
		return _stamina;
	}

	int Actor::getAttack()
	{
		return _attack;
	}

	void Actor::setAttack(int attack)
	{
		_attack = attack;
	}

	int Actor::getDefense()
	{
		return _defense;
	}

	void Actor::setDefense(int defense)
	{
		_defense = defense;
	}

	string Actor::getType()
	{
		return _type;
	}

	string Actor::getBehavior()
	{
		return _behavior;
	}

	int Actor::getX()
	{
		return _location->getX();
	}

	int Actor::getY()
	{
		return _location->getY();
	}

	int Actor::getZ()
	{
		return _location->getZ();
	}

	Vector3D * Actor::getVectorLocation()
	{
		return _location;
	}

	int Actor::getAlliance()
	{
		return _alliance;
	}

	string Actor::getSymbol()
	{
		return _symbol;
	}

	string Actor::getColor()
	{
		return _color;
	}

	int Actor::getEnemyAlliance()
	{
		return _alliance * -1;
	}

	Inventory& Actor::getInventory()
	{
		return _inventory;
	}

	int Actor::getLevel()
	{
		return _level;
	}

	void Actor::setLevel(int newLevel)
	{
		_level = newLevel;
	}

	int Actor::getExperience()
	{
		return _experience;
	}

	void Actor::setExperience(int newExperience)
	{
		_experience = newExperience;
	}

	int Actor::getTotalExperienceThisLevel()
	{
		return _totalExperienceThisLevel;
	}

	void Actor::setTotalExperienceThisLevel(int newTotalExperienceThisLevel)
	{
		_totalExperienceThisLevel = newTotalExperienceThisLevel;
	}

	int Actor::getMaximumHealth()
	{
		return _maximumHealth;
	}

	void Actor::setMaximumHealth(int maximumHealth)
	{
		_maximumHealth = maximumHealth;
	}

	void Actor::setMaximumStamina(int maximumStamina)
	{
		_maximumStamina = maximumStamina;
	}

	string Actor::toString()
	{
		return _name;
	}
}
