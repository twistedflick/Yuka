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

#ifndef YUKA_SCENEOBJECT_HH_
# define YUKA_SCENEOBJECT_HH_          1

#include <iostream>
#include <string>
#include <unordered_map>

#include "Object.hh"
#include "decl.h"

namespace Yuka
{
	class YUKA_EXPORT_ SceneObject: public Object
	{
	public:
		typedef std::unordered_map<std::string, std::string> Properties;
	
		static SceneObject *sceneObjectWithKind(std::string kind, Properties properties);
		
		virtual int add(SceneObject *child);
		virtual int apply(Properties properties);
	
		virtual SceneObject *parent(void);
		
		friend YUKA_EXPORT_ std::ostream& operator<<(std::ostream &os, const SceneObject *me);
	protected:
	
		class List;

		std::string kind;
		std::string id;
		SceneObject *container;
		List *children;
	
		SceneObject(std::string kind);
		virtual ~SceneObject();

		virtual std::ostream &dump(std::ostream &stream, int depth) const;
	};

};

#endif /*!YUKA_SCENEOBJECT_HH_*/
