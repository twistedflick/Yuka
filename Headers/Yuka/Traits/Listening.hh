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

#ifndef YUKA_TRAITS_LISTENING_HH_
# define YUKA_TRAITS_LISTENING_HH_     1

# include "../Trait.hh"
# include "../decl.h"

namespace Yuka
{
	namespace Events
	{
		struct Event;
	};
	
	namespace Traits
	{
		class Observable;
		
		const IdentityFlag ListeningTrait = 0x00000080;
		
		/* Observable objects are those that receive events */
		class YUKA_EXPORT_ Listening:
			public virtual Trait
		{
			friend class Yuka::Traits::Observable;
		protected:
			virtual bool process(Yuka::Events::Event *event);
		};
	}
};

#endif /*!YUKA_TRAITS_LISTENING_HH_*/
