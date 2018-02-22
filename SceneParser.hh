#ifndef SCENEPARSER_HH_
# define SCENEPARSER_HH_               1

#include <libxml/xmlreader.h>

#include "Scene.hh"

class SceneParser
{
public:
	static SceneParser *parserForFile(const char *pathname);
	
	virtual ~SceneParser();
	
	int parseIntoScene(Scene *scene);
protected:
	xmlTextReaderPtr reader;
	SceneObject *parent;
	
	SceneParser(xmlTextReaderPtr reader);
	
	int processNode(Scene *scene);
};

#endif /*!SCENEPARSER_HH_*/
