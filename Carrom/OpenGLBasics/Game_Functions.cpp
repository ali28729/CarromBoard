#include "Game_Functions.h"
#include <ctgmath>
#include "Variables.h"
#include "glut.h"
#include <chrono>
#include <Windows.h>//For Sound
#include <mmsystem.h>//For Sound


#define PI 3.14159265359

using namespace std;

void draw_Circle(float a, float b, float r, int accuracy)  //(a,b)=(x,y) of centre. R is radius
{
	float x, y, angle;
	glBegin(GL_POLYGON);
	for (int i = 0; i < accuracy; i++)
	{
		angle = i * 2 * 3.1416 / accuracy;
		x = r*cosf(angle);
		y = r*sinf(angle);
		glVertex2f(x + a, b + y);
	}
	glEnd();
}

void renderBitmapString(float x, float y, char *string)
{
	char *c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
}

void renderBitmapString2(float x, float y, char *string)
{
	char *c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
	}
}

void renderBitmapString3(float x, float y, char *string)
{
	char *c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}
}

float Distance(float X1, float Y1, float X2, float Y2)
{
	return sqrtf((X1 - X2)*(X1 - X2) + (Y1 - Y2)*(Y1 - Y2));
}

float Distance(int coin1, int coin2)
{
	return sqrtf((posX[coin1] - posX[coin2])*(posX[coin1] - posX[coin2]) + (posY[coin1] - posY[coin2])*(posY[coin1] - posY[coin2]));
}


void DisplayMain()
{
	glClear(GL_COLOR_BUFFER_BIT);
	DisplayLayout();
	int closest_coin;
	float x, y;
	/* CODE FOR DISPLAYING THE DIRECTION INDICATOR FROM STRIKER */
	if (!Moving)
	{
		Coin_InPath(&closest_coin, &x, &y);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_BLEND);
		glBegin(GL_POLYGON);
		glColor4f(0.9, 0.9, 0.0f, 0.5f);
		glVertex2f(posX[0] + x, posY[0] - y);
		glColor4f(0.2 + Left_Click_Press_Duration / 2.5f, 1 - Left_Click_Press_Duration / 2, 0.0f, 0.9f);
		glVertex2f((posX[0] + x) - ((posX[0] + x) - (mouse_X + x)) *Left_Click_Press_Duration / 2, (posY[0] - y) - ((posY[0] - y) - (mouse_Y - y)) *Left_Click_Press_Duration / 2);
		glColor4f(0.15 + Left_Click_Press_Duration / 2.5f, 1 - Left_Click_Press_Duration / 2, 0.0f, 0.6f);
		glVertex2f((posX[0] - x) - ((posX[0] - x) - (mouse_X - x)) *Left_Click_Press_Duration / 2, (posY[0] + y) - ((posY[0] + y) - (mouse_Y + y)) *Left_Click_Press_Duration / 2);
		glColor4f(0.7f, 0.9f, 0.0f, 0.5f);
		glVertex2f(posX[0] - x, posY[0] + y);
		glEnd();
		glDisable(GL_BLEND);
	}

	DisplayCoins();

	if (!Moving)
	{
		glLineWidth(1);
		glLineStipple(3, 0xAAAA);
		glEnable(GL_LINE_STIPPLE);

		glColor3f(0.2f, .05f, .02f);
		glBegin(GL_LINES);
		glVertex2f(posX[0], posY[0]);
		glVertex2f(mouse_X, mouse_Y);
		glEnd();

		glDisable(GL_LINE_STIPPLE);

		glColor3f(0.6f, .4f, .25f);
		glBegin(GL_LINES);
		glVertex2f(posX[0] + x, posY[0] - y);
		glVertex2f(mouse_X + x, mouse_Y - y);
		glVertex2f(posX[0] - x, posY[0] + y);
		glVertex2f(mouse_X - x, mouse_Y + y);
		glEnd();

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		draw_Circle(mouse_X, mouse_Y, 25, 25);
		if (closest_coin != 0)
		{
			glLineWidth(2);
			glColor3f(1.0f, 0.0f, 0.f);
			draw_Circle(posX[closest_coin], posY[closest_coin], 14, 25);
		}
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	}

}

void DisplayWin()
{
	if (Game_Won_By != 0) /*If variable is not equal to zero that means someone won the game*/
	{
		char score[10];
		/* PRINTING THE VICTORY INFO ACCORDINGLY */
		if (Game_Won_By == 1)
		{
			glEnable(GL_BLEND);
			glColor4f(0.0f, 0.0f, 0.0f, 0.9f);
			glBegin(GL_POLYGON);

			glVertex2f(0, 0);
			glVertex2f(900, 0);
			glVertex2f(900, 700);
			glVertex2f(0, 700);

			glEnd();
			glDisable(GL_BLEND);
			glColor3f(1.0f, 0.6f, 0.4f);
			renderBitmapString3(300, 337, "BLACK TEAM WON!");
			renderBitmapString3(300, 365, "Points:");
			if (Queen_Pocketed_By == 1)
				renderBitmapString3(375, 365, _itoa(White_Left + 5, score, 10));
			else
				renderBitmapString3(375, 365, _itoa(White_Left, score, 10));
		}
		else if (Game_Won_By == 2)
		{
			glEnable(GL_BLEND);
			glColor4f(1.0f, 1.0f, 1.0f, 0.9f);
			glBegin(GL_POLYGON);

			glVertex2f(0, 0);
			glVertex2f(900, 0);
			glVertex2f(900, 700);
			glVertex2f(0, 700);

			glEnd();
			glDisable(GL_BLEND);
			glColor3f(0.4f, 0.1f, 0.05f);
			renderBitmapString3(300, 337, "WHITE TEAM WON!");
			renderBitmapString3(300, 365, "Points:");
			if (Queen_Pocketed_By == 2)
				renderBitmapString3(375, 365, _itoa(Black_Left + 5, score, 10));
			else
				renderBitmapString3(375, 365, _itoa(Black_Left, score, 10));
		}
	}
}

