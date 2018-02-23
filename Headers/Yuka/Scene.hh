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

#ifndef YUKA_SCENE_HH_
# define YUKA_SCENE_HH_                1

# define NS_YUKA                       "https://twistedflick.github.io/Yuka/"

# include "SceneObject.hh"
# include "decl.h"

namespace Yuka
{

	class YUKA_EXPORT_ Scene: public SceneObject
	{
	public:
		Scene(): SceneObject(NS_YUKA "scene") { };
	
		int load(const char *pathname);
	};

};

#endif /*!SCENE_HH_*/
