
all: final

final: obj/bmp_viewer.o obj/features.o inc/features.h
	gcc obj/bmp_viewer.o obj/features.o -o final -lSDL2 

obj/bmp_viewer.o: src/bmp_viewer.c inc/features.h
	gcc -c src/bmp_viewer.c -o obj/bmp_viewer.o -iquote inc

obj/features.o: src/features.c inc/features.h
	gcc -c src/features.c -o obj/features.o -iquote inc

clean:
	rm obj/*.o final