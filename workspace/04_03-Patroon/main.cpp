#include "hwlib.hpp"


int main( void )
{	
	// kill the watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	namespace target = hwlib::target;
	
	auto led0 = target::pin_out(target::pins::d7);
	auto led1 = target::pin_out(target::pins::d6);
	auto led2 = target::pin_out(target::pins::d5);
	auto led3 = target::pin_out(target::pins::d4);
	
	target::pin_out* leds[] = {&led0, &led1, &led2, &led3};
	
	
	int patternArray[] = 
	{
		0b0011,
		0b0110,
		0b1100,
		0b0110
	};
	
	
	while(1){
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 4; j++){
				leds[j]->set(( patternArray[i] & (0x01 << j) ));
			}
			hwlib::wait_ms(1000);
		}
	}

}

