complier= gcc
pp= python3
DEPS = src/hellomake.h


install: src/hellomake.c src/hellofunc.c
	rm -rf build
	mkdir build
	$(complier) -o build/hellomake src/hellomake.c src/hellofunc.c -I.


start:	build/hellomake
	build/hellomake


clean:
	rm -rf build

testPy:
	$(pp) -m http.server 8000