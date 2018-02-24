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
#include "Behaviours/Transform.hh"
#include "decl.h"

namespace Yuka
{
	class Scene;

	class YUKA_EXPORT_ SceneObject: public Object
	{
		friend class Scene;
	public:
		typedef std::unordered_map<std::string, std::string> Properties;
	
		static SceneObject *sceneObjectWithKind(const std::string kind, Properties properties);
		
		/* Append child to our list of children */
		virtual void add(SceneObject *child);
		
		/* Add a behaviour to this object */
		virtual void add(Behaviour *behaviour);
		
		/* Remove a behaviour from this object */
		virtual void remove(Behaviour *behaviour);
		
		/* Apply an unordered map of (string => string) properties to this
		 * object
		 */
		virtual bool apply(Properties properties);
		
		/* Set a single named property to the specified string value,
		 * converting to native types as required.
		 */
		virtual bool set(const std::string key, const std::string value);
		
		/* Return our immediate parent in the scene graph */
		virtual SceneObject *parent(void) const;
		
		/* Return the scene this object is attached to, if any */
		virtual Scene *scene(void) const;
		
		/* Return the kind of object that this is */
		virtual std::string kind(void) const;

		/* Return the name of this object, if any */
		virtual std::string name(void) const;
		
	protected:
	
		class List;

		std::string m_kind;
		std::string m_id;
		SceneObject *m_container;
		List *m_children;
		YUKA_WEAKPTR_ Scene *m_scene;
	
		Transform *m_transform;
	
		SceneObject(const std::string kind);
		virtual ~SceneObject();

		virtual std::ostream &printProperties(std::ostream &stream) const;
		virtual std::ostream &printChildren(std::ostream &stream) const;
		virtual std::ostream &printBehaviours(std::ostream &stream) const;
	};

};

#endif /*!YUKA_SCENEOBJECT_HH_*/
