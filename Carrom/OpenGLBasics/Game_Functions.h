void draw_Circle(float , float , float , int );
void DisplayCoins();
void NewGame(float angle);		/* STARTS A NEW GAME */
void SetFlower(float angle);	/* SETS THE COINS IN THEIR STARTING ORDER*/
void DisplayLayout();		/*DISPLAYS CARROM BOARD*/
void movement();		/* HANDLES THE MOVEMENT OF COINS */
void Shoot_Striker();
void Collision_Check();/*COMPLETE FUNCTION WHICH CHECKS FOR ALL POSSIBLE COLLISIONS AND OTHER RELATED STUFF (e.g. PocketCheck, OutofBounds check etc)*/
void OutOfBounds_Check(int coin_number, float radius);	/*CHECKS IF THE COIN IS GOING OUT OF BOUNDS*/
void Perform_Collision(int coin1, int coin2, float Distance, float CollideDistance); /*PERFORMS THE OPERATIONS FOR MOMENTUM TRANSFER AFTER COLLISION*/
void Coin_InPath(int *closest, float *x, float *y);	/* SEARCHES FOR THE CLOSEST COIN IN PATH OF STRIKER*/
float Distance(float x1, float y1, float x2, float y2);	/*Calculates distance b/w two pairs of (x,y) coordinates*/
float Distance(int coin1, int coin2);	/*calculates distance between the centres of two given coins*/
void StrikerPassiveFunc();			/*Perform miscellaneous striker functions when not in move*/
void renderBitmapString(float x, float y, char *string);
void DisplayMain();/*Main Display function that calls "DisplayCoins" "DisplayLayout" Functions and performs other tasks*/
void DisplayMenu();					/*Display the starting menu*/
void DisplaySubMenu(int x);			/*Display the 2 Submenus*/
void DisplayPanel();				/*Display the right panel during the game*/
void DisplayWin();					/*If game won then display it*/

int Direction_Check(int turn);			/*Checks if the striker is being shot backwards or forwards*/
bool Pocket_Check(int coin_number);		/*Check if a coin is pocketed or not*/
bool Arc_Foul();		/*Check for the Arc foul*/
void MoveEndFunc();			/* Perform different tasks when the move ends (Also checks if the turn ends or not)*/
bool Foul_BaseLine_Check(int CoinNum);	/*Check for base line foul*/
void Striker_CrossBaseLine_Check();		/*Check whether the striker crossed baseline or not*/