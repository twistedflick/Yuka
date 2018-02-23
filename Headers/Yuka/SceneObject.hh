/* Copyright 2018 Mo McRoberts.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifndef YUKA_SCENEOBJECT_HH_
# define YUKA_SCENEOBJECT_HH_          1

#include <string>
#include <unordered_map>

#include "decl.h"

class YUKA_EXPORT_ SceneObject
{
public:
	typedef std::unordered_map<std::string, std::string> Properties;
	
	static SceneObject *sceneObjectWithKind(std::string kind, Properties properties);
	
	virtual ~SceneObject();
	
	virtual int add(SceneObject *child);
	virtual int apply(Properties properties);
	
	virtual SceneObject *parent(void);
protected:
	
	class List;
	
	SceneObject(std::string kind);

	std::string kind;
	std::string id;
	SceneObject *container;
	List *children;
};

/* A prop is any kind of potentially-visible scene object
 * which may have physics properties.
 */

class Prop: public SceneObject
{
protected:
	Prop(std::string kind): SceneObject(kind) { };
};

/* Primitives are the group of Prop classes which represent
 * primitive 3D objects: sphere, cuboid, plane, etc.
 */
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
