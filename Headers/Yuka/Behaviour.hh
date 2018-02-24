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
#include "decl.h"

namespace Yuka
{
	/* Behaviours are objects which alter how SceneObjects interact with
	 * their environment (be that visually, physically, or in terms of
	 * interactivity and state).
	 *
	 * Yuka::Transform is a key example of a behaviour.
	 */

	class YUKA_EXPORT_ Behaviour: public Object
	{
	public:
		virtual bool enabled(void) const;
		virtual void enable(void);
		virtual void disable(void);
		virtual void setEnabled(const bool value);
		virtual bool setEnabled(const std::string value);
		
		virtual std::string kind(void) const;
		
		virtual bool set(const std::string key, const std::string value);
	protected:
		Behaviour();
		
		virtual std::ostream &print(std::ostream &stream) const;
		virtual std::ostream &printProperties(std::ostream &stream) const;
	private:
		bool m_enabled;
	};

};

#endif /*!YUKA_BEHAVIOUR_HH_*/
