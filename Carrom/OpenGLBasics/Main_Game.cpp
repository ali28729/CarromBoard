#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#include "tga.cpp"
#include "glut.h"
#include <chrono>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <ctgmath>
#include "Variables.h"
#include "Game_Functions.h"

#define PI 3.14159265359

using namespace std;

int g_Width=700;
int g_Height=700;

int mouse_X=0;	
int mouse_Y=0;	

float
posX[20],
posY[20],
VX[20],
VY[20],		//0 = STRIIKER 1 = QUEEN, 2 - 10 = BLACK , 11 - 19 = WHITE
t,
friction = -300,
Left_Click_Press_Duration = 0
;

auto start = glutGet(GLUT_ELAPSED_TIME), finish = glutGet(GLUT_ELAPSED_TIME);

bool
Moving = false,
StrikerCollide = true,
KeyState[256],
Coin_Active[20],
Left_Click_Press = false,
Foul_BaseLine = false,
Striker_CrossedBaseLine = false,
Black_Pocketed = false,
White_Pocketed = false,
Queen_Pocketed = false,
Queen_Pocketed_Prev_Turn = false,
Black_Touch = false,
White_Touch = false,
Queen_Touch = false
;

int
timer = 0,
squareX[][4] = { { 141, 559, 559, 141 }, { 158, 542, 542, 158 } },
squareY[][4] = { { 143, 143, 557, 557 }, { 160, 160, 540, 540 } },
radius = 14,
CoinsInMotion = 1,
TurnCounter = 0,
StrikerLimitX[4][2] = { { squareX[1][0] + 30, squareX[1][1] - 30 }, { squareX[1][1], squareX[0][1] }, { squareX[1][0] + 30, squareX[1][1] - 30 }, { squareX[0][0], squareX[1][0] } },
StrikerLimitY[4][2] = { { squareY[1][2], squareY[0][2] }, { squareY[1][0] + 27, squareY[1][2] - 27 }, { squareY[0][0], squareY[1][0] }, { squareY[1][0] + 28, squareY[1][2] - 28 } },
StrikerInitialX[4] = { 350, 550, 350, 150 },
StrikerInitialY[4] = { 550, 350, 150, 350 },
FirstCoinCollision = 0,
MenuSelect = 0,
MenuButtonSelected = 0,
Queen_Pocketed_By = 0,
White_Left = 9,
Black_Left = 9,
Players = 0,
Game_Won_By = 0
;


GLuint BackId, MenuId[3], ButtonId[2];

void init();
void myMouseFunction( int button, int state, int mouseX, int mouseY );
void myKeyboardFunction( unsigned char key, int mouseX, int mouseY );
void mySpecialKeysFunction(int key, int x, int y);
void myReshapeFunction( int width, int height );
void myTimerFunction( int val );
void myDisplayFunction();
void mySpecialKeyUp(int key, int x, int y);


void KeyOperations();
void myPassiveMouseFunction(int, int);



GLuint loadtexture(char *name)
{
	GLuint temp ;
	glGenTextures(1,&temp);
	loadTGA(name,temp);
	return temp;
}

int main(int argc, char** argv)
{
	glutInit( &argc, argv );		//initilize the GLUT libraray

	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA );		//has four colour components red, green,blue, and alpha 
	glutInitWindowSize(g_Width + 200, g_Height);	//size of window
	glutInitWindowPosition( 0, 0 );		//poistion of window
	glutCreateWindow( "CARROM BOARD!" );

	init();
	BackId=loadtexture("Soft.tga");
	MenuId[0] = loadtexture("Menu4.tga");
	MenuId[1] = loadtexture("Menu5.tga");
	MenuId[2] = loadtexture("Menu6.tga");
	ButtonId[0] = loadtexture("back.tga");
	ButtonId[1] = loadtexture("quit.tga");

	glutMouseFunc( myMouseFunction );
	glutKeyboardFunc( myKeyboardFunction );
	glutSpecialFunc( mySpecialKeysFunction );
	glutSpecialUpFunc(mySpecialKeyUp);
	glutPassiveMotionFunc(myPassiveMouseFunction);

	glutReshapeFunc( myReshapeFunction );
	glutDisplayFunc( myDisplayFunction ); 
	glutTimerFunc( timer, myTimerFunction, 0 ); 	

	glutFullScreen();	// make the screen fullscreen
	glutSetCursor( GLUT_CURSOR_CROSSHAIR );	//Displays the type of cursor u want
	SetFlower(0);
	glutMainLoop();
	
	return 0;
}

