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
 * State header file.
 *
 */

#ifndef STATE_H_
#define STATE_H_

#include <iostream>
#include "../Resources/DynamicArray.h"
#include "../Interfaces/IStateCallback.h"
#include "../Interfaces/ITickable.h"
#include "../Actors/Actor.h"
#include "../SceneManager/Vector3D.h"
#include "../Resources/Constant.h"
#include "../Resources/Color.h"
#include "../LevelingSystem/LevelingSystem.h"

using namespace std;

namespace bammm
{
	class State: public ITickable
	{
		protected:
			Actor* _actor;
			IStateCallback* _stateMachine;
			LevelingSystem _levelingSystem;

		public:
			State();
			State(Actor& actor);
			virtual ~State();

			/**
			 setup
			 @Pre-Condition- No input
			 @Post-Condition- Sets up the state
			 */
			virtual void setup();

			/**
			 breakdown
			 @Pre-Condition- No input
			 @Post-Condition- Performs a breakdown on the state
			 */
			virtual void breakdown();

			/**
			 tick
			 @Pre-Condition- Takes in a float deltaTime
			 @Post-Condition- Executes a tick of length deltaTime
			 */
			virtual void tick(float deltaTime);

			/**
			 registerTransitionCallback
			 @Pre-Condition- Takes in a IStateCallback& state machine
			 @Post-Condition- A transition callback is registered
			 */
			virtual void registerTransitionCallback(
					IStateCallback* stateMachine);

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
			virtual string toString();

			/**
			 operator==
			 @Pre-Condition- Takes in a State*
			 @Post-Condition- Returns a boolean of the comparison between two states
			 */
			virtual bool operator==(State* state);
	};
}

#endif
