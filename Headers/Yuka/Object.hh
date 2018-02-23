/* Copyright 2018 Mo McRoberts.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifndef YUKA_OBJECT_HH_
# define YUKA_OBJECT_HH_               1

#include <iostream>
#include <string>
#include <unordered_map>

#include "decl.h"

namespace Yuka
{
	/* Yuka::Object is a reference-counted base class which is used to
	 * implement every other type of object.
	 */
	class YUKA_EXPORT_ Object
	{
	public:
		/* Increment the reference count */
		virtual int retain(void);
		/* Decrement the reference count (will free the object when it reaches 0) */
		virtual int release(void);
		
		/* Return a numeric instance identifier for this object, guaranteed
		 * to be unique amongst all other Yuka::Object instances currently
		 * in existence.
		 *
		 * Note that instance identifiers are as temporary as the objects
		 * themselves and may be reused once an object has been freed.
		 */
		virtual unsigned long instanceId(void) const;
		
		/* Return an arbitrary integer tag which can be associated with the
		 * object.
		 */
		virtual int tag(void) const;
		/* Set the arbitrary integer tag for an object */
		virtual void setTag(int newTag);
	protected:
		Object();
		Object(const Object &source);
		Object(const Object *source);
		virtual ~Object();
		
		friend YUKA_EXPORT_ std::ostream& operator<<(std::ostream &os, const Object *me);
		friend YUKA_EXPORT_ std::ostream& operator<<(std::ostream &os, const Object &me);
	private:
		unsigned long m_refcount;
		int m_tag;
	};

};

#endif /*!YUKA_OBJECT_HH_*/
