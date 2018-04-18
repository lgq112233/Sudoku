#include<iostream>
#include<time.h>
#include<algorithm>
#include<string>
#include<stdlib.h>

#pragma warning(disable:4996)

using namespace std;

void swap(int &a, int &b);
void Swap_col(int s, int e);  //交换两列
void Swap_row(int s, int e);   //交换两行
int qipan[9][9];
int f[9];
void swap(int &a, int &b) {

	int temp ;
	temp = a;
	a = b;
	b = temp;
}
int shengcheng(int M[]) {   
	for (int i = 0; i < 9; i++)   
		M[i] = i + 1;
	for (int i = 0; i < 20; i++) {
		int j = rand() % 9;    
		swap(M[j], M[8]); 
	}
	return 0;
}
int check(int x, int y, int num) {  
	for (int i = 0; i < 9; i++)
	{   
		if (qipan[x][i] == num)
			return 0;
		if (qipan[i][y] == num)
			return 0;
	}
	int left_x = x - x % 3, left_y = y - y % 3;    //计算所在小块的第一个数字的公式
	for (int i = left_x; i < left_x + 3; i++)  
		for (int j =left_y; j < left_y + 3; j++)
			if (qipan[i][j] == num)
				return 0;
	return 1;
}
int Fill(int x, int y) {    
	int next_x = x + (y + 1) / 9, next_y = (y + 1) % 9, q = qipan[x][y];
	if (x >= 9)    
		return 1;
	if(!qipan[x][y])
	{
		int i = 0;
		while(i>=0&&i<9)
		{
			int N = f[i++];    
			if (check( x, y, N))
			{    
				qipan[x][y] = N;
				if (Fill(next_x, next_y))
					return 1;
			}
		}
	}
	else {
		if (Fill(next_x, next_y))
			return 1;
	}
	qipan[x][y] = q;   
	return 0;
}
void Swap_Row(int s, int e) {
	for (int i = 0; i < 5; i++) 
	{
		int j = rand() % (e - s + 1) + s;
		for (int k = 0; k < 9; k++)
			swap(qipan[j][k], qipan[e][k]);
	}
}
void Swap_Col(int s, int e) 
{   
	for (int i = 0; i < 5; i++)
	{
		int j = rand() % (e - s + 1) + s;
		for (int k = 0; k < 9; k++)
			swap(qipan[k][j], qipan[k][e]);
	}
}
int Creat(int N) {   
	freopen("sudoku.txt", "w", stdout);   //打开文件 进行写入
	int initMat[9][9] =
	{
		{ 5, 3, 2, 1, 4, 6, 9, 7, 8 },
		{ 2 ,7 ,4 ,3 ,9 ,8 ,5 ,1 ,6 },
		{ 8 ,1, 3, 6, 4, 5, 2, 9, 7 },
		{ 4 ,5 ,8 ,1 ,6 ,3 ,7 ,2 ,9 },
		{ 6 ,3 ,1, 7, 2, 9, 4, 8, 5 },
		{ 7 ,2 ,9 ,8, 5 ,4, 1 ,6 ,3 },
		{ 3 ,8, 5, 9, 7, 1 ,6 ,4 ,2 },
		{ 9 ,4 ,2, 5, 8, 6, 3, 7, 1 },
		{ 1 ,6 ,7 ,4 ,3 ,2 ,9 ,5 ,8 }
	};
	while (N>0) {
		int ext = 1000;                //题目要求1000个
		memset(qipan, 0, sizeof(qipan));  
		for (int i = 0; i < 100; i++)
		{    
			shengcheng(qipan[0]);    
			for (int j = 0; j < 9; j++)
				if (qipan[0][j] == 5)           //学号后两位22 (2+2)%9+1=5
				{    
					swap(qipan[0][0], qipan[0][j]);
					break;
				}
			shengcheng(f);  
			Fill(1, 0);    
		}	
		while (ext--) {   
			if (N-- == 0)
				break;
			Swap_Col( 1, 2), Swap_Row( 1, 2);    //各行列之间的交换
			Swap_Col(3, 5), Swap_Row( 3, 5);
			Swap_Col(6, 8), Swap_Row( 6, 8);
			for (int i = 0; i < 9; i++)   
				for (int j = 0; j < 9; j++) 
				{
					putchar(qipan[i][j] + '0');
					printf(" ");
					if (j == 8)
						printf("\n");
					}	
		if (N)
			printf("\n");
		}
	}
	fclose(stdout);
	return 0;
}
int Solve(char File[]) {    
	freopen(File, "r", stdin);
	freopen("sudoku.txt", "w", stdout);   
	shengcheng(f);
	int i = 0, j = 0,count=0;
	if (count == 81)
	{
		for (i = 0; i < 9; i++)
			printf("%d", qipan[i][0]);
		for (j = 1; j < 9; j++)
			printf(" %d", qipan[i][j]);
		printf("\n");
	}
	while (scanf_s("%d", &qipan[i][j])) 
	{
		i =i+ (j + 1) / 9;    
		j = (j + 1) % 9;
		if (i == 9) 
		{    
			Fill(0, 0);	
			for (int i = 0; i < 9; i++)  
				for (int j = 0; j < 9; j++)
				{
						putchar(qipan[i][j] + '0');
						printf(" ");
						if (j == 8)
							printf("\n");
					}
				}
		printf("\n");
		}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
int dushu(char str[])
{
	int N = 0, l = strlen(str);
	for (int i = 0; i < l; i++)
	{
		if (str[i]<'0' || str[i]>'9')
			return 0;
		N = N * 10;
		N = N + str[i] - '0';
		if (N > 1000000 || N == 0)
		{
			printf("输入有误\n");
			return 0;
		}
	}
	return N;
}
int main(int argc, char **argv) {
	if (argc < 2) {    
		printf("error\n");
		return 0;
	}
	if (strcmp(argv[1], "-c") == 0) {    
		if (int N= dushu(argv[2]))
			Creat(N);    
		else
			printf("error\n");    
	}
	else if (strcmp(argv[1], "-s") == 0) {    
		Solve(argv[2]);
	}
	return 0;
}