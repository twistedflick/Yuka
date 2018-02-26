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
	Traits::Flexible(),
	Object(),
	m_kind(kind),
	m_parent(NULL),
	m_children(NULL),
	m_scene(NULL),
	m_transform(NULL)
{
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
	dirty();
	child->invalidate();
	m_children->push(child);
	child->attachToParent(this);
	if(scene())
	{
		child->attachToScene(scene());
	}
	update();
}

void
SceneObject::remove(SceneObject *child)
{
	if(!child || !m_children || !m_children->has(child))
	{
		return;
	}
	dirty();
	if(m_scene)
	{
		child->detachFromScene(m_scene);
	}
	child->detachFromParent(this);
	m_children->remove(child);
	update();
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
	invalidate();
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
	invalidate();
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
		dirty();
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
	invalidate();
	m_scene = NULL;
	i = NULL;
	child = NULL;
	while(m_children && m_children->next(&i, &child))
	{
		child->detachFromScene(oldscene);
	}
}

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

/** Flexible trait **/

void
SceneObject::dirtyParent(void)
{
	if(m_parent)
	{
		Flexible::dirtyParent();
		m_parent->dirty();
	}
}

void
SceneObject::invalidateDependents(void)
{
	SceneObject::List::Iterator i;
	SceneObject *child;
	std::string indent = printIndent();
	
	Flexible::invalidateDependents();
	i = NULL;
	child = NULL;
	while(m_children && m_children->next(&i, &child))
	{
		child->invalidate();
	}
}

void
SceneObject::updateDependents(void)
{
	SceneObject::List::Iterator i;
	SceneObject *child;
	std::string indent = printIndent();
	
	Flexible::updateDependents();
	i = NULL;
	child = NULL;
	while(m_children && m_children->next(&i, &child))
	{
		child->update();
	}
}

/** Scriptable trait **/

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
	update();
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
		/* Use m_transform to keep track of a Behaviours::Transform() object
		 * which we will attach to this instance.
		 */
		if(!m_transform)
		{
			m_transform = new Behaviours::Transform();
			add(m_transform);
		}
		return m_transform->set(key, value);
	}
	return Object::set(key, value);
}

/** Identifiable trait **/

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

/** Debuggable trait **/

/* Print our properties to a std::ostream */
std::ostream &
SceneObject::printProperties(std::ostream &stream) const
{
	std::string indent = printIndent();
	
	Object::printProperties(stream);
	
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

	Object::printChildren(stream);

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
