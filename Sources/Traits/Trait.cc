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

using namespace Yuka;
using Yuka::Traits::Trait;

/* Protected constructor for all Trait-based objects */

Trait::Trait():
	m_traits(0),
	m_traitFlags(0)
{
}

/* Protected destructor for all Trait-based objects */

Trait::~Trait()
{
}

/* What traits does this object have? */
Traits::Identity
Trait::traits(void) const
{
	return m_traits;
}

bool
Trait::is(Traits::Identity trait) const
{
	return (m_traits & trait);
}
