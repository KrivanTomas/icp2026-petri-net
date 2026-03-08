# Makefile
# Authors:
# 	Tomáš Křivan

.PHONY: build doxygen pack clean

build:
	cd ./src && make

doxygen:
	echo todo

pack:
	echo todo

clean:
	rm -rf ./doc/*
	echo "todo others"
