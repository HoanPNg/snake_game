#pragma once

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <fstream>
#include <string>

#include "System.h"

using namespace std;

#define SCREEN_HEIGHT 400 //can be changed
#define SCREEN_WIDTH 600 // can be changed

enum Direction { UP, DOWN, LEFT, RIGHT };

struct Segment
{
	char symbol;

	int x;
	int y;
};

struct Snake
{
	Segment* seg;
	char head;
	double speedx;
	double speedy;
	int dir;
	int score;
	bool alive;
	int size;
	double hx;
	double hy;
};
struct ListName { char name[50]; };

//Functions are taken from the instruction
void GotoXY(int x, int y); 
void FixConsoleWindow();

//WEEK 1
void InitSnake(Snake& snake); //initialize the snake 
void DrawSnake(Snake& snake); //draw full snake on the screen

void LoadSegment(Snake& snake); //change the segment's coordinate after moving
void AddSegment(Snake& snake);  //add more symbol into the snake's segment when eating food

void Move(Snake& snake, int foodx, int foody, ListName listname[]);   //combination with 4 functions below <read more in snake.cpp>
void MoveUp(Snake& snake);   //is used in move()
void MoveDown(Snake& snake); //is used in move()
void MoveLeft(Snake& snake); //is used in move()
void MoveRight(Snake& snake);//is used in move()

void SetSegmentXY(Segment& seg, int x, int y); //make it easier to move the segments <is used in LoadSegment>
void CheckHitSelf(Snake& snake);


 
