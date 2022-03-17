SOURCE = ./src/main.o
OUTPUT = ./build/game.exe
ENGINE_COMPONENTS_SRC = $(wildcard engine/src/Sage/*/*.cpp)
ENGINE_COMPONENTS = $(ENGINE_COMPONENTS_SRC:.cpp=.o)
ENGINE = ./engine/src/Sage/engine.o

OBJECTSRC = $(wildcard game/objects/*.cpp)
OBJECTS = $(OBJECTSRC:.cpp=.o)
SCENESSRC = $(wildcard game/scenes/*.cpp)
SCENES = $(SCENESSRC:.cpp=.o)

CXXFLAGS = -Idependencies/include/ -Iengine/src -Igame/ -Wall


LINKER = -Ldependencies/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

all: $(SOURCE) $(ENGINE_COMPONENTS) $(OBJECTS) $(SCENES) $(ENGINE)
	g++ -o $(OUTPUT) $(SOURCE) $(ENGINE_COMPONENTS) $(OBJECTS) $(SCENES) $(ENGINE) $(LINKER)

%.o: %.cpp
	g++ -c $(CXXFLAGS) $< -o $@

clean: 
	rm -f $(ENGINE_COMPONENTS) $(OBJECTS) $(SCENES) $(ENGINE) $(SOURCE)
	echo "Project Cleaned"