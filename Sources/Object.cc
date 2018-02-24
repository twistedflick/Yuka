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

static thread_local unsigned int indent_level;
static thread_local bool debug_enable;

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

/* Get an object's instance identifier */
unsigned long
Object::instanceId(void) const
{
	return (unsigned long) static_cast<const void *>(this);
}

/* Return the kind of object that this is */
std::string
Object::kind(void) const
{
	return "Object";
}

/* Return the internal representation of the kind of object that this is */
std::string
Object::internalKind(void) const
{
	return kind();
}

/* Return the name of this object, providing one if none has been set */
std::string
Object::name(void) const
{
	char inststr[24];
	
	snprintf(inststr, sizeof(inststr), "auto_%08lx", instanceId());
	return inststr;
}

/* Return display name of this object in the form "<type> <name>" */
std::string
Object::displayName(void) const
{
	std::string xname = kind();
	
	xname.append(" ");
	xname.append(name());

	return xname;
}

/* Return the 'live' internal name of this object */
std::string
Object::internalName(void) const
{
	char inststr[24];
	int xtag;
	std::string xname = internalKind();

	xname.append(" ");
	xname.append(name());
	xtag = tag();
	if(xtag)
	{
		snprintf(inststr, sizeof(inststr), "[%d]", xtag);
		xname.append(inststr);
	}
	snprintf(inststr, sizeof(inststr), "{%08lx}", instanceId());
	xname.append(inststr);
	
	return xname;
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

bool
Object::set(const std::string key, const std::string value)
{
	if(key == "tag")
	{
		return setTag(value);
	}
	std::cerr << "Warning: Unsupported property " << kind() << "['" << key << "']\n";
	return false;
}

/* String to native type conversions */
bool
Object::parseInt(const std::string str, int *out)
{
	char *endp;
	int d;
	
	endp = NULL;
	d = (int) strtol(str.c_str(), &endp, 0);
	if(endp && *endp)
	{
		std::cerr << "Error: Cannot convert '" << str << "' to an integer value\n";
		return false;
	}
	*out = d;
	return true;
}

bool
Object::parseBool(const std::string str, bool *out)
{
	const char *cstr;
	char *endp;
	int d;
	
	cstr = str.c_str();
	if(!strcasecmp(cstr, "t") ||
		!strcasecmp(cstr, "true") ||
		!strcasecmp(cstr, "yes") ||
		!strcasecmp(cstr, "on"))
	{
		*out = true;
		return true;
	}
	if(!strcasecmp(cstr, "f") ||
		!strcasecmp(cstr, "false") ||
		!strcasecmp(cstr, "no") ||
		!strcasecmp(cstr, "off"))
	{
		*out = false;
		return true;
	}
	endp = NULL;
	d = (int) strtol(cstr, &endp, 0);
	if(endp && *endp)
	{
		std::cerr << "Error: Cannot convert '" << str << "' to boolean value\n";
		return false;
	}
	*out = d ? true : false;
	return true;
}
bool
Object::parseDouble(const std::string str, double *out)
{
	char *endp;
	double d;
	
	endp = NULL;
	d = strtod(str.c_str(), &endp);
	if(endp && *endp)
	{
		std::cerr << "Error: Cannot convert '" << str << "' to a double-precision floating point value\n";
		return false;
	}
	*out = d;
	return true;
}

/* Dump an object to std::clog */
void
Object::dump(void) const
{
	print(std::clog);
}

/* Enable debugging on this thread */
void
Object::debug(void)
{
	debug_enable = true;
}

/* Is debugging enabled on this thread? */
bool
Object::debugging(void) const
{
	return debug_enable;
}

/* Output a representation of this object to the provided stream */
std::ostream &
Object::print(std::ostream &stream) const
{
	std::string indent = printIndent();
	
	if(debugging())
	{
		stream << internalName() << " = {\n";
	}
	else
	{
		stream << displayName() << " = {\n";
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
Object::printProperties(std::ostream &stream) const
{
	std::string indent = printIndent();
	int t = tag();
	
	if(t || debugging())
	{
		stream << indent << ".tag = " << t << ";\n";
	}
	
	return stream;
}

/* Output a representation of this object's children to the provided stream */
std::ostream &
Object::printChildren(std::ostream &stream) const
{
	return stream;
}

/* Return a string representing the current indentation level */
std::string
Object::printIndent(void) const
{
	return std::string(printDepth(), '\t');
}

/* Return the current print depth */
unsigned int
Object::printDepth(void) const
{
	return indent_level;
}

/* Push the indent level (increment it) */
void
Object::printPush(void) const
{
	indent_level++;
}

/* Pop the indent level (decrement it) */
void
Object::printPop(void) const
{
	indent_level--;
}

/* Allow a const Object pointer to be serialised to a std::ostream
 * using the conventional stream << obj notation.
 */
std::ostream&
Yuka::operator<<(std::ostream& os, const Object *me)
{
	me->print(os);
	return os;
}

std::ostream&
Yuka::operator<<(std::ostream& os, const Object &me)
{
	me.print(os);
	return os;
}
