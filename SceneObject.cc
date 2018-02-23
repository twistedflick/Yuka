#include <iostream>
#include <iomanip>

#include "Scene.hh"
#include "SceneObject.hh"

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

SceneObject *
SceneObject::sceneObjectWithKind(std::string kind, SceneObject::Properties properties)
{
	SceneObject *obj = NULL;
	
	/* We could accomplish this with a map of constructors, or something of
	 * that ilk
	 */
	if(kind == NS_SCENE "sphere")
	{
		obj = new Sphere(kind);
	}
	else if(kind == NS_SCENE "cube")
	{
		obj = new Cube(kind);
	}
	if(obj)
	{
		if(obj->apply(properties) < 0)
		{
			/* There was a hard error applying the properties */
			delete obj;
			return NULL;
		}
	}
	return obj;
}

SceneObject::SceneObject(std::string kind):
	kind(kind),
	container(NULL),
	children(NULL)
{
	std::clog << "++ SceneObject[0x" << std::hex << std::setw(8) << (unsigned long) static_cast<void *>(this) << "] <" << kind << ">\n";
}

SceneObject::~SceneObject()
{
	delete children;
	if(id.length())
	{
		std::clog << "-- SceneObject[" << id << "=0x" << std::hex << std::setw(8) << (unsigned long) static_cast<void *>(this) << "] <" << kind << ">\n";
	}
	else
	{
		std::clog << "-- SceneObject[0x" << std::hex << std::setw(8) << (unsigned long) static_cast<void *>(this) << "] <" << kind << ">\n";
	}
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

/* Apply a SceneObject::Properties map to this object, warning about any
 * properties we don't understand. Descendents should override this method
 * to catch properties it knows about before invoking this implementation.
 */
int
SceneObject::apply(SceneObject::Properties properties)
{
	SceneObject::Properties::iterator i;
	int e;
	
	e = 0;
	for(i = properties.begin(); i != properties.end(); ++i)
	{
		if(i->first == "@id")
		{
			id = i->second;
			continue;
		}
		std::clog << "Warning: Unsupported property '" << i->first << "' in definition of <" << kind << ">\n";
		e = 1;
	}
	return e;
}
