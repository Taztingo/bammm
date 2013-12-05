#
#makefile for Game
#

RM = rm -f
SRCPATH = .
SRC = Behavior/Behavior.cpp LevelingSystem/LevelingSystem.cpp Actors/Actor.cpp Actors/ActorInfo.cpp \
Controllers/AiController.cpp Controllers/Controller.cpp Controllers/PlayerController.cpp \
States/BrawlState.cpp States/DrinkState.cpp States/MoveState.cpp \
States/IdleState.cpp Interfaces/IStateCallback.cpp States/CombatState.cpp \
States/SingState.cpp States/SleepState.cpp States/State.cpp States/StateMachine.cpp \
<<<<<<< HEAD
States/DamageState.cpp States/SearchState.cpp States/CraftState.cpp  States/ChopState.cpp\
=======
States/DamageState.cpp States/SearchState.cpp States/GatherState.cpp \
States/EatState.cpp \
>>>>>>> refs/heads/master
\
Resources/DynamicArray.h Resources/HashMap.h Resources/HashNode.h \
Resources/Heap.h Resources/Queue.h Resources/Stack.h Resources/Color.cpp \
Resources/TreeNode.h Resources/Tree.h \
\
Weapons/WeaponData.cpp Weapons/MeleeWeapon.cpp Weapons/RangedWeapon.cpp \
Interfaces/IWeaponType.h Weapons/MeleeCombat.cpp \
\
SceneManager/Vector3D.cpp SceneManager/Grid3D.h SceneManager/SceneManager.cpp  \
Factories/Factory.cpp \
Interfaces/ITickable.cpp \
JSON/JSON.cpp JSON/JSONParser.cpp JSON/JSONArray.cpp \
JSON/JSONPrimitive.cpp \
\
TestSuite/Time.cpp \
\
Inventory/Item.cpp Inventory/Inventory.cpp
TESTNAME = test
TESTSRC = Main.cpp

all: re $(SRC) $(TESTSRC)
	g++ $(SRC) $(TESTSRC) -Wall -Werror -std=c++0x -o $(TESTNAME)

debug: re $(SRC) $(TESTSRC)
	g++ $(SRC) $(TESTSRC) -Wall -Werror -std=c++0x -o $(TESTNAME) -g

retest: re test

clean:
	-$(RM) *.o
	-$(RM) *~
	-$(RM) \#*
	-$(RM) *.core
	-$(RM) *.gch

fclean: clean
	-$(RM) $(TESTNAME)

re: fclean

test: fclean $(TESTSRC)
	g++ $(TESTSRC) -Wall -Werror -std=c++0x -o $(TESTNAME)
