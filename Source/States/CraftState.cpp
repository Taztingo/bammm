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

namespace bammm
{

	CraftState::CraftState(Actor& actor);

	CraftState::CraftState(Actor& actor, IStateCallback* stateMachine);

	void CraftState::setup();

	void CraftState::breakdown();

	void CraftState::tick();

	string CraftState::toString()
	{
		return "craft";
	}

}
