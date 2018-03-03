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

#ifndef YUKA_EVENTS_SCENE_HH_
# define YUKA_EVENTS_SCENE_HH_         1

#include "Event.hh"
#include "../decl.h"

namespace Yuka
{
	class Scene;
	class SceneObject;
	
	namespace Events
	{
		/** Yuka::Events::Scene:
		 *
		 * This is a base class for all scene-related events, including
		 * SceneObject hierarchy changes.
		 *
		 * All of the events can be observed by listening to the scene itself,
		 * althought they will always also fire on the individual objects
		 * affected.
		 *
		 * Events::Scene objects are never created directly: instead,
		 * instances of subclasses (such as Events::SceneLoaded) are used.
		 *
		 * All scene events have an event class of Events::SceneEvents (defined
		 * in <Yuka/Events/Event.hh>).
		 *
		 * All scene event kind constants (used for comparison with
		 * Event::eventKind()) are namespaced within Events::Scene,
		 * for example, Events::Scene::ObjetAddedToScene.
		 */
		struct YUKA_EXPORT_ Scene:
			public Event
		{
			Yuka::Scene *scene;
			Yuka::SceneObject *sceneObject;
			
			friend class Yuka::Scene;
			friend class Yuka::SceneObject;
			
		public:
			/* SceneEvents */
			static const EventType Loaded = MakeEventType(SceneEvents, 0x00);
			static const EventType ObjectAddedToScene = MakeEventType(SceneEvents, 0x01);
			static const EventType ObjectRemovedFromScene = MakeEventType(SceneEvents, 0x02);
			static const EventType ObjectUpdate = MakeEventType(SceneEvents, 0x03);
			static const EventType ObjectReparented = MakeEventType(SceneEvents, 0x04);
			static const EventType ObjectOrphaned = MakeEventType(SceneEvents, 0x05);
			
		public:
			Scene(Yuka::Traits::Observable *sender, EventType kind);
			Scene(Yuka::Traits::Observable *sender, EventType kind, EventFlags flags);
			virtual ~Scene();
			
			virtual std::string eventName(void) const;
			
			virtual void setScene(Yuka::Scene *newScene);
			virtual void setSceneObject(Yuka::SceneObject *newSceneObject);
		protected:
			virtual std::ostream &printProperties(std::ostream &stream) const;
		};

		struct YUKA_EXPORT_ SceneLoaded:
			public Scene
		{
			SceneLoaded(Yuka::Traits::Observable *sender, Yuka::Scene *scene = NULL);
		};
		
		struct YUKA_EXPORT_ SceneObjectAddedToScene:
			public Scene
		{
			SceneObjectAddedToScene(Yuka::Traits::Observable *sender, Yuka::Scene *scene = NULL, Yuka::SceneObject *obj = NULL);
		};

		struct YUKA_EXPORT_ SceneObjectRemovedFromScene:
			public Scene
		{
			SceneObjectRemovedFromScene(Yuka::Traits::Observable *sender, Yuka::Scene *scene = NULL, Yuka::SceneObject *obj = NULL);
		};

		struct YUKA_EXPORT_ SceneObjectReparented:
			public Scene
		{
			SceneObjectReparented(Yuka::Traits::Observable *sender, Yuka::SceneObject *obj = NULL);
		};

		struct YUKA_EXPORT_ SceneObjectOrphaned:
			public Scene
		{
			SceneObjectOrphaned(Yuka::Traits::Observable *sender, Yuka::SceneObject *obj = NULL);
		};

		struct YUKA_EXPORT_ SceneObjectUpdate:
			public Scene
		{
			SceneObjectUpdate(Yuka::Traits::Observable *sender, Yuka::SceneObject *obj = NULL);
		};

	};

	typedef struct Yuka::Events::Scene SceneEvent;
};

#endif /*!YUKA_EVENTS_SCENE_HH_*/
