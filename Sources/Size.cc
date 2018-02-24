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

/* Public constructors for Size objects */

Size::Size():
	Vector(1, 1, 1)
{
}

Size::Size(const double factor):
	Vector(factor, factor, factor)
{
}

Size::Size(const double px, const double py, const double pz):
	Vector(px, py, pz)
{
}

std::string
Size::kind(void) const
{
	return "Size";
}
