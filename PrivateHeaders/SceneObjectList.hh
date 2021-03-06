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

#ifndef YUKA_SCENEOBJECTLIST_HH_
# define YUKA_SCENEOBJECTLIST_HH_      1

# include "Yuka/Intrinsics/Object.hh"
# include "Yuka/Scene/SceneObject.hh"
# include "Yuka/decl.h"

namespace Yuka
{
	/* This is a private implementation of linked list to track objects
	 * which is used by a SceneObject to organise the graph.
	 */
	class YUKA_PRIVATE_ SceneObject::List: public Object
	{
	public:
		List();
		virtual ~List();
	
		bool push(SceneObject *object);
		SceneObject *pop(void);
		bool remove(const SceneObject *object);
		bool has(const SceneObject *object) const;
	protected:
		struct Entry
		{
			Entry *prev, *next;
			SceneObject *obj;
		};
	
		Entry *first, *last;
	public:
		typedef struct List::Entry *Iterator;
		int next(Iterator *iterator, SceneObject **object);
	};
};

#endif /*!YUKA_SCENEOBJECTLIST_HH_*/
