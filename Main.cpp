
#pragma comment(lib, "winmm.lib")
#include <cstdio>
#include <stdio.h>
#include "Snake.h"
#include "System.h"
#include "Food.h"
#include "Level.h"
#include "windows.h"
#include "Gate.h"
#include "SaveLoad.h"

#include "HighScore.h"

int nScreenWidth = 120;
int nScreenHeight = 30;
using namespace std;


int main()
{

	FixConsoleWindow();
	ShowCur(0);
	BackColor();
	Snake snake;
	Food food;
	Level myLevelList;
	Level ending;
	Level begin;
	Level levelUp;

	Level blank;
	Gate* pGate = nullptr;
	Level last;	int foodx, foody;
	Highscore highscore[5];
	ListName listname[20];
	
Reset:
	BackColor();
	InitLevel("LevelUp.txt", levelUp);
	system("cls");
	bool gateOn = 0;
	short count = 0;
	char st;
	
	char name[50];
	char a;

	InitScore(highscore);
	initListname(listname);
	InitSnake(snake);
	InitLevel("MyList.txt", myLevelList);
	InitLevel("Ending.txt", ending);
	InitLevel("Starting.txt", begin);
	InitLevel("Starting.txt", blank);
	InitLevel("Won.txt", last);
	
	
	
	int choice = DrawMenu(begin);
	

		switch (choice)
		{



		case 1:

			food = InitFood(snake, myLevelList);
			foodx = food.x;
			foody = food.y;

			

			while (1)
			{
			Run:
				//system("COLOR F0");
				if (!gateOn)
				{
					color(9 + count);
					DrawLevel(myLevelList, snake);
					color(15);
				}
				
				

				short oldx = snake.seg[snake.size - 1].x;
				short oldy = snake.seg[snake.size - 1].y;

				Move(snake, foodx, foody, listname);

				CheckCollision(snake, myLevelList);
				CheckHitSelf(snake);
				
				if (!snake.alive)
				{
					CheckHighScore(highscore, snake.score);
					//color(9 + count);
					int color1 = 241 + CheckLevel(snake);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color1);
					DrawScreen(ending);
					color(15);
					a = _getch();

					if (a == 'y' || a == 'Y')
						goto Reset;
					else
						return 0;

				}
				

				if (snake.score == 200)
				{
					CheckHighScore(highscore, snake.score);
					//color(9);
					int color1 = 241 + CheckLevel(snake);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color1);
					DrawScreen(last);
					color(15);

					a = _getch();

					if (a == 'y' || a == 'Y')
						goto Reset;
					else
						return 0;
				}

				if (isEaten(food, snake))
				{
					food = InitFood(snake, myLevelList);
					foodx = food.x;
					foody = food.y;
					PlaySound(TEXT("eat.wav"), NULL, SND_ASYNC);

					if (snake.score == 40 || snake.score == 80 || snake.score == 120 || snake.score == 160)
					{
						//pGate = new Gate;
						pGate = (Gate*)malloc(sizeof(Gate));
						if (pGate != NULL)
						{
							InitGate(food, pGate);
							st = 'i';
							gateOn = 1;
							PlaySound(TEXT("lvup.wav"), NULL, SND_ASYNC);
							count++;
						}
					}

				}

				if (gateOn)
				{
					int color1 = 241 + CheckLevel(snake);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color1);
					DrawScreen(levelUp);
					color(15);

					DrawGate(pGate, st);
					CheckHitGate(snake, pGate);


					if (EnterGateSuccess(snake, pGate))
					{
						Delgate(pGate);


						InitGate(food, pGate);
						st = 'o';

						DrawGate(pGate, st);
						snake.hx = (int64_t)(*pGate).x + 1;
						snake.hy = (*pGate).y;
						LoadSegment(snake);
					}

					if (snake.seg[snake.size - 1].x == (*pGate).x + 1 && snake.seg[snake.size - 1].y == (*pGate).y)
					{
						Delgate(pGate);	
						std::free(pGate); 
						pGate = NULL;
						gateOn = 0;
						

					}
				}
				else
				{
					int color1 = 241 + CheckLevel(snake);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color1);
					DrawFood(food);
					color(15);
				}
					

				int color1 = 241 + CheckLevel(snake);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color1);
				//color(9 + count);
				GotoXY(111, 6);
				std::cout << "<" << snake.hx << "," << snake.hy << ">";
				GotoXY(111, 4);
				std::cout << snake.score;
				color(15);



				DrawSnake(snake);
				//delete snake tail	
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color1);
				GotoXY(oldx, oldy);
				std::cout << " ";
				color(15);

				if (snake.alive == false)
				{
					PlaySound(TEXT("hitwall.wav"), NULL, SND_ASYNC);
					color(13);
					DrawSnake(snake);
					Sleep(300);
				}
				//the snake seems to be faster when level is up
				Sleep(90 - CheckLevel(snake) * 5);
			}

			std::free(pGate);
			std::free(snake.seg);
			break;
		case 2:
			
			
			DrawScreen(blank);
			//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 241 + CheckLevel(snake));
			ShowListname(listname);
			
			
			GotoXY(20, 16);

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 241);
			std::cout << "Enter your loadfile's name (ending with .txt ^.^) :";

			GotoXY(20, 17);
			std::cin >> name;
			color(15);
			food.symbol = 167;
			food = Food{ 6, 6, 0, food.symbol };
			count = CheckLevel(snake) +1;

			LoadGame(name, snake, food);
			

			foodx = food.x;
			foody = food.y; 

			goto Run;
			
			break;
		case 3: 
			
			
			DrawScreen(blank);
		
			color(15);
			ShowHighScore(highscore);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 241 + CheckLevel(snake));
			GotoXY(37, 15);
			std::cout << "PRESS Y TO RETURN TO MENU";
			color(15);
			a = _getch();

			if (a == 'y' || a == 'Y')
				goto Reset;
			else
				return 0;
			
			break;
		case 4:
			break;
		}
	return 0;
}
