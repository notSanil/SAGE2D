SOURCE = ./src/main.o
SCENE_MANAGER = ./engine/gameScene/sceneManager.o
ANIMATOR = ./engine/animator/animator.o
OUTPUT = ./build/game.exe
CAMERA = ./engine/camera/camera.o
RENDERER = ./engine/renderer/renderer.o
OBJECTFACTORY = ./engine/gameObject/gameObjectFactory.o
SCENEFACTORY = ./engine/gameScene/gameSceneFactory.o
TEXT = ./engine/renderer/text_renderer.o
POINT = ./engine/transform/point.o

OBJECTS = $(wildcard ./game/objects/*.o)
SCENES = $(wildcard ./game/scenes/*.o)

ENGINE = ./engine/engine.o


LINKER = -Ldependencies/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

all: $(SOURCE) $(SCENE_MANAGER) $(ANIMATOR) $(CAMERA) $(RENDERER) $(OBJECTFACTORY) $(SCENEFACTORY) $(TEXT) $(POINT) $(ENGINE)
	g++ -o $(OUTPUT) $(SOURCE) $(SCENE_MANAGER) $(ANIMATOR) $(CAMERA) \
$(RENDERER) $(TEXT) $(OBJECTFACTORY) $(SCENEFACTORY) $(POINT) $(OBJECTS) $(SCENES) $(ENGINE) $(LINKER)
