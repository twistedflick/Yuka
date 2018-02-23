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

#include "p_Yuka.hh"

/* Implements the private SceneObject::List class */

SceneObject::List::List() :
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
		delete e->obj;
		delete e;
	}
}

int
SceneObject::List::add(SceneObject *object)
{
	List::Entry *e;
	
	e = new List::Entry();
	e->prev = last;
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
	return 0;
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
