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

SUBDIRS = Parsers Traits Intrinsics Behaviours Scene Props Lights Events .

EXTRA_DIST = version.cc.in

AM_CPPFLAGS = @AM_CPPFLAGS@

## libYuka -- a (shared) library containing the engine

lib_LTLIBRARIES = libYuka.la

libYuka_la_SOURCES = p_Yuka.hh \
	version.cc

libYuka_la_LDFLAGS = -avoid-version -no-undefined

libYuka_la_LIBADD = Traits/libYukaTraits.la \
	Behaviours/libYukaBehaviours.la \
	Props/libYukaProps.la \
	Intrinsics/libYukaIntrinsics.la \
	Parsers/libYukaParsers.la \
	Events/libYukaEvents.la \
	Lights/libYukaLights.la \
	Scene/libYukaScene.la

## scenetool -- a utility for loading a scene and dumping its contents

noinst_PROGRAMS = scenetool

scenetool_SOURCES = scenetool.cc 

scenetool_LDADD = libYuka.la
