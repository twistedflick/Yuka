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
SceneObject::sceneObjectWithKind(const std::string kind, SceneObject::Properties properties)
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
	else if(kind == "PointLight")
	{
		obj = new PointLight(kind);
	}
	if(obj)
	{
		obj->apply(properties);
	}
	return obj;
}

/* Protected constructor for SceneObjects */
SceneObject::SceneObject(const std::string kind):
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
void
SceneObject::add(SceneObject *child)
{
	if(!children)
	{
		children = new SceneObject::List();
	}
	child->retain();
	children->add(child);
	child->container = this;
}

/* Return a pointer to our parent (containing) SceneObject */
SceneObject *
SceneObject::parent(void)
{
	return container;
}

/* Apply a SceneObject::Properties map to this object, warning about any
 * properties we don't understand. Descendents should override
 * SceneObject::set() to catch properties it knows about before invoking this
 * implementation.
 */
bool
SceneObject::apply(SceneObject::Properties properties)
{
	SceneObject::Properties::iterator i;
	bool result;
	
	result = true;
	for(i = properties.begin(); i != properties.end(); ++i)
	{
		if(set(i->first, i->second))
		{
			result = false;
		}
	}
	return result;
}

/* Attempt to set a property on this SceneObject, warning about any properties
 * that aren't understood.  Descendents should override this method
 * to catch properties it knows about before invoking this implementation.
 */
bool
SceneObject::set(const std::string key, const std::string value)
{
	if(key == "@id")
	{
		id = value;
		return true;
	}
	if(key == "x")
	{
		if(!transform)
		{
			transform = new Transform();
		}
		return transform->setX(value);
	}
	if(key == "y")
	{
		if(!transform)
		{
			transform = new Transform();
		}
		return transform->setY(value);
	}
	if(key == "z")
	{
		if(!transform)
		{
			transform = new Transform();
		}
		return transform->setZ(value);
	}
	std::cerr << "Warning: Unsupported property " << kind << "['" << key << "']\n";
	return false;
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
