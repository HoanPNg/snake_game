#pragma once


#include <vector>
#include <string>
#include <fstream>

#include "System.h"
#include "Snake.h"

#define MAX_LEVEL 5
#define HEIGHT 20
#define WIDTH 100

using namespace std;

struct Level
{
	vector <string> level;
};

void InitLevel(string text, Level& list);
void DrawLevel(Level& list, Snake& snake);
int CheckLevel(Snake& snake);
void CheckCollision(Snake& snake, Level& list);

void DrawScreen(Level& screen);

int DrawMenu(Level& screen);