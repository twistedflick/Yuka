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

#include "p_YukaTraits.hh"

/* Protected constructors for Identifiable objects */
Identifiable::Identifiable():
	m_tag(0)
{
}

/* Protected constructors for Identifiable objects */
Identifiable::Identifiable(const Identifiable *src):
	m_tag(src->tag())
{
}

/* Protected constructors for Identifiable objects */
Identifiable::Identifiable(const Identifiable &src):
	m_tag(src.tag())
{
}

/* Return an object's instance identifier */
unsigned long
Identifiable::instanceId(void) const
{
	return (unsigned long) static_cast<const void *>(this);
}

std::string
Identifiable::instanceString(void) const
{
	char inststr[24];
	
	snprintf(inststr, sizeof(inststr), "{@0x%08lx}", instanceId());
	return inststr;
}

/* Return the kind of object that this is */
std::string
Identifiable::kind(void) const
{
	return "Unknown";
}

/* Return the name of this object, providing one if none has been set */
std::string
Identifiable::name(void) const
{
	char inststr[24];
	
	snprintf(inststr, sizeof(inststr), "auto_%08lx", instanceId());
	return inststr;
}

/* Return display name of this object in the form "<type> <name>" */
std::string
Identifiable::displayName(void) const
{
	std::string xname = kind();
	
	xname.append(" ");
	xname.append(name());

	return xname;
}

/* Return the internal representation of the kind of object that this is */
std::string
Identifiable::internalKind(void) const
{
	return kind();
}

/* Return the 'live' internal name of this object */
std::string
Identifiable::internalName(void) const
{
	std::string xname = internalKind();

	xname.append(" ");
	xname.append(name());
	xname.append(instanceString());
	return xname;
}

/* Get and set an Object's tag */
int
Identifiable::tag(void) const
{
	return m_tag;
}

void
Identifiable::setTag(int tag)
{
	m_tag = tag;
}

bool
Identifiable::setTag(const std::string str)
{
	return Scriptable::parseInt(str, &m_tag);
}
