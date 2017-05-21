#include<iostream>
#include<cstdlib>      //rand(),time()
#include<ctime>
#include<conio.h>       //getch()�ӿ���̨��ȡһ���ַ���������ʾ����Ļ��
#include<ctype.h>
#include<vector>
#include<algorithm>
#include<math.h>      //pow��x��y�η�
#include<iomanip>    //setw���ƿո���
#pragma warning(disable : 4996)   //Э��getch��ȡ���룬��ֹ����c4996����
using namespace std;

int array[4][4] = { 0 };

int randpro()
{
	srand(time(0));          //������������ӣ��Ե�ǰʱ��Ϊ����
	int k = rand() % 4;          //����0-3�������
	return k;
}


void display1()      //��ʾ����
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


void display()     //��ʾ����
{
	cout << setw(46) << "2048" << endl;       //���������ʽ
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



void newgame()     //�µ���Ϸ��ʼ
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

int randpros(int n)    //�������0-n-1�������
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

//ͳ��0�ĸ���������ͨ��һ��vector���������
//p��Ҫ�ж�
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

//�������һ�����֣�ͨ���ո�ĸ����������
//����ֵΪtrue��˵���ɹ����룬����δ�ܲ���
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


///////////��ü��̷���//////////////
//��ȡ����
//����ֵ
//  1   ��   72
//  2   ��   80
//  3   ��   75
//  4   ��   77
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


//////////�ƶ�����
//�������Ҳ���
//������Ϊ���������Ƚ����ڵ���ͬ���ּ�������Ȼ��ȥ���ո�
//������֮����Ҫ��������
//֮ǰ��Ϊ�������뷨�����⣬������������ͬ����֮����0�Ļ���Ҳ�ǿ��Խ�ϵ�

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
	system("cls");/////����
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
	system("cls");//����
	display();
}

void rightdir()
{
	//��ɵ�һ��
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
	system("cls");//����
	display();
}

///////////��Ϸ����
//�ж���Ϸ�Ƿ����
//��������ֵ���ж�2048�ۺ���һ��
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


//���캯��
//��������ˮƽ���ߴ�ֱ

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

//Ԥ�л��ܷ������ƶ�
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