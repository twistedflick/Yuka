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

#ifndef YUKA_BEHAVIOUR_HH_
# define YUKA_BEHAVIOUR_HH_            1

#include "Object.hh"
#include "Traits/Listening.hh"
#include "decl.h"

namespace Yuka
{
	class SceneObject;
	
	namespace Traits
	{
		class Flexible;
		class Debuggable;
	};
	
	/* Behaviours are objects which alter how Traits::Flexible objects interact
	 * with their environment (be that visually, physically, or in terms of
	 * interactivity and state).
	 *
	 * Yuka::Behaviours::Transform is a key example of a behaviour.
	 */

	class YUKA_EXPORT_ Behaviour:
		public Object,
		virtual public Traits::Listening
	{
		friend class Traits::Flexible;
		friend class Traits::Debuggable;
	public:
		virtual bool enabled(void) const;
		virtual void enable(void);
		virtual void disable(void);
		virtual void setEnabled(const bool value);
		virtual bool setEnabled(const std::string value);

		/* Return the flexible object we're attached to */
		virtual Traits::Flexible *owner(void) const;
		/* Return the next behaviour in the chain we're in */
		virtual Behaviour *next(void) const;
	protected:
		Behaviour();
		/* Mark this behaviour as dirty, and so invalidating our owning object.
		 */
		virtual void dirty(void);
	protected:
		/* Protected interface with Traits::Flexible */
		Behaviour *m_prev;
		Behaviour *m_next;
		/* Invoked by a flexible object when a Behaviour is added to it */
		virtual void attachTo(Traits::Flexible *obj);
		/* Invoked by a flexible object when a Behaviour is removed from it */
		virtual void detachFrom(Traits::Flexible *obj);
		/* Invoked by a flexible object when a Behaviour must update it */
		virtual void update(void);
		/* Invoked when the owning object is changed */
		virtual void ownerChangedTo(Traits::Flexible *obj);
	private:
		bool m_enabled;
		YUKA_WEAKPTR_ Traits::Flexible *m_owner;
	public:
		/* Identifiable trait */
		virtual std::string kind(void) const;
	public:
		/* Scriptable trait */
		virtual bool set(const std::string key, const std::string value);
	public:
		/* Debuggable trait */
		virtual std::ostream &print(std::ostream &stream) const;
	protected:
		/* Debuggable trait */
		virtual std::ostream &printProperties(std::ostream &stream) const;
		
	};

};

#endif /*!YUKA_BEHAVIOUR_HH_*/
