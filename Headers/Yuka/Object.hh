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
	 * implement every other type of object.
	 */
	class YUKA_EXPORT_ Object:
		public Traits::Debuggable,
		public Traits::Scriptable,
		public Traits::Identifiable
	{
	public:
		/* Increment the reference count */
		virtual int retain(void);
		/* Decrement the reference count (will free the object when it reaches 0) */
		virtual int release(void);
		
		/* Return an arbitrary integer tag which can be associated with the
		 * object.
		 */
		virtual int tag(void) const;
		/* Set the arbitrary integer tag for an object */
		virtual void setTag(int newTag);
		virtual bool setTag(const std::string tag);
	protected:
		/* Debuggable trait */
		virtual std::ostream &printProperties(std::ostream &stream) const;
	public:
		/* Scriptable trait */
		virtual bool set(const std::string key, const std::string value);
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
		int m_tag;
	};

};

#endif /*!YUKA_OBJECT_HH_*/
