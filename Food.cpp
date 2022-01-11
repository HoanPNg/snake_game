#include "Food.h"

int RandomX()
{
	//return random integer
	srand(time(0));
	int a = rand() % (WIDTH-7) + 6;

	return a;
}

int RandomY()
{
	//return random integer
	srand(time(0));
	int a = rand() % (HEIGHT-4) + 4;

	return a;
}

Food InitFood(Snake &snake,Level &list)
{
	Food food;
	int x, y;

	//this is going to be upgraded
	food.symbol = 167;

	//do this until we got a valid coordinate for our food
	do
	{
		//take 2 ints
		x = RandomX();
		y = RandomY();

		//check if it is valid ?
		if (isCoorValid(x, y, snake,list))
		{
			food.x = x;
			food.y = y;
		}
	} while (!isCoorValid(x, y, snake,list));

	return food;
}




void DrawFood(Food const& food)
{
	//move the cursor to food.x and food.y then print it
	GotoXY(food.x, food.y);
	cout << food.symbol;
}

bool isCoorValid(int x, int y, Snake &snake, Level &list)
{
	bool valid = true;
	char a = 219;
	char b = 220;

	//check if it has same coordinate with snake's head <if not then continue to check each segment>
	if (x != snake.hx && y != snake.hy)
	{
		//loop through the segments
		for (int i = 0; i < snake.size; i++)
		{
			//if x and y have the same coordinate with any segment then bye bye :<
			if (x == snake.seg[i].x && y == snake.seg[i].y)
				valid = false;
			else if (list.level[y][x] == a || list.level[y][x] == b)
				valid = false;
		}
			
	}
	else //if x and coincides with head's coor then bye bye :<
		valid = false;

	return valid;
}

bool isEaten(Food &food, Snake &snake)
{
	bool eaten = false;

	//if snake's head touch the food
	if (snake.hx == food.x && snake.hy == food.y)
	{
		eaten = true;
		snake.score += 10;
		AddSegment(snake); //increase size
	}
		
	return eaten;
}
