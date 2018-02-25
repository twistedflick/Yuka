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
	else if(kind == "Group")
	{
		obj = new Group(kind);
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
	m_parent(NULL),
	m_children(NULL),
	m_scene(NULL),
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
	/* TODO: check if child is a parent of this */
	if(!child)
	{
		return;
	}
	if(!m_children)
	{
		m_children = new SceneObject::List();
	}
	m_children->push(child);
	child->attachToParent(this);
	if(scene())
	{
		child->attachToScene(scene());
	}
}

void
SceneObject::remove(SceneObject *child)
{
	if(!child || !m_children || !m_children->has(child))
	{
		return;
	}
	if(m_scene)
	{
		child->detachFromScene(m_scene);
	}
	child->detachFromParent(this);
	m_children->remove(child);
}

/* Invoked by a parent SceneObject when we're added or removed from it */
void
SceneObject::attachToParent(SceneObject *newparent)
{
	if(newparent == m_parent)
	{
		return;
	}
	if(m_parent)
	{
		/* Don't invoke detachFromParent() directly, let SceneObject
		 * invoke it as part of SceneObject::remove()
		 */
		m_parent->remove(this);
	}
	m_parent = newparent;
}

void
SceneObject::detachFromParent(SceneObject *oldparent)
{
	if(m_parent != oldparent)
	{
		return;
	}
	m_parent = NULL;
}

/* Invoked by a parent SceneObject when we're added or removed from a scene */
void
SceneObject::attachToScene(Scene *newscene)
{
	SceneObject::List::Iterator i;
	SceneObject *child;
	
	if(newscene == m_scene)
	{
		return;
	}
	if(m_scene)
	{
		detachFromScene(m_scene);
	}
	m_scene = newscene;
	i = NULL;
	child = NULL;
	while(m_children && m_children->next(&i, &child))
	{
		child->attachToScene(newscene);
	}
	
}

void
SceneObject::detachFromScene(Scene *oldscene)
{
	SceneObject::List::Iterator i;
	SceneObject *child;

	if(m_scene != oldscene)
	{
		return;
	}
	m_scene = NULL;
	i = NULL;
	child = NULL;
	while(m_children && m_children->next(&i, &child))
	{
		child->detachFromScene(oldscene);
	}
}


/* Add and remove behaviours. Note that doing so retains the behaviour, and
 * will also remove it from any other SceneObject that it is currently
 * attached to.
 */
void
SceneObject::add(Behaviour *behaviour)
{
	SceneObject *oldp;
	Transform *t;
	
	behaviour->retain();
	t = dynamic_cast<Transform *>(behaviour);
	if(!t)
	{
		/* Currently we only support adding a Transform behaviour */
		std::clog << "Attempt to add unsupported behaviour " << behaviour->internalName() << " to " << internalName() << "\n";
		behaviour->release();
		return;
	}
	oldp = behaviour->sceneObject();
	if(oldp && oldp == this)
	{
		/* This behaviour is already attached to this scene object */
		behaviour->release();
		return;
	}
	if(oldp)
	{
		/* Remove the behaviour from the scene object it was previously
		 * attached to
		 */
		oldp->remove(behaviour);
	}
	/* Tell the behaviour that we're adding it to this scene object */
	behaviour->attachTo(this);
	if(t)
	{
		/* If it was a Transform, we can set m_transform to it */
		m_transform = t;
	}
	else
	{
		/* For now, just release it, as we don't have a list of behaviours */

		/* Note that this code is not ever executed due to the hard preflight
		 * check driven by the dynamic_cast<>() result.
		 */
		behaviour->release();
	}
}

void
SceneObject::remove(Behaviour *behaviour)
{
	if(behaviour == m_transform)
	{
		behaviour->detachFrom(this);
		m_transform = NULL;
	}
}

/* Remove a behaviour from our object, releasing it */

/* Return a pointer to our parent (containing) SceneObject */
SceneObject *
SceneObject::parent(void) const
{
	return m_parent;
}

/* Return a pointer to the scene we're a part of, if any */
Scene *
SceneObject::scene(void) const
{
	return m_scene;
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
		if(!set(i->first, i->second))
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
	if(key == "x" || key == "y" || key == "z" ||
		key == "rx" || key == "ry" || key == "rz" ||
		key == "scale" || key == "sx" || key == "sy" || key == "sz")
	{
		if(!m_transform)
		{
			Transform *t = new Transform();
			add(t);
			t->release();
		}
		return m_transform->set(key, value);
	}
	return Object::set(key, value);
}

/* Print our properties to a std::ostream */
std::ostream &
SceneObject::printProperties(std::ostream &stream) const
{
	std::string indent = printIndent();
	
	Object::printProperties(stream);
	
	stream << indent << "/* SceneObject properties */\n";
	
	if(debugging())
	{
		if(m_parent)
		{
			stream << indent << ".parent = " << m_parent->internalName() << ";\n";
		}
		else
		{
			stream << indent << ".parent = nil;\n";
		}
		if(m_scene)
		{
			stream << indent << ".scene = " << m_scene->internalName() << ";\n";
		}
		else
		{
			stream << indent << ".scene = nil;\n";
		}
	}
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
		stream << indent << child << ";\n";
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
