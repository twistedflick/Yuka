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

/* Public constructors for Transform objects */

Transform::Transform():
	Behaviour(),
	m_position(0, 0, 0)
{
}

Transform::Transform(const Point pos):
	Behaviour(),
	m_position(pos)
{
}

Transform::Transform(const double px, const double py, const double pz):
	Behaviour(),
	m_position(Point(px, py, pz))
{
}

Point
Transform::position(void) const
{
	return m_position;
}

double
Transform::x(void) const
{
	return m_position.x;
}

void
Transform::setX(const double nx)
{
	m_position.x = nx;
}

bool
Transform::setX(const std::string nx)
{
	return m_position.setX(nx);
}

double
Transform::y(void) const
{
	return m_position.y;
}

void
Transform::setY(const double ny)
{
	m_position.y = ny;
}

bool
Transform::setY(const std::string ny)
{
	return m_position.setY(ny);
}

double
Transform::z(void) const
{
	return m_position.z;
}

void
Transform::setZ(const double nz)
{
	m_position.z = nz;
}

bool
Transform::setZ(const std::string nz)
{
	return m_position.setZ(nz);
}

/* Return the name of this class, for introspection */
std::string
Transform::kind(void) const
{
	return "Transform";
}

/* Print our properties to a std::ostream */
std::ostream &
Transform::printProperties(std::ostream &stream) const
{
	std::string indent = printIndent();
	
	Behaviour::printProperties(stream);
	
	stream << indent << ".position = " << m_position << ";\n";
	
	return stream;
}
