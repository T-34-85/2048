#include<iostream>
#include<cstdlib>      //rand(),time()
#include<ctime>
#include<conio.h>       //getch()从控制台读取一个字符，但不显示在屏幕上
#include<ctype.h>
#include<vector>
#include<algorithm>
#include<math.h>      //pow求x得y次方
#include<iomanip>    //setw控制空格数
#pragma warning(disable : 4996)   //协助getch获取输入，防止出现c4996错误
using namespace std;

int array[4][4] = { 0 };

int randpro()
{
	srand(time(0));          //重置随机数种子，以当前时间为参数
	int k = rand() % 4;          //生成0-3的随机数
	return k;
}


void display1()      //显示界面
{
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (array[i][j] == 0)
			{
				cout << " " << "   ";
			}
			else
				cout << array[i][j] << "     ";
		}
		cout << endl;
	}
	cout << "----------------" << endl;
}


void display()     //显示棋盘
{
	cout << setw(46) << "2048" << endl;       //控制输出格式
	cout << setw(50) << "|-----------------------|" << endl;
	for (int i = 0; i <= 3; i++)
	{
		cout << setw(24) << "";
		for (int j = 0; j <= 3; j++)
		{
			if (array[i][j] == 0)
			{
				cout << setw(2) << "|" << setw(4) << " ";
			}
			else
			{
				cout << setw(2) << "|" << setw(4) << array[i][j];
			}
			if (j == 3)
			{
				cout << setw(2) << "|" << endl;
				cout << setw(50) << "|-----------------------|" << endl;
			}
		}
	}
}



void newgame()     //新的游戏开始
{
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			array[i][j] = 0;
		}
	}
	int m = randpro();
	int n = randpro();
	array[m][n] = 2;
	display;
}

int randpros(int n)    //随机产生0-n-1的随机数
{
	srand(time(0));
	int k = rand() % n;
	return k;
}


int randpross(int n)
{
	srand(time(0));
	int k = rand() % (n + 1);
	return k;
}

//统计0的个数，并且通过一个vector来存放坐标
//p需要判断
vector<vector<int>> zeronum(int *p)
{
	int i, j;
	int k = 0;

	vector<vector<int >> v(16, vector<int>());

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (array[i][j] == 0)
			{
				v[k].push_back(i);
				v[k].push_back(j);
				k++;
			}
		}
	}
	*p = k;
	return v;
}

//随机插入一个数字，通过空格的个数随机插入
//返回值为true就说明成功输入，否则未能插入
bool insertnum()
{
	int k = 0;
	vector<vector<int>> v;
	v = zeronum(&k);

	if (k > 0)
	{
		int m = randpros(k);
		int x = v[m][0];
		int y = v[m][1];
		array[x][y] = pow(2.0, randpross(2));
		return true;
	}
	return false;
}


///////////获得键盘方向//////////////
//获取方向
//返回值
//  1   上   72
//  2   下   80
//  3   左   75
//  4   右   77
int getdirection()
{
	char c1, c2;
	int ret = 0;
	c1 = getch();
	if (!isascii(c1))
	{
		c2 = getch();
		switch (c2)
		{
		    case 72:ret = 1; break;
			case 80:ret = 2; break;
			case 75:ret = 3; break;
			case 77:ret = 4; break;
			default:break;
		}
	}
	return ret;
}


//////////移动操作
//上下左右操作
//操作分为两步，首先将相邻的相同数字加起来，然后去除空格
//操作完之后需要插入数字
//之前分为两步的想法有问题，假如是两个相同数字之间有0的话，也是可以结合的

void updir()
{
	int i, j;
	for (i = 0; i < 4; i++)
	{
		int k = 0;
		int x = 0;
		int y = 0;
		for (j = 0; j < 4; j++)
		{
			if (k == array[j][i] && k != 0)
			{
				array[x][y] = 2 * k;
				array[j][i] = 0;
				k = 0;
				continue;
			}
			if (array[j][i] != 0)
			{
				k = array[j][i];
				x = j;
				y = i;
			}
		}
	}
	for (i = 0; i < 4; i++)
	{
		int k = 0;
		for (j = 0; j < 4; j++)
		{
			if (array[j][i])
			{
				if (k != j)
				{
					array[k][i] = array[j][i];
					array[j][i] = 0;
				}
				k++;
			}
		}
	}

	insertnum();
	system("cls");/////清屏
	display();
}

