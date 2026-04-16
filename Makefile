# Makefile
# Authors:
# 	Tomáš Křivan

.PHONY: build doxygen pack clean

build: dir_build
	cd ./build && cmake ..
	cd ./build && make

doxygen:
	echo todo

pack:
	echo todo

dir_build:
	mkdir -p ./build

clean:
	rm -rf ./doc/doxygen
	rm -rf ./build
	echo "todo others"
