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
 * PlayerController header file.
 *
 */

#ifndef PLAYERCONTROLLER_H_
#define PLAYERCONTROLLER_H_

#include "Controller.h"
#include "../Factories/Factory.h"
#include "../Resources/Constant.h"

using namespace std;

namespace bammm
{
	class PlayerController: public Controller
	{
		public:
			PlayerController();
			~PlayerController();

			/**
			 input
			 @Pre-Condition- Takes multiple commands and a deltaTime
			 @Post-Condition- The commands are executed.
			 */
			void input(DynamicArray<string>* commandString, float deltaTime);

			/**
			 input
			 @Pre-Condition- Takes a single command and a deltaTime
			 @Post-Condition- The command is executed.
			 */
			void input(string command, float deltaTime);

			/**
			 setup
			 @Pre-Condition- Takes an Actor, MeleeCombat, and Grid3D as input
			 @Post-Condition- Sets up the controller with the passed Actor, MeleeCombat, and Grid3D.
			 */
			void setup(Actor& actor, MeleeCombat& meleeC,
					Grid3D<Actor*>& sceneGraph);

			/**
			 printOptions
			 @Pre-Condition- Takes no arguments
			 @Post-Condition- Prints out control options to the screen
			 */
			void printOptions();

			/** 
			 canDelete
			 @Pre-Condition- Takes nothing
			 @Post-Condition- Returns a boolean representing if the Controller can be deleted or not.
			 */
			virtual bool canDelete();

			/**
			 tick
			 @Pre-Condition- Takes a float deltaTime
			 @Post-Condition- Ticks for deltaTime
			 */
			virtual void tick(float deltaTime);

			/**
			 tick
			 @Pre-Condition- Takes nothing
			 @Post-Condition- Returns a string representation of a tickable
			 */
			virtual string toString();
	};
}

#endif
