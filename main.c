		
	

		#include	"include/crawler.h"





// size_t writeFunction(void* payload, size_t size, size_t nmemb, char* fileStream, char *url)
// {
// 	if(payload!=NULL)
// 	{
	

// 		// const char *indexFileHandlerName=genIndexFileName(url);

// 		// struct string *auxString;

// 		// auxString->length=size*nmemb;

// 		// auxString->content=malloc(auxString->length +1);

// 		// memset(auxString->content, '\0', auxString->length);

// 		// memcpy(auxString->content, payload, auxString->length);





// 		// FILE *nyTimesFileHandler=fopen(indexFileHandlerName, "r");

// 		// fseek(nyTimesFileHandler, 0L, SEEK_END);

// 		// size_t currentBufferSize=ftell(nyTimesFileHandler);

// 		// fclose(nyTimesFileHandler);

// 		// nyTimesFileHandler=NULL;




// 	}
// 	else
// 	{
// 		printf("ERROR writeFunction(): The payload should not be empty\n");
// 		exit(EXIT_FAILURE);
// 	}


// 	return 	0;
// }



/////////////////////////////////////////

// char* simpleGetRequest(const char* url)
// {

// 	CURL *curl;
// 	CURLcode res;

// 	curl = curl_easy_init();
// 	if(curl)
// 	{
// 		struct string s;
// 		char * indexFileName=genIndexFileName(url);
// 		stringInit(&s);

// 		curl_easy_setopt(curl, CURLOPT_URL, url); //provide the url link we want to visit

// 		// curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction); //call a custom writefunction instead of fwrite

// 		// curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);//where to write the output 

// 		curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

// 		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); // do not check for the ssl certificate authenticity 

// 		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);	// allow redirections

// 		res = curl_easy_perform(curl);

// 		if(res!=CURLE_OK)
// 			printf("curl_easy_perform() failed with error code: %s\n", curl_easy_strerror(res));
		
// 		curl_easy_cleanup(curl);
		


		
// 		s.content[s.length]='\0';
		
// 		FILE *outputFile = fopen(indexFileName, "w");
		
// 		fwrite(s.content, s.length, 1, outputFile);
		
// 		fclose(outputFile);
		
// 		outputFile=NULL;
		

// 		free(indexFileName);
// 		indexFileName=NULL;

// 		printf("Size is: %llu bytes\n", (unsigned long long )s.length);


// 		return (char*) &s.content[0];
// 	}
// 	return (char*) NULL;
// }


int main(int argc, char **argv)
{
	printf("Crawler initialized succesfully!\nNumber of arguments: %d\n\n\n\n",argc);

	LOGGING_MODE = 0x0;
	LOGFILE_SIZE=getFileSize(LOGFILE);

	printf("[LOGFILE_SIZE] is: %llu bytes!\n", LOGFILE_SIZE);

	if(argc>1)
	{
		size_t i=0;
		for(i=0;i<argc;++i)
		{
			if(duplicate(argv[i], "-q"))
			{
				LOGGING_MODE = 0x1;
				//quiet (prints only in logfile, but not in the stdout)
				break;
			}
			if(duplicate(argv[i], "-m"))
			{
				LOGGING_MODE = 0x2;
				//muted (does not print to either logfile or stdout)
				break;
			}
		}
	}

	printf("The LOGGING_MODE is: %u\n", (unsigned long)LOGGING_MODE);



	printf("THE NEWS SOURCES ARE:\n\n");
	size_t i=0;
	for(i=0;sources[i];++i)
		printf("\t%s\n", sources[i]);

	const unsigned long long NUMBER_OF_WRAPPER_OBJECTS=(const unsigned long long)i;

	struct wrapperStruct* wrapperArray[(const unsigned long long)i];


	checkForNewContent(sources, NUMBER_OF_WRAPPER_OBJECTS);


	// size_t i=0;

	// some testing

	for(i=0;sources[i];++i)
	{
		char *fIndex=genIndexFileName(sources[i]);
		char *fpath=getFilePath(fIndex);
		printf("The indexFilePath for %s is:\t\t%s\n", fIndex, fpath);
		free(fIndex);
		fIndex=NULL;
		free(fpath);
		fpath=NULL;
	}




	printf("\n");
	printf("Pattern found? %s\t%s %llu\n", sources[0], "nytimes.com", findPattern((char*)sources[0], "http"));
	printf("Pattern found? %s\t%s %llu\n", sources[1], "wsj.com", findPattern((char*)sources[1], "wsj.com"));
	printf("Pattern found? %s\t%s %llu\n", sources[2], "techcrunch.com", findPattern((char*)sources[2], "techcrunch.com"));
	printf("Pattern found? %s\t%s %llu\n", sources[0], "nytimes.com", findPattern((char*)sources[0], "nytimes.com"));
	printf("Pattern found? %s\t%s %llu\n", sources[0], "nytimes.com", findPattern((char*)sources[0], "nytimes.com"));
	printf("Pattern found? %s\t%s %llu\n", sources[0], "nytimes.com", findPattern((char*)sources[0], "nytimes.com"));


	printf("The file size of main.c is: %llu bytes\n", getFileSize((const char*)"main.c"));

	struct timeFormat* time=getCurrentTime();

		printf("The current time is: %u:%u:%u\n", time->hour, time->minute, time->second);



	
	char *timeHeader=getTimeHeader(time);
	printf("%s\n", timeHeader);
	

	free(timeHeader);
	timeHeader=NULL;

	free(time);
	time=NULL;

	


	printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n\n\n\n\n");






	wrapperArrayInit();

	printSources();
	printPaths();

	freeWrapperArray();


	return 0;
}


