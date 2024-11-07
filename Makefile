
lib/libolingc.so: obj/phonology.o
	gcc -v -shared -o lib/libolingc.so obj/phonology.o
obj/phonology.o: src/phonology.c include/phonology.h
	gcc -v -fPIC -o obj/phonology.o -I ./include -c src/phonology.c
