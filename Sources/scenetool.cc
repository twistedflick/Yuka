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

#include <iostream>

#include "Yuka/Yuka.hh"

int
main(int argc, char **argv)
{
	Yuka::Scene *scene;
	
	/* Check command-line arguments */
	if(argc != 2)
	{
		std::cerr << "Expected a single scene file name argument.\n";
		
		std::cout << "\nUsage:\n\n" <<
			"  " << argv[0] << " FILENAME\n";
		return 0;
	}
	/* Attempt to load the scene from the named file */
	scene = Yuka::Scene::sceneFromPath(argv[1]);
	if(!scene)
	{
		std::cerr << argv[0] << ": failed to load scene '" << argv[1] << "'.\n";
		return 1;
	}
	/* Print the scene graph, then release it and return */
	Yuka::Object::debug();
	std::cout << scene << "\n";
	scene->release();
	return 0;
}
