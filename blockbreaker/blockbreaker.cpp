// blockbreaker.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

using namespace std;

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code)&0x8000)?1:0)
int g_arrMap[15][10] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
	{ 1, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
	{ 1, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
};
struct sData
{
	int nRow;
	int nCol;
	int nRowBk;
	int nColBk;
};

sData g_arrBoard[3];
enum
{
	E_DIR_NONE,
	E_DIR_LEFT_UP,
	E_DIR_LEFT_DOWN,
	E_DIR_RIGHT_UP,
	E_DIR_RIGHT_DOWN,
};
int g_nDir = E_DIR_NONE;
sData g_Ball;
int main()
{
	g_Ball.nRow = 12;
	g_Ball.nCol = 5;
	g_Ball.nRowBk = 12;
	g_Ball.nColBk = 5;
	//设置板的坐标
	for (int i = 0; i < 3; i++)
	{
		g_arrBoard[i].nRow = 13;
		g_arrBoard[i].nCol = 4 + i;
		g_arrBoard[i].nRowBk = 13;
		g_arrBoard[i].nColBk = 4 + i;
	}

	while (true)
	{
		system("cls");
		//板坐标备份
		for (int i = 0; i < 3; i++)
		{
			g_arrBoard[i].nRowBk = g_arrBoard[i].nRow;
			g_arrBoard[i].nColBk = g_arrBoard[i].nCol;
		}

		if (KEY_DOWN(VK_LEFT))
		{
			for (int i = 0; i < 3; i++)
			{
				g_arrBoard[i].nCol--;
			}
		}
		else if (KEY_DOWN(VK_RIGHT))
		{
			for (int i = 0; i < 3; i++)
			{
				g_arrBoard[i].nCol++;
			}
		}
		else if (KEY_DOWN(VK_RETURN))
		{
			g_nDir = E_DIR_LEFT_UP;
		}
		//球备份
		g_Ball.nRowBk = g_Ball.nRow;
		g_Ball.nColBk = g_Ball.nCol;
		//球运动
		if (E_DIR_LEFT_UP == g_nDir)
		{
			g_Ball.nRow--;
			g_Ball.nCol--;
		}
		else if (E_DIR_RIGHT_UP == g_nDir)
		{
			g_Ball.nRow--;
			g_Ball.nCol++;
		}
		else if (E_DIR_LEFT_DOWN == g_nDir)
		{
			g_Ball.nRow++;
			g_Ball.nCol--;
		}
		else if (E_DIR_RIGHT_DOWN == g_nDir)
		{
			g_Ball.nRow++;
			g_Ball.nCol++;
		}
		//球撞墙板
		bool bTouchBoard = false;
		for (int i = 0; i < 3; i++)
		{
			if ((g_arrBoard[i].nRow == g_Ball.nRow)
				&& (g_arrBoard[i].nCol == g_Ball.nCol))
			{
				bTouchBoard = true;
				if (E_DIR_LEFT_DOWN == g_nDir && bTouchBoard)
				{
					g_nDir = E_DIR_LEFT_UP;
				}
				else if (E_DIR_RIGHT_DOWN == g_nDir && bTouchBoard)
				{
					g_nDir = E_DIR_RIGHT_UP;
				}
				g_Ball.nRow = g_Ball.nRowBk;
				g_Ball.nCol = g_Ball.nColBk;
				break;
			}
		}
		//球撞墙
		if (1 == g_arrMap[g_Ball.nRow][g_Ball.nCol])
		{

			if (E_DIR_LEFT_UP == g_nDir && g_Ball.nCol == 0)
			{
				g_nDir = E_DIR_RIGHT_UP;
			}
			else if (E_DIR_LEFT_DOWN == g_nDir && g_Ball.nCol == 0)
			{
				g_nDir = E_DIR_RIGHT_DOWN;
			}
			else if (E_DIR_RIGHT_UP == g_nDir && g_Ball.nRow == 0)
			{
				g_nDir = E_DIR_RIGHT_DOWN;
			}
			else if (E_DIR_LEFT_UP == g_nDir && g_Ball.nRow == 0)
			{
				g_nDir = E_DIR_LEFT_DOWN;
			}
			else if (E_DIR_RIGHT_DOWN == g_nDir && g_Ball.nCol == 9)
			{
				g_nDir = E_DIR_LEFT_DOWN;
			}
			else if (E_DIR_RIGHT_UP == g_nDir && g_Ball.nCol == 9)
			{
				g_nDir = E_DIR_LEFT_UP;
			}
			else if (E_DIR_LEFT_DOWN == g_nDir && bTouchBoard)
			{
				g_nDir = E_DIR_LEFT_UP;
			}
			else if (E_DIR_RIGHT_DOWN == g_nDir && bTouchBoard)
			{
				g_nDir = E_DIR_RIGHT_UP;
			}
			g_Ball.nRow = g_Ball.nRowBk;
			g_Ball.nCol = g_Ball.nColBk;
		}

		//判断板碰墙
		if ((1 == g_arrMap[g_arrBoard[0].nRow][g_arrBoard[0].nCol])
			|| (1 == g_arrMap[g_arrBoard[2].nRow][g_arrBoard[2].nCol]))
		{
			for (int i = 0; i < 3; i++)
			{
				g_arrBoard[i].nRow = g_arrBoard[i].nRowBk;
				g_arrBoard[i].nCol = g_arrBoard[i].nColBk;
			}
		}

		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				bool bDrawBoard = false;
				for (int m = 0; m < 3; m++)
				{
					if (g_arrBoard[m].nRow == i && g_arrBoard[m].nCol == j)
					{
						bDrawBoard = true;
						break;
					}
				}
				if (1 == g_arrMap[i][j])
				{
					cout << "■";
				}
				else if (2 == g_arrMap[i][j])
				{
					cout << "■";
				}
				else if (g_Ball.nRow == i && g_Ball.nCol == j)
				{
					cout << "●";
				}
				else if (bDrawBoard)
				{
					cout << "■";
				}
				else
				{
					cout << "  ";
				}
			}
			cout << endl;
		}
	}
	return 0;
}



// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
