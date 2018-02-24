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
	m_kind(kind),
	m_container(NULL),
	m_children(NULL),
	m_transform(NULL)
{
/*	std::clog << "** SceneObject[0x" << std::hex << std::setw(8) << instanceId() << ":" << tag() << "]<" << kind << ">\n"; */
}

/* Public destructor for SceneObjects */
SceneObject::~SceneObject()
{
	if(m_children)
	{
		m_children->release();
	}
	if(m_transform)
	{
		m_transform->release();
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

std::string
SceneObject::kind(void) const
{
	if(m_kind.length())
	{
		return m_kind;
	}
	return "SceneObject";
}

std::string
SceneObject::name(void) const
{
	if(m_id.length())
	{
		return m_id;
	}
	return Object::name();
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
	if(!m_children)
	{
		m_children = new SceneObject::List();
	}
	m_children->add(child);
	child->m_container = this;
}

/* Return a pointer to our parent (containing) SceneObject */
SceneObject *
SceneObject::parent(void)
{
	return m_container;
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
		m_id = value;
		return true;
	}
	if(key == "x")
	{
		if(!m_transform)
		{
			m_transform = new Transform();
		}
		return m_transform->setX(value);
	}
	if(key == "y")
	{
		if(!m_transform)
		{
			m_transform = new Transform();
		}
		return m_transform->setY(value);
	}
	if(key == "z")
	{
		if(!m_transform)
		{
			m_transform = new Transform();
		}
		return m_transform->setZ(value);
	}
	std::cerr << "Warning: Unsupported property " << kind() << "['" << key << "']\n";
	return false;
}

/* Print our properties to a std::ostream */
std::ostream &
SceneObject::printProperties(std::ostream &stream) const
{
	std::string indent = printIndent();
	
	Object::printProperties(stream);
	
	stream << indent << "/* SceneObject properties */\n";
	
	return stream;
}

/* Print our children to a std::ostream */
std::ostream &
SceneObject::printChildren(std::ostream &stream) const
{
	std::string indent = printIndent();
	
	SceneObject::List::Iterator i;
	SceneObject *child;
	
	printBehaviours(stream);
	
	i = NULL;
	child = NULL;
	if(m_children)
	{
		stream << "\n" << indent << "/* " << kind() << " members */\n\n";
	}
	while(m_children && m_children->next(&i, &child))
	{
		stream << indent << child;
		stream << "\n";
	}
	
	return stream;
}

/* Print our behaviours to a std::ostream */
std::ostream &
SceneObject::printBehaviours(std::ostream &stream) const
{
	std::string indent = printIndent();
	
	stream << "\n" << indent << "/* Behaviours */\n\n";
	if(m_transform)
	{
		stream << indent << "@transform = " << m_transform << ";\n";
	}
	return stream;
}