void DisplayPanel()
{
	/*DRAW WHOLE MAIN PANEL*/
	glColor3f(0.35f, 0.27f, 0.17f);
	glBegin(GL_POLYGON);
	glVertex2f(700, 0);
	glVertex2f(900, 0);
	glColor3f(0.05f, 0.05f, 0.05f);
	glVertex2f(900, 700);
	glVertex2f(700, 700);
	glEnd();

	/*DRAW FRAME OF MAIN PANEL*/
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(7);
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(700, 3);
	glColor3f(.95f, .95f, .95f);
	glVertex2f(897, 3);
	glColor3f(0.45f, 0.45f, 0.55f);
	glVertex2f(897, 697);
	glColor3f(0.75f, 0.63f, 0.73f);
	glVertex2f(700, 697);
	glEnd();

	///*DRAW POWER BAR*/
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glBegin(GL_POLYGON);
	//glColor3f(0.8f, 0.21f, 0.01f);
	//glVertex2f(720, 500);
	//glColor3f(0.4f, 0.08f, 0.0f);
	//glVertex2f(720 + Left_Click_Press_Duration * 80, 500);
	//glColor3f(0.25f, 0.03f, 0.0f);
	//glVertex2f(720 + Left_Click_Press_Duration * 80, 540);
	//glColor3f(0.65f, 0.16f, 0.01f);
	//glVertex2f(720, 540);
	//glEnd();

	///*DRAW FRAME OF POWER BAR*/
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glLineWidth(3);
	//glBegin(GL_POLYGON);
	//glColor3f(1.0f, 1.0f, 1.0f);
	//glVertex2f(720, 500);
	//glColor3f(.8f, .8f, .8f);
	//glVertex2f(880, 500);
	//glColor3f(0.55f, 0.55f, 0.6f);
	//glVertex2f(880, 540);
	//glColor3f(0.95f, 0.95f, 0.95f);
	//glVertex2f(720, 540);
	//glEnd();
							

	/*	DISPLAY		*/
	/*	QUIT AND	*/
	/*	BACK		*/
	/*	BUTTONS		*/
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_BLEND);	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ButtonId[0]);
	
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);
	glVertex2f(g_Width + 32, 40);
	glTexCoord2f(1.0, 1.0);
	glVertex2f(g_Width + 168, 40);
	glTexCoord2f(1.0, 0.0);
	glVertex2f(g_Width + 168, 104); 
	glTexCoord2f(0.0, 0.0);
	glVertex2f(g_Width + 32, 104);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, ButtonId[1]);

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);
	glVertex2f(g_Width + 32, 105);
	glTexCoord2f(1.0, 1.0);
	glVertex2f(g_Width + 168, 105);
	glTexCoord2f(1.0, 0.0);
	glVertex2f(g_Width + 168, 169);
	glTexCoord2f(0.0, 0.0);
	glVertex2f(g_Width + 32, 169);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	

	/*CODE FOR HIGHLITING AND SELECTING OF BUTTONS*/
	if (mouse_X >= g_Width + 32 && mouse_X <= g_Width + 168)
	{
		glColor4f(1.0f, 1.0f, 1.0f, 0.1f);
		if (mouse_Y >= 40 && mouse_Y <= 104)
		{
			MenuButtonSelected = 5;
			glBegin(GL_POLYGON);
			glVertex2f(g_Width + 32, 40);
			glVertex2f(g_Width + 168, 40);
			glVertex2f(g_Width + 168, 104);
			glVertex2f(g_Width + 32, 104);
			glEnd();
		}
		else if (mouse_Y >= 105 && mouse_Y <= 169)
		{
			MenuButtonSelected = 6;
			glBegin(GL_POLYGON);
			glVertex2f(g_Width + 32, 105);
			glVertex2f(g_Width + 168, 105);
			glVertex2f(g_Width + 168, 169);
			glVertex2f(g_Width + 32, 169);
			glEnd();
		}
		else
			MenuButtonSelected = 0;
	}
	else
		MenuButtonSelected = 0;
	glDisable(GL_BLEND);
	
											/*WRITE ALL INFORMATION TEXT*/
	glColor3f(1.0f, 1.0f, 1.0f);
	if (TurnCounter % 2)
		renderBitmapString(720, 340, "Black Side's Turn.\n");
	else
		renderBitmapString(720, 340, "White Side's Turn.\n");
	{ 
		char x[10];
		renderBitmapString(720, 375, "Black Coins Left:");
		renderBitmapString(870, 375, _itoa(Black_Left, x, 10));
		renderBitmapString(720, 400, "White Coins Left:");
		renderBitmapString(870, 400, _itoa(White_Left, x, 10));
	}
	if (Foul_BaseLine)
	{
		glColor3f(1.0f, 0.0f, 0.0f);
		renderBitmapString(720, 270, "Base Line FOUL.");
	}
	if (!Moving)
	{
		if (StrikerCollide)
		{
			glColor3f(1.0f, 0.1f, 0.3f);
			renderBitmapString(720, 255, "Cannot Deploy");
			renderBitmapString(720, 280, "Striker Here!");
		}
		else if (Arc_Foul())
		{
			glColor3f(1.0f, 0.1f, 0.3f);
			renderBitmapString(720, 255, "Either Complete the");
			renderBitmapString(720, 280, "Circle Or Leave it!");
		}
	}

	glColor3f(0.7f, 0.65f, 0.35f);
	renderBitmapString2(720, 600, "Created By:");
	renderBitmapString2(750, 620, "Sohaib Zahid");
	renderBitmapString2(750, 640, "Muhammad Ali");
	renderBitmapString2(750, 660, "M. Junaid Nadeem");
}

