#include "stdafx.h"

#include <iostream>

using namespace std;

int base[40][40] = { 0 };
int sti[10][10] = { 0 };
int N, M, K;

void rot(int sticker[10][10], int r, int c)
{
	int temp[10][10];
	int N = r;
	int M = c;

	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
			temp[i][j] = sticker[N - j - 1][i];
	}

	for (int i = 0; i < c; ++i)
	{
		for (int j = 0; j < r; ++j)
		{
			sti[i][j] = temp[i][j];
		}
	}

}

bool Check(int sti[10][10], int r, int c)
{
	int x = 0, y = 0;
	bool b2 = false;
	while (!b2)
	{
		bool b = false;

		if (r > N || c > M)
			return false;

		for (int i = x; i < r + x; ++i)
		{
			for (int j = y; j < c + y; ++j)
			{
				if (base[i][j] == 1 && sti[i - x][j - y] == 1)         // 노트북 공간에 스티커가 있을 때
				{
					//return false;
					b = true;
					break;
				}

			}
			if (b)
				break;

		}
		if (!b)                                             // 여기까지 오면 노트북에 스티커 붙일 공간을 찾은 것
		{
			for (int i = x; i < r + x; ++i)
			{
				for (int j = y; j < c + y; ++j)
				{
					if (sti[i - x][j - y] == 1)
						base[i][j] = 1;

				}
			}
			//break;
			return true;
		}

		y += 1;
		if (y > M - c)
		{
			x += 1;
			y = 0;
			if (x > N - r)
			{
				//b2 = true;
				return false;
			}
		}
	}
}

int main()
{

	cin >> N >> M >> K;



	for (int k = 0; k < K; ++k)
	{

		int r, c;
		cin >> r >> c;

		for (int i = 0; i < r; ++i)
		{
			for (int j = 0; j < c; ++j)
			{
				cin >> sti[i][j];
			}
		}
		if (!Check(sti, r, c))                        // 회전 하기 전 검사
		{
			for (int i = 0; i < 3; ++i)
			{
				rot(sti, r, c);
				int temp = r;
				r = c;
				c = temp;

				if (Check(sti, r, c))
				{
					break;
				}
			}

		}

	}
	int answer = 0;
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			if (base[i][j] == 1)
				++answer;
		}
	}

	cout << answer << endl;
}