#include "flashmemory.h"

void writeFlash(struct game_state_t* gs){
    uint32_t address = 0x0800F800;
    uint8_t i, j;
    FLASH_Unlock();  // Unlock FLASH for modification
    FLASH_ClearFlag( FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR );
    FLASH_ErasePage(address);
    for ( i = 0; i < 5 ; i++ ){
 		for ( j = 0; j < 7; j++){
            // Writes the names
            FLASH_ProgramHalfWord(address + (i * 7 + j) * 2, gs->highscorenames[i][j]);
 		}
 		// Writes the scores
 		FLASH_ProgramHalfWord(address + (5 * 7 + 7) * 2 + i * 2, gs->highscores[i]);
 		// Writes the time info
 		// The address is moved 10 steps
 		FLASH_ProgramHalfWord(address + (5 * 7 + 12) * 2 + i * 2, gs->highscoreMinutes[i]);
 		FLASH_ProgramHalfWord(address + (5 * 7 + 17) * 2 + i * 2, gs->highscoreHours[i]);
 		FLASH_ProgramHalfWord(address + (5 * 7 + 22) * 2 + i * 2, gs->highscoreDate[i]);
 		FLASH_ProgramHalfWord(address + (5 * 7 + 27) * 2 + i * 2, gs->highscoreMonth[i]);
 	}
 	FLASH_Lock(); // Locks FLASH for modification


}

void readFlash(struct game_state_t* gs){
    uint32_t address = 0x0800F800;// Starting address of the last page
    uint8_t i, j;
    for ( i = 0; i < 5 ; i++ ){
        for ( j = 0; j < 7; j++){
        gs->highscorenames[i][j] = (*(uint16_t *)(address + (i * 7 + j) * 2)); // Read names
        }
        gs->highscores[i] = *(uint16_t *)(address + (5 * 7 + 7) * 2 + i * 2); // Read scores

        gs->highscoreMinutes[i] = *(uint16_t *)(address + (5 * 7 + 12) * 2 + i * 2); // Read minutes
        gs->highscoreHours[i] = *(uint16_t *)(address + (5 * 7 + 17) * 2 + i * 2); // Read hours
        gs->highscoreDate[i] = *(uint16_t *)(address + (5 * 7 + 22) * 2 + i * 2); // Read date
        gs->highscoreMonth[i] = *(uint16_t *)(address + (5 * 7 + 27) * 2 + i * 2); // Read month
    }
}
