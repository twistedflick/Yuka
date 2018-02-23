#ifndef YUKA_SCENEPARSER_HH_
# define YUKA_SCENEPARSER_HH_          1

#include <libxml/xmlreader.h>

#include "Scene.hh"

#include "decl.h"

class YUKA_EXPORT_ SceneParser
{
public:
	static SceneParser *parserForFile(const char *pathname);
	
	virtual ~SceneParser();
	
	int parseIntoScene(Scene *scene);
protected:
	xmlTextReaderPtr reader;
	SceneObject *parent;
	bool root;
	
	SceneParser(xmlTextReaderPtr reader);
	
	int processNode();
};

#endif /*!SCENEPARSER_HH_*/
