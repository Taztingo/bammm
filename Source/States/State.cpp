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
 * State cpp file.
 *
 */

#include "State.h"

namespace bammm
{
	State::State()
	{
	}

	State::State(Actor& actor)
	{
		_actor = &actor;
	}

	State::~State()
	{

	}

	void State::setup()
	{

	}

	void State::breakdown()
	{
		cout << "wrong breakdown" << "\n";
	}


	void State::tick(float deltaTime)
	{
		cout << "In parent state\n";
	}

	void State::registerTransitionCallback(IStateCallback* stateMachine)
	{
		_stateMachine = stateMachine;
	}

	void State::switchState(string nextState)
	{
		//_statemachine->switchState(this, nextState);
	}

	string State::toString()
	{
		return "State";
	}

	bool State::operator==(State* state)
	{
		return false;
	}
}
