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

/* Debuggable trait constructor */
Debuggable::Debuggable():
	Traits::Trait()
{
	m_traits |= Traits::DebuggableTrait;
}

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
	printTraits(stream);
	printBehaviours(stream);
	printChildren(stream);
	printPop();
	stream << indent << "}";
	return stream;
}

/* Print our behaviours to a std::ostream */
std::ostream &
Debuggable::printBehaviours(std::ostream &stream) const
{
	const Flexible *me;
	const Behaviours::Behaviour *p;
	std::string indent = printIndent();
	
	if((me = dynamic_cast<const Flexible *>(this)))
	{
		if(me->m_behaviours.first)
		{
			stream << "\n" << indent << "/* Behaviours */\n\n";
			for(p = me->m_behaviours.first; p; p = p->m_next)
			{
				stream << indent << "@[] = " << p << ";\n";
			}
		}
	}
	return stream;
}


/* Output a representation of this object's properties to the provided stream */
std::ostream &
Debuggable::printProperties(std::ostream &stream) const
{
	return stream;
}

/* Output a representation of this object's traits to the provided stream */
std::ostream &
Debuggable::printTraits(std::ostream &stream) const
{
	const Identifiable *id = dynamic_cast<const Identifiable *>(this);
	const Spatial *spatial = dynamic_cast<const Spatial *>(this);
	std::string indent = printIndent();
	bool d = debugging();
	char hexbuf[24];
	unsigned tval;
	
	stream << "\n" << indent << "/* Traits */\n\n";
	/* The object must have the Debuggable trait otherwise this method
	 * wouldn't have been invoked
	 */
	stream << indent << ".traits = ( Debuggable";
	if(m_traits & Traits::IdentifiableTrait)
	{
		/* 0x0002 */
		stream << " | Identifiable";
	}
	if(m_traits & Traits::ScriptableTrait)
	{
		/* 0x0004 */
		stream << " | Scriptable";
	}
	if(m_traits & Traits::FlexibleTrait)
	{
		/* 0x0008 */
		stream << " | Flexible";
	}
	if(m_traits & Traits::SpatialTrait)
	{
		/* 0x0010 */
		stream << " | Spatial";
	}
	if(m_traits & Traits::SolidTrait)
	{
		/* 0x0020 */
		stream << " | Solid";
	}
	if(m_traits & Traits::ObservableTrait)
	{
		/* 0x0040 */
		stream << " | Observable";
	}
	if(m_traits & Traits::ListeningTrait)
	{
		/* 0x0040 */
		stream << " | Listening";
	}
	tval = m_traits >> 8;
	if(tval)
	{
		snprintf(hexbuf, sizeof(hexbuf) - 1, "%08x", tval);
		stream << " | " << hexbuf;
	}
	stream << " );\n";
	
	/* Dump the identity for each trait */
	if(m_traits & Traits::DebuggableTrait)
	{
		/* 0x0002 */
		stream << indent << ".debuggable = { };\n";
	}
	if(m_traits & Traits::IdentifiableTrait)
	{
		/* 0x0002 */
		stream << indent << ".identifiable = {\n";
		printPush();
		indent = printIndent();

		stream << indent << ".name = \"" << id->name() << "\";\n";
		stream << indent << ".kind = " << id->kind() << ";\n";
		
		printPop();
		indent = printIndent();
		stream << indent << "};\n";
	
	}
	if(m_traits & Traits::ScriptableTrait)
	{
		/* 0x0004 */
		stream << indent << ".scriptable = { };\n";
	}
	if(m_traits & Traits::FlexibleTrait)
	{
		/* 0x0008 */
		stream << indent << ".flexible = { };\n";
	}
	if(m_traits & Traits::SpatialTrait)
	{
		/* 0x0010 */
		stream << indent << ".spatial = {\n";
		printPush();
		indent = printIndent();
		stream << indent << ".position = " << spatial->m_spatial.identity.position << ";\n";
		stream << indent << ".rotation = " << spatial->m_spatial.identity.rotation << ";\n";
		stream << indent << ".scale = " << spatial->m_spatial.identity.scale << ";\n";
		printPop();
		indent = printIndent();
		stream << indent << "};\n";
	}
	if(m_traits & Traits::SolidTrait)
	{
		/* 0x0020 */
		stream << indent << ".solid = { };\n";
	}
	if(m_traits & Traits::ObservableTrait)
	{
		/* 0x0040 */
		stream << indent << ".observable = { };\n";
	}
	if(m_traits & Traits::ListeningTrait)
	{
		/* 0x0040 */
		stream << indent << ".listening = { };\n";
	}
		
	/* Dump the traits' current state */
	stream << "\n";
	
	stream << indent << ".state = {\n";
	printPush();
	indent = printIndent();

	/* Trait (base) state */
	if(d)
	{
		/* Only dumped when debugging */
		snprintf(hexbuf, sizeof(hexbuf) - 1, "%08x", m_traitFlags);
		stream << indent << ".traitFlags = 0x" << hexbuf << ";\n";
	}
	
	/* Identifiable trait state */
	if(id)
	{
		int t = id->tag();

		stream << indent << ".identifiable = {\n";
		printPush();
		indent = printIndent();

		stream << indent << ".instanceId = " << id->instanceString() << ";\n";
		if(d || t)
		{
			/* Only when debugging or if a tag was explicitly set */
			stream << indent << ".tag = " << t << ";\n";
		}
		
		printPop();
		indent = printIndent();
		stream << indent << "};\n";
	}
	
	/* Spatial trait state */
	if(spatial)
	{
		stream << indent << ".spatial = {\n";
		printPush();
		indent = printIndent();
		stream << indent << ".position = " << spatial->m_spatial.current.position << ";\n";
		stream << indent << ".rotation = " << spatial->m_spatial.current.rotation << ";\n";
		stream << indent << ".scale = " << spatial->m_spatial.current.scale << ";\n";
		printPop();
		indent = printIndent();
		stream << indent << "};\n";
	}

	printPop();
	indent = printIndent();
	
	stream << indent << "};\n";

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
