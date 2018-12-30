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

#include "p_YukaParsers.hh"

SceneParser *
SceneParser::parserFromPath(const char *pathname)
{
	return XMLSceneParser::parserFromPath(pathname);
}

void
SceneParser::didFinishLoading(Scene *scene)
{
	Events::SceneLoaded ev(this, scene);
	
	scene->emit(&ev);
}

SceneParser::~SceneParser()
{
}

/** Identifiable trait **/

std::string
SceneParser::kind(void) const
{
	return "SceneParser";
}
