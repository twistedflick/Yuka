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
	Behaviour()
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

/* Return the position (translation vector) of this transform  */
Point
Transform::position(void) const
{
	return m_position;
}

/* Set the translation vector of this transform */
void
Transform::setPosition(const Point pos)
{
	m_position = pos;
}

/* Return the X co-ordinate from the translation vector of this transform */
double
Transform::x(void) const
{
	return m_position.x;
}

/* Set the X co-ordinate of the translation vector of this transform */
void
Transform::setX(const double nx)
{
	m_position.x = nx;
}

/* Parse an X co-ordinate into the translation vector of this transform */
bool
Transform::setX(const std::string nx)
{
	return m_position.setX(nx);
}

/* Return the Y co-ordinate from the translation vector of this transform */
double
Transform::y(void) const
{
	return m_position.y;
}

/* Set the Y co-ordinate of the translation vector of this transform */
void
Transform::setY(const double ny)
{
	m_position.y = ny;
}

/* Parse a Y co-ordinate into the translation vector of this transform */
bool
Transform::setY(const std::string ny)
{
	return m_position.setY(ny);
}

/* Return the Z co-ordinate from the translation vector of this transform */
double
Transform::z(void) const
{
	return m_position.z;
}

/* Set the Z co-ordinate of the translation vector of this transform */
void
Transform::setZ(const double nz)
{
	m_position.z = nz;
}

/* Parse a Z co-ordinate into the translation vector of this transform */
bool
Transform::setZ(const std::string nz)
{
	return m_position.setZ(nz);
}

/* Return the rotation vector of this transform */
Orientation
Transform::rotation(void) const
{
	return m_rotation;
}

/* Set the rotation vector of this transform */
void
Transform::setRotation(const Orientation rot)
{
	m_rotation = rot;
}

/* Return the X co-ordinate from the rotation vector of this transform */
double
Transform::rotX(void) const
{
	return m_rotation.x;
}

/* Set the X co-ordinate of the rotation vector of this transform */
void
Transform::setRotX(const double nx)
{
	m_rotation.x = nx;
}

/* Parse an X co-ordinate into the rotation vector of this transform */
bool
Transform::setRotX(const std::string nx)
{
	return m_rotation.setX(nx);
}

/* Return the Y co-ordinate from the rotation vector of this transform */
double
Transform::rotY(void) const
{
	return m_rotation.y;
}

/* Set the Y co-ordinate of the rotation vector of this transform */
void
Transform::setRotY(const double ny)
{
	m_rotation.y = ny;
}

/* Parse a Y co-ordinate into the rotation vector of this transform */
bool
Transform::setRotY(const std::string ny)
{
	return m_rotation.setY(ny);
}

/* Return the Z co-ordinate from the rotation vector of this transform */
double
Transform::rotZ(void) const
{
	return m_rotation.z;
}

/* Set the Z co-ordinate of the rotation vector of this transform */
void
Transform::setRotZ(const double nz)
{
	m_rotation.z = nz;
}

/* Parse a Z co-ordinate into the rotation vector of this transform */
bool
Transform::setRotZ(const std::string nz)
{
	return m_rotation.setZ(nz);
}

/* Return the scale factor vector of this transform */
Scale
Transform::scale(void) const
{
	return m_scale;
}

/* Set the scale factor vector of this transform */
void
Transform::setScale(const Scale factor)
{
	m_scale = factor;
}

void
Transform::setScale(const double factor)
{
	m_scale = Scale(factor);
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
	stream << indent << ".rotation = " << m_rotation << ";\n";
	stream << indent << ".scale = " << m_scale << ";\n";
	
	return stream;
}
