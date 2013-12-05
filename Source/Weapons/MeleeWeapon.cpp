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
 * MeleeWeapon cpp file.
 *
 */

#include "MeleeWeapon.h"

namespace bammm
{
	MeleeWeapon::MeleeWeapon()
	{
		_timer = 0;
	}

	MeleeWeapon::MeleeWeapon(WeaponData weaponData)
	{
		_weaponData = weaponData;
		_timer = 0;
	}

	MeleeWeapon::~MeleeWeapon()
	{
	}

	int MeleeWeapon::attack()
	{
		_time = _time.current();
		_timer = _time.getSeconds() + _weaponData.getFireRate();
		return _weaponData.getDamage();
	}

	bool MeleeWeapon::canAttack()
	{
		_time = _time.current();
		if (_time.getSeconds() < _timer)
		{
			return false;
		}
		return true;
	}

	string MeleeWeapon::getType()
	{
		return _weaponData.getType();
	}
}
