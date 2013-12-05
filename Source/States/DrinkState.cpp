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
 * DrinkState cpp file.
 *
 */

#include "DrinkState.h"

namespace bammm
{
	DrinkState::DrinkState(Actor& actor)
	{
		_actor = &actor;
	}

	DrinkState::DrinkState(Actor& actor, IStateCallback* stateMachine)
	{
		_actor = &actor;
		registerTransitionCallback(stateMachine);
	}

	void DrinkState::setup()
	{
		_stoutLife = _stoutSize;
	}

	void DrinkState::breakdown()
	{
		double BAC = _actor->getBAC();
		if (BAC < 0.1)
		{
			//Do nothing
		}
		else if (BAC < 0.25)
		{
			cout << _actor->getName()
					<< " puts down his drink.  He's slightly tipsy, but is ready to get back to work!"
					<< "\n";
		}
		else if (BAC < 0.35)
		{
			_actor->incrementBAC();
			cout << _actor->getName()
					<< " finishes his sloppily drink and slams it down on the counter, ready to go out and explore the village."
					<< "\n";
		}
		else if (BAC < 0.5)
		{
			_actor->reduceHealth(2);
			cout << _actor->getName()
					<< " is very drunk.  He gets up to leave and falls over a table before making his way out the door."
					<< "\n";
		}
	}

	void DrinkState::tick(float deltaTime)
	{

		string name = _actor->getName();
		if (_stoutLife == 0)
		{
			_stoutLife = 5;
			if (!(_actor->spendGold(3)))
			{
				cout << _actor->getName()
						<< " does not have enough gold to buy alcohol." << "\n";
				return;
			}
		}

		_stoutLife--;
		_actor->reduceStamina(1);
		_actor->incrementBAC();

		if (_actor->getBAC() >= 0.5)
		{
			cout << name
					<< " is too drunk to continue.  He drops his glass and passes out on the floor."
					<< "\n";
			switchState("sleep");
		}
		else if (_stoutLife < 1)
		{
			cout << name
					<< " finishes his drink. \"There's nothin' like a Dwarveren Ale from Ironforge.\""
					<< "\n";
		}
		else
		{
			cout << name << " takes a sip of the Dwarven Ale." << "\n";
		}
	}

	void DrinkState::switchState(string nextState)
	{
		_stateMachine->switchState(this, nextState);
	}

	string DrinkState::toString()
	{
		return "drink";
	}
}
