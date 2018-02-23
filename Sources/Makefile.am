
AM_CPPFLAGS = @AM_CPPFLAGS@ @XML_CPPFLAGS@

lib_LTLIBRARIES = libYuka.la

libYuka_la_SOURCES = SceneObject.cc Scene.cc SceneParser.cc

libYuka_la_LDFLAGS = -avoid-version -no-undefined

libYuka_la_LIBADD = @XML_LIBS@


noinst_PROGRAMS = scenetool

scenetool_SOURCES = scenetool.cc 

scenetool_LDADD = libYuka.la
