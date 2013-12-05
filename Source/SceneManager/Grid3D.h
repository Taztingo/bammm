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
 * Grid3D header file.
 *
 */

#ifndef GRID3D_H_
#define GRID3D_H_

#include <iostream>
#include <string>
#include "../Resources/DynamicArray.h"
#include "Vector3D.h"
#include "../Resources/Stack.h"
#include "../Actors/Actor.h"
#include "../Resources/Constant.h"
#include "../Resources/Color.h"
#include "../Resources/Tree.h"
#include "../Resources/TreeNode.h"
#include <math.h>

using namespace std;

namespace bammm
{
	template<typename T> class Grid3D
	{
		private:
			DynamicArray<DynamicArray<T>*>* _grid;
			int _width;
			int _length;
			int _height;

			/*
			 convertToPosition
			 @Pre-Condition- Takes a Vector3D vector
			 @Post-Condition- Converts it to an int representing a position in the grid
			 */
			int convertToPosition(Vector3D* vector);

			/*
			 * convertToVector
			 * @Pre-Condition- Takes integer
			 * @Post-Condition- Converts integer to vector3d
			 */
			Vector3D* convertToVector(int position);

		public:
			Vector3D* UP;
			Vector3D* DOWN;
			Vector3D* LEFT;
			Vector3D* RIGHT;
			Vector3D* ZERO;

			Grid3D();
			Grid3D(int width, int length, int height);
			~Grid3D();

			/*
			 setupDirections
			 @Pre-Condition- No input
			 @Post-Condition- Sets up directions
			 */
			void setupDirections();

			/*
			 access
			 @Pre-Condition- Takes in x,y,z  point system ( a vector)
			 @Post-Condition- Will return an array that represents the surrounding point
			 */
			DynamicArray<DynamicArray<T>*>* access(Vector3D *vector,
					int radius);

			/*
			 access
			 @Pre-Condition- Takes in an int x, y, and z
			 @Post-Condition- Returns location of that position on the grid
			 */
			DynamicArray<T>* access(int x, int y, int z);

			/*
			 add
			 @Pre-Condition- Takes in a vector an an object
			 @Post-Condition- The object is added to the grid at the given vector
			 */
			void add(Vector3D* vector, T object);

			/*
			 insert
			 @Pre-Condition- Takes a vector and and object to insert
			 @Post-Condition- Inserts object into the grid space
			 */
			void insert(Vector3D *vector, T object);

			/*
			 remove
			 @Pre-Condition- Takes in xyz coordinate (a vector)
			 @Post-Condition- Removes object specified by the coordinates
			 */
			bool remove(Vector3D *vector, T object);

			/*
			 * getPath
			 * @Pre-Condition- takes current Actor, destination string
			 * @Post-Condition- returns queue of directions
			 */
			Queue<Vector3D*>* getPath(Actor* actor, string destination);

			/*
			 findInGrid
			 @Pre-Condition- Takes an Actor*
			 @Post-Condition- Returns the Actor of the target's type.
			 */
			T findInGrid(string target);

			/*
			 findClosestInGrid
			 @Pre-Condition- Takes a unit to search from and target's type
			 @Post-Condition- Returns the Actor of the target's type.
			 */
			T findClosestInGrid(T unit, string target);

			/*
			 getDistance
			 @Pre-Condition- Takes two vector references
			 @Post-Condition- Returns the distance between two vectors
			 */
			float getDistance(Vector3D& vector1, Vector3D& vector2);
			
			/*
			 toString
			 @Pre-Condition- No input
			 @Post-Condition- Returns a string that represents the Grid3D
			 */
			string toString();

			/*
			 getEnemy
			 @Pre-Condition- Takes location and an actor
			 @Post-Condition- Returns that enemy on that location
			 */
			T getEnemy(Vector3D* location, T unit);

			/*
			 move
			 @Pre-Condition- Takes in an actor and a vector newLocation
			 @Post-Condition- The actor moves to the new location. newLocation will be deleted if the actor cannot move.
			 */
			void move(T actor, Vector3D* newLocation);

			/*
			 moveTowards
			 @Pre-Condition- Takes in the object being ordered and a vector newLocation
			 @Post-Condition- The ordered object is told to move towards the new location
			 */
			void moveTowards(T ordered, Vector3D* newLocation);

			/*
			 isWalkable
			 @Pre-Condition- Takes a location/vector
			 @Post-Condition- A boolean representing if the spot is walkable
			 */
			bool isWalkable(Vector3D location);

			/*
			 getX
			 @Pre-Condition- No input
			 @Post-Condition- Returns _x as an int
			 */
			int getX();

			/*
			 getY
			 @Pre-Condition- No input
			 @Post-Condition- Returns _y as an int
			 */
			int getY();

			/*
			 getZ
			 @Pre-Condition- No input
			 @Post-Condition- Returns _z as an int
			 */
			int getZ();
	};

