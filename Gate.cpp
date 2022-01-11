#include "Gate.h"
#include "system.h"
//MAP (98, 19)
int RandomCoorX()
{
	int x = 1;
	srand(time(0));
	int r = rand() % 2 + 1;

	if (r == 1)
		x = rand() % 3 + 2;
	else
		x = 95 - (rand() % 20);
	return x;
}

int RandomCoorY()
{
	int y = 1;
	srand(time(0));
	int r = rand() % 2 + 1;
	r = 2;
	if (r == 1)
		y = rand() % 10 + 5;
	else
		y = 15 - (rand() % 9 + 6);
	return y;
}

void InitGate(Food const& food, Gate*& pGate)
{
	(*pGate).x = RandomCoorX();
	(*pGate).y = RandomCoorY();

	if ((*pGate).x == food.x && (*pGate).y == food.y)
	{
		(*pGate).x = rand() % 20;
		(*pGate).y = rand() % 15;
	}
}

void DrawGate(Gate*& pGate, char st)
{
	color(102);
	if (pGate != NULL)
	{
		for (int i = 0; i <= 2; i++)
		{
			GotoXY((*pGate).x + i, (*pGate).y);
			cout << "*";
			GotoXY((*pGate).x + i, (*pGate).y + 1);
			cout << "*";
		}
		color(15);
		if (st == 'i')
		{
			GotoXY((*pGate).x + 1, (*pGate).y + 1);
			cout << " ";
		}
		else
		{
			GotoXY((*pGate).x + 1, (*pGate).y);
			cout << " ";
		}
	}
}

void CheckHitGate(Snake& snake, Gate* const pGate)
{
	if (snake.hy == (int64_t)(*pGate).y + 1 && snake.hx == (*pGate).x || snake.hy == (int64_t)(*pGate).y + 1 && snake.hx == (int64_t)(*pGate).x + 2)
		snake.alive = false;
	for (int i = 0; i <= 2; i++)
		if (snake.hy == (*pGate).y && snake.hx == (int64_t)(*pGate).x + i)
			snake.alive = false;
}

bool EnterGateSuccess(Snake const& snake, Gate* pGate)
{
	bool success = false;
	if (snake.hx == (int64_t)(*pGate).x + 1 && snake.hy == (int64_t)(*pGate).y + 1)
		success = true;
	return success;
}

void Delgate(Gate* pGate)
{
	for (int i = 0; i <= 2; i++)
	{
		GotoXY((*pGate).x + i, (*pGate).y);
		cout << " ";
		GotoXY((*pGate).x + i, (*pGate).y + 1);
		cout << " ";
	}
}