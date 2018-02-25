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

# include "Flexible.hh"
# include "../decl.h"

namespace Yuka
{
	class Transform;

	namespace Traits
	{
		/* Classes with the Spatial trait have positional co-ordinates, which
		 * are usually manipulated by the Transform behaviour.
		 */
		class YUKA_EXPORT_ Spatial: public Flexible
		{
			friend class Yuka::Transform;
		public:
		protected:
		};
	}
};

#endif /*!YUKA_TRAITS_SPATIAL_HH_*/
