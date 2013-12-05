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
 * SceneManager cpp file.
 *
 */

#include <string>
#include "SceneManager.h"
#include "../Controllers/PlayerController.h"

using namespace std;

namespace bammm
{
	SceneManager::SceneManager() :
			_sceneGraph(SCENE_X, SCENE_Y, SCENE_Z)
	{
		_focus = NULL;
	}

	SceneManager::~SceneManager()
	{
	}

	void SceneManager::setMeleeCombat(MeleeCombat& meleeCombat)
	{
		_meleeCombat = &meleeCombat;
	}

	void SceneManager::addActor(Actor* actor)
	{
		_allActors.add(actor);
		_sceneGraph.add(actor->getLocation(), actor);

		if (actor->getType() == "dwarf")
		{
			PlayerController* controller = new PlayerController();
			controller->setup(*actor, *_meleeCombat, _sceneGraph);
			this->addTickable(controller);
			this->addPlayerController(controller);
		}
		else if (actor->getType() == "orc")
		{
			AiController* controller = new AiController();
			controller->setup(*actor, *_meleeCombat, _sceneGraph);
			this->addTickable(controller);
			this->addAiController(controller);
		}
	}

	Actor* SceneManager::removeActor(Actor* actor)
	{
		_allActors.removeElement(actor);
		_sceneGraph.remove(actor->getLocation(), actor);
		return actor;
	}

	void SceneManager::addTickable(ITickable* tickable)
	{
		_allTickables.add(tickable);
	}

	void SceneManager::addPlayerController(PlayerController* controller)
	{
		_allPlayerControllers.add(controller);
	}

	void SceneManager::addAiController(AiController* controller)
	{
		_allAiControllers.add(controller);
	}

	ITickable* SceneManager::removeTickable(ITickable* tickable)
	{
		_allTickables.removeElement(tickable);
		return tickable;
	}

	Grid3D<Actor*>& SceneManager::getSceneGraph()
	{
		return _sceneGraph;
	}

	void SceneManager::tick(float deltaTime)
	{
		int size = _allTickables.getSize();

		for (int i = 0; i < size; i++)
		{
			ITickable* tickable = _allTickables.get(i);
			PlayerController* playerController =
					static_cast<PlayerController*>(tickable);
			AiController* aiController = static_cast<AiController*>(tickable);

			if (playerController->canDelete())
			{
				Actor* removedActor = playerController->getActor();
				_allPlayerControllers.removeElement(playerController);
				removeActor(removedActor);
				removeTickable(tickable);
				size--;
				i--;
			}
			else if (aiController->canDelete())
			{

				Actor* removedActor = aiController->getActor();
				_allAiControllers.removeElement(aiController);
				removeActor(removedActor);
				removeTickable(tickable);
				size--;
				i--;
			}
			else
			{
				tickable->tick(deltaTime);
			}
		}
	}

	void SceneManager::input(DynamicArray<string>* args, float deltaTime)
	{
		string newState = args->get(0);

		if (newState == "focus")
		{
			if (args->getSize() == 2)
			{
				_focus = getControllerByActor(args->get(1));
				return;
			}
			else
			{
				cout << "Invalid arguments" << endl;
			}
		}
		else if (newState == "lose")
		{
			if (args->getSize() == 2 && args->get(1) == "focus")
			{
				_focus = NULL;
				return;
			}
			else
			{
				cout << "Invalid arguments" << endl;
			}
		}
		else if ((newState == "eat" || newState == "inventory") && _focus == NULL)
		{
			cout
					<< "Invalid input: Must be focused on a Dwarf to use this command."
					<< endl;
			return;
		}

		PlayerController* controller;

		if (_focus == NULL)
		{
			controller = this->findController(newState);
			if (controller == NULL)
			{
				return;
			}
		}
		else
		{
			controller = _focus;
			while (controller->runningStates().getSize() > 0)
			{
				controller->runningStates().remove(0);
			}
		}

		controller->input(args, deltaTime);
	}

	string SceneManager::toString()
	{
		return "";
	}

	PlayerController* SceneManager::findController(string command)
	{
		PlayerController* current;

		for (unsigned int i = 0; i < _allPlayerControllers.getSize(); i++)
		{
			current = _allPlayerControllers.get(i);
			DynamicArray<State*>& runningStates = current->runningStates();
			HashMap<State*>& allStates = current->allStates();

			if (current->numberOfStates() == 0)  //return *current
			{
				return current;
			}
			else if ((runningStates.getSize() == 1)
					&& ((runningStates.contains(allStates.getValue("drink")))
							|| (runningStates.contains(
									allStates.getValue("sing")))
							|| (runningStates.contains(
									allStates.getValue("sleep")))
							|| (runningStates.contains(
									allStates.getValue("idle")))))
			{
				runningStates.remove(0);
				return current;
			}

		}
		cout << "Sorry, all your dwarves are busy!" << endl;

		return NULL;
	}

	PlayerController* SceneManager::getControllerByActor(string name)
	{
		PlayerController* current;
		for (unsigned int i = 0; i < _allPlayerControllers.getSize(); i++)
		{
			current = _allPlayerControllers.get(i);
			if (current->getActor()->getName() == name)
			{
				cout << "Focused on " << name << "!" << endl;
				return current;
			}
		}
		cout << "A Dwarf by the name of " << name << " was not found." << endl;
		return NULL;
	}

}
