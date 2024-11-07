bin/test-libolingc: lib/libolingc.a src/test/test-phonology.c
	$(info Creating testing binary...)
	gcc -o bin/test-libolingc -I ./include src/test/test-phonology.c lib/libolingc.a
lib/libolingc.a: obj/phonology.o
	$(info Creating static library...)
	ar rcs lib/libolingc.a obj/phonology.o
lib/libolingc.so: obj/phonology.o
	$(info Creating shared library...)
	gcc -shared -o lib/libolingc.so obj/phonology.o
obj/phonology.o: src/phonology.c include/phonology.h
	$(info Creating objects...)
	gcc -fPIC -o obj/phonology.o -I ./include -c src/phonology.c