void init(void) 
{
	glClearColor( 0.05, 0.02, 0.02, 1.0 );		//background color of openGl window
	//			 ^red, green, blue, alpha(opaquenss) 
	glMatrixMode( GL_PROJECTION );		//glMatrixMode — specify which matrix is the current matrix ????
	glLoadIdentity();		//glLoadIdentity — replace the current matrix with the identity matrix	????

	glOrtho(0.0, g_Width + 200, 0.0, g_Height, -1.0, 1.0);	//set (0,0) on left top
}

void myMouseFunction(int button, int state, int mouseX, int mouseY)
{
	if (MenuSelect == 3)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) //Click
		{
			Left_Click_Press = true;
		}
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if (MenuSelect == 3)
		{
			Left_Click_Press = false;
			Shoot_Striker();
			printf("mouse clicked \n");
			printf("\nmouseX: %d mouseY: %d, State: %d", mouseX, mouseY, state);
		}
		switch (MenuButtonSelected)
		{
		case 1:
			MenuSelect = 3;
			Players = 2;
			NewGame(4);
			break;
		case 2:
			MenuSelect = 3;
			Players = 4;
			NewGame(4);
			break;
		case 3:
			MenuSelect = 1;
			break;
		case 4:
			MenuSelect = 2;
			break;
		case 5:
			MenuSelect = 0;
			break;
		case 6:	
			exit(0);
			break;
		default:
			break;
		}
	}
}

void myPassiveMouseFunction(int X, int Y)
{
	mouse_X = X - 170;
	mouse_Y = Y - 34;
}

void myKeyboardFunction( unsigned char key, int mouseX, int mouseY )
{
	KeyState[key] = true;
	if( key == '4' )
	{
		NewGame(-0.03);
	}
	if (key == '6')
	{
		NewGame(0.03);
	}
}

void mySpecialKeysFunction(int key, int x, int y)
{
	KeyState[key] = true;
	switch( key )
	{
	case GLUT_KEY_UP:
		break;
	case GLUT_KEY_DOWN:
		break;
	case GLUT_KEY_LEFT:
		break;
	case GLUT_KEY_RIGHT:
		break;
	case GLUT_KEY_HOME:
		break;
	case GLUT_KEY_END:
		break;
	case GLUT_KEY_PAGE_UP:
		break;
	case GLUT_KEY_PAGE_DOWN:
		break;
	}
}

void mySpecialKeyUp(int key, int x, int y)
{
	KeyState[key] = false;
}

void myReshapeFunction( int width, int height )
{
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport (0, 0, width, height);

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glOrtho(-170.0, width-170, height-34, -34, -1.0, 1.0);	//change the (0,0) to top left
}

void myTimerFunction( int val )
{
	glutTimerFunc( timer, myTimerFunction, 0 );
	if (MenuSelect == 3)
	{
		KeyOperations();
		Collision_Check();
		finish = glutGet(GLUT_ELAPSED_TIME);
		t = finish - start;
		start = finish;
		movement();
		if (CoinsInMotion == 0 && Moving)
		{
			MoveEndFunc();
		}
		if (Moving)
		{
			Striker_CrossBaseLine_Check();
		}
		else
		{
			StrikerPassiveFunc();
		}
	}
	myDisplayFunction();
	//printf("%d",TurnCounter);
}

void myDisplayFunction()
{
	if (MenuSelect == 3)
	{
		DisplayMain();
		DisplayPanel();
		DisplayWin();
	}
	else if (MenuSelect == 0)
	{
		DisplayMenu();
	}
	else if (MenuSelect == 1 || MenuSelect == 2)
	{
		DisplaySubMenu(MenuSelect);
	}

	glutSwapBuffers();		//brings the openGl window on the front
}

void KeyOperations()
{
	if (!Moving)
	{
		if (KeyState[GLUT_KEY_LEFT])
			VX[0] = -100;
		else if (KeyState[GLUT_KEY_RIGHT])
			VX[0] = 100;
		else
			VX[0] = 0;
		if (KeyState[GLUT_KEY_UP])
			VY[0] = -100;
		else if (KeyState[GLUT_KEY_DOWN])
			VY[0] = 100;
		else
			VY[0] = 0;
	}
}

