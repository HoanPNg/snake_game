#include "Level.h"



void InitLevel(string text, Level &list)
{
	ifstream file(text);

	if (!file.fail())
	{
		string line;

		while (getline(file, line))
			list.level.push_back(line);
	}



	char symbol_1 = 220;
	char symbol_2 = 219;
	char symbol_3 = 176;

	for (int i = 0; i < list.level.size(); i++)
	{
		for (int j = 0; j < list.level[i].size(); j++)
		{
			if (list.level[i][j] == '1')
				list.level[i][j] = symbol_1;
			else if (list.level[i][j] == '2')
		 		list.level[i][j] = symbol_2;
			else if (list.level[i][j] == '3')
				list.level[i][j] = symbol_3;
		}
	}

	file.close();

}

int CheckLevel(Snake& snake)
{
	//return the number of level based on snake's score 
	//0 - Level 1, 1 - Level 2 ....
	if (snake.score >= 0 && snake.score < 40)
		return 0;
	else if (snake.score >= 40 && snake.score < 80)
		return 1;
	else if (snake.score >= 80 && snake.score < 120)
		return 2;
	else if (snake.score >= 120 && snake.score < 160)
		return 3;
	else
		return 4;
}

void DrawLevel(Level& list, Snake& snake)
{
	int level = CheckLevel(snake);
	int score[5] = {0,40,80,120,160};
	static int counter = 0;
	char a;



	if (!snake.alive)
		counter = 0;

	if (snake.score % 40 == 0 && snake.score != score[counter])
		counter++;

	int color1 = 241 + CheckLevel(snake);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color1);
	for (int i = level * HEIGHT; i < level * HEIGHT + HEIGHT; i++)
	{
		//
		GotoXY(0, i - level * HEIGHT);
		printf("%s", list.level[i].c_str());

	}

	/**/
	/*for (int i = level * HEIGHT; i < level * HEIGHT + HEIGHT; i++)
	{
		for (int j = 0; j < list.level[i].size(); j++)
		{
			
			
			cout << list.level[i][j];
		}
	}*/

	color(15);
}

void CheckCollision(Snake& snake, Level& list)
{
	char a = 219;
	char b = 220;

	//if snake's head coordinate is the same coordinate with character 219 or 220 then collision happens
	if (list.level[snake.hy][snake.hx] == a || list.level[snake.hy][snake.hx] == b)
	{
		snake.alive = false; //die :<
	}
		
}


void DrawScreen(Level& screen)
{
	for (int i = 0; i < HEIGHT; i++)
	{
		GotoXY(0, i);                          //always draw from line 0-19 on screen
		printf("%s", screen.level[i].c_str()); //faster than cout
	}
	cout << endl;
}

int DrawMenu(Level& screen)
{
	int set[] = { 240,240,240,240 };
	int counter = 1;
	char key;

	//the same at drawscreen()
	for (int i = 0; i < HEIGHT; i++)
	{
		GotoXY(0, i);
		printf("%s", screen.level[i].c_str());
	}
	
	color(240);
	//convert to text ;;-;;
	GotoXY(20, 5);  cout << "  .-')        .-') _    ('-.    .-. .-')     ('-.   ";
	GotoXY(20, 6);  cout << " ( OO ).     ( OO ) )  ( OO ).-. \\  ( OO )  _(  OO)  ";
	GotoXY(20, 7);  cout << "(_)--- \\_),--./ ,--,'  / . --. /,--. ,--. (,------. ";
	GotoXY(20, 8);	cout << "/     _ ||   \\ |  |\\   | \\-.   \\|  .'   /  |  .---' ";
	GotoXY(20, 9);  cout << "\\  :` `. |    \\|  | ).-'-'  |  ||      /,  |  |     ";
	GotoXY(20, 10);	cout << " '..`''.)|  .     |/  \\| |_.'  ||     ' _)(|  '--.  ";
	GotoXY(20, 11); cout << ".-._)   \\|  |\\    |    |  .-.  ||  .   \\   |  .--'  ";
	GotoXY(20, 12); cout << "\\       /|  | \\   |    |  | |  ||  |\\   \\  |  `---. ";
	GotoXY(20, 13); cout << " `-----' `--'  `--'    `--' `--'`--' '--'  `------' ";


	for (int i = 0; ;)
	{
		if (counter == 1)
			set[0] = 244;
		if (counter == 2)
			set[1] = 244;
		if (counter == 3)
			set[2] = 244;
		if (counter == 4)
			set[3] = 244;



		GotoXY(43, 15);
		color(set[0]);
		cout << "Start Game";

		GotoXY(43, 16);
		color(set[1]);
		cout << "Load Game";

		GotoXY(43, 17);
		color(set[2]);
		cout << "High Score";

		GotoXY(43, 18);
		color(set[3]);
		cout << "Quit";


		key = _getch();

		if (key == 'w' && (counter >= 2 && counter <= 4))
			counter -= 1;
		if (key == 's' && (counter >= 1 && counter <= 3))
			counter += 1;
		if (key == '\r') //press enter
		{
			system("cls");
			return counter;
		}
		set[0] = 240;
		set[1] = 240;
		set[2] = 240;
		set[3] = 240;

	}
	
	return 0;
}