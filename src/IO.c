#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course

#include "struct.h"
#include "IO.h"



void initJoystick(){
RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for GPIO Port A
RCC->AHBENR |= RCC_AHBPeriph_GPIOB; // Enable clock for GPIO Port B
RCC->AHBENR |= RCC_AHBPeriph_GPIOC; // Enable clock for GPIO Port C



	/***************************/
	/* right joystick	       */
	/***************************/
// Set pin PC0 to input
    GPIOC->MODER &= ~(0x00000003 << (0 * 2)); // Clear mode register
    GPIOC->MODER |= (0x00000000 << (0 * 2));
    // Set mode register (0x00 - Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
    GPIOC->PUPDR &= ~(0x00000003 << (0 * 2)); // Clear push/pull register
    GPIOC->PUPDR |= (0x00000002 << (0 * 2));
    // Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down)

    GPIOC->ODR |= (0x0001 << 2); //Set pin PC0 to high


 // Set pin PC2 to output
    GPIOC->OSPEEDR &= ~(0x00000003 << (2 * 2)); // Clear speed register
    GPIOC->OSPEEDR |= (0x00000002 << (2 * 2));
    // set speed register (0x01 - 10MHz, 0x02 - 2 MHz, 0x03 - 50 MHz)
    GPIOC->OTYPER &= ~(0x0001 << (2)); // Clear output type register
    GPIOC->OTYPER |= (0x0000 << (2));
    // Set output type register (0x00 - Push pull, 0x01 - Open drain)
    GPIOC->MODER &= ~(0x00000003 << (2 * 2)); // Clear mode register
    GPIOC->MODER |= (0x00000001 << (2 * 2));
    // Set mode register (0x00 - Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)

	/***************************/
	/* left joystick	       */
	/***************************/
// Set pin PC1 to input
    GPIOC->MODER &= ~(0x00000003 << (1 * 2)); // Clear mode register
    GPIOC->MODER |= (0x00000000 << (1 * 2));
    // Set mode register (0x00 - Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
    GPIOC->PUPDR &= ~(0x00000003 << (1 * 2)); // Clear push/pull register
    GPIOC->PUPDR |= (0x00000002 << (1 * 2));
    // Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down)


    GPIOC->ODR |= (0x0001 << 3); //Set pin PC1 to high


 // Set pin PC3 to output
    GPIOC->OSPEEDR &= ~(0x00000003 << (3 * 2)); // Clear speed register
    GPIOC->OSPEEDR |= (0x00000002 << (3 * 2));
    // set speed register (0x01 - 10MHz, 0x02 - 2 MHz, 0x03 - 50 MHz)
    GPIOC->OTYPER &= ~(0x0001 << (3)); // Clear output type register
    GPIOC->OTYPER |= (0x0000 << (3));
    // Set output type register (0x00 - Push pull, 0x01 - Open drain)
    GPIOC->MODER &= ~(0x00000003 << (3 * 2)); // Clear mode register
    GPIOC->MODER |= (0x00000001 << (3 * 2));
    // Set mode register (0x00 - Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)


	/***************************/
	/* up joystick	           */
	/***************************/
// Set pin PA4 to input
    GPIOA->MODER &= ~(0x00000003 << (4 * 2)); // Clear mode register
    GPIOA->MODER |= (0x00000000 << (4 * 2));
    // Set mode register (0x00 - Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
    GPIOA->PUPDR &= ~(0x00000003 << (4 * 2)); // Clear push/pull register
    GPIOA->PUPDR |= (0x00000002 << (4 * 2));
    // Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down)


    GPIOA->ODR |= (0x0001 << 5); //Set pin PA4 to high


 // Set pin PA5 to output
    GPIOA->OSPEEDR &= ~(0x00000003 << (5 * 2)); // Clear speed register
    GPIOA->OSPEEDR |= (0x00000002 << (5 * 2));
    // set speed register (0x01 - 10MHz, 0x02 - 2 MHz, 0x03 - 50 MHz)
    GPIOA->OTYPER &= ~(0x0001 << (5)); // Clear output type register
    GPIOA->OTYPER |= (0x0000 << (5));
    // Set output type register (0x00 - Push pull, 0x01 - Open drain)
    GPIOA->MODER &= ~(0x00000003 << (5 * 2)); // Clear mode register
    GPIOA->MODER |= (0x00000001 << (5 * 2));
    // Set mode register (0x00 - Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)

	/***************************/
	/* center joystick	       */
	/***************************/
// Set pin PB5 to input
    GPIOB->MODER &= ~(0x00000003 << (5 * 2)); // Clear mode register
    GPIOB->MODER |= (0x00000000 << (5 * 2));
    // Set mode register (0x00 - Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
    GPIOB->PUPDR &= ~(0x00000003 << (5 * 2)); // Clear push/pull register
    GPIOB->PUPDR |= (0x00000002 << (5 * 2));
    // Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down)


    GPIOB->ODR |= (0x0001 << 6); //Set pin PB5 to high


 // Set pin PB6 to output
    GPIOB->OSPEEDR &= ~(0x00000003 << (6 * 2)); // Clear speed register
    GPIOB->OSPEEDR |= (0x00000002 << (6 * 2));
    // set speed register (0x01 - 10MHz, 0x02 - 2 MHz, 0x03 - 50 MHz)
    GPIOB->OTYPER &= ~(0x0001 << (6)); // Clear output type register
    GPIOB->OTYPER |= (0x0000 << (6));
    // Set output type register (0x00 - Push pull, 0x01 - Open drain)
    GPIOB->MODER &= ~(0x00000003 << (6 * 2)); // Clear mode register
    GPIOB->MODER |= (0x00000001 << (6 * 2));
    // Set mode register (0x00 - Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)

 	/***************************/
	/* down joystick	       */
	/***************************/
 // Set pin PB0 to input
    GPIOB->MODER &= ~(0x00000003 << (0 * 2)); // Clear mode register
    GPIOB->MODER |= (0x00000000 << (0 * 2));
    // Set mode register (0x00 - Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
    GPIOB->PUPDR &= ~(0x00000003 << (0 * 2)); // Clear push/pull register
    GPIOB->PUPDR |= (0x00000002 << (0 * 2));
    // Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down)



    GPIOB->ODR |= (0x0001 << 1); //Set pin PB0 to high


 // Set pin PB1 to output
    GPIOB->OSPEEDR &= ~(0x00000003 << (1 * 2)); // Clear speed register
    GPIOB->OSPEEDR |= (0x00000002 << (1 * 2));
    // set speed register (0x01 - 10MHz, 0x02 - 2 MHz, 0x03 - 50 MHz)
    GPIOB->OTYPER &= ~(0x0001 << (1)); // Clear output type register
    GPIOB->OTYPER |= (0x0000 << (1));
    // Set output type register (0x00 - Push pull, 0x01 - Open drain)
    GPIOB->MODER &= ~(0x00000003 << (1 * 2)); // Clear mode register
    GPIOB->MODER |= (0x00000001 << (1 * 2));
    // Set mode register (0x00 - Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
}

