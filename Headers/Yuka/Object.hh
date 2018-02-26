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

#include "Traits/Debuggable.hh"
#include "Traits/Scriptable.hh"
#include "Traits/Identifiable.hh"

#include "decl.h"

namespace Yuka
{
	/* Yuka::Object is a reference-counted base class which is used to
	 * implement most other types of object.
	 * 
	 * All Yuka::Object instances have the Debuggable, Scriptable and
	 * Identifable traits, which means that you can:
	 * - Inspect them to determine their type and properties
	 * - Set properties at runtime via Scriptable::set()
	 * - Set and retrieve an arbitrary numeric tag on each instance
	 * - Dump an object to a stream via <<
	 */
	class YUKA_EXPORT_ Object:
		public virtual Traits::Debuggable,
		public virtual Traits::Scriptable,
		public virtual Traits::Identifiable
	{
	public:
		/* Increment the reference count */
		virtual int retain(void);
		/* Decrement the reference count (will free the object when it reaches 0) */
		virtual int release(void);
	protected:
		/* Debuggable trait */
		virtual std::ostream &printProperties(std::ostream &stream) const;
	public:
		/* Identifiable trait */
		virtual std::string kind(void) const;
	protected:
		Object();
		Object(const Object &source);
		Object(const Object *source);
		virtual ~Object();
	private:
		unsigned long m_refcount;
	};

};

#endif /*!YUKA_OBJECT_HH_*/
