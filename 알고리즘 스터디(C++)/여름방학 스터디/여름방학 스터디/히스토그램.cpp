#include "stdafx.h"

#include <iostream>
#include <stack>


using namespace std;

int main()
{
	int N;
	cin >> N;

	int Height[100000] = { 0 };
	stack<int> s;

	for (int i = 0; i < N; ++i)
	{
		cin >> Height[i];
	}
	//cout << endl;	
	int answer = 0;
	for (int i = 0; i <= N; ++i)
	{
		int top = 0;
		while (!s.empty() && Height[s.top()] > Height[i])
		{
			int bot = 0;
			top = s.top();
			s.pop();

			if (s.empty())
				bot = i;
			else
			{
				bot = i - s.top() - 1;
			}

			if (Height[top] * bot > answer)
				answer = Height[top] * bot;
			
		}

		s.push(i);
	}
	cout << answer << endl;

}