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

static thread_local unsigned int indent_level;
static thread_local bool debug_enable;

/* Dump this object to std::clog */
void
Debuggable::dump(void) const
{
	print(std::clog);
}

/* Output a representation of this object to the provided stream */
std::ostream &
Debuggable::print(std::ostream &stream) const
{
	std::string indent = printIndent();
	const Identifiable *id = dynamic_cast<const Identifiable *>(this);
	
	if(id)
	{
		if(debugging())
		{
			stream << id->internalName() << " = {\n";
		}
		else
		{
			stream << id->displayName() << " = {\n";
		}
	}
	else
	{
		stream << "{\n";
	}
	printPush();
	printProperties(stream);
	printChildren(stream);
	printPop();
	stream << indent << "}";
	return stream;
}

/* Output a representation of this object's properties to the provided stream */
std::ostream &
Debuggable::printProperties(std::ostream &stream) const
{
	return stream;
}

/* Output a representation of this object's children to the provided stream */
std::ostream &
Debuggable::printChildren(std::ostream &stream) const
{
	return stream;
}

/* Return a string representing the current indentation level */
std::string
Debuggable::printIndent(void) const
{
	return std::string(printDepth(), '\t');
}

/* Return the current print depth */
unsigned int
Debuggable::printDepth(void) const
{
	return indent_level;
}

/* Push the indent level (increment it) */
void
Debuggable::printPush(void) const
{
	indent_level++;
}

/* Pop the indent level (decrement it) */
void
Debuggable::printPop(void) const
{
	indent_level--;
}

/* Enable debug output on this thread */
void
Debuggable::debug(void)
{
	debug_enable = true;
}

/* Is debug output enabled on this thread? */
bool
Debuggable::debugging(void) const
{
	return debug_enable;
}


/* Allow a const Debuggable pointer to be serialised to a std::ostream
 * using the conventional stream << obj notation.
 */
std::ostream&
Yuka::Traits::operator<<(std::ostream& os, const Debuggable *me)
{
	me->print(os);
	return os;
}

std::ostream&
Yuka::Traits::operator<<(std::ostream& os, const Debuggable &me)
{
	me.print(os);
	return os;
}
