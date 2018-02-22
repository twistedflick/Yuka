#ifndef SCENEOBJECT_HH_
# define SCENEOBJECT_HH_               1

class SceneObjectList;

class SceneObject
{
public:
	SceneObject();
	virtual ~SceneObject();
	
	int add(SceneObject *child);
	SceneObject *parent(void);
protected:
	SceneObject *container;
	SceneObjectList *children;
};

#endif /*!SCENEOBJECT_HH_*/
