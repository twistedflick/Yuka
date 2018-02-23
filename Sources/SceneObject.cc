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

#include "p_Yuka.hh"

SceneObject *
SceneObject::sceneObjectWithKind(std::string kind, SceneObject::Properties properties)
{
	SceneObject *obj = NULL;
	
	/* We could accomplish this with a map of constructors, or something of
	 * that ilk
	 */
	if(kind == NS_YUKA "sphere")
	{
		obj = new Sphere(kind);
	}
	else if(kind == NS_YUKA "cube")
	{
		obj = new Cube(kind);
	}
	if(obj)
	{
		if(obj->apply(properties) < 0)
		{
			/* There was a hard error applying the properties */
			delete obj;
			return NULL;
		}
	}
	return obj;
}

SceneObject::SceneObject(std::string kind):
	kind(kind),
	container(NULL),
	children(NULL)
{
	std::clog << "++ SceneObject[0x" << std::hex << std::setw(8) << (unsigned long) static_cast<void *>(this) << "] <" << kind << ">\n";
}

SceneObject::~SceneObject()
{
	delete children;
	if(id.length())
	{
		std::clog << "-- SceneObject[" << id << "=0x" << std::hex << std::setw(8) << (unsigned long) static_cast<void *>(this) << "] <" << kind << ">\n";
	}
	else
	{
		std::clog << "-- SceneObject[0x" << std::hex << std::setw(8) << (unsigned long) static_cast<void *>(this) << "] <" << kind << ">\n";
	}
}

/* Add a scene object to the scene graph as a child of this one. This won't
 * necessarily always make sense from any sort of rendering or physics
 * perspective, but it's easier to treat all objects as equivalent and having
 * the same basic set of capabilities from the outset than it is to attempt
 * prevent hypothetical instances of programmer error which are unlikely to
 * actually be damaging (even if irritating).
 */
int
SceneObject::add(SceneObject *child)
{
	if(!children)
	{
		children = new SceneObject::List();
	}
	children->add(child);
	child->container = this;
	return 0;
}

SceneObject *
SceneObject::parent(void)
{
	return container;
}

/* Apply a SceneObject::Properties map to this object, warning about any
 * properties we don't understand. Descendents should override this method
 * to catch properties it knows about before invoking this implementation.
 */
int
SceneObject::apply(SceneObject::Properties properties)
{
	SceneObject::Properties::iterator i;
	int e;
	
	e = 0;
	for(i = properties.begin(); i != properties.end(); ++i)
	{
		if(i->first == "@id")
		{
			id = i->second;
			continue;
		}
		std::clog << "Warning: Unsupported property '" << i->first << "' in definition of <" << kind << ">\n";
		e = 1;
	}
	return e;
}
