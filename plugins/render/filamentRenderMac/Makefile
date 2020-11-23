FILAMENT_LIBS=-lfilament -lbackend -lbluegl -lbluevk -lfilabridge -lfilaflat -lutils -lgeometry -lsmol-v -libl
FRAMEWORKS=-framework Cocoa -framework Metal -framework CoreVideo
CC=clang++

main: main.o
	$(CC) -Llib/x86_64/ main.o $(FILAMENT_LIBS) $(FRAMEWORKS) -o main

main.o: main.cpp
	$(CC) -Iinclude/ -std=c++17 -c main.cpp

clean:
	rm -f main main.o

.PHONY: clean