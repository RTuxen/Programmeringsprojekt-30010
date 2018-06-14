#ifndef _STRUCT_H_
#define _STRUCT_H_
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course


// Map size constants
#define X1 1
#define Y1 1
#define X2 60
#define Y2 241

// Keyboard constants
#define SPACE 32




struct vector_t {
    int32_t x, y;
};

struct ball_t {
    int32_t x;
    int32_t y;
    int32_t speed;
    int32_t angle;
};


struct timepoint {
    uint8_t centiseconds, seconds, minutes, milliseconds, hours;
    uint16_t joystickdebouncer;
};
volatile struct timepoint tid; //Global variables




struct player_t {
	int32_t x;
	int32_t y;
};

struct block_t {
	uint16_t x;
	uint16_t y;
	int8_t lives;
	int8_t fallingObject;
};

struct level_t {
	struct block_t blocks[128];
	uint8_t lives;
};

struct game_state_t {
 	uint8_t speed;
 	uint8_t mirror;
 	uint16_t highscores[5];
	uint16_t points;
	uint8_t lives;
	uint8_t startlevel;
	uint8_t currentlevel;
	uint8_t buffer[512];
	uint8_t players;
};

struct fallingPowUp_t {
        int type;
        uint16_t x;
        uint16_t y;
};

// const int MaxObjects=5;

 struct fallingObjectsType_t {
        int8_t numberOfObjects;
        struct fallingPowUp_t fallingObjectArray[5];
};

#endif /*_STRUCT_H_*/
