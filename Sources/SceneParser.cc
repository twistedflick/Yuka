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

#include "p_Yuka.hh"

SceneParser *
SceneParser::parserForFile(const char *pathname)
{
	xmlTextReaderPtr reader;

	reader = xmlReaderForFile(pathname, NULL, 0);
	if (!reader)
	{
		return NULL;
	}
	/* Create a new SceneParser instance which take ownership of the
	 * xmlTextReader.
	 */
	return new SceneParser(reader);
}

SceneParser::SceneParser(xmlTextReaderPtr reader):
	reader(reader),
	parent(NULL)
{
}

SceneParser::~SceneParser()
{
	xmlFreeTextReader(reader);
}

int
SceneParser::parseIntoScene(Scene *scene)
{
	int ret;
	
	parent = scene;
	root = true;
	ret = xmlTextReaderRead(reader);
	/* xmlTextReaderRead() returns 1 for 'more remaining', 0 for 'complete',
	 * any other value for an error
	 */
	while(ret == 1)
	{
		if((ret = processNode()))
		{
			/* processNode() returns non-zero on error */
			break;
		}
		ret = xmlTextReaderRead(reader);
	}
	parent = NULL;
	if(ret)
	{
		/* At this point, ret should be zero if the file was
		 * processed successfully; as it's non-zero here, we
		 * know an error occurred.
		 */
		return -1;
	}
	return 0;
}

int
SceneParser::processNode()
{
	const char *name, *lname, *ns;
	int type;
	SceneObject *obj;
	bool isempty;
	
	type = xmlTextReaderNodeType(reader);
	ns = (const char *) xmlTextReaderConstNamespaceUri(reader);
	name = (const char *) xmlTextReaderConstName(reader);
	lname = (const char *) xmlTextReaderConstLocalName(reader);
	isempty = xmlTextReaderIsEmptyElement(reader);
	
	switch(type)
	{
		case XML_READER_TYPE_ELEMENT:
		{
			SceneObject::Properties attributes;
			std::string objname;
			
			int ac, c;
			
			if(!ns)
			{
				std::cerr << "Scene description contains XML elements without a namespace at <" << name << ">\n";
				return -1;
			}
			objname = ns;
			objname.append(lname);
			ac = xmlTextReaderAttributeCount(reader);
			for(c = 0; c < ac; c++)
			{
				const char *atns, *atname;
				std::string key, value;
				
				xmlTextReaderMoveToAttributeNo(reader, c);
				atns = (const char *) xmlTextReaderConstNamespaceUri(reader);
				atname = (const char *) xmlTextReaderConstLocalName(reader);
				value = (const char *) xmlTextReaderConstValue(reader);
				if(atns)
				{
					if(!strcmp(atns, NS_XMLNS))
					{
						continue;
					}
					if(!strcmp(atns, NS_XML))
					{
						atns = "@";
					}
					key = atns;
					key.append(atname);
				}
				else
				{
					key = atname;
				}
				attributes[key] = value;
			}
			if(root)
			{
				if(objname == NS_YUKA "scene")
				{
					/* Skip the root, because this->parent is already set */
					root = false;
					return 0;
				}
				else
				{
					std::cerr << "Expected a root <scene /> element in namespace <" NS_YUKA ">, found <" << name << " /> in namespace <" << ns << ">\n";
					return -1;
				}
			}
			obj = SceneObject::sceneObjectWithKind(objname, attributes);
			if(!obj)
			{
				std::clog << "Unable to create a new scene object for <" << name << ">\n";
				return -1;
			}
			parent->add(obj);
			if(!isempty)
			{
				parent = obj;
			}
			break;
		}
		case XML_READER_TYPE_END_ELEMENT:
			parent = parent->parent();
			break;
/*
		default:
			std::clog << "Ignoring node " << type << ", name = '" << ((const char *) name) << "'\n";
*/
	}
	return 0;
}
