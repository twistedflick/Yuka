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

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "p_YukaEvents.hh"

/* Public constructors for Events::Scene structures */

Events::Scene::Scene(Traits::Observable *sender, EventType kind):
	Event(sender, MakeEventType(SceneEvents, kind)),
	scene(NULL),
	sceneObject(NULL)
{
}

Events::Scene::Scene(Traits::Observable *sender, EventType kind, EventFlags flags):
	Event(sender, MakeEventType(SceneEvents, kind), flags),
	scene(NULL),
	sceneObject(NULL)
{
}

Events::Scene::~Scene()
{
	if(scene)
	{
		scene->release();
	}
	if(sceneObject)
	{
		sceneObject->release();
	}
}

std::string
Events::Scene::eventName(void) const
{
	switch(eventKind())
	{
		case Events::Scene::Loaded:
			return "Scene::Loaded";
		case Events::Scene::ObjectAddedToScene:
			return "Scene::ObjectAddedToScene";
		case Events::Scene::ObjectRemovedFromScene:
			return "Scene::ObjectRemovedFromScene";
		case Events::Scene::ObjectUpdate:
			return "Scene::ObjectUpdate";
		case Events::Scene::ObjectReparented:
			return "Scene::ObjectReparented";
		case Events::Scene::ObjectOrphaned:
			return "Scene::ObjectOrphaned";
	}
	return Events::Event::eventName();
}

/* Set the scene and scene object */

void
Events::Scene::setScene(Yuka::Scene *newScene)
{
	if(newScene)
	{
		newScene->retain();
	}
	if(scene)
	{
		scene->release();
	}
	scene = newScene;
}

void
Events::Scene::setSceneObject(Yuka::SceneObject *newSceneObject)
{
	if(newSceneObject)
	{
		newSceneObject->retain();
	}
	if(sceneObject)
	{
		sceneObject->release();
	}
	sceneObject = newSceneObject;
}

/** Debuggable trait (via Events::Event) **/

std::ostream &
Events::Scene::printProperties(std::ostream &stream) const
{
	std::string indent = printIndent();
	
	Events::Event::printProperties(stream);
	
	if(scene)
	{
		stream << indent << ".scene = " << scene->internalName() << ";\n";
	}
	else
	{
		stream << indent << ".scene = nil;\n";
	}
	if(sceneObject)
	{
		stream << indent << ".sceneObject = " << sceneObject->internalName() << ";\n";
	}
	else
	{
		stream << indent << ".sceneObject = nil;\n";
	}
	return stream;
}

/** Scene event constructors **/

Events::SceneLoaded::SceneLoaded(Traits::Observable *sender, Yuka::Scene *scene):
	Events::Scene(sender, Events::Scene::Loaded)
{
	setScene(scene);
	setSceneObject(scene);
}

Events::SceneObjectAddedToScene::SceneObjectAddedToScene(Traits::Observable *sender, Yuka::Scene *scene, Yuka::SceneObject *obj):
	Events::Scene(sender, Events::Scene::ObjectAddedToScene)
{
	setScene(scene);
	setSceneObject(obj);
}

Events::SceneObjectRemovedFromScene::SceneObjectRemovedFromScene(Traits::Observable *sender, Yuka::Scene *scene, Yuka::SceneObject *obj):
	Events::Scene(sender, Events::Scene::ObjectRemovedFromScene)
{
	setScene(scene);
	setSceneObject(obj);
}

Events::SceneObjectUpdate::SceneObjectUpdate(Traits::Observable *sender, Yuka::SceneObject *obj):
	Events::Scene(sender, Events::Scene::ObjectUpdate)
{
	setSceneObject(obj);
	if(obj)
	{
		setScene(obj->scene());
	}
}

Events::SceneObjectOrphaned::SceneObjectOrphaned(Traits::Observable *sender, Yuka::SceneObject *obj):
	Events::Scene(sender, Events::Scene::ObjectOrphaned)
{
	setSceneObject(obj);
	if(obj)
	{
		setScene(obj->scene());
	}
}

Events::SceneObjectReparented::SceneObjectReparented(Traits::Observable *sender, Yuka::SceneObject *obj):
	Events::Scene(sender, Events::Scene::ObjectReparented)
{
	setSceneObject(obj);
	if(obj)
	{
		setScene(obj->scene());
	}
}

