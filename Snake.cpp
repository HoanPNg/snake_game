#include "Snake.h"
#include "SaveLoad.h"



void DrawSnake(Snake& snake)
{
	char dum = 205;


	//print all the segment then print the head according to its coordinate
	//color(9);
	int color1 = 241 + CheckLevel(snake);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color1);
	for (int i = 0; i < snake.size; i++)
	{
		if (snake.seg[i].symbol == dum)
			snake.seg[i].symbol = symbolArr[i]; 

		GotoXY(snake.seg[i].x, snake.seg[i].y);
		cout << snake.seg[i].symbol;
	}

	GotoXY(snake.hx, snake.hy);
	cout << snake.head;
	color(15);
}

//simple function to set coordinate for each segment
void SetSegmentXY(Segment& seg, int x, int y)
{
	seg.x = x;
	seg.y = y;
}

void InitSnake(Snake& snake)
{
	snake.score = 0;
	snake.speedx = 1;
	snake.speedy = 1;
	snake.head = 254; //254 //print the square

	snake.dir = RIGHT;
	snake.alive = true;
	snake.size = 4;

	snake.hx = 12;
	snake.hy = 5;

	snake.seg = NULL;
	//our beloved malloc is finally used =))))
	snake.seg = (Segment*)malloc(snake.size * sizeof(Segment));

	if (snake.seg)
	{
		snake.seg[0].symbol = '1';
		snake.seg[1].symbol = '9';
		snake.seg[2].symbol = '1';
		snake.seg[3].symbol = '2';
	}

	//set the segment coordinate toward the left size of the head
	for (int i = 0; i < snake.size; i++)
	{
		if (snake.seg)
		{
			snake.seg[i].x = snake.hx + i + 1;
			snake.seg[i].y = snake.hy;
		}
	}
}

void MoveRight(Snake& snake)
{
	//move all the segment first then move the head
	LoadSegment(snake);
	snake.hx += snake.speedx;

}

void MoveUp(Snake& snake)
{
	//move all the segment first then move the head
	LoadSegment(snake);
	snake.hy -= snake.speedy;

}

void MoveDown(Snake& snake)
{
	//move all the segment first then move the head
	LoadSegment(snake);
	snake.hy += snake.speedy;

}

void MoveLeft(Snake& snake)
{
	//move all the segment first then move the head
	LoadSegment(snake);
	snake.hx -= snake.speedx;

}

void LoadSegment(Snake& snake)
{
	int x, y;

	//the i segment will gains the coordinate of the i - 1 segment (the segment before it)
	for (int index = snake.size - 1; index > 0; index--)
	{
		x = snake.seg[index - 1].x;
		y = snake.seg[index - 1].y;

		SetSegmentXY(snake.seg[index], x, y);

	}

	//the [0] segment will gain head's coordinate
	SetSegmentXY(snake.seg[0], snake.hx, snake.hy);
}

void Move(Snake& snake, int foodx, int foody, ListName listname[])
{
	//initialize key
	static char key = 'a';
	static char lock = 'd';
	static char preKey = 'a';

	if (_kbhit())  //if we hit the keyboard, maybe we can change our direction
	{
		//save the key 
		preKey = key;
		//gains new value from the keyboard
		key = _getch();
		char filename[50];
		ofstream saveFile;
		int color1 = 241 + CheckLevel(snake);
		//check if the new value is different from lock <if yes then continue>
		if (key != lock)
		{
			switch (key)
			{
			case 'a':
				snake.dir = LEFT;
				lock = 'd';
				MoveLeft(snake);
				break;
			case 's':
				lock = 'w';
				snake.dir = DOWN;
				MoveDown(snake);
				break;
			case 'd':
				lock = 'a';
				snake.dir = RIGHT;
				MoveRight(snake);
				break;
			case 'w':
				lock = 's';
				snake.dir = UP;
				MoveUp(snake);
				break;
			case 'z':
				
				////////////////////////////////
				
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color1);
				system("cls");
				GotoXY(30, 6);
				cout << "===================================================";
			
				GotoXY(32, 8);
				cout << "Enter your savefile's name (ending with .txt ^_^): " ;

				GotoXY(30, 11);
				cout << "===================================================";
				
				GotoXY(32, 9);
				cin >> filename;
				CheckDuplicateName(listname, filename);
				SaveGame(filename, snake, foodx, foody);
				color(15);
				

				
				return;
				break;
				///////////////////////////////////
			default: //if user hit some random keys then dont change snake's direction
				key = preKey;
			}
		}
		else //if the new value gained from the keyboard is similar to lock then just give it the old value <move in the same direction>
			key = preKey;

	}
	else //if we dont press keyboard then the snake still moves but dont change it direction
	{
		switch (key)
		{
		case 'a':
			snake.dir = LEFT;
			lock = 'd';
			MoveLeft(snake);
			break;
		case 's':
			lock = 'w';
			snake.dir = DOWN;
			MoveDown(snake);
			break;
		case 'd':
			lock = 'a';
			snake.dir = RIGHT;
			MoveRight(snake);
			break;
		case 'w':
			lock = 's';
			snake.dir = UP;
			MoveUp(snake);
			break;

		}
	}
}

void AddSegment(Snake& snake)
{
	snake.size++;

	//int size = snake.size;

	//use realloc to expand our segments then give it a new symbol at the back
	Segment* newSegs = (Segment*)realloc(snake.seg, snake.size * sizeof(Segment));

	if (newSegs)
		newSegs[snake.size - 1].symbol = symbolArr[snake.size - 1];

	newSegs[snake.size - 1].x = newSegs[snake.size - 2].x;
	newSegs[snake.size - 1].y = newSegs[snake.size - 2].y;

	snake.seg = newSegs;


}

void CheckHitSelf(Snake &snake)
{
	bool check = 0;
	if(snake.size > 3)
		for(int i=3; i<snake.size; i++)
			if(snake.seg[i].x == snake.hx && snake.seg[i].y == snake.hy)
				snake.alive = false;

}