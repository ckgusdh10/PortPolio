#include "stdafx.h"

#include <iostream>
#include <vector>

using namespace std;

int N, M, H;

int base[50][50];
int answer = 99;

int Down()
{
	int xpos;
	int ypos;
	for (int i = 1; i < N + 1; ++i)
	{	
		xpos = i;
		ypos = 0;

		for (int j = 0; j < H + 1; ++j)               // 세로로 내려가야 하는 횟수
		{
			if (base[j][xpos] == 1)
			{
				++xpos;
			}
			else if (base[j][xpos - 1] == 1)
			{
				--xpos;
			}
			ypos += 1;

		}
		//cout << xpos << " " << ypos << endl;
		if (xpos != i)
		{
			return 0;
		}
	}
	return 1;
}

void LadderAdd(int x, int y, int count)
{
	if (count > 3)
	{
		//answer = -1;
		return;
	}
	if (Down())
	{
		if (count < answer)
		{
			answer = count;
		}
		//cout << count << endl;
		return;
	}

	for (int i = x; i < H + 1; ++i)
	{
		for (int j = 1; j < N + 1; ++j)
		{
			if (base[i][j] == 1 || base[i][j - 1] == 1 || base[i][j + 1] == 1)
				continue;

			base[i][j] = 1;
			LadderAdd(i, y, count + 1);
			base[i][j] = 0;
		}
	}
}

int main()
{
	

	cin >> N >> M >> H;

	if (M > 0)
	{
		for (int i = 0; i < M; ++i)
		{
			int a, b;
			cin >> a >> b;
			base[a][b] = 1;
			
		}
	}

	LadderAdd(1, 1, 0);

	if (answer > 3)
		answer = -1;
	cout << answer << endl;

	
}