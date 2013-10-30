// KnightRider.c
//
// Example program for bcm2835 library
// Blinks a pin on an off every 0.5 secs
//
// After installing bcm2835, you can build this 
// with something like:
// gcc -o blink blink.c -l bcm2835
// sudo ./blink

#include <bcm2835.h>

#define PIN3 RPI_V2_GPIO_P1_03
#define PIN5 RPI_V2_GPIO_P1_05
#define PIN7 RPI_V2_GPIO_P1_07
#define PIN8 RPI_V2_GPIO_P1_08
#define PIN10 RPI_V2_GPIO_P1_10
#define PIN11 RPI_V2_GPIO_P1_11
#define PIN12 RPI_V2_GPIO_P1_12
#define PIN13 RPI_V2_GPIO_P1_13
#define PIN15 RPI_V2_GPIO_P1_15
#define PIN16 RPI_V2_GPIO_P1_16
#define PIN18 RPI_V2_GPIO_P1_18

#define OUTP BCM2835_GPIO_FSEL_OUTP

int main(int argc, char **argv)
{

    if (!bcm2835_init())
	return 1;

    // Set the pin to be an output
    bcm2835_gpio_fsel(PIN3, OUTP);
    bcm2835_gpio_fsel(PIN5, OUTP);
    bcm2835_gpio_fsel(PIN7, OUTP);
    bcm2835_gpio_fsel(PIN8, OUTP);
    bcm2835_gpio_fsel(PIN10, OUTP);
    //bcm2835_gpio_fsel(PIN11, OUTP);
    bcm2835_gpio_fsel(PIN12, OUTP);
    bcm2835_gpio_fsel(PIN13, OUTP);
	
	int pause = 150;

    // KnightRider
    while (1)
    {
	bcm2835_gpio_write(PIN3, HIGH);
	bcm2835_delay(pause);
	
	bcm2835_gpio_write(PIN3, LOW);
	bcm2835_gpio_write(PIN5, HIGH);
	bcm2835_delay(pause);
		
	bcm2835_gpio_write(PIN5, LOW);	
	bcm2835_gpio_write(PIN7, HIGH);
	bcm2835_delay(pause);
	
	bcm2835_gpio_write(PIN7, LOW);
	bcm2835_gpio_write(PIN8, HIGH);
	bcm2835_delay(pause);
	
	bcm2835_gpio_write(PIN8, LOW);
	bcm2835_gpio_write(PIN10, HIGH);
	bcm2835_delay(pause);
	
	bcm2835_gpio_write(PIN10, LOW);
	bcm2835_gpio_write(PIN12, HIGH);
	bcm2835_delay(pause);
	
	bcm2835_gpio_write(PIN12, LOW);
	bcm2835_gpio_write(PIN13, HIGH);
	bcm2835_delay(pause);
	
	bcm2835_gpio_write(PIN13, LOW);
	bcm2835_gpio_write(PIN12, HIGH);
	bcm2835_delay(pause);
	
	bcm2835_gpio_write(PIN12, LOW);
	bcm2835_gpio_write(PIN10, HIGH);
	bcm2835_delay(pause);
	
	bcm2835_gpio_write(PIN10, LOW);
	bcm2835_gpio_write(PIN8, HIGH);	
	bcm2835_delay(pause);
	
	bcm2835_gpio_write(PIN8, LOW);
	bcm2835_gpio_write(PIN7, HIGH);
	bcm2835_delay(pause);
	
	bcm2835_gpio_write(PIN7, LOW);
	bcm2835_gpio_write(PIN5, HIGH);
	bcm2835_delay(pause);
	
	bcm2835_gpio_write(PIN5, LOW);
    }
    bcm2835_close();
    return 0;
}

