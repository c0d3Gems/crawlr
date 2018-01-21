#!/bin/bash





all: main.c
	clear && cc -Wall -lcurl -lpthread -O2 -o crawler main.c src/*

r: crawler
	clear && ./crawler

v: 	crawler
	clear && valgrind --track-origins=yes ./crawler


rm: crawler
	clear && rm crawler