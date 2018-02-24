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

/* Protected constructor for Behaviour objects */
Behaviour::Behaviour():
	Object(),
	m_enabled(true)
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
	return true;
}

void
Behaviour::enable(void)
{
	m_enabled = true;
}

void
Behaviour::disable(void)
{
	m_enabled = false;
}

bool
Behaviour::set(const std::string key, const std::string value)
{
	if(key == "enabled")
	{
		return setEnabled(value);
	}
	return Object::set(key, value);
}

/* Output a representation of this object to the provided stream */
std::ostream &
Behaviour::print(std::ostream &stream) const
{
	std::string indent = printIndent();
	
	stream << kind() << "() {\n";
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
