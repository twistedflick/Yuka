## Copyright 2018 Mo McRoberts.
##
##  Licensed under the Apache License, Version 2.0 (the "License");
##  you may not use this file except in compliance with the License.
##  You may obtain a copy of the License at
##
##      http://www.apache.org/licenses/LICENSE-2.0
##
##  Unless required by applicable law or agreed to in writing, software
##  distributed under the License is distributed on an "AS IS" BASIS,
##  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
##  See the License for the specific language governing permissions and
##  limitations under the License.

AM_CPPFLAGS = @AM_CPPFLAGS@ @XML_CPPFLAGS@

lib_LTLIBRARIES = libYuka.la

libYuka_la_SOURCES = p_Yuka.hh \
	Trait.cc Debuggable.cc Identifiable.cc Scriptable.cc Flexible.cc Spatial.cc \
	Vector.cc Point.cc Orientation.cc Size.cc \
	Object.cc \
	SceneObject.cc SceneObjectList.cc \
	Scene.cc \
	Group.cc \
	Prop.cc \
	Primitive.cc Sphere.cc Cube.cc \
	Light.cc PointLight.cc \
	SceneParser.cc XMLSceneParser.cc \
	Behaviour.cc Transform.cc

libYuka_la_LDFLAGS = -avoid-version -no-undefined

libYuka_la_LIBADD = @XML_LIBS@


noinst_PROGRAMS = scenetool

scenetool_SOURCES = scenetool.cc 

scenetool_LDADD = libYuka.la
