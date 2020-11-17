#include "stdafx.h"

#include <iostream>
#include <stack>

using namespace std;


struct STONE {
	int x;
	int y;
	int dir;
};


int N, K;
int base[13][13] = { 0 };
STONE stone[10];

stack<int> s[13][13];

int dirX[4] = { 0,0,-1,1 };
int dirY[4] = { 1,-1,0,0 };
bool flag = false;

void move(int index, int c)
{
	if (c > 1)
		return;
	int nx = stone[index].x + dirX[stone[index].dir - 1];
	int ny = stone[index].y + dirY[stone[index].dir - 1];

	if (nx > N || ny > N || nx <= 0 || ny <= 0 || base[nx][ny] == 2)
	{
		if (c == 1)
			return;
		if (stone[index].dir == 1)
			stone[index].dir = 2;
		else if (stone[index].dir == 2)
			stone[index].dir = 1;
		else if (stone[index].dir == 3)
			stone[index].dir = 4;
		else if (stone[index].dir == 4)
			stone[index].dir = 3;

		move(index, c + 1);

		return;
	}

	if (base[nx][ny] == 0)
	{
		stack<int> temp;
		while (!s[stone[index].x][stone[index].y].empty())
		{
			int t = s[stone[index].x][stone[index].y].top();
			temp.push(t);
			s[stone[index].x][stone[index].y].pop();

			stone[t].x = nx;
			stone[t].y = ny;
			if (t == index)
				break;
		}
		while (!temp.empty())
		{
			s[nx][ny].push(temp.top());
			temp.pop();
			
		}
		for (int i = 1; i <= N; ++i)
		{
			for (int j = 1; j <= N; ++j)
			{
				if (s[i][j].size() >= 4)
				{
					//cout << answer << endl;
					flag = true;
				}
			}
		}
		if (s[nx][ny].size() >= 4)
		{
			flag = true;
		}
	}

	if (base[nx][ny] == 1)
	{
		while (!s[stone[index].x][stone[index].y].empty())
		{
			int t = s[stone[index].x][stone[index].y].top();
			s[nx][ny].push(t);
			s[stone[index].x][stone[index].y].pop();

			stone[t].x = nx;
			stone[t].y = ny;

			if (t == index)
				break;
		}
		for (int i = 1; i <= N; ++i)
		{
			for (int j = 1; j <= N; ++j)
			{
				if (s[i][j].size() >= 4)
				{
					//cout << answer << endl;
					flag = true;
				}
			}
		}

	}

}



int main()
{
	cin >> N >> K;

	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= N; ++j)
		{
			cin >> base[i][j];
		}
	}

	for (int i = 0; i < K; ++i)
	{
		cin >> stone[i].x >> stone[i].y >> stone[i].dir;
		s[stone[i].x][stone[i].y].push(i);
	
	}

	int answer = 0;

	while (!flag)
	{
		++answer;
		if (answer > 1000)
		{
			cout << "-1" << endl;
			break;
		}
		for (int i = 0; i < K; ++i)
		{
			move(i, 0);
		}
		
	}
	if(flag)
		cout << answer << endl;
}