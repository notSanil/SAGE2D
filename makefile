SOURCE = ./src/main.o
SCENE_MANAGER = ./engine/gameScene/sceneManager.o
ANIMATOR = ./engine/animator/animator.o
OUTPUT = ./build/game.exe
CAMERA = ./engine/camera/camera.o
RENDERER = ./engine/renderer/renderer.o


LINKER = -Ldependencies/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf


all: $(SOURCE) $(SCENE_MANAGER) $(ANIMATOR) $(CAMERA) $(RENDERER)
	g++ -o $(OUTPUT)  $(SOURCE) $(SCENE_MANAGER) $(ANIMATOR) $(CAMERA) $(RENDERER) $(LINKER)

clean:
	$(RM) game.exe

launch: ./build/game.exe
	./build/game.exe