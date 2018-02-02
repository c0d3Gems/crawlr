

	#include "../include/crawler.h"

		
		void customGetRequest(const char* url, FILE* fHandler)
		{
			CURL *curl;
			CURLcode res;

			curl = curl_easy_init();
			struct curl_slist *list = NULL;

			// printf("Threaded writing says: %s\n", url);
			if(curl)
			{

				//start of custom headers
				//if(duplicate(url, sources[1]))//custom headers for wsj
				//{
					list = curl_slist_append(list, "cookie: DJSESSION=country=us||continent=us||region=||city=ny||zip=||ORCS=us; wsjregion=europe; usr_bkt=ixi4E5ylqa;");
					list = curl_slist_append(list, "accept-encoding: gzip, deflate, br");
					list = curl_slist_append(list, "accept-language: en-US,en;q=0.9,und;q=0.8,da;q=0.7");
					list = curl_slist_append(list, "upgrade-insecure-requests: 1");
					list = curl_slist_append(list, "user-agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.84 Safari/537.36");
					list = curl_slist_append(list, "accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8");
					list = curl_slist_append(list, "cache-control: max-age=0");
					list = curl_slist_append(list, "authority: www.wsj.com");
					list = curl_slist_append(list, "referer: https://www.twitter.com/");

					goto next;
				//}



				next:;
				//end of custom headers
				curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);//parsing the custom headers
				curl_easy_setopt(curl, CURLOPT_URL, url);
				curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)fHandler);
				curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "gzip, deflate, br");
				curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.84 Safari/537.36");
				curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); 
				curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
				res = curl_easy_perform(curl);

				if(res!=CURLE_OK)
				{
						printLog("simpleGetRequest() failed with error code:");
						printLog(curl_easy_strerror(res));
				}

				curl_easy_cleanup(curl);
			}

			curl=NULL;

		}

		void simpleGetRequest(const char* url)
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