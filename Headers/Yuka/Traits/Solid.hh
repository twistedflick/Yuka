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

#ifndef YUKA_TRAITS_SOLID_HH_
# define YUKA_TRAITS_SOLID_HH_         1

# include "Trait.hh"
# include "../decl.h"

namespace Yuka
{
	namespace Traits
	{
		class Debuggable;
		
		const Identity SolidTrait = 0x00000020;
		
		/* Solid objects are those that have meshes */
		class YUKA_EXPORT_ Solid:
			public virtual Trait
		{
			friend class Yuka::Traits::Debuggable;
		protected:
			Solid();
		};
	}
};

#endif /*!YUKA_TRAITS_SOLID_HH_*/
