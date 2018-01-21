


	#include "../include/crawler.h"





	struct timeFormat* getCurrentTime(void)
	{
		struct timeFormat *timev=malloc(sizeof(struct timeFormat)+1);
		if(!timev)
		{
			printf("Could not malloc space for time variable\n");
			exit(EXIT_FAILURE);
		}
		
		time_t t = time(NULL);
		struct tm tm = *localtime(&t);

		timev->year=(unsigned int)tm.tm_year+1900;
		timev->month=(unsigned short)tm.tm_mon+1;
		timev->day=(unsigned short)tm.tm_mday;

		timev->hour=tm.tm_hour;
		timev->minute=tm.tm_min;
		timev->second=tm.tm_sec;
		return timev;
	}