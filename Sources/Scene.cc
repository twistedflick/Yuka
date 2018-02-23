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

#include "p_Yuka.hh"

Scene *
Scene::sceneFromPath(const char *pathname)
{
	Scene *obj;
	
	obj = new Scene();
	if(obj->load(pathname))
	{
		delete obj;
		return NULL;
	}
	return obj;
}

int
Scene::load(const char *pathname)
{
	SceneParser *parser;
	int ret;
	
	parser = SceneParser::parserForFile(pathname);
	if(!parser)
	{
		return -1;
	}
	ret = parser->parseIntoScene(this);
	delete parser;
	return ret;
}

/* Dump our object properties to an ostream at the specified indent level */
std::ostream &
Scene::dump(std::ostream &stream, int depth) const
{
	std::string indent(depth, '\t');
	
	SceneObject::dump(stream, depth);
	stream << indent << "/* Scene properties */\n";

	return stream;
}
