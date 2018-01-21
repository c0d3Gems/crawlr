
	#ifndef STRING_H
	#define STRING_H

	

		extern struct string
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



		unsigned short duplicate(char* a, char *b);
		//returns 1 (true) if str a is equal to str b
		//returns 0 (false) if str a is not equal to str b

	#endif	