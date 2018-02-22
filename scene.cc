#include <iostream>

#include <libxml/xmlreader.h>

class Scene
{
public:
	int load(const char *pathname);
};

class SceneParser
{
public:
	static SceneParser *parserForFile(const char *pathname);
	
	virtual ~SceneParser();
	
	int parseIntoScene(Scene *scene);
protected:
	xmlTextReaderPtr reader;
	
	SceneParser(xmlTextReaderPtr reader);
	
	int processNode(Scene *scene);
};

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

SceneParser::SceneParser(xmlTextReaderPtr reader): reader(reader)
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
	if(ns)
	{
		std::clog << "Found node type " << type << ", name = '" << ((const char *) ns) << ((const char *) name) << "'\n";
	}
	else
	{
		std::clog << "Found node type " << type << ", name = '" << ((const char *) name) << "'\n";
	}
	return 0;
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
