/*
 * JSONArray.h
 *
 *  Created on: Nov 19, 2013
 *      Author: michael
 *
 *      DOCUMENTATION
 *
 *      Inherits from JSON
 *      Represents an Array in JSON
 *      May hold any JSON Object including JSONPrimitive and JSONArray
 *      Stores JSON Objects in a DynamicArray
 *
 */

#ifndef JSONARRAY_H_
#define JSONARRAY_H_

#include "../Resources/DynamicArray.h"
#include "JSON.h"

namespace bammm
{

	class JSONArray: public JSON
	{

		private:

			DynamicArray<JSON> _children;

		public:

			JSONArray();
			JSONArray(string);
			JSONArray(string, JSON*);

			~JSONArray();

			void addChild(JSON &);

			JSON operator[](const unsigned int & rhs);

	};

}
#endif /* JSONARRAY_H_ */