	template<class T>
	Grid3D<T>::Grid3D()
	{
		_width = 0;
		_length = 0;
		_height = 0;
		_grid = new DynamicArray<DynamicArray<T>*>();

		setupDirections();

	}

	template<class T>
	Grid3D<T>::Grid3D(int width, int length, int height)
	{
		_width = width;
		_length = length;
		_height = height;
		_grid = new DynamicArray<DynamicArray<T>*>(_width * _length * _height);

		int size = _width * _length * _height;
		for (int i = 0; i < size; i++)
		{
			_grid->add(new DynamicArray<T>);
		}

		setupDirections();
	}

	template<class T>
	Grid3D<T>::~Grid3D()
	{
		int size = _width * _length * _height;
		for (int i = 0; i < size; i++)
		{
			delete _grid->get(i);
		}
		delete _grid;
	}

	template<class T>
	void Grid3D<T>::setupDirections()
	{
		UP = new Vector3D(-1, 0, 0);
		DOWN = new Vector3D(1, 0, 0);
		LEFT = new Vector3D(0,-1, 0);
		RIGHT = new Vector3D(0, 1, 0);
		ZERO = new Vector3D(0, 0, 0);
	}

	template<class T>
	DynamicArray<DynamicArray<T>*>* Grid3D<T>::access(Vector3D *vector,
			int radius)
	{
		int position = convertToPosition(vector);
		int start = position - radius;
		int end = position + radius;
		DynamicArray<DynamicArray<T>*>*space =
				new DynamicArray<DynamicArray<T>*>();
		if (start < 0)
		{
			start = 0;
		}
		if (end > (int) _grid->getCapacity())
		{
			end = _grid->getSize() - 1;
		}
		for (int i = start; i <= end; i++)
		{
			_grid->get(i);
			space->add(_grid->get(i));
		}
		return space;
	}

	template<class T>
	DynamicArray<T>* Grid3D<T>::access(int x, int y, int z)
	{
		int position = x + (y * _width) + (z * _width * _height);
		return _grid->get(position);
	}

	template<class T>
	void Grid3D<T>::add(Vector3D* vector, T object)
	{
		int position = convertToPosition(vector);
		_grid->get(position)->add(object);
		object->setLocation(vector);
	}

	template<class T>
	void Grid3D<T>::insert(Vector3D *vector, T object)
	{
		int position = convertToPosition(vector);
		_grid->get(position)->insert(position, object);
	}

	template<class T>
	bool Grid3D<T>::remove(Vector3D *vector, T object)
	{
		bool deletedValue = access(vector, 0)->get(0)->removeElement(object);
		return deletedValue;
	}

