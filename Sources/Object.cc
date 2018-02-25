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

/* Protected constructor for new Object instances */
Object::Object():
	m_refcount(1),
	m_tag(0)
{
/*	std::clog << "** Object[0x" << std::hex << std::setw(8) << instanceId() << "]\n"; */
}

/* Protected copy-constructor for Object instances */
Object::Object(const Object *src):
	m_refcount(1),
	m_tag(src->m_tag)
{
/*	std::clog << "** Object[0x" << std::hex << std::setw(8) << instanceId() << "]\n"; */
}

/* Protected copy-constructor for Object instances */
Object::Object(const Object &src):
	m_refcount(1),
	m_tag(src.m_tag)
{
/*	std::clog << "** Object[0x" << std::hex << std::setw(8) << instanceId() << "]\n"; */
}

/* Protected destructor for Object instances */
Object::~Object()
{
/*	std::clog << "~~ Object[0x" << std::hex << std::setw(8) << instanceId() << "]\n"; */
}

/* Increment the reference count of an Object */
int
Object::retain(void)
{
	m_refcount++;
/*	std::clog << "++ Object[0x" << std::hex << std::setw(8) << instanceId() << "] refcount = " << m_refcount << "\n"; */
	return m_refcount;
}

/* Decrement the reference count of an Object; when it reaches zero, the
 * object will be destroyed.
 */
int
Object::release(void)
{
	m_refcount--;
/*	std::clog << "-- Object[0x" << std::hex << std::setw(8) << instanceId() << "] refcount = " << m_refcount << "\n"; */
	if(m_refcount == 0)
	{
		delete this;
		return 0;
	}
	return m_refcount;
}

/* Get and set an Object's tag */
int
Object::tag(void) const
{
	return m_tag;
}

void
Object::setTag(int tag)
{
	m_tag = tag;
}

bool
Object::setTag(const std::string str)
{
	return parseInt(str, &m_tag);
}

/** Scriptable trait **/

bool
Object::set(const std::string key, const std::string value)
{
	if(key == "tag")
	{
		return setTag(value);
	}
	return Scriptable::set(key, value);
}

/** Identifiable trait **/

/* Return the kind of object that this is */
std::string
Object::kind(void) const
{
	return "Object";
}

/** Debuggable trait **/

/* Output a representation of this object's properties to the provided stream */
std::ostream &
Object::printProperties(std::ostream &stream) const
{
	std::string indent = printIndent();
	int t = tag();
	bool d = debugging();
	
	if(d)
	{
		stream << indent << ".refcount = " << m_refcount << ";\n";
	}
	if(d || t)
	{
		stream << indent << ".tag = " << t << ";\n";
	}
	
	return stream;
}
