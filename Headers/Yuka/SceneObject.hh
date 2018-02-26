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
#include "Traits/Flexible.hh"
#include "decl.h"

namespace Yuka
{
	class Scene;
	
	namespace Behaviours
	{
		class Transform;
	};
	
	class YUKA_EXPORT_ SceneObject:
		public Object,
		public virtual Traits::Flexible
	{
		friend class Scene;
	public:
		class List;
		typedef std::unordered_map<std::string, std::string> Properties;
	
		static SceneObject *sceneObjectWithKind(const std::string kind, Properties properties);
		
		/* Ensure the compiler doesn't think we're trying to inadvertently
		 * hide the behavioural add() and remove() methods from
		 * Traits::Flexible.
		 */
		using Traits::Flexible::add;
		using Traits::Flexible::remove;
		
		/* Append child to our list of children */
		virtual void add(SceneObject *child);
		
		/* Remove a child from our list of children */
		virtual void remove(SceneObject *child);
		
		/* Apply an unordered map of (string => string) properties to this
		 * object
		 */
		virtual bool apply(Properties properties);
		
		/* Return our immediate parent in the scene graph */
		virtual SceneObject *parent(void) const;
		
		/* Return the scene this object is attached to, if any */
		virtual Scene *scene(void) const;
	protected:
		/* Flexible trait */
		virtual void dirtyParent(void);
		virtual void updateDependents(void);
		virtual void invalidateDependents(void);
	public:
		/* Identifiable trait (via Object) */
		virtual std::string kind(void) const;
		virtual std::string name(void) const;
	public:
		/* Scriptable trait (via Object) */
		virtual bool set(const std::string key, const std::string value);
	protected:
		/* Printable trait (via Object) */
		virtual std::ostream &printProperties(std::ostream &stream) const;
		virtual std::ostream &printChildren(std::ostream &stream) const;
	protected:
	
		std::string m_kind;
		std::string m_id;
		YUKA_WEAKPTR_ SceneObject *m_parent;
		List *m_children;
		YUKA_WEAKPTR_ Scene *m_scene;
	
		Behaviours::Transform *m_transform;
	
		SceneObject(const std::string kind);
		virtual ~SceneObject();

		/* Invoked by a parent SceneObject when we're added or removed from it */
		virtual void attachToParent(SceneObject *newparent);
		virtual void detachFromParent(SceneObject *oldparent);

		/* Invoked by a parent SceneObject when we're added or removed from a scene */
		virtual void attachToScene(Scene *newscene);
		virtual void detachFromScene(Scene *oldscene);
	};

};

#endif /*!YUKA_SCENEOBJECT_HH_*/
