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
 * MeleeWeapon header file.
 *
 */

#ifndef MELEEWEAPON_H_
#define MELEEWEAPON_H_

#include "../Interfaces/IWeaponType.h"
#include "../TestSuite/Time.h"
#include "../Resources/Constant.h"

namespace bammm
{
	class Actor;

	//TODO:This needs to implement IWeaponType
	//TODO: Why is this so different from RangedWeapon? This (and RangedWeapon) look incomplete. Not consistent with each other.
	class MeleeWeapon
	{
		protected:
			WeaponData _weaponData;
			uint _timer;
			Time _time;

		public:
			MeleeWeapon();
			MeleeWeapon(WeaponData weaponData);
			virtual ~MeleeWeapon();

			/**
			 attack
			 @Pre-Condition- No input
			 @Post-Condition- Attack is executed
			 */
			virtual int attack();

			/**
			 canAttack
			 @Pre-Condition- No input
			 @Post-Condition- Returns true if weapon can attack
			 */
			virtual bool canAttack();

			/**
			 getType
			 @Pre-Condition- No input
			 @Post-Condition- Returns a string containing the weapon type.
			 */
			virtual string getType();
	};
}

#endif