void downdir()
{
	int i, j;
	for (i = 0; i<4; i++)
	{
		int k = 0;
		int x = 0;
		int y = 0;
		for (j = 3; j >= 0; j--)
		{
			if (k == array[j][i] && k != 0)
			{
				array[x][y] = 2 * k;
				array[j][i] = 0;
				k = 0;
				continue;
			}
			if (array[j][i] != 0)
			{
				k = array[j][i];
				x = j;
				y = i;
			}
		}
	}

	for (i = 0; i<4; i++)
	{
		int k = 3;
		for (j = 3; j >= 0; j--)
		{
			if (array[j][i])
			{
				if (k != j)
				{
					array[k][i] = array[j][i];
					array[j][i] = 0;
				}
				k--;
			}
		}
	}

	insertnum();
	system("cls");
	display();
}


void leftdir()
{
	int i, j;
	for (i = 0; i<4; i++)
	{
		int k = 0;
		int x = 0;
		int y = 0;
		for (j = 0; j<4; j++)
		{
			if (k == array[i][j] && k != 0)
			{
				array[x][y] = 2 * k;
				array[i][j] = 0;
				k = 0;
				continue;
			}
			if (array[i][j] != 0)
			{
				k = array[i][j];
				x = i;
				y = j;
			}
		}

	}

	for (i = 0; i<4; i++)
	{
		int k = 0;
		for (j = 0; j<4; j++)
		{
			if (array[i][j])
			{
				if (k != j)
				{
					array[i][k] = array[i][j];
					array[i][j] = 0;
				}
				k++;
			}
		}
	}

	insertnum();
	system("cls");//清屏
	display();
}

void rightdir()
{
	//完成第一步
	int i, j;
	for (i = 0; i<4; i++)
	{
		int k = 0;
		int x = 0;
		int y = 0;
		for (j = 3; j >= 0; j--)
		{
			if (k == array[i][j] && k != 0)
			{
				array[x][y] = 2 * k;
				array[i][j] = 0;
				k = 0;
				continue;
			}
			if (array[i][j] != 0)
			{
				k = array[i][j];
				x = i;
				y = j;
			}
		}
	}

	for (i = 0; i<4; i++)
	{
		int k = 3;
		for (j = 3; j >= 0; j--)
		{
			if (array[i][j])
			{
				if (k != j)
				{
					array[i][k] = array[i][j];
					array[i][j] = 0;
				}
				k--;
			}
		}
	}

	insertnum();
	system("cls");//清屏
	display();
}

///////////游戏结束
//判断游戏是否结束
//将求解最大值和判断2048糅合在一起
bool iswin()
{
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (array[i][j] == 2048)
			{
				return true;
			}
		}
	}
	return false;
}


//构造函数
//两个方向，水平或者垂直

bool canver()
{
	int i, j;
	for (i = 0; i < 4; i++)
	{
		int k = 0;
		for (j = 0; j < 4; j++)
		{
			if (k == array[j][i] && k != 0)
			{
				return true;
			}
			if (array[j][i] != 0)
			{
				k = array[j][i];
			}
		}
	}
	return false;
}


bool canhor()
{
	int i, j;
	for (i = 0; i < 4; i++)
	{
		int k = 0;
		for (j = 3; j >= 0; j--)
		{
			if (array[i][j] && k != 0)
			{
				return true;
			}
			if (array[i][j] != 0)
			{
				k = array[i][j];
			}
		}
	}
	return false;
}

//预判还能否左右移动
bool islose()
{
	int k = 0;
	zeronum(&k);
	if (k>0)
	{
		return false;
	}
	if (canver() || canhor())
	{
		return false;
	}
	return true;
}

void main()
{
	newgame();
	int dir = 0;
	while (1)
	{
		if (iswin())
		{
			cout << "you win" << endl;
			break;
		}
		if (islose())
		{
			cout << "you lose" << endl;
			break;
		}
		dir = getdirection();
		switch (dir)
		{
		case 1: updir(); break;
		case 2: downdir(); break;
		case 3: leftdir(); break;
		case 4: rightdir(); break;
		default:break;
		}
	}

	system("pause");
}