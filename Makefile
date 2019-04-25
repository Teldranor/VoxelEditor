CC=g++
HEADER=-IHeader/ -IMyScript/inc/ -IUI/imgui/ -ITinyXml/
LIB=-lSDL2 -lGL
CPP= UI/*.cpp UI/imgui/*.cpp TinyXml/*.cpp Application/*.cpp Graphic/*.cpp Component/*.cpp Cube/*.cpp Factory/*.cpp Input/*.cpp MyScript/src/*.cpp
EXEC=voxel

$(EXEC) : $(CPP)
		$(CC) $(CFLAGS) $(CPP) $(LIB) $(HEADER) -o $(EXEC) Main.cpp
