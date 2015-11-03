#include <iostream>
#include <stdlib.h>
#include <conio.h>

using namespace std;

void func_a(int **input, int M, int N, int *&B);
void func_b(int **input, int M, int N, int *&B);
void func_d(int** input, int M, int N, int *&B);
void func_d_1(int** input, int M, int N, int *&B, int i_left, int i_right, int j_up, int j_down, int n);
void func_c(int** input, int M, int N, int *&B);
void func_c_1(int** input, int M, int N, int *&B, int i_left, int i_right, int j_up, int j_down, int n);

void func_2();

const int N = 5;

int main()
{
	setlocale(LC_CTYPE, "rus"); // вызов функции настройки локали
	int **A, *B;
	A = new int *[N];
	B = new int[N*N];
	for(int i = 0; i < N; i++)
	{
		A[i] = new int[N];
		for(int j = 0; j < N; j++)	A[i][j] = j + i*10;
	}
	cout<<"A:"<<endl;
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			cout<<A[i][j]<<"\t";
		}
		cout<<endl;
	}
	func_a(A, N, N, B);
	cout<<"B:"<<endl<<"По правым диагоналям справа налево"<<endl;
	for(int i = 0; i < N*N; i++) cout<<B[i]<<" ";
	func_b(A, N, N, B);
	cout<<endl<<"По левым диагоналям слева направо"<<endl;
	for(int i = 0; i < N*N; i++) cout<<B[i]<<" ";
	
	func_c(A, N, N, B);
	cout<<endl<<"Спираль с центра"<<endl;
	for(int i = 0; i < N*N; i++) cout<<B[i]<<" ";
	func_d(A, N, N, B);
	cout<<endl<<"Спираль с левого верхнего элемента"<<endl;
	for(int i = 0; i < N*N; i++) cout<<B[i]<<" ";
	func_2();
	getch();
	return 1;
}

void func_a(int **input, int M, int N, int *&B)
{
	int k = 0, j = 0, pos = 0;
	for(int i = N - 1; i >= 0; i--)
	{
		k = i;
		j = 0;
		while(1)
		{
			if(k >= N || j >= N) break;
			B[pos++] = input[j][k];
			k++;
			j++;
		}
	}
	for(int i = 1; i < N; i++)
	{
		k = 0;
		j = i;
		while(1)
		{
			if(k >= N || j >= N) break;
			B[pos++] = input[j][k];
			k++;
			j++;
		}
	}
}

void func_2()
{
	int N = 5;
	int **B = new int*[5];
	cout<<endl<<endl;
	for(int i = 0; i < N; i++)	
	{
		B[i] = new int[i + 1];
		for(int j = 0; j < i + 1; j++)
		{
			B[i][j] = rand() % 256;
			cout<<B[i][j]<<"\t";
		}
		cout<<endl;
	}
}

void func_b(int **input, int M, int N, int *&B)
{
	int k = 0, j = 0, pos = 0;
	for(int i = 0; i < N; i++)
	{
		k = i;
		j = 0;
		while(1)
		{
			if(k < 0 || j >= N) break;
			B[pos++] = input[j][k];
			k--;
			j++;
		}
	}
	for(int i = 1; i < N; i++)
	{
		k = N - 1;
		j = i;
		while(1)
		{
			if(k < 0 || j >= N) break;
			B[pos++] = input[j][k];
			k--;
			j++;
		}
	}
}

void func_d(int** input, int M, int N, int *&B)
{
	func_d_1(input, M, N, B, 0, N, 0, M, 0);
}

void func_d_1(int** input, int M, int N, int *&B, int i_left, int i_right, int j_up, int j_down, int n)
{
	if(j_up >= j_down && i_left >= i_right) return;
	for(int i = i_left; i < i_right; i++)
	{
		B[n++] = input[j_up][i];
	}
	j_up++;
	for(int i = j_up; i < j_down; i++)
	{
		B[n++] = input[i][i_right - 1];
	}
	i_right--;
	for(int i = i_right - 1; i >= i_left; i--)
	{
		B[n++] = input[j_down-1][i];
	}
	j_down--;
	for(int i = j_down - 1; i >= j_up; i--)
	{
		B[n++] = input[i][i_left];
	}
	i_left++;
	func_d_1( input,  M,  N, B,  i_left,  i_right,  j_up,  j_down,  n);
}

void func_c(int** input, int M, int N, int *&B)
{
	func_c_1(input, M, N, B, 0, N - 1, 0, M - 1, M * N - 1);
}

void func_c_1(int** input, int M, int N, int *&B, int i_left, int i_right, int j_up, int j_down, int n)
{
	if(j_up > j_down && i_left > i_right) return;
	func_c_1( input,  M,  N, B,  i_left + 1,  i_right - 1,  j_up + 1,  j_down - 1,  n - 2 * ((j_down - j_up) + (i_right - i_left)));
	for(int i = i_left; i <= i_right; i++)
	{
		B[n--] = input[j_up][i];
	}
	for(int i = j_up + 1; i <= j_down; i++)
	{
		B[n--] = input[i][i_right];
	}
	for(int i = i_right - 1; i >= i_left; i--)
	{
		B[n--] = input[j_down][i];
	}
	for(int i = j_down - 1; i > j_up; i--)
	{
		B[n--] = input[i][i_left];
	}
}
