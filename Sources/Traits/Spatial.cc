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

/* Obtain a pointer to our spatial state object which can be updated by a
 * a behaviour.
 *
 * If this is the first time this is invoked during a pass through the
 * behaviour chain, the bit in m_traitFlags mask for SpatialTrait will be
 * SET, and we should unset it after resetting our current spatial state back
 * to its initial 'identity' state. This allows behaviour-chain updates to
 * have a predictable lifecycle without needing to bake knowledge of each
 * type of trait into base classes.
 */
Spatial::Coordinates *
Spatial::spatialState()
{
	if(m_traitFlags & SpatialTrait)
	{
		/* Reset the state back to the identity state */
		m_spatial.current = m_spatial.identity;
		m_traitFlags &= ~SpatialTrait;
	}
	return &(m_spatial.current);
}
