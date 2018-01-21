
	#include "../include/crawler.h"

		


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

		unsigned short printLog(char* str,unsigned short LOGGING_MODE)
		{
			switch(LOGGING_MODE){
				case 0x1://quiet (only in log file)
				break;
				case 0x2://muted (nowhere)
				break;
				case 0x0://print everywhere
				break;
				default:break;
				//in theory, this case should never reach the default stage
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
				printf("Could not malloc() in function getFilePath()\n");
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
				if(pthread_create(&threads[i], NULL, threadFunc, (void*)str))
				{
					printf("ERROR spawning thread %lu\n", i);
					exit(EXIT_FAILURE);
				}
				printf("Thread %lu spawned!\n", i);
			}
			for(i=0;i<vecSize;++i)
			{
				pthread_join(threads[i], NULL);
			}
			printf("\n");
		}