void initLED(){
RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for GPIO Port A
RCC->AHBENR |= RCC_AHBPeriph_GPIOB; // Enable clock for GPIO Port B
RCC->AHBENR |= RCC_AHBPeriph_GPIOC; // Enable clock for GPIO Port C

 	/***************************/
	/* Red LED	               */
	/***************************/

    GPIOB->ODR |= (0x0001 << 4); //Set pin PB0 to high


 // Set pin PB4 to output
    GPIOB->OSPEEDR &= ~(0x00000003 << (4 * 2)); // Clear speed register
    GPIOB->OSPEEDR |= (0x00000002 << (4 * 2));
    // set speed register (0x01 - 10MHz, 0x02 - 2 MHz, 0x03 - 50 MHz)
    GPIOB->OTYPER &= ~(0x0001 << (4)); // Clear output type register
    GPIOB->OTYPER |= (0x0000 << (4));
    // Set output type register (0x00 - Push pull, 0x01 - Open drain)
    GPIOB->MODER &= ~(0x00000003 << (4 * 2)); // Clear mode register
    GPIOB->MODER |= (0x00000001 << (4 * 2));
    // Set mode register (0x00 - Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)

 	/***************************/
	/* Green LED	           */
	/***************************/

    GPIOC->ODR |= (0x0001 << 7); //Set pin PB0 to high


 // Set pin PC7 to output
    GPIOC->OSPEEDR &= ~(0x00000003 << (7 * 2)); // Clear speed register
    GPIOC->OSPEEDR |= (0x00000002 << (7 * 2));
    // set speed register (0x01 - 10MHz, 0x02 - 2 MHz, 0x03 - 50 MHz)
    GPIOC->OTYPER &= ~(0x0001 << (7)); // Clear output type register
    GPIOC->OTYPER |= (0x0000 << (7));
    // Set output type register (0x00 - Push pull, 0x01 - Open drain)
    GPIOC->MODER &= ~(0x00000003 << (7 * 2)); // Clear mode register
    GPIOC->MODER |= (0x00000001 << (7 * 2));
    // Set mode register (0x00 - Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)

 	/***************************/
	/* Blue LED	           */
	/***************************/

    GPIOA->ODR |= (0x0001 << 9); //Set pin PB0 to high


 // Set pin PA9 to output
    GPIOA->OSPEEDR &= ~(0x00000003 << (9 * 2)); // Clear speed register
    GPIOA->OSPEEDR |= (0x00000002 << (9 * 2));
    // set speed register (0x01 - 10MHz, 0x02 - 2 MHz, 0x03 - 50 MHz)
    GPIOA->OTYPER &= ~(0x0001 << (9)); // Clear output type register
    GPIOA->OTYPER |= (0x0000 << (9));
    // Set output type register (0x00 - Push pull, 0x01 - Open drain)
    GPIOA->MODER &= ~(0x00000003 << (9 * 2)); // Clear mode register
    GPIOA->MODER |= (0x00000001 << (9 * 2));
    // Set mode register (0x00 - Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)

}




