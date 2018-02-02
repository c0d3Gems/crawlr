

	#ifndef REQUESTS_H
	#define REQUESTS_H

		
	
		
		void customGetRequest(const char* url, FILE* fHandler);
		//function that performs a simple get request to the url mentioned as a parameter
	
		
		void simpleGetRequest(const char*);
		//function that performs a custom get request to the url mentioned as a parameter, with custom headers predefined 
		

	#endif	