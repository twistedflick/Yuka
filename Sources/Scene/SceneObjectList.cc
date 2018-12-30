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

#include "p_YukaScene.hh"

/* Implements the private SceneObject::List class */

SceneObject::List::List() :
	Object(),
	first(NULL),
	last(NULL)
{	
}

SceneObject::List::~List()
{
	List::Entry *e, *next;

	for(e = first; e; e = next)
	{
		next = e->next;
		e->obj->release();
		delete e;
	}
}

bool
SceneObject::List::push(SceneObject *object)
{
	List::Entry *e;
	
	e = new List::Entry();
	e->next = NULL;
	e->prev = last;
	object->retain();
	e->obj = object;
	if(first)
	{
		last->next = e;
	}
	else
	{
		first = e;
	}
	last = e;
	return true;
}

bool
SceneObject::List::has(const SceneObject *object) const
{
	List::Entry *p;
	
	for(p = first; p; p = p->next)
	{
		if(p->obj == object)
		{
			return true;
		}
	}
	return false;
}

bool
SceneObject::List::remove(const SceneObject *object)
{
	List::Entry *p;
	
	for(p = first; p; p = p->next)
	{
		if(p->obj == object)
		{
			p->obj->release();
			if(first == p)
			{
				first = first->next;
			}
			if(last == p)
			{
				last = last->prev;
			}
			if(p->prev)
			{
				p->prev->next = p->next;
			}
			if(p->next)
			{
				p->next->prev = p->prev;
			}
			delete p;
			return true;
		}
	}
	return false;
}

SceneObject *
SceneObject::List::pop(void)
{
	List::Entry *e;
	SceneObject *obj;
	
	if(!last)
	{
		return NULL;
	}
	e = last;
	last = last->prev;
	if(!last)
	{
		first = NULL;
	}
	obj = e->obj;
	delete(e);
	/* obj is still retained - it's the caller's responsibility to release it */
	return obj;
}

int
SceneObject::List::next(SceneObject::List::Iterator *i, SceneObject **object)
{
	*object = NULL;
	if(*i)
	{
		*i = (*i)->next;
	}
	else
	{
		*i = first;
	}
	if(*i)
	{
		*object = (*i)->obj;
		return 1;
	}
	return 0;
}
