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

#include "Yuka/SceneObject.hh"

/* Protected constructor for Flexible objects */

Flexible::Flexible():
	Trait()
{
	m_behaviours.first = NULL;
	m_behaviours.last = NULL;
}

/* Protected destructor for Flexible objects */

Flexible::~Flexible()
{
	Behaviour *p, *next;
	
	for(p = m_behaviours.first; p; p = next)
	{
		next = p->m_next;
		p->detachFrom(this);
		p->m_prev = NULL;
		p->m_next = NULL;
		p->release();
	}
	m_behaviours.first = NULL;
	m_behaviours.last = NULL;
}

/* Add and remove behaviours. Note that doing so retains the behaviour, and
 * will also remove it from any other SceneObject that it is currently
 * attached to.
 */
void
Flexible::add(Behaviour *behaviour)
{
	Flexible *oldp;

	oldp = behaviour->owner();
	if(oldp && oldp == this)
	{
		/* This behaviour is already attached to this scene object */
		return;
	}
	if(oldp)
	{
		/* Remove the behaviour from the scene object it was previously
		 * attached to
		 */
		oldp->remove(behaviour);
	}
	/* Add the behaviour to our linked list */
	behaviour->retain();
	if(m_behaviours.first)
	{
		behaviour->m_prev = m_behaviours.last;
		m_behaviours.last->m_next = behaviour;
	}
	else
	{
		m_behaviours.first = behaviour;
	}
	m_behaviours.last = behaviour;
	/* Tell the behaviour that we're adding it to this flexible object */
	behaviour->attachTo(this);
}

void
Flexible::remove(Behaviour *behaviour)
{
	behaviour->detachFrom(this);
	behaviour->m_prev = NULL;
	behaviour->m_next = NULL;
	behaviour->release();
}

void
Flexible::dirty(void)
{
	m_traitFlags |= FlexibleTrait;
	dirtyParent();
}

void
Flexible::invalidate(void)
{
	m_traitFlags |= FlexibleTrait;
	invalidateDependents();
}

void
Flexible::update(void)
{
	Behaviour *p, *next;
	
	if(!(m_traitFlags & FlexibleTrait))
	{
		return;
	}
	m_traitFlags = AllTraits & ~FlexibleTrait;
	
	for(p = m_behaviours.first; p; p = next)
	{
		next = p->m_next;
		if(p->enabled())
		{
			p->update();
		}
	}
	
	updateDependents();
	
	m_traitFlags = NoTraits;
}

void
Flexible::dirtyParent(void)
{
}

void
Flexible::invalidateDependents(void)
{
}

void
Flexible::updateDependents(void)
{
}