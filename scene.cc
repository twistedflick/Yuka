#include <iostream>
#include <iomanip>

#include <libxml/xmlreader.h>

#include "SceneObject.hh"
#include "Scene.hh"
#include "SceneParser.hh"

/* Threading note: unless otherwise noted, it is unsafe to invoke multiple
 * method calls on a single given instance of any of these classes across
 * multiple threads simultaneously, without using some kind of external
 * barrier (such as a POSIX mutex or a spinlock).
 *
 * However, it is perfectly safe to use them in multiple threads so long
 * as no single object is being accessed by two threads at the same time.
 * Particular care must be taken with scenes and the objects within them -
 * if one thread is touching part of a scene, you can't assume it's safe
 * to modify a different part of the scene at the same time in a different
 * thread. In contrast, if you have two threads which are each manipulating
 * independent scenes, then no concurrency issues will arise.
 *
 * This is unquestionably a limitation of the implementation, but it's a
 * limitation which can be removed in future by adding and using locking
 * primitives in certain parts of the code without requiring significant
 * reorganisation.
 */

SceneObject::SceneObject()
{
	std::clog << "++ SceneObject 0x" << std::hex << std::setw(8) << (unsigned long) static_cast<void *>(this) << "\n";
}

SceneObject::~SceneObject()
{
	std::clog << "-- SceneObject 0x" << std::hex << std::setw(8) << (unsigned long) static_cast<void *>(this) << "\n";
}

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
	ret = xmlTextReaderRead(reader);
	/* xmlTextReaderRead() returns 1 for 'more remaining', 0 for 'complete',
	 * any other value for an error
	 */
	while(ret == 1)
	{
		if((ret = processNode(scene)))
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
SceneParser::processNode(Scene *scene)
{
	const xmlChar *name, *ns;
	int type;
	
	type = xmlTextReaderNodeType(reader);
	ns = xmlTextReaderConstNamespaceUri(reader);
	name = xmlTextReaderConstName(reader);
	
	switch(type)
	{
		case XML_READER_TYPE_ELEMENT:
			if(ns)
			{
				std::clog << "Found element, name = '" << ((const char *) ns) << ((const char *) name) << "'\n";
			}
			else
			{
				std::clog << "Found element, name = '" << ((const char *) name) << "'\n";
			}
			break;
		default:
			std::clog << "Ignoring node " << type << ", name = '" << ((const char *) name) << "'\n";
	}
	return 0;
}

Scene::Scene():
	SceneObject()
{
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

int
main(int argc, char **argv)
{
	Scene s;
	
	/* Ensure that we're linked against a compatible version of the
	 * libxml2 runtime
	 */
	LIBXML_TEST_VERSION;
	/* Check command-line arguments */
	if(argc != 2)
	{
		std::cerr << "Expected a single scene file name argument.\n";
		
		std::cout << "\nUsage:\n\n" <<
			"  " << argv[0] << " FILENAME\n";
		return 0;
	}
	/* Attempt to load the scene from the named file */
	if(s.load(argv[1]))
	{
		std::cerr << argv[0] << ": failed to load scene '" << argv[1] << "'.\n";
		return 1;
	}
	/* We don't DO anything with the loaded scene, so we can just
	 * return success after cleaning up.
	 */
	xmlCleanupParser();
	return 0;
}
