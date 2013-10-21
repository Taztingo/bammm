/*
 * CS585
 *
 * Team Bammm
 * 	Alvaro Home
 * 	Matt Konstantinou
 * 	Michael Abramo
 *	Matt Witkowski
 *	Bradley Crusco
 *
 * Description:
 * Drinking state header file.
 *
 * Last Modified: Matthew Konstantinou
 *
 */

#ifndef STATE_H_
#define STATE_H_

#include <iostream>
#include "../resources/dynamicarray.h"
#include "../IStateCallback.h"
#include "../actors/actor.h"

#ifndef NULL
#define NULL (void *)0
#endif

using namespace std;

namespace bammm
{
    class State
    {
        public:
	    State();

	    /*
	    * setup
	    * Pre-Condition- no parameters
	    * Post-Condition- no return value
	    *
	    * Sets actor's necessary attributes for beginning a state
	    */
	    void setup();

	    /*
	    * breakDown
	    * Pre-Condition- no parameters
	    * Post-Condition- no return value
	    *
	    * Returns Actor to old state
	    */
	    void breakdown();

	    /*
	    * tick
	    *
	    * Pre-Condition- time as recorded since beginning state
	    * Post-Condition- no return value
	    *
	    * Process state updates based on passed time
	    */
	    void tick(float dTime);

	    //void registerTransitionCallback(IStateCallback callback);
    protected:
	    Actor* _actor;
    };
}
#endif
