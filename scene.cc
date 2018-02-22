#include <iostream>

#include <libxml/SAX.h>

class Scene
{
public:
	int load(const char *pathname);
};

int
Scene::load(const char *pathname)
{
	return -1;
}

int
main(int argc, char **argv)
{
	Scene s;
	
	if(argc != 2)
	{
		std::cerr << "Expected a single scene file name argument.\n";
		
		std::cout << "\nUsage:\n\n" <<
			"  " << argv[0] << " FILENAME\n";
		return 0;
	}
	if(s.load(argv[1]))
	{
		std::cerr << argv[0] << ": failed to load scene '" << argv[1] << "'.\n";
		return 1;
	}
	return 0;
}
