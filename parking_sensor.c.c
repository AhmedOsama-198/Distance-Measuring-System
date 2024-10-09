#include "icu.h"
#include "lcd.h"
#include "ultrasonic_sensor.h"
#include "avr_registers.h"


int main()
{
	uint16 distance = 0;	/* variable to store distance */

	SREG_REG.Bits.I_Bit=1;	/* enabling global I-bit */

	Ultrasonic_init();		/* initializing ultrasonic sensor */
	LCD_init();				/* initializing LCD driver */

	LCD_displayString((uint8 *)"Distance =");

	while(1)
	{
		distance = Ultrasonic_readDistance();

		Ultrasonic_alarmSystem();	/* checking alarm system */

		/* displaying the distance value on LCD */
		LCD_moveCursor(0,11);
		LCD_intgerToString(distance);
		LCD_displayString((uint8 *)"Cm   ");

		if(distance <= 50)/* displaying a warning messege on lCD if distance is very small */
		{
			LCD_displayStringRowColumn(1, 3, (uint8 *)"WARNNIG!!!");
		}
		else if(distance > 50)/* clearing the warning messege */
		{
			LCD_displayStringRowColumn(1, 3, (uint8 *)"          ");
		}
	}
}