void DisplayMenu()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, MenuId[0]);
	//Bottom
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glScalef(1, 1, 1);
	glColor4ub(255, 255, 255, 255);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);
	glVertex2f(100, 0);
	glTexCoord2f(1.0, 1.0);
	glVertex2f(868 , 0);
	glTexCoord2f(1.0, 0.0);
	glVertex2f(868, g_Height);
	glTexCoord2f(0.0, 0.0);
	glVertex2f(100, g_Height);
	glEnd();
	glPopMatrix();

	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, ButtonId[1]);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);
	glVertex2f(730, 600);
	glTexCoord2f(1.0, 1.0);
	glVertex2f(858, 600);
	glTexCoord2f(1.0, 0.0);
	glVertex2f(858, 664);
	glTexCoord2f(0.0, 0.0);
	glVertex2f(730, 664);
	glEnd();


	glDisable(GL_TEXTURE_2D);

	glColor4f(1.0f, 1.0f, 1.0f, 0.1f);
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if ((mouse_X >= 245 && mouse_X <= 739) && (mouse_Y >= 180 && mouse_Y <= 280))
	{
		MenuButtonSelected = 1;
		glBegin(GL_POLYGON);
		glVertex2f(245, 180);
		glVertex2f(739, 180);
		glVertex2f(739, 280);
		glVertex2f(245, 280);
		glEnd();
	}
	else if ((mouse_X >= 245 && mouse_X <= 739) && (mouse_Y >= 285 && mouse_Y <= 385))
	{
		MenuButtonSelected = 2;
		glBegin(GL_POLYGON);
		glVertex2f(245, 285);
		glVertex2f(739, 285);
		glVertex2f(739, 385);
		glVertex2f(245, 385);
		glEnd();
	}
	else if ((mouse_X >= 211 && mouse_X <= 779) && (mouse_Y >= 400 && mouse_Y <= 500))
	{
		MenuButtonSelected = 3;
		glBegin(GL_POLYGON);
		glVertex2f(211, 400);
		glVertex2f(779, 400);
		glVertex2f(779, 500);
		glVertex2f(211, 500);
		glEnd();
	}
	else if ((mouse_X >= 349 && mouse_X <= 649) && (mouse_Y >= 505 && mouse_Y <= 600))
	{
		MenuButtonSelected = 4;
		glBegin(GL_POLYGON);
		glVertex2f(349, 505);
		glVertex2f(649, 505);
		glVertex2f(649, 600);
		glVertex2f(349, 600);
		glEnd();
	}
	else if ((mouse_X >= 730 && mouse_X <= 858) && (mouse_Y >= 600 && mouse_Y <= 664))
	{
		MenuButtonSelected = 6;
		glBegin(GL_POLYGON);
		glVertex2f(730, 600);
		glVertex2f(858, 600);
		glVertex2f(858, 664);
		glVertex2f(730, 664);
		glEnd();
	}
	else
		MenuButtonSelected = 0;
	glDisable(GL_BLEND);
}

void DisplaySubMenu(int x)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, MenuId[x]);
	//Bottom
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glScalef(1, 1, 1);
	glColor4ub(255, 255, 255, 255);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);
	glVertex2f(0, 0);//draw square for menu
	glTexCoord2f(1.0, 1.0);
	glVertex2f(1024, 0);//2nd
	glTexCoord2f(1.0, 0.0);
	glVertex2f(1024, g_Height);//3rd 
	glTexCoord2f(0.0, 0.0);
	glVertex2f(0, g_Height);//4th
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	if ((mouse_X >= 349 && mouse_X <= 649) && (mouse_Y >= 510 && mouse_Y <= 610))
	{
		MenuButtonSelected = 5;
		glColor4f(1.0f, 1.0f, 1.0f, 0.1f);
		glEnable(GL_BLEND);											//ENABLES 
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBegin(GL_POLYGON);
		glVertex2f(349, 510);
		glVertex2f(649, 510);
		glVertex2f(649, 610);
		glVertex2f(349, 610);
		glEnd();
		glDisable(GL_BLEND);
	}
	else
		MenuButtonSelected = 0;
}

