#pragma warning (disable: 4996)
#include "SaveLoad.h"

void SaveGame(char* filename, Snake snake, int foodx, int foody)
{

	ofstream saveFile;

	saveFile.open(filename, ios_base::out);



	saveFile << snake.speedx << " " << snake.speedy << " ";
	saveFile << snake.dir << " " << snake.score << " ";
	saveFile << snake.alive << " ";
	saveFile << snake.size << " " << snake.hx << " " << snake.hy << " ";

	for (int i = 0; i < snake.size; i++)
	{
		saveFile << snake.seg[i].symbol << " ";
		saveFile << snake.seg[i].x << " " << snake.seg[i].y << " ";
	}

	saveFile << foodx << " " << foody;

	saveFile.close();

}



void LoadGame(char* filename, Snake &snake, Food &food)
{
	ifstream loadFile;
	loadFile.open(filename, ios_base::in);


	snake.head = 254;
	food.symbol = 167;
	food.eaten = false;

	while (!loadFile.eof())
	{

		loadFile >> snake.speedx >> snake.speedy >> snake.dir >> snake.score;
		loadFile >> snake.alive;
		loadFile >> snake.size >> snake.hx >> snake.hy;

		for (int i = 0; i < snake.size; i++)
		{
			loadFile >> snake.seg[i].symbol;
			loadFile >> snake.seg[i].x >> snake.seg[i].y;
		}

		loadFile >> food.x >> food.y;



	}
	loadFile.close();
}
void SaveListName(ListName listname[])
{
	ofstream saveName;

	saveName.open("Listname.txt", ios_base::out);

	for (int i = 0; i < 20; i++)
	{
		saveName << listname[i].name << " ";
	}

	saveName.close();

}
bool EmptyCheck()
{

	int size = 0;;
	ifstream loadName;
	loadName.open("Listname.txt", ios_base::in);
	if (loadName.is_open())
	{
		loadName.seekg(0, ios::end);
		size = loadName.tellg();
		loadName.close();
	}
	if (size == 0)
		return 1;
	else
		return 0;
}

void initListname(ListName listname[])
{
	if (EmptyCheck())
	{
		for (int i = 0;i < 20;i++)
		{
			strcpy(listname[i].name, "Name");
		}
		SaveListName(listname);
	}
	else
	{

		ifstream loadName;
		loadName.open("Listname.txt", ios_base::in);

		for (int i = 0;i < 20;)
		{
			
				loadName >> listname[i].name;
				i++;


		}
	}
}
void ShowListname(ListName listname[])
{
	ifstream loadName;
	loadName.open("Listname.txt", ios_base::in);
	for (int i = 0; i < 20; i++)
		loadName >> listname[i].name;
	loadName.close();
	color(12);
	GotoXY(35, 2);

	//
	int color1 = 241;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 241);

	cout << "PLAYERS LIST";


	for (int i = 0; i < 20; i++)
	{
		if (i % 2 == 0)
		{
			GotoXY(5, 4 + i / 2);
			cout << " PLAYER: " << "\t" << listname[i].name;
		}
		else
		{
			GotoXY(50, 4 + i / 2);
			cout << " PLAYER: " << "\t" << listname[i].name;
		}
	}
	color(15);

}
void CheckDuplicateName(ListName listname[], char* name)
{
	for (int i = 0; i < 20;)
	{
		if (strcmp(listname[i].name, name) == 0)
		{
			break;
		}
		else if (strcmp(listname[i].name, "Name") == 0)
		{
			strcpy(listname[i].name, name);
			break;
		}
		else
		{
			i++;
		}


	}
	SaveListName(listname);
}