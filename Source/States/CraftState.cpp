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
 * Craft State source file.
 *
 */

#include "CraftState.h"
#include <string>

namespace bammm
{

	CraftState::CraftState(Actor& actor)
	{
		_actor = &actor;
	}

	CraftState::CraftState(Actor& actor, IStateCallback* stateMachine)
	{
		_actor = &actor;
		registerTransitionCallback(stateMachine);
	}

	void CraftState::setup()
	{

	}

	void CraftState::breakdown()
	{

	}

	void CraftState::tick(float deltaTime)
	{




	}

	void CraftState::switchState(string nextState)
	{
		_stateMachine->switchState(this, nextState);
	}

	string CraftState::toString()
	{
		return "craft";
	}

	void CraftState::setCraftable(Item* craftableItem)
	{
		_craftableItem = craftableItem;
	}

	void CraftState::setAmount(int craftableAmount)
	{
		_craftableAmount = craftableAmount;
	}

}
