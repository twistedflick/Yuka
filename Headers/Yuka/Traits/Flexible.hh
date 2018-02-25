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

#ifndef YUKA_TRAITS_FLEXIBLE_HH_
# define YUKA_TRAITS_FLEXIBLE_HH_      1

# include "../Trait.hh"
# include "../decl.h"

namespace Yuka
{
	class Behaviour;

	namespace Traits
	{
	
		/* Classes with the Flexible trait can have behaviours attached
		 * to them.
		 *
		 * Subclasses of Flexible support specific interactions with
		 * certain classes of behaviour. For example, the Transform behaviour
		 * interacts with the Moveable trait, which is a subclass of
		 * Controllable.
		 */
		class YUKA_EXPORT_ Flexible: public Trait
		{
			friend class Yuka::Behaviour;
		public:
			/* Add a behaviour to this object */
			virtual void add(Behaviour *behaviour) = 0;
		
			/* Remove a behaviour from this object */
			virtual void remove(Behaviour *behaviour) = 0;
		protected:
		};
	}
};

#endif /*!YUKA_TRAITS_FLEXIBLE_HH_*/
