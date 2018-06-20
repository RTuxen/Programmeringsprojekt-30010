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

    GPIOB->ODR |= (0x0001 << 4); //Set pin PB4 to high


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

    GPIOC->ODR |= (0x0001 << 7); //Set pin PC7 to high


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

    GPIOA->ODR |= (0x0001 << 9); //Set pin PA9 to high


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

int8_t readJoyStickContinous(){
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

int8_t readJoyStick(){
    static uint16_t time = 0;
    static uint8_t old1_direction;
    static uint8_t old2_direction;
    uint8_t direction = 0;
    uint16_t valUp = GPIOA->IDR & (0x0001 << 4);
    uint16_t valDown = GPIOB->IDR & (0x0001 << 0);
    uint16_t valLeft = GPIOC->IDR & (0x0001 << 1);
    uint16_t valRight = GPIOC->IDR & (0x0001 << 0);
    uint16_t valCenter = GPIOB->IDR & (0x0001 << 5);

    if (valUp){
        direction = 1;
    }
    if (valDown){
        direction = 2;
    }
    if (valLeft){
        direction = 4;
    }
    if (valRight){
        direction = 8;
    }
    if (valCenter){
        direction = 16;
    }
    if (old1_direction != direction) {
        time = tid.joystickdebouncer;
    }

    if (tid.joystickdebouncer >=  time+25){
        if (old2_direction != direction) {
            old2_direction = direction;
            return direction;
        }
    }
    old1_direction = direction;
    return 32;
}

void turnOffLED(){
    GPIOB->ODR |= RED; //Set pin PB4 to low
    GPIOC->ODR |= GREEN; //Set pin PC7 to low
    GPIOA->ODR |= BLUE; //Set pin PA9 to low
}

void setLed(struct game_state_t* gs){ // LED turns on at low
    static uint8_t oldlives;

    if (oldlives > gs->lives){ // Red
        GPIOB->ODR &= ~RED;
        GPIOC->ODR |= GREEN;
        GPIOA->ODR |= BLUE;
    } else if(oldlives < gs->lives){ // GREEN
        GPIOB->ODR |= RED;
        GPIOC->ODR &= ~GREEN;
        GPIOA->ODR |= BLUE;
    } else if(gs->randomAnglePowerup){ // BLUE
        GPIOB->ODR |= RED;
        GPIOC->ODR |= GREEN;
        GPIOA->ODR &= ~BLUE;
    } else if(gs->mirror != gs->startmirror){ // Yellow
        GPIOB->ODR &= ~RED;
        GPIOC->ODR &= ~GREEN;
        GPIOA->ODR |= BLUE;
    } else if (oldlives == gs->lives && !gs->randomAnglePowerup && gs->mirror==gs->startmirror){// No light
        GPIOB->ODR |= RED;
        GPIOC->ODR |= GREEN;
        GPIOA->ODR |= BLUE;
    }
    oldlives = gs->lives;
}

void initADC() {

    RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for GPIO Port A

    // Set pin PA0 to input
    GPIOA->MODER &= ~(0x00000003 << (0 * 2)); // Clear mode register
    GPIOA->MODER |= (0x00000000 << (0 * 2));
    // Set mode register (0x00 - Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
    GPIOA->PUPDR &= ~(0x00000003 << (0 * 2)); // Clear push/pull register

   // Set pin PA1 to input
    GPIOA->MODER &= ~(0x00000003 << (1 * 2)); // Clear mode register
    GPIOA->MODER |= (0x00000000 << (1 * 2));
    // Set mode register (0x00 - Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
    GPIOA->PUPDR &= ~(0x00000003 << (1 * 2)); // Clear push/pull register

    RCC->CFGR2 &= ~RCC_CFGR2_ADCPRE12;     // Clear ADC12 prescaler bits
    RCC->CFGR2 |= RCC_CFGR2_ADCPRE12_DIV6; // Set ADC12 prescaler to 6
    RCC->AHBENR |= RCC_AHBPeriph_ADC12;    // Enable clock for ADC12

    ADC1->CR = 0x00000000;          // Clear CR register
    ADC1->CFGR &= 0xFDFFC007;       // Clear ADC1 config register
    ADC1->SQR1 &= ~ADC_SQR1_L;      // Clear regular sequence register 1

    ADC1->CR |= 0x10000000;             // Enable internal ADC voltage regulator
    for (int i = 0 ; i < 1000 ; i++) {} // Wait for about 16 microseconds

    ADC1->CR |= 0x80000000;             // Start ADC1 calibration
    while (!(ADC1->CR & 0x80000000));   // Wait for calibration to finish
    for (int i = 0 ; i < 100 ; i++) {}  // Wait for a little while

    ADC1->CR |= 0x00000001;             // Enable ADC1 (0x01 - Enable, 0x02 - Disable)
    while (!(ADC1->ISR & 0x00000001));  // Wait until ready
}

uint16_t readADC_pa0() { //Channel 1
    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_1Cycles5);
    ADC_StartConversion(ADC1);                          // Start ADC read
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == 0); // Wait for ADC read
    uint16_t x = ADC_GetConversionValue(ADC1);          // Read the ADC value
    return x;
}

uint16_t readADC_pa1() { //Channel 2
    ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_1Cycles5);
    ADC_StartConversion(ADC1);                          // Start ADC read
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == 0); // Wait for ADC read
    uint16_t x = ADC_GetConversionValue(ADC1);          // Read the ADC value
    return x;
}

uint8_t readKeyboard() { // Reads keyboard input

    if(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == SET){
        return (uint8_t)USART_ReceiveData(USART2);
    } else{
        return 0;
    }
}

