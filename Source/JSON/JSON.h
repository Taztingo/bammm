/*
 * JSON.h
 *
 *  Created on: Nov 19, 2013
 *      Author: michael
 */

#ifndef JSON_H_
#define JSON_H_

#include <string>
#include "../Resources/HashMap.h"

namespace bammm
{
	enum JSON_TYPE
	{
		JSON_NULL,
		JSON_ARRAY,
		JSON_STRING,
		JSON_INT,
		JSON_DOUBLE,
		JSON_BOOL,
		JSON_OBJECT
	};

	class JSON
	{

		protected:

			string _name;
			JSON_TYPE _type;
			JSON *_parent;
			HashMap<JSON*> _children;

		public:

			JSON();
			JSON(string);
			~JSON();

			/*
			 getName
			 @Pre-Condition-  Takes no argument
			 @Post-Condition- returns the name (key) of this JSON Node
			 */
			string getName();

			/*
			 getType
			 @Pre-Condition-  Takes no argument
			 @Post-Condition- returns the JSON_TYPE of this JSON Node
			 */
			JSON_TYPE getType();

			/*
			 getParent
			 @Pre-Condition-  Takes no argument
			 @Post-Condition- returns the parent of this JSON Node
			 */
			JSON * getParent();

			/*
			 setName
			 @Pre-Condition-  Takes a string argument
			 @Post-Condition- sets this JSON Nodes name equal to the string argument. Returns void.
			 */
			void setName(string);

			/*
			 setType
			 @Pre-Condition-  Takes a JSON_TYPE argument
			 @Post-Condition- sets this JSON Nodes JSON_TYPE equal to the JSON_TYPE argument. Returns void.
			 */
			void setType(JSON_TYPE);

			void setParent(JSON &);

			void addChild(JSON &);

	};

}

#endif /* JSON_H_ */
