#include <iostream>
#include <iomanip>
#include <cstring>
#include <libxml/xmlreader.h>

#include "SceneObject.hh"
#include "Scene.hh"
#include "SceneParser.hh"

#define NS_SCENE                       "https://twistedflick.github.io/scene/"

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

/* This is a private implementation of linked list to track scene objects
 * which is used by a SceneObject to organise the graph.
 */

class SceneObjectList
{
public:
	SceneObjectList();
	virtual ~SceneObjectList();
	
	int add(SceneObject *object);
protected:
	struct Entry
	{
		Entry *prev, *next;
		SceneObject *obj;
	};
	
	Entry *first, *last;
};

SceneObjectList::SceneObjectList() :
	first(NULL),
	last(NULL)
{	
}

SceneObjectList::~SceneObjectList()
{
	SceneObjectList::Entry *e, *next;

	for(e = first; e; e = next)
	{
		next = e->next;
		delete e->obj;
		delete e;
	}
}

int
SceneObjectList::add(SceneObject *object)
{
	SceneObjectList::Entry *e;
	
	e = new SceneObjectList::Entry();
	e->prev = last;
	e->obj = object;
	if(first)
	{
		last->next = e;
	}
	else
	{
		first = e;
	}
	last = e;
	return 0;
}

SceneObject::SceneObject():
	container(NULL),
	children(NULL)
{
	std::clog << "++ SceneObject 0x" << std::hex << std::setw(8) << (unsigned long) static_cast<void *>(this) << "\n";
}

SceneObject::~SceneObject()
{
	delete children;
	std::clog << "-- SceneObject 0x" << std::hex << std::setw(8) << (unsigned long) static_cast<void *>(this) << "\n";
}

/* Add a scene object to the scene graph as a child of this one. This won't
 * necessarily always make sense from any sort of rendering or physics
 * perspective, but it's easier to treat all objects as equivalent and having
 * the same basic set of capabilities from the outset than it is to attempt
 * prevent hypothetical instances of programmer error which are unlikely to
 * actually be damaging (even if irritating).
 */
int
SceneObject::add(SceneObject *child)
{
	if(!children)
	{
		children = new SceneObjectList();
	}
	children->add(child);
	child->container = this;
	return 0;
}

SceneObject *
SceneObject::parent(void)
{
	return container;
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
	const char *name, *ns;
	int type;
	SceneObject *obj;
	
	type = xmlTextReaderNodeType(reader);
	ns = (const char *) xmlTextReaderConstNamespaceUri(reader);
	name = (const char *) xmlTextReaderConstName(reader);
	
	switch(type)
	{
		case XML_READER_TYPE_ELEMENT:
			if(ns)
			{
				std::clog << "Found element, name = '" << ns << name << "'\n";
				if(strcmp(ns, NS_SCENE))
				{
					std::cerr << "Scene description contains XML elements in an unsupported namespace (<" << ns << "> was specified where <" << NS_SCENE << "> was expected)\n";
					return -1;
				}
				if(root)
				{
					if(!strcmp(ns, NS_SCENE) && !strcmp(name, "scene"))
					{
						/* Skip the root, because this->parent is already set */
						root = false;
						return 0;
					}
					else
					{
						std::cerr << "Expected a root <scene /> element, found <" << name << " />\n";
						return -1;
					}
				}
			}
			else
			{
				std::clog << "Found element, name = '" << ((const char *) name) << "'\n";
				std::cerr << "Scene description contains XML elements without a namespace at <" << name << ">\n";
				return -1;
			}
			obj = new SceneObject();
			parent->add(obj);
			parent = obj;
			break;
		case XML_READER_TYPE_END_ELEMENT:
			std::clog << "End of element, name = '" << ((const char *) name) << "'\n";
			parent = parent->parent();
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
