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

/* Allow a const SceneObject pointer to be serialised to a std::ostream
 * using the conventional stream << sceneobj notation.
 */
std::ostream&
Yuka::operator<<(std::ostream& os, const SceneObject *me)
{
	static thread_local int depth;
	
	SceneObject::List::Iterator i;
	SceneObject *object;
	std::string indent(depth, '\t');
	int c;
	
	os << indent << me->kind << " ";
	if(me->id.length())
	{
		os << '"' << me->id << '"';
	}
	os << "\n" << indent << "{\n";
	me->dump(os, depth + 1);
	i = NULL;
	depth++;
	c = 0;
	while(me->children && me->children->next(&i, &object))
	{
		os << "\n";
		os << object;
		c++;
	}
	depth--;
	os << indent << "};\n";
	return os;
}

/* Public factory method for new SceneObjects */
SceneObject *
SceneObject::sceneObjectWithKind(std::string kind, SceneObject::Properties properties)
{
	SceneObject *obj = NULL;
	
	/* We could accomplish this with a map of constructors, or something of
	 * that ilk
	 */
	if(kind == "Sphere")
	{
		obj = new Sphere(kind);
	}
	else if(kind == "Cube")
	{
		obj = new Cube(kind);
	}
	if(obj)
	{
		if(obj->apply(properties) < 0)
		{
			/* There was a hard error applying the properties */
			obj->release();
			return NULL;
		}
	}
	return obj;
}

/* Protected constructor for SceneObjects */
SceneObject::SceneObject(std::string kind):
	Object(),
	kind(kind),
	container(NULL),
	children(NULL),
	transform(NULL)
{
/*	std::clog << "** SceneObject[0x" << std::hex << std::setw(8) << instanceId() << ":" << tag() << "]<" << kind << ">\n"; */
}

/* Public destructor for SceneObjects */
SceneObject::~SceneObject()
{
	if(children)
	{
		children->release();
	}
	if(transform)
	{
		transform->release();
	}
/*
	if(id.length())
	{
		std::clog << "~~ SceneObject[" << id << "=0x" << std::hex << std::setw(8) << instanceId() << ":" << tag() << "]<" << kind << ">\n";
	}
	else
	{
		std::clog << "~~ SceneObject[0x" << std::hex << std::setw(8) << instanceId() << ":" << tag() << "]<" << kind << ">\n";
	}
*/
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
	child->retain();
	children->add(child);
	child->container = this;
	return 0;
}

/* Return a pointer to our parent (containing) SceneObject */
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
		std::cerr << "Warning: Unsupported property '" << i->first << "' in definition of <" << kind << ">\n";
		e = 1;
	}
	return e;
}

/* Dump our object properties to an ostream at the specified indent level */
std::ostream &
SceneObject::dump(std::ostream &stream, int depth) const
{
	std::string indent(depth, '\t');
	
	stream << indent << "/* SceneObject properties */\n";
	
	if(transform)
	{
		stream << indent << "double x = " << transform->x() <<";\n";
		stream << indent << "double y = " << transform->y() <<";\n";
		stream << indent << "double z = " << transform->z() <<";\n";
	}
	return stream;
}
