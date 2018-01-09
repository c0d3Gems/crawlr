		


		#include <stdio.h>
		#include <string.h>
		#include <stdlib.h>
		#include <unistd.h>
		#include <pthread.h>
		#include <curl/curl.h>


		#define NY_TIMES 	(const char*)"NY_TIMES"
		#define OTHER 		(const char*)"OTHER"
		#define WSJ 		(const char*)"WALL_STREET_JOURNAL"


		#define NY_TIMES_URL 	(const char*)"https://www.nytimes.com/"
		#define WSJ_URL 		(const char*)"https://www.wsj.com/"

struct string
{
	char* content;
	size_t	length;
};


void stringInit(struct string *s)
{
	s->length=0;
	s->content=malloc(s->length + 1);
	if(s->content==NULL)
	{
		printf("malloc() failed\n");
		exit(EXIT_FAILURE);
	}
	s->content[0]='\0';
}

size_t writeFunction(void *ptr, size_t size, size_t nmemb, struct string *s)
{
	size_t new_len = s->length + size*nmemb;

	free(s->content);
	s->content=NULL;
	s->content=malloc(new_len+1);

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


char* simpleGetRequest(const char* url)
{

	CURL *curl;
	CURLcode res;

	curl = curl_easy_init();
	if(curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, url);

		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); 

		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

		res = curl_easy_perform(curl);
		if(res!=CURLE_OK)
			printf("curl_easy_perform() failed with error code: %s\n", curl_easy_strerror(res));
		curl_easy_cleanup(curl);
		
		return (char*) res;
	}
	return (char*) NULL;
}





char* sendGET_request(const char* url, const char* source)
{
	CURL *curl=NULL;
	CURLcode res;

	
	if(url && curl)
	{

		if(source == NY_TIMES)
		{
				struct curl_slist *chunk=NULL; // the structure where we add all of the custom headers to unlock the paid content
				chunk = curl_slist_append(chunk, "Accept:");

				return (char*)res;

		}

		if(source == WSJ)
		{
				struct curl_slist *chunk=NULL;
				chunk = curl_slist_append(chunk, "Accept:");

				return (char*)res;
		}

		res=(CURLcode)simpleGetRequest(url);
		return (char*)res;
	}
	return (char*) NULL;
}



unsigned short verify(const char *source)
{
	if(source==NY_TIMES)
	{
		FILE *nyTimesFileHandler = fopen("nyTimes", "w");




		fclose(nyTimesFileHandler);
		
		nyTimesFileHandler=NULL;
	}
	return 0;
}


void watchdog()
{
	while(1)
	{
		verify(NY_TIMES);
		verify(WSJ);

		sleep(30);
	}
}


char* getContentFromHTML(const char* url)
{




	return (char*)NULL;
}


int main(int argc, char **argv)
{

	printf("Hello, world!\n");
	char *rawContentNyTimes=simpleGetRequest("https://www.nytimes.com");

	//printf("%s\n", rawContentNyTimes);
	// printf("%llu\n", (unsigned long long )strlen(rawContentNyTimes));
	free(rawContentNyTimes);
	return 0;
}

