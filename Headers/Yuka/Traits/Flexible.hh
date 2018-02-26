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
		class Debuggable;

		const IdentityFlag FlexibleTrait = 0x00000008;
		
		/* Classes with the Flexible trait can have behaviours attached
		 * to them.
		 *
		 * Subclasses of Flexible support specific interactions with
		 * certain classes of behaviour. For example, the Transform behaviour
		 * interacts with the Moveable trait, which is a subclass of
		 * Controllable.
		 */
		class YUKA_EXPORT_ Flexible:
			public virtual Trait
		{
			friend class Yuka::Behaviour;
			friend class Debuggable;
		public:
			/* Add a behaviour to this object */
			virtual void add(Behaviour *behaviour);
		
			/* Remove a behaviour from this object */
			virtual void remove(Behaviour *behaviour);
			
			/* Mark this object, and any descendants, as being invalidated
			 * and needing to be updated by their behaviours
			 */
			virtual void invalidate(void);
		protected:
			Flexible();
			virtual ~Flexible();
		protected:
			struct
			{
				Behaviour *first;
				Behaviour *last;
			} m_behaviours;

			/* Invoked by a behaviour to indicate that the behaviour chain
			 * is dirty.
			 */
			virtual void dirty(void);
			
			/* Update our state using our list of behaviours */
			virtual void update(void);
			/* Mark our parent/owner as dirty */
			virtual void dirtyParent(void);
			/* Mark any dependent objects as invalidated */
			virtual void invalidateDependents(void);
			/* Ask any dependent objects to update */
			virtual void updateDependents(void);
		};
	};
};

#endif /*!YUKA_TRAITS_FLEXIBLE_HH_*/
