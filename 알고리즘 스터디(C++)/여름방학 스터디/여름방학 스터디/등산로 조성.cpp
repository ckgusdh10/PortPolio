#include "stdafx.h"

#include <iostream>
#include <vector>


using namespace std;

int base[8][8];
vector<pair<int, int>> v;
int roadnum = 1;

int N, K;

void findroad(int xpos, int ypos, int rn)
{
	if (xpos > 0)
	{
		if (base[xpos - 1][ypos] < base[xpos][ypos])
		{
			findroad(xpos - 1, ypos, rn + 1);
		}
	}
	if (xpos < N - 1)
	{
		if (base[xpos + 1][ypos] < base[xpos][ypos])
		{
			findroad(xpos + 1, ypos, rn + 1);
		}
	}
	if (ypos > 0)
	{
		if (base[xpos][ypos - 1] < base[xpos][ypos])
		{
			findroad(xpos, ypos - 1, rn + 1);
		}
	}
	if (ypos < N - 1)
	{
		if (base[xpos][ypos + 1] < base[xpos][ypos])
		{
			findroad(xpos, ypos + 1, rn +1);
		}
	}
	
	if (rn > roadnum)
		roadnum = rn;
	
}

int main()
{
	int T;
	cin >> T;
	

	for (int i = 0; i < T; ++i)
	{
		int high = 0;
		int maxroad = 0;
		cin >> N >> K;

		for (int j = 0; j < N; ++j)
		{
			for (int k = 0; k < N; ++k)
			{
				int height = 0;
				cin >> height;
				//if (height > high)
					//high = height;
				base[j][k] = height;
			}
		}
		

		for (int a = 0; a <= K; ++a)
		{
			for (int r = 0; r < N; ++r)
			{
				for (int s = 0; s < N; ++s)
				{
					base[r][s] -= a;
					for (int j = 0; j < N; ++j)
					{
						for (int k = 0; k < N; ++k)
						{
							//int high = 0;
							//cin >> height;
							if (base[j][k] > high)
								high = base[j][k];
							//base[j][k] = height;
						}
					}

					for (int j = 0; j < N; ++j)
					{
						for (int k = 0; k < N; ++k)
						{
							if (base[j][k] == high)
								v.push_back(make_pair(j, k));
						}
					}
					for (auto x : v)
					{
						findroad(x.first, x.second, 1);
						//cout << roadnum << endl;
						if (roadnum > maxroad)
							maxroad = roadnum;
					
						roadnum = 1;
					}
					v.clear();
					base[r][s] += a;
				}
			}
			
			roadnum = 0;
		}
		cout << "#" << i+1 << " " << maxroad << endl;
		maxroad = 0;
	
	}
}