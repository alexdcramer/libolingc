
lib/libolingc.so: obj/phonology.o
	gcc -shared -o lib/libolingc.so obj/phonology.o
obj/phonology.o: src/phonology.c include/phonology.h
	gcc -fPIC -o obj/phonology.o -I ./include -c src/phonology.c
