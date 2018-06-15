#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course

#ifndef _STRUCT_H_
#define _STRUCT_H_

// Map size constants
#define X1 1
#define Y1 2
#define X2 60
#define Y2 242

// Menu size and increment constants
#define INCRY 25
#define INCRX 2
#define MENUX1 30
#define MENUX2 54
#define MENUY1 100
#define MENUY2 150

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
    uint16_t joystickdebouncer, seconds, gametime, randomAngle;
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
	int8_t lives;
};

struct game_state_t {
    int8_t lives;
 	uint8_t speed;
 	uint8_t startmirror;
 	uint8_t mirror;
 	uint8_t randomAnglePowerup;
 	uint16_t highscores[5];
	uint16_t points;
	uint8_t startlevel;
	uint8_t currentlevel;
	uint8_t buffer[512];
	uint8_t players;
	uint16_t mirroruptime;
	uint16_t randomAnglePoweruptime;
};

struct fallingObject_t {
        int type;
        uint16_t x;
        uint16_t y;
};

// const int MaxObjects=5;

 struct fallingObjectsType_t {
        int8_t numberOfObjects;
        struct fallingObject_t fallingObjectArray[10];
};

#endif /*_STRUCT_H_*/
