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

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "p_YukaEvents.hh"

/* Protected constructors for event types */

Event::Event(Yuka::Traits::Observable *sender, EventType type):
	eventType(type),
	source(sender),
	userData(NULL)
{
}

Event::Event(Yuka::Traits::Observable *sender, EventType type, EventFlags flags):
	eventType(((flags & 0xffff) << 16) | (type & 0xffff)),
	source(sender),
	userData(NULL)
{
}

/* Determine a name for this event */

std::string
Event::eventName(void) const
{
	EventClass c = eventClass();
	switch(c)
	{
		case SystemEvents:
			return "System";
		case SceneEvents:
			return "Scene";
		case RenderEvents:
			return "Render";
		case PhysicsEvents:
			return "Physics";
		case InteractionEvents:
			return "Interaction";
		default:
			if(c >= UserEvents && c <= UserEventsMax)
			{
				return "User";
			}
			return "Event";
	}
}

/** Debuggable trait **/

std::ostream &
Event::print(std::ostream &stream) const
{
	std::string indent = printIndent();

	stream << "Events::" << eventName() << " = {\n";
	printPush();
	printProperties(stream);
	printPop();
	stream << indent << "}";
	return stream;
}

std::ostream &
Event::printProperties(std::ostream &stream) const
{
	EventClass ec = eventClass();
	std::string indent = printIndent();
	const Yuka::Traits::Identifiable *identifiable = dynamic_cast<const Yuka::Traits::Identifiable *>(source);
	
	switch(ec)
	{
		case SystemEvents:
			stream << indent << ".eventClass = SystemEvents;\n";
			break;
		case SceneEvents:
			stream << indent << ".eventClass = SceneEvents;\n";
			break;
		case PhysicsEvents:
			stream << indent << ".eventClass = PhysicsEvents;\n";
			break;
		case RenderEvents:
			stream << indent << ".eventClass = RenderEvents;\n";
			break;
		case InteractionEvents:
			stream << indent << ".eventClass = InteractionEvents;\n";
			break;
		default:
			if(ec >= UserEvents && ec <= UserEventsMax)
			{
				stream << indent << ".eventClass = (UserEvents + " << (ec - UserEvents) << ")";
			}
			else
			{
				stream << indent << ".eventClass = " << eventClass() << ";\n";
			}
	}
	stream << indent << ".eventKind = " << eventKind() << ";\n";
	stream << indent << ".eventFlags = " << eventFlags() << ";\n";
	
	if(identifiable)
	{
		stream << indent << ".source = " << identifiable->internalName() << ";\n";
	}
	else if(source)
	{
		stream << indent << ".source = Observable;\n";	
	}
	else
	{
		stream << indent << ".source = nil;\n";
	}
	return stream;
}
