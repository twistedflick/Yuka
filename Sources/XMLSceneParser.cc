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
	stack = new SceneObject::List();
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
	delete stack;
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
			if(isempty)
			{
				/* If it's an empty element, we can add it directly to the
				 * parent.
				 */
				parent->add(obj);
				/* Now that obj has been added, we can release it */
				obj->release();
				return true;
			}
			/* It's not an empty element: we need to keep track of two things
			 * until we reach the end, allowing for recursion.
			 *
			 * 1 - The object we've just created. This is a new instance
			 *     with refcount = 1
			 * 2 - Our current parent, to which the new object will be added
			 *     as a child when we reach the end of the element (see
			 *     XML_READER_TYPE_END_ELEMENT below)
			 */
			/* Push our current parent onto our parentage stack, which will
			 * retain it on our behalf. Note that the parent is ALREADY
			 * retained by us, either because it's a brand new object, or
			 * because it's a scene we're parsing into.
			 */
			stack->push(parent);
			/* Now set our 'current parent' to point to the new object, so
			 * that its children will be correctly added to it.
			 */
			parent = obj;
			break;
		}
		case XML_READER_TYPE_END_ELEMENT:
			/* Obtain the object that we pushed, above */
			obj = parent;
			/* Pop the old parent off the stack.
			 * Note that stack->pop() TRANSFERS its retained ownership to us;
			 * this means that we are now retaining parent twice - once from
			 * when it was created (if it's a new scene object) or supplied
			 * as the scene, and once when it was pushed onto the parentage
			 * stack.
			 * Therefore, we should release it now to restore balance.
			 */
			parent = stack->pop();
			if(parent)
			{
				/* Transfer ownership of the object from us to the parent */
				parent->add(obj);
				obj->release();
				/* Release our outstanding reference to the parent */
				parent->release();
			}
			break;
/*
		default:
			std::clog << "Ignoring node " << type << ", name = '" << ((const char *) name) << "'\n";
*/
	}
	return true;
}
