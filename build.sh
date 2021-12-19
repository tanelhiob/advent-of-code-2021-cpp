#!/bin/bash

for i in {01..25}
do
	main=./$i/$i.cpp
	if test -f $main; then
		echo building $main
		mkdir -p ./release/$i
		clang++ -Ofast -o ./release/$i/program$i $main
		cp ./$i/input.txt ./release/$i/input.txt
	fi
done

cp ./run.sh ./release/