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

#ifndef YUKA_TRAIT_HH_
# define YUKA_TRAIT_HH_                1

#include "../decl.h"

namespace Yuka
{
	namespace Traits
	{
		/* This is a bitfield type that will be used by individual traits to
		 * control how they interact with behaviours.
		 */
		typedef unsigned Identity;
		
		const Identity AllTraits = (Identity) -1;
		const Identity NoTraits = 0;

		/* Traits are base classes which can be inherited-from to provide
		 * certain kinds of capabilities. For example, objects which can
		 * be moved around will have the Moveable trait. Objects that can
		 * have Behaviours attached will have the Flexible trait.
		 */

		class YUKA_EXPORT_ Trait
		{
		protected:
			Trait();
			~Trait();
		public:
			virtual Traits::Identity traits(void) const;
			virtual bool is(Traits::Identity trait) const;
		protected:
			Traits::Identity m_traits;
			Traits::Identity m_traitFlags;
		};
	};
};

#endif /*!YUKA_TRAIT_HH_*/