int8_t readJoyStick(){
    int8_t direction = 0;
    uint16_t valRight = GPIOC->IDR & (0x0001 << 0);
    uint16_t valDown = GPIOB->IDR & (0x0001 << 0);
    uint16_t valCenter = GPIOB->IDR & (0x0001 << 5);
    uint16_t valLeft = GPIOC->IDR & (0x0001 << 1);
    uint16_t valUp = GPIOA->IDR & (0x0001 << 4);

    if (valUp){
        direction += 1;
    }
    if (valDown){
        direction += 2;
    }
    if (valLeft){
        direction += 4;
    }
    if (valRight){
        direction += 8;
    }
    if (valCenter){
        direction += 16;
    }

    return direction;

}

void setLed(int8_t value){ // LED turns on at low

    if (value == 0){ //white
        GPIOB->ODR &= ~RED;
        GPIOC->ODR &= ~GREEN;
        GPIOA->ODR &= ~BLUE;
    } else if(value == 1){ //Red
        GPIOB->ODR &= ~RED;
        GPIOC->ODR |= GREEN;
        GPIOA->ODR |= BLUE;
    } else if(value == 2){ // GREEN
        GPIOB->ODR |= RED;
        GPIOC->ODR &= ~GREEN;
        GPIOA->ODR |= BLUE;
    } else if(value == 4){ // BLUE
        GPIOB->ODR |= RED;
        GPIOC->ODR |= GREEN;
        GPIOA->ODR &= ~BLUE;
    } else if(value == 8){ // Yellow
        GPIOB->ODR &= ~RED;
        GPIOC->ODR &= ~GREEN;
        GPIOA->ODR |= BLUE;
    } else if(value == 16){ // Magenta
        GPIOB->ODR &= ~RED;
        GPIOC->ODR |= GREEN;
        GPIOA->ODR &= ~BLUE;
    } else if(value == 5 || value == 6 || value == 9 || value == 10 || value == 24 || value == 17 || value == 18 || value == 19 || value == 20 || value == 21 || value == 22 || value == 25){ // Cyan
        GPIOB->ODR |= RED;
        GPIOC->ODR &= ~GREEN;
        GPIOA->ODR &= ~BLUE;
    }

}
