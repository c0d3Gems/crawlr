

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
				printLog("stringInit(): malloc failed\n");
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

		unsigned long long findPatternFromPosition(char* str, char* pat, unsigned long long position)
		{
			unsigned long long i=0,j=0;
			for(i=position;str[i]!='\0';++i)
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

		unsigned short duplicate(char *a, char* b)
		{
			char *pa=a,*pb=b;
			while(true)
			{
				if(*pa!=*pb)
					return false;
				if(*pa=='\0'&&*pb=='\0')
					return true;
				pa++;
				pb++;
			}
		}

		void flipString(char* a)
		{
			if(a)
			{
				unsigned long long size=getStringLength(a);
				unsigned long long half=(unsigned long long)size/2;
				if(size>0)
				{
					char c='\0';
					unsigned long long i=0;
					for(i=0;i<half;++i)
					{
						c=a[i];
						a[i]=a[size-i-1];
						a[size-i-1]=c;
					}
				}
			}
		}


		unsigned long long countDigits(unsigned long long number)
		{
			if(number==0)return 1;
			unsigned long long numberOfDigits=0;
			while(number)
			{
				numberOfDigits++;
				number/=10;
			}
			return numberOfDigits;
		}

		char *toString(unsigned long long var, char sign)
		{
			unsigned int size=countDigits(var)+1;
			if(sign=='-'||sign=='+')
				size++;
			char *res=malloc(size);
			memset(res, '\0', size);
			char *pres=&res[size-2];
			do
			{
				*pres=(char)(var%10)+48;
				pres--;
				var/=10;
			}while(var);
			if(sign=='-'||sign=='+')
				res[0]=sign;
			return res;
		}