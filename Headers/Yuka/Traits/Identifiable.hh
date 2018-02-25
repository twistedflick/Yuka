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

#ifndef YUKA_TRAITS_IDENTIFIABLE_HH_
# define YUKA_TRAITS_IDENTIFIABLE_HH_  1

# include "../Trait.hh"
# include "../decl.h"

namespace Yuka
{
	class Behaviour;
	
	namespace Traits
	{
		/* Classes with the Identifiable trait provide properties allowing them
		 * to be inspected at run-time.
		 */
		class YUKA_EXPORT_ Identifiable: public Trait
		{
		public:
			/* Return a numeric instance identifier for this object, guaranteed
			 * to be unique amongst all other instances currently
			 * in existence.
			 *
	 		 * Note that instance identifiers are as temporary as the objects
	 		 * themselves and may be reused once an object has been freed.
			 */
			virtual unsigned long instanceId(void) const;
			virtual std::string instanceString(void) const;
		
			/* Return the kind of object that this is */
			virtual std::string kind(void) const;

			/* Return the (verbose) internal kind of object that this is */
			virtual std::string internalKind(void) const;
		
			/* Return the name of this object, if any */
			virtual std::string name(void) const;
		
			/* Return consise qualified display name of this object */
			virtual std::string displayName(void) const;
		
			/* Return the 'live' internal name of this object */
			virtual std::string internalName(void) const;
			
			/* Return an arbitrary integer tag which can be associated with the
			 * object.
			 */
			virtual int tag(void) const;
			/* Set the arbitrary integer tag for an object */
			virtual void setTag(int newTag);
			virtual bool setTag(const std::string tag);
		protected:
			Identifiable();
			Identifiable(const Identifiable &src);
			Identifiable(const Identifiable *src);
		private:
			int m_tag;
		};
	}
};

#endif /*!YUKA_TRAITS_IDENTIFIABLE_HH_*/
