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

/* Create a new XML-based scene parser for a supplied pathname.
 *
 * Note that you should not call this directly -- instead, use
 * Yuka::SceneParser::parserFromPath().
 */
XMLSceneParser *
XMLSceneParser::parserFromPath(const char *pathname)
{
	xmlTextReaderPtr reader;

	reader = xmlReaderForFile(pathname, NULL, 0);
	if (!reader)
	{
		return NULL;
	}
	/* Create a new XMLSceneParser instance which take ownership of the
	 * xmlTextReader.
	 */
	return new XMLSceneParser(reader);
}

XMLSceneParser::XMLSceneParser(xmlTextReaderPtr reader):
	SceneParser(),
	reader(reader),
	parent(NULL),
	root(false)
{
	/* Ensure that we're linked against a compatible version of the
	* libxml2 runtime
	*/
	LIBXML_TEST_VERSION;
}

XMLSceneParser::~XMLSceneParser()
{
	xmlFreeTextReader(reader);
}

bool
XMLSceneParser::parseIntoScene(Scene *scene)
{
	int ret;
	
	scene->retain();
	parent = scene;
	root = true;
	ret = xmlTextReaderRead(reader);
	/* xmlTextReaderRead() returns 1 for 'more remaining', 0 for 'complete',
	 * any other value for an error
	 */
	while(ret == 1)
	{
		if(!processNode())
		{
			/* processNode() returns false on error */
			ret = -1;
			break;
		}
		ret = xmlTextReaderRead(reader);
	}
	scene->release();
	parent = NULL;
	if(ret)
	{
		/* At this point, ret should be zero if the file was
		 * processed successfully; as it's non-zero here, we
		 * know an error occurred.
		 */
		std::clog << "An error occurred while parsing the XML document into the scene.\n";
		return false;
	}
	return true;
}

bool
XMLSceneParser::processNode()
{
	const char *name, *lname, *ns;
	int type;
	SceneObject *obj, *oldp;
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
				return false;
			}
			if(!strcmp(ns, NS_YUKA))
			{
				/* Make this *our* default namespace */
				ns = "";
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
				if(objname == "Scene")
				{
					/* Don't try to create a new scene object, because
					 * this->parent is already set
					*/
					root = false;
					return parent->apply(attributes);
				}
				else
				{
					std::cerr << "Expected a root <Scene /> element in namespace <" NS_YUKA ">, found <" << name << " /> in namespace <" << ns << ">\n";
					return false;
				}
			}
			obj = SceneObject::sceneObjectWithKind(objname, attributes);
			if(!obj)
			{
				std::cerr << "Unable to create a new scene object for <" << name << ">\n";
				return false;
			}
			parent->add(obj);
			if(isempty)
			{
				obj->release();
			}
			else
			{
				parent = obj;
			}
			break;
		}
		case XML_READER_TYPE_END_ELEMENT:
			oldp = parent;
			parent = parent->parent();
			if(xmlTextReaderDepth(reader))
			{
				/* Only release objects we've created - the root Scene instance
				 * doesn't belong to us
				 */
				oldp->release();
			}
			break;
/*
		default:
			std::clog << "Ignoring node " << type << ", name = '" << ((const char *) name) << "'\n";
*/
	}
	return true;
}
