#pragma once
#pragma warning (disable: 4996)
#include <fstream>
#include <string>

#include "Snake.h"
#include "Food.h"
using namespace std;

struct Highscore
{
	int score;
	char name[30];
};
void SaveHighScore(Highscore highscore[]);
void InitScore(Highscore highscore[]);
void CheckHighScore(Highscore highscore[], int score);
void ShowHighScore(Highscore highscore[]);