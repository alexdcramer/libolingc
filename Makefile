objs := obj/phonology.o
libs := lib/libolingc.a lib/libolingc.so
bins := bin/test-libolingc

system_includes := /usr/include/olingc/phonology.h

compile: lib/libolingc.a lib/libolingc.so
install: compile /usr/lib/libolingc.so /usr/include/olingc/phonology.h
test: compile install bin/test-libolingc
	bin/test-libolingc

bin/test-libolingc: /usr/lib/libolingc.so $(system_includes)
	$(info Creating testing binary...)
	gcc -o bin/test-libolingc src/test/test-phonology.c -lolingc
/usr/lib/libolingc.so: lib/libolingc.so
	cp lib/libolingc.so /usr/lib/libolingc.so
	ldconfig -n -v /usr/lib
/usr/include/olingc/phonology.h: include/phonology.h
	mkdir /usr/include/olingc
	cp include/phonology.h /usr/include/olingc/phonology.h
lib/libolingc.a: obj/phonology.o
	$(info Creating static library...)
	ar rcs lib/libolingc.a obj/phonology.o
lib/libolingc.so: obj/phonology.o
	$(info Creating shared library...)
	gcc -shared -o lib/libolingc.so obj/phonology.o
obj/phonology.o: src/phonology.c include/phonology.h
	$(info Creating objects...)
	gcc -fPIC -o obj/phonology.o -I ./include -c src/phonology.c

clean:
	rm $(objs) $(libs) $(bins)
