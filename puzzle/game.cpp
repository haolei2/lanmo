#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string>
IMAGE img, blank,img1;
int step = 0,preStep = 0;
int array2D[4][4] = { 0 };
int array1D[16] = {0};
std::string tips;
int gameOver[4][4] = {  {0,1,2,3},
						{4,5,6,7},
						{8,9,10,11},
						{12,13,14,15},
}; 
int t[4][4] = { {0,1,2,3},
						{4,5,6,7},
						{8,9,10,11},
						{12,13,15,14},
};



void drawMenu()
{
	initgraph(600, 400);
	setbkcolor(WHITE);
	cleardevice();
	setfillcolor(BLUE);
	settextstyle(30,0,"宋体");
	setbkmode(TRANSPARENT);

	fillrectangle(200,200,400,250);
	fillrectangle(200, 200+80, 400, 250+80);

	outtextxy(200+40,200+13,"开始游戏");
	outtextxy(200 + 40, 280 + 13, "退出游戏");
	MOUSEMSG m;
	while (1)
	{
		m = GetMouseMsg();
		if (m.x >= 200 && m.x <= 400 && m.y >= 200 && m.y <= 250)
		{
			setlinecolor(RED);
			rectangle(190, 190, 410, 260);
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				break;
			}
		}
		else if (m.x >= 200 && m.x <= 400 && m.y >= 280 && m.y <= 330)
		{
			setlinecolor(RED);
			rectangle(190, 270, 410, 340);
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				exit(0);
			}
		}
		else
		{
			setlinecolor(WHITE);
			rectangle(190, 190, 410, 260);
			rectangle(190, 270, 410, 340);
		}
	}
	closegraph();
}

void loadResource()
{
	srand((unsigned int) time(NULL));
	int length = 15;
	int j,pos = 0;
	for (int i = 0; i < 16; i++)
		array1D[i] = i;

	for (int i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (i == 3 && j == 3)
			{
				array2D[i][j] = 15;
				break;
			}
			pos = rand() % length;
			array2D[i][j] = array1D[pos];
			for (int k = pos; k < length-1; k++)
			{
				array1D[k] = array1D[k+1];
			}
			length--;
		}
		if (i == 3 && j == 3)
		{
			array2D[i][j] = 15;
			break;
		}
	}
	loadimage(&img1, "jinjun.jpg", 150, 100);
	putimage(600, 300, &img1);

	loadimage(&img,"jinjun.jpg",600,400);
	loadimage(&blank, "timg.jpg", 150, 100);
	step = preStep = 0;
	tips = "Step  " + std::to_string(step);
	//TCHAR* tip = char2TCAHR(tips.c_str());
	outtextxy(630, 150, tips.c_str());
}

void drawgraph()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int x = i * 150;
			int y = j * 100;
			switch (array2D[i][j])
			{
			case 0:
			case 1:
			case 2:
			case 3:
				putimage(x,y, 150,100,&img, array2D[i][j]*150,0);
				break;
			case 4:
			case 5:
			case 6:
			case 7:
				putimage(x, y, 150, 100, &img, (array2D[i][j]-4) * 150, 100);
				break;
			case 8:
			case 9:
			case 10:
			case 11:
				putimage(x, y, 150, 100, &img, (array2D[i][j] - 8) * 150, 200);
				break;
			case 12:
			case 13:
			case 14:
				putimage(x, y, 150, 100, &img, (array2D[i][j] - 12) * 150, 300);
				break;
			case 15:
				putimage(x,y,&blank);
				break;
			default:
				break;
			}

		}
	}
	if (preStep != step)
	{
		clearrectangle(630, 150, 750, 300);
		tips = "Step  " + std::to_string(step);
		//TCHAR* tip = char2TCAHR(tips.c_str());
		outtextxy(630, 150, tips.c_str());
		preStep = step;
	}
}

