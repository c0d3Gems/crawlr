


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

	char* getTimeHeader(struct timeFormat *time)
	{
		char* hour;
		char* minute;
		char* second;
		char* day;
		char* month;
		char* year;

		hour   =	toString((unsigned long long)time->hour,   NULL);
		minute =	toString((unsigned long long)time->minute, NULL);
		second =	toString((unsigned long long)time->second, NULL);
		day	   =	toString((unsigned long long)time->day,    NULL);
		month  =	toString((unsigned long long)time->month,  NULL);
		year   =	toString((unsigned long long)time->year,   NULL);

		unsigned short hourLength   =getStringLength(hour);
		unsigned short minuteLength =getStringLength(minute);
		unsigned short secondLength =getStringLength(second);
		unsigned short dayLength    =getStringLength(day);
		unsigned short monthLength  =getStringLength(month);
		unsigned short yearLength   =getStringLength(year);

		unsigned long long size=1+hourLength+minuteLength+secondLength+dayLength+yearLength+1;
		printf("SIZE IS %llu\n", size);
		unsigned long long tmpSize=2;

		char* res=malloc(size);
		if(res==NULL)
		{
			exit(EXIT_FAILURE);
			return (char*)NULL;
		}

		memset(res, '\0', size);
		

		printf("%s is the time formatted as string\n", res);

		// free(res);
		// res=NULL;




		free(hour);
		free(minute);
		free(second);
		free(day);
		free(month);
		free(year);

		hour=NULL;
		minute=NULL;
		second=NULL;
		day=NULL;
		month=NULL;
		year=NULL;

		return res;
	}

	