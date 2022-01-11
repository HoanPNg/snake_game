#pragma once
//contains functions to deal with graphic on console <or functions in the instruction>
#define MAX_LENGTH 40
const char symbolArr[MAX_LENGTH] = {'1','9','1','2','0','4','9','2',
									'1','9','1','2','0','4','9','4', 
									'1','9','1','2','0','4','9','6', 
									'1','9','1','2','0','4','9','8', 
									'1','9','1','2','0','5','1','4', };

void GotoXY(int x, int y);
void FixConsoleWindow();
void color(int color);
void ShowCur(bool CursorVisibility);
void BackColor();
