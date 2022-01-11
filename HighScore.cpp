#include "HighScore.h"
#pragma warning (disable: 6001)

void SaveHighScore(Highscore highscore[])
{
	ofstream saveScore;

	saveScore.open("Highscore.txt", ios_base::out);

	for (int i = 0; i < 5; i++)
	{
		saveScore << highscore[i].name << " " << highscore[i].score << " ";
	}

	saveScore.close();

}
//Kiem tra neu file rong
bool isEmpty()
{

	int size;
	ifstream loadScore;
	loadScore.open("Highscore.txt", ios_base::in);
	if (loadScore.is_open())
	{
		loadScore.seekg(0, ios::end);
		size = loadScore.tellg();
		loadScore.close();
	}
	if (size == 0)
		return 1;
	else
		return 0;
}

//Neu file rong, khoi tao 5 gia tri co ten la 'PLAYER' va so diem la 0

void InitScore(Highscore highscore[])
{

	if (isEmpty())
	{
		for (int i = 0; i < 5; i++)
		{
			strcpy(highscore[i].name, "PLAYER");
			highscore[i].score = 0;
		}
		SaveHighScore(highscore);
	}
	else
	{

		int count = 0;
		ifstream loadScore;
		loadScore.open("Highscore.txt", ios_base::in);

		for (int i = 0; i < 5;)
		{
			
			count++;

			if (count % 2 == 1)
			{
				loadScore >> highscore[i].name;
			}
			else
			{
				loadScore >> highscore[i].score;
				i++;
			}
			

		}
	}
}
void ShowHighScore(Highscore highscore[])
{
	ifstream loadScore;
	loadScore.open("Highscore.txt", ios_base::in);
	for (int i = 0; i < 5; i++)
		loadScore >> highscore[i].name >> highscore[i].score;
	loadScore.close();
	color(12);
	int color1 = 241;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color1);
	
	GotoXY(20, 4);
	cout << "HIGH SCORE";

	for (int i = 0; i < 5; i++)
	{
		
		GotoXY(20, 6 + i);
		cout << i + 1 << ".  ";
		cout << highscore[i].name << "\t\t" << highscore[i].score << endl;
		
	}
	color(15);
}

void CheckHighScore(Highscore highscore[], int score)
{
	char name[50];
	int color1 = 241;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color1);
	for (int i = 0; i < 5; i++)
	{
		if (score > highscore[i].score)
		{
			if (i == 0)
			{

				GotoXY(65, 21);
				cout << "BEST SCORE!!" << endl;
			}
			else
			{
				GotoXY(65, 21);
				cout << " HIGH SCORE!" << endl;
			}
			GotoXY(65, 24);
			cout << " Enter player's name: ";
			cin >> name;



			for (int j = 4; j < i; j--)
			{
				strcpy(highscore[j].name, highscore[j - 1].name);
				highscore[j].score = highscore[j - 1].score;
			}
			strcpy(highscore[i].name, name);
			highscore[i].score = score;
			break;
		}

	}
	color(15);
	SaveHighScore(highscore);
}





