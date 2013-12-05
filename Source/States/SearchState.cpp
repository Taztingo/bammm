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
 * SearchState cpp file.
 *
 */

#include "SearchState.h"

namespace bammm
{
	SearchState::SearchState(Actor& actor)
	{
		_actor = &actor;
	}

	SearchState::SearchState(Actor& actor, IStateCallback* stateMachine,
			Grid3D<Actor*>& sceneGraph)
	{
		_sceneGraph = &sceneGraph;
		_actor = &actor;
		registerTransitionCallback(stateMachine);
	}

	void SearchState::setTarget(string target)
	{
		_target = target;

	}

	void SearchState::setDestState(State* goal)
	{
		_goalState = goal;
	}

	void SearchState::setup()
	{
		if (_target == "")
		{
			string behavior = _actor->getBehavior();
			if (behavior == "drink")
			{
				_target = "Pub";
			}
			else if (behavior == "sleep")
			{
				_target = "Inn";
			}
			else
			{
				_target = "Inn";
			}
		}

		_path = _sceneGraph->getPath(_actor, _target);
	}

	void SearchState::breakdown()
	{
	}

	void SearchState::tick(float deltaTime)
	{
		if (_path->isEmpty())
		{
			switchState("null");

		}
		else
		{
			Vector3D* newloc = _path->remove();
			_sceneGraph->move(_actor, newloc);
		}

		Vector3D* targetActor = _sceneGraph->findClosestInGrid(_actor, _target)->getLocation();

		if (_actor->getLocation()->getX() == targetActor->getX() &&
				_actor->getLocation()->getY() == targetActor->getY() &&
				_actor->getLocation()->getZ() == targetActor->getZ())
		{
			if (_goalState != NULL)
			{
				switchState(_goalState);
			}
			else
			{
				switchState(_actor->getBehavior());
			}
		}
	}

	void SearchState::switchState(string nextState)
	{
		_stateMachine->switchState(this, nextState);
	}

	void SearchState::switchState(State* nextState)
	{
		_stateMachine->switchState(this, nextState);
	}

	string SearchState::toString()
	{
		return "search";
	}
}