void DisplayCoins()
{
	glColor3f(.9f, .65f, .47f);
	draw_Circle(posX[0], posY[0], 25, 12);
	glLineWidth(2);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(.7f, .45f, .27f);
	draw_Circle(posX[0], posY[0], 25, 25);
	//draw_Circle(posX[0], posY[0], 17, 25);
	//draw_Circle(posX[0], posY[0], 17, 25);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (int i = 1; i < 20; i++)
	{
		if (i == 1)
			glColor3f(1.0f, 0.2f, 0.2f);
		if (i == 2)
			glColor3f(0.2f, 0.2f, 0.2f);
		if (i == 11)
			glColor3f(1.0f, .85f, .63f);
		if (Coin_Active[i])
			draw_Circle(posX[i], posY[i], 14, 10);
	}
	
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (int i = 1; i < 20; i++)
	{
		if (i == 1)
			glColor3f(0.7f, 0.05f, 0.05f);
		if (i == 2)
			glColor3f(0.0f, 0.0f, 0.0f);
		if (i == 11)
			glColor3f(0.8f, .65f, .43f);
		if (Coin_Active[i])
		{
			draw_Circle(posX[i], posY[i], 7, 25);
			draw_Circle(posX[i], posY[i], 14, 25);
		}
	}
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void DisplayLayout()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, BackId);
	//Bottom
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glScalef(1, 1, 1);
	glColor4ub(255, 255, 255, 255);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);
	glVertex2f(0, 0);
	glTexCoord2f(1.0, 1.0);
	glVertex2f(g_Width, 0);
	glTexCoord2f(1.0, 0.0);
	glVertex2f(g_Width, g_Height);
	glTexCoord2f(0.0, 0.0);
	glVertex2f(0, g_Height);
	glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glLineWidth(1);
	//glColor3f(1.0, 1.0, 1.0);
	//draw_Circle(350, 350, 60, 100);
	//draw_Circle(squareX[1][3] + 5, squareY[1][3] + 20, 20, 25);
	//draw_Circle(squareX[1][3] - 20, squareY[1][3] - 5, 20, 25);
	//draw_Circle(squareX[1][2] - 5, squareY[1][2] + 20, 20, 25);
	//draw_Circle(squareX[1][2] + 20, squareY[1][2] - 5, 20, 25);
	//draw_Circle(squareX[1][1] - 5, squareY[1][1] - 20, 20, 25);
	//draw_Circle(squareX[1][1] + 20, squareY[1][1] + 5, 20, 25);
	//draw_Circle(squareX[1][0] + 5, squareY[1][0] - 20, 20, 25);
	//draw_Circle(squareX[1][0] - 20, squareY[1][0] + 5, 20, 25);
	//glBegin(GL_QUADS);
	//
	//glVertex2f(squareX[0][0], squareY[0][0]);//top left
	//glVertex2f(squareX[0][1], squareY[0][1]);//top right
	//glVertex2f(squareX[0][2], squareY[0][2]);//bottom right
	//glVertex2f(squareX[0][3], squareY[0][3]);//bottom left
	//glVertex2f(squareX[1][0], squareY[1][0]);//top left
	//glVertex2f(squareX[1][1], squareY[1][1]);//top right
	//glVertex2f(squareX[1][2], squareY[1][2]);//bottom right
	//glVertex2f(squareX[1][3], squareY[1][3]);//bottom left
	//glEnd();
	////glVertex2f(linetopX2, linetopY2 + 2);//bottom right
	////glVertex2f(linetopX1, linetopY1 + 2);//bottom left
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void NewGame(float angle)
{
	SetFlower(angle);

	for (int i = 0; i < 20; i++)
	{
		VX[i] = 0;
		VY[i] = 0;
		Coin_Active[i] = true;
	}
	Left_Click_Press_Duration = 0;
	Moving = false;
	StrikerCollide = true;
	Left_Click_Press = false;
	Foul_BaseLine = false;
	Striker_CrossedBaseLine = false;
	Black_Pocketed = false;
	White_Pocketed = false;
	Queen_Pocketed = false;
	Queen_Pocketed_Prev_Turn = false;
	Black_Touch = false;
	White_Touch = false;
	Queen_Touch = false;

	White_Left = 9;
	Black_Left = 9;

	FirstCoinCollision = 0;
	MenuButtonSelected = 0;
	Queen_Pocketed_By = 0;
	TurnCounter = 0;
	posX[TurnCounter] = 350;
	posY[TurnCounter] = 550;
	Game_Won_By = 0;
}

