/*
 * CS585
 *
 * Team Bammm
 * 	Alvaro Home
 * 	Matt Konstantinou
 * 	Michael Abramo
 *	Matt Witkowski
 *	Bradley Crusco
 * Description:
 * DamageState cpp file.
 *
 */

#include "DamageState.h"
#include "../Resources/Color.h"

namespace bammm
{
	DamageState::DamageState(Actor& actor)
	{
		_actor = &actor;
	}

	DamageState::DamageState(Actor& actor, IStateCallback* stateMachine)
	{
		_actor = &actor;
		registerTransitionCallback(stateMachine);
	}

	void DamageState::setTarget(Actor& target)
	{
		_target = &target;
	}

	void DamageState::setup()
	{
	}

	void DamageState::breakdown()
	{
	}

	void DamageState::tick(float deltaTime)
	{
		MeleeWeapon* weapon = _actor->getMeleeWeapon();
		string attackerName = _actor->getName();
		string targetName = _target->getName();
		string weaponName = weapon->getType();

		if (weapon->canAttack())
		{
			int damage = weapon->attack();
			_target->reduceHealth(damage);
			cout << attackerName << " hits " << targetName << " with " << weaponName << " for " << Color::colorText(to_string(damage), "red")
					<< " damage. ";
			cout << targetName << " has " << Color::colorText(to_string(_target->getHealth()), "green") << " health.\n";
			if (_target->getHealth() <= 0)
			{
				cout << attackerName << Color::colorText(" has slain ", "red") << targetName << ".\n";

				_actor = _levelingSystem.gainExperience(_actor);

			}
		}
		else
		{
			cout << attackerName << " can't attack yet." << "\n";
		}

		switchState("null");
	}

	void DamageState::switchState(string nextState)
	{
		_stateMachine->switchState(this, nextState);
	}

	string DamageState::toString()
	{
		return "damage";
	}
}
