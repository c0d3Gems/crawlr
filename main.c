		
	

		#include	"include/crawler.h"



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




	// printf("\n");
	// printf("Pattern found? %s\t%s %llu\n", sources[0], "nytimes.com", findPattern((char*)sources[0], "http"));
	// printf("Pattern found? %s\t%s %llu\n", sources[1], "wsj.com", findPattern((char*)sources[1], "wsj.com"));
	// printf("Pattern found? %s\t%s %llu\n", sources[2], "techcrunch.com", findPattern((char*)sources[2], "techcrunch.com"));
	// printf("Pattern found? %s\t%s %llu\n", sources[0], "nytimes.com", findPattern((char*)sources[0], "nytimes.com"));
	// printf("Pattern found? %s\t%s %llu\n", sources[0], "nytimes.com", findPattern((char*)sources[0], "nytimes.com"));
	// printf("Pattern found? %s\t%s %llu\n", sources[0], "nytimes.com", findPattern((char*)sources[0], "nytimes.com"));


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

	printf("findPat(): %llu\n", findPattern("This is fucking awesome!", "This"));






	// wrapperArrayInit();

	// printSources();
	// printPaths();

	// freeWrapperArray();


	FILE *testDownloadFile=fopen("test.html", "w");
	if(testDownloadFile){
		customGetRequest("https://www.wsj.com/articles/how-j-d-power-was-acquired-by-a-chinese-company-shrouded-in-mystery-1517426465", testDownloadFile);
	fclose(testDownloadFile);
	}





	FILE *testFileHandler=fopen("test.html", "r");
	if(testFileHandler)
	{
		unsigned long long testFileSize=getFileSize("test.html");
		char *rawHtml=malloc(testFileSize+1);
		memset(rawHtml, '\0', testFileSize+1);
		fread(rawHtml, testFileSize, 1, testFileHandler);
		struct string** str;
		extractLinks(rawHtml, str);

		free(rawHtml);
		rawHtml=NULL;
		fclose(testFileHandler);
		testFileHandler=NULL;
	}
	else
	{
		printLog("Main() Could not open file for test writing in simple get request");
		exit(EXIT_FAILURE);
	}


	return 0;
}


