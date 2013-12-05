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
 * GatherState cpp file.
 *
 */

#include "GatherState.h"
#include "../Inventory/Inventory.h"
#include "../Inventory/Item.h"

namespace bammm
{
	GatherState::GatherState(Actor& actor)
	{
		_actor = &actor;
	}

	GatherState::GatherState(Actor& actor, IStateCallback* stateMachine)
	{
		_actor = &actor;
		registerTransitionCallback(stateMachine);
	}

	GatherState::~GatherState()
	{
	}

	void GatherState::setup()
	{
		_successChance = 30;
		cout << _actor->getName() << " began gathering!" << "\n";

	}

	void GatherState::setAmount(int amount)
	{
		_amount = amount;
	}

	void GatherState::setTarget(Actor* target)
	{
		_target = target;
	}

	void GatherState::breakdown()
	{
		cout << _actor->getName() << " is finished gathering!" << "\n";
	}

	void GatherState::tick(float deltaTime)
	{
		if (canGather())
		{
			if (_actor->getBAC() > .4)
			{
				cout << _actor->getName()
						<< " drunkenly swings the tool, hits himself in the foot, and decides not to do that anymore."
						<< " drunkenly swings the pickaxe, hits himself in the foot, and decides not to do that anymore."
						<< "\n";
				switchState("null"); //Ends this state;
			}
			else
			{
				bool canPickup = true;
				string typeName = _target->getName();
				Item* removedItem;
				if (typeName.find("gold") != string::npos)
				{
					Item gold("gold", _target->getColor(), true);
					removedItem = _target->getInventory().removeItem(gold);
				}
				else if (typeName.find("iron") != string::npos)
				{
					Item iron("iron", _target->getColor(), true);
					removedItem = _target->getInventory().removeItem(iron);
				}
				else if (typeName.find("coal") != string::npos)
				{
					Item coal("coal", _target->getColor(), true);
					removedItem = _target->getInventory().removeItem(coal);
				}
				else if (typeName.find("redwood") != string::npos ||
						typeName.find("oak") != string::npos ||
						typeName.find("birch") != string::npos
						)
				{
					Item wood("wood", _target->getColor(), true);
					removedItem = _target->getInventory().removeItem(wood);
				}
				else if (typeName.find("dock") != string::npos)
				{
					Item fish("fish", _target->getColor(), true);
					removedItem = _target->getInventory().removeItem(fish);
				}



				_actor->reduceStamina(1);

				string coloredName = Color::colorText(removedItem->getName(), removedItem->getColor());
				canPickup = _actor->getInventory().addItem(removedItem);
				cout << _actor->getName()
						<< " lifts his pickaxe, and swings it at the rock. " << "\n";
				cout << _actor->getName()
						<< " successfully mines some " << coloredName << "\n";

				cout << "Can pickup: " << canPickup << "\n";
				if(!canPickup)
				{
					delete removedItem;
					cout << _actor->getName()
						<< " has a full inventory, and drops " << coloredName
						<< " on the ground.\n";
					_amount = 0;
					switchState("null");
				}
				_amount--;
			}

		}

		else
		{
			//cout << _actor->getName() << " is finished gathering!" << "\n";
			_amount= 0;

			switchState("null");
		}
	}

	void GatherState::switchState(string nextState)
	{
		_stateMachine->switchState(this, nextState);
	}

	string GatherState::toString()
	{
		return "gather";
	}

	bool GatherState::canGather()
	{
		int canMine = 0;

		if(_amount > 0)
		{
			Item gold("gold", true);
			if(_target->getInventory().contains(gold))
			{
				canMine++;
			}

			Item iron("iron", true);
			if(_target->getInventory().contains(iron))
			{
				canMine++;
			}

			Item coal("coal", true);
			if(_target->getInventory().contains(coal))
			{
				canMine++;
			}

			Item wood("wood", true);
			if(_target->getInventory().contains(wood))
			{
				canMine++;
			}

			Item fish("fish", true);
			if(_target->getInventory().contains(fish))
			{
				canMine++;
			}
		}

		return !!canMine;

	}
}
