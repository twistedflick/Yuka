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

#ifndef YUKA_EVENTS_EVENT_HH_
# define YUKA_EVENTS_EVENT_HH_         1

# include "../Traits/Debuggable.hh"
# include "../decl.h"

# define MakeEvent(eclass, ekind, flags) \
	(((flags) & 0xffff) << 16) | \
	(((eclass) & 0xff) << 8) | \
	((ekind) & 0xff)

# define MakeEventType(eclass, ekind) \
	(((eclass) & 0xff) << 8) | ((ekind) & 0xff)

namespace Yuka
{
	namespace Traits
	{
		class Observable;
	}
	
	namespace Events
	{
		/* An EventType is a 32-bit unsigned integer structured as:
		 *
		 * {EventFlags:16} {EventClass:8} {EventKind:8}
		 *
		 * The EventKind is specific to each EventClass; for example,
		 * EventKind = 0 for EventClass = EV_System is different to
		 * EventKind = 0 for EventClass = EV_Scene. For this reason,
		 * accessors always return either EventClass alone, or
		 * (EventClass << 8) | EventKind together.
		 *
		 * EventFlags are common to all kinds of events (although some
		 * combinations of flags and events may not necessarily occur
		 * in practice)
		 */
		typedef unsigned EventType;
		typedef unsigned EventKind;

		const EventType EventClassMask = 0x0000ff00;
		const EventType EventKindMask = 0x0000ffff;
		const EventType EventFlagsMask = 0xffff0000;

		typedef enum
		{
			UserEvents = 0x00,
			UserEventsMax = 0x9F,
			SystemEvents = 0xA0,
			SceneEvents = 0xA1,
			RenderEvents = 0xA2,
			PhysicsEvents = 0xA3,
			InteractionEvents = 0xB0
		} EventClass;
		
		typedef enum
		{
			NoFlags = 0x0000,
			CancellableFlag = 0x0001,
			CancelledFlag = 0x0021,
			BubbleFlag = 0x0040,
			CascadeFlag = 0x0080
		} EventFlags;
		
		/* Events are simple structures which are passed from Observable
		 * to Listening objects.
		 */
		struct YUKA_EXPORT_ Event:
			public virtual Yuka::Traits::Debuggable
		{
			friend class Yuka::Traits::Observable;
			
			EventType eventType;
			Yuka::Traits::Observable *source;
			void *userData;
			
		protected:
			Event(Yuka::Traits::Observable *source, EventType type);
			Event(Yuka::Traits::Observable *source, EventType type, EventFlags flags);
		public:
			virtual std::string eventName(void) const;
			
			virtual EventClass eventClass(void) const
			{
				return (EventClass) ((eventType & EventClassMask) >> 8);
			};

			virtual EventKind eventKind(void) const
			{
				return (EventKind) (eventType & EventKindMask);
			};
			
			virtual EventFlags eventFlags(void) const
			{
				return (EventFlags) ((eventType & EventFlagsMask) >> 16);
			};
			
		protected:
			virtual void resetFlags(void)
			{
				eventType &= 0xffff;
			}
			
			virtual void setFlag(EventFlags flag)
			{
				eventType |= ((flag & 0xffff) << 16);
			}

			virtual void clearFlag(EventFlags flag)
			{
				eventType &= ((~(flag & 0xffff)) << 16) | 0xffff;
			}
			
		protected:
			/* Debuggable trait */
			virtual std::ostream &print(std::ostream &stream) const;
			virtual std::ostream &printProperties(std::ostream &stream) const;
		};

	};
};

#endif /*!YUKA_EVENTS_EVENT_HH_*/
