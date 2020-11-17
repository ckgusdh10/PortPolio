#include "stdafx.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int solution(string str1, string str2) {
	int answer = 0;

	vector<string> v;
	vector<string> v2;

	for (int i = 0; i < str1.size() - 1; ++i)
	{
		int a = str1[i];
		int b = str1[i + 1];
		
		if (str1[i] == ' ' || str1[i + 1] == ' ')
		{
			continue;
		}
		if (a < 65 || a > 122)
			continue;
		if (90 < a && a < 97)
			continue;
		if (b < 65 || b > 122)
			continue;
		if (90 < b && b < 97)
			continue;
		//if (64 < a < 91 || 96 < a < 123)
		{
			char c = tolower(str1[i]);
			char c1 = tolower(str1[i + 1]);
			string s;
			s += c;
			s += c1;
			v.push_back(s);
			//cout << s << endl;
		}
	}
	
	for (int i = 0; i < str2.size() - 1; ++i)
	{
		int a = str2[i];
		int b = str2[i + 1];
		if (str2[i] == ' ' || str2[i + 1] == ' ')
		{
			continue;
		}
		if (a < 65 || a > 122)
			continue;
		if (90 < a && a < 97)
			continue;
		if (b < 65 || b > 122)
			continue;
		if (90 < b && b < 97)
			continue;
		//if (64 < a < 91 || 96 < a < 123)
		{
			char c = tolower(str2[i]);
			char c1 = tolower(str2[i + 1]);
			string s;
			s += c;
			s += c1;
			v2.push_back(s);
			//cout << s << endl;
		}
	}
	if (v.size() == 0 || v2.size() == 0)
	{
		answer = 65536;
		return answer;
	}
	double sum = v.size() + v2.size();
	//cout << sum << endl;
	double intersection = 0;
	double union_num = 0;
	if (v.size() < v2.size())
	{
		for (int i = 0; i < v.size(); ++i)
		{
			for (int j = 0; j < v2.size(); ++j)
			{
				if (v[i] == v2[j])
				{
					++intersection;
					break;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < v2.size(); ++i)
		{
			for (int j = 0; j < v.size(); ++j)
			{
				if (v2[i] == v[j])
				{
					++intersection;
					break;
				}
			}
		}
	}
	if (intersection == 0)
	{
		answer = 0;
		return answer;
	}
	union_num = sum - intersection;
	double d = (intersection / union_num);
	//cout << (int)(d * 65536) << endl;
	answer = (int)(d * 65536);

	/*for (auto a : v)
		cout << a << endl;
	cout << endl;
	for (auto a : v2)
		cout << a << endl;

	cout << sum << " " << intersection << " " << union_num << endl;*/

	return answer;
}

int main()
{
	string s1 = "FRANCE";
	string s2 = "french";

	string s3 = "handshake";
	string s4 = "shake hands";

	string s5 = "aa1+aa2";
	string s6 = "AAAA12";

	string s7 = "E=M*C^2";
	string s8 = "e=m*c^2";

	//string s9 = "FRANCE";
	//string s10 = "FRENCHARM";

	//cout << ("AA","aa") << endl;

	cout << solution(s8, s7) << endl;
}