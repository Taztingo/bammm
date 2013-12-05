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
 * Crafting State header file.
 *
 */

#ifndef CRAFTSTATE_H_
#define CRAFTSTATE_H_

#include "State.h"

namespace bammm
{

	class CraftState: public State
	{

		private:

			int _craftableAmount;
			Item* _craftableItem;

		public:

			CraftState(Actor& actor);
			CraftState(Actor& actor, IStateCallback* stateMachine);

			/**
			 setup
			 @Pre-Condition- No input
			 @Post-Condition- Sets up the state
			 */
			void setup();

			/**
			 breakdown
			 @Pre-Condition- No input
			 @Post-Condition- Performs a breakdown on the state
			 */
			void breakdown();

			/**
			 tick
			 @Pre-Condition- Takes in a float deltaTime
			 @Post-Condition- Executes a tick of length deltaTime
			 */
			virtual void tick(float deltaTime);

			/**
			 switchState
			 @Pre-Condition- Takes in a string nextState
			 @Post-Condition- The current state is switched to the given nextState
			 */
			virtual void switchState(string nextState);

			/**
			 toString
			 @Pre-Condition- No input
			 @Post-Condition- Returns a string representation of the state
			 */
			string toString();

			void setCraftable(Item* craftableItem);

			void setAmount(int craftableAmount);

			void craft();

	};

}

#endif
