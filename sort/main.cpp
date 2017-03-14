#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

struct bohr_vrtx {
	int next_vrtx[26], pat_num;
	bool flag;
};

vector<bohr_vrtx> bohr;
vector<pair<string, unsigned>> pattern_count;

bohr_vrtx make_bohr_vrtx() {
	bohr_vrtx v;
	memset(v.next_vrtx, 255, sizeof(v.next_vrtx));
	v.flag = false;
	return v;
}
void bohr_ini() {
	bohr.push_back(make_bohr_vrtx());
}

void check_string_in_bohr_else_add(const string& s) {
	int num = 0;
	for (int i = 0; i < s.length(); i++)
	{
		char ch = s[i] - 'a';
		if (bohr[num].next_vrtx[ch] == -1)
		{
			bohr.push_back(make_bohr_vrtx());
			bohr[num].next_vrtx[ch] = bohr.size() - 1;
		}
		num = bohr[num].next_vrtx[ch];
	}
	if (bohr[num].flag)
	{
		++pattern_count[bohr[num].pat_num].second;
	}
	else
	{
		bohr[num].flag = true;
		pattern_count.push_back(make_pair(s, 1u));
		bohr[num].pat_num = pattern_count.size() - 1;
	}
}

int main()
{
	ifstream fin("in.txt");
	string word;
	bohr_ini();
	set<unsigned> count;

	// input
	size_t start_time = clock();
	if (!fin.is_open()) return 1;
	while (fin >> word)
	{
		for (size_t i = 0; i < word.length(); i++)
		{
			if ((word[i] < 65 || word[i] > 90) && (word[i] < 97 || word[i] > 122))
			{
				word.erase(i, 1);
				--i;
				continue;
			}
			if ((word[i] >= 65) && (word[i] <= 90)) word[i] += 32;
		}
		check_string_in_bohr_else_add(word);

	}
	fin.close();
	cout << "input - " << clock() - start_time << endl;

	// search max
	start_time = clock();
	for (auto it = pattern_count.begin(); it != pattern_count.end(); ++it)
	{
		count.insert(it->second);
	}
	cout << "search max - " << clock() - start_time << endl;
	// sort
	start_time = clock();
	vector<pair<const string*, const unsigned*>> elems;
	for (auto it = pattern_count.begin(); it != pattern_count.end(); ++it)
	{
		elems.push_back(make_pair(&it->first, &it->second));
	}
	sort(elems.begin(), elems.end(), [](auto left, auto right)
	{
		return *(left.first) < *(right.first);
	});
	cout << "sort - " << clock() - start_time << endl;

	// output
	start_time = clock();
	ofstream fout("out.txt");
	if (!fout.is_open()) return 1;
	for (auto itc = count.rbegin(); itc != count.rend(); ++itc)
	{
		for (auto ite = elems.begin(); ite != elems.end(); ++ite)
		{
			if (*(ite->second) == *itc) fout << *(ite->first) << " : " << *(ite->second) << endl;
		}
	}
	fout.close();
	cout << "output - " << clock() - start_time << endl;
	return 0;
}

