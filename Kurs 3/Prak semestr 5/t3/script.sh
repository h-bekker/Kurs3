#!/bin/bash
make

for i in ~/Kurs\ 3/Prak\ semestr\ 5/Task0/t3/encrypt/*; do
	echo "================================================";
	echo "Test name: ${i}:";
	cat "$i/request.txt";
	echo "RUN:";
	./prog1 "$i/request.txt";
	
	echo "EXPECTED:"
	cat "${i}"/exp*.txt
	echo "================================================"
done;
