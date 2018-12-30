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

#ifndef YUKA_TRAITS_SPATIAL_HH_
# define YUKA_TRAITS_SPATIAL_HH_       1

# include "Trait.hh"
# include "../Intrinsics/Point.hh"
# include "../Intrinsics/Size.hh"
# include "../Intrinsics/Orientation.hh"
# include "../decl.h"

namespace Yuka
{
	namespace Behaviours
	{
		class Transform;
	};

	namespace Traits
	{
		class Debuggable;
		
		const Identity SpatialTrait = 0x00000010;
		
		/* Classes with the Spatial trait have positional co-ordinates, which
		 * are usually manipulated by the Transform behaviour.
		 */
		class YUKA_EXPORT_ Spatial:
			public virtual Trait
		{
			friend class Yuka::Behaviours::Transform;
			friend class Yuka::Traits::Debuggable;
		public:
			struct Coordinates
			{
				Point position;
				Orientation rotation;
				Size scale;
				
				Coordinates():
					position(),
					rotation(),
					scale(1.0)
				{
				};
			};
		protected:
			/* Invoked by friendly behaviours to retrieve a pointer to our
			 * spatial state
			*/
			virtual Coordinates *spatialState(void);
		private:
			struct
			{
				Coordinates identity;
				Coordinates current;
			} m_spatial;
		protected:
			Spatial();
		};
	}
};

#endif /*!YUKA_TRAITS_SPATIAL_HH_*/
