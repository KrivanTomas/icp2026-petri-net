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
	
pack: clean
	zip -r petri-net.zip ./src ./doc ./tests ./examples ./Makefile ./Doxyfile ./CMakeLists.txt ./.editorconfig ./README.md ./README.txt

dir_build:
	mkdir -p ./build

clean:
	rm -rf ./doc/html
	rm -rf ./build
