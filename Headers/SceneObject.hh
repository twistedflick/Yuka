#ifndef SCENEOBJECT_HH_
# define SCENEOBJECT_HH_               1

#include <string>
#include <unordered_map>

class SceneObjectList;

class SceneObject
{
public:
	typedef std::unordered_map<std::string, std::string> Properties;
	
	static SceneObject *sceneObjectWithKind(std::string kind, Properties properties);
	
	virtual ~SceneObject();
	
	int add(SceneObject *child);
	int apply(Properties properties);
	
	SceneObject *parent(void);
protected:
	
	SceneObject(std::string kind);

	std::string kind;
	std::string id;
	SceneObject *container;
	SceneObjectList *children;
};

class Prop: public SceneObject
{
protected:
	Prop(std::string kind): SceneObject(kind) { };
};

class Primitive: public Prop
{
protected:
	Primitive(std::string kind): Prop(kind) { };
};

class Sphere: public Primitive
{
	friend class SceneObject;
protected:
	Sphere(std::string kind): Primitive(kind) { };
};

class Cube: public Primitive
{
	friend class SceneObject;
protected:
	Cube(std::string kind): Primitive(kind) { };
};

#endif /*!SCENEOBJECT_HH_*/
