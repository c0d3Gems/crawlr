#!/bin/bash





all: crawler.c
	clear && cc -Wall -lcurl -lpthread -O2 crawler.c -o crawler

r: crawler
	clear && ./crawler

v: 	crawler
	clear && valgrind --track-origins=yes ./crawler


rm: crawler
	clear && rm crawler