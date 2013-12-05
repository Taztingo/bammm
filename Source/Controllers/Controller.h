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
 * Controller header file.
 *
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <string>
#include "../Interfaces/ITickable.h"
#include "../States/State.h"
#include "../States/IdleState.h"
#include "../States/DrinkState.h"
#include "../States/BrawlState.h"
#include "../States/SleepState.h"
#include "../States/SingState.h"
#include "../States/CombatState.h"
#include "../States/DamageState.h"
#include "../States/EatState.h"
#include "../States/MoveState.h"
#include "../States/SearchState.h"
#include "../States/GatherState.h"
#include "../Resources/HashMap.h"
#include "../Actors/Actor.h"
#include "../States/StateMachine.h"
#include "../Weapons/MeleeCombat.h"
#include "../Weapons/RangedCombat.h"
#include "../SceneManager/Grid3D.h"

using namespace std;

namespace bammm
{
	class Controller: public ITickable
	{
		protected:
			HashMap<State*> _states;
			Actor* _actor;
			Grid3D<Actor*>* _sceneGraph;
			StateMachine _stateMachine;
			MeleeCombat* _meleeCombat;
			RangedCombat* _rangedCombat;

		public:
			Controller();
			virtual ~Controller();

			/**
			 setup
			 @Pre-Condition- Takes an Actor, MeleeCombat, and Grid3D as input
			 @Post-Condition - Sets up the controller with the passed Actor, MeleeCombat, and Grid3D.
			 */
			virtual void setup(Actor& actor, MeleeCombat& meleeCombat,
					Grid3D<Actor*>& sceneGraph)=0;

			virtual void tick(float deltaTime)=0;

			/**
			 canDelete
			 @Pre-Condition- Takes nothing
			 @Post-Condition- Returns a boolean representing fi the Controller can be deleted or not.
			 */
			virtual bool canDelete()=0;
			
			/**
			 getActor
			 @Pre-Condition- Takes nothing
			 @Post-Condition- Returns the actor the controller uses
			 */
			virtual Actor* getActor()=0;

			/**
			 toString
			 @Pre-Condition- Takes nothing
			 @Post-Condition- Returns a string representation of Controller
			 */
			virtual string toString()=0;
	};
}

#endif
