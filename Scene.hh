#ifndef SCENE_HH_
# define SCENE_HH_                     1

# include "SceneObject.hh"

class Scene: public SceneObject
{
public:
	Scene();
	
	int load(const char *pathname);
};

#endif /*!SCENE_HH_*/
