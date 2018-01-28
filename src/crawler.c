
	#include "../include/crawler.h"

		
	unsigned short LOGGING_MODE;

		unsigned long long getFileSize(const char *fpath)
		{
			FILE *fHandler=fopen(fpath, "r");
			if(fHandler)
			{
				unsigned long long size=0;
				fseek(fHandler, 0L, SEEK_END);
				size=ftell(fHandler)+1;
				fclose(fHandler);
				fHandler=NULL;
				return size;
			}
			return 0;
		}

		void printLog(char* str)
		{
			char *timeHeader=NULL;
			char *res=NULL;
			unsigned long long resSize;
			unsigned long long strSize;
			unsigned long long timeHeaderSize;
			struct timeFormat* currentTime=NULL;
			FILE *logHandler=NULL;

			switch(LOGGING_MODE){

				case 0x1:
				//quiet (only in log file) triggered by the flag -q: ex. ./crawler -q

					currentTime=getCurrentTime();
					timeHeader=getTimeHeader(currentTime);
					free(currentTime);
					currentTime=NULL;

					timeHeaderSize=getStringLength(timeHeader);
					strSize=getStringLength(str);
					resSize=timeHeaderSize+strSize+2;

					res=malloc(resSize);
					if(res==NULL)
					{
						printf("[FATAL ERROR]: Could not malloc memory in function printLog\n");
						free(timeHeader);
						timeHeader=NULL;
						exit(EXIT_FAILURE);
					}

					memset(res, 				 	'\0', resSize);
					memcpy(&res[0], 			 	timeHeader, timeHeaderSize);
					memcpy(&res[timeHeaderSize],	": ", 2);
					memcpy(&res[timeHeaderSize+2], 	str, strSize);
					

					free(timeHeader);
					timeHeader=NULL;

					logHandler=fopen("log.txt", "a");
					if(!logHandler)
					{
						printf("Could not open logFile\n");
						exit(EXIT_FAILURE);
					}
					fwrite("\n",2 ,1 ,logHandler);
					fwrite(res, resSize, 1 ,logHandler);
					fclose(logHandler);
					logHandler=NULL;

					free(res);
					res=NULL;
				break;

				case 0x2:
				//muted (nowhere) triggered with the flag -m (ex. ./crawler -m)
				break;

				default:
				//print everywhere (no -m -q flag mentioned when launching the crawler)
					currentTime=getCurrentTime();
					timeHeader=getTimeHeader(currentTime);
					free(currentTime);
					currentTime=NULL;

					timeHeaderSize=getStringLength(timeHeader);

					strSize=getStringLength(str);
					resSize=timeHeaderSize+strSize+2;

					printf("RESSIZE = %llu\n", resSize);
					res=malloc(resSize);
					
					if(res==NULL)
					{
						printf("%s [FATAL ERROR]: Could not malloc memory in function printLog\n", timeHeader);
						free(timeHeader);
						timeHeader=NULL;
						exit(EXIT_FAILURE);
					}

					memset(res,'\0', resSize);
					memcpy(&res[0], timeHeader, timeHeaderSize);
					memcpy(&res[timeHeaderSize],	" ", 1);
					memcpy(&res[timeHeaderSize+1], str, strSize);
					
					free(timeHeader);
					timeHeader=NULL;


					logHandler=fopen("log.txt", "a");
					if(logHandler==NULL)
					{
						printf("Could not open logFile\n");
						exit(EXIT_FAILURE);
					}
					fwrite("\n",2 ,1 ,logHandler);
					fwrite(res, resSize, 1 ,logHandler);
					
					fclose(logHandler);
					logHandler=NULL;
					printf("%s\n", res);

					free(res);
					res=NULL;
				break;

			}
		}
		


		char *getSourceFromUrl(const char* str)
		{
			if(!str) return (char*)NULL;
			size_t i=0,j=0, length=strlen(str);
			char *buffer=malloc(length);
			memset(buffer, '\0', length);
			for (i = 0; str[i]!='\0'; ++i)
			{
				if((str[i]>='a'&&str[i]<='z') ||
				   (str[i]>='A'&&str[i]<='Z') ||
				    str[i]=='.' )
					buffer[j]=str[i];
			}
			return buffer;
		}




		unsigned short 
		customWriteFunction(void *ptr, size_t size, size_t nmemb, struct string *s)
		{
			size_t new_len = s->length + size*nmemb;

			free(s->content);
			s->content=NULL;
			s->content=malloc(new_len+1);
			memset(s->content, '\0', new_len+1);
			if(s->content==NULL)
			{
				printLog("ERROR malloc customWriteFunction\n");
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
				printLog("(genIndexFileName) The parameter should not be null\n");
				exit(EXIT_FAILURE);
			}
			size_t i=0,j=0, strSize=getStringLength(str), totalSize=strSize+4;
			char *res=malloc(totalSize);
			if(res==NULL)
			{
				printLog("(genIndexFileName) ERROR malloc-ing the space for genIndexFileName function.\nMaybe not enough free memory?!\n");
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



		char *getFilePath(char* fname)
		{
			size_t fnameSize=getStringLength(fname), totalSize=fnameSize+6;
			char *res=malloc(totalSize);
			if(res!=NULL)
			{
				memset(res, '\0',totalSize);// valgrind loves this.
				memcpy(res, DOWNLOAD_DIRECTORY, 6);
				memcpy(&res[5], fname, fnameSize);
				return res;	// needs to be freed
			}
			else
			{
				printLog("Could not malloc() in function getFilePath()\n");
				exit(EXIT_FAILURE);
				return (char*)NULL;	//this might be rendundant since we have the exit function, but I put it anyway.
			}
		}

		void* threadFunc(void* param)
		{
			const char *str=(const char*)param;
			printf("THREAD OUTPUTS: %s\n", str);
			// simpleGetRequest((const char*)param);
			return NULL;
		}

		size_t writeFunctionCaller(const char **sources, size_t vecSize)
		{
			size_t i=0;
			pthread_t threads[(const unsigned int)vecSize];
			for(i=0;i<vecSize;++i)
			{
				char* str=(char*)sources[i];
				char *istring=toString(i, NULL);
				unsigned int isize=getStringLength(istring);
				if(pthread_create(&threads[i], NULL, threadFunc, (void*)str))
				{
					char str[]="writeFunctionCaller() ERROR spawning thread ";
					unsigned int strSize=getStringLength(str);
					istring[isize]='\0';
					char error[(const unsigned int)(strSize+isize+1)];
					memset(error, '\0', strSize+isize+1);
					memcpy(&error[0], str, strSize);
					memcpy(&error[strSize], istring, isize);
					printLog(error);
					free(istring);
					istring=NULL;
					exit(EXIT_FAILURE);
				}
				char msg[]="SPAWNED THREAD # ";
				unsigned short msgSize=getStringLength(msg);
				char *success_msg=malloc(msgSize+isize+1);
				memset(success_msg, '\0', msgSize+isize+1);
				memcpy(&success_msg[0], msg, msgSize);
				memcpy(&success_msg[msgSize], istring,isize);
				printLog(success_msg);
				free(istring);
				free(success_msg);
				istring=NULL;
				success_msg=NULL;
			}
			for(i=0;i<vecSize;++i)
			{
				pthread_join(threads[i], NULL);
			}//to wait for all threads to finish. 
		}