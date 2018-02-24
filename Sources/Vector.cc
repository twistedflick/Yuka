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

/* Public constructors for Vector objects */
Vector::Vector():
	x(0), y(0), z(0)
{
}

Vector::Vector(const double px, const double py, const double pz):
	x(px), y(py), z(pz)
{
}

void
Vector::setX(const double nx)
{
	x = nx;
}

bool
Vector::setX(const std::string nx)
{
	char *endp;
	double d;
	
	endp = NULL;
	d = ::strtod(nx.c_str(), &endp);
	if(endp && *endp)
	{
		std::cerr << "Error: Cannot convert '" << nx << "' to a Vector::x co-ordinate\n";
		return -1;
	}
	x = d;
	return 0;
}

void
Vector::setY(const double ny)
{
	y = ny;
}

bool
Vector::setY(const std::string ny)
{
	char *endp;
	double d;
	
	endp = NULL;
	d = ::strtod(ny.c_str(), &endp);
	if(endp && *endp)
	{
		std::cerr << "Error: Cannot convert '" << ny << "' to a Vector::y co-ordinate\n";
		return -1;
	}
	y = d;
	return 0;
}

void
Vector::setZ(const double nz)
{
	z = nz;
}

bool
Vector::setZ(const std::string nz)
{
	char *endp;
	double d;
	
	endp = NULL;
	d = ::strtod(nz.c_str(), &endp);
	if(endp && *endp)
	{
		std::cerr << "Error: Cannot convert '" << nz << "' to a Vector::z co-ordinate\n";
		return -1;
	}
	z = d;
	return 0;
}

std::string
Vector::kind(void) const
{
	return "Vector";
}

std::ostream &
Yuka::operator<<(std::ostream &stream, const Vector &vec)
{
	stream << vec.kind() << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
	
	return stream;
}

std::ostream &
Yuka::operator<<(std::ostream &stream, const Vector *vec)
{
	stream << vec->kind() << "(" << vec->x << ", " << vec->y << ", " << vec->z << ")";
	
	return stream;
}
