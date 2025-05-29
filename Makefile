all:
	gcc src/main.c src/pila.c -Iraylib/include -Lraylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm

run: all
	./a.exe

clean:
	del a.exe

PHONY: clean run