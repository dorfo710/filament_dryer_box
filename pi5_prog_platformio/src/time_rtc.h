#ifndef _time_rtc_H_
#define _time_rtc_H_

#include <Arduino.h>


class Hora{

	private:
	public:
		Hora();
        char Atual(int, int, int, int, int);
        int Definir();	
			
};
#endif

