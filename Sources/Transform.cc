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
	Object(),
	m_position(0, 0, 0)
{
}

Transform::Transform(const Point pos):
	Object(),
	m_position(pos)
{
}

Transform::Transform(const double px, const double py, const double pz):
	Object(),
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

double
Transform::y(void) const
{
	return m_position.y;
}

double
Transform::z(void) const
{
	return m_position.z;
}
