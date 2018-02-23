OUT = scene
OBJ = scenetool.o SceneObject.o Scene.o SceneParser.o

CXXFLAGS = `xml2-config --cflags` -g -O0 -W -Wall
LIBS = `xml2-config --libs` -g

all: $(OUT)

clean:
	rm -f $(OUT) $(OBJ)

$(OUT): $(OBJ)
	$(CXX) $(LDFLAGS) -o $(OUT) $(OBJ) $(LIBS)
