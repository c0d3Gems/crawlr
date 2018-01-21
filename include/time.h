
		#ifndef TIME_H
		#define TIME_H

			struct timeFormat
			{
				unsigned short hour;
				unsigned short minute;
				unsigned short second;

				unsigned short day;
				unsigned short month;
				unsigned int   year;
			};
		
			
			struct timeFormat* getCurrentTime(void);
			//function that returns the time @ the moment wnen it's called

		#endif	