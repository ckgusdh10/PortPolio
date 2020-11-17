#include "stdafx.h"

#include <iostream>

struct Camera {
	int x;
	int y;
	int val;
	int dir;
};

using namespace std;

int N, M;
int base[8][8];
Camera cctv[8];

int cctv_num = 0;
int answer = 9999999;

void east(int x, int y)
{
	while (true)
	{
		if (base[x][y + 1] == 6 || y + 1 == M)
		{
			break;
		}
		else
		{
			base[x][++y] = -1;
		}
	}
}

void west(int x, int y)
{
	while (true)
	{
		if (base[x][y - 1] == 6 || y == 0)
		{
			break;
		}
		else
		{
			base[x][--y] = -1;
		}
	}
}

void north(int x, int y)
{
	while (true)
	{
		if (base[x - 1][y] == 6 || x == 0)
		{
			break;
		}
		else
		{
			base[--x][y] = -1;
		}
	}
}

void south(int x, int y)
{
	while (true)
	{
		if (base[x + 1][y] == 6 || x + 1 == N)
		{
			break;
		}
		else
		{
			base[++x][y] = -1;
		}
	}
}

void dfs(int cnt)
{
	int ans = 0;
	if (cnt == cctv_num)
	{
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				if (base[i][j] == 0)
				{
					ans++;
				}
			}
		}
		
		if (ans < answer)
		{
			answer = ans;
		}
		return;
	}
	int val = cctv[cnt].val;
	int x = cctv[cnt].x;
	int y = cctv[cnt].y;
	int dir = cctv[cnt].dir;

	int temp[8][8];
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			temp[i][j] = base[i][j];
		}
	}
	if (val == 1)
	{
		for (int i = 0; i < 4; ++i)
		{
			if (i == 0)
			{
				east(x, y);
				dfs(cnt + 1);
				
			}
			else if (i == 1)
			{
				south(x, y);
				dfs(cnt + 1);
			}
			else if (i == 2)
			{
				west(x, y);
				dfs(cnt + 1);
			}
			else
			{
				north(x, y);
				dfs(cnt + 1);
			}

			for (int i = 0; i < 8; ++i)
			{
				for (int j = 0; j < 8; ++j)
				{
					base[i][j] = temp[i][j];
				}
			}
				
		}
	}
	else if (val == 2)
	{
		for (int i = 0; i < 2; ++i)
		{
			if (i == 0)
			{
				east(x, y);
				west(x, y);
				dfs(cnt + 1);

			}
			else 
			{
				south(x, y);
				north(x, y);
				dfs(cnt + 1);
			}

			for (int i = 0; i < 8; ++i)
			{
				for (int j = 0; j < 8; ++j)
				{
					base[i][j] = temp[i][j];
				}
			}

		}
	}
	else if (val == 3)
	{
		for (int i = 0; i < 4; ++i)
		{
			if (i == 0)
			{
				east(x, y);
				north(x, y);
				dfs(cnt + 1);

			}
			else if (i == 1)
			{
				south(x, y);
				east(x, y);
				dfs(cnt + 1);
			}
			else if (i == 2)
			{
				west(x, y);
				south(x, y);
				dfs(cnt + 1);
			}
			else
			{
				north(x, y);
				west(x, y);
				dfs(cnt + 1);
			}

			for (int i = 0; i < 8; ++i)
			{
				for (int j = 0; j < 8; ++j)
				{
					base[i][j] = temp[i][j];
				}
			}

		}
	}
	else if (val == 4)
	{
		for (int i = 0; i < 4; ++i)
		{
			if (i == 0)
			{
				east(x, y);
				north(x, y);
				west(x, y);
				dfs(cnt + 1);

			}
			else if (i == 1)
			{
				south(x, y);
				east(x, y);
				north(x, y);
				dfs(cnt + 1);
			}
			else if (i == 2)
			{
				west(x, y);
				south(x, y);
				east(x, y);
				dfs(cnt + 1);
			}
			else
			{
				north(x, y);
				west(x, y);
				south(x, y);
				dfs(cnt + 1);
			}

			for (int i = 0; i < 8; ++i)
			{
				for (int j = 0; j < 8; ++j)
				{
					base[i][j] = temp[i][j];
				}
			}

		}
	}
	else
	{
		north(x, y);
		west(x, y);
		south(x, y);
		east(x, y);
		dfs(cnt + 1);
		for (int i = 0; i < 8; ++i)
		{
			for (int j = 0; j < 8; ++j)
			{
				base[i][j] = temp[i][j];
			}
		}
	}
}

int main()
{
	cin >> N >> M;

	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			cin >> base[i][j];
			if (base[i][j] != 0 && base[i][j] != 6)
			{
				cctv[cctv_num].x = i;
				cctv[cctv_num].y = j;
				cctv[cctv_num].val = base[i][j];
				cctv[cctv_num].dir = 0;
				cctv_num++;
			}
		}
	}

	dfs(0);

	cout << answer << endl;
	/*for (int i = 0; i < cctv_num; ++i)
	{
		cout << cctv[i].x << " " << cctv[i].y << endl;
	}*/

}