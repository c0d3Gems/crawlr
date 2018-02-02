
	#ifndef STRING_H
	#define STRING_H

	

		struct string
		{
			char* content;
			unsigned long long length;
		};
		//standard definition of the string object

	
		unsigned long long getStringLength(char *);
		//Function that returns the length of a string: 0 if null, 1 if empty or more.


		void stringInit(struct string *);
		//function for string basic mallocation.


		unsigned long long findPattern(char*, char*);
		//returns the ending position where the pattern was found in the greater string. 

		unsigned long long findPatternFromPosition(char* str, char* pat, unsigned long long position);
		//find pattern after the given position. 

		unsigned short duplicate(char* a, char *b);
		//returns 1 (true) if str a is equal to str b
		//returns 0 (false) if str a is not equal to str b


		unsigned long long countDigits(unsigned long long number);
		//function that counts how many digits exist in a variable


		char *toString(unsigned long long var, char sign);
		//function that converts a number to a string and returns it
		//the char* needs to be freed after we're done with it

		void flipString(char* a);
		//function that returns the string flipped form end to start
		//ex. abc -> cba

	#endif	