	template<class T>
	Queue<Vector3D*>* Grid3D<T>::getPath(Actor* actor, string destination)
	{
		Vector3D* target = findClosestInGrid(actor, destination)->getLocation();
		Vector3D* actorLocation = actor->getLocation();

		int actorLocInt = convertToPosition(actorLocation);

		DynamicArray<DynamicArray<bool>*>* visited = new DynamicArray<DynamicArray<bool>*>();

		for (uint i = 0; i < (uint)_width; i++)
		{
			visited->add(new DynamicArray<bool>());
			for (uint j= 0; j < (uint)_length; j++)
			{
				visited->get(i)->add(false);
			}
		}

		Tree<Vector3D*>* mapTree = new Tree<Vector3D*>();
		TreeNode<Vector3D*>* rootNode = NULL;
		mapTree->add(target, rootNode);


		TreeNode<Vector3D*>* current;
		TreeNode<Vector3D*>* foundActor;

		bool isFound = false;

		while (!mapTree->isEmpty())
		{
			current = mapTree->get();
			//Get location as vector and integer
			Vector3D* currentLocation = current->getValue();
			int currentLocInt = convertToPosition(currentLocation);


			//cout << currentLocation->getX() << ", " << currentLocation->getY() << endl;

			//Set current location to visited
			visited->get(currentLocation->getX())->get(currentLocation->getY()) = true;

			//If found
			if (currentLocInt == actorLocInt)
			{
				isFound = true;
				foundActor = current;
				break;
			}

			//Start adding if possible
			Vector3D newLoc1;
			bool hasVisited;

			//add UP to mapTree
			newLoc1 = *currentLocation + *UP;
			if (isWalkable(newLoc1))		//If not a ollision object
			{
				Vector3D* newLocation = new Vector3D(newLoc1.getX(), newLoc1.getY(), newLoc1.getZ());
				hasVisited = visited->get(newLocation->getX())->get(newLocation->getY());
				if (!hasVisited)			//If hasn't been visited
				{
					//cout << newLocation->getX() << ", " << newLocation->getY() << endl;
					visited->get(newLocation->getX())->get(newLocation->getY()) = true;
					mapTree->add(newLocation, current);
				}
			}

			//add RIGHT to mapTree
			Vector3D newLoc2 = *currentLocation + *RIGHT;
			if (isWalkable(newLoc2))		//If not a ollision object
			{
				Vector3D* newLocation = new Vector3D(newLoc2.getX(), newLoc2.getY(), newLoc2.getZ());
				hasVisited = visited->get(newLocation->getX())->get(newLocation->getY());
				if (!hasVisited)			//If hasn't been visited
				{
					//cout << newLocation->getX() << ", " << newLocation->getY() << endl;
					visited->get(newLocation->getX())->get(newLocation->getY()) = true;
					mapTree->add(newLocation, current);
				}
			}

			//add DOWN to mapTree
			Vector3D newLoc3 = *currentLocation + *DOWN;
			if (isWalkable(newLoc3))			//If not a ollision object
			{
				Vector3D* newLocation = new Vector3D(newLoc3.getX(), newLoc3.getY(), newLoc3.getZ());
				hasVisited = visited->get(newLocation->getX())->get(newLocation->getY());
				if (!hasVisited)				//If hasn't been visited
				{
					//cout << newLocation->getX() << ", " << newLocation->getY() << endl;
					visited->get(newLocation->getX())->get(newLocation->getY()) = true;
					mapTree->add(newLocation, current);
				}
			}

			//add LEFT to mapTree
			Vector3D newLoc4 = *currentLocation + *LEFT;
			if (isWalkable(newLoc4))			//If not a ollision object
			{
				Vector3D* newLocation = new Vector3D(newLoc4.getX(), newLoc4.getY(), newLoc4.getZ());
				hasVisited = visited->get(newLocation->getX())->get(newLocation->getY());
				if (!hasVisited)				//If hasn't been visited
				{
					//cout << newLocation->getX() << ", " << newLocation->getY() << endl;
					visited->get(newLocation->getX())->get(newLocation->getY()) = true;
					mapTree->add(newLocation, current);
				}
			}
		}


		//Building Queue---------------------------------------

		Queue<Vector3D*>* path = new Queue<Vector3D*>();
		current = foundActor;

		if (isFound)
		{
			Vector3D* currentVector;
			while(foundActor != NULL)
			{
				currentVector = foundActor->getValue();
				path->add(currentVector);
				foundActor = foundActor->getParent();

			}
		}
		return path;
	}


	template<class T>
	T Grid3D<T>::findInGrid(string target)
	{
		for (uint gridIndex = 0; gridIndex < _grid->getSize(); gridIndex++)
		{
			DynamicArray<T>* cell = _grid->get(gridIndex);
			for (uint cellIndex = 0; cellIndex < cell->getSize(); cellIndex++)
			{
				T actor = cell->get(cellIndex);
				//if (actor->toString() == target)
				if (actor->toString().find(target)!=string::npos)
				{
					return actor;
				}
			}
		}
		return NULL;
	}

	template<class T>
	T Grid3D<T>::findClosestInGrid(T unit, string target)
	{
		T closest = NULL;
		float minDistance = 1000;
		for (uint gridIndex = 0; gridIndex < _grid->getSize(); gridIndex++)
		{
			DynamicArray<T>* cell = _grid->get(gridIndex);
			for (uint cellIndex = 0; cellIndex < cell->getSize(); cellIndex++)
			{
				T actor = cell->get(cellIndex);
				if (actor->toString().find(target)!=string::npos)
				{
					float distance = getDistance(*unit->getLocation(), *actor->getLocation());
					if(distance < minDistance && !(unit == actor))
					{
						closest = actor;
					}
				}
			}
		}
		return closest;
	}

	template<class T>
	float Grid3D<T>::getDistance(Vector3D& vector1, Vector3D& vector2)
	{
		float x = pow(vector1.getX() - vector2.getX(), 2);
		float y = pow(vector1.getY() - vector2.getY(), 2);
		float z = pow(vector1.getZ() - vector2.getZ(), 2);

		return sqrt(x+y+z);
	}

	template<class T>
	string Grid3D<T>::toString()
	{
		string gridString = "";

		for (int y = 0; y < _length; y++)
		{
			for (int x = 0; x < _width; x++)
			{
				DynamicArray<T>* atLocation;
				atLocation = access(x, y, 0);

				if (atLocation->getSize() <= 0)
				{
					gridString = gridString + Color::colorText(". ", "green");
				}
				else
				{
					int size = atLocation->getSize() - 1;
					string symbol = atLocation->get(size)->getSymbol();
					string color = atLocation->get(size)->getColor();
					gridString = gridString + Color::colorText(symbol, color)
							+ " ";
				}
			}
			gridString = gridString + "\n";
		}

		return gridString;
	}

