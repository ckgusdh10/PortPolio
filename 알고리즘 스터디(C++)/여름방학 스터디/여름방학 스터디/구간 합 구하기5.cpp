#include "stdafx.h"

#include <iostream>

using namespace std;

int main()
{
	int N, M;
	//cin >> N >> M;
	scanf_s("%d %d", &N, &M);
	//scanf("%d", &M);

	int base[1025][1025];

	for (int i = 0; i<N; ++i)
	{
		for (int j = 0; j<N; ++j)
		{
			int num;
			//cin >> num;
			scanf_s("%d", &num);

			base[i + 1][j + 1] = base[i + 1][j] + base[i][j + 1] - base[i][j] + num;
		}
	}

	for (int i = 0; i < M; ++i)
	{
		int x1, x2, y1, y2;
		cin >> x1 >> y1 >> x2 >> y2;

		printf("%d\n", base[x2][y2] - base[x1 - 1][y2] - base[x2][y1 - 1] + base[x1 - 1][y1 - 1]);
	}

}