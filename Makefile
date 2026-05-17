# Makefile
# Authors:
# 	Tomáš Křivan

.PHONY: build run doxygen pack clean

build: dir_build
	cd ./build && cmake ..
	cd ./build && make

run: build
	./build/main 

doxygen:
	doxygen
	
pack:
	echo todo

dir_build:
	mkdir -p ./build

clean:
	rm -rf ./doc/doxygen
	rm -rf ./build
	echo "todo others"
