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

#include "p_YukaTraits.hh"

/* Protected destructor */
Observable::~Observable()
{
	delete m_observable;
}

/* Construct our private ObservableData */
void
Observable::initObservable()
{
	if(m_observable)
	{
		return;
	}
	m_observable = new ObservableData(this);
}

/* Attach a listener to a specific event */
void
Observable::on(Yuka::Events::EventKind what, Listening *listener)
{
	ListenerVector *vec;
	
	initObservable();
	
	vec = m_observable->vectorFor(what, true);
	vec->push_back(listener);
}

/* Deliver an event to all listeners registered for it */
bool
Observable::emit(Yuka::Events::Event *ev)
{
	ListenerVector *vec;
	
	/* If <this> also has the Flexible trait, deliver the event to all of
	 * our attached behaviours
	 */
	initObservable();
	if(m_observable->flex)
	{
		Behaviour *p, *next;
	
		/* Our behaviours are always listeners for events we emit */
		for(p = m_observable->flex->m_behaviours.first; p; p = next)
		{
			next = p->next();
			if(!p->enabled())
			{
				continue;
			}
			/* For the moment, ignore the result - in future this may, depending
			 * upon the event flags, allow the event to be canceled conditionally.
			 */
			deliver(ev, p);
		}
	}
	/* Next, send the event to all of our registered listeners */
	if((vec = m_observable->vectorFor(ev->eventKind())))
	{
		ListenerVector::iterator i;
		
		for(i = vec->begin(); i != vec->end(); ++i)
		{
			deliver(ev, *i);
		}
	}
	return true;
}

bool
Observable::emit(Yuka::Events::Event &ev)
{
	return emit(&ev);
}

bool
Observable::deliver(Yuka::Events::Event *ev, Listening *listener)
{
	return listener->process(ev);
}

/* ObservableData implementation */

ObservableData::ObservableData(Observable *owner):
	flex(dynamic_cast<Flexible *>(owner)),
	map()
{
}

ListenerVector *
ObservableData::vectorFor(Events::EventKind what, bool shouldCreate)
{
	ListenerMap::iterator i;
		
	if(shouldCreate)
	{
		return &(map[what]);
	}
	i = map.find(what);
	if(i == map.end())
	{
		return NULL;
	}
	return &(i->second);
}
