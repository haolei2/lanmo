#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#define MAXSNAKE 1000
HWND hwnd = NULL;
int cas = 1;
int speed = 50;
typedef struct Point
{
	int x;
	int y;
}MYPOINT;

struct mySnake
{
	int num;
	MYPOINT p[MAXSNAKE];
	char pos;    //蛇的方向
}snake;

struct myFood
{
	MYPOINT fdxy;
	int flag;
	int eatgrade;
}food;

enum movPostion
{
	right = 72,
	left = 75,
	down = 77,
	up = 80
};

void initSnake()
{
	snake.num = 3;
	int position = 20;
	for (int i = 0; i < snake.num; i++)
	{
		snake.p[i].x = position;
		snake.p[i].y = 0;
		position -= 10;
	}
	snake.pos = right;
	food.flag = 0;
}
void drawSnake()
{
	for (int i = 0; i < snake.num; i++)
	{
		setcolor(BLACK);
		setfillcolor(BLACK);
		fillrectangle(snake.p[i].x, snake.p[i].y, snake.p[i].x+10, snake.p[i].y+10);
	}
}
void moveSnake()
{
	for (int i = snake.num - 1; i > 0; i--)
	{
		snake.p[i] = snake.p[i-1];
	}
	switch (snake.pos)
	{
	case right:
		snake.p[0].x += 10;
		break;
	case left:
		snake.p[0].x -= 10;
		break;
	case down:
		snake.p[0].y += 10;
		break;
	case up:
		snake.p[0].y -= 10;
		break;
	default:
		break;
	}
}
void keyDown()
{
	char ch = _getch();
	switch (ch)
	{
	case right:
		if (snake.pos != down)
			snake.pos = up;
		break;
	case left:
		if (snake.pos != right)
			snake.pos = left;
		break;
	case down:
		if (snake.pos != left)
			snake.pos = right;
		break;
	case up:
		if (snake.pos != up)
			snake.pos = down;
		break;
	default:
		break;
	}
}

void initfood()
{
	while (1)
	{
		bool is_ok = true;
		food.fdxy.x = (rand() % 62)*10;
		food.fdxy.y = (rand() % 47)*10;
		food.flag = 1;

		for (int i = 0; i < snake.num; i++)
		{
			if (food.fdxy.x == snake.p[i].x && food.fdxy.y == snake.p[i].y)
			{
				is_ok = false;
			}
		}
		if (is_ok)
			break;
	}
}

void drawfood()
{
	setlinecolor(BLACK);
	setfillcolor(BLACK);
	fillrectangle(food.fdxy.x, food.fdxy.y, food.fdxy.x+10, food.fdxy.y + 10);
}

void eatFood()
{
	if (food.fdxy.x == snake.p[0].x && food.fdxy.y == snake.p[0].y)
	{
		snake.num++;
		food.eatgrade += 1;
		food.flag = 0;
	}
}

 int gameOver()
{
	if (snake.p[0].x < 0 || snake.p[0].y < 0 || snake.p[0].x>640 - 10 || snake.p[0].y>480-10)
	{
		MessageBox(hwnd, (LPCWSTR)L"游戏结束",(LPCWSTR)L"失败!",0);
		return 0;
	}
	for (int i = 1; i < snake.num; i++)
	{
		if (snake.p[0].x == snake.p[i].x && snake.p[0].y == snake.p[i].y)
		{
			MessageBox(hwnd, (LPCWSTR)L"游戏结束", (LPCWSTR)L"失败!", 0);
			return 0;
		}
	}
	return 1;
}
 void CharToTchar(const char* _char, TCHAR* tchar)
 {
	 int iLength;
	 iLength = MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, NULL, 0);
	 MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, tchar, iLength);
 }
 void showScore()
{
	 char gradetmp[100] = {""};
	 sprintf(gradetmp, "分数：%d", food.eatgrade);
	 TCHAR grade[100];
	 CharToTchar(gradetmp,grade);
	 setbkmode(TRANSPARENT);
	 settextcolor(RED);
	 char casStrtmp[100] = { "" };
	 sprintf(casStrtmp, "第%d关", cas);
	 TCHAR casStr[100];
	 CharToTchar(casStrtmp, casStr);
	 outtextxy(570,20, grade);
	 outtextxy(570, 40, casStr);
}
int main()
{
	srand((unsigned int)time(NULL));
	hwnd = initgraph(640,480);
	setbkcolor(WHITE);
	cleardevice();
	initSnake();
	while (1)
	{
		cleardevice();
		if (food.flag == 0)
		{
			initfood();
		}
		drawfood();
		drawSnake();
		if (!gameOver())
		{
			break;
		}
		eatFood();
		moveSnake();
		while (_kbhit())
		{
			keyDown();
		}
		if (food.eatgrade != 0)
		{
			cas = food.eatgrade/10 + 1;
		}
		showScore();
		Sleep(200- speed*cas);
	}
	//getchar();
	closegraph();
	return 0;
}