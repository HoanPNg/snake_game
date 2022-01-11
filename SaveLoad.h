#pragma once
#include <fstream>
#include <string>

#include "Snake.h"
#include "Food.h"

using namespace std;

void SaveGame(char* filename, Snake snake, int foodx, int foody);
void LoadGame(char* filename, Snake &snake, Food &food);

void SaveListName(ListName listname[]);
bool EmptyCheck();
void initListname(ListName listname[]);
void ShowListname(ListName listname[]);
void CheckDuplicateName(ListName listname[], char* name);