bool gameover()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (array2D[i][j] != gameOver[i][j])
				return false;
		}
	}

	return true;
}

void playGame()
{
	MOUSEMSG m;
	int i, j;
	int j_mourse, i_mourse;
	while (1)
	{
		drawgraph();
		
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				if (array2D[i][j] == 15)
					break;
			}
			if (j<4&&array2D[i][j] == 15)
				break; 
		}

		//printf("%d %d\n", i, j);
		if (MouseHit())
		{
			m = GetMouseMsg();
			switch (m.uMsg)
			{
			case WM_LBUTTONDOWN:
				i_mourse = m.x / 150;
				j_mourse = m.y / 100;
				if (i_mourse >= 0 && i_mourse <= 3 && j_mourse >= 0 && j_mourse <= 3)
				{
					if (i_mourse == i + 1 && j_mourse == j)
					{
						array2D[i][j] = array2D[i_mourse][j_mourse];
						array2D[i_mourse][j_mourse] = 15;
						step++;
					}
					if (i_mourse == i - 1 && j_mourse == j)
					{
						array2D[i][j] = array2D[i_mourse][j_mourse];
						array2D[i_mourse][j_mourse] = 15;
						step++;
					}
					if (i_mourse == i && j_mourse == j - 1)
					{
						array2D[i][j] = array2D[i_mourse][j_mourse];
						array2D[i_mourse][j_mourse] = 15;
						step++;
					}
					if (i_mourse == i && j_mourse == j + 1)
					{
						array2D[i][j] = array2D[i_mourse][j_mourse];
						array2D[i_mourse][j_mourse] = 15;
						step++;
					}
				}
				break;
			}
		}
		if (_kbhit())
		{
			char choice = _getch();
			switch (choice)
			{
			case 'a':
			case 'A':
			case 75:
				if (i - 1 >= 0 && i - 1 <= 3)
				{
					array2D[i][j] = array2D[i - 1][j];
					array2D[i - 1][j] = 15;
					step++;
				}
				break;
			case 'd':
			case 'D':
			case 77:
				if (i + 1 >= 0 && i + 1 <= 3)
				{
					array2D[i][j] = array2D[i + 1][j];
					array2D[i + 1][j] = 15;
					step++;
				}
				break;
			case 'w':
			case 'W':
			case 72:
				if (j - 1 >= 0 && j - 1 <= 3)
				{
					array2D[i][j] = array2D[i][j - 1];
					array2D[i][j - 1] = 15;
					step++;
				}
				break;
			case 's':
			case 'S':
			case 80:
				if (j + 1 >= 0 && j + 1 <= 3)
				{
					array2D[i][j] = array2D[i][j + 1];
					array2D[i][j + 1] = 15;
					step++;
				}
				break;
			default:
				break;
			}
		}
		if (gameover())
			break;
	}
}

void test()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			array2D[i][j] = t[i][j];
		}
	}
}
void drawGameOver()
{
	initgraph(600, 400);
	setbkcolor(WHITE);
	cleardevice();
	setfillcolor(BLUE);
	settextstyle(30, 0, "宋体");
	setbkmode(TRANSPARENT);

	fillrectangle(150, 200, 450, 250);
	//fillrectangle(200, 200 + 80, 400, 250 + 80);

	outtextxy(200 + 40, 200 + 13, "金俊好厉害");
	//outtextxy(200 + 40, 280 + 13, "退出游戏");
	Sleep(1000);
	closegraph();
}

int main()
{
	while (1)
	{
		drawMenu();
		initgraph(750, 400);
		setbkcolor(CYAN);
		cleardevice();
		//setfillcolor(RED);
		settextstyle(30, 0, "宋体");
		setbkmode(TRANSPARENT);

		//fillrectangle(630, 150, 730, 200);
		loadResource();
		//drawgraph();
		//test();
		playGame();
		closegraph();
		drawGameOver();
	}
	return 0;
}
