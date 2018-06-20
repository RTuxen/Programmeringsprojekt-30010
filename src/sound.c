  #include "sound.h"

// Main Mario melody
const uint16_t  MELODY[] = {
  0, NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0
};
// Main Mario tempo
const uint8_t TEMPO[] = {
  0, 120, 120, 120, 120,
  120, 120, 120, 120,
  120, 120, 120, 120,
  120, 120, 120, 120,

  120, 120, 120, 120,
  120, 120, 120, 120,
  120, 120, 120, 120,
  120, 120, 120, 120,

  120, 120, 120, 120,
  120, 120, 120, 120,
  120, 120, 120, 120,
  120, 120, 120, 120,

  120, 120, 120, 120,
  120, 120, 120, 120,
  120, 120, 120, 120,
  120, 120, 120, 120,

  120, 120, 120, 120,
  120, 120, 120, 120,
  120, 120, 120, 120,
  120, 120, 120, 120,
};
// Underworld melody
const uint16_t UNDERWORLD_MELODY[] = {
  0,NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0, NOTE_DS4, NOTE_CS4, NOTE_D4,
  NOTE_CS4, NOTE_DS4,
  NOTE_DS4, NOTE_GS3,
  NOTE_G3, NOTE_CS4,
  NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
  NOTE_GS4, NOTE_DS4, NOTE_B3,
  NOTE_AS3, NOTE_A3, NOTE_GS3,
  0, 0, 0
};
// Underworld tempo
const uint8_t UNDERWORLD_TEMPO[] = {
  0,120, 120, 120, 120,
  120, 120, 60,
  30,
  120, 120, 120, 120,
  120, 120, 60,
  30,
  120, 120, 120, 120,
  120, 120, 60,
  30,
  120, 120, 120, 120,
  120, 120, 60,
  60, 180, 180, 180,
  60, 60,
  60, 60,
  60, 60,
  180, 180, 180, 180, 180, 180,
  100, 100, 100,
  100, 100, 100,
  30, 30, 30
};
// Tetris melody
const uint16_t TETRIS_MELODY[] = {
  0,NOTE_E5, 0, NOTE_E3, 0, NOTE_B4, 0, NOTE_C5, 0, NOTE_D5, 0,NOTE_E5, 0, NOTE_D5, 0, NOTE_C5,
  0, NOTE_B4, 0, NOTE_A4, 0, NOTE_A3, 0, NOTE_A4, 0, NOTE_C5, 0, NOTE_E5, 0, NOTE_A3, 0, NOTE_D5,
  0, NOTE_C5, 0, NOTE_B4, 0, NOTE_E4, 0,NOTE_G4, 0, NOTE_C5, 0, NOTE_D5, 0, NOTE_E3, 0, NOTE_E5,
  0, NOTE_E3, 0, NOTE_C5, 0, NOTE_A3, 0,NOTE_A4, 0, NOTE_A3, 0, NOTE_A4, 0, NOTE_A3, 0, NOTE_B2,
  0, NOTE_C3, 0, NOTE_D3, 0, NOTE_D5, 0,NOTE_F5, 0, NOTE_A5, 0, NOTE_C5, 0, NOTE_C5, 0, NOTE_G5,
  0, NOTE_F5, 0, NOTE_E5, 0, NOTE_C3, 0, 0, NOTE_C5, 0, NOTE_E5, 0, NOTE_A4, 0, NOTE_G4, 0, NOTE_D5,
  0, NOTE_C5, 0, NOTE_B4, 0, NOTE_E4, 0, NOTE_B4, 0, NOTE_C5, 0, NOTE_D5, 0, NOTE_G4, 0, NOTE_E5,
  0, NOTE_G4, 0, NOTE_C5, 0, NOTE_E4, 0, NOTE_A4, 0, NOTE_E3, 0, NOTE_A4, 0,
  0, NOTE_E5, 0, NOTE_E3, 0, NOTE_B4, 0, NOTE_C5, 0, NOTE_D5, 0, NOTE_E5, 0, NOTE_D5, 0,NOTE_C5,
  0, NOTE_B4, 0, NOTE_A4, 0, NOTE_A3, 0, NOTE_A4, 0, NOTE_C5, 0, NOTE_E5, 0, NOTE_A3, 0,NOTE_D5,
  0, NOTE_C5, 0, NOTE_B4, 0, NOTE_E4, 0, NOTE_G4, 0, NOTE_C5, 0, NOTE_D5, 0, NOTE_E3, 0,NOTE_E5,
  0, NOTE_E3, 0, NOTE_C5, 0, NOTE_A3, 0, NOTE_A4, 0, NOTE_A3, 0, NOTE_A4, 0, NOTE_A3, 0,NOTE_B2,
  0, NOTE_C3, 0, NOTE_D3, 0, NOTE_D5, 0, NOTE_F5, 0, NOTE_A5, 0, NOTE_C5, 0, NOTE_C5, 0,NOTE_G5,
  0, NOTE_F5, 0, NOTE_E5, 0, NOTE_C3, 0, 0, NOTE_C5, 0, NOTE_E5, 0, NOTE_A4, 0, NOTE_G4, 0, NOTE_D5,
  0, NOTE_C5, 0, NOTE_B4, 0, NOTE_E4, 0, NOTE_B4, 0, NOTE_C5, 0, NOTE_D5, 0, NOTE_G4, 0, NOTE_E5,
  0, NOTE_G4, 0, NOTE_C5, 0, NOTE_E4, 0, NOTE_A4, 0, NOTE_E3, 0, NOTE_A4, 0,
  0, NOTE_E4, 0, NOTE_E3, 0, NOTE_A2, 0, NOTE_E3, 0, NOTE_C4, 0, NOTE_E3, 0, NOTE_A2, 0, NOTE_E3,
  0, NOTE_D4, 0, NOTE_E3, 0, NOTE_GS2, 0, NOTE_E3, 0, NOTE_B3, 0,NOTE_E3, 0, NOTE_GS2, 0, NOTE_E3,
  0, NOTE_C4, 0, NOTE_E3, 0, NOTE_A2, 0, NOTE_E3, 0, NOTE_A3, 0, NOTE_E3, 0, NOTE_A2, 0, NOTE_E3,
  0, NOTE_GS3, 0,  NOTE_E3, 0, NOTE_GS2, 0, NOTE_E3, 0, NOTE_B3, 0, NOTE_E3, 0, NOTE_GS2, 0, NOTE_E3,
  0, NOTE_E4, 0, NOTE_E3, 0, NOTE_A2, 0, NOTE_E3, 0, NOTE_C4, 0, NOTE_E3, 0, NOTE_A2, 0, NOTE_E3,
  0, NOTE_D4, 0, NOTE_E3, 0, NOTE_GS2, 0, NOTE_E3, 0, NOTE_B3, 0, NOTE_E3, 0, NOTE_GS2, 0, NOTE_E3,
  0, NOTE_C4, 0, NOTE_E3, 0, NOTE_E4, 0, NOTE_E3, 0, NOTE_A4, 0, NOTE_E3, 0, NOTE_A2, 0, NOTE_E3,
  0, NOTE_GS4, 0, NOTE_E3, 0, NOTE_GS2, 0, NOTE_E3, 0, NOTE_GS2, 0, NOTE_E3, 0, NOTE_GS2, 0, NOTE_E3,
  0, NOTE_E5, 0, NOTE_E3, 0, NOTE_B4, 0, NOTE_C5, 0, NOTE_D5, 0, NOTE_E5, 0, NOTE_D5, 0, NOTE_C5,
  0, NOTE_B4, 0, NOTE_A4, 0, NOTE_A3, 0, NOTE_A4, 0, NOTE_C5, 0, NOTE_E5, 0, NOTE_A3, 0, NOTE_D5,
  0, NOTE_C5, 0, NOTE_B4, 0, NOTE_E4, 0, NOTE_G4, 0, NOTE_C5, 0, NOTE_D5, 0, NOTE_E3, 0, NOTE_E5,
  0, NOTE_E3, 0, NOTE_C5, 0, NOTE_A3, 0, NOTE_A4, 0, NOTE_A3, 0, NOTE_A4, 0, NOTE_A3, 0, NOTE_B2,
  0, NOTE_C3, 0, NOTE_D3, 0, NOTE_D5, 0, NOTE_F5, 0, NOTE_A5, 0, NOTE_C5, 0, NOTE_C5, 0, NOTE_G5,
  0, NOTE_F5, 0, NOTE_E5, 0, NOTE_C3, 0, 0, NOTE_C5, 0, NOTE_E5, 0, NOTE_A4, 0, NOTE_G4, 0, NOTE_D5,
  0, NOTE_C5, 0, NOTE_B4, 0, NOTE_E4, 0, NOTE_B4, 0, NOTE_C5, 0, NOTE_D5, 0, NOTE_G4, 0, NOTE_E5,
  0, NOTE_G4, 0, NOTE_C5, 0, NOTE_E4, 0, NOTE_A4, 0, NOTE_E3, 0, NOTE_A4, 0,
  0, NOTE_E5, 0, NOTE_E3, 0, NOTE_B4, 0, NOTE_C5, 0, NOTE_D5, 0, NOTE_E5, 0, NOTE_D5, 0,NOTE_C5,
  0, NOTE_B4, 0, NOTE_A4, 0, NOTE_A3, 0, NOTE_A4, 0, NOTE_C5, 0, NOTE_E5, 0, NOTE_A3, 0,NOTE_D5,
  0, NOTE_C5, 0, NOTE_B4, 0, NOTE_E4, 0, NOTE_G4, 0, NOTE_C5, 0, NOTE_D5, 0, NOTE_E3, 0,NOTE_E5,
  0, NOTE_E3, 0, NOTE_C5, 0, NOTE_A3, 0, NOTE_A4, 0, NOTE_A3, 0, NOTE_A4, 0, NOTE_A3, 0,NOTE_B2,
  0, NOTE_C3, 0, NOTE_D3, 0, NOTE_D5, 0, NOTE_F5, 0, NOTE_A5, 0, NOTE_C5, 0, NOTE_C5, 0,NOTE_G5,
  0, NOTE_F5, 0, NOTE_E5, 0, NOTE_C3, 0, 0, NOTE_C5, 0, NOTE_E5, 0, NOTE_A4, 0, NOTE_G4, 0, NOTE_D5,
  0, NOTE_C5, 0, NOTE_B4, 0, NOTE_E4, 0, NOTE_B4, 0, NOTE_C5, 0, NOTE_D5, 0, NOTE_G4, 0, NOTE_E5,
  0, NOTE_G4, 0, NOTE_C5, 0, NOTE_E4, 0, NOTE_A4, 0, NOTE_E3, 0, NOTE_A4, 0,
  0, NOTE_E4, 0, NOTE_E3, 0, NOTE_A2, 0, NOTE_E3, 0, NOTE_C4, 0, NOTE_E3, 0, NOTE_A2, 0, NOTE_E3,
  0, NOTE_D4, 0, NOTE_E3, 0, NOTE_GS2, 0, NOTE_E3, 0,NOTE_B3, 0, NOTE_E3, 0, NOTE_GS2, 0, NOTE_E3,
  0, NOTE_C4, 0, NOTE_E3, 0, NOTE_A2, 0, NOTE_E3, 0, NOTE_A3, 0, NOTE_E3, 0, NOTE_A2, 0, NOTE_E3,
  0, NOTE_GS3, 0, NOTE_E3, 0, NOTE_GS2, 0, NOTE_E3, 0, NOTE_B3, 0, NOTE_E3, 0, NOTE_GS2, 0, NOTE_E3,
  0, NOTE_E4, 0, NOTE_E3, 0, NOTE_A2, 0, NOTE_E3, 0, NOTE_C4, 0, NOTE_E3, 0, NOTE_A2, 0, NOTE_E3,
  0, NOTE_D4, 0, NOTE_E3, 0, NOTE_GS2, 0, NOTE_E3, 0, NOTE_B3, 0, NOTE_E3, 0, NOTE_GS2, 0, NOTE_E3,
  0, NOTE_C4, 0, NOTE_E3, 0, NOTE_E4, 0, NOTE_E3, 0, NOTE_A4, 0, NOTE_E3, 0, NOTE_A2, 0, NOTE_E3,
  0, NOTE_GS4, 0, NOTE_E3, 0, NOTE_GS2, 0, NOTE_E3, 0, NOTE_GS2, 0, NOTE_E3, 0, NOTE_GS2, 0, NOTE_E3,
};
// Tetris tempo
const uint8_t TETRIS_TEMPO[] = {
  40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 63, 20, 63, 20, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40,
  125, 40, 250, 80, 125, 40, 125, 40, 63, 20, 63, 20, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 63, 20, 63, 20, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 250, 80, 250, 80,
  125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 63, 20, 63, 20, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40,
  125, 40, 250, 80, 125, 40, 125, 40, 63, 20, 63, 20, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 63, 20, 63, 20, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 250, 80, 250, 80,
  125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40,
  125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40,
  125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 63, 20, 63, 20, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40,
  125, 40, 250, 80, 125, 40, 125, 40, 63, 20, 63, 20, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 63, 20, 63, 20, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 250, 80, 250, 80,
  125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 63, 20, 63, 20, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40,
  125, 40, 250, 80, 125, 40, 125, 40, 63, 20, 63, 20, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 63, 20, 63, 20, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 250, 80, 250, 80,
  125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40,
  125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40, 125, 40,
};