void SetFlower(float angle)
{
	for (int i = 0; i < 20; i++)
	{
		Coin_Active[i] = true;
	}

	static float angle_local = 3;
	angle_local += angle;
	//	STRIKER
	//posX[0] = 350;
	//posY[0] = 550;

	//	QUEEN
	posX[1] = 350;
	posY[1] = 350;

	//	11-18	=	WHITE COINS
	posX[11] = posX[1] + 28 * cosf(angle_local + PI / 3);
	posY[11] = posY[1] + 28 * sinf(angle_local + PI / 3);

	posX[12] = posX[1] + 28 * cosf(angle_local + PI);
	posY[12] = posY[1] + 28 * sinf(angle_local + PI);

	posX[13] = posX[1] + 28 * cosf(angle_local + 5 * PI / 3);
	posY[13] = posY[1] + 28 * sinf(angle_local + 5 * PI / 3);

	posX[14] = posX[1] + 56 * cosf(angle_local);
	posY[14] = posY[1] + 56 * sinf(angle_local);

	posX[15] = posX[1] + 56 * cosf(angle_local + PI / 3);
	posY[15] = posY[1] + 56 * sinf(angle_local + PI / 3);

	posX[16] = posX[1] + 56 * cosf(angle_local + 2 * PI / 3);
	posY[16] = posY[1] + 56 * sinf(angle_local + 2 * PI / 3);

	posX[17] = posX[1] + 56 * cosf(angle_local + PI);
	posY[17] = posY[1] + 56 * sinf(angle_local + PI);

	posX[18] = posX[1] + 56 * cosf(angle_local + 4 * PI / 3);
	posY[18] = posY[1] + 56 * sinf(angle_local + 4 * PI / 3);

	posX[19] = posX[1] + 56 * cosf(angle_local + 5 * PI / 3);
	posY[19] = posY[1] + 56 * sinf(angle_local + 5 * PI / 3);

	//	2-10	=	BLACK COINS 
	posX[2] = posX[1] + 28 * cosf(angle_local);
	posY[2] = posY[1] + 28 * sinf(angle_local);

	posX[3] = posX[1] + 28 * cosf(angle_local + 2 * PI / 3);
	posY[3] = posY[1] + 28 * sinf(angle_local + 2 * PI / 3);

	posX[4] = posX[1] + 28 * cosf(angle_local + 4 * PI / 3);
	posY[4] = posY[1] + 28 * sinf(angle_local + 4 * PI / 3);

	posX[5] = (posX[14] + posX[15]) / 2;
	posY[5] = (posY[14] + posY[15]) / 2;

	posX[6] = (posX[15] + posX[16]) / 2;
	posY[6] = (posY[15] + posY[16]) / 2;

	posX[7] = (posX[16] + posX[17]) / 2;
	posY[7] = (posY[16] + posY[17]) / 2;

	posX[8] = (posX[17] + posX[18]) / 2;
	posY[8] = (posY[17] + posY[18]) / 2;

	posX[9] = (posX[18] + posX[19]) / 2;
	posY[9] = (posY[18] + posY[19]) / 2;

	posX[10] = (posX[14] + posX[19]) / 2;
	posY[10] = (posY[14] + posY[19]) / 2;
}

void movement()
{
	CoinsInMotion = 0;
	for (int i = 0; i < 20; i++)
	{
		if (VX[i] != 0 || VY[i] != 0)
		{
			float angle = atan2f(VY[i], VX[i]);
			if (abs(VX[i]) <= abs(friction*cosf(angle)*(timer + t) / 1000))
				VX[i] = 0;
			else
				VX[i] = VX[i] + friction*cosf(angle)*(timer + t) / 1000;
			if (abs(VY[i]) <= abs(friction*sinf(angle)*(timer + t) / 1000))
				VY[i] = 0;
			else
				VY[i] = VY[i] + friction*sinf(angle)*(timer + t) / 1000;
			posX[i] = posX[i] + VX[i] * (timer + t) / 1000;
			posY[i] = posY[i] + VY[i] * (timer + t) / 1000;
			CoinsInMotion++;
			//printf("%f %f\n", VX[i], VY[i]);
		}
	}
}

void Shoot_Striker()
{
	if (Left_Click_Press_Duration != 0)//(!StrikerCollide && !Moving)
	{
		//if (Direction_Check(TurnCounter))
		{
			float Power = Left_Click_Press_Duration * 900;
			float X = mouse_X - posX[0];
			float Y = mouse_Y - posY[0];
			float angle = atan2f(Y, X);
			VX[0] = Power * cosf(angle);
			VY[0] = Power * sinf(angle);
			Moving = true;
			Left_Click_Press_Duration = 0;
		}
	}
}

void Collision_Check()
{
	for (int i = 0; Moving ? i < 20 : i < 1; i++)
	if (Coin_Active[i])
	{
		Coin_Active[i] = !Pocket_Check(i);
		if (i == 0)
			radius = 25;
		else
			radius = 14;

		OutOfBounds_Check(i, radius);

		StrikerCollide = false;

		for (int j = i + 1; j < 20; j++)
		if (Coin_Active[j])
		{
			float CollideDistance = 0;
			float distance = Distance(i, j);
			if (i == 0)
				CollideDistance = radius + 14;
			else
				CollideDistance = radius * 2;
			if (abs(posX[i] - posX[j]) <= CollideDistance && abs(posY[i] - posY[j]) <= CollideDistance)
			if (distance <= CollideDistance)
			{
				if (Moving)
				{

					if (i == 0)
					{
						if (Foul_BaseLine == false)
						{
							Foul_BaseLine = Foul_BaseLine_Check(j);
						}
						if (FirstCoinCollision == 0)
							FirstCoinCollision = j;

						if (j == 1)
							Queen_Touch = true;
						else if (j <= 10)
							Black_Touch = true;
						else if (j <= 19)
							White_Touch = true;
					}
					Perform_Collision(i, j, distance, CollideDistance);
				}
				else if (i == 0)
				{
					StrikerCollide = true;
				}
			}
		}
	}
}

