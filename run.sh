#!/bin/bash

for i in {01..25}
do
	app=./$i/program$i
	if test -f $app; then
		cd $i

		echo executing $app		
		./program$i
		
		cd ..
	fi
done