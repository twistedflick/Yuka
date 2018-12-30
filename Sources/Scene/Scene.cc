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

#include "p_YukaScene.hh"

/* Public factory for creating and populating a Scene object from a file */
Scene *
Scene::sceneFromPath(const char *pathname)
{
	Scene *obj;
	
	obj = new Scene();
	if(!obj->load(pathname))
	{
		obj->release();
		return NULL;
	}
	return obj;
}

/* Public constructor for Scene objects */
Scene::Scene():
	SceneObject("Scene")
{
}

/* Protected constructor for Scene objects */
Scene::Scene(const std::string kind):
	SceneObject(kind)
{
}

/* Convenience method to load the contents of a file into an existing
 * scene.
 */
bool
Scene::load(const char *pathname)
{
	SceneParser *parser;
	bool ret;
	
	parser = SceneParser::parserFromPath(pathname);
	if(!parser)
	{
		return false;
	}
	ret = parser->parseIntoScene(this);
	parser->release();
	update();
	return ret;
}

/* Add a SceneObject to the root of this scene */
void
Scene::add(SceneObject *child)
{
	SceneObject::add(child);
	if(child)
	{
		Events::SceneObjectAddedToScene ev(this, this, child), ev2(this, this, child);
		child->attachToScene(this);
		/* Emit an event ourselves (because we are the scene), then
		 * ask the child to emit an event
		 */
		emit(&ev);
		ev2.setFlag(Events::CascadeFlag);
		child->emit(&ev);
	}
}
