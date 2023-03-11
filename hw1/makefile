complier= gcc
pp= python3
DEPS = src/hellomake.h


install: src/hellomake.c src/19050111068.c
	rm -rf build
	mkdir build
	$(complier) -o build/main src/hellomake.c src/19050111068.c -I.


start:	build/main
	build/main


clean:
	rm -rf build

testPy:
	$(pp) -m http.server 8000