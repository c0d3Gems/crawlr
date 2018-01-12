		


		#include <stdio.h>
		#include <string.h>
		#include <stdlib.h>
		#include <unistd.h>
		#include <pthread.h>
		#include <curl/curl.h>

		#define DOWNLOAD_DIRECTORY 		(const char*)"dlds/"








size_t getStringLength(char *str)
{
	if(str)
	{
		char *p=&str[0];
		size_t i=1;
		while(*p!='\0'){p++;i++;}
		return i;
	}
	return 0;
}



struct string
{
	char* content;
	size_t	length;
};

void stringInit(struct string *s)
{
	s->length=0;
	s->content=malloc(s->length + 1);
	memset(s->content, '\0', s->length+1);
	if(s->content==NULL)
	{
		printf("malloc() failed\n");
		exit(EXIT_FAILURE);
	}
	s->content[0]='\0';
}

size_t findPattern(char* str, char* pat)
{
	size_t i=0,j=0;
	for(i=0;str[i]!='\0';++i)
	{
		if(str[i]==pat[j])
		{
			while(str[i]==pat[j]){ ++i; ++j; }
			if(pat[j]=='\0')
				return i;
			else
				{i-=j;j=0;}
		}
	}
	return 0;
}

char *getSourceFromUrl(const char* str)
{
	if(!str) return (char*)NULL;
	size_t i=0,j=0, length=strlen(str);
	char *buffer=malloc(length);
	memset(buffer, '\0', length);
	for (i = 0; str[i]!='\0'; ++i)
	{
		if((str[i]>='a'&&str[i]<='z') || (str[i]>='A'&&str[i]<='Z') || str[i]=='.' )
			buffer[j]=str[i];
	}
	return buffer;
}

size_t anotherWriteFunction(void *ptr, size_t size, size_t nmemb, struct string *s)
{
	size_t new_len = s->length + size*nmemb;

	free(s->content);
	s->content=NULL;
	s->content=malloc(new_len+1);
	memset(s->content, '\0', new_len+1);

	if(s->content==NULL)

	{
		printf("ERROR realloc() \n");
		exit(EXIT_FAILURE);
	}
	memcpy(s->content+s->length, ptr, size*nmemb);
	s->content[new_len]='\0';
	s->length=new_len;

	return size*nmemb;
}

const char* genIndexFileName(char *str)
{
	if(str==NULL || getStringLength(str)<2)
	{
		printf("The parameter should not be null\n");
		exit(EXIT_FAILURE);
	}
	size_t i=0,j=0, strSize=getStringLength(str), totalSize=strSize+4;
	char *res=malloc(totalSize);
	if(res==NULL)
	{
		printf("ERROR mallocing the space for genIndexFileName function.\nMaybe not enough free memory?!\n");
		exit(EXIT_FAILURE);
	}
	memset(res, '\0', totalSize);
	for(i=0;str[i]!='\0';++i)
	{
		if((str[i]>='a'&&str[i]<='z')||\
		   (str[i]>='A'&&str[i]<='Z')||\
		   (str[i]>='0'&&str[i]<='9')||\
		   	str[i]=='.')
			{
				res[j]=str[i];
				j++;
			}
	}
	return res;
}

size_t writeFunction(void* payload, size_t size, size_t nmemb, char* fileStream, char *url)
{
	if(payload)
	{
	

		const char *indexFileHandlerName=genIndexFileName(url);

		struct string *auxString;

		auxString->length=size*nmemb;

		auxString->content=malloc(auxString->length +1);

		memset(auxString->content, '\0', auxString->length);

		memcpy(auxString->content, payload, auxString->length);





		// FILE *nyTimesFileHandler=fopen(indexFileHandlerName, "r");

		// fseek(nyTimesFileHandler, 0L, SEEK_END);

		// size_t currentBufferSize=ftell(nyTimesFileHandler);

		// fclose(nyTimesFileHandler);

		// nyTimesFileHandler=NULL;




	}


	return 	0;
}





char* simpleGetRequest(const char* url)
{

	CURL *curl;
	CURLcode res;

	curl = curl_easy_init();
	if(curl)
	{
		struct string s;
		char * indexFileName=genIndexFileName(url);
		stringInit(&s);

		curl_easy_setopt(curl, CURLOPT_URL, url); //provide the url link we want to visit

		// curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction); //call a custom writefunction instead of fwrite

		// curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);//where to write the output 

		curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); // do not check for the ssl certificate authenticity 

		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);	// allow redirections

		res = curl_easy_perform(curl);

		if(res!=CURLE_OK)
			printf("curl_easy_perform() failed with error code: %s\n", curl_easy_strerror(res));
		
		curl_easy_cleanup(curl);
		


		
		s.content[s.length]='\0';
		
		FILE *outputFile = fopen(indexFileName, "w");
		
		fwrite(s.content, s.length, 1, outputFile);
		
		fclose(outputFile);
		
		outputFile=NULL;
		

		free(indexFileName);
		indexFileName=NULL;

		printf("Size is: %llu bytes\n", (unsigned long long )s.length);


		return (char*) &s.content[0];
	}
	return (char*) NULL;
}


int main(int argc, char **argv)
{



	printf("Crawler initialized succesfully!\nNumber of arguments: %d\n\n\n\n",argc);




	const char* sources[]={									
		"https://www.nytimes.com/", 	
		"https://www.wsj.com/",	
		"https://techcrunch.com/", 
		"https://www.theverge.com/",
		"https://www.recode.net/",
		"https://www.cnet.com/news/", 
		"https://www.reuters.com/",
		"https://www.theguardian.com/us",
		"http://www.bbc.com/news",
		"http://www.telegraph.co.uk/news/",
		(const char*)NULL
	};

	size_t i=0;
	printf("THE NEWS SOURCES ARE:\n\n");
	for(i=0;sources[i];++i)
	{
		printf("\t%s\n", sources[i]);
	}
	printf("\n");

	printf("Pattern found? %s\t%s %lu\n", sources[0], "nytimes.com", findPattern((char*)sources[0], "http"));
	printf("Pattern found? %s\t%s %lu\n", sources[0], "nytimes.com", findPattern((char*)sources[1], "wsj.com"));
	printf("Pattern found? %s\t%s %lu\n", sources[0], "nytimes.com", findPattern((char*)sources[2], "techcrunch.com"));
	printf("Pattern found? %s\t%s %lu\n", sources[0], "nytimes.com", findPattern((char*)sources[0], "nytimes.com"));
	printf("Pattern found? %s\t%s %lu\n", sources[0], "nytimes.com", findPattern((char*)sources[0], "nytimes.com"));
	printf("Pattern found? %s\t%s %lu\n", sources[0], "nytimes.com", findPattern((char*)sources[0], "nytimses.com"));


	char *str=genIndexFileName((char*)sources[1]);

	printf("Get index file name of %s: %s\n", sources[1], str);
	free(str);
	str=NULL;

	return 0;
}


