

	#include "../include/crawler.h"

		const char* sources[11];
		const char* fpath[11];

		void simpleGetRequest(const char* url)
		{
			CURL *curl;
			CURLcode res;

			curl = curl_easy_init();

			// printf("Threaded writing says: %s\n", url);

			curl_easy_cleanup(curl);
			curl=NULL;

		}

		void customGetRequest(const char* url)
		{
			size_t i=0;
			for(i=0;sources[i]!=NULL;++i)
			{
				printf("\tEXTERN CONST CHAR ARRAY %s\n", sources[i]);
				// if( duplicate(url, sources[i]) && i==0 )//nytimes
				// {
				// 	printf("\t\t\tREACHED NEW YORK TIMES STAGE\n");
				// 	break;
				// }
			}
		}