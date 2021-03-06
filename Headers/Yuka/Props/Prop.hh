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

#ifndef YUKA_PROP_HH_
# define YUKA_PROP_HH_                 1

# include "../Scene/SceneObject.hh"
# include "../Traits/Spatial.hh"
# include "../Traits/Solid.hh"
# include "../decl.h"

namespace Yuka
{
	/* A prop is any kind of potentially-visible scene object
	 * which may have physics properties.
	 */

	class Prop:
		public SceneObject,
		public Traits::Spatial,
		public Traits::Solid
	{
	protected:
		Prop(const std::string kind);
	};

};

#endif /*!YUKA_PROP_HH_*/
