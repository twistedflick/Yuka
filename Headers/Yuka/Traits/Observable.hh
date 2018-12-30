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

#ifndef YUKA_TRAITS_OBSERVABLE_HH_
# define YUKA_TRAITS_OBSERVABLE_HH_    1

# include "Trait.hh"
# include "../Events/Event.hh"
# include "../decl.h"

namespace Yuka
{
	namespace Traits
	{
		class Debuggable;
		class Listening;
		
		const Identity ObservableTrait = 0x00000040;
		
		/* Observable objects are those that can emit events */
		class YUKA_EXPORT_ Observable:
			public virtual Trait
		{
		public:
			/* Attach a listener to a specific event */
			virtual void on(Yuka::Events::EventKind what, Listening *listener);
		protected:
			/* Deliver an event to all listeners registered for it */
			virtual bool emit(Yuka::Events::Event *ev);
			virtual bool emit(Yuka::Events::Event &ev);
			/* Deliver an event to a specific listener */
			virtual bool deliver(Yuka::Events::Event *ev, Listening *listener);
		protected:
			Observable();
			virtual ~Observable();
		private:
			struct ObservableData *m_observable = NULL;
			void initObservable(void);
		};
	}
};

#endif /*!YUKA_TRAITS_OBSERVABLE_HH_*/