	template<class T>
	T Grid3D<T>::getEnemy(Vector3D* location, T unit)
	{
		DynamicArray<DynamicArray<T>*>* tiles = access(location, 0);
		DynamicArray<T>* allOnTile = tiles->get(0);
		int actorEnemyAlliance = unit->getEnemyAlliance();

		for (int i = 0; i < (int) allOnTile->getSize(); i++)
		{
			Actor* otherActor = allOnTile->get(i);
			if (actorEnemyAlliance == otherActor->getAlliance())
			{
				delete tiles;
				return otherActor;
			}
		}

		delete tiles;
		return NULL;
	}

	template<class T>
	void Grid3D<T>::move(T actor, Vector3D* newLocation)
	{
		if (isWalkable(*newLocation))
		{
			remove(actor->getLocation(), actor);
			delete actor->getLocation();
			add(newLocation, actor);
		}
		else
		{
			//delete newLocation;
		}
	}

	template<class T>
	bool Grid3D<T>::isWalkable(Vector3D location)
	{
		//Checks for in grid bounds
		if (location.getX() < 0 || location.getY() < 0 || location.getZ() < 0)
		{
			return false;
		}

		//Checks for in grid bounds
		if (location.getX() >= _width || location.getY() >= _length
				|| location.getZ() >= _height)
		{
			return false;
		}

		//int radius = 0;
		DynamicArray<DynamicArray<T>*>* tiles = access(&location, 0);
		DynamicArray<T>* allOnTile = tiles->get(0);
		int size = allOnTile->getSize();
		for (int i = 0; i < size; i++)
		{
			if (allOnTile->get(i)->getCollision() == 1)
			{
				return false;
			}
		}

		return true;
	}

	template<class T>
	void Grid3D<T>::moveTowards(T ordered, Vector3D* newLocation)
	{
		Vector3D* orderedLocation = ordered->getLocation();
		Vector3D* targetLocation = newLocation;

		bool sameX = orderedLocation->getX() == targetLocation->getX();
		bool sameY = orderedLocation->getY() == targetLocation->getY();
		bool orderedXLess = orderedLocation->getX() < targetLocation->getX();
		bool orderedXGreater = orderedLocation->getX() > targetLocation->getX();
		bool orderedYLess = orderedLocation->getY() < targetLocation->getY();
		bool orderedYGreater = orderedLocation->getY() > targetLocation->getY();

		float newX;
		float newY;

		if (sameX && sameY)
		{
			return;
		}
		else if (sameX)
		{
			if (orderedYLess)
			{
				newY = orderedLocation->getY() + 1;
			}
			else
			{
				newY = orderedLocation->getY() - 1;
			}

			newX = orderedLocation->getX();
		}
		else if (sameY)
		{
			if (orderedXLess)
			{
				newX = orderedLocation->getX() + 1;
			}
			else
			{
				newX = orderedLocation->getX() - 1;
			}

			newY = orderedLocation->getY();
		}
		else
		{
			if (orderedXLess && orderedYLess)
			{
				newX = orderedLocation->getX() + 1;
				newY = orderedLocation->getY() + 1;
			}
			else if (orderedXLess && orderedYGreater)
			{
				newX = orderedLocation->getX() + 1;
				newY = orderedLocation->getY() - 1;
			}
			else if (orderedXGreater && orderedYLess)
			{
				newX = orderedLocation->getX() - 1;
				newY = orderedLocation->getY() + 1;
			}
			else if (orderedXGreater && orderedYGreater)
			{
				newX = orderedLocation->getX() - 1;
				newY = orderedLocation->getY() - 1;
			}
		}
		newLocation = new Vector3D(newX, newY, 0);
		move(ordered, newLocation);
	}

	template<class T>
	int Grid3D<T>::getX()
	{
		return _width;
	}

	template<class T>
	int Grid3D<T>::getY()
	{
		return _length;
	}

	template<class T>
	int Grid3D<T>::getZ()
	{
		return _height;
	}

	template<class T>
	int Grid3D<T>::convertToPosition(Vector3D* vector)
	{
		return vector->getX() + (vector->getY() * _width)
				+ (vector->getZ() * _width * _height);
	}

	template<class T>
	Vector3D* Grid3D<T>::convertToVector(int position)
	{
		int z = (position - (position % (_length * _width)))/(_length * _width);
		int y = position / _length;
		int x = position % _length;
		return new Vector3D(x, y, z);
	}
}

#endif
