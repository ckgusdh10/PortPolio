#include "stdafx.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int solution(int m, int n, vector<string> board) {
	int answer = 0;
	

	while (true)
	{
		vector<pair<int, int>> v;
		for (int i = 0; i < m - 1; ++i)
		{
			for (int j = 0; j < n - 1; ++j)
			{
				char c = board[i][j];
				if (c == 'z')
					continue;
				if (c == board[i + 1][j] && c == board[i][j + 1] && c == board[i + 1][j + 1])
				{
					v.push_back(make_pair(i, j));
				}
			}
		}

		if (v.size() == 0)
		{
			break;
		}


		for (int i = 0; i < v.size(); ++i)
		{
			int x = v[i].first;
			int y = v[i].second;

			if (board[x][y] != 'z')
			{
				board[x][y] = 'z';
				++answer;
			}
			if (board[x + 1][y] != 'z')
			{
				board[x + 1][y] = 'z';
				++answer;
			}
			if (board[x][y + 1] != 'z')
			{
				board[x][y + 1] = 'z';
				++answer;
			}
			if (board[x + 1][y + 1] != 'z')
			{
				board[x + 1][y + 1] = 'z';
				++answer;
			}

		}

		bool flag = true;
		while (flag)
		{
			flag = false;
			for (int i = 0; i < m - 1; ++i)
			{
				for (int j = 0; j < n; ++j)
				{
					if (board[i + 1][j] == 'z')
					{
						board[i + 1][j] = board[i][j];
						board[i][j] = 'z';
						//flag = true;
					}
				}
			}
			for (int i = 0; i < m - 1; ++i)
			{
				for (int j = 0; j < n; ++j)
				{
					if (board[i][j] != 'z' && board[i + 1][j] == 'z')
					{
						flag = true;
					}
				}
			}

		}

	}

	return answer;
}

int main()
{
	int m = 4;
	int n = 5;

	int m2 = 6;
	int n2 = 6;

	vector<string> v = { "CCBDE", "AAADE", "AAABF", "CCBBF" };
	vector<string> v2 = { "TTTANT", "RRFACC", "RRRFCC", "TRRRAA", "TTMMMF", "TMMTTJ" };
	cout << solution(m2, n2, v2) << endl;

}