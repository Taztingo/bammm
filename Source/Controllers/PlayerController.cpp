/*
 * CS585
 *
 * Team Bammm
 * 	Alvaro Home
 * 	Matt Konstantinou
 * 	Michael Abramo
 *	Matt Witkowski
 *   Bradley Crusco
 * Description:
 * PlayerController cpp file.
 *
 */

#include "PlayerController.h"

namespace bammm
{
	PlayerController::PlayerController()
	{
	}

	PlayerController::~PlayerController()
	{
	}

	void PlayerController::setup(Actor& actor, MeleeCombat& meleeCombat,
			Grid3D<Actor*>& sceneGraph)
	{
		_meleeCombat = &meleeCombat;
		_sceneGraph = &sceneGraph;

		_actor = &actor;
		_stateMachine.setup(actor, _states, _meleeCombat);

		//Create the states
		DrinkState* drinkState = new DrinkState(actor, &_stateMachine);
		SingState* singState = new SingState(actor, &_stateMachine);
		BrawlState* brawlState = new BrawlState(actor, &_stateMachine);
		SleepState* sleepState = new SleepState(actor, &_stateMachine);
		IdleState* idleState = new IdleState(actor, &_stateMachine);
		CombatState* combatState = new CombatState(actor, &_stateMachine);
		SearchState* searchState = new SearchState(actor, &_stateMachine, *_sceneGraph);
		DamageState* damageState = new DamageState(actor, &_stateMachine);
		MoveState* moveState = new MoveState(actor, &_stateMachine, sceneGraph);
		GatherState* gatherState = new GatherState(actor, &_stateMachine);
		EatState* eatState = new EatState(actor, &_stateMachine);

		_states.add(idleState->toString(), idleState);
		_states.add(drinkState->toString(), drinkState);
		_states.add(singState->toString(), singState);
		_states.add(brawlState->toString(), brawlState);
		_states.add(sleepState->toString(), sleepState);
		_states.add(combatState->toString(), combatState);
		_states.add(searchState->toString(), searchState);
		_states.add(damageState->toString(), damageState);
		_states.add(moveState->toString(), moveState);
		_states.add(gatherState->toString(), gatherState);
		_states.add(eatState->toString(), eatState);

		//Put actor in default behavior state
		_stateMachine.initialState(_states.getValue(idleState->toString()));
	}

	void PlayerController::input(DynamicArray<string>* commandString,
			float deltaTime)
	{
		string newState = commandString->get(0);
		//bool doTick = true;
		State* stateToAdd;

		DynamicArray<string>* oreType = new DynamicArray<string>();
		oreType->add("iron");
		oreType->add("coal");
		oreType->add("gold");

		DynamicArray<string>* woodType = new DynamicArray<string>();
		woodType->add("redwood");
		woodType->add("birch");
		woodType->add("oak");

		DynamicArray<string>* fishType = new DynamicArray<string>();
		fishType->add("swordfish");
		fishType->add("tuna");
		fishType->add("salmon");

		DynamicArray<string>* foodTypes = new DynamicArray<string>();
		foodTypes->add("fish");

		if (newState == "mine" || newState == "chop" || newState == "fish")
		{
			int numToGather;
			string type;

			if (commandString->getSize() == 3)
			{
				string arg1 = commandString->get(1);
				numToGather = atoi(arg1.c_str());

				if (numToGather == 0)
				{
					cout << "Invalid argument number \n";
					return;
				}

				type = commandString->get(2);
				if ( (newState == "mine" && !(oreType->contains(type))) )
				{
					cout << "Invalid ore type" << endl;
					return;
				}
				else if ( (newState == "chop" && !(woodType->contains(type))) )
				{
					cout << "Invalid wood type" << endl;
					return;
				}
				else if ( (newState == "fish" && !(fishType->contains(type))) )
				{
					cout << "Invalid fish type" << endl;	
					return;
				}

				cout << _actor->getName() << " has been sent to " << newState << " " << type << "!" << endl;


				if (newState == "fish")
				{
					type = "dock";
				}

				Actor* target = _sceneGraph->findInGrid(type);
				stateToAdd = _states.getValue("gather");
				GatherState* tempState = static_cast<GatherState*>(stateToAdd);
				tempState->setAmount(numToGather);
				tempState->setTarget(target);

				//Add to controllerinput
				SearchState* search = static_cast<SearchState*>(_states.getValue("search"));
				search->setTarget(type);
				search->setDestState(tempState);
				_stateMachine.addState(search);

			}
		}
		else if (newState == "drink")
		{
			cout << _actor->getName() << " has been sent to drink at the Pub!" << endl;

			stateToAdd = _states.getValue(newState);
			SearchState* search = static_cast<SearchState*>(_states.getValue("search"));
			search->setTarget("Pub");
			search->setDestState(stateToAdd);
			_stateMachine.addState(search);
		}
		else if (commandString->getSize() == 3 && newState == "eat")
		{
			string arg1 = commandString->get(1);
			int numToEat = atoi(arg1.c_str());

			if (numToEat == 0)
			{
				cout << "Invalid argument number \n";
				return;
			}

			string type = commandString->get(2);
			if (!(foodTypes->contains(type)))
			{
				cout << "Invalid argument number \n";
				return;
			}


			EatState* tempState = static_cast<EatState*>(_states.getValue(newState));
			tempState->setAmount(numToEat);
			tempState->setType(type);
			_stateMachine.addState(tempState);
		}
		else if (newState == "inventory")
		{
			cout << _actor->getInventory().toString() << endl;
		}

		else
		{
			cout << "Invalid command" << endl;
		}

	}

	void PlayerController::input(string command, float deltaTime)
	{
		DynamicArray<string>* passValue = new DynamicArray<string>();
		passValue->add(command);
		input(passValue, deltaTime);
		delete passValue;
	}

	void PlayerController::printOptions()
	{
		//DynamicArray<State*>& currentStates = _stateMachine.getCurrentStates();
		cout << "What would you like your villagers to do?\n  To run the simulation, enter \"wait [number of iterations]\"." << endl;

	}

	bool PlayerController::canDelete()
	{
		if (_actor->getHealth() <= 0)
		{
			return true;
		}

		return false;
	}

	void PlayerController::tick(float deltaTime)
	{
		Actor* enemy = _sceneGraph->getEnemy(_actor->getLocation(), _actor);
		DynamicArray<State*>& currentStates = _stateMachine.getCurrentStates();
		State* newState;

		if (enemy)
		{
			newState = _states.getValue("damage");

			if(!currentStates.contains(newState))
			{
				_stateMachine.addState(newState);
				DamageState* castedState = static_cast<DamageState*>(newState);
				castedState->setTarget(*enemy);
			}
		}

		_stateMachine.tick(deltaTime);
	}

	string PlayerController::toString()
	{
		return "PlayerController";
	}

	int PlayerController::numberOfStates()
	{
		return _stateMachine.getCurrentStates().getSize();
	}

	DynamicArray<State*>& PlayerController::runningStates()
	{
		return _stateMachine.getCurrentStates();
	}

	HashMap<State*>& PlayerController::allStates()
	{
		return _states;
	}

	Actor* PlayerController::getActor()
	{
		return _actor;
	}

}
