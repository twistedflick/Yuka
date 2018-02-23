#ifndef YUKA_SCENE_HH_
# define YUKA_SCENE_HH_                1

# define NS_YUKA                       "https://twistedflick.github.io/Yuka/"

# include "SceneObject.hh"
# include "decl.h"

class YUKA_EXPORT_ Scene: public SceneObject
{
public:
	Scene(): SceneObject(NS_YUKA "scene") { };
	
	int load(const char *pathname);
};

#endif /*!SCENE_HH_*/
