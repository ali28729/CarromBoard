#include <chrono>
#include "glut.h"

using namespace std;

extern float
posX[20],
posY[20],
VX[20],
VY[20],		//0 = STRIIKER 1 = QUEEN, 2 - 10, 11 - 19
t,/*Time elapsed in one call of timer function*/
friction,
Left_Click_Press_Duration
;


extern int
mouse_X,
mouse_Y,

g_Width,
g_Height,

timer,
squareX[][4],/*Imaginary squares for setting limits for striker*/
squareY[][4],
radius,
CoinsInMotion,
TurnCounter,
StrikerLimitX[4][2],
StrikerLimitY[4][2],
StrikerInitialX[4],/*Initial x-values for striker*/
StrikerInitialY[4],/*Initial y-values for striker*/
FirstCoinCollision,
MenuButtonSelected,/*1=2 Players, 2=4 Players, 3=How to Play, 4=Rules, 5=Back, 6=Exit*/
Queen_Pocketed_By,/*0 = NONE, 1= BLACK, 2= WHITE*/
White_Left,
Black_Left,
Players,
Game_Won_By/*0 = NONE, 1= BLACK, 2= WHITE*/
;

extern bool
Moving,
StrikerCollide,
KeyState[256],
Coin_Active[20],
Left_Click_Press,

Foul_BaseLine,
Striker_CrossedBaseLine,
Black_Pocketed,
White_Pocketed,
Queen_Pocketed,
Queen_Pocketed_Prev_Turn,
Black_Touch,
White_Touch,
Queen_Touch
;


extern GLuint BackId, MenuId[3], ButtonId[2];