void initBuzzer(){
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN; // Enable clock line for GPIO bank B
    GPIOB->MODER &= ~(0x00000003 << (10 * 2)); // Clear mode register
    GPIOB->MODER |= (0x00000002 << (10 * 2)); // Set mode register
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_1);// Set alternate function 1 - PWM Output
}

void I2C_init(){

    /**************/
    /**** GPIO ****/
    /**************/
    RCC->AHBENR |= 0x00040000; // Enable clock for GPIO Bank B

    GPIOB->AFR[8 >> 0x03] &= ~(0x0000000F << ((8 & 0x00000007) * 4)); // Clear alternate function for PB8
    GPIOB->AFR[8 >> 0x03] |=  (0x00000004 << ((8 & 0x00000007) * 4)); // Set alternate 4 function for PB8
    GPIOB->AFR[9 >> 0x03] &= ~(0x0000000F << ((9 & 0x00000007) * 4)); // Clear alternate function for PB9
    GPIOB->AFR[9 >> 0x03] |=  (0x00000004 << ((9 & 0x00000007) * 4)); // Set alternate 4 function for PB9

    // Configure pins PB8 and PB9 for 10 MHz alternate function
    GPIOB->OSPEEDR &= ~(0x00000003 << (8 * 2) | 0x00000003 << (9 * 2));    // Clear speed register
    GPIOB->OSPEEDR |=  (0x00000001 << (8 * 2) | 0x00000001 << (9 * 2));    // set speed register (0x01 - 10 MHz, 0x02 - 2 MHz, 0x03 - 50 MHz)
    GPIOB->OTYPER  &= ~(0x0001     << (8)     | 0x0001     << (9));        // Clear output type register
    GPIOB->OTYPER  |=  (0x0001     << (8)     | 0x0001     << (9));        // Set output type register (0x00 - Push pull, 0x01 - Open drain)
    GPIOB->MODER   &= ~(0x00000003 << (8 * 2) | 0x00000003 << (9 * 2));    // Clear mode register
    GPIOB->MODER   |=  (0x00000002 << (8 * 2) | 0x00000002 << (9 * 2));    // Set mode register (0x00 - Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
    GPIOB->PUPDR   &= ~(0x00000003 << (8 * 2) | 0x00000003 << (9 * 2));    // Clear push/pull register
    GPIOB->PUPDR   |=  (0x00000001 << (8 * 2) | 0x00000001 << (9 * 2));    // Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down)

    /*************/
    /**** I2C ****/
    /*************/
    RCC->APB1ENR |=  0x00200000; // Enable clock for I2C1

    I2C1->CR1 &= ~0x00000001;  // Disable I2C1 peripheral during config
    I2C1->CR1 &= 0x00CFE0FF;   // Clear config
    I2C1->CR1 |= 0x00000000;   // Set Analog filter (0x00000000 - Enabled, 0x00001000 - Disabled)
    I2C1->CR1 |= 0x00 << 8;    // Set digital filter (0x00 - 0x0F)
    I2C1->TIMINGR = 0x10805E89 & 0xF0FFFFFF; // Set timing register to 0x10805E89. See reference manual for more
    I2C1->CR1  |= 0x00000001;  // Enable I2C1 peripheral
    I2C1->OAR1  = 0x00000000;  // Clear own address register 1
    I2C1->OAR2  = 0x00000000;  // Clear own address register 2
    I2C1->OAR1 |= 0x00000000;  // Configure for 7-bit address (0x00000000 - 7-bit, 0x00000400 - 10-bit)
    I2C1->OAR1 |= 0xAB;        // Set own address to 0xAB
    I2C1->OAR1 |= 0x00008000;  // Enable own address acknowledgment
    I2C1->CR1  |= 0x00000000;  // Set mode (0x00000000 - I2C, 0x00200000 - SMBus Device, 0x00100000 - SMBus Host)
    I2C1->CR2  &= 0x07FF7FFF;  // Clear config 2
    I2C1->CR2  |= 0x00000000;  // Configure acknowledgment (0x00000000 - Enabled, 0x00008000 - Disabled)

//    I2C1->CR1 |= 0x00200000;
}

uint8_t I2C_Read(uint16_t address, uint8_t reg) {
    uint8_t val = 0;

    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY) == SET); // Wait until free

    I2C_TransferHandling(I2C1, address, 1, I2C_SoftEnd_Mode, I2C_Generate_Start_Write); // Initiate transfer

    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_TXIS) == RESET); // Wait until free

    I2C_SendData(I2C1, reg); // Send register address

    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_TC) == RESET); // Wait until free

    I2C_TransferHandling(I2C1, address, 1, I2C_AutoEnd_Mode, I2C_Generate_Start_Read); // Resend address


    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_RXNE) == RESET); // Wait until free

    val = I2C_ReceiveData(I2C1);  // Transfer data

    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_STOPF) == RESET); // Wait for stop flag

    I2C_ClearFlag(I2C1, I2C_FLAG_STOPF); // Clear stop flag

    return val;
}

void I2C_Write(uint16_t address, uint8_t reg, uint8_t val) {
    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY) == SET); // Wait until free

    I2C_TransferHandling(I2C1, address, 1, I2C_Reload_Mode, I2C_Generate_Start_Write); // Initiate transfer

    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_TXIS) == RESET); // Wait until free

    I2C_SendData(I2C1, reg); // Send register address

    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_TCR) == RESET); // Wait until free

    I2C_TransferHandling(I2C1, address, 1, I2C_AutoEnd_Mode, I2C_No_StartStop); // Resend address

    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_TXIS) == RESET); // Wait until free

    I2C_SendData(I2C1, val); // Transfer data

    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_STOPF) == RESET); // Wait for stop flag

    I2C_ClearFlag(I2C1, I2C_FLAG_STOPF); // Clear stop flag
}
