#ifndef SCENE_HH_
# define SCENE_HH_                     1

# define NS_SCENE                      "https://twistedflick.github.io/scene/"

# include "SceneObject.hh"

class Scene: public SceneObject
{
public:
	Scene(): SceneObject(NS_SCENE "scene") { };
	
	int load(const char *pathname);
};

#endif /*!SCENE_HH_*/
