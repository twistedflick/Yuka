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

#include "p_YukaBehaviours.hh"

/* Protected constructor for Behaviour objects */
Behaviour::Behaviour():
	Traits::Listening(),
	Object(),
	m_prev(NULL),
	m_next(NULL),
	m_enabled(true),
	m_owner(NULL)
{
}

std::string
Behaviour::kind(void) const
{
	return "Behaviour";
}

bool
Behaviour::enabled(void) const
{
	return m_enabled;
}

void
Behaviour::setEnabled(bool value)
{
	m_enabled = value;
}

bool
Behaviour::setEnabled(std::string value)
{
	bool b;
	
	if(!parseBool(value, &b))
	{
		return false;
	}
	m_enabled = b;
	dirty();
	return true;
}

void
Behaviour::enable(void)
{
	m_enabled = true;
	dirty();
}

void
Behaviour::disable(void)
{
	m_enabled = false;
	dirty();
}

Traits::Flexible *
Behaviour::owner(void) const
{
	return m_owner;
}

Behaviour *
Behaviour::next(void) const
{
	return m_next;
}

/* Invoked to indicate that some aspect of this behaviour has changed which
 * will impact upon how we update the object we're attached to
 */
void
Behaviour::dirty(void)
{
	if(m_owner)
	{
		m_owner->dirty();
	}
}

/* Invoked by a flexible object when it's time to apply our behaviour to it */
void
Behaviour::update(void)
{
}

/* Invoked by a flexible object when a Behaviour is attached to it */
void
Behaviour::attachTo(Traits::Flexible *obj)
{
	if(obj == m_owner)
	{
		return;
	}
	if(m_owner)
	{
		/* Don't invoke detachFrom() directly, let SceneObject
		 * invoke it as part of SceneObject::remove()
		 */
		m_owner->removeBehaviour(this);
		m_owner = NULL;
	}
	m_owner = obj;
	ownerChangedTo(m_owner);
}

/* Invoked by a SceneObject when a Behaviour is removed from it */
void
Behaviour::detachFrom(Traits::Flexible *obj)
{
	if(obj != m_owner)
	{
		return;
	}
	dirty();
	m_owner = NULL;
	ownerChangedTo(NULL);
}

void
Behaviour::ownerChangedTo(Traits::Flexible *obj)
{
	(void) obj;
}

/** Scriptable trait **/

bool
Behaviour::set(const std::string key, const std::string value)
{
	if(key == "enabled")
	{
		return setEnabled(value);
	}
	return Object::set(key, value);
}

/** Debuggable trait **/

/* Output a representation of this object to the provided stream */
std::ostream &
Behaviour::print(std::ostream &stream) const
{
	std::string indent = printIndent();
	
	if(debugging())
	{
		stream << internalKind() << "() {\n";
	}
	else
	{
		stream << kind() << "() {\n";
	}
	printPush();
	printProperties(stream);
	printChildren(stream);
	printPop();
	stream << indent << "}";
	return stream;
}

/* Output our properties to the provided stream */
std::ostream &
Behaviour::printProperties(std::ostream &stream) const
{
	std::string indent = printIndent();
	
	Object::printProperties(stream);
	stream << indent << ".enabled = " << (enabled() ? "true" : "false") << ";\n";
	return stream;
}
