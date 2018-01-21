

	#include "../include/crawler.h"

			
	
		unsigned long long getStringLength(char *str)
		{
			if(str)
			{
				unsigned long long i=1;
				while(str[i]!='\0')++i;
				return i;
			}
			return 0;
		}



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

		unsigned long long findPattern(char* str, char* pat)
		{
			unsigned long long i=0,j=0;
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