

	#include "../include/crawler.h"



		void simpleGetRequest(const char* url)
		{
			CURL *curl;
			CURLcode res;

			curl = curl_easy_init();

			// printf("Threaded writing says: %s\n", url);

			curl_easy_cleanup(curl);
			curl=NULL;

		}