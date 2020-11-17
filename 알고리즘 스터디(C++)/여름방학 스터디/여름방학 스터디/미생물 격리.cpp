#include "stdafx.h"

#include <iostream>
#include <vector>


using namespace std;

struct community {
public:
	int xpos;
	int ypos;
	int num;
	int dir;

};

int main()
{
	int T = 0;
	int N, M, K;

	vector<int> check[1420][1420];
	
	cin >> T;

	for (int i = 0; i < T; ++i)
	{
		cin >> N >> M >> K;
		vector<community> com;
		
		for (int j = 0; j < K; ++j)
		{
			community c;
			cin >> c.xpos >> c.ypos >> c.num >> c.dir;
			check[c.xpos][c.ypos].push_back(j);
			com.push_back(c);
			//cin >> com[j].xpos >> com[j].ypos >> com[j].num >> com[j].dir;
		}

		while (M != 0)
		{
			for (int r = 0; r < N; ++r)
			{
				for (int k = 0; k < N; ++k)
				{
					check[r][k].clear();
				}
			}

			for (int r = 0; r < K; ++r)
			{
				if (com[r].num == 0)
					continue;
				if (com[r].dir == 1)
				{

					com[r].xpos -= 1;
					check[com[r].xpos][com[r].ypos].push_back(r);

					if (com[r].xpos == 0)
					{
						com[r].num /= 2;
						com[r].dir = 2;
					}
				}
				else if (com[r].dir == 2)
				{
					com[r].xpos += 1;
					check[com[r].xpos][com[r].ypos].push_back(r);

					if (com[r].xpos == N - 1)
					{
						com[r].num /= 2;
						com[r].dir = 1;
					}
				}
				else if (com[r].dir == 3)
				{
					com[r].ypos -= 1;
					check[com[r].xpos][com[r].ypos].push_back(r);

					if (com[r].ypos == 0)
					{
						com[r].num /= 2;
						com[r].dir = 4;
					}
				}
				else
				{
					com[r].ypos += 1;
					check[com[r].xpos][com[r].ypos].push_back(r);

					if (com[r].ypos == N - 1)
					{
						com[r].num /= 2;
						com[r].dir = 3;
					}
				}
			}
			for (int r = 0; r < K; ++r)
			{
				int max_num = 0;
				int index = 0;
				int add = 0;
				int max_dir = 0;
				if (check[com[r].xpos][com[r].ypos].size() > 1)
				{
					//cout << r << endl;
					for (int k = 0; k < check[com[r].xpos][com[r].ypos].size(); ++k)
					{
						add += com[check[com[r].xpos][com[r].ypos][k]].num;
						if (com[check[com[r].xpos][com[r].ypos][k]].num > max_num)
						{
							max_num = com[check[com[r].xpos][com[r].ypos][k]].num;
							max_dir = com[check[com[r].xpos][com[r].ypos][k]].dir;
							index = check[com[r].xpos][com[r].ypos][k];
						}
						com[check[com[r].xpos][com[r].ypos][k]].num = 0;
					}
					com[index].dir = max_dir;
					com[index].num = add;

				}
			}
			//cout << endl;
			--M;
		}

		int ans = 0;
		for (int i = 0; i < K; ++i)
		{
			//cout << com[i].num << endl;
			ans += com[i].num;
		}
		cout << "#" << i + 1 << " " << ans << endl;

	
	}
}


