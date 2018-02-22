OUT = scene
OBJ = scene.o

CXXFLAGS = `xml2-config --cflags` -g -O0
LIBS = `xml2-config --libs` -g

all: $(OUT)

$(OUT): $(OBJ)
	$(CXX) $(LDFLAGS) -o $(OUT) $(OBJ) $(LIBS)
