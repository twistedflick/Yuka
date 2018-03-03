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

#ifndef YUKA_BEHAVIOURS_SPY_HH_
# define YUKA_BEHAVIOURS_SPY_HH_       1

#include "../Behaviour.hh"
#include "../decl.h"

namespace Yuka
{
	namespace Events
	{
		struct Event;
	};
	
	namespace Traits
	{
		class Identifiable;
		class Flexible;
	};
	
	namespace Behaviours
	{
		/* The Spy behaviour is used for event debugging - any event
		 * emitted by its owner (provided it's Observable) will be
		 * logged by the Spy.
		 */
		class YUKA_EXPORT_ Spy:
			public Yuka::Behaviour
		{
		public:
			Spy();
			virtual ~Spy();
		protected:
			const Traits::Identifiable *m_id;
			char m_ownername[32];
		protected:
			/* Behaviour overrides */
			virtual void ownerChangedTo(Traits::Flexible *obj);
		protected:
			/* Listening trait (via Behaviour) */
			virtual bool process(Yuka::Events::Event *ev);
		public:
			/* Identifiable trait (via Behaviour) */
			virtual std::string kind(void) const;
			
		};
	};
};

#endif /*!YUKA_BEHAVIOURS_SPY_HH_*/
