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

# include "SceneObject.hh"
# include "decl.h"

namespace Yuka
{

	class YUKA_EXPORT_ Scene: public SceneObject
	{
	public:
		static Scene *sceneFromPath(const char *pathname);
		
		Scene();
	
		/* Constructor a parser for the supplied path and attempt to load
		 * this scene into it.
		 */
		virtual bool load(const char *pathname);
		
		/* Add a child to the root of this scene */
		virtual void add(SceneObject *child);
	protected:
		Scene(std::string kind);
		
		virtual std::ostream &printProperties(std::ostream &stream) const;
	};

};

#endif /*!YUKA_SCENE_HH_*/
