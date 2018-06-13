#include "flashmemory.h"

void writeFlash(struct game_state_t* gs){
    uint32_t address = 0x0800F800;
    FLASH_Unlock();  // Unlock FLASH for modification
    FLASH_ClearFlag( FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR );
    FLASH_ErasePage(address);
    for ( int i = 0 ; i < 5 ; i++ ){
 		FLASH_ProgramHalfWord(address + i * 2, gs->highscores[i]);
 	}
 	FLASH_Lock(); // Locks FLASH for modification


}

void readFlash(struct game_state_t* gs){
    uint32_t address = 0x0800F800;// Starting address of the last page
    for ( uint32_t i = 0 ; i < 5 ; i++ ){
        gs->highscores[i] = *(uint16_t *)(address + i * 2); // Read Command
    }
}

