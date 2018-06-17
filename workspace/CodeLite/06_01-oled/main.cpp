#include "hwlib.hpp"

class house{
private:
	hwlib::glcd_oled & display;
	
	void drawBase()
	{
		for( uint16_t i = 50; i < display.size.x - 40; i++ )
		{
			for(uint16_t j = 30; j < display.size.y - 5; j++)
			{
				display.write( hwlib::location( i, j ), hwlib::black );
			}
		}
	}
	
	void drawroof()
	{
		int index = 0;
		//int roofy = 0;
		int distx = display.size.x - 40;
		for( uint16_t i = 50; i < distx; i++ )
		{
			hwlib::cout << i << " | " << index << "\n";
			if( i < 50+((distx-50)/2))
			{
				display.write( hwlib::location( i, 30-index ), hwlib::black);
				index++;
			}
			else
			{
				display.write( hwlib::location( i, 30-index ), hwlib::black);
				index--;
			}
		}
	}
	
	
	void drawDoor()
	{
		for( uint16_t i = 65; i < display.size.x - 50; i++ )
		{
			for(uint16_t j = 45; j < display.size.y - 5; j++)
			{
				display.write( hwlib::location( i, j ), hwlib::white );
			}
		}
	}
	
	void drawR()
	{
		for(int i = 3; i <= 10; i++)
		{
			display.write( hwlib::location( 3, i ), hwlib::black );
		}
		
		display.write( hwlib::location( 4,3 ), hwlib::black );
		display.write( hwlib::location( 5,4 ), hwlib::black );
		display.write( hwlib::location( 6,5 ), hwlib::black );
		display.write( hwlib::location( 5,6 ), hwlib::black );
		display.write( hwlib::location( 4,7 ), hwlib::black );
		display.write( hwlib::location( 5,8 ), hwlib::black );
		display.write( hwlib::location( 6,9 ), hwlib::black );
		display.write( hwlib::location( 7,10 ), hwlib::black );
	}
	
public:
	house(hwlib::glcd_oled & display):
		display(display)
	{}
	
	void drawHouse()
	{
		drawBase();
		drawDoor();
		drawroof();
		drawR();
		display.flush();
	}
	
};


int main( void ){	

	// kill the watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;

	namespace target = hwlib::target;


	auto scl = target::pin_oc( target::pins::scl );
	auto sda = target::pin_oc( target::pins::sda );


	auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );

	auto display = hwlib::glcd_oled( i2c_bus, 0x3c );  
	 
	auto figure = house(display);
	
	display.clear();
	figure.drawHouse();
	
}
