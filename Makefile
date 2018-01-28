#!/bin/bash





all: main.c #build everything
	clear && cc -Wall -lcurl -lpthread -O2 -o crawler main.c src/*

r: crawler  #basic test run 
	clear && ./crawler

v: 	crawler #test run with valgrind memory leak checker
	clear && valgrind --track-origins=yes ./crawler

c: crawler  #clean the binary executable and other files that don't need to be uploaded on github
	clear && rm crawler log.txt

git: main.c
	clear && cp main.c ~/git/c_crawler_for_specific_task/main.c && cp Makefile ~/git/c_crawler_for_specific_task/Makefile && cp src/* ~/git/c_crawler_for_specific_task/src/ && cp include/* ~/git/c_crawler_for_specific_task/include/ 