void OutOfBounds_Check(int coin_number, float radius)
{
	if (posX[coin_number] < 62 + radius)
	{
		PlaySound(TEXT("hit.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
		VX[coin_number] = -VX[coin_number];
		posX[coin_number] = 62 + radius;
		if (FirstCoinCollision == 0)
			FirstCoinCollision = -1;
	}
	else if (posX[coin_number] > 638 - radius)
	{
		PlaySound(TEXT("hit.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
		VX[coin_number] = -VX[coin_number];
		posX[coin_number] = 638 - radius;
		if (FirstCoinCollision == 0)
			FirstCoinCollision = -1;
	}
	else if (posY[coin_number] < 62 + radius)
	{
		PlaySound(TEXT("hit.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
		VY[coin_number] = -VY[coin_number];
		posY[coin_number] = 62 + radius;
		if (FirstCoinCollision == 0)
			FirstCoinCollision = -1;
	}
	else if (posY[coin_number] > 638 - radius)
	{
		PlaySound(TEXT("hit.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
		VY[coin_number] = -VY[coin_number];
		posY[coin_number] = 638 - radius;
		if (FirstCoinCollision == 0)
			FirstCoinCollision = -1;
	}
}

void Perform_Collision(int coin1, int coin2, float Distance, float CollideDistance)
{
	if (VX[coin1] != 0 || VX[coin2] != 0 || VY[coin1] != 0 || VY[coin2] != 0)
		PlaySound(TEXT("hit2.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
	float temp1, temp2, CollideAxis, VelParallel1, VelNormal1, VelParallel2, VelNormal2, velocity1, velocity2, angle1, angle2;
	velocity1 = sqrtf(VX[coin1] * VX[coin1] + VY[coin1] * VY[coin1]);
	velocity2 = sqrtf(VX[coin2] * VX[coin2] + VY[coin2] * VY[coin2]);

	angle1 = atan2f(VY[coin1], VX[coin1]);
	angle2 = atan2f(VY[coin2], VX[coin2]);

	CollideAxis = atan2f(posY[coin2] - posY[coin1], posX[coin2] - posX[coin1]);
	VelParallel1 = velocity1 * cosf(CollideAxis - angle1);
	VelNormal1 = velocity1 * sinf(CollideAxis - angle1);
	VelParallel2 = velocity2 * cosf(CollideAxis - angle2);
	VelNormal2 = velocity2 * sinf(CollideAxis - angle2);

	if (coin1 != 0)
	{
		temp1 = VelParallel1;
		VelParallel1 = VelParallel2;
		VelParallel2 = temp1;
	}
	else
	{
		temp1 = VelParallel1;
		temp2 = VelParallel2;
		VelParallel1 = temp1 / 3 + 2 * temp2 / 3;
		VelParallel2 = 4 * temp1 / 3 - temp2 / 3;
	}
	//FINDING VELOCITIES AFTER EXCHANGING PARALLEL COMPONENTS
	velocity1 = sqrtf(VelParallel1*VelParallel1 + VelNormal1*VelNormal1);
	velocity2 = sqrtf(VelParallel2*VelParallel2 + VelNormal2*VelNormal2);

	angle1 = atan2f(VelNormal1, VelParallel1);
	angle2 = atan2f(VelNormal2, VelParallel2);

	posX[coin1] = posX[coin1] - 1.1*((CollideDistance - Distance) / 2)*cosf(CollideAxis);
	posY[coin1] = posY[coin1] - 1.1*((CollideDistance - Distance) / 2)*sinf(CollideAxis);
	posX[coin2] = posX[coin2] + 1.1*((CollideDistance - Distance) / 2)*cosf(CollideAxis);
	posY[coin2] = posY[coin2] + 1.1*((CollideDistance - Distance) / 2)*sinf(CollideAxis);

	VX[coin1] = velocity1 * cosf(CollideAxis - angle1);
	VY[coin1] = velocity1 * sinf(CollideAxis - angle1);
	VX[coin2] = velocity2 * cosf(CollideAxis - angle2);
	VY[coin2] = velocity2 * sinf(CollideAxis - angle2);
}

void Coin_InPath(int *closest, float *X, float *Y)
{
	float slope, angle, Normal_Distance, Vertical_Distance;
	slope = -(mouse_Y - posY[0]) / (mouse_X - posX[0]);
	angle = atan2f((mouse_Y - posY[0]), (mouse_X - posX[0]));
	*closest = 0;
	bool InPath[20];
	for (int i = 1; i < 20; i++)
	{
		if (Coin_Active[i] == true)
		{
			float Y_OnLine = -posX[i] * slope + slope * posX[0] + posY[0];
			Vertical_Distance = posY[i] - Y_OnLine;
			Normal_Distance = abs(Vertical_Distance * cosf(angle));
			if (Normal_Distance <= 39)
			if ((abs(slope) <= 1 && signbit(posX[0] - mouse_X) == signbit(posX[0] - posX[i]))
				||
				(abs(slope) >= 1 && signbit(posY[0] - mouse_Y) == signbit(posY[0] - posY[i])))
			{
				InPath[i] = true;
				continue;
			}
		}
		InPath[i] = false;
	}

	for (int i = 1; i < 20; i++)
	{
		if (InPath[i])
		{
			if (Distance(0, i) < Distance(*closest, 0) || *closest == 0)
				*closest = i;
		}
	}

	//if (Closest_Coin == 0)
	//{
	//	*X = posX[0];
	//	*Y = posY[0];
	//	return;
	//}
	//float ptX, ptY;
	//if (angle >= PI / 2 && angle <= 3 * PI / 2)
	//	ptX = posX[Closest_Coin] - (Normal_Distance*cosf(-angle));
	//else
	//	ptX = posX[Closest_Coin] + (Normal_Distance*cosf(-angle));
	//ptY = -slope*ptX + slope*posX[0] + posY[0];
	//for (ptX; sqrtf((ptX - posX[Closest_Coin])*(ptX - posX[Closest_Coin]) + (ptY - posY[Closest_Coin])*(ptY - posY[Closest_Coin])) <= 39; ptX>posX[0] ? ptX-- : ptX++)
	//{
	//	ptY = +slope*ptX - slope*posX[0] - posY[0];
	//}
	//if (abs(posX[0] - posX[Closest_Coin]) < abs(posY[0] - posY[Closest_Coin]))
	//{
	//	ptY = (posY[0] + posY[Closest_Coin]) / 2;
	//	ptX = -(ptY - slope*posX[0] - posY[0]) / slope;
	//	do
	//	{
	//		if (Distance(ptX, ptY, posX[Closest_Coin], posY[Closest_Coin]) > 39)
	//			ptY = (ptY + posY[Closest_Coin]) / 2;
	//		else
	//			ptY = (ptY + posY[0]) / 2;
	//		ptX = -(ptY - slope*posX[0] - posY[0]) / slope;
	//	} while (Distance(ptX, ptY, posX[Closest_Coin], posY[Closest_Coin]) >= 39.00005 && Distance(ptX, ptY, posX[Closest_Coin], posY[Closest_Coin]) <= 38.99995);
	//}
	//else
	//{
	//	ptX = (posX[0] + posX[Closest_Coin]) / 2;
	//	ptY = -slope*ptX + slope*posX[0] + posY[0];
	//	do
	//	{
	//		if (Distance(ptX, ptY, posX[Closest_Coin], posY[Closest_Coin]) > 39)
	//			ptX = (ptX + posX[Closest_Coin]) / 2;
	//		else
	//			ptX = (ptX + posX[0]) / 2;			
	//		ptY = -slope*ptX + slope*posX[0] + posY[0];
	//	} while (Distance(ptX, ptY, posX[Closest_Coin], posY[Closest_Coin]) >= 39.00005 && Distance(ptX, ptY, posX[Closest_Coin], posY[Closest_Coin]) <= 38.99995);
	//}




	//*X = ptX;
	//*Y = ptY;
	*X = 25*sinf(angle);
	*Y = 25*cosf(angle);
}

void StrikerPassiveFunc()
{
	if (Left_Click_Press == true && !Arc_Foul() && !StrikerCollide && Direction_Check(TurnCounter*(4 / Players)))
	{
		if (Left_Click_Press_Duration <= 2)
			Left_Click_Press_Duration += t / 1000;
	}
	else
		Left_Click_Press_Duration = 0;

	if (posX[0] < StrikerLimitX[TurnCounter*(4 / Players)][0])
		posX[0] = StrikerLimitX[TurnCounter*(4 / Players)][0];
	else if (posX[0] > StrikerLimitX[TurnCounter*(4 / Players)][1])
		posX[0] = StrikerLimitX[TurnCounter*(4 / Players)][1];

	if (posY[0] < StrikerLimitY[TurnCounter*(4 / Players)][0])
		posY[0] = StrikerLimitY[TurnCounter*(4 / Players)][0];
	else if (posY[0] > StrikerLimitY[TurnCounter*(4 / Players)][1])
		posY[0] = StrikerLimitY[TurnCounter*(4 / Players)][1];
}







int Direction_Check(int turn)
{
	switch (turn)
	{
	case 0:
		if (mouse_Y > 548)
			return 0;
		else
			return 1;
		break;
	case 1:
		if (mouse_X > 548)
			return 0;
		else
			return 1;
		break;
	case 2:
		if (mouse_Y < 152)
			return 0;
		else
			return 1;
		break;
	case 3:
		if (mouse_X < 150)
			return 0;
		else
			return 1;
		break;
	default:
		return -1;
		break;
	}
}

bool Pocket_Check(int coin_number)
{
	if (!Coin_Active[coin_number])
		return true;

	if (Distance(81, 81, posX[coin_number], posY[coin_number]) > 13.5)
	if (Distance(619, 81, posX[coin_number], posY[coin_number]) > 13.5)
	if (Distance(81, 619, posX[coin_number], posY[coin_number]) > 13.5)
	if (Distance(619, 619, posX[coin_number], posY[coin_number]) > 13.5)
		return false;

	if (coin_number == 0)
		return false;

	if (coin_number == 1)
		Queen_Pocketed = true;
	else if (coin_number <= 10)
	{
		Black_Pocketed = true;
		Black_Left--;
	}
	else if (coin_number <= 19)
	{
		White_Pocketed = true;
		White_Left--;
	}

	PlaySound(TEXT("click2.wav"), NULL, SND_FILENAME | SND_ASYNC);
	VX[coin_number] = 0;
	VY[coin_number] = 0;
	return true;
}

bool Arc_Foul()
{
	if (!Moving)
	{
		float x1, x2, y1, y2;
		switch (TurnCounter*(4 / Players))
		{
		case 0:
			if (posX[0] == StrikerLimitX[0][0] || posX[0] == StrikerLimitX[0][1])
				return false;
			else
			{
				x1 = 180.5;
				y1 = 700 - 151.5;
				x2 = 700 - 180.5;
				y2 = 700 - 151.5;
			}
			break;
		case 1:
			if (posY[0] == StrikerLimitY[1][0] || posY[0] == StrikerLimitY[1][1])
				return false;
			else
			{
				x1 = 700 - 151.5;
				y1 = 180.5;
				x2 = 700 - 151.5;
				y2 = 700 - 180.5;
			}
			break;
		case 2:
			if (posX[0] == StrikerLimitX[2][0] || posX[0] == StrikerLimitX[2][1])
				return false;
			else
			{
				x1 = 180.5;
				y1 = 151.5;
				x2 = 700 - 180.5;
				y2 = 151.5;
			}
			break;
		case 3:
			if (posY[0] == StrikerLimitY[3][0] || posY[0] == StrikerLimitY[3][1])
				return false;
			else
			{
				x1 = 150.5;
				y1 = 180.5;
				x2 = 150.5;
				y2 = 700 - 180.5;
			}
			break;
		}
		if (Distance(x1, y1, posX[0], posY[0]) <= 41 || Distance(x2, y2, posX[0], posY[0]) <= 41)
			return true;
	}
	return false;
}

void MoveEndFunc()
{
	bool Turn_End = true;

	if (Queen_Pocketed_By != 0 && Game_Won_By == 0)
	{
		if (White_Left == 0)
			Game_Won_By = 2;
		else if (Black_Left == 0)
			Game_Won_By = 1;
	}

	switch (TurnCounter)
	{
	case 1:
	case 3:
		if (White_Pocketed && White_Left == 0)
		{
			Coin_Active[11] = true;
			posX[11] = 350;
			posY[11] = 350;
			White_Left++;
			for (int i = 2; i < 11; i++)
			{
				if (Coin_Active[i] == false)
				{
					Coin_Active[i] = true;
					posX[i] = 350;
					posY[i] = 350;
					Black_Left++;
					break;
				}
			}
		}
		if (Foul_BaseLine == true || Black_Left == 0)
		{
			Turn_End = true;
			for (int i = 2; i < 11; i++)
			{
				if (Coin_Active[i] == false)
				{
					Coin_Active[i] = true;
					posX[i] = 350;
					posY[i] = 350;
					Black_Left++;
					break;
				}
			}
		}
		else if ((Black_Pocketed || Queen_Pocketed) && (Black_Touch || Queen_Touch))
		{
			if (Queen_Pocketed_Prev_Turn)
				Queen_Pocketed_By = 2;
			Turn_End = false;
		}
		break;

	case 0:
	case 2:
		if (Black_Pocketed && Black_Left == 0)
		{
			Coin_Active[2] = true;
			posX[2] = 350;
			posY[2] = 350;
			Black_Left++;
			for (int i = 11; i < 20; i++)
			{
				if (Coin_Active[i] == false)
				{
					Coin_Active[i] = true;
					posX[i] = 350;
					posY[i] = 350;
					White_Left++;
					break;
				}
			}
		}
		if (Foul_BaseLine || White_Left == 0)
		{
			Turn_End = true;
			for (int i = 11; i < 20; i++)
			{
				if (Coin_Active[i] == false)
				{
					Coin_Active[i] = true;
					posX[i] = 350;
					posY[i] = 350;
					White_Left++;
					break;
				}
			}
		}
		else if ((White_Pocketed || Queen_Pocketed) && (White_Touch || Queen_Touch))
		{
			if (Queen_Pocketed_Prev_Turn)
			{
				Queen_Pocketed_By = 1;
			}
			Turn_End = false;
		}
		break;

	default:
		break;
	}

	if (Turn_End)
	{
		TurnCounter++;
		TurnCounter %= Players;
		if (Queen_Pocketed_Prev_Turn || Queen_Pocketed)
		{
			Coin_Active[1] = true;
			posX[1] = 350;
			posY[1] = 350;
		}
	}
	Queen_Pocketed_Prev_Turn = Queen_Pocketed;

	Collision_Check();
	Moving = false;
	posX[0] = StrikerInitialX[TurnCounter*(4 / Players)];
	posY[0] = StrikerInitialY[TurnCounter*(4 / Players)];
	FirstCoinCollision = 0;
	Black_Pocketed = false;
	White_Pocketed = false;
	Queen_Pocketed = false;
	Foul_BaseLine = false;
	Striker_CrossedBaseLine = false;
}

bool Foul_BaseLine_Check(int CoinNum)
{
	if (Striker_CrossedBaseLine == false)
	{
		switch (TurnCounter*(4 / Players))
		{
		case 0:
			if (posY[CoinNum] + 14 >= squareY[1][3] - 6)
				return true;
			break;
		case 1:
			if (posX[CoinNum] + 14 >= squareX[1][2] - 6)
				return true;
			break;
		case 2:
			if (posY[CoinNum] - 14 <= squareY[1][0] + 6)
				return true;
			break;
		case 3:
			if (posX[CoinNum] - 14 <= squareX[1][0] + 6)
				return true;
			break;
		default:
			break;
		}
	}
	return false;
}

void Striker_CrossBaseLine_Check()
{
	if (Striker_CrossedBaseLine == false)
	{
		switch (TurnCounter*(4 / Players))
		{
		case 0:
			if (posY[0] + 25 >= squareY[1][3])
				Striker_CrossedBaseLine = false;
			else
				Striker_CrossedBaseLine = true;
			break;
		case 1:
			if (posX[0] + 25 >= squareX[1][2])
				Striker_CrossedBaseLine = false;
			else
				Striker_CrossedBaseLine = true;
			break;
		case 2:
			if (posY[0] - 25 <= squareY[1][0])
				Striker_CrossedBaseLine = false;
			else
				Striker_CrossedBaseLine = true;
			break;
		case 3:
			if (posX[0] - 25 <= squareX[1][0])
				Striker_CrossedBaseLine = false;
			else
				Striker_CrossedBaseLine = true;
			break;
		default:
			break;
		}
	}
}