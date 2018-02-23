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

#ifndef YUKA_XMLSCENEPARSER_HH_
# define YUKA_XMLSCENEPARSER_HH_       1

# include <libxml/xmlreader.h>
# include "Yuka/SceneParser.hh"
# include "Yuka/decl.h"

namespace Yuka
{
	class XMLSceneParser: public SceneParser
	{
	public:
		static XMLSceneParser *parserFromPath(const char *pathname);
	
		virtual ~XMLSceneParser();
	
		virtual int parseIntoScene(Scene *scene);
	protected:
		xmlTextReaderPtr reader;
		SceneObject *parent;
		bool root;
	
		XMLSceneParser(xmlTextReaderPtr reader);
	
		int processNode();
	};
};

#endif /*!YUKA_XMLSCENEPARSER_HH_*/
