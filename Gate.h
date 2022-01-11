#pragma once

#pragma once
#include "System.h"
#include "Snake.h"
#include "Food.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

struct Gate
{
	int x; //should we change it to short, less byte
	int y;
};

int RandomCoorX();
int RandomCoorY();
void InitGate(Food const& food, Gate*& pGate);
void DrawGate(Gate*& pGate, char st);
void CheckHitGate(Snake& snake, Gate* const pGate);
bool EnterGateSuccess(Snake const& snake, Gate* pGate);
void Delgate(Gate* pGate);
