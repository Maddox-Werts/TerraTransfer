# Variables
LIBS:= -lSDL2main -lSDL2 -lSDL2_TTF -lSDL2_Image
TARGET:= terratransfer

# Instructions
all: clrscr compile link

clrscr:
	clear

compile:
	g++ -c -I include source/Terra/terra.cpp -o bin/terra.o
	g++ -c -I include source/Terra/app.cpp -o bin/app.o
	g++ -c -I include source/main.cpp -o bin/main.o

link:
	g++ bin/*.o -L lib $(LIBS) -o build/$(TARGET)

cpydat:
	cp -r data build

# Complimentary
run:
	clear
	./build/$(TARGET)
