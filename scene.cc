#include <iostream>

#include <libxml/xmlreader.h>

class Scene
{
public:
	int load(const char *pathname);
protected:
	int processNode(xmlTextReaderPtr reader);
};

int
Scene::load(const char *pathname)
{
	xmlTextReaderPtr reader;
	int ret;

	reader = xmlReaderForFile(pathname, NULL, 0);
	if (!reader)
	{
		return -1;
	}
	ret = xmlTextReaderRead(reader);
	/* xmlTextReaderRead() returns 1 for 'more remaining', 0 for 'complete',
	 * any other value for an error
	 */
	while(ret == 1)
	{
		if((ret = processNode(reader)))
		{
			/* processNode() returns non-zero on error */
			break;
		}
		ret = xmlTextReaderRead(reader);
	}
	xmlFreeTextReader(reader);
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
Scene::processNode(xmlTextReaderPtr reader)
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
