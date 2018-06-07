# Programmeringsprojekt-30010

PowerUps/Downs Ideer:
- Extra ball
- Extra speed/less speed
- Extra board speed on demand
- Bigger/smaller board
- DangerBomb
hej
- Extra life
- Sticky board
- Reverse board direction

Controller Ideer:
- Joystick - (Første kontroller vi skal have til at virke)
- Ret
- Wiiboard
- Potentiometer (blå dimser) - (Kan måske bruges til ændring af hastighed ingame)
- Accelerometer

MENU:
-chooseMenuOptions()
-While(1) styr med "controller" op og ned og button-click to choose
Vælg mellem: Play, options, highscore, help
Mulig styre metode: joystick - up/ned og right to choose, left to go back 
}
-changeOptions(){
Change difficulty - speed and direction
}
-chooseLevel(){
Efter play er valgt, kan levels (maps) vælges
}
-helpMenu(){
Vis controls
}

//DRAW:

drawMenu(){
//Clear screen
//Draw window with title at top and options in middle
}

initLevel(){
// Draws current window(3 walls), level, player and ball.
// Gives angle and speed upon starting
}

drawPlayer(struct player_t){
// Draws stick
}

drawLevel(struct level_t){
// Draws all blocks with color depending on number of lives.
}

drawBall(struct ball_t){
// Draws ball
}


//GAMEPHYSICS:

updatePlayerPos(struct player_t){
// Check direction, drawPlayer
}

updateBall(struct ball_t){
// Check for kollision
// Hvis kollision med blocks, updateLevel, updateVector
// Hvis kollision med player eller en af 3 walls, updateVector og drawBall
// Hvis ingen kollision, drawBall ud fra sidste position og vector
// Hvis out of bounds, restart ballPos og playerPos uden restart af level (mulig brug af initLevel), updateLives
}

updateLevel(struct level_t){
// Fjern block, hvis ramt
// Kaldes fra updateBall/checkBlockCollision
// Hvis sidste block er ramt, nextLevel
}

updateLives(){
// Hvis out of bounds (under player), -1 fra antal liv
// Kaldes fra updateBall/checkWallCollision
}

updateScore(){
// Hvis block ramt, updater score
// Score incrementes alt efter sværhedsgrad
// Kaldes fra updateBall/checkBlockCollision
}

checkPlayerCollision(struct ball_t bold, struct player_t player);
checkBlockCollision(struct ball_t bold, struct level_t level);
checkWallCollision(struct ball_t bold, X1,Y1,X2,Y2){
// Also checks loss condition
}


//DISPLAY:

showLivesLCD(){
// Vis liv på LCD
}

showLevelLCD(){
// Vis level på LCD
}

showScoreLCD(){
// Vis score på LCD
}

showLivesPutty(){
// Vis liv på Putty
}

showLevelPutty(){
// Vis level på Putty
}

showScorePutty(){
//Vis score på Putty
}
